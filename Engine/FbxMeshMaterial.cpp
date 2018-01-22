#include "FbxMeshMaterial.h"

// =================================================================
// Constructor / Destructor
// =================================================================
FbxMeshMaterial::FbxMeshMaterial(FbxMesh* mesh)
{
  //const T_UINT16 polygon_count = mesh->GetPolygonCount();
  this->indices_count_ = mesh->GetPolygonVertexCount();
  this->indices_ = new T_UINT16[this->indices_count_];
  const T_INT32* polygon_indices = mesh->GetPolygonVertices();
  for (T_UINT16 i = 0; i < this->indices_count_; ++i)
  {
    this->indices_[i] = (T_UINT16)polygon_indices[i];
  }

  this->vertexes_count_ = mesh->GetControlPointsCount();
  FbxVector4* src = mesh->GetControlPoints();

  this->vertexes_ = new Vertex::VNCT[this->vertexes_count_];
  for (T_UINT16 i = 0; i < this->vertexes_count_; ++i)
  {
    this->vertexes_[i].coord[0] = src[i][0];
    this->vertexes_[i].coord[1] = src[i][1];
    this->vertexes_[i].coord[2] = src[i][2];
    this->vertexes_[i].coord[3] = src[i][3];
  }

  T_UINT8 layer_num = mesh->GetLayerCount();
  FbxLayerElementNormal* normal_element = nullptr;
  for (T_UINT8 i = 0; i < layer_num; ++i)
  {
    normal_element = mesh->GetLayer(i)->GetNormals();
    if (normal_element)
    {
      break;
    }
  }
  T_UINT16 normal_count = normal_element->GetDirectArray().GetCount();
  T_UINT16 normal_index_count = normal_element->GetIndexArray().GetCount();

  FbxLayerElement::EMappingMode mapping_mode = normal_element->GetMappingMode();
  FbxLayerElement::EReferenceMode reference_mode = normal_element->GetReferenceMode();

  if (mapping_mode == FbxLayerElement::eByPolygonVertex)
  {
    if (reference_mode == FbxLayerElement::eDirect)
    {
      for (T_UINT16 i = 0; i < normal_count; ++i)
      {

      }
    }
    else if (reference_mode == FbxLayerElement::eIndexToDirect)
    {
      for (T_UINT16 i = 0; i < normal_count; ++i)
      {

      }
    }
  }
  else if (mapping_mode == FbxLayerElement::eByControlPoint)
  {
    if (reference_mode == FbxLayerElement::eDirect)
    {
      for (T_UINT16 i = 0; i < normal_count; ++i)
      {

      }
    }
    else if (reference_mode == FbxLayerElement::eIndexToDirect)
    {
      for (T_UINT16 i = 0; i < normal_count; ++i)
      {

      }
    }
  }
}

FbxMeshMaterial::~FbxMeshMaterial()
{
  delete[] this->indices_;
  delete[] this->vertexes_;
}

// =================================================================
// Method for/from Interface/SuperClass
// =================================================================
T_UINT16 FbxMeshMaterial::GetVertexesCount() const
{
  return this->vertexes_count_;
}

void FbxMeshMaterial::SetupVertex(void* dest) const
{
  for (T_UINT16 i = 0; i < this->vertexes_count_; ++i)
  {
    ((Vertex::VNCT*)dest)[i] = this->vertexes_[i];
  }
}

T_UINT16 FbxMeshMaterial::GetIndicesCount() const
{
  return this->indices_count_;
}

const T_UINT16* FbxMeshMaterial::GetIndices() const
{
  return this->indices_;
}

INativeProcess_Graphics::PrimitiveType FbxMeshMaterial::GetPrimitiveType() const
{
  return INativeProcess_Graphics::PRIMITIVE_TRIANGLES;
}

Vertex::VertexType FbxMeshMaterial::GetVertexType() const
{
  return Vertex::VERTEX_TYPE_VNCT;
}
