#include "ParticleDataLoader.h"
#include "NativeMethod.h"
#include "JsonParser.h"
#include "MathConstants.h"
#include "UserResourcePool.h"

enum EmitterType
{
  EM_TYPE_GRAVITY,
  EM_TYPE_RADIUS,
};

const ParticleDataLoader* ParticleDataLoader::DynamicLoad(const char* path)
{
  return UserResourcePool::GetInstance().DynamicLoad<ParticleDataLoader>(path);
}

// =================================================================
// Constructor / Destructor
// =================================================================
ParticleDataLoader::ParticleDataLoader(const char* path)
  : FileResource("ParticleData", path)
{}

ParticleData* ParticleDataLoader::NativeLoadProcess(const std::string& path)
{
  std::string str = NativeMethod::IO().TextFile_Read(path.c_str());
  JsonParser parser;
  JsonNode* json = parser.Parse(str.c_str());

  T_UINT8 type = json->GetValue("emitterType")->IntValue();

  ParticleData* data = nullptr;

  if (type == EM_TYPE_GRAVITY)
  {
    ParticleData_Gravity* exdata = new ParticleData_Gravity();
    data = exdata;

    exdata->accel_rad = json->GetValue("radialAcceleration")->FloatValue();
    exdata->accel_rad_variance = json->GetValue("radialAccelVariance")->FloatValue();

    exdata->accel_tan = json->GetValue("tangentialAcceleration")->FloatValue();
    exdata->accel_tan_variance = json->GetValue("tangentialAccelVariance")->FloatValue();

    exdata->speed = json->GetValue("speed")->FloatValue();
    exdata->speed_variance = json->GetValue("speedVariance")->FloatValue();

    exdata->gravity_x = json->GetValue("gravityx")->FloatValue();
    exdata->gravity_y = json->GetValue("gravityy")->FloatValue();

    exdata->emission_variance_x = json->GetValue("sourcePositionVariancex")->FloatValue();
    exdata->emission_variance_y = json->GetValue("sourcePositionVariancey")->FloatValue();
  }
  if (type == EM_TYPE_RADIUS)
  {
    ParticleData_Radius* exdata = new ParticleData_Radius();
    data = exdata;

    exdata->max_radius = json->GetValue("maxRadius")->FloatValue();
    exdata->max_radius_variance = json->GetValue("maxRadiusVariance")->FloatValue();
    exdata->min_radius = json->GetValue("minRadius")->FloatValue();
    //exdata->min_radius_variance = json->GetValue("minRadiusVariance")->IntValue();
    exdata->rotate_per_sec = json->GetValue("rotatePerSecond")->FloatValue();
    exdata->rotate_per_sec_variance = json->GetValue("rotatePerSecondVariance")->FloatValue();
  }
  data->region_ = this->atlas_->GetTextureRegion(json->GetString("textureFileName")->StringValue());

  data->start_color_r = json->GetValue("startColorRed")->FloatValue();
  data->start_color_g = json->GetValue("startColorGreen")->FloatValue();
  data->start_color_b = json->GetValue("startColorBlue")->FloatValue();
  data->start_color_a = json->GetValue("startColorAlpha")->FloatValue();

  data->start_color_r_variance = json->GetValue("startColorVarianceRed")->FloatValue();
  data->start_color_g_variance = json->GetValue("startColorVarianceGreen")->FloatValue();
  data->start_color_b_variance = json->GetValue("startColorVarianceBlue")->FloatValue();
  data->start_color_a_variance = json->GetValue("startColorVarianceAlpha")->FloatValue();

  data->end_color_r = json->GetValue("finishColorRed")->FloatValue();
  data->end_color_g = json->GetValue("finishColorGreen")->FloatValue();
  data->end_color_b = json->GetValue("finishColorBlue")->FloatValue();
  data->end_color_a = json->GetValue("finishColorAlpha")->FloatValue();

  data->end_color_r_variance = json->GetValue("finishColorVarianceRed")->FloatValue();
  data->end_color_g_variance = json->GetValue("finishColorVarianceGreen")->FloatValue();
  data->end_color_b_variance = json->GetValue("finishColorVarianceBlue")->FloatValue();
  data->end_color_a_variance = json->GetValue("finishColorVarianceAlpha")->FloatValue();

  data->start_spin = MathConstants::DegToRad(json->GetValue("rotationStart")->FloatValue());
  data->start_spin_variance = MathConstants::DegToRad(json->GetValue("rotationStartVariance")->FloatValue());
  data->end_spin = MathConstants::DegToRad(json->GetValue("rotationEnd")->FloatValue());
  data->end_spin_variance = MathConstants::DegToRad(json->GetValue("rotationEndVariance")->FloatValue());

  data->start_size = json->GetValue("startParticleSize")->FloatValue();
  data->start_size_variance = json->GetValue("startParticleSizeVariance")->FloatValue();
  data->end_size = json->GetValue("finishParticleSize")->FloatValue();
  data->end_size_variance = json->GetValue("finishParticleSizeVariance")->FloatValue();

  data->angle = MathConstants::DegToRad(json->GetValue("angle")->FloatValue());
  data->angle_variance = MathConstants::DegToRad(json->GetValue("angleVariance")->FloatValue());

  data->duration = json->GetValue("duration")->FloatValue();

  data->life_time = json->GetValue("particleLifespan")->FloatValue();
  data->life_time_variance = json->GetValue("particleLifespanVariance")->FloatValue();

  data->max_particles = json->GetValue("maxParticles")->IntValue();

  return data;
}
