#pragma once

#include "UpdateEvent.h"
#include "EntityModifier.h"
#include "PoolAllocator.h"

struct EntityModifierAllocateOption
{
  EntityModifierAllocateOption();
  T_UINT16 entity_modifier_root_count;
  T_UINT16 attribute_modifier_count;
  T_UINT16 attribute_ex_modifier_count;
  T_UINT16 delay_modifier_count;
  T_UINT16 sequence_modifier_count;
  T_UINT16 synchronized_modifier_count;
  T_UINT16 round_modifier_count;
  T_UINT16 loop_modifier_count;
};

class EntityModifierManager
{
public:
  static EntityModifierManager& GetInstance()
  {
    static EntityModifierManager self = EntityModifierManager();
    return self;
  }

private:
  EntityModifierManager();

public:
  ~EntityModifierManager();

public:
  void Init(EntityModifierAllocateOption* option);
  void Uninit();

  bool OnUpdate(T_UINT16 frame_elapsed);

public:
  void ClearModifiers();
  void ClearModifiersWithTargetEntity(GameObject2D* target);

public:
  inline PoolAllocator<EntityModifierRoot>* GetModifierRootAllocator() const
  {
    return this->modifier_root_pool_;
  }
  inline PoolAllocator<AttributeEntityModifier>* GetAttributeModifierAllocator() const
  {
    return this->attribute_modifier_pool_;
  }
  inline PoolAllocator<AttributeEntityModifierEx>* GetAttributeModifierExAllocator() const
  {
    return this->attribute_ex_modifier_pool_;
  }
  inline PoolAllocator<DelayEntityModifier>* GetDelayModifierAllocator() const
  {
    return this->delay_modifier_pool_;
  }
  inline PoolAllocator<SequenceEntityModifier>* GetSequenceModifierAllocator() const
  {
    return this->sequence_modifier_pool_;
  }
  inline PoolAllocator<SynchronizedEntityModifier>* GetSynchronizedModifierAllocator() const
  {
    return this->synchronized_modifier_pool_;
  }  
  inline PoolAllocator<RoundEntityModifier>* GetRoundModifierAllocator() const
  {
    return this->round_modifier_pool_;
  }
  inline PoolAllocator<LoopEntityModifier>* GetLoopModifierAllocator() const
  {
    return this->loop_modifier_pool_;
  }

private:
  PoolAllocator<EntityModifierRoot>* modifier_root_pool_;
  std::deque<EntityModifierRoot*> finished_roots_;

  PoolAllocator<AttributeEntityModifier>* attribute_modifier_pool_;
  PoolAllocator<AttributeEntityModifierEx>* attribute_ex_modifier_pool_;
  PoolAllocator<DelayEntityModifier>* delay_modifier_pool_;
  PoolAllocator<SequenceEntityModifier>* sequence_modifier_pool_;
  PoolAllocator<SynchronizedEntityModifier>* synchronized_modifier_pool_;
  PoolAllocator<RoundEntityModifier>* round_modifier_pool_;
  PoolAllocator<LoopEntityModifier>* loop_modifier_pool_;
};
