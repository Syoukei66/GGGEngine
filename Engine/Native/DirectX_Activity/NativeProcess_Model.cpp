#include "NativeProcess_Model.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <Director.h>
#include <HalEngine.h>
#include "DirectXDirector.h"

struct DirectXModelData {
public:
  LPD3DXMESH mesh;
  T_UINT32 material_count;
  Material** materials;
  const ITexture** textures;
};

LP_MODEL NativeProcess_Model::Model_Load(const char* full_path)
{
  const LPDIRECT3DDEVICE9 pDevice = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  DirectXModelData* ret = new DirectXModelData();
  LPD3DXBUFFER pAdjacency = NULL;
  LPD3DXBUFFER materialBuffer;
  DWORD material_count = 0;
  D3DXLoadMeshFromX(
    full_path,
    D3DXMESH_SYSTEMMEM,
    pDevice,
    &pAdjacency,
    &materialBuffer,
    NULL,
    &material_count,
    &ret->mesh
  );
  ret->material_count = material_count;
  static const DWORD d3dxMeshOpt = D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE;
  ret->mesh->OptimizeInplace(d3dxMeshOpt, (DWORD*)pAdjacency->GetBufferPointer(), NULL, NULL, NULL);
  LPD3DXMESH pCloneMesh;
  D3DVERTEXELEMENT9 elements[MAXD3DDECLLENGTH + 1];
  ret->mesh->GetDeclaration(elements);
  ret->mesh->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY, elements, pDevice, &pCloneMesh);
  ret->mesh->Release();
  ret->mesh = pCloneMesh;

  D3DXMATERIAL* materials;
  materials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();

  ret->materials = new Material*[ret->material_count]();
  ret->textures = new const ITexture*[ret->material_count]();
  for (T_UINT32 i = 0; i < ret->material_count; ++i) {
    ret->materials[i] = new Material((LP_MATERIAL)&materials[i].MatD3D);
    ret->textures[i] = HalEngine::Resource::GetTexture(materials[i].pTextureFilename);
  }
  return (LP_MODEL)ret;
}

void NativeProcess_Model::Model_Unload(LP_MODEL model)
{
}

void NativeProcess_Model::Model_Draw(LP_MODEL model)
{
  const LPDIRECT3DDEVICE9 pDevice = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  DirectXModelData* dx_model = (DirectXModelData*)model;
  for (T_UINT32 i = 0; i < dx_model->material_count; ++i)
  {
    NativeMethod::Graphics().Graphics_SetMaterial(dx_model->materials[i]);
    NativeMethod::Graphics().Graphics_SetTexture(dx_model->textures[i]);
    dx_model->mesh->DrawSubset(i);
  }
}
