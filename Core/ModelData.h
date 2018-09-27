#pragma once

#include <string>
#include <vector>
#include "NativeType.h"

struct ModelData
{
  ModelData() = default;

  T_UINT32 mesh_unique_id_;
  std::vector<T_UINT32> material_unique_ids_;

  //=============================================================================
  // Serializer / Deserializer
  //=============================================================================
  static ModelData* Deserialize(const std::string& path);
  void Serialize(const std::string& path, bool test = false) const;

};