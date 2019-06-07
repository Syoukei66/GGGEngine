#include "TextureSelectScene.h"
#include <Converter/AssetConverter.h>
#include <Converter/AssetConverterContext.h>
#include <Engine/Component/Renderer/MeshRenderer.h>
#include <Engine/GameObject/GameObjectRenderState.h>

#include <Engine/Component/Camera/Camera2D.h>
#include <Engine/Component/Camera/Camera3D_LookAt.h>
#include <Engine/Component/Camera/Camera3D.h>

static const T_FLOAT PADDING = 16.0f;
static const T_UINT32 X_NUM = 2;
static const T_UINT32 Y_NUM = 5;
static const T_FLOAT IMAGE_SIZE = 100.0f;
static const T_FLOAT PAD_IMAGE_SIZE = IMAGE_SIZE + PADDING;
static const T_FLOAT SCREEN_WIDTH = X_NUM * (PAD_IMAGE_SIZE) + PADDING;
static const T_FLOAT SCREEN_HEIGHT = Y_NUM * (PAD_IMAGE_SIZE) + PADDING;

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
  const T_FLOAT offset_x = -SCREEN_WIDTH * 0.5f + IMAGE_SIZE * 0.5f + PADDING;
  const T_FLOAT offset_y = -SCREEN_HEIGHT * 0.5f + IMAGE_SIZE * 0.5f + PADDING;

  for (const auto& pair : this->entities_)
  {
    this->textures_[pair.second->GetMetaData()->GetURI().GetFileName()] = AssetManager::Load<rcTexture>(pair.second->GetMetaData()->GetUniqueID());
  }

  for (T_UINT32 y = 0, i = 0; y < Y_NUM + 1; ++y)
  {
    for (T_UINT32 x = 0; x < X_NUM; ++x, ++i)
    {
      if (i > this->entities_.size())
      {
        break;
      }
      const SharedRef<GameObject>& obj = GameObject::Create();
      const SharedRef<MeshRenderer>& renderer = obj->AddComponent<MeshRenderer>();
      const SharedRef<rcMaterial>& material = AssetManager::Load<rcMaterial>(DefaultUniqueID::MATERIAL_UNLIT)->Clone();
      renderer->SetMaterial(material);
      renderer->SetMesh(AssetManager::Load<rcMesh>(DefaultUniqueID::MESH_PLANE));
      obj->GetTransform()->SetScale(IMAGE_SIZE);
      obj->GetTransform()->SetPosition(offset_x + x * PAD_IMAGE_SIZE, -(offset_y + y * PAD_IMAGE_SIZE), 0.0f);
      this->AddChild(obj);
      this->images_.emplace_back(obj);
    }
  }

  this->scroll_ = 0.0f;
  this->scroll_max_ = PAD_IMAGE_SIZE * this->textures_.size() / X_NUM + PADDING + IMAGE_SIZE * 0.5f - SCREEN_HEIGHT;

  this->OnUpdateScreen();
}

void TextureSelectScene::OnHide(const ActivityContext& context)
{
  for (const auto& image : this->images_)
  {
    image->RemoveSelf();
  }
  this->images_.clear();
  this->textures_.clear();
}

void TextureSelectScene::Update(const ActivityContext& context)
{
  using namespace GameInput;
  // クリック処理
  if (context.Input(0)->GetButtonDown(MOUSE_CLICK_L))
  {
    const T_FLOAT mouse_x = context.Input(0)->GetAxis(MOUSE_SCREEN_X, 0.0f) * 0.5f * context.GetOption().window_size.width;
    const T_FLOAT mouse_y = -context.Input(0)->GetAxis(MOUSE_SCREEN_Y, 0.0f) * 0.5f * context.GetOption().window_size.height;
    const T_UINT32 texture_index_offset = std::floor((this->scroll_ / (Y_NUM * PAD_IMAGE_SIZE)) * Y_NUM) * X_NUM;
    const T_FLOAT r = IMAGE_SIZE * 0.5f;
    T_UINT32 i = 0;
    auto itr = this->textures_.begin();
    for (T_UINT32 j = 0; j < texture_index_offset; ++j, ++itr);
    for (const SharedRef<GameObject>& obj : this->images_)
    {
      if (itr == this->textures_.end())
      {
        break;
      }
      const T_FLOAT x = obj->GetTransform()->GetX();
      const T_FLOAT y = obj->GetTransform()->GetY();
      if (
        x - r <= mouse_x && mouse_x <= x + r &&
        y - r <= mouse_y && mouse_y <= y + r
        )
      {
        this->callback_(itr->second);
        break;
      }
      ++i;
      ++itr;
    }
  }

  // スクロール処理
  T_FLOAT old_scroll = this->scroll_;
  const T_FLOAT wheel_move = context.Input(0)->GetAxis(MOUSE_MOVE_Z, 0.0f);
  this->next_scroll_ -= wheel_move * 100.0f;
  this->next_scroll_ = std::min(this->scroll_max_, std::max(0.0f, this->next_scroll_));
  this->scroll_ = Mathf::Lerp(this->scroll_, this->next_scroll_, 0.1f);
  if (this->scroll_ != old_scroll)
  {
    this->OnUpdateScreen();
  }
}

void TextureSelectScene::Run(const SharedRef<rcTexture>& current_texture, const std::function<void(const SharedRef<rcTexture>& texture)>& callback)
{
  this->current_texture_ = current_texture;
  this->callback_ = callback;

  if (!this->activity_)
  {
    // アクティビティを作成する
    this->activity_ = GameActivity::Create();
    ActivityOption op = ActivityOption();
    op.activity_name = "テクスチャ選択";
    op.resize_window = false;
    op.sub_window = true;
    op.window_size = TVec2f(SCREEN_WIDTH, SCREEN_HEIGHT);
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

void TextureSelectScene::Reload(AssetViewerBehavior* behavior, AssetConverterContext* context)
{
  // 現在AssetConverterContextが管理しているテクスチャを全て取得する
  std::deque<SharedRef<AssetEntity>> entities = std::deque<SharedRef<AssetEntity>>();
  context->GetEntities(&entities, [&](const SharedRef<AssetEntity>& entity)
  {
    AssetConverter* converter = entity->GetConverter(context);
    return converter ? converter->IsTargetAsset<rcTexture>() : false;
  });
  for (const auto& pair : this->entities_)
  {
    behavior->RemoveEditorUseEntity(pair.second);
  }
  this->entities_.clear();
  for (const SharedRef<AssetEntity>& entity : entities)
  {
    const T_UINT32 unique_id = entity->GetMetaData()->GetUniqueID();
    entity->Load(context);
    this->entities_[unique_id] = entity;
    behavior->AddEditorUseEntity(entity);
  }

  this->textures_.clear();
  for (const auto& pair : this->entities_)
  {
    this->textures_[pair.second->GetMetaData()->GetURI().GetFileName()] = AssetManager::Load<rcTexture>(pair.second->GetMetaData()->GetUniqueID());
  }
  this->OnUpdateScreen();
}

void TextureSelectScene::OnUpdateScreen()
{
  const T_UINT32 texture_index_offset = std::floor((this->scroll_ / (Y_NUM * PAD_IMAGE_SIZE)) * Y_NUM) * X_NUM;
  T_UINT32 texture_index = 0;
  T_UINT32 image_index = 0;

  T_FLOAT offset_y = -SCREEN_HEIGHT * 0.5f + IMAGE_SIZE * 0.5f + PADDING;
  offset_y -= std::fmodf(this->scroll_, PAD_IMAGE_SIZE);

  for (const SharedRef<GameObject>& obj : this->images_)
  {
    obj->SetEnabled(false);
  }

  for (const auto& pair : this->textures_)
  {
    if (image_index >= this->images_.size())
    {
      break;
    }
    if (texture_index < texture_index_offset)
    {
      ++texture_index;
      continue;
    }
    const SharedRef<GameObject>& obj = this->images_[image_index];
    obj->SetEnabled(true);
    const SharedRef<rcMaterial>& mat = obj->GetComponent<Renderer>()->GetMaterial();
    mat->SetTexture("_MainTex", pair.second);
    mat->CommitChanges();
    obj->GetTransform()->SetY(-(offset_y + image_index / X_NUM * PAD_IMAGE_SIZE));
    ++texture_index;
    ++image_index;
  }
}
