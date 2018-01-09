#pragma once

#include "Color.h"

class Material
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Material();
  Material(LP_MATERIAL native_material);
  ~Material();
 
  // =================================================================
  // Method
  // =================================================================
public:
  void Apply();

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline LP_MATERIAL GetNativeMaterial() const
  {
    return this->material_;
  }

  void SetAmbient(const Color& color);
  void SetAmbient(T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a);
  inline const Color& GetAmbient() const
  {
    return this->ambient_;
  }

  void SetDiffuse(const Color& color);
  void SetDiffuse(T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a);
  inline const Color& GetDiffuse() const
  {
    return this->diffuse_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  bool material_delete_;
  LP_MATERIAL material_;
  Color ambient_;
  Color diffuse_;
  
};
