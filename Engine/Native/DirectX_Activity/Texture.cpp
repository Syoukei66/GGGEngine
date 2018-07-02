#include <Texture.h>

static LPDIRECT3DTEXTURE9 TextureLoad(const std::string& path)
{
  LP_DEVICE device = Director::GetInstance()->GetDevice();
  LPDIRECT3DTEXTURE9 dest = nullptr;

  HRESULT hr = D3DXCreateTextureFromFileEx(
    (LPDIRECT3DDEVICE9)device,
    path.c_str(),
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
    &dest);

  NATIVE_ASSERT(SUCCEEDED(hr), "テクスチャのロードに失敗しました");

  return dest;
}

Texture* Texture::Create(const std::string& path)
{
  D3DXIMAGE_INFO info;
  HRESULT hr = D3DXGetImageInfoFromFile(
    path.c_str(),
    &info
  );
  NATIVE_ASSERT(SUCCEEDED(hr), "テクスチャサイズの取得に失敗しました");

  return new Texture(info.Width, info.Height, TextureLoad(path));
}

Texture* Texture::Create(T_UINT16 width, T_UINT16 height, void* native_obj)
{
  return new Texture(width, height, native_obj);
}

Texture::Texture(T_UINT16 width, T_UINT16 height, void* native_obj)
  : native_obj_(native_obj)
  , width_(width)
  , height_(height)
{
  LPDIRECT3DTEXTURE9 tex = (LPDIRECT3DTEXTURE9)native_obj;

  D3DSURFACE_DESC desc;
  HRESULT hr = tex->GetLevelDesc(0, &desc);
  NATIVE_ASSERT(SUCCEEDED(hr), "テクスチャの情報の取得に失敗しました");
  this->two_powered_width_ = desc.Width;
  this->two_powered_height_ = desc.Height;

  this->color_buffer_ = new RenderBuffer(this);
}

Texture::~Texture()
{
  delete this->color_buffer_;
  ((LPDIRECT3DTEXTURE9)this->native_obj_)->Release();
}