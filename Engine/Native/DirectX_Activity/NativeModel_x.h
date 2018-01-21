#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <HalEngine.h>

class NativeModel_x : public INativeModel
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  NativeModel_x(const char* asset_path, const char* name);
  ~NativeModel_x();

  // =================================================================
  // Method for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void Draw(GameObjectRenderState* state) const override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  LPD3DXMESH mesh_;
  T_UINT32 material_count_;
  Material** materials_;

};