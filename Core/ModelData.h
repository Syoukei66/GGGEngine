#pragma once

#include <string>
#include "NativeType.h"

struct ModelData
{
  ModelData() = default;

  T_UINT32 mesh_unique_id_;
  T_UINT8 submesh_count_;
  T_UINT8* mesh_material_indices_;

  T_UINT8 material_count_;
  T_UINT32* material_unique_ids_;

  //=============================================================================
  // Serealizer / Deserealizer
  //=============================================================================
  static ModelData* Deserealize(const std::string& path);
  void Serealize(const std::string& path, bool test = false);

};