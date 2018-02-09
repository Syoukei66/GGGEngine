#include "ParticleSystem.h"
#include "MathConstants.h"
#include "ParticleData.h"
#include "Director.h"
#include "Moniker.h"

//===============================================================
// Particle
//===============================================================
void Particle::OnAllocated()
{
  this->offset_x_ = 0;
  this->offset_y_ = 0;
//  this->GetMaterial()->SetBlendFunction(BlendFunction::BLEND_ADD_SRC, BlendFunction::BLEND_ADD_DST);
}

void Particle::OnFree()
{
}

void Particle::OnEmission(const ParticleData* data, const Transform2D* offset)
{
  if (offset)
  {
    this->offset_x_ = offset->GetX();
    this->offset_y_ = offset->GetY();
  }

  //TODO: Œ»Ý•`‰æ•s‰Â”\
  //this->SetTextureRegion(data->region_);
  //this->FitToTexture();

  this->life_time = data->CalcValueByVariance(data->life_time, data->life_time_variance, 0) * Director::GetInstance()->GetFrameRate();
  this->life_time_rest = this->life_time;

  this->start_size = data->CalcValueByVariance(data->start_size, data->start_size_variance, 0) * 0.01f;
  this->start_spin = MathConstants::DegToRad((T_FLOAT)data->CalcValueByVariance(data->start_spin, data->start_spin_variance, 0));
  this->start_color_r = data->CalcValueByVariance(data->start_color_r, data->start_color_r_variance, 0);
  this->start_color_g = data->CalcValueByVariance(data->start_color_g, data->start_color_g_variance, 0);
  this->start_color_b = data->CalcValueByVariance(data->start_color_b, data->start_color_b_variance, 0);
  this->start_color_a = data->CalcValueByVariance(data->start_color_a, data->start_color_a_variance, 0);

  if (data->end_size == -1.0f)
  {
    this->end_size = this->start_size;
  }
  else
  {
    this->end_size = data->CalcValueByVariance(data->end_size, data->end_size_variance, 0) * 0.01f;
  }
  this->end_spin = MathConstants::DegToRad(data->CalcValueByVariance(data->end_spin, data->end_spin_variance, 0));
  this->end_color_r = data->CalcValueByVariance(data->end_color_r, data->end_color_r_variance, 0);
  this->end_color_g = data->CalcValueByVariance(data->end_color_g, data->end_color_g_variance, 0);
  this->end_color_b = data->CalcValueByVariance(data->end_color_b, data->end_color_b_variance, 0);
  this->end_color_a = data->CalcValueByVariance(data->end_color_a, data->end_color_a_variance, 0);

  data->OnEmission(this, offset);

  this->OnUpdate(data);
}

bool Particle::OnUpdate(const ParticleData* data)
{
  const T_FLOAT pre_progress = 1.0f - (T_FLOAT)(this->life_time_rest) / (this->life_time - 1.0f);
  const T_FLOAT progress = 1.0f - (T_FLOAT)(this->life_time_rest - 1.0f) / (this->life_time - 1.0f);
  this->life_time_rest = std::max(0.0f, this->life_time_rest - 1.0f);
  this->GetTransform()->SetScale(data->CalcValueByProgress(this->start_size, this->end_size, progress));
  this->GetTransform()->SetRotation(data->CalcValueByProgress(this->start_spin, this->end_spin, progress));
  this->GetRenderer()->GetMaterial()->GetDiffuse().SetRed(data->CalcValueByProgress(this->start_color_r, this->end_color_r, progress));
  this->GetRenderer()->GetMaterial()->GetDiffuse().SetGreen(data->CalcValueByProgress(this->start_color_g, this->end_color_g, progress));
  this->GetRenderer()->GetMaterial()->GetDiffuse().SetBlue(data->CalcValueByProgress(this->start_color_b, this->end_color_b, progress));
  this->GetRenderer()->GetMaterial()->GetDiffuse().SetAlpha(data->CalcValueByProgress(this->start_color_a, this->end_color_a, progress));

  return data->OnUpdate(this, progress, pre_progress - progress);
}

T_FLOAT Particle::GetOffsetX()
{
  return this->offset_x_;
}

T_FLOAT Particle::GetOffsetY()
{
  return this->offset_y_;
}

//===============================================================
// ParticleSystem
//===============================================================
ParticleSystem* ParticleSystem::CreateWithData(const ParticleData* data)
{
  ParticleSystem* ret = new ParticleSystem();
  ret->Prepare(data);
  ret->Init();
  return ret;
}

ParticleSystem::ParticleSystem()
  : data_(nullptr)
  , particles_(nullptr)
  , duration_(0)
  , time_count_(0.0f)
  , apply_local_position_(true)
{}

ParticleSystem::~ParticleSystem()
{
  delete this->particles_;
}

void ParticleSystem::Prepare(const ParticleData* data)
{
  this->data_ = data;
  this->particles_ = new PoolAllocator<Particle>(data->max_particles);
}

void ParticleSystem::Init()
{
  if (this->data_->duration <= 0)
  {
    this->duration_ = -1.0f;
  }
  else
  {
    this->duration_ = this->data_->duration * Director::GetInstance()->GetFrameRate();
  }
}

void ParticleSystem::Update()
{
  if (this->data_->duration == -1.0f || this->duration_ > 0.0f)
  {
    this->duration_ -= 1.0f;
    const T_FLOAT emission_time = (T_FLOAT)Director::GetInstance()->GetFrameRate() * this->data_->life_time / this->data_->max_particles;
    this->time_count_ += 1.0f;
    while (this->time_count_ > emission_time)
    {
      this->time_count_ -= emission_time;
      Particle* new_p = this->particles_->Allocate();
      if (new_p)
      {
        if (apply_local_position_)
        {
          new_p->OnEmission(this->data_, nullptr);
        }
        else
        {
          new_p->OnEmission(this->data_, this->GetTransform());
        }
        this->AddChild(new_p);
      }
    }
  }

  if (this->particles_->GetAllocatedCount() == 0)
  {
    return;
  }
  this->particles_->RemoveIf([&](Particle* p)
  {
    if (!p->OnUpdate(this->data_))
    {
      return false;
    }
    this->RemoveChild(p);
    return true;
  });
  if (this->particles_->GetAllocatedCount() == 0)
  {
    this->Init();
  }
}

void ParticleSystem::PushMatrixStack(GameObjectRenderState* state)
{
  if (this->apply_local_position_)
  {
    GameObject2D::PushMatrixStack(state);
  }
}

void ParticleSystem::PopMatrixStack(GameObjectRenderState* state)
{
  if (this->apply_local_position_)
  {
    GameObject2D::PopMatrixStack(state);
  }
}
