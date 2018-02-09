#include "EntityModifier.h"
#include <algorithm>

#include "EasingFunctionManager.h"
#include "EntityModifierManager.h"

//=========================================================================
// EntityModifierRoot
//=========================================================================
void EntityModifierRoot::OnAllocated()
{
  this->is_loop_ = false;
  this->is_pause_ = false;
  this->is_reverse_ = false;
  this->modifier_ = NULL;
  this->target_ = NULL;
  this->duration_ = 0;
  this->duration_rest_ = 0;
  this->listeners_.clear();
}

void EntityModifierRoot::OnFree()
{
  this->modifier_->Free();
  this->listeners_.clear();
}

bool EntityModifierRoot::OnUpdate(T_UINT16 frame_elapsed)
{
  if (this->is_pause_)
  {
    return true;
  }
  this->duration_rest_ = (T_UINT16)std::max((T_INT32)0, (T_INT32)this->duration_rest_ - (T_INT32)frame_elapsed);
  const T_UINT16 duration_rest = this->is_reverse_ ? this->duration_ - this->duration_rest_ : this->duration_rest_;
  const T_FLOAT progress = 1.0f - (T_FLOAT)duration_rest / this->duration_;
  this->modifier_->OnUpdate(this->target_, progress);
  return this->duration_rest_ > 0;
}

void EntityModifierRoot::OnUpdateFinish()
{
  for (std::function<void()>& listener : this->listeners_)
  {
    listener();
  }
}

void EntityModifierRoot::Prepare(EntityModifier* modifier)
{
  this->modifier_ = modifier;
  this->duration_ = modifier->GetDuration();
  this->duration_rest_ = this->duration_;
}

void EntityModifierRoot::OnAttached(GameObject2D* target)
{
  this->target_ = target;
}

void EntityModifierRoot::OnDetached()
{
  this->target_ = nullptr;
}

void EntityModifierRoot::Release()
{
  this->reference_count_--;
  this->OnRelease();
}

void EntityModifierRoot::OnRelease()
{
  if (this->reference_count_ > 0)
  {
    return;
  }
  
  EntityModifierManager::GetInstance().GetModifierRootAllocator()->Free(this);
}

void EntityModifierRoot::OnFinish()
{
  if (this->is_loop_)
  {
    this->Play();
    return;
  }
  this->OnRelease();
}

void EntityModifierRoot::Play()
{
  this->is_reverse_ = false;
  this->duration_rest_ = this->duration_;
  this->is_pause_ = false;
}

void EntityModifierRoot::Reverse()
{
  this->is_reverse_ = !this->is_reverse_;
  this->duration_rest_ = this->duration_ - this->duration_rest_;
  this->is_pause_ = false;
}

void EntityModifierRoot::Pause()
{
  this->is_pause_ = true;
}

void EntityModifierRoot::Resume()
{
  this->is_pause_ = false;
}

void EntityModifierRoot::Stop()
{
  this->duration_rest_ = this->duration_;
  this->is_pause_ = true;
  this->is_reverse_ = false;
}

void EntityModifierRoot::AddEntityModifierListener(std::function<void()> listener)
{
  this->listeners_.push_back(listener);
}

void EntityModifierRoot::ClearEntityModifierListener()
{
  this->listeners_.clear();
}

bool EntityModifierRoot::IsFinished()
{
  return this->duration_rest_ == 0;
}

//=========================================================================
// EntityModifier
//=========================================================================
void EntityModifier::OnAllocated()
{
  this->duration_ = 0;
  this->easing_func_ = EasingFunction::FK_LINER;
  this->easing_operator_ = EasingFunction::EASE_IN;
}

void EntityModifier::OnUpdate(GameObject2D* target, T_FLOAT progress)
{
  //Linerの場合はEasingFunctionの呼び出しを省略する
  //0.0fと1.0fの場合も計算を省略
  if (this->easing_func_ != EasingFunction::FK_LINER &&
    0.0f < progress && progress < 1.0f)
  {
    progress = EasingFunctionManager::GetInstance()->CalcByID(this->easing_func_, this->easing_operator_, progress);
  }
  this->OnTimelineUpdate(target, progress);
}

void EntityModifier::BasePrepare(T_UINT16 duration)
{
  this->duration_ = duration;
}

//=========================================================================
// DelayEntityModifier
//=========================================================================
void DelayEntityModifier::OnFree()
{}

void DelayEntityModifier::Free()
{
  EntityModifierManager::GetInstance().GetDelayModifierAllocator()->Free(this);
}

void DelayEntityModifier::OnTimelineUpdate(GameObject2D* target, T_FLOAT progress)
{}

void DelayEntityModifier::Prepare(T_UINT16 duration)
{
  EntityModifier::BasePrepare(duration);
}

//=========================================================================
// SequenceEntityModifier
//=========================================================================
void SequenceEntityModifier::OnAllocated()
{
  EntityModifier::OnAllocated();
  this->modifiers_.clear();
}

void SequenceEntityModifier::OnFree()
{
  for (EntityModifier* modifier : this->modifiers_)
  {
    modifier->Free();
  }
  this->modifiers_.clear();
}

void SequenceEntityModifier::Free()
{
  EntityModifierManager::GetInstance().GetSequenceModifierAllocator()->Free(this);
}

void SequenceEntityModifier::OnTimelineUpdate(GameObject2D* target, T_FLOAT progress)
{
  const T_FLOAT duration = (T_FLOAT)this->GetDuration();
  for (EntityModifier* modifier : this->modifiers_)
  {
    const T_FLOAT progress_rate = modifier->GetDuration() / duration;
    if (progress < progress_rate)
    {
      modifier->OnUpdate(target, progress / progress_rate);
      return;
    }
    modifier->OnUpdate(target, 1.0f);
    progress -= progress_rate;
  }
}

void SequenceEntityModifier::Register(EntityModifier* modifier)
{
  this->modifiers_.push_back(modifier);
}

void SequenceEntityModifier::Prepare()
{
  T_UINT16 need_power_sum = 0;
  for (EntityModifier* modifier : this->modifiers_)
  {
    need_power_sum += modifier->GetDuration();
  }
  EntityModifier::BasePrepare(need_power_sum);
}

//=========================================================================
// SynchronizedEntityModifier
//=========================================================================
void SynchronizedEntityModifier::OnAllocated()
{
  EntityModifier::OnAllocated();
  this->modifiers_.clear();
}

void SynchronizedEntityModifier::OnFree()
{
  for (EntityModifier* modifier : this->modifiers_)
  {
    modifier->Free();
  }
  this->modifiers_.clear();
}

void SynchronizedEntityModifier::Free()
{
  EntityModifierManager::GetInstance().GetSynchronizedModifierAllocator()->Free(this);
}

void SynchronizedEntityModifier::OnTimelineUpdate(GameObject2D* target, T_FLOAT progress)
{
  const T_FLOAT duration = (T_FLOAT)this->GetDuration();
  for (EntityModifier* modifier : this->modifiers_)
  {
    const T_FLOAT progress_rate = duration / modifier->GetDuration();
    const T_FLOAT finally_progress = std::min(1.0f, progress * progress_rate);
    modifier->OnUpdate(target, finally_progress);
  }
}

void SynchronizedEntityModifier::Register(EntityModifier* modifier)
{
  this->modifiers_.push_back(modifier);
}

void SynchronizedEntityModifier::Prepare()
{
  T_UINT16 need_power_max = 0;
  for (EntityModifier* modifier : this->modifiers_)
  {
    need_power_max = std::max(need_power_max, modifier->GetDuration());
  }
  EntityModifier::BasePrepare(need_power_max);
}

//=========================================================================
// LoopEntityModifier
// セットしたModifierを指定した回数だけ実行する
//=========================================================================
void LoopEntityModifier::OnAllocated()
{
  EntityModifier::OnAllocated();
  this->modifier_ = NULL;
  this->loop_count_ = 0;
}

void LoopEntityModifier::OnFree()
{
  this->modifier_->Free();
  this->modifier_ = NULL;
}

void LoopEntityModifier::Free()
{
  EntityModifierManager::GetInstance().GetLoopModifierAllocator()->Free(this);
}

void LoopEntityModifier::OnTimelineUpdate(GameObject2D* target, T_FLOAT progress)
{
  const T_FLOAT duration = (T_FLOAT)this->GetDuration();
  for (T_UINT8 i = 0; i < this->loop_count_; ++i)
  {
    const T_FLOAT progress_rate = this->modifier_->GetDuration() / duration;
    if (progress < progress_rate)
    {
      this->modifier_->OnUpdate(target, progress / progress_rate);
      return;
    }
    this->modifier_->OnUpdate(target, 1.0f);
    progress -= progress_rate;
  }
}

void LoopEntityModifier::Prepare(EntityModifier* modifier, T_UINT8 loop_count)
{
  this->modifier_ = modifier;
  this->loop_count_ = loop_count;
  EntityModifier::BasePrepare(this->modifier_->GetDuration() * this->loop_count_);
}

//=========================================================================
// RoundEntityModifier
//=========================================================================
void RoundEntityModifier::OnAllocated()
{
  EntityModifier::OnAllocated();
  this->modifier_ = NULL;
}

void RoundEntityModifier::OnFree()
{
  this->modifier_->Free();
}

void RoundEntityModifier::Free()
{
  EntityModifierManager::GetInstance().GetRoundModifierAllocator()->Free(this);
}

void RoundEntityModifier::OnTimelineUpdate(GameObject2D* target, T_FLOAT progress)
{
  if (progress < 0.5f)
  {
    this->modifier_->OnUpdate(target, progress * 2.0f);
    return;
  }
  this->modifier_->OnUpdate(target, 1.0f);
  this->modifier_->OnUpdate(target, 2.0f - progress * 2.0f);
}

void RoundEntityModifier::Prepare(EntityModifier* modifier)
{
  this->modifier_ = modifier;
  EntityModifier::BasePrepare(this->modifier_->GetDuration() * 2);
}

//=========================================================================
// Operator Function
// メモリ削減の為インターフェースや関数ポインタではなく関数を配列で用意し、
// そのインデックスの関数を実行するで多態性を実現する
// (オペレーターは拡張性がこれ以上無いと思われる為)
//=========================================================================
static T_FLOAT Operator_FromBy(GameObject2D* target, const EntityModifierAttribute* attr, T_FLOAT from, T_FLOAT val, T_FLOAT progress)
{
  return from + val * progress;
}

static T_FLOAT Operator_FromTo(GameObject2D* target, const EntityModifierAttribute* attr, T_FLOAT from, T_FLOAT to, T_FLOAT progress)
{
  return from + (to - from) * progress;
}

static T_FLOAT Operator_By(GameObject2D* target, const EntityModifierAttribute* attr, T_FLOAT n, T_FLOAT val, T_FLOAT progress)
{
  return Operator_FromBy(target, attr, attr->GetValue(target), val, progress);
}

static T_FLOAT Operator_To(GameObject2D* target, const EntityModifierAttribute* attr, T_FLOAT n, T_FLOAT to, T_FLOAT progress)
{
  return Operator_FromTo(target, attr, attr->GetValue(target), to, progress);
}

static T_FLOAT Operator_Add(GameObject2D* target, const EntityModifierAttribute* attr, T_FLOAT from, T_FLOAT val, T_FLOAT progress)
{
  return from + val * progress;
}

static T_FLOAT Operator_Sub(GameObject2D* target, const EntityModifierAttribute* attr, T_FLOAT from, T_FLOAT val, T_FLOAT progress)
{
  return from - val * progress;
}

static T_FLOAT Operator_Mul(GameObject2D* target, const EntityModifierAttribute* attr, T_FLOAT from, T_FLOAT val, T_FLOAT progress)
{
  return from * pow(val, progress);
}

static T_FLOAT Operator_Div(GameObject2D* target, const EntityModifierAttribute* attr, T_FLOAT from, T_FLOAT val, T_FLOAT progress)
{
  return from / pow(val, progress);
}

typedef T_FLOAT(*OPERATOR_FUNC)(GameObject2D*, const EntityModifierAttribute*, T_FLOAT, T_FLOAT, T_FLOAT);
static const OPERATOR_FUNC OPERATOR_FUNCS[AttributeEntityModifier::MODIFIER_OP_DATANUM] =
{
  Operator_By,
  Operator_To,
  Operator_FromBy,
  Operator_FromTo,
  Operator_Add,
  Operator_Sub,
  Operator_Mul,
  Operator_Div,
};

//=========================================================================
// Attribute
//=========================================================================
void AttributeEntityModifier::OnAllocated()
{
  EntityModifier::OnAllocated();
  this->arg0_ = 0.0f;
  this->arg1_ = 0.0f;
  this->attribute_ = NULL;
  this->rate_operator_ = AttributeEntityModifier::MODIFIER_OP_BY;
}

void AttributeEntityModifier::OnFree()
{
}

void AttributeEntityModifier::Free()
{
  EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Free(this);
}

void AttributeEntityModifier::OnTimelineUpdate(GameObject2D* target, T_FLOAT progress)
{
  this->attribute_->SetValue(target, OPERATOR_FUNCS[this->rate_operator_](target, this->attribute_, this->arg0_, this->arg1_, progress));
}

void AttributeEntityModifier::Prepare(T_UINT16 duration, T_FLOAT arg0, T_FLOAT arg1, const EntityModifierAttribute* attr, T_UINT8 op)
{
  EntityModifier::BasePrepare(duration);
  this->arg0_ = arg0;
  this->arg1_ = arg1;
  this->attribute_ = attr;
  this->rate_operator_ = op;
}

//=========================================================================
// AttributeEntityModifierEX
//=========================================================================
AttributeEntityModifierEx::AttributeEntityModifierEx()
  : other_(NULL)
  , other_attribute_(NULL)
{}

void AttributeEntityModifierEx::OnAllocated()
{
  AttributeEntityModifier::OnAllocated();
  this->other_ = NULL;
  this->other_attribute_ = NULL;
}

void AttributeEntityModifierEx::OnFree()
{
}

void AttributeEntityModifierEx::Free()
{
  EntityModifierManager::GetInstance().GetAttributeModifierExAllocator()->Free(this);
}

void AttributeEntityModifierEx::OnTimelineUpdate(GameObject2D* target, T_FLOAT progress)
{
  this->arg1_ = this->other_attribute_->GetValue(this->other_);
  AttributeEntityModifier::OnTimelineUpdate(target, progress);
}

void AttributeEntityModifierEx::Prepare(T_UINT16 duration, T_FLOAT arg0, T_FLOAT arg1, const EntityModifierAttribute* attr, T_UINT8 op, GameObject2D* other, const EntityModifierAttribute* other_attr)
{
  this->other_ = other;
  this->other_attribute_ = other_attr;
  AttributeEntityModifier::Prepare(duration, arg0, arg1, attr, op);
}