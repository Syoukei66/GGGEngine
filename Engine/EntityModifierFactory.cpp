#include "EntityModifierFactory.h"
#include "Moniker.h"

namespace EntityModifierFactory
{

//=======================================================================
// Root
//=======================================================================
EntityModifierRoot* Root(EntityModifier* modifier)
{
  EntityModifierRoot* ret = EntityModifierManager::GetInstance().GetModifierRootAllocator()->Allocate();
  ret->Prepare(modifier);
  return ret;
}

//=======================================================================
// Sequence
//=======================================================================
EntityModifier* Sequence(EntityModifier* m0, EntityModifier* m1)
{
  SequenceEntityModifier* ret = EntityModifierManager::GetInstance().GetSequenceModifierAllocator()->Allocate();
  ret->Register(m0);
  ret->Register(m1);
  ret->Prepare();
  return ret;
}

EntityModifier* Sequence(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2)
{
  SequenceEntityModifier* ret = EntityModifierManager::GetInstance().GetSequenceModifierAllocator()->Allocate();
  ret->Register(m0);
  ret->Register(m1);
  ret->Register(m2);
  ret->Prepare();
  return ret;
}

EntityModifier* Sequence(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2, EntityModifier* m3)
{
  SequenceEntityModifier* ret = EntityModifierManager::GetInstance().GetSequenceModifierAllocator()->Allocate();
  ret->Register(m0);
  ret->Register(m1);
  ret->Register(m2);
  ret->Register(m3);
  ret->Prepare();
  return ret;
}

EntityModifier* Sequence(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2, EntityModifier* m3, EntityModifier* m4)
{
  SequenceEntityModifier* ret = EntityModifierManager::GetInstance().GetSequenceModifierAllocator()->Allocate();
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
EntityModifier* Synchronized(EntityModifier* m0, EntityModifier* m1)
{
  SynchronizedEntityModifier* ret = EntityModifierManager::GetInstance().GetSynchronizedModifierAllocator()->Allocate();
  ret->Register(m0);
  ret->Register(m1);
  ret->Prepare();
  return ret;
}

EntityModifier* Synchronized(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2)
{
  SynchronizedEntityModifier* ret = EntityModifierManager::GetInstance().GetSynchronizedModifierAllocator()->Allocate();
  ret->Register(m0);
  ret->Register(m1);
  ret->Register(m2);
  ret->Prepare();
  return ret;
}

EntityModifier* Synchronized(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2, EntityModifier* m3)
{
  SynchronizedEntityModifier* ret = EntityModifierManager::GetInstance().GetSynchronizedModifierAllocator()->Allocate();
  ret->Register(m0);
  ret->Register(m1);
  ret->Register(m2);
  ret->Register(m3);
  ret->Prepare();
  return ret;
}

EntityModifier* Synchronized(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2, EntityModifier* m3, EntityModifier* m4)
{
  SynchronizedEntityModifier* ret = EntityModifierManager::GetInstance().GetSynchronizedModifierAllocator()->Allocate();
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
EntityModifier* Loop(EntityModifier* target, T_UINT8 loop_count)
{
  LoopEntityModifier* ret = EntityModifierManager::GetInstance().GetLoopModifierAllocator()->Allocate();
  ret->Prepare(target, loop_count);
  return ret;
}

//=======================================================================
// Delay
//=======================================================================
EntityModifier* Delay(T_UINT32 duration)
{
  DelayEntityModifier* const ret = EntityModifierManager::GetInstance().GetDelayModifierAllocator()->Allocate();
  ret->Prepare(duration);
  return ret;
}

//=======================================================================
// Delay
//=======================================================================
EntityModifier* Round(EntityModifier* target)
{
  RoundEntityModifier* const ret = EntityModifierManager::GetInstance().GetRoundModifierAllocator()->Allocate();
  ret->Prepare(target);
  return ret;
}

//=======================================================================
// Scale
//=======================================================================
EntityModifier* ScaleMove(T_UINT32 duration, const TVec2f& value)
{
  return ScaleMove(duration, value.x, value.y);
}

EntityModifier* ScaleMove(T_UINT32 duration, T_FLOAT value)
{
  return ScaleMove(duration, value, value);
}

EntityModifier* ScaleMove(T_UINT32 duration, T_FLOAT value_x, T_FLOAT value_y)
{
  return Synchronized(
    ScaleMoveX(duration, value_x),
    ScaleMoveY(duration, value_y)
  );
}

EntityModifier* ScaleMoveX(T_UINT32 duration, T_FLOAT value_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_X),
    AttributeEntityModifier::MODIFIER_OP_BY
    );
  return ret;
}

EntityModifier* ScaleMoveY(T_UINT32 duration, T_FLOAT value_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_Y),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

EntityModifier* ScaleTo(T_UINT32 duration, const TVec2f& to)
{
  return ScaleTo(duration, to.x, to.y);
}

EntityModifier* ScaleTo(T_UINT32 duration, T_FLOAT to)
{
  return ScaleTo(duration, to, to);
}

EntityModifier* ScaleTo(T_UINT32 duration, T_FLOAT to_x, T_FLOAT to_y)
{
  return Synchronized(
    ScaleToX(duration, to_x),
    ScaleToY(duration, to_y)
  );
}

EntityModifier* ScaleToX(T_UINT32 duration, T_FLOAT to_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_X),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* ScaleToY(T_UINT32 duration,  T_FLOAT to_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_Y),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* ScaleFromMove(T_UINT32 duration, const TVec2f& from, const TVec2f& value)
{
  return ScaleFromMove(duration, from.x, from.y, value.x, value.y);
}

EntityModifier* ScaleFromMove(T_UINT32 duration, T_FLOAT from, T_FLOAT value)
{
  return ScaleFromMove(duration, from, from, value, value);
}

EntityModifier* ScaleFromMove(T_UINT32 duration, T_FLOAT from_x, T_FLOAT from_y, T_FLOAT value_x, T_FLOAT value_y)
{
  return Synchronized(
    ScaleFromMoveX(duration, from_x, value_x),
    ScaleFromMoveY(duration, from_y, value_y)
  );
}

EntityModifier* ScaleFromMoveX(T_UINT32 duration, T_FLOAT from_x, T_FLOAT value_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_x, value_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_X),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* ScaleFromMoveY(T_UINT32 duration, T_FLOAT from_y, T_FLOAT value_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_y, value_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_Y),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* ScaleFromTo(T_UINT32 duration, const TVec2f& from, const TVec2f& to)
{
  return ScaleFromTo(duration, from.x, from.y, to.x, to.y);
}

EntityModifier* ScaleFromTo(T_UINT32 duration, T_FLOAT from, T_FLOAT to)
{
  return ScaleFromTo(duration, from, from, to, to);
}

EntityModifier* ScaleFromTo(T_UINT32 duration, T_FLOAT from_x, T_FLOAT from_y, T_FLOAT to_x, T_FLOAT to_y)
{
  return Synchronized(
    ScaleFromToX(duration, from_x, to_x),
    ScaleFromToY(duration, from_y, to_y)
  );
}

EntityModifier* ScaleFromToX(T_UINT32 duration, T_FLOAT from_x, T_FLOAT to_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_x, to_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_X),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

EntityModifier* ScaleFromToY(T_UINT32 duration, T_FLOAT from_y, T_FLOAT to_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_y, to_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_SCALE_Y),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

//=======================================================================
// Translate
//=======================================================================
EntityModifier* TranslateBy(T_UINT32 duration, const TVec2f & value)
{
  return TranslateBy(duration, value.x, value.y);
}

EntityModifier* TranslateBy(T_UINT32 duration, T_FLOAT value)
{
  return TranslateBy(duration, value, value);
}

EntityModifier* TranslateBy(T_UINT32 duration, T_FLOAT value_x, T_FLOAT value_y)
{
  return Synchronized(
    TranslateByX(duration, value_x),
    TranslateByY(duration, value_y)
  );
}

EntityModifier* TranslateByX(T_UINT32 duration, T_FLOAT value_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_X),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

EntityModifier* TranslateByY(T_UINT32 duration, T_FLOAT value_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_Y),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

EntityModifier* TranslateTo(T_UINT32 duration, const TVec2f & to)
{
  return TranslateTo(duration, to.x, to.y);
}

EntityModifier* TranslateTo(T_UINT32 duration, T_FLOAT to)
{
  return TranslateTo(duration, to, to);
}

EntityModifier* TranslateTo(T_UINT32 duration, T_FLOAT to_x, T_FLOAT to_y)
{
  return Synchronized(
    TranslateToX(duration, to_x),
    TranslateToY(duration, to_y)
  );
}

EntityModifier* TranslateToX(T_UINT32 duration, T_FLOAT to_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_X),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* TranslateToY(T_UINT32 duration, T_FLOAT to_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_Y),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* TranslateFromBy(T_UINT32 duration, const TVec2f& from, const TVec2f& value)
{
  return TranslateFromBy(duration, from.x, from.y, value.x, value.y);
}

EntityModifier* TranslateFromBy(T_UINT32 duration, T_FLOAT from_x, T_FLOAT from_y, T_FLOAT value_x, T_FLOAT value_y)
{
  return Synchronized(
    TranslateFromByX(duration, from_x, value_x),
    TranslateFromByY(duration, from_y, value_y)
  );
}

EntityModifier* TranslateFromByX(T_UINT32 duration, T_FLOAT from_x, T_FLOAT value_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_x, value_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_X),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* TranslateFromByY(T_UINT32 duration, T_FLOAT from_y, T_FLOAT value_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_y, value_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_Y),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* TranslateFromTo(T_UINT32 duration, const TVec2f& from, const TVec2f& to)
{
  return TranslateFromTo(duration, from.x, from.y, to.x, to.y);
}

EntityModifier* TranslateFromTo(T_UINT32 duration, T_FLOAT from_x, T_FLOAT from_y, T_FLOAT to_x, T_FLOAT to_y)
{
  return Synchronized(
    TranslateFromToX(duration, from_x, to_x),
    TranslateFromToY(duration, from_y, to_y)
  );
}

EntityModifier* TranslateFromToX(T_UINT32 duration, T_FLOAT from_x, T_FLOAT to_x)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_x, to_x,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_X),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

EntityModifier* TranslateFromToY(T_UINT32 duration, T_FLOAT from_y, T_FLOAT to_y)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_y, to_y,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_TRANSLATE_Y),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

//=======================================================================
// Rotation
//=======================================================================
EntityModifier* RotationBy(T_UINT32 duration, T_FLOAT value)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_ROTATION),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

EntityModifier* RotationTo(T_UINT32 duration, T_FLOAT to)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_ROTATION),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* RotationFromBy(T_UINT32 duration, T_FLOAT from, T_FLOAT value)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from, value,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_ROTATION),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* RotationFromTo(T_UINT32 duration, T_FLOAT from, T_FLOAT to)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from, to,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_ROTATION),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

//=======================================================================
// Color
//=======================================================================
EntityModifier* ColorBy(T_UINT32 duration, const Color4F& value)
{
  return ColorBy(duration, value.GetRed(), value.GetGreen(), value.GetBlue(), value.GetAlpha());
}

EntityModifier* ColorBy(T_UINT32 duration, T_FLOAT value_r, T_FLOAT value_g, T_FLOAT value_b, T_FLOAT value_a)
{
  return Synchronized(
    ColorByRed(duration, value_r),
    ColorByGreen(duration, value_g),
    ColorByBlue(duration, value_b),
    ColorByAlpha(duration, value_a)
  );
}

EntityModifier* ColorByRed(T_UINT32 duration, T_FLOAT value_r)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_r,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_R),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

EntityModifier* ColorByGreen(T_UINT32 duration, T_FLOAT value_g)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_g,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_G),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

EntityModifier* ColorByBlue(T_UINT32 duration, T_FLOAT value_b)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_b,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_B),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

EntityModifier* ColorByAlpha(T_UINT32 duration, T_FLOAT value_a)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, value_a,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_A),
    AttributeEntityModifier::MODIFIER_OP_BY
  );
  return ret;
}

EntityModifier* ColorTo(T_UINT32 duration, const Color4F& to)
{
  return ColorTo(duration, to.GetRed(), to.GetGreen(), to.GetBlue(), to.GetAlpha());
}

EntityModifier* ColorTo(T_UINT32 duration, T_FLOAT to_r, T_FLOAT to_g, T_FLOAT to_b, T_FLOAT to_a)
{
  return Synchronized(
    ColorToRed(duration, to_r),
    ColorToGreen(duration, to_g),
    ColorToBlue(duration, to_b),
    ColorToAlpha(duration, to_a)
  );
}

EntityModifier* ColorToRed(T_UINT32 duration, T_FLOAT to_r)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_r,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_R),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* ColorToGreen(T_UINT32 duration, T_FLOAT to_g)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_g,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_G),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* ColorToBlue(T_UINT32 duration, T_FLOAT to_b)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_b,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_B),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* ColorToAlpha(T_UINT32 duration, T_FLOAT to_a)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    0, to_a,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_A),
    AttributeEntityModifier::MODIFIER_OP_TO
  );
  return ret;
}

EntityModifier* ColorFromBy(T_UINT32 duration, const Color4F& from, const Color4F& value)
{
  return ColorFromBy(
    duration,
    from.GetRed(), value.GetRed(),
    from.GetGreen(), value.GetGreen(),
    from.GetBlue(), value.GetBlue(),
    from.GetAlpha(), value.GetAlpha()
  );
}

EntityModifier* ColorFromBy(T_UINT32 duration, T_FLOAT from_r, T_FLOAT from_g, T_FLOAT from_b, T_FLOAT from_a, T_FLOAT value_r, T_FLOAT value_g, T_FLOAT value_b, T_FLOAT value_a)
{
  return Synchronized(
    ColorFromByRed(duration, from_r, value_r),
    ColorFromByGreen(duration, from_g, value_g),
    ColorFromByBlue(duration, from_b, value_b),
    ColorFromByAlpha(duration, from_a, value_a)
  );
}

EntityModifier* ColorFromByRed(T_UINT32 duration, T_FLOAT from_r, T_FLOAT value_r)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_r, value_r,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_R),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* ColorFromByGreen(T_UINT32 duration, T_FLOAT from_g, T_FLOAT value_g)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_g, value_g,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_G),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* ColorFromByBlue(T_UINT32 duration, T_FLOAT from_b, T_FLOAT value_b)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_b, value_b,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_B),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* ColorFromByAlpha(T_UINT32 duration, T_FLOAT from_a, T_FLOAT value_a)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_a, value_a,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_A),
    AttributeEntityModifier::MODIFIER_OP_FROM_BY
  );
  return ret;
}

EntityModifier* ColorFromTo(T_UINT32 duration, const Color4F& from, const Color4F& to)
{
  return Synchronized(
    ColorFromToRed(duration, from.GetRed(), to.GetRed()),
    ColorFromToGreen(duration, from.GetGreen(), to.GetGreen()),
    ColorFromToBlue(duration, from.GetBlue(), to.GetBlue()),
    ColorFromToAlpha(duration, from.GetAlpha(), to.GetAlpha())
  );
}

EntityModifier* ColorFromTo(T_UINT32 duration, T_FLOAT from_r, T_FLOAT from_g, T_FLOAT from_b, T_FLOAT from_a, T_FLOAT to_r, T_FLOAT to_g, T_FLOAT to_b, T_FLOAT to_a)
{
  return Synchronized(
    ColorFromToRed(duration, from_r, to_r),
    ColorFromToGreen(duration, from_g, to_g),
    ColorFromToBlue(duration, from_b, to_b),
    ColorFromToAlpha(duration, from_a, to_a)
  );
}

EntityModifier* ColorFromToRed(T_UINT32 duration, T_FLOAT from_r, T_FLOAT to_r)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_r, to_r,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_R),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

EntityModifier* ColorFromToGreen(T_UINT32 duration, T_FLOAT from_g, T_FLOAT to_g)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_g, to_g,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_G),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

EntityModifier* ColorFromToBlue(T_UINT32 duration, T_FLOAT from_b, T_FLOAT to_b)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_b, to_b,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_B),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

EntityModifier* ColorFromToAlpha(T_UINT32 duration, T_FLOAT from_a, T_FLOAT to_a)
{
  AttributeEntityModifier* const ret = EntityModifierManager::GetInstance().GetAttributeModifierAllocator()->Allocate();
  ret->Prepare(duration,
    from_a, to_a,
    EntityModifierAttribute::Create(EntityModifierAttribute::MODIFIER_ATTR_COLOR_A),
    AttributeEntityModifier::MODIFIER_OP_FROM_TO
  );
  return ret;
}

}
