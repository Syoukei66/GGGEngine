#pragma once

#include "NativeType.h"
#include "TextureResource.h"
#include "ParticleSystem.h"

//===============================================================
// ParticleSystem
//===============================================================
class ParticleData
{
public:
  ParticleData();
  
  virtual void OnEmission(Particle* particle, const Transform2D* offset) const = 0;
  virtual bool OnUpdate(Particle* particle, T_FLOAT progress, T_FLOAT dp) const = 0;

  T_FLOAT CalcValueByVariance(T_FLOAT value, T_FLOAT variance, T_FLOAT min = Limit::T_FLOAT_MIN, T_FLOAT max = Limit::T_FLOAT_MAX) const;
  inline T_FLOAT CalcValueByProgress(T_FLOAT min, T_FLOAT max, T_FLOAT progress) const
  {
    return min + (max - min) * progress;
  }
  inline T_FLOAT CalcScaleBySize(Particle* particle, T_FLOAT size) const
  {
    return size / particle->GetSpriteRenderer()->GetWidth();
  }

public:
  ITextureRegion* region_;

  T_FLOAT duration;
  T_FLOAT life_time;
  T_FLOAT life_time_variance;
  T_UINT16 max_particles;
  T_FLOAT angle;
  T_FLOAT angle_variance;

  T_FLOAT start_size;
  T_FLOAT start_size_variance;
  T_FLOAT start_spin;
  T_FLOAT start_spin_variance;
  T_FLOAT start_color_r;
  T_FLOAT start_color_r_variance;
  T_FLOAT start_color_g;
  T_FLOAT start_color_g_variance;
  T_FLOAT start_color_b;
  T_FLOAT start_color_b_variance;
  T_FLOAT start_color_a;
  T_FLOAT start_color_a_variance;

  T_FLOAT end_size;
  T_FLOAT end_size_variance;
  T_FLOAT end_spin;
  T_FLOAT end_spin_variance;
  T_FLOAT end_color_r;
  T_FLOAT end_color_r_variance;
  T_FLOAT end_color_g;
  T_FLOAT end_color_g_variance;
  T_FLOAT end_color_b;
  T_FLOAT end_color_b_variance;
  T_FLOAT end_color_a;
  T_FLOAT end_color_a_variance;
};

//===============================================================
// ParticleSystem_Gravity
//===============================================================
class ParticleData_Gravity : public ParticleData
{
private:
  enum
  {
    ATTR_VELOCITY_X,
    ATTR_VELOCITY_Y,
    ATTR_ACCEL_RAD,
    ATTR_ACCEL_TAN,
  };
public:
  ParticleData_Gravity();

  void OnEmission(Particle* particle, const Transform2D* offset) const override;
  bool OnUpdate(Particle* particle, T_FLOAT progress, T_FLOAT dp) const override;

  T_FLOAT speed;
  T_FLOAT speed_variance;
  T_FLOAT emission_variance_x;
  T_FLOAT emission_variance_y;
  T_FLOAT gravity_x;
  T_FLOAT gravity_y;
  T_FLOAT accel_rad;
  T_FLOAT accel_rad_variance;
  T_FLOAT accel_tan;
  T_FLOAT accel_tan_variance;
};

//===============================================================
// ParticleSystem_Radius
//===============================================================
class ParticleData_Radius : public ParticleData
{
private:
  enum
  {
    ATTR_START_RADIUS,
    ATTR_END_RADIUS,
    ATTR_ROTATE,
    ATTR_ROTATE_PER_SECOND,
  };
public:
  ParticleData_Radius();
  
  void OnEmission(Particle* particle, const Transform2D* offset) const override;
  bool OnUpdate(Particle* particle, T_FLOAT progress, T_FLOAT dp) const override;

  T_FLOAT max_radius;
  T_FLOAT max_radius_variance;
  T_FLOAT min_radius;
  T_FLOAT rotate_per_sec;
  T_FLOAT rotate_per_sec_variance;
};
