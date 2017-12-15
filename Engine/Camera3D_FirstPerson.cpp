//#include "Camera3D_FirstPerson.h"
//#include "MathConstants.h"
//
//// =================================================================
//// Constructor / Destructor
//// =================================================================
//Camera3D_FirstPerson::Camera3D_FirstPerson(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max)
//  : Camera3D(x, y, width, height, z_min, z_max)
//  , target_(nullptr)
//  , look_at_pos_()
//{
//  this->entity_ = new GameObject3D();
//  this->matrix_ = NativeMethod::Matrix().Matrix4x4_Create();
//  this->inv_ = NativeMethod::Matrix().Matrix4x4_Create();
//  
//}
//
//Camera3D_FirstPerson::Camera3D_FirstPerson()
//  : Camera3D()
//  , target_(nullptr)
//  , look_at_pos_()
//{
//  this->entity_ = new GameObject3D();
//  this->matrix_ = NativeMethod::Matrix().Matrix4x4_Create();
//  this->inv_ = NativeMethod::Matrix().Matrix4x4_Create();
//}
//
//Camera3D_FirstPerson::~Camera3D_FirstPerson()
//{
//  delete this->entity_;
//  NativeMethod::Matrix().Matrix4x4_Delete(this->matrix_);
//  NativeMethod::Matrix().Matrix4x4_Delete(this->inv_);
//}
//
//// =================================================================
//// Methods for/from SuperClass/Interfaces
//// =================================================================
//LP_MATRIX_4x4 Camera3D_FirstPerson::GetViewMatrix()
//{
//  GameObject3D* player = this->entity_->GetParent();
//  NativeMethod::Matrix().Matrix4x4_Init(this->matrix_);
//  if (this->target_)
//  {
//    NativeMethod::Matrix().Matrix4x4_LookAtLH(
//      this->matrix_,
//      this->GetTransform()->GetWorldPosition(),
//      player->GetTransform()->GetWorldPosition(),
//      TVec3f(0.0f, 1.0f, 0.0f)
//    );
//  }
//  else
//  {
//    NativeMethod::Matrix().Matrix4x4_LookAtLH(
//      this->matrix_,
//      this->GetTransform()->GetWorldPosition(),
//      player->GetTransform()->GetWorldPosition(),
//      TVec3f(0.0f, 1.0f, 0.0f)
//    );
//  }
//  if (player)
//  {
//    NativeMethod::Matrix().Matrix4x4_Inverse(this->inv_, player->GetTransform()->GetMatrix());
//    NativeMethod::Matrix().Matrix4x4_Multiply(this->matrix_, this->inv_);
//    GameObject3D* p = player->GetParent();
//    while (p)
//    {
//      NativeMethod::Matrix().Matrix4x4_Multiply(this->matrix_, p->GetTransform()->GetMatrix());
//      p = p->GetParent();
//    }
//  }
//  NativeMethod::Matrix().Matrix4x4_Inverse(this->inv_, this->entity_->GetTransform()->GetMatrix());
//  NativeMethod::Matrix().Matrix4x4_Multiply(this->matrix_, this->inv_);
//
//  return this->matrix_;
//}
//
//void Camera3D_FirstPerson::SetPlayer(GameObject3D* player)
//{
//  if (this->entity_->HasParent())
//  {
//    this->entity_->RemoveSelf();
//  }
//  player->AddChild(this->entity_);
//}
//
