#ifndef HAL_ENGINE_ENTITY_SHAPE_SPRITE_TEXTUREREGION_ITEXTUREREGION_H_
#define HAL_ENGINE_ENTITY_SHAPE_SPRITE_TEXTUREREGION_ITEXTUREREGION_H_

#include "NativeType.h"
#include "Material.h"

class ITextureRegion
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  virtual ~ITextureRegion() {}
protected:
  ITextureRegion();

  // =================================================================
  // Method
  // =================================================================
public:
  void Init();
  void FitToTexture();
  //VBOが管理している頂点のUV座標を更新させるため、
  //テクスチャに変更があった場合、それを呼び出し元に伝えます。
  bool UpdateTextureCoord();
  void OnTextureCoordDirty();

protected:
  virtual void OnUpdateTextureCoord(const INativeTexture* texture) = 0;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline void SetTexture(const INativeTexture* texture)
  {
    this->texture_ = texture;
  }
  inline const INativeTexture* GetTexture() const
  {
    return this->texture_;
  }

  inline void SetU0(T_FLOAT u0)
  {
    this->uv0_.x = u0;
  }
  void SetV0(T_FLOAT v0)
  {
    this->uv0_.y = v0;
  }
  void SetU1(T_FLOAT u1)
  {
    this->uv1_.x = u1;
  }
  void SetV1(T_FLOAT v1)
  {
    this->uv1_.y = v1;
  }
  const TVec2f& GetUV0() const
  {
    const_cast<ITextureRegion*>(this)->UpdateTextureCoord();
    return this->uv0_;
  }
  const TVec2f& GetUV1() const
  {
    const_cast<ITextureRegion*>(this)->UpdateTextureCoord();
    return this->uv1_;
  }

  void SetX(T_FLOAT x);
  inline T_FLOAT GetX() const
  {
    return this->texture_region_.pos.x;
  }
  void SetY(T_FLOAT y);
  inline T_FLOAT GetY() const
  {
    return this->texture_region_.pos.y;
  }
  inline void SetSize(const TSizef& size)
  {
    this->texture_region_.size = size;
  }
  inline const TSizef& GetSize()
  {
    return this->texture_region_.size;
  }
  void SetWidth(T_FLOAT width);
  inline T_FLOAT GetWidth() const
  {
    return this->texture_region_.size.width;
  }
  void SetHeight(T_FLOAT height);
  inline T_FLOAT GetHeight() const
  {
    return this->texture_region_.size.height;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  const INativeTexture* texture_;
  TAreaf texture_region_;
  TVec2f uv0_, uv1_;
  bool texture_coord_dirty_;
};

#endif//HAL_ENGINE_ENTITY_SHAPE_SPRITE_TEXTUREREGION_ITEXTUREREGION_H_
