#include "DirectXActivity.h"

#define NOMINMAX
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <Texture.h>
#include <Color.h>
#include <Director.h>
#include <NativeMethod.h>

#include "NativeProcess_Graphics.h"
#include "NativeProcess_IO.h"
#include "NativeProcess_Time.h"

#include "DirectXDirector.h"
#include "AudioManager.h"

#include "imgui\imgui.h"
#include "imgui\imgui_impl_dx9.h"
#include "imgui_ja_gryph_ranges.h"

#ifdef _DEBUG
static const T_UINT8 DEBUG_FONT_WIDTH = 16;
static const T_UINT8 DEBUG_FONT_HEIGHT = 32;
#endif

// =================================================================
// Constructor / Destructor
// =================================================================
DirectXActivity::DirectXActivity(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
  : instance_(hInstance)
  , prev_instance_(hPrevInstance)
  , cmdline_(lpCmdLine)
  , show_cmd_(nShowCmd)
  , wnd_(NULL)
  , before_update_count_(0)
  , d3d_(NULL)
  , d3d_device_(NULL)
  , input_(NULL)
  , msg_()
#ifdef _DEBUG
  , debug_font_(NULL)
#endif
{}

DirectXActivity::~DirectXActivity()
{
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
INativeProcess_Graphics* DirectXActivity::SetupNativeProcess_Graphics()
{
  return new NativeProcess_Graphics();
}

INativeProcess_IO* DirectXActivity::SetupNativeProcess_IO()
{
  return new NativeProcess_IO();
}

INativeProcess_Time* DirectXActivity::SetupNativeProcess_Time()
{
  return new NativeProcess_Time();
}

bool DirectXActivity::ApplyEngineOption(const EngineOption* option)
{
  WNDCLASSEX wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_VREDRAW | CS_HREDRAW | CS_CLASSDC;
  wcex.lpfnWndProc = this->WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = this->instance_;
  wcex.hIcon = NULL;
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = option->activity_name;
  wcex.hIconSm = NULL;

  RegisterClassEx(&wcex);
  DWORD windowStyle = WS_OVERLAPPEDWINDOW & ~WS_MINIMIZEBOX & ~WS_MAXIMIZEBOX;
  RECT wr = { 0, 0, option->window_size.width, option->window_size.height };
  int windowWidth = wr.right - wr.left;
  int windowHeight = wr.bottom - wr.top;

  AdjustWindowRect(&wr, windowStyle, true);

  RECT dr;
  GetWindowRect(GetDesktopWindow(), &dr);

  int desktopWidth = dr.right - dr.left;
  int desktopHeight = dr.bottom - dr.top;
  int windowX = desktopWidth < windowWidth ? 0 : (desktopWidth - windowWidth) >> 1;
  int windowY = desktopHeight < windowHeight ? 0 : (desktopHeight - windowHeight) >> 1;

  this->wnd_ = CreateWindowEx(
    0,				//�g���E�B���h�E�X�^�C��
    option->activity_name,	//�o�^����Ă���N���X��
    option->activity_name,	//�E�B���h�E��
    windowStyle,	//�E�B���h�E�X�^�C��
    windowX,	//�E�B���h�E�������̈ʒu
    windowY,	//�E�B���h�E�c�����̈ʒu
    windowWidth,	//�E�B���h�E�̕�
    windowHeight,	//�E�B���h�E�̍���
    NULL,		//�e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
    NULL,		//���j���[�n���h���܂��͎q���ʎq
    this->instance_,	//�A�v���P�[�V�����C���X�^���X�̃n���h��
    NULL		//�E�B���h�E�쐬�f�[�^
  );
  ShowWindow(this->wnd_, this->show_cmd_);
  UpdateWindow(this->wnd_);
  return false;
}

bool DirectXActivity::Init(const EngineOption* option)
{
  DirectXDirector::GetInstance().SetActivity(this);
  this->native_implements_ = new DirectXNativeImplements();

  D3DPRESENT_PARAMETERS d3dpp;
  D3DDISPLAYMODE d3ddm;

  // Direct3D�C���^�t�F�[�X�̍쐬
  this->d3d_ = Direct3DCreate9(D3D9b_SDK_VERSION);
  if (!this->d3d_)
  {
    //DirectX�����^�C�����擾�ł��Ȃ�����
    return false;
  }
  //���݂̃f�B�X�v���C���[�h���擾
  if (FAILED(this->d3d_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
  {
    return false;
  }
  
  //�f�o�C�X�̃v���[���e�[�V�����p�����[�^���擾
  ZeroMemory(&d3dpp, sizeof(d3dpp));
  d3dpp.BackBufferWidth = this->window_rect_.right - this->window_rect_.left;
  d3dpp.BackBufferHeight = this->window_rect_.top - this->window_rect_.bottom;
  d3dpp.BackBufferFormat = d3ddm.Format;
  d3dpp.BackBufferCount = 1;
  d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  d3dpp.EnableAutoDepthStencil = TRUE;
  d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
  d3dpp.Windowed = TRUE;
  d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
  d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

  if (FAILED(this->d3d_->CreateDevice(
    D3DADAPTER_DEFAULT,
    D3DDEVTYPE_HAL,
    this->wnd_,
    D3DCREATE_HARDWARE_VERTEXPROCESSING,
    &d3dpp,
    &this->d3d_device_ //�o���オ�����f�o�C�X
  )))
  {
    MessageBox(NULL, "DirectX�f�o�C�X���쐬�ł��܂���ł����B", "���m�点", MB_OK);
  }

  //�e�N�X�`���̐ݒ�
  this->d3d_device_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
  this->d3d_device_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
  this->d3d_device_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

  this->d3d_device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
  this->d3d_device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
  this->d3d_device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

  this->d3d_device_->SetRenderState(D3DRS_LIGHTING, false);
  this->d3d_device_->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

  //�e�N�X�`���̃A�h���X�O���Q�Ƃ����ꍇ�ɂǂ����邩�̐ݒ�
  //g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, XXXXX);
  //g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, XXXXX);

  //CLAMP ��Ԓ[��pixel�������L�΂����

  //�X�P�[�����}�C�i�X�ɂ������ɔ��]�`�悳���悤��
  //g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

  //�����x��K�p���邽�߂̏���
  this->d3d_device_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
  // SRC_RGB * SRC_�� + DEST_RGB * (1 - SRC_��)
  this->d3d_device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
  this->d3d_device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

  this->input_ = new DirectXInputDeviceManager();
  this->native_implements_->SetupInputDevices(this->input_);

  //�f�o�b�O�p�t�H���g
#ifdef _DEBUG
  D3DXCreateFont(
    this->d3d_device_, //Device
    DEBUG_FONT_HEIGHT, // Height
    DEBUG_FONT_WIDTH,  // Width
    0,  // Weight
    0,  // MipLevels
    0,  // Italic
    0,  // CharSet
    0,  // OutputPrecision
    0,  // Quality
    0,  // PitchAndFamily
    0,  // Facename
    &this->debug_font_  //LPD3DXFONT*
    );
#endif

  //imgui initialize
  ImGui_ImplDX9_Init(this->GetHWnd(), this->d3d_device_);
  ImGui::StyleColorsDark();
  ImGui::SetupJapaneseString();

  AudioManager::GetInstance().Init();

  return true;
}

bool DirectXActivity::Uninit()
{
  AudioManager::GetInstance().Uninit();

  //imgui uninitialize
  ImGui_ImplDX9_Shutdown();

  if (this->d3d_device_)
  {	//�f�o�C�X�̉�� (�d�v)
    this->d3d_device_->Release();
    this->d3d_device_ = nullptr;
  }
  if (this->input_)
  {
    this->input_->UnloadDevices();
    delete this->input_;
    this->input_ = nullptr;
  }
#ifdef _DEBUG
  if (this->debug_font_)
  {
    this->debug_font_->Release();
    this->debug_font_ = nullptr;
  }
#endif
  if (this->d3d_)
  {
    this->d3d_->Release();
    this->d3d_ = nullptr;
  }
  delete this->native_implements_;
  return true;
}

bool DirectXActivity::FrameEnabled()
{
  if (PeekMessage(&this->msg_, NULL, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&this->msg_);
    DispatchMessage(&this->msg_);
    return false;
  }
  //imgui
  ImGui_ImplDX9_NewFrame();
  return true;
}

bool DirectXActivity::ContinueEnabled()
{
  return this->msg_.message != WM_QUIT;
}

bool DirectXActivity::PreDraw()
{
  //imgui
  ImGui::EndFrame();

  if (SUCCEEDED(this->d3d_device_->BeginScene()))
  {
    return true;
  }
  return false;
}

void DirectXActivity::PostDraw()
{
#ifdef _DEBUG  
  D3DVIEWPORT9 viewport;
  viewport.X = 0;
  viewport.Y = 0;
  viewport.Width = (DWORD)Director::GetInstance()->GetScreenWidth();
  viewport.Height = (DWORD)Director::GetInstance()->GetScreenHeight();
  viewport.MinZ = 0.0f;
  viewport.MaxZ = 1.0f;
  this->d3d_device_->SetViewport(&viewport);

  const T_UINT8 edge = 2;
  const std::string debug_text = std::to_string(NativeMethod::Time().FPS_GetValue());
  this->DrawFPS(debug_text.c_str(), -edge, -edge, 0xFF000000);
  this->DrawFPS(debug_text.c_str(), edge, -edge, 0xFF000000);
  this->DrawFPS(debug_text.c_str(), -edge, edge, 0xFF000000);
  this->DrawFPS(debug_text.c_str(), edge, edge, 0xFF000000);
  this->DrawFPS(debug_text.c_str(), 0, 0, 0xFFFFFFFF);
#endif

  //imgui
  ImGui::Render();

  this->d3d_device_->EndScene();
  this->d3d_device_->Present(NULL, NULL, NULL, NULL);
}

void DirectXActivity::InputProcess(EngineInputState* state)
{
  this->input_->InputProcess(state);
}

void DirectXActivity::DrawFPS(const char* text, T_FLOAT x, T_FLOAT y, T_UINT32 color)
{
#ifdef _DEBUG
  const T_UINT16 width = Director::GetInstance()->GetScreenWidth();
  const T_UINT16 height = Director::GetInstance()->GetScreenHeight();
  RECT rect = { (LONG)x, (LONG)y, (LONG)(x + width), (LONG)(y + height) };

  this->debug_font_->DrawText(
    NULL,
    text,
    -1,
    &rect,
    NULL,
    color
  );
#endif
}

// =================================================================
// Setter / Getter
// =================================================================
LP_DEVICE DirectXActivity::GetDevice() const
{
  return (LP_DEVICE)this->d3d_device_;
}

// =================================================================
// Method
// =================================================================
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT DirectXActivity::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
  {
    return true;
  }
  if (uMsg == WM_CLOSE) {
    DestroyWindow(hWnd);
  }
  if (uMsg == WM_DESTROY)
  {
    PostQuitMessage(0);
  }
  if (uMsg == WM_KEYDOWN)
  {
    if (wParam == VK_ESCAPE)
    {
      if (MessageBox(hWnd, "�I�����܂����H", "�I���̂��m�点", MB_YESNO | MB_NOFOCUS) == IDYES)
      {
        DestroyWindow(hWnd);
      }
    }
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
