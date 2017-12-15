#pragma once

#include "GameObject3D.h"

/*
  TODO:現在の形だとわざわざネイティブ側のデータとエンジン側のデータの２つを用意する必要があり無駄が多い
  Materialも同様、Textureは微妙
*/

//Directional Light
class Light
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Light();
  virtual ~Light();

  // =================================================================
  // Method
  // =================================================================
public:
  void Apply();

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline void SetDiffuse(const Color& diffuse)
  {
    this->diffuse_ = diffuse;
  }
  inline void SetDiffuse(T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a)
  {
    this->diffuse_.SetColor(r, g, b, a);
  }
  inline const Color& GetDiffuse() const
  {
    return this->diffuse_;
  }

  inline void SetAmbient(const Color& ambient)
  {
    this->ambient_ = ambient;
  }
  inline void SetAmbient(T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a)
  {
    this->ambient_.SetColor(r, g, b, a);
  }
  inline const Color& GetAmbient() const
  {
    return this->ambient_;
  }

  inline void SetDirection(const TVec3f& direction)
  {
    this->direction_ = direction;
  }
  void SetDirection(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  inline const TVec3f GetDirection() const
  {
    return this->direction_;
  }
  inline void SetDirectionX(T_FLOAT x)
  {
    this->direction_.x = x;
  }
  inline T_FLOAT GetDirectionX() const
  {
    return this->direction_.x;
  }
  inline void SetDirectionY(T_FLOAT y)
  {
    this->direction_.y = y;
  }
  inline T_FLOAT GetDirectionY() const
  {
    return this->direction_.y;
  }
  inline void SetDirectionZ(T_FLOAT z)
  {
    this->direction_.z = z;
  }
  inline T_FLOAT GetDirectionZ() const
  {
    return this->direction_.z;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT16 light_id_;
  LP_LIGHT light_;
  Color diffuse_;
  Color ambient_;
  TVec3f direction_;

};