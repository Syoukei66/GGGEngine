#pragma once

#include <string>

#include "../Common/NativeType.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "../Common/Color.h"
#include "Matrix4x4.h"
#include "Bounds.h"
#include "Quaternion.h"

//=============================================================================
// ModelAnimationKeyData
//=============================================================================
struct ModelAnimationVectorKeyData
{
  T_FLOAT time_;
  TVec3f value_;
};

struct ModelAnimationQuaternionKeyData
{
  T_FLOAT time_;
  Quaternion value_;
};

//=============================================================================
// ModelNodeAnimationData
//=============================================================================
struct ModelNodeAnimationData
{
  enum AnimationBehaviour
  {
    ANIM_BEHAVIOUR_DEFAULT,
    ANIM_BEHAVIOUR_CONSTANT,
    ANIM_BEHAVIOUR_LINEAR,
    ANIM_BEHAVIOUR_REPEAT,
  };

  ModelNodeAnimationData() = delete;
  ~ModelNodeAnimationData()
  {
    delete[] this->position_keys_;
    delete[] this->rotation_keys_;
    delete[] this->scaling_keys_;
  }

  std::string node_name_;
  
  T_UINT32 position_key_count_;
  ModelAnimationVectorKeyData* position_keys_;

  T_UINT32 rotation_key_count_;
  ModelAnimationQuaternionKeyData* rotation_keys_;

  T_UINT32 scaling_key_count_;
  ModelAnimationVectorKeyData* scaling_keys_;

  AnimationBehaviour pre_state_;
  AnimationBehaviour post_state_;
};

//=============================================================================
// ModelMeshAnimationKeyData
//=============================================================================
struct ModelMeshAnimationKeyData
{
  T_FLOAT time_;
  T_UINT32 value_;
};

//=============================================================================
// ModelMeshAnimationData
//=============================================================================
struct ModelMeshAnimationData
{
  std::string name_;
  
  T_UINT32 key_counts_;
  ModelMeshAnimationKeyData* keys_;
};

//=============================================================================
// ModelMeshMorphAnimationData
//=============================================================================
struct ModelMeshMorphAnimationData
{

};

//=============================================================================
// ModelAnimationData
//=============================================================================
struct ModelAnimationData
{
  std::string name_;
  T_FLOAT duration_;

  T_UINT32 channel_count_;


  T_UINT32 mesh_channel_count_;
  T_UINT32 morph_mesh_channel_count_;
};
