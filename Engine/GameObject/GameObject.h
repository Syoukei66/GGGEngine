#pragma once

#include <Engine/Component/GameComponent.h>
#include <Engine/Component/Renderer/Renderer.h>
#include <Engine/GameObject/Transform/Transform.h>

class GameObjectRenderState;

class GameObject
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameObject();
  virtual ~GameObject();

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual void Init();

  // =================================================================
  // Events
  // =================================================================
public:
  //TODO:描画処理は描画スレッドに描画コマンドを送信する事で実現するように変更(Rendererが行う)
  virtual void ManagedDraw(GameObjectRenderState* state) = 0;

  //TODO:アップデート処理はタスクスレッドにタスクを渡す事で実現するように変更する
  virtual void ManagedPreUpdate() = 0;
  virtual void ManagedUpdate() = 0;
  virtual void ManagedPostUpdate() = 0;

protected:
  void Draw(GameObjectRenderState* state);

  virtual void PreUpdate() {}
  virtual void Update() {}
  virtual void PostUpdate() {}

  // =================================================================
  // Events
  // =================================================================
public:
  virtual void FireOnPositionChanged(GameObject* root) = 0;
  virtual void FireOnScaleChanged(GameObject* root) = 0;
  virtual void FireOnRotationChanged(GameObject* root) = 0;

protected:
  virtual void OnPositionChanged(GameObject* root) {}
  virtual void OnScaleChanged(GameObject* root) {}
  virtual void OnRotationChanged(GameObject* root) {}
  
  // =================================================================
  // Hierarchy 
  // =================================================================
public:

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE void SetVisible(bool visible)
  {
    this->visible_ = visible;
  }
  GG_INLINE bool IsVisible() const
  {
    return this->visible_;
  }

  GG_INLINE void SetRenderer(Renderer* renderer)
  {
    this->renderer_ = renderer;
  }
  GG_INLINE Renderer* GetRenderer() const
  {
    return this->renderer_;
  }

  // =================================================================
  // delegate to Transform
  // =================================================================
  GG_INLINE const Matrix4x4& GetMatrix() const
  {
    return this->transform_->GetMatrix();
  }

  GG_INLINE const Matrix4x4& GetTranslateMatrix() const
  {
    return this->transform_->GetTranslateMatrix();
  }

  GG_INLINE const Matrix4x4& GetRotationMatrix() const
  {
    return this->transform_->GetRotationMatrix();
  }

  GG_INLINE const Matrix4x4& GetScaleMatrix() const
  {
    return this->transform_->GetScaleMatrix();
  }

  GG_INLINE const Matrix4x4& GetWorldMatrix() const
  {
    return this->transform_->GetWorldMatrix();
  }

  // =================================================================
  // delegate to Renderer
  // =================================================================
  GG_INLINE void SetLayerId(T_UINT8 layer_id)
  {
    this->renderer_->SetLayerId(layer_id);
  }
  GG_INLINE T_UINT8 GetLayerId() const
  {
    this->renderer_->GetLayerId();
  }
  GG_INLINE void SetMaterial(const SharedRef<rcMaterial>& material, T_UINT16 index = 0)
  {
    this->renderer_->SetMaterial(material, index);
  }
  GG_INLINE SharedRef<const rcMaterial> GetMaterial(T_UINT16 index = 0) const
  {
    return this->renderer_->GetMaterial(index);
  }
  GG_INLINE SharedRef<rcMaterial> GetMaterial(T_UINT16 index = 0)
  {
    return this->renderer_->GetMaterial(index);
  }
  GG_INLINE T_UINT16 GetMaterialCount()
  {
    return this->renderer_->GetMaterialCount();
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  Transform* transform_;

private:
	bool visible_;
  Renderer* renderer_;
};
