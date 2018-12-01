#include "DX11GraphicsAPI.h"

#include <Native/Windows/WindowsApplication.h>

#include "imgui\imgui_impl_dx11.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(DX11GraphicsAPI)
{
  D3D_DRIVER_TYPE driverTypes[] =
  {
      D3D_DRIVER_TYPE_HARDWARE,
      D3D_DRIVER_TYPE_WARP,
      D3D_DRIVER_TYPE_REFERENCE,
  };
  UINT numDriverTypes = ARRAYSIZE(driverTypes);

  D3D_FEATURE_LEVEL featureLevels[] =
  {
      D3D_FEATURE_LEVEL_11_0,
      D3D_FEATURE_LEVEL_10_1,
      D3D_FEATURE_LEVEL_10_0,
  };
  UINT numFeatureLevels = ARRAYSIZE(featureLevels);

  UINT createDeviceFlags = 0;
#ifdef _DEBUG
  createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

  HWND hwnd = WindowsApplication::GetMainActivity()->GetWindowHandle();

  RECT rect;
  GetClientRect(hwnd, &rect);

  UINT width = rect.right - rect.left;
  UINT height = rect.bottom - rect.top;

  DXGI_SWAP_CHAIN_DESC sd;
  ZeroMemory(&sd, sizeof(sd));
  sd.BufferCount = 1;
  sd.BufferDesc.Width = width;
  sd.BufferDesc.Height = height;
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  sd.BufferDesc.RefreshRate.Numerator = 60; // リフレッシュレート分母
  sd.BufferDesc.RefreshRate.Denominator = 1; // リフレッシュレート分子
  sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.OutputWindow = hwnd;
  sd.SampleDesc.Count = 1; // マルチサンプリング数
  sd.SampleDesc.Quality = 0; //マルチサンプリングクオリティ
  sd.Windowed = TRUE;
  sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

  HRESULT hr = S_OK;

  this->driver_type_ = D3D_DRIVER_TYPE_NULL;
  for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
  {
    this->driver_type_ = driverTypes[driverTypeIndex];
    hr = D3D11CreateDeviceAndSwapChain(
      NULL,
      this->driver_type_,
      NULL,
      createDeviceFlags,
      featureLevels,
      numFeatureLevels,
      D3D11_SDK_VERSION, 
      &sd,
      &this->swap_chain_, 
      &this->device_, 
      &this->feature_level_, 
      &this->immediate_context_
    );
    if (SUCCEEDED(hr))
    {
      break;
    }
  }
  if (FAILED(hr))
  {
    return false;
  }

  // Create a render target view
  ID3D11Texture2D* pBackBuffer = NULL;
  hr = this->swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
  if (FAILED(hr))
  {
    return false;
  }

  hr = this->device_->CreateRenderTargetView(pBackBuffer, NULL, &this->render_target_view_);
  pBackBuffer->Release();
  if (FAILED(hr))
  {
    return false;
  }

  this->immediate_context_->OMSetRenderTargets(1, &this->render_target_view_, NULL);

  // Setup the viewport
  D3D11_VIEWPORT vp;
  vp.Width = (FLOAT)width;
  vp.Height = (FLOAT)height;
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;
  this->immediate_context_->RSSetViewports(1, &vp);

  // imgui initialize
  ImGui_ImplDX11_Init(this->device_, this->immediate_context_);
  return true;
}

GG_DESTRUCT_FUNC_IMPL(DX11GraphicsAPI)
{
  //imgui uninitialize
  ImGui_ImplDX11_Shutdown();

  if (this->immediate_context_) this->immediate_context_->ClearState();
  if (this->render_target_view_) this->render_target_view_->Release();
  if (this->swap_chain_) this->swap_chain_->Release();
  if (this->immediate_context_) this->immediate_context_->Release();
  if (this->device_) this->device_->Release();

  return true;
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void DX11GraphicsAPI::ViewportClear(const TColor& color)
{
  this->immediate_context_->ClearRenderTargetView(this->render_target_view_, color.data);
  this->swap_chain_->Present(0, 0);
}

void DX11GraphicsAPI::SetViewport(T_FLOAT x, T_FLOAT y, T_FLOAT w, T_FLOAT h, T_FLOAT minZ, T_FLOAT maxZ)
{
}

void DX11GraphicsAPI::PackColor4u8(T_FIXED_UINT32* color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a)
{
}

void DX11GraphicsAPI::UnpackColor4u8(T_FIXED_UINT32 color, T_UINT8* r, T_UINT8* g, T_UINT8* b, T_UINT8* a)
{
}

void DX11GraphicsAPI::SetRenderTarget(const SharedRef<rcRenderBuffer>& color_buffer, const SharedRef<rcRenderBuffer>& depth_stencil_buffer, bool clear)
{
}

void DX11GraphicsAPI::ResetRenderTarget()
{
}

void DX11GraphicsAPI::DrawStencilBuffer()
{
}

void DX11GraphicsAPI::DrawIndexedPrimitive(Vertex::PrimitiveType primitive_type, const SharedRef<const rcIndexBuffer>& index_buffer)
{
}

UniqueRef<rcTexture> DX11GraphicsAPI::TextureLoad(const char* path)
{
  return UniqueRef<rcTexture>();
}

void DX11GraphicsAPI::DeleteTexture(rcTexture* texture)
{
}

void DX11GraphicsAPI::GetTextureSize(const rcTexture* texture, T_UINT16* width_dest, T_UINT16* height_dest)
{
}

UniqueRef<rcRenderBuffer> DX11GraphicsAPI::CreateColorBuffer(const SharedRef<const rcTexture>& texture)
{
  return UniqueRef<rcRenderBuffer>();
}

UniqueRef<rcRenderBuffer> DX11GraphicsAPI::CreateDepthStencilBuffer(T_UINT16 width, T_UINT16 height, ::Graphics::PixelFormat format)
{
  return UniqueRef<rcRenderBuffer>();
}

void DX11GraphicsAPI::DeleteRenderBuffer(rcRenderBuffer* render_buffer)
{
}

UniqueRef<rcRenderTexture> DX11GraphicsAPI::CreateRenderTexture(T_UINT16 width, T_UINT16 height, ::Graphics::PixelFormat format, ::Graphics::PixelFormat depth_format)
{
  return UniqueRef<rcRenderTexture>();
}

UniqueRef<rcShader> DX11GraphicsAPI::ShaderLoad(const char* path)
{
  return UniqueRef<rcShader>();
}

UniqueRef<rcVertexBuffer> DX11GraphicsAPI::CreateVertexBuffer(T_UINT32 size)
{
  return UniqueRef<rcVertexBuffer>();
}

UniqueRef<rcIndexBuffer> DX11GraphicsAPI::CreateIndexBuffer(T_UINT32 vertex_count, T_UINT32 polygon_count, Vertex::IndexFormat format)
{
  return UniqueRef<rcIndexBuffer>();
}

UniqueRef<rcVertexDeclaration> DX11GraphicsAPI::CreateVertexDeclaration(T_UINT32 format)
{
  return UniqueRef<rcVertexDeclaration>();
}

bool DX11GraphicsAPI::ImGuiNewFrame()
{
  ImGui_ImplDX11_NewFrame();
  return true;
}

bool DX11GraphicsAPI::PreDraw()
{
  return true;
}

bool DX11GraphicsAPI::PostDraw()
{
  //imgui
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

  this->swap_chain_->Present(0, 0);
  return true;
}
