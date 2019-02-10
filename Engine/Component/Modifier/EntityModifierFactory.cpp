#include "EntityModifierFactory.h"
#include "EntityModifierManager.h"

//=======================================================================
// Root
//=======================================================================
EntityModifierRoot* EntityModifierFactory::Root(EntityModifier* modifier)
{
  EntityModifierRoot* ret = EntityModifierManager::GetModifierRootAllocator()->Allocate();
  ret->Prepare(modifier);
  return ret;
}

//=======================================================================
// Sequence
//=======================================================================
EntityModifier* EntityModifierFactory::Sequence(EntityModifier* m0, EntityModifier* m1)
{
  SequenceEntityModifier* ret = EntityModifierManager::GetSequenceModifierAllocator()->Allocate();
  ret->Register(m0);
  ret->Register(m1);
  ret->Prepare();
  return ret;
}

EntityModifier* EntityModifierFactory::Sequence(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2)
{
  SequenceEntityModifier* ret = EntityModifierManager::GetSequenceModifierAllocator()->Allocate();
  ret->Register(m0);
  ret->Register(m1);
  ret->Register(m2);
  ret->Prepare();
  return ret;
}

EntityModifier* EntityModifierFactory::Sequence(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2, EntityModifier* m3)
{
  SequenceEntityModifier* ret = EntityModifierManager::GetSequenceModifierAllocator()->Allocate();
  ret->Register(m0);
  ret->Register(m1);
  ret->Register(m2);
  ret->Register(m3);
  ret->Prepare();
  return ret;
}

EntityModifier* EntityModifierFactory::Sequence(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2, EntityModifier* m3, EntityModifier* m4)
{
  SequenceEntityModifier* ret = EntityModifierManager::GetSequenceModifierAllocator()->Allocate();
  ret->Register(m0);
  ret->Register(m1);
  ret->Register(m2);
  ret->Register(m3);
  ret->Register(m4);
  ret->Prepare();
  return ret;
}

//=======================================================================
// Synchronized
//=======================================================================
EntityModifier* EntityModifierFactory::Synchronized(EntityModifier* m0, EntityModifier* m1)
{
  SynchronizedEntityModifier* ret = EntityModifierManager::GetSynchronizedModifierAllocator()->Allocate();
  ret->Register(m0);
  ret->Register(m1);
  ret->Prepare();
  return ret;
}

EntityModifier* EntityModifierFactory::Synchronized(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2)
{
  SynchronizedEntityModifier* ret = EntityModifierManager::GetSynchronizedModifierAllocator()->Allocate();
  ret->Register(m0);
  ret->Register(m1);
  ret->Register(m2);
  ret->Prepare();
  return ret;
}

EntityModifier* EntityModifierFactory::Synchronized(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2, EntityModifier* m3)
{
  SynchronizedEntityModifier* ret = EntityModifierManager::GetSynchronizedModifierAllocator()->Allocate();
  ret->Register(m0);
  ret->Register(m1);
  ret->Register(m2);
  ret->Register(m3);
  ret->Prepare();
  return ret;
}

EntityModifier* EntityModifierFactory::Synchronized(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2, EntityModifier* m3, EntityModifier* m4)
{
  SynchronizedEntityModifier* ret = EntityModifierManager::GetSynchronizedModifierAllocator()->Allocate();
  ret->Register(m0);
  ret->Register(m1);
  ret->Register(m2);
  ret->Register(m3);
  ret->Register(m4);
  ret->Prepare();
  return ret;
}

//=======================================================================
// Loop
//=======================================================================
EntityModifier* EntityModifierFactory::Loop(EntityModifier* target, T_UINT8 loop_count)
{
  LoopEntityModifier* ret = EntityModifierManager::GetLoopModifierAllocator()->Allocate();
  ret->Prepare(target, loop_count);
  return ret;
}

//=======================================================================
// Delay
//=======================================================================
EntityModifier* EntityModifierFactory::Delay(T_FLOAT duration)
{
  DelayEntityModifier* const ret = EntityModifierManager::GetDelayModifierAllocator()->Allocate();
  ret->Prepare(duration);
  return ret;
}

//=======================================================================
// Delay
//=======================================================================
EntityModifier* EntityModifierFactory::Round(EntityModifier* target)
{
  RoundEntityModifier* const ret = EntityModifierManager::GetRoundModifierAllocator()->Allocate();
  ret->Prepare(target);
  return ret;
}

//=======================================================================
// ScaleBy
//=======================================================================
EntityModifier* EntityModifierFactory::ScaleBy(T_FLOAT duration, T_FLOAT value)
{
  return ScaleBy(duration, TVec2f(value, value));
}

EntityModifier* EntityModifierFactory::ScaleBy(T_FLOAT duration, const TVec2f& value)
{
  return Synchronized(
    ScaleByX(duration, value.x),
    ScaleByY(duration, value.y)
  );
}

EntityModifier* EntityModifierFactory::ScaleBy(T_FLOAT duration, const TVec3f& value)
{
  return Synchronized(
    ScaleByX(duration, value.x),
    ScaleByY(duration, value.y),
    ScaleByZ(duration, value.z)
  );
}
EntityModifier* EntityModifierFactory::ScaleByX(T_FLOAT duration, T_FLOAT value_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_X),
    AttributeEntityModifier::MODIFIER_OP_BY
    );
  return ret;
}

EntityModifier* EntityModifierFactory::ScaleByY(T_FLOAT duration, T_FLOAT value_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_Y),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ScaleByZ(T_FLOAT duration, T_FLOAT value_z)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_z,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_Z),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

//=======================================================================
// ScaleTo
//=======================================================================
EntityModifier* EntityModifierFactory::ScaleTo(T_FLOAT duration, T_FLOAT to)
{
  return ScaleTo(duration, TVec3f(to, to, to));
}

EntityModifier* EntityModifierFactory::ScaleTo(T_FLOAT duration, const TVec2f& to)
{
  return Synchronized(
    ScaleToX(duration, to.x),
    ScaleToY(duration, to.y)
  );
}

EntityModifier* EntityModifierFactory::ScaleTo(T_FLOAT duration, const TVec3f& to)
{
  return Synchronized(
    ScaleToX(duration, to.x),
    ScaleToY(duration, to.y),
    ScaleToZ(duration, to.z)
  );
}

EntityModifier* EntityModifierFactory::ScaleToX(T_FLOAT duration, T_FLOAT to_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_X),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ScaleToY(T_FLOAT duration,  T_FLOAT to_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_Y),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ScaleToZ(T_FLOAT duration, T_FLOAT to_z)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_z,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_Z),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

//=======================================================================
// ScaleFromBy
//=======================================================================
EntityModifier* EntityModifierFactory::ScaleFromBy(T_FLOAT duration, T_FLOAT from, T_FLOAT value)
{
  return ScaleFromBy(duration, TVec3f(from, from, from), TVec3f(value, value, value));
}

EntityModifier* EntityModifierFactory::ScaleFromBy(T_FLOAT duration, const TVec2f& from, const TVec2f& value)
{
  return Synchronized(
    ScaleFromByX(duration, from.x, value.x),
    ScaleFromByY(duration, from.y, value.y)
  );
}

EntityModifier* EntityModifierFactory::ScaleFromBy(T_FLOAT duration, const TVec3f& from, const TVec3f& value)
{
  return Synchronized(
    ScaleFromByX(duration, from.x, value.x),
    ScaleFromByY(duration, from.y, value.y),
    ScaleFromByZ(duration, from.z, value.z)
  );
}

EntityModifier* EntityModifierFactory::ScaleFromByX(T_FLOAT duration, T_FLOAT from_x, T_FLOAT value_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_x, value_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_X),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ScaleFromByY(T_FLOAT duration, T_FLOAT from_y, T_FLOAT value_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_y, value_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_Y),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ScaleFromByZ(T_FLOAT duration, T_FLOAT from_z, T_FLOAT value_z)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_z, value_z,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_Z),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

//=======================================================================
// ScaleFromTo
//=======================================================================
EntityModifier* EntityModifierFactory::ScaleFromTo(T_FLOAT duration, T_FLOAT from, T_FLOAT to)
{
  return ScaleFromTo(duration, TVec3f(from, from, from), TVec3f(to, to, to));
}

EntityModifier* EntityModifierFactory::ScaleFromTo(T_FLOAT duration, const TVec2f& from, const TVec2f& to)
{
  return Synchronized(
    ScaleFromToX(duration, from.x, to.x),
    ScaleFromToY(duration, from.y, to.y)
  );
}

EntityModifier* EntityModifierFactory::ScaleFromTo(T_FLOAT duration, const TVec3f& from, const TVec3f& to)
{
  return Synchronized(
    ScaleFromToX(duration, from.x, to.x),
    ScaleFromToY(duration, from.y, to.y),
    ScaleFromToZ(duration, from.z, to.z)
  );
}

EntityModifier* EntityModifierFactory::ScaleFromToX(T_FLOAT duration, T_FLOAT from_x, T_FLOAT to_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_x, to_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_X),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ScaleFromToY(T_FLOAT duration, T_FLOAT from_y, T_FLOAT to_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_y, to_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_Y),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ScaleFromToZ(T_FLOAT duration, T_FLOAT from_z, T_FLOAT to_z)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_z, to_z,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_Z),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

//=======================================================================
// TranslateBy
//=======================================================================
EntityModifier* EntityModifierFactory::TranslateBy(T_FLOAT duration, const TVec2f& value)
{
  return Synchronized(
    TranslateByX(duration, value.x),
    TranslateByY(duration, value.y)
  );
}

EntityModifier* EntityModifierFactory::TranslateBy(T_FLOAT duration, const TVec3f& value)
{
  return Synchronized(
    TranslateByX(duration, value.x),
    TranslateByY(duration, value.y),
    TranslateByZ(duration, value.z)
  );
}

EntityModifier* EntityModifierFactory::TranslateByX(T_FLOAT duration, T_FLOAT value_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_X),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

EntityModifier* EntityModifierFactory::TranslateByY(T_FLOAT duration, T_FLOAT value_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_Y),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

EntityModifier* EntityModifierFactory::TranslateByZ(T_FLOAT duration, T_FLOAT value_z)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_z,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_Z),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

//=======================================================================
// TranslateTo
//=======================================================================
EntityModifier* EntityModifierFactory::TranslateTo(T_FLOAT duration, const TVec2f& to)
{
  return Synchronized(
    TranslateToX(duration, to.x),
    TranslateToY(duration, to.y)
  );
}

EntityModifier* EntityModifierFactory::TranslateTo(T_FLOAT duration, const TVec3f& to)
{
  return Synchronized(
    TranslateToX(duration, to.x),
    TranslateToY(duration, to.y),
    TranslateToZ(duration, to.z)
  );
}

EntityModifier* EntityModifierFactory::TranslateToX(T_FLOAT duration, T_FLOAT to_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_X),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::TranslateToY(T_FLOAT duration, T_FLOAT to_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_Y),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::TranslateToZ(T_FLOAT duration, T_FLOAT to_z)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_z,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_Z),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

//=======================================================================
// TranslateFromBy
//=======================================================================
EntityModifier* EntityModifierFactory::TranslateFromBy(T_FLOAT duration, const TVec2f& from, const TVec2f& value)
{
  return Synchronized(
    TranslateFromByX(duration, from.x, value.x),
    TranslateFromByY(duration, from.y, value.y)
  );
}

EntityModifier* EntityModifierFactory::TranslateFromBy(T_FLOAT duration, const TVec3f& from, const TVec3f& value)
{
  return Synchronized(
    TranslateFromByX(duration, from.x, value.x),
    TranslateFromByY(duration, from.y, value.y),
    TranslateFromByZ(duration, from.z, value.z)
  );
}

EntityModifier* EntityModifierFactory::TranslateFromByX(T_FLOAT duration, T_FLOAT from_x, T_FLOAT value_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_x, value_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_X),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* EntityModifierFactory::TranslateFromByY(T_FLOAT duration, T_FLOAT from_y, T_FLOAT value_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_y, value_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_Y),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* EntityModifierFactory::TranslateFromByZ(T_FLOAT duration, T_FLOAT from_z, T_FLOAT value_z)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_z, value_z,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_Z),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

//=======================================================================
// TranslateFromTo
//=======================================================================
EntityModifier* EntityModifierFactory::TranslateFromTo(T_FLOAT duration, const TVec2f& from, const TVec2f& to)
{
  return Synchronized(
    TranslateFromToX(duration, from.x, to.x),
    TranslateFromToY(duration, from.y, to.y)
  );
}

EntityModifier* EntityModifierFactory::TranslateFromTo(T_FLOAT duration, const TVec3f& from, const TVec3f& to)
{
  return Synchronized(
    TranslateFromToX(duration, from.x, to.x),
    TranslateFromToY(duration, from.y, to.y),
    TranslateFromToZ(duration, from.z, to.z)
  );
}

EntityModifier* EntityModifierFactory::TranslateFromToX(T_FLOAT duration, T_FLOAT from_x, T_FLOAT to_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_x, to_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_X),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::TranslateFromToY(T_FLOAT duration, T_FLOAT from_y, T_FLOAT to_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_y, to_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_Y),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::TranslateFromToZ(T_FLOAT duration, T_FLOAT from_z, T_FLOAT to_z)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_z, to_z,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_Z),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

//=======================================================================
// RotationBy
//=======================================================================
EntityModifier* EntityModifierFactory::RotationBy(T_FLOAT duration, const TVec2f& value)
{
  return Synchronized(
    RotationByX(duration, value.x),
    RotationByY(duration, value.y)
  );
}

EntityModifier* EntityModifierFactory::RotationBy(T_FLOAT duration, const TVec3f& value)
{
  return Synchronized(
    RotationByX(duration, value.x),
    RotationByY(duration, value.y),
    RotationByZ(duration, value.z)
  );
}

EntityModifier* EntityModifierFactory::RotationByX(T_FLOAT duration, T_FLOAT value_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_ROTATE_X),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

EntityModifier* EntityModifierFactory::RotationByY(T_FLOAT duration, T_FLOAT value_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_ROTATE_Y),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

EntityModifier* EntityModifierFactory::RotationByZ(T_FLOAT duration, T_FLOAT value_z)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_z,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_ROTATE_Z),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

//=======================================================================
// RotationTo
//=======================================================================
EntityModifier* EntityModifierFactory::RotationTo(T_FLOAT duration, const TVec2f& to)
{
  return Synchronized(
    RotationToX(duration, to.x),
    RotationToY(duration, to.y)
  );
}

EntityModifier* EntityModifierFactory::RotationTo(T_FLOAT duration, const TVec3f& to)
{
  return Synchronized(
    RotationToX(duration, to.x),
    RotationToY(duration, to.y),
    RotationToZ(duration, to.z)
  );
}

EntityModifier* EntityModifierFactory::RotationToX(T_FLOAT duration, T_FLOAT to_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_ROTATE_X),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::RotationToY(T_FLOAT duration, T_FLOAT to_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_ROTATE_Y),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::RotationToZ(T_FLOAT duration, T_FLOAT to_z)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_z,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_ROTATE_Z),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

//=======================================================================
// RotationFromBy
//=======================================================================
EntityModifier* EntityModifierFactory::RotationFromBy(T_FLOAT duration, const TVec2f& from, const TVec2f& value)
{
  return Synchronized(
    RotationFromByX(duration, from.x, value.x),
    RotationFromByY(duration, from.y, value.y)
  );
}

EntityModifier* EntityModifierFactory::RotationFromBy(T_FLOAT duration, const TVec3f& from, const TVec3f& value)
{
  return Synchronized(
    RotationFromByX(duration, from.x, value.x),
    RotationFromByY(duration, from.y, value.y),
    RotationFromByZ(duration, from.z, value.z)
  );
}

EntityModifier* EntityModifierFactory::RotationFromByX(T_FLOAT duration, T_FLOAT from_x, T_FLOAT value_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_x, value_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_ROTATE_X),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* EntityModifierFactory::RotationFromByY(T_FLOAT duration, T_FLOAT from_y, T_FLOAT value_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_y, value_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_ROTATE_Y),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* EntityModifierFactory::RotationFromByZ(T_FLOAT duration, T_FLOAT from_z, T_FLOAT value_z)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_z, value_z,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_ROTATE_Z),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

//=======================================================================
// RotationFromTo
//=======================================================================
EntityModifier* EntityModifierFactory::RotationFromTo(T_FLOAT duration, const TVec2f& from, const TVec2f& to)
{
  return Synchronized(
    RotationFromToX(duration, from.x, to.x),
    RotationFromToY(duration, from.y, to.y)
  );
}

EntityModifier* EntityModifierFactory::RotationFromTo(T_FLOAT duration, const TVec3f& from, const TVec3f& to)
{
  return Synchronized(
    RotationFromToX(duration, from.x, to.x),
    RotationFromToY(duration, from.y, to.y),
    RotationFromToZ(duration, from.z, to.z)
  );
}

EntityModifier* EntityModifierFactory::RotationFromToX(T_FLOAT duration, T_FLOAT from_x, T_FLOAT to_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_x, to_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_ROTATE_X),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::RotationFromToY(T_FLOAT duration, T_FLOAT from_y, T_FLOAT to_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_y, to_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_ROTATE_Y),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::RotationFromToZ(T_FLOAT duration, T_FLOAT from_z, T_FLOAT to_z)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_z, to_z,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_ROTATE_Z),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

//=======================================================================
// ColorBy
//=======================================================================
EntityModifier* EntityModifierFactory::ColorBy(T_FLOAT duration, const TColor& value)
{
  return ColorBy(duration, value.r, value.g, value.b, value.a);
}

EntityModifier* EntityModifierFactory::ColorBy(T_FLOAT duration, T_FLOAT value_r, T_FLOAT value_g, T_FLOAT value_b, T_FLOAT value_a)
{
  return Synchronized(
    ColorByRed(duration, value_r),
    ColorByGreen(duration, value_g),
    ColorByBlue(duration, value_b),
    ColorByAlpha(duration, value_a)
  );
}

EntityModifier* EntityModifierFactory::ColorByRed(T_FLOAT duration, T_FLOAT value_r)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_r,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_R),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ColorByGreen(T_FLOAT duration, T_FLOAT value_g)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_g,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_G),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ColorByBlue(T_FLOAT duration, T_FLOAT value_b)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_b,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_B),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ColorByAlpha(T_FLOAT duration, T_FLOAT value_a)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_a,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_A),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

//=======================================================================
// ColorTo
//=======================================================================
EntityModifier* EntityModifierFactory::ColorTo(T_FLOAT duration, const TColor& to)
{
  return ColorTo(duration, to.r, to.g, to.b, to.a);
}

EntityModifier* EntityModifierFactory::ColorTo(T_FLOAT duration, T_FLOAT to_r, T_FLOAT to_g, T_FLOAT to_b, T_FLOAT to_a)
{
  return Synchronized(
    ColorToRed(duration, to_r),
    ColorToGreen(duration, to_g),
    ColorToBlue(duration, to_b),
    ColorToAlpha(duration, to_a)
  );
}

EntityModifier* EntityModifierFactory::ColorToRed(T_FLOAT duration, T_FLOAT to_r)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_r,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_R),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ColorToGreen(T_FLOAT duration, T_FLOAT to_g)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_g,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_G),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ColorToBlue(T_FLOAT duration, T_FLOAT to_b)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_b,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_B),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ColorToAlpha(T_FLOAT duration, T_FLOAT to_a)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_a,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_A),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

//=======================================================================
// ColorFromBy
//=======================================================================
EntityModifier* EntityModifierFactory::ColorFromBy(T_FLOAT duration, const TColor& from, const TColor& value)
{
  return ColorFromBy(
    duration,
    from.r, value.r,
    from.g, value.g,
    from.b, value.b,
    from.a, value.a
  );
}

EntityModifier* EntityModifierFactory::ColorFromBy(T_FLOAT duration, T_FLOAT from_r, T_FLOAT from_g, T_FLOAT from_b, T_FLOAT from_a, T_FLOAT value_r, T_FLOAT value_g, T_FLOAT value_b, T_FLOAT value_a)
{
  return Synchronized(
    ColorFromByRed(duration, from_r, value_r),
    ColorFromByGreen(duration, from_g, value_g),
    ColorFromByBlue(duration, from_b, value_b),
    ColorFromByAlpha(duration, from_a, value_a)
  );
}

EntityModifier* EntityModifierFactory::ColorFromByRed(T_FLOAT duration, T_FLOAT from_r, T_FLOAT value_r)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_r, value_r,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_R),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ColorFromByGreen(T_FLOAT duration, T_FLOAT from_g, T_FLOAT value_g)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_g, value_g,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_G),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ColorFromByBlue(T_FLOAT duration, T_FLOAT from_b, T_FLOAT value_b)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_b, value_b,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_B),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ColorFromByAlpha(T_FLOAT duration, T_FLOAT from_a, T_FLOAT value_a)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_a, value_a,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_A),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

//=======================================================================
// ColorFromTo
//=======================================================================
EntityModifier* EntityModifierFactory::ColorFromTo(T_FLOAT duration, const TColor& from, const TColor& to)
{
  return Synchronized(
    ColorFromToRed(duration,   from.r, to.r),
    ColorFromToGreen(duration, from.g, to.g),
    ColorFromToBlue(duration,  from.b, to.b),
    ColorFromToAlpha(duration, from.a, to.a)
  );
}

EntityModifier* EntityModifierFactory::ColorFromTo(T_FLOAT duration, T_FLOAT from_r, T_FLOAT from_g, T_FLOAT from_b, T_FLOAT from_a, T_FLOAT to_r, T_FLOAT to_g, T_FLOAT to_b, T_FLOAT to_a)
{
  return Synchronized(
    ColorFromToRed(duration, from_r, to_r),
    ColorFromToGreen(duration, from_g, to_g),
    ColorFromToBlue(duration, from_b, to_b),
    ColorFromToAlpha(duration, from_a, to_a)
  );
}

EntityModifier* EntityModifierFactory::ColorFromToRed(T_FLOAT duration, T_FLOAT from_r, T_FLOAT to_r)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_r, to_r,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_R),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ColorFromToGreen(T_FLOAT duration, T_FLOAT from_g, T_FLOAT to_g)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_g, to_g,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_G),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ColorFromToBlue(T_FLOAT duration, T_FLOAT from_b, T_FLOAT to_b)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_b, to_b,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_B),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

EntityModifier* EntityModifierFactory::ColorFromToAlpha(T_FLOAT duration, T_FLOAT from_a, T_FLOAT to_a)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_a, to_a,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_A),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}
