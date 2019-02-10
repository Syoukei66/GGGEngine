#include "TextureSelectScene.h"
#include <Converter/AssetConverter.h>
#include <Converter/AssetConverterContext.h>
#include <Entity/AssetEntity.h>
#include <Engine/Component/Renderer/MeshRenderer.h>
#include <Engine/GameObject/GameObjectRenderState.h>

#include <Engine/Component/Camera/Camera2D.h>
#include <Engine/Component/Camera/Camera3D_LookAt.h>
#include <Engine/Component/Camera/Camera3D.h>

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(TextureSelectScene)
{
  return Scene::Init();
}

// =================================================================
// Methods from Scene
// =================================================================
void TextureSelectScene::OnLoad(const ActivityContext& context)
{
  this->camera_ = GameObject::Create();
  const SharedRef<Camera>& camera = this->camera_->AddComponent<Camera2D>();
  camera->SetViewportClear(true);
  camera->SetBgColor(TColor::RED);
  camera->SetViewportWidth(context.GetOption().window_size.width);
  camera->SetViewportHeight(context.GetOption().window_size.height);
  this->AddCamera(camera);
  this->camera_->GetTransform()->SetZ(-10.0f);
  //this->AddChild(this->camera_);
}

void TextureSelectScene::OnUnload(const ActivityContext& context)
{
  this->ClearChildren();
  this->camera_ = nullptr;
}

void TextureSelectScene::OnShow(const ActivityContext& context)
{
  for (const auto& pair : this->textures_)
  {
    const SharedRef<GameObject>& obj = GameObject::Create();
    const SharedRef<MeshRenderer>& renderer = obj->AddComponent<MeshRenderer>();
    const SharedRef<rcMaterial>& material = AssetManager::Load<rcMaterial>(DefaultUniqueID::MATERIAL_UNLIT);
    material->SetTexture(Shader::MAIN_TEXTURE_NAME, pair.second);
    renderer->SetMaterial(material);
    renderer->SetMesh(AssetManager::Load<rcMesh>(DefaultUniqueID::MESH_PLANE));
    obj->GetTransform()->SetScale(128.0f);
    this->AddChild(obj);
  }
}

void TextureSelectScene::OnHide(const ActivityContext& context)
{
}

void TextureSelectScene::Update(const ActivityContext& context)
{
}

void TextureSelectScene::Run(const SharedRef<rcTexture>& current_texture, AssetConverterContext* context, const std::function<void(const SharedRef<rcTexture>& texture)>& callback)
{
  this->current_texture_ = current_texture;
  this->callback_ = callback;

  // 現在AssetConverterContextが管理しているテクスチャを全て取得する
  std::deque<SharedRef<AssetEntity>> entities = std::deque<SharedRef<AssetEntity>>();
  context->GetEntities(&entities, [&](const SharedRef<AssetEntity>& entity)
  {
    AssetConverter* converter = entity->GetConverter(context);
    return converter ? converter->IsTargetAsset<rcTexture>() : false;
  });
  this->textures_.clear();
  for (const SharedRef<AssetEntity>& entity : entities)
  {
    const T_UINT32 unique_id = entity->GetMetaData()->GetUniqueID();
    entity->Load(context);
    this->textures_[unique_id] = AssetManager::Load<rcTexture>(unique_id);
  }

  if (!this->activity_)
  {
    // アクティビティを作成する
    this->activity_ = GameActivity::Create();
    ActivityOption op = ActivityOption();
    op.activity_name = "テクスチャ選択";
    op.resize_window = false;
    op.sub_window = true;
    op.window_size = TVec2f(300.0f, 600.0f);
    Application::StartActivity(this->activity_, op);
    this->activity_->ChangeScene(SharedRef<Scene>(this));
  }
  this->activity_->GetContext().Show();
}

void TextureSelectScene::End()
{
  if (this->activity_)
  {
    this->activity_->GetContext().Hide();
    this->activity_ = nullptr;
  }
}
