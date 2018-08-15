#include "NativeSound.h"
#include "../Core/NativeAssert.h"
#include "AudioManager.h"

//=============================================================================
// �`�����N�̃`�F�b�N
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
  {// �t�@�C���|�C���^��擪�Ɉړ�
    return HRESULT_FROM_WIN32(GetLastError());
  }

  while (hr == S_OK)
  {
    if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
    {// �`�����N�̓ǂݍ���
      hr = HRESULT_FROM_WIN32(GetLastError());
    }

    if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
    {// �`�����N�f�[�^�̓ǂݍ���
      hr = HRESULT_FROM_WIN32(GetLastError());
    }

    switch (dwChunkType)
    {
    case 'FFIR':
      dwRIFFDataSize = dwChunkDataSize;
      dwChunkDataSize = 4;
      if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
      {// �t�@�C���^�C�v�̓ǂݍ���
        hr = HRESULT_FROM_WIN32(GetLastError());
      }
      break;

    default:
      if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
      {// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
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
// �`�����N�f�[�^�̓ǂݍ���
//=============================================================================
static HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
  DWORD dwRead;

  if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
  {// �t�@�C���|�C���^���w��ʒu�܂ňړ�
    return HRESULT_FROM_WIN32(GetLastError());
  }

  if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
  {// �f�[�^�̓ǂݍ���
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

  // �o�b�t�@�̃N���A
  memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
  memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

  // �T�E���h�f�[�^�t�@�C���̐���
  hFile = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
  if (hFile == INVALID_HANDLE_VALUE)
  {
    NATIVE_ASSERT(false, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)");
  }
  if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
  {// �t�@�C���|�C���^��擪�Ɉړ�
    NATIVE_ASSERT(false, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)");
  }

  HRESULT hr;
  // WAVE�t�@�C���̃`�F�b�N
  hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
  NATIVE_ASSERT(SUCCEEDED(hr), "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)");
  hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
  NATIVE_ASSERT(SUCCEEDED(hr), "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)");
  if (dwFiletype != 'EVAW')
  {
    NATIVE_ASSERT(FAILED(hr), "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)");
  }

  // �t�H�[�}�b�g�`�F�b�N
  hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
  NATIVE_ASSERT(SUCCEEDED(hr), "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)");
  hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
  NATIVE_ASSERT(SUCCEEDED(hr), "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)");

  // �I�[�f�B�I�f�[�^�ǂݍ���
  hr = CheckChunk(hFile, 'atad', &this->size_audio_, &dwChunkPosition);
  NATIVE_ASSERT(SUCCEEDED(hr), "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)");
  this->data_audio_ = (BYTE*)malloc(this->size_audio_);
  hr = ReadChunkData(hFile, this->data_audio_, this->size_audio_, dwChunkPosition);
  NATIVE_ASSERT(SUCCEEDED(hr), "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)");

  // �\�[�X�{�C�X�̐���
  hr = AudioManager::GetInstance().GetXAudio()->CreateSourceVoice(&this->souce_voice_, &(wfx.Format));
  NATIVE_ASSERT(SUCCEEDED(hr), "�\�[�X�{�C�X�̐����Ɏ��s�I");
}

NativeSound::~NativeSound()
{
  if (this->souce_voice_)
  {
    // �ꎞ��~
    this->souce_voice_->Stop(0);

    // �\�[�X�{�C�X�̔j��
    this->souce_voice_->DestroyVoice();
    this->souce_voice_ = nullptr;

    // �I�[�f�B�I�f�[�^�̊J��
    free(this->data_audio_);
    this->data_audio_ = nullptr;
  }
}

void NativeSound::Play(T_UINT8 loop_count)
{
  XAUDIO2_VOICE_STATE xa2state;
  XAUDIO2_BUFFER buffer;

  // �o�b�t�@�̒l�ݒ�
  memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
  buffer.AudioBytes = this->size_audio_;
  buffer.pAudioData = this->data_audio_;
  buffer.Flags = XAUDIO2_END_OF_STREAM;
  buffer.LoopCount = loop_count;

  // ��Ԏ擾
  this->souce_voice_->GetState(&xa2state);
  if (xa2state.BuffersQueued != 0)
  {// �Đ���
    // �ꎞ��~
    this->souce_voice_->Stop(0);

    // �I�[�f�B�I�o�b�t�@�̍폜
    this->souce_voice_->FlushSourceBuffers();
  }

  // �I�[�f�B�I�o�b�t�@�̓o�^
  this->souce_voice_->SubmitSourceBuffer(&buffer);

  // �Đ�
  this->souce_voice_->Start(0);
}

void NativeSound::Stop()
{
  XAUDIO2_VOICE_STATE xa2state;

  // ��Ԏ擾
  this->souce_voice_->GetState(&xa2state);
  if (xa2state.BuffersQueued != 0)
  {// �Đ���
   // �ꎞ��~
    this->souce_voice_->Stop(0);

    // �I�[�f�B�I�o�b�t�@�̍폜
    this->souce_voice_->FlushSourceBuffers();
  }
}

void NativeSound::Pause()
{
  this->souce_voice_->Stop(0);
}

void NativeSound::Resume()
{
  // �Đ�
  this->souce_voice_->Start(0);
}
