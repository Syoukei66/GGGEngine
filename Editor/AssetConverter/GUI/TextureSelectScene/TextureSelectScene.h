#pragma once

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
  virtual void OnLoad() override;
  virtual void OnUnload() override;
  virtual void OnShow() override;
  virtual void OnHide() override;
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

  SharedRef<GameObject2D> camera_;
  std::map<T_UINT32, SharedRef<GameObject3D>> images_;
  std::unordered_map<T_UINT32, SharedRef<rcTexture>> textures_;

};
