#pragma once
//
//#include <string>
//#include "../Core/NativeType.h"
//
//#include "Vector2.h"
//#include "Vector3.h"
//#include "Vector4.h"
//#include "../Core/Color.h"
//#include "Matrix4x4.h"
//
////=============================================================================
//// TextureData
////=============================================================================
//struct ModelTextureData
//{
//
//  ModelTextureData() = default;
//  ~ModelTextureData()
//  {
//  }
//
//  std::string path_;
//  T_UINT8 mapping_;
//  T_UINT8 uv_index_;
//  T_FLOAT blend_;
//  T_UINT8 op_;
//  T_UINT8 map_mode_;
//};
//
////=============================================================================
//// MaterialPropertyData
////=============================================================================
//template <typename T>
//struct ModelMaterialPropertyData
//{
//  ModelMaterialPropertyData() = default;
//  ~ModelMaterialPropertyData()
//  {
//  }
//
//  std::string name;
//  T value;
//};
//
////=============================================================================
//// MaterialData
////=============================================================================
//struct ModelMaterialData
//{
//  static std::string KEY_DIFFUSE;
//  static std::string KEY_AMBIENT;
//  static std::string KEY_EMISSIVE;
//  static std::string KEY_BUMP;
//  static std::string KEY_TRANSPARENT;
//  static std::string KEY_SPECULAR;
//  static std::string KEY_REFLECTION;
//  static std::string KEY_POWER;
//
//  ModelMaterialData() = default;
//  ~ModelMaterialData()
//  {
//    for (T_UINT8 i = 0; i < ModelTextureData::TEX_TYPE_DATANUM; ++i)
//    {
//      for (T_UINT8 j = 0; j < this->texture_counts_[i]; ++j)
//      {
//        delete this->texture_datas_[i][j];
//      }
//      delete[] this->texture_datas_[i];
//    }
//
//    for (T_UINT8 i = 0; i < this->bool_property_count_; ++i)
//    {
//      delete this->bool_properties_[i];
//    }
//    delete[] this->bool_properties_;
//
//    for (T_UINT8 i = 0; i < this->int_property_count_; ++i)
//    {
//      delete this->int_properties_[i];
//    }
//    delete[] this->int_properties_;
//
//    for (T_UINT8 i = 0; i < this->float_property_count_; ++i)
//    {
//      delete this->float_properties_[i];
//    }
//    delete[] this->float_properties_;
//
//    for (T_UINT8 i = 0; i < this->vec2_property_count_; ++i)
//    {
//      delete this->vec2_properties_[i];
//    }
//    delete[] this->vec2_properties_;
//
//    for (T_UINT8 i = 0; i < this->vec3_property_count_; ++i)
//    {
//      delete this->vec3_properties_[i];
//    }
//    delete[] this->vec3_properties_;
//
//    for (T_UINT8 i = 0; i < this->vec4_property_count_; ++i)
//    {
//      delete this->vec4_properties_[i];
//    }
//    delete[] this->vec4_properties_;
//
//    for (T_UINT8 i = 0; i < this->color_property_count_; ++i)
//    {
//      delete this->color_properties_[i];
//    }
//    delete[] this->color_properties_;
//
//    for (T_UINT8 i = 0; i < this->matrix_property_count_; ++i)
//    {
//      delete this->matrix_properties_[i];
//    }
//    delete[] this->matrix_properties_;
//  }
//
//  T_UINT8 texture_counts_[ModelTextureData::TEX_TYPE_DATANUM];
//  ModelTextureData** texture_datas_[ModelTextureData::TEX_TYPE_DATANUM];
//
//  T_UINT8 bool_property_count_;
//  ModelMaterialPropertyData<bool>** bool_properties_;
//
//  T_UINT8 int_property_count_;
//  ModelMaterialPropertyData<T_INT32>** int_properties_;
//
//  T_UINT8 float_property_count_;
//  ModelMaterialPropertyData<T_FLOAT>** float_properties_;
//
//  T_UINT8 vec2_property_count_;
//  ModelMaterialPropertyData<TVec2f>** vec2_properties_;
//
//  T_UINT8 vec3_property_count_;
//  ModelMaterialPropertyData<TVec3f>** vec3_properties_;
//
//  T_UINT8 vec4_property_count_;
//  ModelMaterialPropertyData<TVec4f>** vec4_properties_;
//
//  T_UINT8 color_property_count_;
//  ModelMaterialPropertyData<TColor>** color_properties_;
//
//  T_UINT8 matrix_property_count_;
//  ModelMaterialPropertyData<Matrix4x4>** matrix_properties_;
//};