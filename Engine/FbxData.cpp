#include "FbxData.h"
#include "Director.h"

// =================================================================
// Factory Method
// =================================================================
FbxData* FbxData::Create(const char* path)
{
  FbxManager* manager = Director::GetInstance()->GetFbxManager();
  FbxIOSettings* ios = FbxIOSettings::Create(manager, IOSROOT);
  manager->SetIOSettings(ios);

  FbxImporter* importer = FbxImporter::Create(manager, "");

  bool import_status = importer->Initialize(path, -1, manager->GetIOSettings());

  NATIVE_ASSERT(import_status, "FBXƒtƒ@ƒCƒ‹‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½");

  FbxScene* ret = FbxScene::Create(manager, "");

  importer->Import(ret);

  FbxGeometryConverter converter = FbxGeometryConverter(manager);
  converter.Triangulate(ret, true);
  converter.RemoveBadPolygonsFromMeshes(ret);
  converter.RecenterSceneToWorldCenter(ret, 0.01f);
  bool result = converter.SplitMeshesPerMaterial(ret, true);

  importer->Destroy();
  return new FbxData(ret);
}

// =================================================================
// Constructor / Destructor
// =================================================================
FbxData::FbxData(FbxScene* scene)
  : scene_(scene)
{
  this->root_data_ = new FbxNodeData(scene->GetRootNode());
}

FbxData::~FbxData()
{
  delete this->root_data_;
}
