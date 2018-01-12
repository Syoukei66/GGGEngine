#ifndef HAL_ENGINE_ENTITY_SHAPE_SPRITE_TEXTUREREGION_ITEXTUREREGION_H_
#define HAL_ENGINE_ENTITY_SHAPE_SPRITE_TEXTUREREGION_ITEXTUREREGION_H_

#include "NativeType.h"
#include "Texture.h"

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
  virtual void OnUpdateTextureCoord() = 0;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline void SetTexture(const Texture* texture)
  {
    this->texture_ = texture;
  }
  inline const Texture* GetTexture() const
  {
    return this->texture_;
  }
  inline void SetU0(T_FLOAT u0)
  {
    this->u0_ = u0;
  }
  T_FLOAT GetU0();
  void SetV0(T_FLOAT v0)
  {
    this->v0_ = v0;
  }
  T_FLOAT GetV0();
  void SetU1(T_FLOAT u1)
  {
    this->u1_ = u1;
  }
  T_FLOAT GetU1();
  void SetV1(T_FLOAT v1)
  {
    this->v1_ = v1;
  }
  T_FLOAT GetV1();
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
  const Texture* texture_;
  TAreaf texture_region_;
  T_FLOAT u0_, v0_, u1_, v1_;
  bool texture_coord_dirty_;
};

#endif//HAL_ENGINE_ENTITY_SHAPE_SPRITE_TEXTUREREGION_ITEXTUREREGION_H_
