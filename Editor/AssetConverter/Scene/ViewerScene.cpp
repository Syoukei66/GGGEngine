#include "ViewerScene.h"
#include <Engine/Utils.h>
#include <Engine/Component/Camera/Camera3D_LookAt.h>
#include <Entity/AssetEntity.h>
#include <Entity/AssetMetaData.h>
#include "GameInput.h"


static const char* CAMERA_STATE_NAMES[ViewerScene::CAMERA_STATE_MAX] =
{
  "3D Scene",
  "3D AnchorCenter",
  "2D",
};

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(ViewerScene)
{
  this->move_speed_ = 0.5f;
  return Scene::Init();
}

// =================================================================
// Methods from Scene
// =================================================================
void ViewerScene::OnLoad()
{
  this->camera_3d_ = new Camera3D_LookAt();
  this->camera_3d_->GetTransform()->SetZ(-20.0f);
  this->AddCamera(this->camera_3d_);
}

void ViewerScene::OnUnload()
{
  this->RemoveCamera(this->camera_3d_);
  delete this->camera_3d_;
}

void ViewerScene::OnShow()
{
  this->current_behavior_->Start(this);
}

void ViewerScene::OnHide()
{
  this->current_behavior_->End();
}

void ViewerScene::Update()
{
  this->current_behavior_->Update();

  using namespace HalEngine;
  Transform3D* transform = this->camera_3d_->GetTransform();

  const T_FLOAT horizontal = Input(0)->GetAxis(GameInput::X_AXIS);
  const T_FLOAT vertical = Input(0)->GetAxis(GameInput::Y_AXIS);

  transform->MoveX(horizontal * 0.3f * this->move_speed_);
  transform->MoveZ(vertical * 0.3f * this->move_speed_);

  const bool mouse_click_L = Input(0)->GetButton(GameInput::MOUSE_CLICK_L);
  const bool mouse_click_C = Input(0)->GetButton(GameInput::MOUSE_CLICK_C);
  const bool mouse_click_R = Input(0)->GetButton(GameInput::MOUSE_CLICK_R);
  const T_FLOAT move_x = Input(0)->GetAxis(GameInput::MOUSE_MOVE_X, 0.01f);
  const T_FLOAT move_y = Input(0)->GetAxis(GameInput::MOUSE_MOVE_Y, 0.01f);
  const T_FLOAT move_z = Input(0)->GetAxis(GameInput::MOUSE_MOVE_Z, 0.01f);
  if (mouse_click_C)
  {
    transform->MoveX(-move_x * 0.66f * this->move_speed_);
    transform->MoveY(move_y * 0.66f * this->move_speed_);
  }
  if (mouse_click_R)
  {
    this->camera_move_x_ -= move_x * 0.05f;
    this->camera_move_y_ += move_y * 0.05f;
  }

  if (this->camera_state_ == CAMERA_2D)
  {
    transform->SetX(this->camera_move_x_);
    transform->SetY(this->camera_move_y_);
    transform->SetEularAngles(TVec3f::zero);
  }
  else if (this->camera_state_ == CAMERA_3D)
  {
    TVec3f pos = TVec3f::zero;
    const T_FLOAT rad = this->camera_move_x_ * Mathf::PI + Mathf::PI_1_2;
    pos.x = cosf(rad);
    pos.z = sinf(rad);
    pos += transform->GetPosition();

    transform->LookAt(pos, TVec3f::up);
    transform->RotateX(this->camera_move_y_ * Mathf::PI);
  }
  else if (this->camera_state_ == CAMERA_3D_ANCHOR_CENTER)
  {

  }

  if (fabs(move_z) != 0.0f)
  {
    transform->MoveZ(move_z * 1.1f * this->move_speed_);
  }

  ImGui::SetNextWindowPos(ImVec2(20.0f, 20.0f), ImGuiCond_Once);
  ImGui::SetNextWindowSize(ImVec2(200.0f, 200.0f), ImGuiCond_Once);

  ImGui::Begin(u8"メニュー");
  ImGui::SliderFloat(u8"カメラ移動速度", &this->move_speed_, 0.0f, 1.0f);

  ImGui::Combo(u8"カメラモード", &this->camera_state_, CAMERA_STATE_NAMES, CAMERA_STATE_MAX);

  if (ImGui::Button(u8"スタートメニューに戻る"))
  {
    Director::PopScene(false);
  }

  ImGui::End();
}

void ViewerScene::Run(const SharedRef<IViewerBehavior>& behavior)
{
  this->current_behavior_ = behavior;
  Director::PushScene(SharedRef<ViewerScene>(this), false);
}
