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

  NATIVE_ASSERT(import_status, "FBX�t�@�C���̓ǂݍ��݂Ɏ��s���܂���");

  FbxScene* ret = FbxScene::Create(manager, "");
  importer->Import(ret);

  importer->Destroy();

  return new FbxData(ret);
}

// =================================================================
// Constructor / Destructor
// =================================================================
FbxData::FbxData(FbxScene* scene)
{
  FbxNode* node = scene->GetRootNode();
  const T_INT16 node_count = node->GetChildCount();
  for (T_INT16 i = 0; i < node_count; ++i)
  {
    FbxMesh* mesh = node->GetMesh();
  }
}

FbxData::~FbxData()
{
}
