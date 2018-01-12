#include "NativeProcess_Material.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <Director.h>

LP_MATERIAL NativeProcess_Material::Material_Create()
{
  return (LP_MATERIAL)(new D3DMATERIAL9());
}

void NativeProcess_Material::Material_Delete(LP_MATERIAL material)
{
  delete (D3DMATERIAL9*)material;
}

void NativeProcess_Material::Material_SetDiffuse(LP_MATERIAL material, const Color& color)
{
  D3DMATERIAL9* mat = (D3DMATERIAL9*)material;
  mat->Diffuse.r = color.GetRed() / 255.0f;
  mat->Diffuse.g = color.GetGreen() / 255.0f;
  mat->Diffuse.b = color.GetBlue() / 255.0f;
  mat->Diffuse.a = color.GetAlpha() / 255.0f;
}

void NativeProcess_Material::Material_SetAmbient(LP_MATERIAL material, const Color& color)
{
  D3DMATERIAL9* mat = (D3DMATERIAL9*)material;
  mat->Ambient.r = color.GetRed() / 255.0f;
  mat->Ambient.g = color.GetGreen() / 255.0f;
  mat->Ambient.b = color.GetBlue() / 255.0f;
  mat->Ambient.a = color.GetAlpha() / 255.0f;
}
