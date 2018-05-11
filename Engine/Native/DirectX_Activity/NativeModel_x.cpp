#include "NativeModel_x.h"

// =================================================================
// Constructor / Destructor
// =================================================================
NativeModel_x::NativeModel_x(const char* asset_path, const char* name)
  : INativeModel(nullptr)
{
  const LPDIRECT3DDEVICE9 pDevice = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  LPD3DXBUFFER pAdjacency = NULL;
  LPD3DXBUFFER materialBuffer;
  DWORD material_count = 0;

  std::string full_path = asset_path;
  full_path.append(name);

  D3DXLoadMeshFromX(
    full_path.c_str(),
    D3DXMESH_SYSTEMMEM,
    pDevice,
    &pAdjacency,
    &materialBuffer,
    NULL,
    &material_count,
    &this->mesh_
  );
  this->material_count_ = material_count;
  static const DWORD d3dxMeshOpt = D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE;
  this->mesh_->OptimizeInplace(d3dxMeshOpt, (DWORD*)pAdjacency->GetBufferPointer(), NULL, NULL, NULL);
 
  LPD3DXMESH pCloneMesh;
  D3DVERTEXELEMENT9 elements[MAXD3DDECLLENGTH + 1];
  this->mesh_->GetDeclaration(elements);
  this->mesh_->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY, elements, pDevice, &pCloneMesh);
  this->mesh_->Release();
  this->mesh_ = pCloneMesh;

  D3DXMATERIAL* materials;
  materials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();

  this->materials_ = new Material*[this->material_count_]();
  for (T_UINT32 i = 0; i < this->material_count_; ++i)
  {
    const D3DMATERIAL9& mat = materials[i].MatD3D;
    this->materials_[i] = new Material(EngineAsset::Shader::LAMBERT);
    this->materials_[i]->SetDiffuse(mat.Diffuse.r, mat.Diffuse.g, mat.Diffuse.b, mat.Diffuse.a);
    this->materials_[i]->ColorProperty("_Ambient") = Color4F(mat.Ambient.r, mat.Ambient.g, mat.Ambient.b, mat.Ambient.a);
    this->materials_[i]->ColorProperty("_Emissive") = Color4F(mat.Emissive.r, mat.Emissive.g, mat.Emissive.b, mat.Emissive.a);
    this->materials_[i]->ColorProperty("_Specular") = Color4F(mat.Specular.r, mat.Specular.g, mat.Specular.b, mat.Specular.a);
    this->materials_[i]->FloatProperty("_SpecularPower") = mat.Power;
    std::string texture_path = asset_path;
    texture_path.append(materials[i].pTextureFilename);
    this->materials_[i]->SetMainTexture(TextureResource::DynamicLoad(texture_path.c_str())->GetContents());
  }
}

NativeModel_x::~NativeModel_x()
{
  this->mesh_->Release();
  for (T_UINT32 i = 0; i < this->material_count_; ++i)
  {
    delete this->materials_[i];
  }
  delete[] this->materials_;
}

// =================================================================
// Method for/from SuperClass/Interfaces
// =================================================================
void NativeModel_x::Draw(GameObjectRenderState* state) const
{
  const LPDIRECT3DDEVICE9 pDevice = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  for (T_UINT32 i = 0; i < this->material_count_; ++i)
  {
    Material* material = this->materials_[i];
    const T_UINT8 pass_count = material->Begin();
    for (T_UINT8 j = 0; j < pass_count; ++j)
    {
      material->BeginPass(j);
      material->SetDefaultProperties(state);
      material->CommitChanges();
      this->mesh_->DrawSubset(i);
      material->EndPass();
    }
    material->End();
  }
}
