#include "AssimpModelImporter.h"
#include <unordered_map>

#include <assimp\Importer.hpp>
#include <assimp\BaseImporter.h>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "../Common/GraphicsConstants.h"
#include "../Asset/ModelMaterialData.h"

//=============================================================================
// MeshData
//=============================================================================
//static void ImportStaticMesh(const aiScene* scene, StaticModelData* data)
//{
//  using namespace Graphics;
//
//  //���_�t�H�[�}�b�g���Ƀ��f���𕪊�
//  std::unordered_map<T_UINT32, std::vector<T_UINT32>> model_index_per_format;
//  std::unordered_map<T_UINT32, T_UINT32> model_format_size = std::unordered_map<T_UINT32, T_UINT32>();
//  for (T_UINT32 m = 0; m < scene->mNumMeshes; ++m)
//  {
//    const aiMesh* mesh = scene->mMeshes[m];
//    T_UINT32 format = 0;
//    T_UINT32 size = 0;
//    if (mesh->HasPositions())
//    {
//      format |= V_ATTR_POSITION;
//      size += V_ATTRSIZE_POSITION;
//    }
//    if (mesh->HasNormals())
//    {
//      format |= V_ATTR_NORMAL;
//      size += V_ATTRSIZE_NORMAL;
//    }
//    if (mesh->HasTextureCoords(0))
//    {
//      format |= V_ATTR_UV;
//      size += V_ATTRSIZE_UV;
//    }
//    if (mesh->HasTextureCoords(1))
//    {
//      format |= V_ATTR_UV2;
//      size += V_ATTRSIZE_UV2;
//    }
//    if (mesh->HasTextureCoords(2))
//    {
//      format |= V_ATTR_UV3;
//      size += V_ATTRSIZE_UV3;
//    }
//    if (mesh->HasTextureCoords(3))
//    {
//      format |= V_ATTR_UV4;
//      size += V_ATTRSIZE_UV4;
//    }
//    if (mesh->HasTangentsAndBitangents())
//    {
//      format |= V_ATTR_TANGENT;
//      size += V_ATTRSIZE_TANGENT;
//    }
//    if (mesh->HasVertexColors(0))
//    {
//      format |= V_ATTR_COLOR;
//      size += V_ATTRSIZE_COLOR;
//    }
//    if (mesh->HasBones())
//    {
//      format |= V_ATTR_BONE_WEIGHTS;
//      size += V_ATTRSIZE_BONE_WEIGHTS;
//    }
//    model_index_per_format[format].push_back(m);
//    model_format_size[format] = size;
//  }
//  data->mesh_count_ = model_index_per_format.size();
//  data->meshes_ = new ModelMeshData*[data->mesh_count_];
//
//  std::unordered_map<std::string, aiBone*> bone_map = std::unordered_map<std::string, aiBone*>();
//
//  for (T_UINT32 mesh_index = 0; mesh_index < scene->mNumMeshes; ++mesh_index)
//  {
//    aiMesh* mesh = scene->mMeshes[mesh_index];
//    for (T_UINT32 bone_index = 0; bone_index < mesh->mNumBones; ++bone_index)
//    {
//      aiBone* bone = mesh->mBones[bone_index];
//      bone_map[bone->mName.C_Str()] = bone;
//    }
//  }
//
//  std::vector<aiBone*> bones;
//  for (auto& pair : bone_map)
//  {
//    bones.push_back(pair.second);
//  }
//  data->bone_count_ = bones.size();
//  data->bone_names_ = new std::string[data->bone_count_]();
//
//  std::unordered_map<T_UINT32, std::unordered_map<T_UINT32, T_FLOAT>> bone_weight_map = std::unordered_map<T_UINT32, std::unordered_map<T_UINT32, T_FLOAT>>();
//  T_UINT32 bone_index = 0;
//  for (aiBone* bone : bones)
//  {
//    data->bone_names_[bone_index] = bone->mName.C_Str();
//    for (T_UINT32 i = 0; i < bone->mNumWeights; ++i)
//    {
//      bone_weight_map[bone->mWeights[i].mVertexId][bone_index] = bone->mWeights[i].mWeight;
//    }
//    ++bone_index;
//  }
//
//  T_UINT32 m = 0;
//  for (auto& pair : model_index_per_format)
//  {
//    const T_UINT32 format = pair.first;
//    const std::vector<T_UINT32>& mesh_indices = pair.second;
//    ModelMeshData* ret = new ModelMeshData();
//    data->meshes_[m] = ret;
//
//    ret->vertex_format_ = format;
//    ret->vertex_size_ = model_format_size[format];
//    ret->submesh_count_ = mesh_indices.size();
//    ret->submesh_index_counts_ = new T_UINT32[ret->submesh_count_]();
//    T_UINT32 submesh_index = 0;
//    for (T_UINT32 mesh_index : mesh_indices)
//    {
//      aiMesh* mesh = scene->mMeshes[mesh_index];
//      ret->vertex_count_ += mesh->mNumVertices;
//      ret->polygon_count_ += mesh->mNumFaces;
//      T_UINT32 index_count = 0;
//      for (T_UINT32 f = 0; f < mesh->mNumFaces; ++f)
//      {
//        index_count += mesh->mFaces[f].mNumIndices;
//      }
//      ret->index_count_ += index_count;
//      ret->submesh_index_counts_[submesh_index] = index_count;
//      ++submesh_index;
//    }
//
//    //���_�����̃Z�b�g
//    ret->vertices_ = new T_FLOAT[ret->vertex_count_ * ret->vertex_size_]();
//    T_UINT32 i = 0;
//    for (T_UINT32 mesh_index : mesh_indices)
//    {
//      aiMesh* mesh = scene->mMeshes[mesh_index];
//      for (T_UINT32 vi = 0; vi < mesh->mNumVertices; ++vi)
//      {
//        //mesh�̒��_�������L�^
//        if (ret->vertex_format_ & V_ATTR_POSITION)
//        {
//          ret->vertices_[i + 0] = mesh->mVertices[vi].x;
//          ret->vertices_[i + 1] = mesh->mVertices[vi].y;
//          ret->vertices_[i + 2] = mesh->mVertices[vi].z;
//          i += V_ATTRSIZE_POSITION;
//        }
//        if (ret->vertex_format_ & V_ATTR_NORMAL)
//        {
//          ret->vertices_[i + 0] = mesh->mNormals[vi].x;
//          ret->vertices_[i + 1] = mesh->mNormals[vi].y;
//          ret->vertices_[i + 2] = mesh->mNormals[vi].z;
//          i += V_ATTRSIZE_NORMAL;
//        }
//        if (ret->vertex_format_ & V_ATTR_UV)
//        {
//          ret->vertices_[i + 0] = mesh->mTextureCoords[0][vi].x;
//          ret->vertices_[i + 1] = mesh->mTextureCoords[0][vi].y;
//          i += V_ATTRSIZE_UV;
//        }
//        if (ret->vertex_format_ & V_ATTR_UV2)
//        {
//          ret->vertices_[i + 0] = mesh->mTextureCoords[1][vi].x;
//          ret->vertices_[i + 1] = mesh->mTextureCoords[1][vi].y;
//          i += V_ATTRSIZE_UV2;
//        }
//        if (ret->vertex_format_ & V_ATTR_UV3)
//        {
//          ret->vertices_[i + 0] = mesh->mTextureCoords[2][vi].x;
//          ret->vertices_[i + 1] = mesh->mTextureCoords[2][vi].y;
//          i += V_ATTRSIZE_UV3;
//        }
//        if (ret->vertex_format_ & V_ATTR_UV4)
//        {
//          ret->vertices_[i + 0] = mesh->mTextureCoords[3][vi].x;
//          ret->vertices_[i + 1] = mesh->mTextureCoords[3][vi].y;
//          i += V_ATTRSIZE_UV4;
//        }
//        if (ret->vertex_format_ & V_ATTR_TANGENT)
//        {
//          //TODO:�G���W�����̃t�H�[�}�b�g�ɍ����Ȃ��̂ŁA
//          //�t�@�C�������^�����ꂽ�f�[�^���g�킸�A
//          //�Ǝ��Ɍv�Z�����K�v������
//          //���x�D���ׁ̈A�t�@�C���T�C�Y���������͎̂d�����Ȃ�
//          ret->vertices_[i + 0] = mesh->mTangents[vi].x;
//          ret->vertices_[i + 1] = mesh->mTangents[vi].y;
//          ret->vertices_[i + 2] = mesh->mTangents[vi].z;
//          ret->vertices_[i + 3] = 0.0f;
//          i += V_ATTRSIZE_TANGENT;
//        }
//        if (ret->vertex_format_ & V_ATTR_COLOR)
//        {
//          ret->vertices_[i + 0] =
//            (((T_UINT8)(mesh->mColors[0][vi].a * 0xff) & 0xff) << 24) |
//            (((T_UINT8)(mesh->mColors[0][vi].r * 0xff) & 0xff) << 16) |
//            (((T_UINT8)(mesh->mColors[0][vi].g * 0xff) & 0xff) <<  8) |
//            (((T_UINT8)(mesh->mColors[0][vi].b * 0xff) & 0xff) <<  0);
//          i += V_ATTRSIZE_COLOR;
//        }
//        if (ret->vertex_format_ & V_ATTR_BONE_WEIGHTS)
//        {
//          if (bone_weight_map.find(vi) != bone_weight_map.end())
//          {
//            std::unordered_map<T_UINT32, T_FLOAT>& weights = bone_weight_map[vi];
//
//            T_UINT32 bi = 0;
//            for (auto& pair : weights)
//            {
//              ret->vertices_[i + bi + 0] = pair.first;
//              ret->vertices_[i + bi + 4] = pair.second;
//              ++bi;
//            }
//          }
//          i += V_ATTRSIZE_BONE_WEIGHTS;
//        }
//      }
//    }
//
//    //�C���f�b�N�X�̃Z�b�g
//    T_UINT32 i = 0;
//    ret->indices_ = new T_UINT32[ret->index_count_]();
//    for (T_UINT32 mesh_index : mesh_indices)
//    {
//      aiMesh* mesh = scene->mMeshes[mesh_index];
//
//      for (T_UINT32 f = 0; f < mesh->mNumFaces; ++f)
//      {
//        for (T_UINT32 fi = 0; fi < mesh->mFaces[f].mNumIndices; ++fi)
//        {
//          ret->indices_[i] = mesh->mFaces[f].mIndices[fi];
//          ++i;
//        }
//      }
//    }
//    ++m;
//  }
//}

////=============================================================================
//// TextureData
////=============================================================================
//static ModelTextureData* ImportTexture(const aiMaterial* material, aiTextureType type, T_UINT32 index)
//{
//  aiString path;
//  aiTextureMapping mapping;
//  T_UINT32 uv_index;
//  T_FLOAT blend;
//  aiTextureOp op;
//  aiTextureMapMode map_mode;
//  material->GetTexture(type, index, &path, &mapping, &uv_index, &blend, &op, &map_mode);
//
//  ModelTextureData* ret = new ModelTextureData();
//  ret->path_ = path.C_Str();
//  ret->mapping_ = ConvertTextureMapping(mapping);
//  ret->uv_index_ = uv_index;
//  ret->blend_ = blend;
//  ret->op_ = ConvertTextureOp(op);
//  ret->map_mode_ = ConvertTextureMapMode(map_mode);
//  return ret;
//}
//
////=============================================================================
//// MaterialData
////=============================================================================
//static ModelTextureData** CreateTextureDatas(T_UINT32 texture_count, const aiMaterial* material, aiTextureType type)
//{
//  if (texture_count == 0)
//  {
//    return nullptr;
//  }
//
//  ModelTextureData** ret = new ModelTextureData*[texture_count]();
//
//  for (T_UINT32 i = 0; i < texture_count; ++i)
//  {
//    ret[i] = ImportTexture(material, type, i);
//  }
//
//  return ret;
//}
//
//static ModelMaterialData* ImportMaterial(const aiMaterial* material)
//{
//  ModelMaterialData* ret = new ModelMaterialData();
//
//  for (T_UINT32 i = 0; i < AI_TEXTURE_TYPE_MAX; ++i)
//  {
//    const aiTextureType type = (aiTextureType)i;
//    const T_INT32 index = ConvertTextureType(type);
//    ret->texture_counts_[index] = material->GetTextureCount(type);
//    ret->texture_datas_[index] = CreateTextureDatas(ret->texture_counts_[index], material, type);
//  }
//
//  return ret;
//}
