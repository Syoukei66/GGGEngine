//#include "Quaternion.h"
//#include <math.h>
//
//#include "MathConstants.h"
//#include "NativeMethod.h"
//
//static const TVec3f X_AXIS = TVec3f(1.0f, 0.0f, 0.0f);
//static const TVec3f Y_AXIS = TVec3f(0.0f, 1.0f, 0.0f);
//static const TVec3f Z_AXIS = TVec3f(0.0f, 0.0f, 1.0f);
//
//// =================================================================
//// Static Member
//// =================================================================
//const Quaternion Quaternion::Identity = Quaternion();
//
//// =================================================================
//// Constructor / Destructor
//// =================================================================
//Quaternion::Quaternion()
//  : v_(0.0f, 0.0f, 0.0f)
//  , w_(1.0f)
//  , eular_angles_(0.0f, 0.0f, 0.0f)
//  , is_normalized_(true)
//{
//}
//
//Quaternion::~Quaternion()
//{
//}
//
//// =================================================================
//// Method
//// =================================================================
//void Quaternion::RotationXAxis(T_FLOAT rad)
//{
//  this->q(X_AXIS, rad);
//}
//
//void Quaternion::RotationYAxis(T_FLOAT rad)
//{
//  this->q(Y_AXIS, rad);
//}
//
//void Quaternion::RotationZAxis(T_FLOAT rad)
//{
//  this->q(Z_AXIS, rad);
//}
//
//void Quaternion::RotationX(const TVec3f& direction, T_FLOAT rad)
//{
//  TVec3f v = direction;
//  v.x = direction.z;
//  v.z = direction.x;
//  this->q(direction, rad);
//}
//
//void Quaternion::RotationY(const TVec3f& direction, T_FLOAT rad)
//{
//  TVec3f v = direction;
//  v.y = direction.z;
//  v.z = direction.y;
//  this->q(direction, rad);
//}
//
//void Quaternion::RotationZ(const TVec3f& direction, T_FLOAT rad)
//{
//  this->q(direction, rad);
//}
//
//const TVec3f& Quaternion::EularAngles()
//{
//  if (!this->is_normalized_)
//  {
//    *this = Normalized(*this);
//    this->is_normalized_ = true;
//    this->eular_angles_ = this->v_ * (MathConstants::PI * 2);
//  }
//  return this->eular_angles_;
//}
//
//void Quaternion::SetRotationWithAxis(const TVec3f rotation)
//{
//
//}
//
//void Quaternion::SetRotationWithAxis(T_FLOAT x, T_FLOAT y, T_FLOAT z)
//{
//}
//
//const TVec3f Quaternion::q(const TVec3f& p, const TVec3f& v, T_FLOAT rad)
//{
//  const T_FLOAT sin_ = sin(rad / 2.0f);
//  const T_FLOAT cos_ = cos(rad / 2.0f);
//  Quaternion Q = Quaternion();
//  Q.v_ = v * sin_;
//  Q.w_ = cos_;
//
//  Quaternion R = Quaternion();
//  R.v_ = v * -sin_;
//  R.w_ = cos_;
//
//  Quaternion P = Quaternion();
//  P.v_ = p;
//  P.w_ = 0.0f;
//
//  //R*P
//
//  //R.w_ = R.w_ * 0.0f - (R.v_.x * 0.0f ...
//  R.w_ = 0.0f;
//  R.v_.x = 
//
//  this->v_ = v * sin_;
//  this->w_ *= cos_;
//  this->is_normalized_ = false;
//}
//
//const void Quaternion::ToRotationMatrix(LP_MATRIX_4x4 rotation_matrix)
//{
//  const T_FLOAT m11 = 1.0f - 2.0f * this->v_.y * this->v_.y - 2.0f * this->v_.z * this->v_.z;
//  const T_FLOAT m12 = 2.0f * this->v_.x * this->v_.y + 2.0f * this->w_ * this->v_.z;
//  const T_FLOAT m13 = 2.0f * this->v_.x * this->v_.z - 2.0f * this->w_ * this->v_.y;
//
//  const T_FLOAT m21 = 2.0f * this->v_.x * this->v_.y - 2.0f * this->w_ * this->v_.z;
//  const T_FLOAT m22 = 1.0f - 2.0f * this->v_.x * this->v_.x - 2.0f * this->v_.z * this->v_.z;
//  const T_FLOAT m23 = 2.0f * this->v_.y * this->v_.z + 2.0f * this->w_ * this->v_.x;
//
//  const T_FLOAT m31 = 2.0f * this->v_.x * this->v_.z + 2.0f * this->w_ * this->v_.y;
//  const T_FLOAT m32 = 2.0f * this->v_.y * this->v_.z - 2.0f * this->w_ * this->v_.x;
//  const T_FLOAT m33 = 1.0f - 2.0f * this->v_.x * this->v_.x - 2.0f * this->v_.y * this->v_.y;
//
//  NativeMethod::Matrix().Matrix4x4_Set(rotation_matrix, 0, 0, m11);
//  NativeMethod::Matrix().Matrix4x4_Set(rotation_matrix, 0, 1, m12);
//  NativeMethod::Matrix().Matrix4x4_Set(rotation_matrix, 0, 2, m13);
//
//  NativeMethod::Matrix().Matrix4x4_Set(rotation_matrix, 1, 0, m21);
//  NativeMethod::Matrix().Matrix4x4_Set(rotation_matrix, 1, 1, m22);
//  NativeMethod::Matrix().Matrix4x4_Set(rotation_matrix, 1, 2, m23);
//
//  NativeMethod::Matrix().Matrix4x4_Set(rotation_matrix, 2, 0, m31);
//  NativeMethod::Matrix().Matrix4x4_Set(rotation_matrix, 2, 1, m32);
//  NativeMethod::Matrix().Matrix4x4_Set(rotation_matrix, 2, 2, m33);
//}
//
//T_FLOAT Quaternion::ScalarSquare(const Quaternion& q)
//{
//  return
//    q.v_.x * q.v_.x +
//    q.v_.y * q.v_.y +
//    q.v_.z * q.v_.z +
//    q.w_ * q.w_;
//}
//
//T_FLOAT Quaternion::Scalar(const Quaternion& q)
//{
//  return sqrt(ScalarSquare(q));
//}
//
//const Quaternion Quaternion::Conjugated(const Quaternion& q)
//{
//  Quaternion ret = Quaternion();
//  ret.v_ = -q.v_;
//  ret.w_ = q.w_;
//  return ret;
//}
//
//const Quaternion Quaternion::Inversed(const Quaternion& q)
//{
//  return Conjugated(q) / ScalarSquare(q);
//}
//
//const Quaternion Quaternion::Normalized(const Quaternion& q)
//{
//  return q / ScalarSquare(q);
//}
