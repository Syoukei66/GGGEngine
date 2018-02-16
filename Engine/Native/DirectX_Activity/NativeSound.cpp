#include "NativeSound.h"
#include "NativeAssert.h"
#include "AudioManager.h"

//=============================================================================
// チャンクのチェック
//=============================================================================
static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
  HRESULT hr = S_OK;
  DWORD dwRead;
  DWORD dwChunkType;
  DWORD dwChunkDataSize;
  DWORD dwRIFFDataSize = 0;
  DWORD dwFileType;
  DWORD dwBytesRead = 0;
  DWORD dwOffset = 0;

  if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
  {// ファイルポインタを先頭に移動
    return HRESULT_FROM_WIN32(GetLastError());
  }

  while (hr == S_OK)
  {
    if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
    {// チャンクの読み込み
      hr = HRESULT_FROM_WIN32(GetLastError());
    }

    if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
    {// チャンクデータの読み込み
      hr = HRESULT_FROM_WIN32(GetLastError());
    }

    switch (dwChunkType)
    {
    case 'FFIR':
      dwRIFFDataSize = dwChunkDataSize;
      dwChunkDataSize = 4;
      if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
      {// ファイルタイプの読み込み
        hr = HRESULT_FROM_WIN32(GetLastError());
      }
      break;

    default:
      if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
      {// ファイルポインタをチャンクデータ分移動
        return HRESULT_FROM_WIN32(GetLastError());
      }
    }

    dwOffset += sizeof(DWORD) * 2;
    if (dwChunkType == format)
    {
      *pChunkSize = dwChunkDataSize;
      *pChunkDataPosition = dwOffset;

      return S_OK;
    }

    dwOffset += dwChunkDataSize;
    if (dwBytesRead >= dwRIFFDataSize)
    {
      return S_FALSE;
    }
  }

  return S_OK;
}

//=============================================================================
// チャンクデータの読み込み
//=============================================================================
static HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
  DWORD dwRead;

  if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
  {// ファイルポインタを指定位置まで移動
    return HRESULT_FROM_WIN32(GetLastError());
  }

  if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
  {// データの読み込み
    return HRESULT_FROM_WIN32(GetLastError());
  }

  return S_OK;
}

NativeSound::NativeSound(const char* path)
  : INativeSound(nullptr)
{
  HANDLE hFile;
  DWORD dwChunkSize = 0;
  DWORD dwChunkPosition = 0;
  DWORD dwFiletype;
  WAVEFORMATEXTENSIBLE wfx;
  XAUDIO2_BUFFER buffer;

  // バッファのクリア
  memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
  memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

  // サウンドデータファイルの生成
  hFile = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
  if (hFile == INVALID_HANDLE_VALUE)
  {
    NATIVE_ASSERT(false, "サウンドデータファイルの生成に失敗！(1)");
  }
  if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
  {// ファイルポインタを先頭に移動
    NATIVE_ASSERT(false, "サウンドデータファイルの生成に失敗！(2)");
  }

  HRESULT hr;
  // WAVEファイルのチェック
  hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
  NATIVE_ASSERT(SUCCEEDED(hr), "WAVEファイルのチェックに失敗！(1)");
  hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
  NATIVE_ASSERT(SUCCEEDED(hr), "WAVEファイルのチェックに失敗！(2)");
  if (dwFiletype != 'EVAW')
  {
    NATIVE_ASSERT(FAILED(hr), "WAVEファイルのチェックに失敗！(3)");
  }

  // フォーマットチェック
  hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
  NATIVE_ASSERT(SUCCEEDED(hr), "フォーマットチェックに失敗！(1)");
  hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
  NATIVE_ASSERT(SUCCEEDED(hr), "フォーマットチェックに失敗！(2)");

  // オーディオデータ読み込み
  hr = CheckChunk(hFile, 'atad', &this->size_audio_, &dwChunkPosition);
  NATIVE_ASSERT(SUCCEEDED(hr), "オーディオデータ読み込みに失敗！(1)");
  this->data_audio_ = (BYTE*)malloc(this->size_audio_);
  hr = ReadChunkData(hFile, this->data_audio_, this->size_audio_, dwChunkPosition);
  NATIVE_ASSERT(SUCCEEDED(hr), "オーディオデータ読み込みに失敗！(2)");

  // ソースボイスの生成
  hr = AudioManager::GetInstance().GetXAudio()->CreateSourceVoice(&this->souce_voice_, &(wfx.Format));
  NATIVE_ASSERT(SUCCEEDED(hr), "ソースボイスの生成に失敗！");
}

NativeSound::~NativeSound()
{
  if (this->souce_voice_)
  {
    // 一時停止
    this->souce_voice_->Stop(0);

    // ソースボイスの破棄
    this->souce_voice_->DestroyVoice();
    this->souce_voice_ = nullptr;

    // オーディオデータの開放
    free(this->data_audio_);
    this->data_audio_ = nullptr;
  }
}

void NativeSound::Play(T_UINT8 loop_count)
{
  XAUDIO2_VOICE_STATE xa2state;
  XAUDIO2_BUFFER buffer;

  // バッファの値設定
  memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
  buffer.AudioBytes = this->size_audio_;
  buffer.pAudioData = this->data_audio_;
  buffer.Flags = XAUDIO2_END_OF_STREAM;
  buffer.LoopCount = loop_count;

  // 状態取得
  this->souce_voice_->GetState(&xa2state);
  if (xa2state.BuffersQueued != 0)
  {// 再生中
    // 一時停止
    this->souce_voice_->Stop(0);

    // オーディオバッファの削除
    this->souce_voice_->FlushSourceBuffers();
  }

  // オーディオバッファの登録
  this->souce_voice_->SubmitSourceBuffer(&buffer);

  // 再生
  this->souce_voice_->Start(0);
}

void NativeSound::Stop()
{
  XAUDIO2_VOICE_STATE xa2state;

  // 状態取得
  this->souce_voice_->GetState(&xa2state);
  if (xa2state.BuffersQueued != 0)
  {// 再生中
   // 一時停止
    this->souce_voice_->Stop(0);

    // オーディオバッファの削除
    this->souce_voice_->FlushSourceBuffers();
  }
}

void NativeSound::Pause()
{
  this->souce_voice_->Stop(0);
}

void NativeSound::Resume()
{
  // 再生
  this->souce_voice_->Start(0);
}
