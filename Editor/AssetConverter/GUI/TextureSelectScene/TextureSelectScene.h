#pragma once

#include <Engine/Scene/Scene.h>

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
  // Methods from Scene
  // =================================================================
public:
  void Run(const SharedRef<rcTexture>& current_texture, AssetConverterContext* context, const std::function<void(const SharedRef<rcTexture>& texture)>& callback);

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::function<void(const SharedRef<rcTexture>& texture)> callback_;
  SharedRef<rcTexture> current_texture_;

  SharedRef<GameObject> camera_;
  std::map<T_UINT32, SharedRef<GameObject>> images_;
  std::unordered_map<T_UINT32, SharedRef<rcTexture>> textures_;

};
