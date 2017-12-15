#define _CRT_SECURE_NO_WARNINGS
#include "SpineData.h"

#include "Texture.h"
#include "EngineAttachmentLoader.h"
#include "NativeMethod.h"
#include "HalEngine.h"
#include "Director.h"

#include <spine/extension.h>

void _spAtlasPage_createTexture(spAtlasPage* self, const char* path)
{
  const ITexture* texture = HalEngine::Resource::GetTexture(path);
  self->rendererObject = texture->GetNativeTexture();
  self->width = texture->GetSize().width;
  self->height = texture->GetSize().height;
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

  char spine_path[256] = {};
  Director::GetInstance()->GetEngineOption()->asset_path.GetSpinePath(path, spine_path);
  char atlas_path[256] = {};
  strcpy(atlas_path, spine_path);
  strcat(atlas_path, ".atlas");
  char skeleton_path[256] = {};
  strcpy(skeleton_path, spine_path);
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
