#include "Camera3D.h"
#include "MathConstants.h"
#include "Scene.h"
#include "Collision3D.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Camera3D::Camera3D(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max)
  : Camera(x, y, width, height, z_min, z_max)
  , billboarding_matrix_()
  , projection_matrix_()
  , fov_(3.0f)
  , z_near_(0.3f)
  , z_far_(1000.0f)
  , projection_dirty_(true)
{
  this->entity_ = new GameObject3D();
}

Camera3D::Camera3D()
  : Camera()
  , billboarding_matrix_()
  , projection_matrix_()
  , fov_(3.0f)
  , z_near_(0.3f)
  , z_far_(1000.0f)
  , projection_dirty_(true)
{
  this->entity_ = new GameObject3D();
}

Camera3D::~Camera3D()
{
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
bool Camera3D::FrustumCulling(const TVec3f& positive, const TVec3f& negative, T_INT8* first_index) const
{
  return Collision3D::Frustum_AABB(this->render_state_->GetViewProjMatrix(), positive, negative, first_index);
}

const Matrix4x4& Camera3D::GetViewMatrix() const
{
  return Matrix4x4::identity;
}

const Matrix4x4& Camera3D::GetProjectionMatrix() const
{
  const_cast<Camera3D*>(this)->CheckProjectionDirty();
  return this->projection_matrix_;
}

void Camera3D::SetupCamera()
{
  Camera::SetupCamera();
  this->billboarding_matrix_ = this->GetViewMatrix().Inverse();

  this->billboarding_matrix_._41 = 0.0f;
  this->billboarding_matrix_._42 = 0.0f;
  this->billboarding_matrix_._43 = 0.0f;
}

void Camera3D::OnViewportChanged()
{
  this->OnProjectionChanged();
}

void Camera3D::OnDrawScene(Scene* scene)
{
  this->render_state_->Init();
  scene->Draw3DLayers(this->render_state_);
  this->render_state_->Draw();
}

// =================================================================
// Method
// =================================================================
void Camera3D::CheckProjectionDirty()
{
  if (!this->projection_dirty_)
  {
    return;
  }
  this->projection_matrix_ = Matrix4x4::Perspective(
    MathConstants::PI / this->fov_,
    this->GetViewportWidth() / this->GetViewportHeight(),
    this->z_near_,
    this->z_far_
  );
  this->projection_dirty_ = false;
}

TVec3f Camera3D::CalcRayVector(const TVec2f& screen_position)
{
  Matrix4x4 ret;
  ret.Translation(screen_position);
  ret = this->GetProjectionMatrix() * ret;
  ret = this->GetViewMatrix() * ret;
  return ret.GetPosition3d();
}

// =================================================================
// setter/getter
// =================================================================
const TVec3f Camera3D::Get2dPositionScale(const GameObject3D* obj) const
{
  Matrix4x4 ret;
  ret = obj->GetTransform()->GetWorldMatrix();
  ret *= this->GetViewMatrix();
  ret *= this->GetProjectionMatrix();
  const TVec4f pos = ret.GetPosition4d();
  return TVec3f(pos.x / pos.w, pos.y / pos.w, pos.z / fabs(pos.w));
}

const TVec3f Camera3D::Get2dPosition(const GameObject3D* obj) const
{
  TVec3f ret = this->Get2dPositionScale(obj);
  ret.x *= this->GetViewportWidth() * 0.5f;
  ret.y *= this->GetViewportHeight() * 0.5f;
  return ret;
}

void Camera3D::SetFov(T_FLOAT fov)
{
  if (this->fov_ == fov)
  {
    return;
  }
  this->fov_ = fov;
  this->OnProjectionChanged();
}

void Camera3D::SetZNear(T_FLOAT z_near)
{
  if (this->z_near_ == z_near)
  {
    return;
  }
  this->z_near_ = z_near;
  this->OnProjectionChanged();
}

void Camera3D::SetZFar(T_FLOAT z_far)
{
  if (this->z_far_ == z_far)
  {
    return;
  }
  this->z_far_ = z_far;
  this->OnProjectionChanged();
}
