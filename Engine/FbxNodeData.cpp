#include "FbxNodeData.h"
#include "EngineAsset.h"

// =================================================================
// Constructor / Destructor
// =================================================================
FbxNodeData::FbxNodeData(FbxNode* node)
  : node_(node)
  , child_count_(node->GetChildCount())
  , mesh_material_(nullptr)
  , mesh_(nullptr)
{
  this->material_ = EngineAsset::Material::MODEL.Clone();
  FbxMesh* mesh = node->GetMesh();
  if (mesh)
  {
    this->mesh_material_ = new FbxMeshMaterial(mesh);
    this->mesh_ = new Mesh(*this->mesh_material_);
  }
  this->children_ = new FbxNodeData*[this->child_count_];
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    this->children_[i] = new FbxNodeData(node->GetChild(i));
    this->children_[i]->parent_ = this;
  }
  //ƒ}ƒeƒŠƒAƒ‹î•ñ‚ÌŽæ“¾
  T_UINT8 material_count = node->GetMaterialCount();
  for (T_UINT8 i = 0; i < material_count; ++i)
  {
    FbxSurfaceMaterial* material = node->GetMaterial(i);
    if (!material)
    {
      continue;
    }
    if (material->GetClassId().Is(FbxSurfaceLambert::ClassId) || material->GetClassId().Is(FbxSurfacePhong::ClassId))
    {
      FbxSurfaceLambert* surface = (FbxSurfaceLambert*)material;

      this->material_->SetDiffuse(
        surface->Diffuse.Get()[0],
        surface->Diffuse.Get()[1],
        surface->Diffuse.Get()[2]
      );
      this->material_->FloatProperty("_DiffuseFactor") = surface->DiffuseFactor.Get();

      this->material_->ColorProperty("_Ambient") = Color4F(
        surface->Ambient.Get()[0],
        surface->Ambient.Get()[1],
        surface->Ambient.Get()[2]
      );
      this->material_->FloatProperty("_AmbientFactor") = surface->AmbientFactor.Get();

      this->material_->ColorProperty("_Emissive") = Color4F(
        surface->Emissive.Get()[0],
        surface->Emissive.Get()[1],
        surface->Emissive.Get()[2]
        );
      this->material_->FloatProperty("_LightBrightness") = surface->EmissiveFactor.Get();

      this->material_->Vec3fProperty("_Bump") = TVec3f(
        surface->Bump.Get()[0],
        surface->Bump.Get()[1],
        surface->Bump.Get()[2]
      );
      this->material_->FloatProperty("_BumpFactor") = surface->BumpFactor.Get();
    }
    if (material->GetClassId().Is(FbxSurfacePhong::ClassId))
    {
      FbxSurfacePhong* surface = (FbxSurfacePhong*)material;
      
      this->material_->ColorProperty("_Specular") = Color4F(
        surface->Specular.Get()[0],
        surface->Specular.Get()[1],
        surface->Specular.Get()[2]
      );
      this->material_->FloatProperty("_SpecularFactor") = surface->SpecularFactor.Get();

      this->material_->FloatProperty("_Power") = surface->Shininess.Get();
      
      this->material_->ColorProperty("_Reflection") = Color4F(
        surface->Reflection.Get()[0],
        surface->Reflection.Get()[1],
        surface->Reflection.Get()[2]
      );
      this->material_->FloatProperty("_ReflectionFactor") = surface->ReflectionFactor.Get();

      this->material_->ColorProperty("_Transparent") = Color4F(
        surface->TransparentColor.Get()[0],
        surface->TransparentColor.Get()[1],
        surface->TransparentColor.Get()[2]
      );
      this->material_->FloatProperty("_TransparentFactor") = surface->TransparencyFactor.Get();
    }
  }
}

FbxNodeData::~FbxNodeData()
{
  delete this->mesh_;
  delete this->mesh_material_;
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    delete this->children_[i];
  }
  delete[] this->children_;
}

// =================================================================
// Method
// =================================================================
FbxNodeData* FbxNodeData::FindFromChildren(const char* name)
{
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    if (strcmp(name, this->children_[i]->node_->GetName()) == 0)
    {
      return this->children_[i];
    }
  }
  return nullptr;
}

FbxNodeData* FbxNodeData::FindFromTree(const char* name)
{
  FbxNodeData* ret = this->FindFromChildren(name);
  if (ret)
  {
    return ret;
  }
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    ret = this->children_[i]->FindFromTree(name);
    if (ret)
    {
      return ret;
    }
  }
  return nullptr;
}
