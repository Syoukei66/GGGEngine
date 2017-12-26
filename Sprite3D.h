#pragma once

#include "BillBoard.h"
#include "ITextureRegion.h"
#include "VertexBufferObject_Sprite3D.h"

class Sprite3D : public Shape3D
{
public:
  static Sprite3D* CreateFromAsset(T_UINT8 palette_id, T_UINT16 texture_id);

public:
  Sprite3D();
  ~Sprite3D();
  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void PreDraw(GameObject3DRenderState* state) override;
  virtual void NativeDraw(GameObject3DRenderState* state) override;

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void OnVertexCoordChanged();
  void OnTextureChanged();
  //Sprite�̃T�C�Y(width/height)��ITextureRegion�ɏ��������̂ɕύX���܂��B
  //ITextureRegion��NULL�̏ꍇ�A�T�C�Y��0*0�ɂȂ�܂��B
  void FitToTexture();

  // =================================================================
  // setter/getter
  // =================================================================
public:
  void SetTextureRegion(ITextureRegion* itr);
  inline ITextureRegion* GetTextureRegion() const
  {
    return this->texture_region_;
  }

  void SetWidth(T_FLOAT width);
  inline T_FLOAT GetWidth() const
  {
    return this->size_.width;
  }
  inline T_FLOAT GetWidthScaled() const
  {
    return this->size_.width * this->GetTransform()->GetScaleX();
  }

  void SetHeight(T_FLOAT height);
  inline T_FLOAT GetHeight() const
  {
    return this->size_.height;
  }
  inline T_FLOAT GetHeightScaled() const
  {
    return this->size_.height * this->GetTransform()->GetScaleY();
  }


private:
  TSizef size_;
  VertexBufferObject_Sprite3D* sprite3d_vbo_;
  ITextureRegion* texture_region_;

};