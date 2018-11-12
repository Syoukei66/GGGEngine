#include "ViewerScene.h"
#include <Engine/Utils.h>
#include <Engine/Component/Camera/Camera3D_LookAt.h>

// =================================================================
// Methods from Scene
// =================================================================
void ViewerScene::OnLoad()
{
  this->camera_3d_ = new Camera3D_LookAt();
  this->camera_3d_->GetTransform()->SetY(5.0f);
  this->camera_3d_->GetTransform()->SetZ(-20.0f);
  this->camera_3d_->GetTransform()->RotateX(Mathf::PI_1_32);
  this->AddCamera(this->camera_3d_);

  this->behavior_->Start(this);
}

void ViewerScene::OnUnload()
{
  this->behavior_->End();

  delete this->camera_3d_;
}

void ViewerScene::OnShow(ISceneShowListener* listener)
{
}

void ViewerScene::OnHide(ISceneHideListener* listener)
{
}

void ViewerScene::Update()
{
  this->behavior_->Update();

  using namespace HalEngine;
  Transform3D* transform = this->camera_3d_->GetTransform();

  const T_FLOAT horizontal = Input(0)->GetAxis(GameInput::X_AXIS);
  const T_FLOAT vertical = Input(0)->GetAxis(GameInput::Y_AXIS);
  const T_FLOAT move_speed = 1.0f;

  transform->MoveX(horizontal * 0.3f * move_speed);
  transform->MoveZ(vertical * 0.3f * move_speed);

  const bool mouse_click_L = Input(0)->GetButton(GameInput::MOUSE_CLICK_L);
  const bool mouse_click_C = Input(0)->GetButton(GameInput::MOUSE_CLICK_C);
  const bool mouse_click_R = Input(0)->GetButton(GameInput::MOUSE_CLICK_R);
  const T_FLOAT move_x = Input(0)->GetAxis(GameInput::MOUSE_MOVE_X, 0.01f);
  const T_FLOAT move_y = Input(0)->GetAxis(GameInput::MOUSE_MOVE_Y, 0.01f);
  const T_FLOAT move_z = Input(0)->GetAxis(GameInput::MOUSE_MOVE_Z, 0.01f);
  if (mouse_click_C)
  {
    transform->MoveX(-move_x * 0.66f * move_speed);
    transform->MoveY(move_y * 0.66f * move_speed);
  }
  if (mouse_click_R)
  {
    this->look_at_rot_x_ -= move_x * 0.05f;
    this->look_at_rot_y_ += move_y * 0.05f;

    TVec3f pos = TVec3f::zero;
    const T_FLOAT rad = this->look_at_rot_x_ * Mathf::PI + Mathf::PI_1_2;
    pos.x = cosf(rad);
    pos.z = sinf(rad);
    pos += transform->GetPosition();

    transform->LookAt(pos, TVec3f::up);
    transform->RotateX(this->look_at_rot_y_ * Mathf::PI);
  }
  if (fabs(move_z) != 0.0f)
  {
    transform->MoveZ(move_z * 1.1f * move_speed);
  }
}

void ViewerScene::Run(IViewerBehavior* behavior)
{
  this->behavior_ = behavior;
  Director::ChangeScene(SharedRef<ViewerScene>(this));
}
