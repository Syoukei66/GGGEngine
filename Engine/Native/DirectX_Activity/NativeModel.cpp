#include "NativeModel.h"

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
  this->textures_ = new const Texture*[this->material_count_]();
  for (T_UINT32 i = 0; i < this->material_count_; ++i)
  {
    this->materials_[i] = new Material((LP_MATERIAL)&materials[i].MatD3D);

    std::string texture_path = asset_path;
    texture_path.append(materials[i].pTextureFilename);
    this->textures_[i] = Texture::DynamicLoad(texture_path.c_str());
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
  delete[] this->textures_;
}

// =================================================================
// Method for/from SuperClass/Interfaces
// =================================================================
void NativeModel_x::Draw() const
{
  const LPDIRECT3DDEVICE9 pDevice = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  for (T_UINT32 i = 0; i < this->material_count_; ++i)
  {
    NativeMethod::Graphics().Graphics_SetMaterial(this->materials_[i]);
    NativeMethod::Graphics().Graphics_SetTexture(this->textures_[i]);
    this->mesh_->DrawSubset(i);
  }
}
