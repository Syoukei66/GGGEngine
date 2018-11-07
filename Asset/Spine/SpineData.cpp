#include "SpineData.h"
#include <spine/spine.h>
#include <spine/extension.h>
#include <Core/Util/FileUtil.h>

#include "EngineAttachmentLoader.h"

// =================================================================
// Factory Method
// =================================================================
void _spAtlasPage_createTexture(spAtlasPage* self, const char* path)
{
  //TextureAsset* texture_asset = AssetManager::GetInstance().GetAsset<TextureAsset>(path);
  //rcTexture* texture = texture_asset->CreateFromFile();
  //self->rendererObject = (void*)texture;
  //self->width = texture->GetWidth();
  //self->height = texture->GetHeight();
}

void _spAtlasPage_disposeTexture(spAtlasPage* self)
{
  GG_ASSERT(false, "‚Ü‚¾‚Å‚«‚Ä‚Ü‚¹‚ñI");
  ((rcTexture*)self->rendererObject);
}

char* _spUtil_readFile(const char* path, int* length)
{
  std::string str = FileUtil::TextFile_Read(path);
  (*length) = (int)str.length();
  char* ret = new char[*length + 1];
  strcpy(ret, str.c_str());
  return ret;
}

UniqueRef<rcSpineData> rcSpineData::CreateFromFile(const char* path)
{
  char atlas_path[256] = {};
  strcpy(atlas_path, path);
  strcat(atlas_path, ".atlas");
  char skeleton_path[256] = {};
  strcpy(skeleton_path, path);
  strcat(skeleton_path, ".json");

  spAtlas* atlas = spAtlas_createFromFile(atlas_path, 0);
  EngineAttachmentLoader* attachment_loader = new EngineAttachmentLoader(atlas);
  spSkeletonJson* json = spSkeletonJson_createWithLoader(&attachment_loader->super);
  json->scale = 1.0f;
  spSkeletonData* skeleton_data = spSkeletonJson_readSkeletonDataFile(json, skeleton_path);
  spSkeletonJson_dispose(json);

  return Create(skeleton_data, atlas);
}

UniqueRef<rcSpineData> rcSpineData::Create(spSkeletonData* skeleton_data, spAtlas* atlas)
{
  return UniqueRef<rcSpineData>(new rcSpineData(skeleton_data, atlas));
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcSpineData::rcSpineData(spSkeletonData* skeleton_data, spAtlas* atlas)
  : skeleton_data_(skeleton_data)
  , atlas_(atlas)
{}
