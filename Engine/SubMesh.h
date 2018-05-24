#pragma once

#include "MeshData.h"
#include "NativeVertexBuffer.h"
#include "NativeIndexBuffer.h"

class SubMesh
{
public:
  SubMesh(MeshData* data);
  SubMesh(const SubMesh& other);
  ~SubMesh();

  // =================================================================
  // Method
  // =================================================================
public:
  SubMesh* Clone();

  void Draw() const;

  //TVec4f* vertices_;
  //TVec3f* normals_;
  //TVec2f* uvs_;
  //TVec2f* uv2s_;
  //TVec3f* tangents_;
  //Color4F* color_;
  void Init(T_UINT16 vertices_count, T_UINT16 indices_count);
  void PrepareVertices();
  void PrepareNormals();
  void PrepareUvs();
  void PrepareUv2s();
  void PrepareTangents();
  void PrepareColors();

  void CommitChanges();

protected:
  void CommitVertices() const;
  void CommitIndices() const;



  // =================================================================
  // Data Member
  // =================================================================
private:
  const SubMesh* orginal_;



  /* ============================================
    nullptrではないパラメータに応じて
    バッファに渡すデータのサイズを変更できるように
   * ============================================ */
  T_UINT16 vertices_count_;
  TVec4f* vertices_;
  TVec3f* normals_;
  TVec2f* uvs_;
  TVec2f* uv2s_;
  TVec3f* tangents_;
  Color4F* colors_;
  //bindPoses
  //boneWeights
  //bounds
  bool vertices_dirty_;

  T_UINT16 indices_count_;
  T_UINT16* indices_;
  bool indices_dirty_;

};