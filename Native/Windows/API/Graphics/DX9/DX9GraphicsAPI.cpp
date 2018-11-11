#include "DX9GraphicsAPI.h"

#define NOMINMAX
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <Core/Application/Platform/API/_Asset/Shader/Shader.h>
#include <Core/Application/Platform/API/_Asset/Texture/Texture.h>
#include <Core/Application/Platform/API/_Resource/RenderBuffer/RenderBuffer.h>
#include <Core/Application/Platform/API/_Resource/RenderTexture/RenderTexture.h>

#include <Native/Windows/Activity/WindowsActivity.h>

#include <Native/Windows/WindowsApplication.h>

#include <ThirdParty/imgui/imgui.h>
#include "imgui\imgui_impl_dx9.h"

#include "DX9Constants.h"
#include "DX9VertexBuffer.h"
#include "DX9IndexBuffer.h"
#include "DX9Shader.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(DX9GraphicsAPI)
{
  D3DPRESENT_PARAMETERS d3dpp;
  D3DDISPLAYMODE d3ddm;

  // Direct3Dインタフェースの作成
  this->d3d_ = Direct3DCreate9(D3D9b_SDK_VERSION);
  if (!this->d3d_)
  {
    //DirectXランタイムを取得できなかった
    return false;
  }
  //現在のディスプレイモードを取得
  if (FAILED(this->d3d_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
  {
    return false;
  }

  HWND hwnd = WindowsApplication::GetMainActivity()->GetWindowHandle();

  RECT rect;
  GetClientRect(hwnd, &rect);

  //デバイスのプレゼンテーションパラメータを取得
  ZeroMemory(&d3dpp, sizeof(d3dpp));
  d3dpp.BackBufferWidth = rect.right - rect.left;
  d3dpp.BackBufferHeight = rect.bottom - rect.top;
  d3dpp.BackBufferFormat = d3ddm.Format;
  d3dpp.BackBufferCount = 1;
  d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  d3dpp.EnableAutoDepthStencil = TRUE;
  d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
  d3dpp.Windowed = TRUE;
  d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
  d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

  if (FAILED(this->d3d_->CreateDevice(
    D3DADAPTER_DEFAULT,
    D3DDEVTYPE_HAL,
    hwnd,
    D3DCREATE_HARDWARE_VERTEXPROCESSING,
    &d3dpp,
    &this->d3d_device_ //出来上がったデバイス
  )))
  {
    MessageBox(NULL, "DirectXデバイスが作成できませんでした。", "お知らせ", MB_OK);
  }

  //テクスチャの設定
  this->d3d_device_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
  this->d3d_device_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
  this->d3d_device_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

  this->d3d_device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
  this->d3d_device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
  this->d3d_device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

  this->d3d_device_->SetRenderState(D3DRS_LIGHTING, false);
  this->d3d_device_->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

  //透明度を適用するための処理
  this->d3d_device_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
  // SRC_RGB * SRC_α + DEST_RGB * (1 - SRC_α)
  this->d3d_device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
  this->d3d_device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);




  // Set up the textures
  this->d3d_device_->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
  this->d3d_device_->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
  this->d3d_device_->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
  this->d3d_device_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
  this->d3d_device_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
  this->d3d_device_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
  this->d3d_device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
  this->d3d_device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

  // Set miscellaneous render states
  this->d3d_device_->SetRenderState(D3DRS_DITHERENABLE, FALSE);
  this->d3d_device_->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
  this->d3d_device_->SetRenderState(D3DRS_ZENABLE, TRUE);
  this->d3d_device_->SetRenderState(D3DRS_AMBIENT, 0x000F0F0F);

  //imgui initialize
  ImGui_ImplDX9_Init(this->d3d_device_);
  return true;
}

GG_DESTRUCT_FUNC_IMPL(DX9GraphicsAPI)
{
  //imgui uninitialize
  ImGui_ImplDX9_Shutdown();

  if (this->d3d_device_)
  {	//デバイスの解放 (重要)
    this->d3d_device_->Release();
    this->d3d_device_ = nullptr;
  }
  if (this->d3d_)
  {
    this->d3d_->Release();
    this->d3d_ = nullptr;
  }
  return true;
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void DX9GraphicsAPI::ViewportClear()
{
  this->d3d_device_->Clear(
    0, NULL,
    (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
    D3DCOLOR_RGBA(0, 0, 0, 255),
    1.0f, 0
  );
}

void DX9GraphicsAPI::SetViewport(T_FLOAT x, T_FLOAT y, T_FLOAT w, T_FLOAT h, T_FLOAT minZ, T_FLOAT maxZ)
{
  D3DVIEWPORT9 viewport;
  viewport.X = (DWORD)x;
  viewport.Y = (DWORD)y;
  viewport.Width = (DWORD)w;
  viewport.Height = (DWORD)h;
  viewport.MinZ = minZ;
  viewport.MaxZ = maxZ;
  this->d3d_device_->SetViewport(&viewport);
}

void DX9GraphicsAPI::PackColor4u8(T_FIXED_UINT32 * color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a)
{
  (*color) = (T_FIXED_UINT32)D3DCOLOR_RGBA(r, g, b, a);
}

static LPDIRECT3DSURFACE9 temp_color_buffer = nullptr;
static LPDIRECT3DSURFACE9 temp_depth_buffer = nullptr;

static SharedRef<rcRenderBuffer> use_color_buffer = nullptr;
static SharedRef<rcRenderBuffer> use_depth_stencil_buffer = nullptr;

void DX9GraphicsAPI::SetRenderTarget(const SharedRef<rcRenderBuffer>& color_buffer, const SharedRef<rcRenderBuffer>& depth_stencil_buffer, bool clear)
{
  use_color_buffer = color_buffer;
  use_depth_stencil_buffer = depth_stencil_buffer;

  this->d3d_device_->EndScene();

  //現在の各バッファを保持しておく
  GG_ASSERT(!temp_color_buffer && !temp_depth_buffer, "RenderBegin()を二重に呼び出しました。");
  this->d3d_device_->GetRenderTarget(0, &temp_color_buffer);
  this->d3d_device_->GetDepthStencilSurface(&temp_depth_buffer);

  HRESULT hr = this->d3d_device_->SetRenderTarget(0, (LPDIRECT3DSURFACE9)use_color_buffer->GetNativeObject());
  GG_ASSERT(SUCCEEDED(hr), "レンダ―ターゲットの設定に失敗しました");

  hr = this->d3d_device_->SetDepthStencilSurface((LPDIRECT3DSURFACE9)use_depth_stencil_buffer->GetNativeObject());
  GG_ASSERT(SUCCEEDED(hr), "深度バッファの設定に失敗しました");

  this->d3d_device_->BeginScene();

  if (clear)
  {
    this->d3d_device_->Clear(0,
      NULL,
      D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
      D3DCOLOR_ARGB(0, 0, 0, 255),
      1.0f,
      0);
  }
}

void DX9GraphicsAPI::ResetRenderTarget()
{
  this->d3d_device_->EndScene();

  HRESULT hr = this->d3d_device_->SetRenderTarget(0, temp_color_buffer);
  GG_ASSERT(SUCCEEDED(hr), "レンダ―ターゲットの設定に失敗しました");
  hr = this->d3d_device_->SetDepthStencilSurface(temp_depth_buffer);
  GG_ASSERT(SUCCEEDED(hr), "深度バッファの設定に失敗しました");

  temp_color_buffer = nullptr;
  temp_depth_buffer = nullptr;

  use_color_buffer = nullptr;
  use_depth_stencil_buffer = nullptr;

  this->d3d_device_->BeginScene();
}

LPDIRECT3DVERTEXBUFFER9 g_VertexBuffer = NULL;

typedef struct
{
  D3DXVECTOR4 pos;
  DWORD color;
  D3DXVECTOR2 texCood;
  enum {
    FVF = D3DFVF_XYZW | D3DFVF_DIFFUSE | D3DFVF_TEX1
  };
} VERTEX_2D;

void DX9GraphicsAPI::DrawStencilBuffer()
{
  this->d3d_device_->SetRenderState(D3DRS_ZENABLE, FALSE);
  this->d3d_device_->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
  this->d3d_device_->SetRenderState(D3DRS_STENCILENABLE, TRUE);
  this->d3d_device_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
  this->d3d_device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
  this->d3d_device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

  this->d3d_device_->SetRenderState(D3DRS_STENCILREF, 0x1);
  this->d3d_device_->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);
  this->d3d_device_->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

  if (!g_VertexBuffer)
  {
    this->d3d_device_->CreateVertexBuffer(
      sizeof(VERTEX_2D) * 4,
      D3DUSAGE_WRITEONLY,
      VERTEX_2D::FVF,
      D3DPOOL_MANAGED,
      &g_VertexBuffer,
      NULL
    );
    VERTEX_2D* pV;
    g_VertexBuffer->Lock(
      0, 0,
      (void**)&pV,
      D3DLOCK_DISCARD
    );

    const float dw = 2.0f;
    const float dh = 2.0f;
    const float dx = -dw * 0.5f;
    const float dy = -dh * 0.5f;

    const float tcx = 0.0f;
    const float tcy = 0.0f;
    const float tcw = 1.0f;
    const float tch = 1.0f;
    const float tw = 1.0;
    const float th = 1.0;

    //四角形の頂点座標を変数に確保しておく
    const float x0 = dx;
    const float y0 = dy;
    const float x1 = dx + dw;
    const float y1 = dy + dh;

    //テクスチャのUV座標を変数に確保しておく
    const float u0 = (float)tcx / tw;
    const float v0 = (float)tcy / th;
    const float u1 = (float)(tcx + tcw) / tw;
    const float v1 = (float)(tcy + tch) / th;

    //各頂点に座標設定
    pV[0].pos = D3DXVECTOR4(x0, y1, 0.0f, 1.0f);
    pV[1].pos = D3DXVECTOR4(x1, y1, 0.0f, 1.0f);
    pV[2].pos = D3DXVECTOR4(x0, y0, 0.0f, 1.0f);
    pV[3].pos = D3DXVECTOR4(x1, y0, 0.0f, 1.0f);

    //各頂点にテクスチャ座標設定
    pV[0].texCood = D3DXVECTOR2(u0, v0);
    pV[1].texCood = D3DXVECTOR2(u1, v0);
    pV[2].texCood = D3DXVECTOR2(u0, v1);
    pV[3].texCood = D3DXVECTOR2(u1, v1);

    //各頂点に色設定
    pV[0].color = D3DCOLOR_RGBA(0, 0, 0, 128);
    pV[1].color = D3DCOLOR_RGBA(0, 0, 0, 128);
    pV[2].color = D3DCOLOR_RGBA(0, 0, 0, 128);
    pV[3].color = D3DCOLOR_RGBA(0, 0, 0, 128);

    g_VertexBuffer->Unlock();
  }

  this->d3d_device_->SetFVF(VERTEX_2D::FVF);
  this->d3d_device_->SetStreamSource(0, g_VertexBuffer, 0, sizeof(VERTEX_2D));
  this->d3d_device_->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

  this->d3d_device_->SetRenderState(D3DRS_ZENABLE, TRUE);
  this->d3d_device_->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
  this->d3d_device_->SetRenderState(D3DRS_STENCILENABLE, FALSE);
  this->d3d_device_->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

}

UniqueRef<rcTexture> DX9GraphicsAPI::TextureLoad(const char* path)
{
  D3DXIMAGE_INFO info;
  HRESULT hr = D3DXGetImageInfoFromFile(
    path,
    &info
  );
  GG_ASSERT(SUCCEEDED(hr), "テクスチャサイズの取得に失敗しました");

  LPDIRECT3DTEXTURE9 tex = nullptr;
  hr = D3DXCreateTextureFromFileEx(
    (LPDIRECT3DDEVICE9)this->d3d_device_,
    path,
    D3DX_DEFAULT,
    D3DX_DEFAULT,
    D3DX_DEFAULT,
    0,
    D3DFMT_UNKNOWN,
    D3DPOOL_MANAGED,
    D3DX_FILTER_NONE,
    D3DX_DEFAULT,
    0,
    NULL,
    NULL,
    &tex);

  GG_ASSERT(SUCCEEDED(hr), "テクスチャのロードに失敗しました");

  return rcTexture::Create((T_UINT16)info.Width, (T_UINT16)info.Height, tex);
}

void DX9GraphicsAPI::DeleteTexture(rcTexture* texture)
{
  ((LPDIRECT3DTEXTURE9)texture->GetNativeObject())->Release();
}

void DX9GraphicsAPI::GetTextureSize(const rcTexture* texture, T_UINT16* width_dest, T_UINT16* height_dest)
{
  LPDIRECT3DTEXTURE9 tex = (LPDIRECT3DTEXTURE9)texture->GetNativeObject();

  D3DSURFACE_DESC desc;
  HRESULT hr = tex->GetLevelDesc(0, &desc);
  GG_ASSERT(SUCCEEDED(hr), "テクスチャの情報の取得に失敗しました");
  (*width_dest) = desc.Width;
  (*height_dest) = desc.Height;
}

UniqueRef<rcRenderBuffer> DX9GraphicsAPI::CreateColorBuffer(const SharedRef<const rcTexture>& texture)
{
  LPDIRECT3DTEXTURE9 tex = (LPDIRECT3DTEXTURE9)texture->GetNativeObject();
  LPDIRECT3DSURFACE9 surf;
  HRESULT hr = tex->GetSurfaceLevel(0, &surf);
  GG_ASSERT(SUCCEEDED(hr), "テクスチャのサーフェイスの取得に失敗しました");
  return rcRenderBuffer::Create(surf);
}

UniqueRef<rcRenderBuffer> DX9GraphicsAPI::CreateDepthStencilBuffer(T_UINT16 width, T_UINT16 height, ::Graphics::PixelFormat format)
{
  LPDIRECT3DSURFACE9 surf;
  HRESULT hr = this->d3d_device_->CreateDepthStencilSurface(
    width,
    height,
    DX9::TEXTURE_FORMATS[static_cast<T_UINT32>(format)],
    D3DMULTISAMPLE_NONE,
    0,
    TRUE,
    &surf,
    nullptr
  );
  GG_ASSERT(SUCCEEDED(hr), "深度バッファの作成に失敗しました");
  return rcRenderBuffer::Create(surf);
}

void DX9GraphicsAPI::DeleteRenderBuffer(rcRenderBuffer* render_buffer)
{
  ((LPDIRECT3DSURFACE9)render_buffer->GetNativeObject())->Release();
}

UniqueRef<rcRenderTexture> DX9GraphicsAPI::CreateRenderTexture(T_UINT16 width, T_UINT16 height, ::Graphics::PixelFormat format, ::Graphics::PixelFormat depth_format)
{
  using namespace DX9;
  width = Mathf::CalcTwoPowerValue(width);
  height = Mathf::CalcTwoPowerValue(height);
  
  //
  LPDIRECT3DTEXTURE9 tex = nullptr;

  HRESULT hr = D3DXCreateTexture(
    (LPDIRECT3DDEVICE9)this->d3d_device_,
    width,
    height,
    0,
    D3DUSAGE_RENDERTARGET,
    TEXTURE_FORMATS[static_cast<T_UINT32>(format)],
    D3DPOOL_DEFAULT,
    &tex);

  GG_ASSERT(SUCCEEDED(hr), "テクスチャの作成に失敗しました");

  return rcRenderTexture::Create(width, height, tex, depth_format);
}

UniqueRef<rcShader> DX9GraphicsAPI::ShaderLoad(const char* path)
{
  LPD3DXEFFECT dest = nullptr;

  HRESULT hr = D3DXCreateEffectFromFile(
    this->d3d_device_,
    path,
    NULL,
    NULL,
    D3DXSHADER_SKIPVALIDATION,
    NULL,
    &dest,
    NULL
  );
  GG_ASSERT(SUCCEEDED(hr), "シェーダーのロードに失敗しました");
  return UniqueRef<rcShader>(new DX9Shader(dest));
}

UniqueRef<rcVertexBuffer> DX9GraphicsAPI::CreateVertexBuffer(T_UINT32 vertex_count, T_UINT32 format)
{
  return UniqueRef<rcVertexBuffer>(new DX9VertexBuffer(vertex_count, format));
}

UniqueRef<rcIndexBuffer> DX9GraphicsAPI::CreateIndexBuffer(T_UINT32 indexes_count, T_UINT32 polygon_count)
{
  return UniqueRef<rcIndexBuffer>(new DX9IndexBuffer(indexes_count, polygon_count));
}

bool DX9GraphicsAPI::ImGuiNewFrame()
{
  ImGui_ImplDX9_NewFrame();
  return true;
}

bool DX9GraphicsAPI::ImGuiEndFrame()
{
  ImGui::EndFrame();
  return true;
}

bool DX9GraphicsAPI::PreDraw()
{
  if (SUCCEEDED(this->d3d_device_->BeginScene()))
  {
    return true;
  }
  return false;
}

bool DX9GraphicsAPI::PostDraw()
{
  //imgui
  ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

  this->d3d_device_->EndScene();
  this->d3d_device_->Present(NULL, NULL, NULL, NULL);
  return true;
}
