//#pragma once
//
//#include <string>
//
//#include "ModelMaterialData.h"
//
//#include "../Common/NativeType.h"
//
//#include "Vector2.h"
//#include "Vector3.h"
//#include "Vector4.h"
//#include "../Common/Color.h"
//#include "Matrix4x4.h"
//#include "Quaternion.h"
//
////=============================================================================
//// MeshData
////=============================================================================
//struct ModelMeshData
//{
//  ModelMeshData() = default;
//  ~ModelMeshData()
//  {
//    delete[] this->vertices_;
//    delete[] this->normals_;
//    delete[] this->uvs_;
//    delete[] this->uv2s_;
//    delete[] this->uv3s_;
//    delete[] this->uv4s_;
//    delete[] this->tangents_;
//    delete[] this->colors_;
//    delete[] this->indices_;
//  }
//
//  T_UINT32 vertex_count_;
//  T_UINT8 vertex_format_;
//  TVec3f* vertices_;
//  TVec3f* normals_;
//  TVec2f* uvs_;
//  TVec2f* uv2s_;
//  TVec2f* uv3s_;
//  TVec2f* uv4s_;
//  TVec3f* tangents_;
//  TColor* colors_;
//
//  T_UINT32 index_count_;
//  T_UINT32* indices_;
//};
//
////=============================================================================
//// NodeNodeData
////=============================================================================
//struct ModelNodeData
//{
//  ModelNodeData() = default;
//  ~ModelNodeData()
//  {
//    for (T_UINT32 i = 0; i < this->child_count_; ++i)
//    {
//      delete this->children_[i];
//    }
//    delete[] this->children_;
//
//    delete[] this->mesh_indices_;
//    delete[] this->material_indices_;
//  }
//
//  TVec3f translation_;
//  TVec3f scaling_;
//  TVec3f rotation_;
//
//  T_UINT32 submesh_count_;
//  T_UINT32* mesh_indices_;
//  T_UINT32* material_indices_;
//
//  T_UINT32 child_count_;
//  ModelNodeData** children_;
//};
//
////=============================================================================
//// ModelNodeAnimationData
////=============================================================================
//
//struct ModelNodeAnimationData
//{
//  enum AnimationBehaviour
//  {
//    ANIM_BEHAVIOUR_DEFAULT,
//    ANIM_BEHAVIOUR_CONSTANT,
//    ANIM_BEHAVIOUR_LINEAR,
//    ANIM_BEHAVIOUR_REPEAT,
//  };
//
//  struct VectorKeyData
//  {
//    T_FLOAT time_;
//    TVec3f value_;
//  };
//
//  struct QuaternionKeyData
//  {
//    T_FLOAT time_;
//    Quaternion value_;
//  };
//
//  ModelNodeAnimationData() = delete;
//  ~ModelNodeAnimationData()
//  {
//    delete[] this->position_keys_;
//    delete[] this->rotation_keys_;
//    delete[] this->scaling_keys_;
//  }
//
//  std::string node_name_;
//
//  T_UINT32 position_key_count_;
//  VectorKeyData* position_keys_;
//
//  T_UINT32 rotation_key_count_;
//  QuaternionKeyData* rotation_keys_;
//
//  T_UINT32 scaling_key_count_;
//  VectorKeyData* scaling_keys_;
//
//  AnimationBehaviour pre_state_;
//  AnimationBehaviour post_state_;
//};
//
////=============================================================================
//// ModelMeshAnimationData
////=============================================================================
//struct ModelMeshAnimationData
//{
//  struct MeshKeyData
//  {
//    T_FLOAT time_;
//    T_UINT32 value_;
//  };
//
//  std::string name_;
//
//  T_UINT32 key_counts_;
//  MeshKeyData* keys_;
//};
//
////=============================================================================
//// ModelMeshMorphAnimationData
////=============================================================================
//struct ModelMeshMorphAnimationData
//{
//  struct KeyData
//  {
//
//  };
//};
//
////=============================================================================
//// ModelAnimationData
////=============================================================================
//struct ModelAnimationData
//{
//  std::string name_;
//  T_FLOAT duration_;
//
//  T_UINT32 channel_count_;
//  ModelNodeAnimationData* channels_;
//
//  T_UINT32 mesh_channel_count_;
//  ModelMeshAnimationData* mesh_channels_;
//
//  T_UINT32 morph_mesh_channel_count_;
//  ModelMeshMorphAnimationData* mesh_morph_channels_;
//};
//
////=============================================================================
//// ModelData
////=============================================================================
//struct ModelData
//{
//  ModelData() = default;
//  ~ModelData()
//  {
//    for (T_UINT32 i = 0; i < this->material_count_; ++i)
//    {
//      delete this->materials_[i];
//    }
//    delete[] this->materials_;
//
//    for (T_UINT32 i = 0; i < this->mesh_count_; ++i)
//    {
//      delete this->meshes_[i];
//    }
//    delete[] this->meshes_;
//
//    delete this->root_;
//  }
//
//  ModelNodeData* root_;
//
//  T_UINT32 material_count_;
//  ModelMaterialData** materials_;
//  T_UINT32 mesh_count_;
//  ModelMeshData** meshes_;
//};
