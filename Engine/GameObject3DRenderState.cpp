#include "GameObject3DRenderState.h"
#include <algorithm>

#include "NativeMethod.h"
#include "GameObject3D.h"
#include "Camera3D.h"

GameObject3DRenderState::GameObject3DRenderState(Camera3D* camera)
  : camera_(camera)
  , post_draw_list_()
{
  this->mat_ = NativeMethod::Matrix().Matrix4x4_Create();
}

GameObject3DRenderState::~GameObject3DRenderState()
{
  NativeMethod::Matrix().Matrix4x4_Delete(this->mat_);
}

void GameObject3DRenderState::Init()
{
  GameObjectRenderState::Init();
}

void GameObject3DRenderState::AddZCheckOrder(GameObject3D* object)
{
  NativeMethod::Matrix().Matrix4x4_Assign(this->mat_, NativeMethod::Matrix().Matrix4x4Stack_GetTop(this->GetMatrixStack()));
  NativeMethod::Matrix().Matrix4x4_Multiply(this->mat_, this->camera_->GetViewMatrix());
  NativeMethod::Matrix().Matrix4x4_Multiply(this->mat_, this->camera_->GetProjectionMatrix());

  TVec4f pos = TVec4f(0.0f, 0.0f, 0.0f, 1.0f);
  NativeMethod::Matrix().Matrix4x4_Apply(this->mat_, &pos);

  PostDrawParam* param = new PostDrawParam();
  param->object = object;
  param->distance = pos.z / pos.w;
  this->post_draw_list_.push_back(param);
}

void GameObject3DRenderState::DrawZOrderedGameObject()
{
  this->camera_->GetDirection();
  std::sort(this->post_draw_list_.begin(), this->post_draw_list_.end(), [](PostDrawParam* a, PostDrawParam* b) {
    return a->distance > b->distance;
  });
  for (std::vector<PostDrawParam*>::iterator itr = this->post_draw_list_.begin(); itr != this->post_draw_list_.end();)
  {
    this->PushMatrix((*itr)->object->GetTransform()->GetWorldMatrix());
    (*itr)->object->ApplyBlendMode(this);
    (*itr)->object->NativeDraw(this);
    this->PopMatrix();
    delete (*itr);
    itr = this->post_draw_list_.erase(itr);
  }
}
