#include "FbxMeshMaterial.h"
#include "Director.h"

// =================================================================
// Constructor / Destructor
// =================================================================
FbxMeshMaterial::FbxMeshMaterial(FbxMesh* mesh)
{
  const T_UINT16 polygon_count = mesh->GetPolygonCount();
  this->indices_count_ = mesh->GetPolygonVertexCount();
  this->indices_ = new T_UINT16[this->indices_count_];
  for (T_UINT16 i = 0; i < this->indices_count_; ++i)
  {
    this->indices_[i] = i;
  }

  this->vertexes_count_ = this->indices_count_;
  //this->vertexes_count_ = mesh->GetControlPointsCount();
  FbxVector4* src = mesh->GetControlPoints();

  const T_INT32* polygon_indices = mesh->GetPolygonVertices();
  this->vertexes_ = new Vertex::VNCT[this->vertexes_count_];
  for (T_UINT16 i = 0; i < this->vertexes_count_; ++i)
  {
    this->vertexes_[i].coord[0] = src[polygon_indices[i]][0];
    this->vertexes_[i].coord[1] = src[polygon_indices[i]][1];
    this->vertexes_[i].coord[2] = src[polygon_indices[i]][2];
    this->vertexes_[i].coord[3] = 1.0f;
  }
  
  T_UINT8 layer_count = mesh->GetLayerCount();
  FbxLayerElementNormal* normal_element = nullptr;
  for (T_UINT8 i = 0; i < layer_count; ++i)
  {
    normal_element = mesh->GetLayer(i)->GetNormals();
    if (!normal_element)
    {
      continue;
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
          this->vertexes_[i].normal[0] = normal_element->GetDirectArray().GetAt(i)[0];
          this->vertexes_[i].normal[1] = normal_element->GetDirectArray().GetAt(i)[1];
          this->vertexes_[i].normal[2] = normal_element->GetDirectArray().GetAt(i)[2];
        }
      }
      else if (reference_mode == FbxLayerElement::eIndexToDirect)
      {
        NATIVE_ASSERT(false, "Ç‹ÇæÇ≈Ç´ÇƒÇ¢Ç‹ÇπÇÒÅI");
        for (T_UINT16 i = 0; i < normal_count; ++i)
        {

        }
      }
    }
    else if (mapping_mode == FbxLayerElement::eByControlPoint)
    {
      NATIVE_ASSERT(false, "Ç‹ÇæÇ≈Ç´ÇƒÇ¢Ç‹ÇπÇÒÅI");
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
