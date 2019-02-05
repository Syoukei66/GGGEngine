#include "DX11GraphicsAPI.h"

#if GG_GRAPHICS_API_DX11

#include <Native/Windows/WindowsApplication.h>
#include <Core/Application/Activity/Activity.h>

#include "imgui\imgui_impl_dx11.h"
#include "DX11Constants.h"

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

  HWND hwnd = WindowsApplication::GetMainActivityContext().GetWindowHandle();

  RECT rect;
  GetClientRect(hwnd, &rect);

  UINT width = rect.right - rect.left;
  UINT height = rect.bottom - rect.top;

  this->swap_chain_desc_.BufferCount = 1;
  this->swap_chain_desc_.BufferDesc.Width = width;
  this->swap_chain_desc_.BufferDesc.Height = height;
  this->swap_chain_desc_.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  this->swap_chain_desc_.BufferDesc.RefreshRate.Numerator = 60; // リフレッシュレート分母
  this->swap_chain_desc_.BufferDesc.RefreshRate.Denominator = 1; // リフレッシュレート分子
  this->swap_chain_desc_.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  this->swap_chain_desc_.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
  this->swap_chain_desc_.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  this->swap_chain_desc_.OutputWindow = hwnd;
  this->swap_chain_desc_.SampleDesc.Count = 1; // マルチサンプリング数
  this->swap_chain_desc_.SampleDesc.Quality = 0; //マルチサンプリングクオリティ
  this->swap_chain_desc_.Windowed = TRUE;
  this->swap_chain_desc_.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

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
      &this->swap_chain_desc_,
      &this->swap_chains_[hwnd],
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

  // Create DXGI Objects
  this->device_->QueryInterface(__uuidof(IDXGIDevice1), (void**)&this->dxgi_);
  this->dxgi_->GetAdapter(&this->adapter_);
  this->adapter_->GetParent(__uuidof(IDXGIFactory), (void**)&this->factory_);

  this->CreateRenderTargets(Application::GetMainActivity());

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

  for (const auto& pair : this->render_target_views_)
  {
    pair.second->Release();
  }
  for (const auto& pair : this->depth_stencil_views_)
  {
    pair.second->Release();
  }
  for (const auto& pair : this->swap_chains_)
  {
    pair.second->Release();
  }
  if (this->immediate_context_) this->immediate_context_->ClearState();
  if (this->immediate_context_) this->immediate_context_->Release();
  if (this->factory_) this->factory_->Release();
  if (this->adapter_) this->adapter_->Release();
  if (this->dxgi_) this->dxgi_->Release();  
  if (this->device_) this->device_->Release();

  return true;
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void DX11GraphicsAPI::ViewportClear(const SharedRef<Activity>& activity, const TColor& color)
{
  HWND hwnd = (HWND)activity->GetContext().GetActivityID();
  this->immediate_context_->ClearRenderTargetView(this->render_target_views_[hwnd], color.data);
  this->immediate_context_->ClearDepthStencilView(this->depth_stencil_views_[hwnd], D3D11_CLEAR_DEPTH, 1.0f, 0);
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

//void DX11GraphicsAPI::SetRenderTarget(const SharedRef<rcRenderBuffer>& color_buffer, const SharedRef<rcRenderBuffer>& depth_stencil_buffer, bool clear)
//{
//}

void DX11GraphicsAPI::SetRenderTarget(const SharedRef<Activity>& activity)
{
  HWND hwnd = (HWND)activity->GetContext().GetActivityID();
  this->immediate_context_->OMSetRenderTargets(1, &this->render_target_views_[hwnd], this->depth_stencil_views_[hwnd]);
}

void DX11GraphicsAPI::ResetRenderTarget()
{
}

void DX11GraphicsAPI::DrawIndexedPrimitive(Vertex::PrimitiveType primitive_type, const SharedRef<const rcIndexBuffer>& index_buffer)
{
  this->immediate_context_->IASetPrimitiveTopology(DX11::PRIMITIVE_TYPES[static_cast<T_UINT32>(primitive_type)]);
  this->immediate_context_->DrawIndexed(index_buffer->GetVertexCount(), 0, 0);
}

bool DX11GraphicsAPI::ImGuiNewFrame()
{
  ImGui_ImplDX11_NewFrame();
  return true;
}

void DX11GraphicsAPI::CreateSubActivityResources(const SharedRef<Activity>& activity)
{
  HWND hwnd = (HWND)activity->GetContext().GetActivityID();
  this->swap_chain_desc_.OutputWindow = hwnd;
  this->factory_->CreateSwapChain(
    this->device_,
    &this->swap_chain_desc_,
    &this->swap_chains_[hwnd]
    );
  this->CreateRenderTargets(activity);
}

void DX11GraphicsAPI::CreateRenderTargets(const SharedRef<Activity>& activity)
{  
  const ActivityOption& option = activity->GetContext().GetOption();
  HWND hwnd = (HWND)activity->GetContext().GetActivityID();

  activity->GetContext().GetImGuiContext()->IO.Fonts->TexID = Application::GetMainActivity()->GetContext().GetImGuiContext()->IO.Fonts->TexID;

  // Create a render target view
  ID3D11Texture2D* pBackBuffer = NULL;
  HRESULT hr = this->swap_chains_[hwnd]->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
  GG_ASSERT(SUCCEEDED(hr), "バックバッファの作成に失敗しました");

  hr = this->device_->CreateRenderTargetView(pBackBuffer, NULL, &this->render_target_views_[hwnd]);
  pBackBuffer->Release();
  GG_ASSERT(SUCCEEDED(hr), "レンダーターゲットビューの作成に失敗しました");

  // Create a depth stencil buffer 
  ID3D11Texture2D* depth_stencil_buffer = NULL;

  D3D11_TEXTURE2D_DESC desc_ds;
  desc_ds.Width = (UINT)option.window_size.width;
  desc_ds.Height = (UINT)option.window_size.height;
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

  hr = this->device_->CreateDepthStencilView(depth_stencil_buffer, NULL, &this->depth_stencil_views_[hwnd]);
  depth_stencil_buffer->Release();
  GG_ASSERT(SUCCEEDED(hr), "深度・ステンシルビューの作成に失敗しました");

}

bool DX11GraphicsAPI::PreDraw(const SharedRef<Activity>& activity)
{
  return true;
}

bool DX11GraphicsAPI::PostDraw(const SharedRef<Activity>& activity)
{
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
  HWND hwnd = (HWND)activity->GetContext().GetActivityID();
  this->swap_chains_[hwnd]->Present(0, 0);
  return true;
}

#endif