#pragma once

#include "TextureRegion.h"

class rcTiledTextureRegion : public rcTextureRegion
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
  static UniqueResource<rcTiledTextureRegion> CreateWithMaterial(const SharedRef<const rcMaterial>& material, T_UINT8 x_num, T_UINT8 y_num);
  static UniqueResource<rcTiledTextureRegion> CreateWithTexture(const SharedRef<const rcTexture>& texture, T_UINT8 x_num, T_UINT8 y_num);
  static UniqueResource<rcTiledTextureRegion> Create();

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcTiledTextureRegion();
  virtual ~rcTiledTextureRegion();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void OnUpdateTextureCoord(const SharedRef<const rcTexture>& texture) override;

private:
  T_UINT16 CalcCurrentIndex();

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline virtual const char* GetResourceName() override
  {
    return "TiledTextureRegion";
  }

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

