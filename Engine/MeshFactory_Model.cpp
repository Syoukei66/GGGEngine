#include "MeshFactory_Model.h"
#include "GraphicsConstants.h"

Mesh* MeshFactory::Model::Create(ModelData* model, ModelNodeData* node, bool readonly)
{
  using namespace GraphicsConstants;
  Mesh* ret = new Mesh();
 
  T_UINT32 format = 0;

  //position
  if (mesh->vertex_format_ & ModelMeshData::V_ELEM_POSITION)
  {
    format |= V_ATTR_POSITION;
  }

  //normal
  if (mesh->vertex_format_ & ModelMeshData::V_ELEM_NORMAL)
  {
    format |= V_ATTR_NORMAL;
  }

  //uv
  if (mesh->vertex_format_ & ModelMeshData::V_ELEM_UV)
  {
    format |= V_ATTR_UV;
  }

  //uv2
  if (mesh->vertex_format_ & ModelMeshData::V_ELEM_UV2)
  {
    format |= V_ATTR_UV2;
  }

  //uv3
  if (mesh->vertex_format_ & ModelMeshData::V_ELEM_UV3)
  {
    format |= V_ATTR_UV3;
  }

  //uv4
  if (mesh->vertex_format_ & ModelMeshData::V_ELEM_UV4)
  {
    format |= V_ATTR_UV4;
  }

  //tangent
  if (mesh->vertex_format_ & ModelMeshData::V_ELEM_TANGENT)
  {
    format |= V_ATTR_TANGENT;
  }

  //color
  if (mesh->vertex_format_ & ModelMeshData::V_ELEM_COLOR)
  {
    format |= V_ATTR_COLOR;
  }

  const T_UINT32 index_count = mesh->index_count_;

  ret->CreateVerticesWithIndex(mesh->vertex_count_, mesh->index_count_, format);

  const T_UINT32 attribute_count = node->GetNodeAttributeCount();
  if (attribute_count == 0)
  {
    return nullptr;
  }

  T_UINT32 submesh_count = 0;

  for (T_UINT32 i = 0; i < attribute_count; ++i)
  {
    FbxNodeAttribute* attr = node->GetNodeAttributeByIndex(i);
    if (attr->GetClassId().Is(FbxMesh::ClassId))
    {
      ++submesh_count;
    }
  }

  if (submesh_count == 0)
  {
    return nullptr;
  }

  T_UINT32* index_counts = new T_UINT32[submesh_count];

  T_UINT32 vertex_count_sum = 0;
  T_UINT32 polygon_count_sum = 0;
  for (T_UINT32 i = 0; i < attribute_count; ++i)
  {
    FbxNodeAttribute* attr = node->GetNodeAttributeByIndex(i);
    if (attr->GetClassId().Is(FbxMesh::ClassId))
    {
      FbxMesh* mesh = (FbxMesh*)attr;
      index_counts[i] = mesh->GetPolygonVertexCount();
      vertex_count_sum += index_counts[i];
      polygon_count_sum += mesh->GetPolygonCount();
    }
  }

  Mesh* ret = new Mesh();
  ret->CreateVertices(
    vertex_count_sum,
    polygon_count_sum,
    GraphicsConstants::V_FORMAT_PNUC
  );
  ret->CreateIndices(submesh_count, index_counts);

  delete[] index_counts;

  T_UINT32 index_offset = 0;
  T_UINT32 vertex_offset = 0;
  for (T_UINT32 attr_index = 0, index_index = 0; attr_index < attribute_count; ++attr_index)
  {
    FbxNodeAttribute* attr = node->GetNodeAttributeByIndex(attr_index);
    if (attr->GetClassId().Is(FbxMesh::ClassId))
    {
      FbxMesh* mesh = (FbxMesh*)attr;
      const T_UINT32 index_count = mesh->GetPolygonVertexCount();
      const T_UINT32 vertex_count = index_count;
      //マテリアル毎のインデックスを取得できるはず
      for (T_UINT32 i = 0; i < index_count; ++i)
      {
        ret->SetIndex(index_index, i, vertex_offset + i);
      }

      const T_UINT32 polygon_count = mesh->GetPolygonCount();

      FbxVector4* src = mesh->GetControlPoints();

      const T_INT32* polygon_indices = mesh->GetPolygonVertices();
      for (T_UINT32 i = 0; i < vertex_count; ++i)
      {
        ret->SetVertex(
          vertex_offset + i,
          {
            (T_FLOAT)src[polygon_indices[i]][0],
            (T_FLOAT)src[polygon_indices[i]][1],
            (T_FLOAT)src[polygon_indices[i]][2],
          });
      }

      T_UINT8 layer_count = mesh->GetLayerCount();
      for (T_UINT8 i = 0; i < layer_count; ++i)
      {
        FbxLayer* layer = mesh->GetLayer(i);

        //法線情報の取得
        FbxLayerElementNormal* normal_element = layer->GetNormals();
        if (normal_element)
        {
          T_UINT32 normal_count = normal_element->GetDirectArray().GetCount();
          T_UINT32 normal_index_count = normal_element->GetIndexArray().GetCount();

          FbxLayerElement::EMappingMode mapping_mode = normal_element->GetMappingMode();
          FbxLayerElement::EReferenceMode reference_mode = normal_element->GetReferenceMode();

          if (mapping_mode == FbxLayerElement::eByPolygonVertex)
          {
            if (reference_mode == FbxLayerElement::eDirect)
            {
              for (T_UINT32 i = 0; i < normal_count; ++i)
              {
                ret->SetNormal(
                  vertex_offset + i,
                  {
                    (T_FLOAT)normal_element->GetDirectArray().GetAt(i)[0],
                    (T_FLOAT)normal_element->GetDirectArray().GetAt(i)[1],
                    (T_FLOAT)normal_element->GetDirectArray().GetAt(i)[2],
                  });
              }
            }
            else if (reference_mode == FbxLayerElement::eIndexToDirect)
            {
              for (T_UINT32 i = 0; i < normal_count; ++i)
              {
                ret->SetNormal(
                  vertex_offset + i,
                  {
                    (T_FLOAT)normal_element->GetDirectArray().GetAt(normal_element->GetIndexArray().GetAt(i))[0],
                    (T_FLOAT)normal_element->GetDirectArray().GetAt(normal_element->GetIndexArray().GetAt(i))[1],
                    (T_FLOAT)normal_element->GetDirectArray().GetAt(normal_element->GetIndexArray().GetAt(i))[2],
                  });
              }
            }
          }
          else if (mapping_mode == FbxLayerElement::eByControlPoint)
          {
            if (reference_mode == FbxLayerElement::eDirect)
            {
              for (T_UINT32 i = 0; i < normal_count; ++i)
              {
                ret->SetNormal(
                  vertex_offset + i,
                  {
                    (T_FLOAT)normal_element->GetDirectArray().GetAt(i)[0],
                    (T_FLOAT)normal_element->GetDirectArray().GetAt(i)[1],
                    (T_FLOAT)normal_element->GetDirectArray().GetAt(i)[2],
                  });
              }
            }
            else if (reference_mode == FbxLayerElement::eIndexToDirect)
            {
              ret->SetNormal(
                vertex_offset + i,
                {
                  (T_FLOAT)normal_element->GetDirectArray().GetAt(normal_element->GetIndexArray().GetAt(i))[0],
                  (T_FLOAT)normal_element->GetDirectArray().GetAt(normal_element->GetIndexArray().GetAt(i))[1],
                  (T_FLOAT)normal_element->GetDirectArray().GetAt(normal_element->GetIndexArray().GetAt(i))[2],
                });
            }
          }
        }
        //UV情報の取得
        FbxLayerElementUV* uv_element = layer->GetUVs();
        if (uv_element)
        {
          T_UINT32 uv_count = uv_element->GetDirectArray().GetCount();
          T_UINT32 uv_index_count = uv_element->GetIndexArray().GetCount();

          FbxLayerElement::EMappingMode mapping_mode = uv_element->GetMappingMode();
          FbxLayerElement::EReferenceMode reference_mode = uv_element->GetReferenceMode();

          if (mapping_mode == FbxLayerElement::eByPolygonVertex)
          {
            if (reference_mode == FbxLayerElement::eDirect)
            {
              for (T_UINT32 i = 0; i < uv_count; ++i)
              {
                ret->SetUv(
                  vertex_offset + i,
                  {
                    (T_FLOAT)uv_element->GetDirectArray().GetAt(i)[0],
                    (T_FLOAT)uv_element->GetDirectArray().GetAt(i)[1]
                  });
              }
            }
            else if (reference_mode == FbxLayerElement::eIndexToDirect)
            {
              for (T_UINT32 i = 0; i < uv_index_count; ++i)
              {
                ret->SetUv(
                  vertex_offset + i,
                  {
                    (T_FLOAT)uv_element->GetDirectArray().GetAt(uv_element->GetIndexArray().GetAt(i))[0],
                    (T_FLOAT)uv_element->GetDirectArray().GetAt(uv_element->GetIndexArray().GetAt(i))[1]
                  });
              }
            }
          }
          else if (mapping_mode == FbxLayerElement::eByControlPoint)
          {
            if (reference_mode == FbxLayerElement::eDirect)
            {
              for (T_UINT32 i = 0; i < uv_count; ++i)
              {
                ret->SetUv(
                  vertex_offset + i,
                  {
                    (T_FLOAT)uv_element->GetDirectArray().GetAt(i)[0],
                    (T_FLOAT)uv_element->GetDirectArray().GetAt(i)[1]
                  });
              }
            }
            else if (reference_mode == FbxLayerElement::eIndexToDirect)
            {
              for (T_UINT32 i = 0; i < uv_index_count; ++i)
              {
                ret->SetUv(
                  vertex_offset + i,
                  {
                    (T_FLOAT)uv_element->GetDirectArray().GetAt(uv_element->GetIndexArray().GetAt(i))[0],
                    (T_FLOAT)uv_element->GetDirectArray().GetAt(uv_element->GetIndexArray().GetAt(i))[1]
                  });
              }
            }
          }
        }
        //頂点カラーの取得
        FbxLayerElementVertexColor* color_element = layer->GetVertexColors();
        if (color_element)
        {
          T_UINT32 color_count = color_element->GetDirectArray().GetCount();
          T_UINT32 color_index_count = color_element->GetIndexArray().GetCount();

          FbxLayerElement::EMappingMode mapping_mode = color_element->GetMappingMode();
          FbxLayerElement::EReferenceMode reference_mode = color_element->GetReferenceMode();
          TColor color = TColor();
          if (mapping_mode == FbxLayerElement::eByPolygonVertex)
          {
            if (reference_mode == FbxLayerElement::eDirect)
            {
              for (T_UINT32 i = 0; i < color_count; ++i)
              {
                color.r = (T_FLOAT)color_element->GetDirectArray().GetAt(i)[0];
                color.g = (T_FLOAT)color_element->GetDirectArray().GetAt(i)[1];
                color.b = (T_FLOAT)color_element->GetDirectArray().GetAt(i)[2];
                color.a = (T_FLOAT)color_element->GetDirectArray().GetAt(i)[3];
                ret->SetColor(vertex_offset + i, color);
              }
            }
            else if (reference_mode == FbxLayerElement::eIndexToDirect)
            {
              for (T_UINT32 i = 0; i < color_index_count; ++i)
              {
                color.r = (T_FLOAT)color_element->GetDirectArray().GetAt(color_element->GetIndexArray().GetAt(i))[0];
                color.g = (T_FLOAT)color_element->GetDirectArray().GetAt(color_element->GetIndexArray().GetAt(i))[1];
                color.b = (T_FLOAT)color_element->GetDirectArray().GetAt(color_element->GetIndexArray().GetAt(i))[2];
                color.a = (T_FLOAT)color_element->GetDirectArray().GetAt(color_element->GetIndexArray().GetAt(i))[3];
                ret->SetColor(vertex_offset + i, color);
              }
            }
          }
          else if (mapping_mode == FbxLayerElement::eByControlPoint)
          {
            if (reference_mode == FbxLayerElement::eDirect)
            {
              for (T_UINT32 i = 0; i < color_count; ++i)
              {
                color.r = (T_FLOAT)color_element->GetDirectArray().GetAt(i)[0];
                color.g = (T_FLOAT)color_element->GetDirectArray().GetAt(i)[1];
                color.b = (T_FLOAT)color_element->GetDirectArray().GetAt(i)[2];
                color.a = (T_FLOAT)color_element->GetDirectArray().GetAt(i)[3];
                ret->SetColor(vertex_offset + i, color);
              }
            }
            else if (reference_mode == FbxLayerElement::eIndexToDirect)
            {
              for (T_UINT32 i = 0; i < color_index_count; ++i)
              {
                color.r = (T_FLOAT)color_element->GetDirectArray().GetAt(color_element->GetIndexArray().GetAt(i))[0];
                color.g = (T_FLOAT)color_element->GetDirectArray().GetAt(color_element->GetIndexArray().GetAt(i))[1];
                color.b = (T_FLOAT)color_element->GetDirectArray().GetAt(color_element->GetIndexArray().GetAt(i))[2];
                color.a = (T_FLOAT)color_element->GetDirectArray().GetAt(color_element->GetIndexArray().GetAt(i))[3];
                ret->SetColor(vertex_offset + i, color);
              }
            }
          }
        }
      }

      index_offset += index_count;
      vertex_offset += vertex_count;
      ++index_index;
    }
  }
  ret->CommitChanges(readonly);

  return ret;
}
