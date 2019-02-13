#pragma once

#include <Engine/Scene/Scene.h>
#include <Engine/GameActivity.h>
#include <Entity/AssetEntity.h>

class AssetViewerBehavior;
class AssetConverterContext;

class TextureSelectScene : public Scene
{
  // =================================================================
  // GGG Statment
  // =================================================================
public:
  GG_OBJECT(TextureSelectScene);
  GG_CREATE_FUNC(TextureSelectScene);

  // =================================================================
  // Methods from Scene
  // =================================================================
public:
  virtual void OnLoad(const ActivityContext& context) override;
  virtual void OnUnload(const ActivityContext& context) override;
  virtual void OnShow(const ActivityContext& context) override;
  virtual void OnHide(const ActivityContext& context) override;
  virtual void Update(const ActivityContext& context) override;

  // =================================================================
  // Methods
  // =================================================================
public:
  void Run(const SharedRef<rcTexture>& current_texture, const std::function<void(const SharedRef<rcTexture>& texture)>& callback);
  void End();
  void Reload(AssetViewerBehavior* behavior, AssetConverterContext* context);

private:
  void OnUpdateScreen();

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::function<void(const SharedRef<rcTexture>& texture)> callback_;
  SharedRef<rcTexture> current_texture_;

  SharedRef<GameActivity> activity_;

  SharedRef<GameObject> camera_;
  std::vector<SharedRef<GameObject>> images_;
  std::map<std::string, SharedRef<rcTexture>> textures_;
  std::unordered_map<T_UINT32, SharedRef<AssetEntity>> entities_;
  T_FLOAT scroll_;
  T_FLOAT next_scroll_;
  T_FLOAT scroll_max_;

};
