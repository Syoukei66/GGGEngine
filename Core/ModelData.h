#pragma once

#include <string>
#include <vector>
#include "NativeType.h"
#include "Serializer.h"

struct ModelData
{
  ModelData() = default;

  T_UINT32 mesh_unique_id_;
  std::vector<T_UINT32> material_unique_ids_;

  SERIALIZE_METHOD(ModelData)
};