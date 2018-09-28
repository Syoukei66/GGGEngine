#pragma once

#include <unordered_map>

#include "NativeType.h"
#include "Serializer.h"

class DefaultUniqueID
{
  friend class DefaultUniqueIDSerializerTester;

public:
  enum {
    DEFAULT_UNIQUE_ID_BEGIN = 1000000,
    SHADER_FLAT,
    SHADER_GOURAUD,
    SHADER_PHONG,
    SHADER_BLIN,
    SHADER_TOON,
    SHADER_OREN_NAYAR,
    SHADER_MINNAERT,
    SHADER_COOK_TORRANCE,
    SHADER_NO_SHADING,
    SHADER_FRESNEL,
  };

  // =================================================================
  // Method
  // =================================================================
public:
  inline void AddCorrespondence(T_UINT32 default_id, T_UINT32 uid)
  {
    this->correspondences_[default_id] = uid;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline T_UINT32 GetUniqueId(T_UINT32 default_id) const
  {
    return this->correspondences_.at(default_id);
  }

  // =================================================================
  // Data Member
  // =================================================================
public:
  std::unordered_map<T_UINT32, T_UINT32> correspondences_;

  SERIALIZE_METHOD(DefaultUniqueID)
};
