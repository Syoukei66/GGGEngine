#pragma once

#include <Core/Application/Allocator/PoolAllocator.h>
#include "EntityModifier.h"

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
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SINGLETON(EntityModifierManager);

public:
  static void Init(const EntityModifierAllocateOption& option);
  static void Uninit();

  static bool OnUpdate(T_UINT16 frame_elapsed);

public:
  void ClearModifiers();
  static void ClearModifiersWithTargetEntity(GameObject2D* target);

public:
  static GG_INLINE PoolAllocator<EntityModifierRoot>* GetModifierRootAllocator()
  {
    return Self().modifier_root_pool_;
  }
  static GG_INLINE PoolAllocator<AttributeEntityModifier>* GetAttributeModifierAllocator()
  {
    return Self().attribute_modifier_pool_;
  }
  static GG_INLINE PoolAllocator<AttributeEntityModifierEx>* GetAttributeModifierExAllocator()
  {
    return Self().attribute_ex_modifier_pool_;
  }
  static GG_INLINE PoolAllocator<DelayEntityModifier>* GetDelayModifierAllocator()
  {
    return Self().delay_modifier_pool_;
  }
  static GG_INLINE PoolAllocator<SequenceEntityModifier>* GetSequenceModifierAllocator()
  {
    return Self().sequence_modifier_pool_;
  }
  static GG_INLINE PoolAllocator<SynchronizedEntityModifier>* GetSynchronizedModifierAllocator()
  {
    return Self().synchronized_modifier_pool_;
  }  
  static GG_INLINE PoolAllocator<RoundEntityModifier>* GetRoundModifierAllocator()
  {
    return Self().round_modifier_pool_;
  }
  static GG_INLINE PoolAllocator<LoopEntityModifier>* GetLoopModifierAllocator()
  {
    return Self().loop_modifier_pool_;
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
