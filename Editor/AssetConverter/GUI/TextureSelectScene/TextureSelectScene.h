#pragma once

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
  void Run(const SharedRef<rcTexture>& current_texture, const std::function<void(const SharedRef<rcTexture>& texture)>& callback);

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::function<void(const SharedRef<rcTexture>& texture)> callback_;
  SharedRef<rcTexture> current_texture_;

  SharedRef<GameObject2D> camera_;
  std::vector<SharedRef<GameObject3D>> images_;

};
