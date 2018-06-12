#include "MeshFactory_Fbx.h"
#include "GraphicsConstants.h"

Mesh* MeshFactory::Fbx::Create(FbxMesh* mesh, bool readonly)
{
  const T_UINT32 polygon_count = mesh->GetPolygonCount();
  const T_UINT32 index_count = mesh->GetPolygonVertexCount();
  const T_UINT16 vertex_count = index_count;

  Mesh* ret = new Mesh();
  ret->CreateVertices(
    vertex_count,
    polygon_count,
    GraphicsConstants::V_FORMAT_PNUC
  );
  ret->CreateIndices(index_count);

  //マテリアル毎のインデックスを取得できるはず
  for (T_UINT16 i = 0; i < index_count; ++i)
  {
    ret->SetIndex(i, i);
  }

  FbxVector4* src = mesh->GetControlPoints();

  const T_INT32* polygon_indices = mesh->GetPolygonVertices();
  for (T_UINT16 i = 0; i < vertex_count; ++i)
  {
    ret->SetVertex(i, 
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
            ret->SetNormal(i,
            {
              (T_FLOAT)normal_element->GetDirectArray().GetAt(i)[0],
              (T_FLOAT)normal_element->GetDirectArray().GetAt(i)[1],
              (T_FLOAT)normal_element->GetDirectArray().GetAt(i)[2],
            });
          }
        }
        else if (reference_mode == FbxLayerElement::eIndexToDirect)
        {
          for (T_UINT16 i = 0; i < normal_count; ++i)
          {
            ret->SetNormal(i,
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
          for (T_UINT16 i = 0; i < normal_count; ++i)
          {
            ret->SetNormal(i,
            {
              (T_FLOAT)normal_element->GetDirectArray().GetAt(i)[0],
              (T_FLOAT)normal_element->GetDirectArray().GetAt(i)[1],
              (T_FLOAT)normal_element->GetDirectArray().GetAt(i)[2],
            });
          }
        }
        else if (reference_mode == FbxLayerElement::eIndexToDirect)
        {
          ret->SetNormal(i,
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
      T_UINT16 uv_count = uv_element->GetDirectArray().GetCount();
      T_UINT16 uv_index_count = uv_element->GetIndexArray().GetCount();

      FbxLayerElement::EMappingMode mapping_mode = uv_element->GetMappingMode();
      FbxLayerElement::EReferenceMode reference_mode = uv_element->GetReferenceMode();

      if (mapping_mode == FbxLayerElement::eByPolygonVertex)
      {
        if (reference_mode == FbxLayerElement::eDirect)
        {
          for (T_UINT16 i = 0; i < uv_count; ++i)
          {
            ret->SetUv(i,
            {
              (T_FLOAT)uv_element->GetDirectArray().GetAt(i)[0],
              (T_FLOAT)uv_element->GetDirectArray().GetAt(i)[1]
            });
          }
        }
        else if (reference_mode == FbxLayerElement::eIndexToDirect)
        {
          for (T_UINT16 i = 0; i < uv_index_count; ++i)
          {
            ret->SetUv(i,
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
          for (T_UINT16 i = 0; i < uv_count; ++i)
          {
            ret->SetUv(i,
            {
              (T_FLOAT)uv_element->GetDirectArray().GetAt(i)[0],
              (T_FLOAT)uv_element->GetDirectArray().GetAt(i)[1]
            });
          }
        }
        else if (reference_mode == FbxLayerElement::eIndexToDirect)
        {
          for (T_UINT16 i = 0; i < uv_index_count; ++i)
          {
            ret->SetUv(i,
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
      T_UINT16 color_count = color_element->GetDirectArray().GetCount();
      T_UINT16 color_index_count = color_element->GetIndexArray().GetCount();

      FbxLayerElement::EMappingMode mapping_mode = color_element->GetMappingMode();
      FbxLayerElement::EReferenceMode reference_mode = color_element->GetReferenceMode();
      Color4F color = Color4F();
      if (mapping_mode == FbxLayerElement::eByPolygonVertex)
      {
        if (reference_mode == FbxLayerElement::eDirect)
        {
          for (T_UINT16 i = 0; i < color_count; ++i)
          {
            color.r = (T_FLOAT)color_element->GetDirectArray().GetAt(i)[0];
            color.g = (T_FLOAT)color_element->GetDirectArray().GetAt(i)[1];
            color.b = (T_FLOAT)color_element->GetDirectArray().GetAt(i)[2];
            color.a = (T_FLOAT)color_element->GetDirectArray().GetAt(i)[3];
            ret->SetColor(i, color);
          }
        }
        else if (reference_mode == FbxLayerElement::eIndexToDirect)
        {
          for (T_UINT16 i = 0; i < color_index_count; ++i)
          {
            color.r = (T_FLOAT)color_element->GetDirectArray().GetAt(color_element->GetIndexArray().GetAt(i))[0];
            color.g = (T_FLOAT)color_element->GetDirectArray().GetAt(color_element->GetIndexArray().GetAt(i))[1];
            color.b = (T_FLOAT)color_element->GetDirectArray().GetAt(color_element->GetIndexArray().GetAt(i))[2];
            color.a = (T_FLOAT)color_element->GetDirectArray().GetAt(color_element->GetIndexArray().GetAt(i))[3];
            ret->SetColor(i, color);
          }
        }
      }
      else if (mapping_mode == FbxLayerElement::eByControlPoint)
      {
        if (reference_mode == FbxLayerElement::eDirect)
        {
          for (T_UINT16 i = 0; i < color_count; ++i)
          {
            color.r = (T_FLOAT)color_element->GetDirectArray().GetAt(i)[0];
            color.g = (T_FLOAT)color_element->GetDirectArray().GetAt(i)[1];
            color.b = (T_FLOAT)color_element->GetDirectArray().GetAt(i)[2];
            color.a = (T_FLOAT)color_element->GetDirectArray().GetAt(i)[3];
            ret->SetColor(i, color);
          }
        }
        else if (reference_mode == FbxLayerElement::eIndexToDirect)
        {
          for (T_UINT16 i = 0; i < color_index_count; ++i)
          {
            color.r = (T_FLOAT)color_element->GetDirectArray().GetAt(color_element->GetIndexArray().GetAt(i))[0];
            color.g = (T_FLOAT)color_element->GetDirectArray().GetAt(color_element->GetIndexArray().GetAt(i))[1];
            color.b = (T_FLOAT)color_element->GetDirectArray().GetAt(color_element->GetIndexArray().GetAt(i))[2];
            color.a = (T_FLOAT)color_element->GetDirectArray().GetAt(color_element->GetIndexArray().GetAt(i))[3];
            ret->SetColor(i, color);
          }
        }
      }
    }
  }

  ret->CommitChanges(readonly);

  return ret;
}
