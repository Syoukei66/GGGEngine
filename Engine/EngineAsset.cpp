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
Cont_ UNLIT = AssetManager::GetInstance().RegisterEngineAsset<T_>(Util::Hash::GetHash("Asset/shader/default/Unlit.cso"), "cso");
Cont_ LAMBERT = AssetManager::GetInstance().RegisterEngineAsset<T_>(Util::Hash::GetHash("Asset/shader/default/Lambert.cso"), "cso");
Cont_ PHONG = AssetManager::GetInstance().RegisterEngineAsset<T_>(Util::Hash::GetHash("Asset/shader/default/Phong.cso"), "cso");
Cont_ SPRITE = AssetManager::GetInstance().RegisterEngineAsset<T_>(Util::Hash::GetHash("Asset/shader/default/Sprite.cso"), "cso");
Cont_ WHITE = AssetManager::GetInstance().RegisterEngineAsset<T_>(Util::Hash::GetHash("Asset/shader/default/White.cso"), "cso");
} // namespace Shader

namespace Material
{
class Material UNLIT(rcShader::UNLIT->GetContents(), true);
class Material LAMBERT(rcShader::LAMBERT->GetContents(), true);
class Material PHONG(rcShader::PHONG->GetContents(), true);
class Material SPRITE(rcShader::SPRITE->GetContents(), true);
class Material WHITE(rcShader::WHITE->GetContents(), true);
} // namespace Material

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