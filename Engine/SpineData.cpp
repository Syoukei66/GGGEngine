#define _CRT_SECURE_NO_WARNINGS
#include "SpineData.h"
#include <spine/extension.h>

#include "TextureResource.h"
#include "EngineAttachmentLoader.h"
#include "NativeMethod.h"
#include "Director.h"
#include "Moniker.h"


void _spAtlasPage_createTexture(spAtlasPage* self, const char* path)
{
  TextureResource* texture = new TextureResource(path);
  texture->Load();
  self->rendererObject = (void*)texture;
  self->width = texture->GetWidth();
  self->height = texture->GetHeight();
}

void _spAtlasPage_disposeTexture(spAtlasPage* self)
{
  //テクスチャは既にロードしてあるものしか使用できないのでこの処理は行われない
}

char* _spUtil_readFile(const char* path, int* length)
{
  std::string str = NativeMethod::IO().TextFile_Read(path);
  (*length) = (int)str.length();
  char* ret = new char[*length + 1];
  strcpy(ret, str.c_str());
  return ret;
}

SpineData* SpineData::CreateFromFile(const char* path)
{
  SpineData* ret = new SpineData();
  
  char atlas_path[256] = {};
  strcpy(atlas_path, path);
  strcat(atlas_path, ".atlas");
  char skeleton_path[256] = {};
  strcpy(skeleton_path, path);
  strcat(skeleton_path, ".json");

  ret->atlas = spAtlas_createFromFile(atlas_path, 0);
  EngineAttachmentLoader* attachment_loader = new EngineAttachmentLoader(ret->atlas);
  spSkeletonJson* json = spSkeletonJson_createWithLoader(&attachment_loader->super);
  json->scale = 1.0f;
  spSkeletonData* skeleton_data = spSkeletonJson_readSkeletonDataFile(json, skeleton_path);
  spSkeletonJson_dispose(json);

  ret->skeleton_data = skeleton_data;

  return ret;
}

SpineData::SpineData()
  : skeleton_data(nullptr)
  , atlas(nullptr)
{}
