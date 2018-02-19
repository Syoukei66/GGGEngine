#include "FbxNodeData.h"
#include "EngineAsset.h"

// =================================================================
// Constructor / Destructor
// =================================================================
FbxNodeData::FbxNodeData(FbxNode* node)
  : node_(node)
  , child_count_(node->GetChildCount())
  , mesh_(nullptr)
  , mesh_materials_(nullptr)
  , translate_(0.0f, 0.0f, 0.0f)
  , scaling_(1.0f, 1.0f, 1.0f)
  , rotation_(0.0f, 0.0f, 0.0f)
{
  this->translate_.x = node->LclTranslation.Get()[0];
  this->translate_.y = node->LclTranslation.Get()[1];
  this->translate_.z = node->LclTranslation.Get()[2];

  this->scaling_.x = node->LclScaling.Get()[0];
  this->scaling_.y = node->LclScaling.Get()[1];
  this->scaling_.z = node->LclScaling.Get()[2];

  this->rotation_.x = MathConstants::DegToRad(node->LclRotation.Get()[0]);
  this->rotation_.y = MathConstants::DegToRad(node->LclRotation.Get()[1]);
  this->rotation_.z = MathConstants::DegToRad(node->LclRotation.Get()[2]);

  this->mesh_material_count_ = 0;
  T_UINT16 attribute_count = node->GetNodeAttributeCount();
  for (T_UINT16 i = 0; i < attribute_count; ++i)
  {
    FbxNodeAttribute* attr = node->GetNodeAttributeByIndex(i);
    if (attr->GetClassId().Is(FbxMesh::ClassId))
    {
      ++this->mesh_material_count_;
    }
  }
  if (this->mesh_material_count_ > 0)
  {
    this->mesh_ = new Mesh();
    this->mesh_materials_ = new FbxMeshMaterial*[this->mesh_material_count_]();
    T_UINT8 mesh_index = 0;
    for (T_UINT16 i = 0; i < attribute_count; ++i)
    {
      FbxNodeAttribute* attr = node->GetNodeAttributeByIndex(i);
      if (attr->GetClassId().Is(FbxMesh::ClassId))
      {
        this->mesh_materials_[mesh_index] = new FbxMeshMaterial((FbxMesh*)attr);
        this->mesh_->AddSubMesh(this->mesh_materials_[mesh_index]->CreateSubMesh());
        ++mesh_index;
      }
    }
  }
  this->children_ = new FbxNodeData*[this->child_count_];
  for (T_UINT8 i = 0; i < this->child_count_; ++i)
  {
    this->children_[i] = new FbxNodeData(node->GetChild(i));
    this->children_[i]->parent_ = this;
  }
  //ƒ}ƒeƒŠƒAƒ‹î•ñ‚ÌŽæ“¾
  this->material_count_ = node->GetMaterialCount();
  if (this->material_count_ == 0)
  {
    this->material_count_ = 1;
    this->material_ = new Material*[this->material_count_];
    this->material_[0] = EngineAsset::Material::DEFAULT.Clone();
    return;
  }
  this->material_ = new Material*[this->material_count_];
  for (T_UINT8 i = 0; i < this->material_count_; ++i)
  {
    FbxSurfaceMaterial* material = node->GetMaterial(i);

    if (material->GetClassId().Is(FbxSurfacePhong::ClassId))
    {
      this->material_[i] = EngineAsset::Material::PHONG.Clone();
    }
    else if (material->GetClassId().Is(FbxSurfaceLambert::ClassId))
    {
      this->material_[i] = EngineAsset::Material::LAMBERT.Clone();
    }
    if (material->GetClassId().Is(FbxSurfaceLambert::ClassId) || material->GetClassId().Is(FbxSurfacePhong::ClassId))
    {
      FbxSurfaceLambert* surface = (FbxSurfaceLambert*)material;

      this->material_[i]->SetDiffuse(
        surface->Diffuse.Get()[0],
        surface->Diffuse.Get()[1],
        surface->Diffuse.Get()[2]
      );
      this->material_[i]->FloatProperty("_DiffuseFactor") = surface->DiffuseFactor.Get();

      //this->material_[i]->ColorProperty("_Ambient") = Color4F(
      //  surface->Ambient.Get()[0],
      //  surface->Ambient.Get()[1],
      //  surface->Ambient.Get()[2]
      //);
      this->material_[i]->FloatProperty("_AmbientFactor") = surface->AmbientFactor.Get();

      this->material_[i]->ColorProperty("_Emissive") = Color4F(
        surface->Emissive.Get()[0],
        surface->Emissive.Get()[1],
        surface->Emissive.Get()[2]
        );
      this->material_[i]->FloatProperty("_LightBrightness") = surface->EmissiveFactor.Get();

      this->material_[i]->Vec3fProperty("_Bump") = TVec3f(
        surface->Bump.Get()[0],
        surface->Bump.Get()[1],
        surface->Bump.Get()[2]
      );
      this->material_[i]->FloatProperty("_BumpFactor") = surface->BumpFactor.Get();
    }
    if (material->GetClassId().Is(FbxSurfacePhong::ClassId))
    {
      FbxSurfacePhong* surface = (FbxSurfacePhong*)material;
      
      this->material_[i]->ColorProperty("_Specular") = Color4F(
        surface->Specular.Get()[0],
        surface->Specular.Get()[1],
        surface->Specular.Get()[2]
      );
      this->material_[i]->FloatProperty("_SpecularFactor") = surface->SpecularFactor.Get();

      this->material_[i]->FloatProperty("_Power") = surface->Shininess.Get();
      
      this->material_[i]->ColorProperty("_Reflection") = Color4F(
        surface->Reflection.Get()[0],
        surface->Reflection.Get()[1],
        surface->Reflection.Get()[2]
      );
      this->material_[i]->FloatProperty("_ReflectionFactor") = surface->ReflectionFactor.Get();

      this->material_[i]->ColorProperty("_Transparent") = Color4F(
        surface->TransparentColor.Get()[0],
        surface->TransparentColor.Get()[1],
        surface->TransparentColor.Get()[2]
      );
      this->material_[i]->FloatProperty("_TransparentFactor") = surface->TransparencyFactor.Get();
    }
  }
}

FbxNodeData::~FbxNodeData()
{
  delete[] this->material_;
  delete this->mesh_;
  for (T_UINT8 i = 0; i < this->mesh_material_count_; ++i)
  {
    delete this->mesh_materials_[i];
  }
  delete[] this->mesh_materials_;
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
