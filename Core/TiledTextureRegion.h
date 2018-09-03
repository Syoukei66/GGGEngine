#pragma once

#include "TextureRegion.h"

class TiledTextureRegion : public rcTextureRegion
{
public:
  enum TiledTextureRegionFormat
  {
    TTR_FORMAT_NONE,
    TTR_FORMAT_CLAMP,
    TTR_FORMAT_LOOP,
  };

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static TiledTextureRegion* CreateWithMaterial(const rcMaterial& material, T_UINT8 x_num, T_UINT8 y_num);
  static TiledTextureRegion* CreateWithTexture(const rcTexture* texture, T_UINT8 x_num, T_UINT8 y_num);
  static TiledTextureRegion* Create();

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  TiledTextureRegion();
  virtual ~TiledTextureRegion();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void OnUpdateTextureCoord(const rcTexture* texture) override;

private:
  T_UINT16 CalcCurrentIndex();

  // =================================================================
  // setter/getter
  // =================================================================
public:
  void SetXNum(T_UINT8 x_num);
  inline T_UINT8 GetXNum() const
  {
    return this->x_num_;
  }
  void SetYNum(T_UINT8 y_num);
  inline T_UINT8 GetYNum() const
  {
    return this->y_num_;
  }
  inline T_UINT16 GetTileCount() const
  {
    return this->x_num_ * this->y_num_;
  }
  void SetCurrentIndex(T_UINT16 current_index);
  inline T_UINT16 GetCurrentIndex() const
  {
    return this->current_index_;
  }
  void SetTiledTextureRegionFormat(TiledTextureRegionFormat format);
  inline TiledTextureRegionFormat GetTiledTextureRegionFormat() const
  {
    return this->format_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT8 x_num_, y_num_;
  T_UINT16 current_index_;
  TiledTextureRegionFormat format_;
};

