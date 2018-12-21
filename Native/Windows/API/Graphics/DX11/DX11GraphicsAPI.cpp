#include "DX11GraphicsAPI.h"

#if GG_GRAPHICS_API_DX11

#include <Native/Windows/WindowsApplication.h>

#include "imgui\imgui_impl_dx11.h"
#include "DX11Constants.h"
#include "DX11TextureResource.h"

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
  GG_ASSERT(SUCCEEDED(hr), "ドライバが対応していません");

  // Create a render target view
  ID3D11Texture2D* pBackBuffer = NULL;
  hr = this->swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
  GG_ASSERT(SUCCEEDED(hr), "バックバッファの作成に失敗しました");

  hr = this->device_->CreateRenderTargetView(pBackBuffer, NULL, &this->render_target_view_);
  pBackBuffer->Release();
  GG_ASSERT(SUCCEEDED(hr), "レンダーターゲットビューの作成に失敗しました");

  // Create a depth stencil buffer 
  ID3D11Texture2D* depth_stencil_buffer = NULL;

  D3D11_TEXTURE2D_DESC desc_ds;
  desc_ds.Width = width;
  desc_ds.Height = height;
  desc_ds.MipLevels = 1;
  desc_ds.ArraySize = 1;
  desc_ds.Format = DXGI_FORMAT_D32_FLOAT;
  desc_ds.SampleDesc.Count = 1;
  desc_ds.SampleDesc.Quality = 0;
  desc_ds.Usage = D3D11_USAGE_DEFAULT;
  desc_ds.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  desc_ds.CPUAccessFlags = 0;
  desc_ds.MiscFlags = 0;
  hr = this->device_->CreateTexture2D(
    &desc_ds,
    NULL,
    &depth_stencil_buffer
  );
  GG_ASSERT(SUCCEEDED(hr), "深度・ステンシルバッファの作成に失敗しました");

  D3D11_DEPTH_STENCIL_VIEW_DESC desc_dsv;
  desc_dsv.Format = desc_ds.Format;
  desc_dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  desc_dsv.Flags = 0;
  desc_dsv.Texture2D.MipSlice = 0;

  hr = this->device_->CreateDepthStencilView(depth_stencil_buffer, NULL, &this->depth_stencil_view_);
  depth_stencil_buffer->Release();
  GG_ASSERT(SUCCEEDED(hr), "深度・ステンシルビューの作成に失敗しました");

  this->immediate_context_->OMSetRenderTargets(1, &this->render_target_view_, this->depth_stencil_view_);

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
  if (this->depth_stencil_view_) this->depth_stencil_view_->Release();
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
  this->immediate_context_->ClearDepthStencilView(this->depth_stencil_view_, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DX11GraphicsAPI::SetViewport(T_FLOAT x, T_FLOAT y, T_FLOAT w, T_FLOAT h, T_FLOAT minZ, T_FLOAT maxZ)
{
  D3D11_VIEWPORT vp;
  vp.TopLeftX = x;
  vp.TopLeftY = y;
  vp.Width = w;
  vp.Height = h;
  vp.MinDepth = minZ;
  vp.MaxDepth = maxZ;
  this->immediate_context_->RSSetViewports(1, &vp);
}

void DX11GraphicsAPI::PackColor4u8(T_FIXED_UINT32* color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a)
{
  (*color) = 
    (r & 0xff) << 24 |
    (g & 0xff) << 16 |
    (b & 0xff) << 8 |
    (a & 0xff) << 0
    ;
}

void DX11GraphicsAPI::UnpackColor4u8(T_FIXED_UINT32 color, T_UINT8* r, T_UINT8* g, T_UINT8* b, T_UINT8* a)
{
  (*r) = (color >> 24) & 0xff;
  (*g) = (color >> 16) & 0xff;
  (*b) = (color >> 8) & 0xff;
  (*a) = (color >> 0) & 0xff;
}

void DX11GraphicsAPI::SetRenderTarget(const SharedRef<rcRenderBuffer>& color_buffer, const SharedRef<rcRenderBuffer>& depth_stencil_buffer, bool clear)
{
}

void DX11GraphicsAPI::ResetRenderTarget()
{
}

void DX11GraphicsAPI::DrawIndexedPrimitive(Vertex::PrimitiveType primitive_type, const SharedRef<const rcIndexBuffer>& index_buffer)
{
  this->immediate_context_->IASetPrimitiveTopology(DX11::PRIMITIVE_TYPES[static_cast<T_UINT32>(primitive_type)]);
  this->immediate_context_->DrawIndexed(index_buffer->GetVertexCount(), 0, 0);
}


#include <DirectXTex.h>
//#include <Editor/ThirdParty/DirectXTex/DirectXTex.inl>
#include <Editor/ThirdParty/DirectXTex/WICTextureLoader/WICTextureLoader.h>

#pragma comment(lib, "DirectXTex.lib")

#include <regex>

UniqueRef<rcTexture> DX11GraphicsAPI::TextureLoad(const char* path)
{
  ID3D11Resource* texture;
  ID3D11ShaderResourceView* shader_resource_view;

  std::string filename = path;
  std::regex re("(.+)\\.(.+)");
  std::smatch result;
  std::regex_match(filename, result, re);
  std::string extension = result[2];

  WCHAR	wpath[256] = {};

  size_t wLen = 0;
  errno_t err = 0;

  //ロケール指定
  setlocale(LC_ALL, "japanese");
  //変換
  err = mbstowcs(wpath, path, sizeof(wpath));
  DirectX::TexMetadata metadata;
  DirectX::ScratchImage image;


  HRESULT hr = S_FALSE;
  if (extension == "tga")
  {
    hr = DirectX::LoadFromTGAFile(wpath, &metadata, image);
  }
  else
  {
    hr = DirectX::LoadFromWICFile(wpath, 0, &metadata, image);
  }
  GG_ASSERT(SUCCEEDED(hr), "テクスチャの読み込みに失敗しました");

  hr = DirectX::CreateShaderResourceView(this->device_, image.GetImages(), image.GetImageCount(), metadata, &shader_resource_view);
  GG_ASSERT(SUCCEEDED(hr), "シェーダーリソースビューの作成に失敗しました");

  return rcTexture::Create(metadata.width, metadata.height, UniqueRef<DX11TextureResource>(new DX11TextureResource(shader_resource_view)));
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

#endif