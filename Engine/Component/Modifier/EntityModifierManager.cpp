#include "EntityModifierManager.h"
#include <algorithm>

static const T_UINT16 DEFAULT_ENTITY_MODIFIER_ROOT_COUNT = 128;
static const T_UINT16 DEFAULT_ATTRIBUTE_MODIFIER_COUNT = 256;
static const T_UINT16 DEFAULT_ATTRIBUTE_EX_MODIFIER_COUNT = 128;
static const T_UINT16 DEFAULT_DELAY_MODIFIER_COUNT = 128;
static const T_UINT16 DEFAULT_SEQUENCE_MODIFIER_COUNT = 128;
static const T_UINT16 DEFAULT_SYNCHRONIZED_MODIFIER_COUNT = 128;
static const T_UINT16 DEFAULT_ROUND_MODIFIER_COUNT = 128;
static const T_UINT16 DEFAULT_LOOP_MODIFIER_COUNT = 128;

EntityModifierAllocateOption::EntityModifierAllocateOption()
  : entity_modifier_root_count(DEFAULT_ENTITY_MODIFIER_ROOT_COUNT)
  , attribute_modifier_count(DEFAULT_ATTRIBUTE_MODIFIER_COUNT)
  , attribute_ex_modifier_count(DEFAULT_ATTRIBUTE_EX_MODIFIER_COUNT)
  , delay_modifier_count(DEFAULT_DELAY_MODIFIER_COUNT)
  , sequence_modifier_count(DEFAULT_SEQUENCE_MODIFIER_COUNT)
  , synchronized_modifier_count(DEFAULT_SYNCHRONIZED_MODIFIER_COUNT)
  , round_modifier_count(DEFAULT_ROUND_MODIFIER_COUNT)
  , loop_modifier_count(DEFAULT_LOOP_MODIFIER_COUNT)
{}

void EntityModifierManager::Init(const EntityModifierAllocateOption& option)
{
  Self().modifier_root_pool_ = new PoolAllocator<EntityModifierRoot>(option.entity_modifier_root_count);

  Self().attribute_modifier_pool_ = new PoolAllocator<AttributeEntityModifier>(option.attribute_modifier_count);
  Self().attribute_ex_modifier_pool_ = new PoolAllocator<AttributeEntityModifierEx>(option.attribute_ex_modifier_count);
  Self().delay_modifier_pool_ = new PoolAllocator<DelayEntityModifier>(option.delay_modifier_count);
  Self().sequence_modifier_pool_ = new PoolAllocator<SequenceEntityModifier>(option.sequence_modifier_count);
  Self().synchronized_modifier_pool_ = new PoolAllocator<SynchronizedEntityModifier>(option.synchronized_modifier_count);
  Self().round_modifier_pool_ = new PoolAllocator<RoundEntityModifier>(option.round_modifier_count);
  Self().loop_modifier_pool_ = new PoolAllocator<LoopEntityModifier>(option.loop_modifier_count);

}

void EntityModifierManager::Uninit()
{
  if (Self().modifier_root_pool_)
  {
    Self().modifier_root_pool_->Clear();
  }
  if (Self().delay_modifier_pool_)
  {
    Self().delay_modifier_pool_->Clear();
  }
  if (Self().sequence_modifier_pool_)
  {
    Self().sequence_modifier_pool_->Clear();
  }
  if (Self().synchronized_modifier_pool_)
  {
    Self().synchronized_modifier_pool_->Clear();
  }
  if (Self().round_modifier_pool_)
  {
    Self().round_modifier_pool_->Clear();
  }
  if (Self().loop_modifier_pool_)
  {
    Self().loop_modifier_pool_->Clear();
  }
  if (Self().attribute_modifier_pool_)
  {
    Self().attribute_modifier_pool_->Clear();
  }
  if (Self().attribute_ex_modifier_pool_)
  {
    Self().attribute_ex_modifier_pool_->Clear();
  }

  if (Self().modifier_root_pool_)
  {
    delete Self().modifier_root_pool_;
    Self().modifier_root_pool_ = nullptr;
  }
  if (Self().delay_modifier_pool_)
  {
    delete Self().delay_modifier_pool_;
    Self().delay_modifier_pool_ = nullptr;
  }
  if (Self().sequence_modifier_pool_)
  {
    delete Self().sequence_modifier_pool_;
    Self().sequence_modifier_pool_ = nullptr;
  }
  if (Self().synchronized_modifier_pool_)
  {
    delete Self().synchronized_modifier_pool_;
    Self().synchronized_modifier_pool_ = nullptr;
  }
  if (Self().round_modifier_pool_)
  {
    delete Self().round_modifier_pool_;
    Self().round_modifier_pool_ = nullptr;
  }
  if (Self().loop_modifier_pool_)
  {
    delete Self().loop_modifier_pool_;
    Self().loop_modifier_pool_ = nullptr;
  }
  if (Self().attribute_modifier_pool_)
  {
    delete Self().attribute_modifier_pool_;
    Self().attribute_modifier_pool_ = nullptr;
  }
  if (Self().attribute_ex_modifier_pool_)
  {
    delete Self().attribute_ex_modifier_pool_;
    Self().attribute_ex_modifier_pool_ = nullptr;
  }
}

void EntityModifierManager::ClearModifiers()
{
  this->modifier_root_pool_->Clear();

  this->attribute_modifier_pool_->Clear();
  this->attribute_ex_modifier_pool_->Clear();
  this->delay_modifier_pool_->Clear();
  this->sequence_modifier_pool_->Clear();
  this->synchronized_modifier_pool_->Clear();
  this->round_modifier_pool_->Clear();
  this->loop_modifier_pool_->Clear();
}

void EntityModifierManager::ClearModifiersWithTargetEntity(GameObject2D* target)
{
  Self().finished_roots_.clear();
  Self().modifier_root_pool_->Loop([&](EntityModifierRoot* root) {
    if (root->GetTargetEntity() != target)
    {
      return;
    }
    root->OnDetached();
    Self().finished_roots_.emplace_back(root);
  });
  for (EntityModifierRoot* root : Self().finished_roots_)
  {
    root->OnRelease();
  }
  Self().finished_roots_.clear();
}

bool EntityModifierManager::OnUpdate(T_UINT16 frame_elapsed)
{
  Self().finished_roots_.clear();
  Self().modifier_root_pool_->Loop([&](EntityModifierRoot* root) {
    if (root->IsFinished())
    {
      return;
    }
    if (!root->IsAttached())
    {
      return;
    }
    if (root->OnUpdate(frame_elapsed))
    {
      return;
    }
    root->OnUpdateFinish();
    Self().finished_roots_.emplace_back(root);
  });
  for (EntityModifierRoot* root : Self().finished_roots_)
  {
    root->OnFinish();
  }
  Self().finished_roots_.clear();
  return true;
}