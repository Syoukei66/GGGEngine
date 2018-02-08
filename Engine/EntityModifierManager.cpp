#include "EntityModifierManager.h"
#include <algorithm>

//Scene–ˆ‚ÉÝ’è‚·‚é•ûŽ®‚Ì•û‚ª‚¢‚¢

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

EntityModifierManager::EntityModifierManager()
  : modifier_root_pool_(nullptr)
  , attribute_modifier_pool_(nullptr)
  , delay_modifier_pool_(nullptr)
  , sequence_modifier_pool_(nullptr)
  , synchronized_modifier_pool_(nullptr)
  , round_modifier_pool_(nullptr)
  , loop_modifier_pool_(nullptr)
{}

EntityModifierManager::~EntityModifierManager()
{
  this->Uninit();
}

void EntityModifierManager::Init(EntityModifierAllocateOption* option)
{
  this->modifier_root_pool_ = new PoolAllocator<EntityModifierRoot>(option->entity_modifier_root_count);

  this->attribute_modifier_pool_ = new PoolAllocator<AttributeEntityModifier>(option->attribute_modifier_count);
  this->attribute_ex_modifier_pool_ = new PoolAllocator<AttributeEntityModifierEx>(option->attribute_ex_modifier_count);
  this->delay_modifier_pool_ = new PoolAllocator<DelayEntityModifier>(option->delay_modifier_count);
  this->sequence_modifier_pool_ = new PoolAllocator<SequenceEntityModifier>(option->sequence_modifier_count);
  this->synchronized_modifier_pool_ = new PoolAllocator<SynchronizedEntityModifier>(option->synchronized_modifier_count);
  this->round_modifier_pool_ = new PoolAllocator<RoundEntityModifier>(option->round_modifier_count);
  this->loop_modifier_pool_ = new PoolAllocator<LoopEntityModifier>(option->loop_modifier_count);

}

void EntityModifierManager::Uninit()
{
  if (this->modifier_root_pool_)
  {
    this->modifier_root_pool_->Clear();
  }
  if (this->delay_modifier_pool_)
  {
    this->delay_modifier_pool_->Clear();
  }
  if (this->sequence_modifier_pool_)
  {
    this->sequence_modifier_pool_->Clear();
  }
  if (this->synchronized_modifier_pool_)
  {
    this->synchronized_modifier_pool_->Clear();
  }
  if (this->round_modifier_pool_)
  {
    this->round_modifier_pool_->Clear();
  }
  if (this->loop_modifier_pool_)
  {
    this->loop_modifier_pool_->Clear();
  }
  if (this->attribute_modifier_pool_)
  {
    this->attribute_modifier_pool_->Clear();
  }
  if (this->attribute_ex_modifier_pool_)
  {
    this->attribute_ex_modifier_pool_->Clear();
  }

  if (this->modifier_root_pool_)
  {
    delete this->modifier_root_pool_;
    this->modifier_root_pool_ = nullptr;
  }
  if (this->delay_modifier_pool_)
  {
    delete this->delay_modifier_pool_;
    this->delay_modifier_pool_ = nullptr;
  }
  if (this->sequence_modifier_pool_)
  {
    delete this->sequence_modifier_pool_;
    this->sequence_modifier_pool_ = nullptr;
  }
  if (this->synchronized_modifier_pool_)
  {
    delete this->synchronized_modifier_pool_;
    this->synchronized_modifier_pool_ = nullptr;
  }
  if (this->round_modifier_pool_)
  {
    delete this->round_modifier_pool_;
    this->round_modifier_pool_ = nullptr;
  }
  if (this->loop_modifier_pool_)
  {
    delete this->loop_modifier_pool_;
    this->loop_modifier_pool_ = nullptr;
  }
  if (this->attribute_modifier_pool_)
  {
    delete this->attribute_modifier_pool_;
    this->attribute_modifier_pool_ = nullptr;
  }
  if (this->attribute_ex_modifier_pool_)
  {
    delete this->attribute_ex_modifier_pool_;
    this->attribute_ex_modifier_pool_ = nullptr;
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
  finished_roots_.clear();
  for (std::list<EntityModifierRoot*>::iterator itr = this->modifier_root_pool_->begin(); itr != this->modifier_root_pool_->end(); ++itr)
  {
    EntityModifierRoot* const root = (*itr);
    if (root->GetTargetEntity() != target)
    {
      continue;
    }
    root->OnDetached();
    finished_roots_.push_back(root);
  }
  for (std::deque<EntityModifierRoot*>::iterator itr = this->finished_roots_.begin(); itr != this->finished_roots_.end(); ++itr)
  {
    (*itr)->OnRelease();
  }
  finished_roots_.clear();
}

bool EntityModifierManager::OnUpdate(T_UINT16 frame_elapsed)
{
  finished_roots_.clear();
  for (std::list<EntityModifierRoot*>::iterator itr = this->modifier_root_pool_->begin(); itr != this->modifier_root_pool_->end(); ++itr)
  {
    EntityModifierRoot* const root = (*itr);
    if (root->IsFinished())
    {
      continue;
    }
    if (!root->IsAttached())
    {
      continue;
    }
    if (root->OnUpdate(frame_elapsed))
    {
      continue;
    }
    root->OnUpdateFinish();
    finished_roots_.push_back(root);
  }
  for (std::deque<EntityModifierRoot*>::iterator itr = this->finished_roots_.begin(); itr != this->finished_roots_.end(); ++itr)
  {
    (*itr)->OnFinish();
  }
  finished_roots_.clear();
  return true;
}