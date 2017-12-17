#include "Light.h"
#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Light::Light()
  : diffuse_(255, 255, 255, 255)
  , ambient_(50, 50, 100, 255)
//  , ambient_(255, 255, 255, 255)
  , direction_(0.0f, -1.0f, 1.0f)
{
  this->light_id_ = NativeMethod::Graphics().Graphics_CreateLight(&this->light_);
}

Light::~Light()
{
  NativeMethod::Graphics().Graphics_DeleteLight(this->light_id_, this->light_);
}

// =================================================================
// Method
// =================================================================
void Light::Apply()
{
  NativeMethod::Graphics().Graphics_SetLightDirection(this->light_id_, this->light_, this->direction_);
  NativeMethod::Graphics().Graphics_SetLightDiffuse(this->light_id_, this->light_, this->diffuse_);
  NativeMethod::Graphics().Graphics_SetLight(this->light_id_, this->light_);
  NativeMethod::Graphics().Graphics_SetLightEnable(this->light_id_, this->light_, true);

  NativeMethod::Graphics().Graphics_SetAmbient(this->ambient_);
}

// =================================================================
// setter/getter
// =================================================================
void Light::SetDirection(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  this->direction_.x = x;
  this->direction_.y = y;
  this->direction_.z = z;
}
