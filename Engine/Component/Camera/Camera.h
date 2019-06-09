#pragma once

#include <Core/Application/Platform/API/_Resource/RenderTexture/RenderTexture.h>
#include <Engine/Component/GameComponent.h>

class Scene;
class GameObjectRenderState;

class Camera : public GameComponent
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_COMPONENT(Camera);
  GG_INIT_FUNC_1(Camera, GameObject*, obj);
  GG_DESTRUCT_FUNC(Camera);

  // =================================================================
  // Methods
  // =================================================================
public:
  void DrawScene(const ActivityContext& context, Scene* scene);

  virtual bool FrustumCulling(const TVec3f& positive, const TVec3f& negative, T_INT8* first_index = nullptr) const = 0;

protected:
  virtual void UpdateViewMatrix() = 0;
  virtual void UpdateProjectionMatrix() = 0;

  GG_INLINE void OnViewportChanged()
  {
    this->projection_dirty_ = true;
  }

  GG_INLINE void OnProjectionChanged()
  {
    this->projection_dirty_ = true;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  const Matrix4x4& GetViewMatrix() const;
  const Matrix4x4& GetProjectionMatrix() const;

  GG_INLINE Transform* GetTransform()
  {
    return this->GetObject()->GetTransform();
  }
  GG_INLINE const Transform* GetTransform() const
  {
    return this->GetObject()->GetTransform();
  }

  //ビューポート領域をクリアしてから描画するかのフラグ
  GG_INLINE void SetViewportClear(bool clear)
  {
    this->viewport_clear_ = clear;
  }
  GG_INLINE bool IsViewportClear() const
  {
    return this->viewport_clear_;
  }

  //GG_INLINE void SetTargetTexture(const SharedRef<rcRenderTexture>& texture)
  //{
  //  this->target_texture_ = texture;
  //}

  //GG_INLINE SharedRef<rcRenderTexture> GetTargetTexture() const
  //{
  //  return this->target_texture_;
  //}

  void SetViewportPosition(const TVec2f& position);
  void SetViewportPosition(T_FLOAT x, T_FLOAT y);
  GG_INLINE const TVec2f& GetViewportPosition() const
  {
    return this->position_;
  }

  void SetViewportX(T_FLOAT x);
  GG_INLINE T_FLOAT GetViewportX() const
  {
    return this->position_.x;
  }

  void SetViewportY(T_FLOAT y);
  GG_INLINE T_FLOAT GetViewportY() const
  {
    return this->position_.y;
  } 

  void SetViewportSize(const TVec2f& size);
  void SetViewportSize(T_FLOAT width, T_FLOAT height);
  GG_INLINE const TVec2f& GetViewportSize() const
  {
    return this->size_;
  }

  void SetViewportWidth(T_FLOAT width);
  GG_INLINE T_FLOAT GetViewportWidth() const
  {
    return this->size_.x;
  }

  void SetViewportHeight(T_FLOAT height);
  GG_INLINE T_FLOAT GetViewportHeight() const
  {
    return this->size_.y;
  }

  void SetViewportZRange(T_FLOAT z_min, T_FLOAT z_max);
  void SetViewportZMin(T_FLOAT z_min);
  GG_INLINE T_FLOAT GetViewportZMin() const
  {
    return this->z_min_;
  }

  void SetViewportZMax(T_FLOAT z_max);
  GG_INLINE T_FLOAT GetViewportZMax() const
  {
    return this->z_max_;
  }

  void SetBgColor(const TColor& color)
  {
    this->bg_color_ = color;
  }
  GG_INLINE const TColor& GetBgColor() const
  {
    return this->bg_color_;
  }

  GG_INLINE const TVec3f& GetDirection() const
  {
    return this->direction_;
  }

  GG_INLINE GameObjectRenderState* GetRenderState()
  {
    return this->render_state_;
  }
  GG_INLINE const GameObjectRenderState* GetRenderState() const
  {
    return this->render_state_;
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  GameObjectRenderState* render_state_;
  TVec3f direction_;

  Matrix4x4 projection_matrix_;
  Matrix4x4 view_matrix_;

private:
  //SharedRef<rcRenderTexture> target_texture_;
  bool viewport_clear_;
  TVec2f position_;
  TVec2f size_;
  T_FLOAT z_min_, z_max_;
  TColor bg_color_;

  bool projection_dirty_;

};
