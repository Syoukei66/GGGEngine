#include "EngineAsset.h"
#include "../Asset/AssetManager.h"
#include "../Core/GraphicsConstants.h"
#include "../Core/HashUtil.h"
#include "MeshBuilder_Cube.h"
#include "MeshBuilder_Plane.h"
#include "MeshBuilder_Sprite.h"

namespace EngineAsset
{

namespace rcShader
{
Cont_ UNLIT = OldAssetManager::GetInstance().RegisterEngineAsset<T_>(Util::Hash::GetHash("Asset/shader/default/Unlit.cso"), "cso");
Cont_ LAMBERT = OldAssetManager::GetInstance().RegisterEngineAsset<T_>(Util::Hash::GetHash("Asset/shader/default/Lambert.cso"), "cso");
Cont_ PHONG = OldAssetManager::GetInstance().RegisterEngineAsset<T_>(Util::Hash::GetHash("Asset/shader/default/Phong.cso"), "cso");
Cont_ SPRITE = OldAssetManager::GetInstance().RegisterEngineAsset<T_>(Util::Hash::GetHash("Asset/shader/default/Sprite.cso"), "cso");
Cont_ WHITE = OldAssetManager::GetInstance().RegisterEngineAsset<T_>(Util::Hash::GetHash("Asset/shader/default/White.cso"), "cso");
} // namespace Shader

namespace rcMaterial
{
class rcMaterial UNLIT(rcShader::UNLIT->GetContents(), true);
class rcMaterial LAMBERT(rcShader::LAMBERT->GetContents(), true);
class rcMaterial PHONG(rcShader::PHONG->GetContents(), true);
class rcMaterial SPRITE(rcShader::SPRITE->GetContents(), true);
class rcMaterial WHITE(rcShader::WHITE->GetContents(), true);
} // namespace rcMaterial

namespace rcCustomMesh
{
class MeshResource QUAD(new MeshBuilder_Sprite());
class MeshResource PLANE(new MeshBuilder_Plane(Graphics::V_FORMAT_PNUTC, 1.0f, 1.0f, 1, 1));
class MeshResource CUBE(new MeshBuilder_Cube(Graphics::V_FORMAT_PNUTC, 1.0f, 1.0f, 1.0f, 1, 1, 1));
} // namespace Mesh

void Load()
{
  rcCustomMesh::QUAD.Load();
  rcCustomMesh::PLANE.Load();
  rcCustomMesh::CUBE.Load();
}

void Unload()
{
}

} // namespace EngineAsset