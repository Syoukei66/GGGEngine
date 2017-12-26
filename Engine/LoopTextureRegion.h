#ifndef HAL_ENGINE_ENTITY_SHAPE_SPRITE_TEXTUREREGION_LOOPTEXTUREREGION_H_
#define HAL_ENGINE_ENTITY_SHAPE_SPRITE_TEXTUREREGION_LOOPTEXTUREREGION_H_

#include "ITextureRegion.h"

class LoopTextureRegion : public ITextureRegion
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static LoopTextureRegion* CreateWithTexture(const ITexture* texture);
  static LoopTextureRegion* CreateFromAsset(T_UINT8 palette_id, T_UINT16 texture_id);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  LoopTextureRegion();
  virtual ~LoopTextureRegion();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void OnUpdateTextureCoord() override;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  void SetLoopSize(const TSizef& size);
  inline const TSizef& GetLoopSize() const
  {
    return this->loop_size_;
  }
  void SetLoopWidth(T_FLOAT width);
  inline const T_FLOAT GetLoopWidth() const
  {
    return this->loop_size_.width;
  }
  void SetLoopHeight(T_FLOAT height);
  inline const T_FLOAT GetLoopHeight() const
  {
    return this->loop_size_.height;
  }

  void SetLoopOffset(const TVec2f& offset);
  inline const TVec2f& GetLoopOffset() const
  {
    return this->loop_offset_;
  }
  void SetLoopOffsetX(T_FLOAT x);
  inline const T_FLOAT GetLoopOffsetX() const
  {
    return this->loop_offset_.x;
  }
  void SetLoopOffsetY(T_FLOAT y);
  inline const T_FLOAT GetLoopOffsetY() const
  {
    return this->loop_offset_.y;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  TSizef loop_size_;
  TVec2f loop_offset_;
};

#endif//HAL_ENGINE_ENTITY_SHAPE_SPRITE_TEXTUREREGION_LOOPTEXTUREREGION_H_