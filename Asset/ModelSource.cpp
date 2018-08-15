//#include "ModelSource.h"
//
////=============================================================================
//// NodeNode
////=============================================================================
//ModelNodeSource::ModelNodeSource(ModelSource* model, ModelNodeData* data)
//{
//}
//
//ModelNodeSource::~ModelNodeSource()
//{
//}
//
//ModelNode* ModelNodeSource::Create()
//{
//  return nullptr;
//}
//
////=============================================================================
//// Model
////=============================================================================
//ModelSource::ModelSource(ModelData* data)
//{
//  using namespace Graphics;
//
//  if (data->mesh_count_ > 0)
//  {
//    const T_UINT32 format = data->meshes_[0]->vertex_format_;
//    T_UINT32 vertex_count = 0;
//    T_UINT32 index_count = 0;
//    T_UINT32* index_counts = new T_UINT32[data->mesh_count_];
//    INativeIndexBuffer** index_buffer = new INativeIndexBuffer*[data->mesh_count_]();
//    for (T_UINT32 i = 0; i < data->mesh_count_; ++i)
//    {
//      vertex_count += data->meshes_[i]->vertex_count_;
//      index_counts[i] = data->meshes_[i]->index_count_;
//      index_count += index_counts[i];
//    }
//
//    Mesh* mesh = new Mesh();
//    mesh->CreateIndices(data->mesh_count_, index_counts);
//
//    for (T_UINT32 i = 0; i < data->mesh_count_; ++i)
//    {
//      for (T_UINT32 j = 0; j < data->meshes_[i]->index_count_; ++j)
//      {
//        mesh->SetIndex(i, j, data->meshes_[i]->indices_[j]);
//      }
//    }
//
//    mesh->CreateVerticesWithIndex(vertex_count, index_count, format);
//    for (T_UINT32 i = 0, vi = 0; i < data->mesh_count_; ++i)
//    {
//      for (T_UINT32 j = 0; j < data->meshes_[i]->vertex_count_; ++j, ++vi)
//      {
//        if (format & V_ATTR_POSITION)
//        {
//          mesh->SetVertex(vi, data->meshes_[i]->vertices_[j]);
//        }
//        if (format & V_ATTR_NORMAL)
//        {
//          mesh->SetNormal(vi, data->meshes_[i]->normals_[j]);
//        }
//        if (format & V_ATTR_UV)
//        {
//          mesh->SetUv(vi, data->meshes_[i]->uvs_[j]);
//        }
//        if (format & V_ATTR_UV2)
//        {
//          mesh->SetUv2(vi, data->meshes_[i]->uv2s_[j]);
//        }
//        if (format & V_ATTR_UV3)
//        {
//          mesh->SetUv3(vi, data->meshes_[i]->uv3s_[j]);
//        }
//        if (format & V_ATTR_UV4)
//        {
//          mesh->SetUv4(vi, data->meshes_[i]->uv4s_[j]);
//        }
//        if (format & V_ATTR_TANGENT)
//        {
//          mesh->SetTangent(vi, TVec4f(data->meshes_[i]->tangents_[j], 0.0f));
//        }
//        if (format & V_ATTR_COLOR)
//        {
//          mesh->SetColor(vi, data->meshes_[i]->colors_[j]);
//        }
//      }
//    }
//
//    mesh->CommitChanges(true);
//
//    this->master_mesh_ = mesh->CloneStatic();
//  }
//
//}
//
//ModelSource::~ModelSource()
//{
//}
//
//Model* ModelSource::Create()
//{
//  return nullptr;
//}
