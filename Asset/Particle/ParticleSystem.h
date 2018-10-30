//#pragma once
//
//#include <Core/NativeType.h>
//#include "Sprite.h"
//#include "PoolAllocator.h"
//
//class ParticleData;
//
////===============================================================
//// Particle
////===============================================================
//class Particle : public Sprite, public IPoolAllocatable
//{
//public:
//  enum
//  {
//    ATTRIBUTE_PARAMS_COUNT = 4
//  };
//
//public:
//  void OnAllocated() override;
//  void OnFree() override;
//  void OnEmission(const ParticleData* data, const Transform2D* offset);
//  bool OnUpdate(const ParticleData* data);
//
//public:
//  T_FLOAT GetOffsetX();
//  T_FLOAT GetOffsetY();
//
//public:
//  GG_INLINE T_FLOAT GetAttributeParam(T_UINT8 index) const
//  {
//    return this->attribute_params_[index];
//  }
//  GG_INLINE void SetAttributeParam(T_UINT8 index, T_FLOAT value)
//  {
//    this->attribute_params_[index] = value;
//  }
//  GG_INLINE T_FLOAT GetLifeTime() const
//  {
//    return this->life_time;
//  }
//
//private:
//  T_FLOAT offset_x_;
//  T_FLOAT offset_y_;
//
//  T_FLOAT attribute_params_[ATTRIBUTE_PARAMS_COUNT];
//
//  T_FLOAT life_time;
//  T_FLOAT life_time_rest;
//
//  T_FLOAT start_size;
//  T_FLOAT start_spin;
//  T_FLOAT start_color_r;
//  T_FLOAT start_color_g;
//  T_FLOAT start_color_b;
//  T_FLOAT start_color_a;
//
//  T_FLOAT end_size;
//  T_FLOAT end_spin;
//  T_FLOAT end_color_r;
//  T_FLOAT end_color_g;
//  T_FLOAT end_color_b;
//  T_FLOAT end_color_a;
//};
//
////===============================================================
//// ParticleSystem
////===============================================================
//class ParticleSystem : public GameObject2D
//{
//public:
//  static ParticleSystem* CreateWithData(const ParticleData* data);
//  
//private:
//  ParticleSystem();
//
//public:
//  ~ParticleSystem();
//
//public:
//  void Prepare(const ParticleData* data);
//  void Init();
//
//  void Update() override;
//
//public:
//  void SetApplyLocalPosition(bool apply_local_position)
//  {
//    this->apply_local_position_ = apply_local_position;
//  }
//
//private:
//  const ParticleData* data_;
//  T_FLOAT time_count_;
//  T_FLOAT duration_;
//  PoolAllocator<Particle>* particles_;
//  //TODO:�@�\���Ȃ��̂�ParticleRenderer�Ȃ艽�Ȃ����ĂȂ�Ƃ�����
//  bool apply_local_position_;
//};
//