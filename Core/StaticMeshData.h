#pragma once

#include "NativeType.h"
#include "Bounds.h"

struct StaticMeshData
{
  StaticMeshData() = default;
  ~StaticMeshData()
  {
    delete[] this->data_;
    delete[] this->indices_;
    delete[] this->submesh_index_counts_;
  }

  T_UINT32 vertex_format_;
  size_t vertex_size_;
  T_UINT32 vertex_count_;
  unsigned char* data_;

  T_UINT32 polygon_count_;

  T_UINT32 index_count_;
  T_UINT32* indices_;

  T_UINT8 submesh_count_;
  T_UINT32* submesh_index_counts_;

  Bounds bounds_;

  //=============================================================================
  // Serealizer / Deserealizer
  //=============================================================================
  static StaticMeshData* Deserealize(const std::string& path);
  void Serealize(const std::string& path, bool test = false);

};
