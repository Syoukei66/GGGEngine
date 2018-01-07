#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <HalEngine.h>

class NativeModel : public INativeModel
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  NativeModel(const char* asset_path, const char* name);
  ~NativeModel();

  // =================================================================
  // Method for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void Draw() const override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  LPD3DXMESH mesh_;
  T_UINT32 material_count_;
  Material** materials_;
  const ITexture** textures_;

};