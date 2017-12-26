#pragma once

#include "Geometry.h"
#include "Color.h"
#include "EntityModifier.h"

namespace EntityModifierFactory
{
//=======================================================================
// Root
//=======================================================================
EntityModifierRoot* Root(EntityModifier* modifier);

//=======================================================================
// Sequence
//=======================================================================
EntityModifier* Sequence(EntityModifier* m0, EntityModifier* m1);
EntityModifier* Sequence(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2);
EntityModifier* Sequence(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2, EntityModifier* m3);
EntityModifier* Sequence(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2, EntityModifier* m3, EntityModifier* m4);

//=======================================================================
// Synchronized
//=======================================================================
EntityModifier* Synchronized(EntityModifier* m0, EntityModifier* m1);
EntityModifier* Synchronized(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2);
EntityModifier* Synchronized(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2, EntityModifier* m3);
EntityModifier* Synchronized(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2, EntityModifier* m3, EntityModifier* m4);

//=======================================================================
// Loop
//=======================================================================
EntityModifier* Loop(EntityModifier* target, T_UINT8 loop_count);

//=======================================================================
// Delay
//=======================================================================
EntityModifier* Delay(T_UINT32 duration);

//=======================================================================
// Round
//=======================================================================
EntityModifier* Round(EntityModifier* target);

//=======================================================================
// Scale
//=======================================================================
EntityModifier* ScaleMove(T_UINT32 duration, const TVec2f& value);
EntityModifier* ScaleMove(T_UINT32 duration, T_FLOAT value);
EntityModifier* ScaleMove(T_UINT32 duration, T_FLOAT value_x, T_FLOAT value_y);
EntityModifier* ScaleMoveX(T_UINT32 duration, T_FLOAT value_x);
EntityModifier* ScaleMoveY(T_UINT32 duration, T_FLOAT value_y);

EntityModifier* ScaleTo(T_UINT32 duration, const TVec2f& to);
EntityModifier* ScaleTo(T_UINT32 duration, T_FLOAT to);
EntityModifier* ScaleTo(T_UINT32 duration, T_FLOAT to_x, T_FLOAT to_y);
EntityModifier* ScaleToX(T_UINT32 duration, T_FLOAT to_x);
EntityModifier* ScaleToY(T_UINT32 duration, T_FLOAT to_y);

EntityModifier* ScaleFromMove(T_UINT32 duration, const TVec2f& from, const TVec2f& value);
EntityModifier* ScaleFromMove(T_UINT32 duration, T_FLOAT from, T_FLOAT value);
EntityModifier* ScaleFromMove(T_UINT32 duration, T_FLOAT from_x, T_FLOAT from_y, T_FLOAT value_x, T_FLOAT value_y);
EntityModifier* ScaleFromMoveX(T_UINT32 duration, T_FLOAT from_x, T_FLOAT value_x);
EntityModifier* ScaleFromMoveY(T_UINT32 duration, T_FLOAT from_y, T_FLOAT value_y);

EntityModifier* ScaleFromTo(T_UINT32 duration, const TVec2f& from, const TVec2f& to);
EntityModifier* ScaleFromTo(T_UINT32 duration, T_FLOAT from, T_FLOAT to);
EntityModifier* ScaleFromTo(T_UINT32 duration, T_FLOAT from_x, T_FLOAT from_y, T_FLOAT to_x, T_FLOAT to_y);
EntityModifier* ScaleFromToX(T_UINT32 duration, T_FLOAT from_x, T_FLOAT to_x);
EntityModifier* ScaleFromToY(T_UINT32 duration, T_FLOAT from_y, T_FLOAT to_y);

//=======================================================================
// Translate
//=======================================================================
EntityModifier* TranslateBy(T_UINT32 duration, const TVec2f& value);
EntityModifier* TranslateBy(T_UINT32 duration, T_FLOAT value);
EntityModifier* TranslateBy(T_UINT32 duration, T_FLOAT value_x, T_FLOAT value_y);
EntityModifier* TranslateByX(T_UINT32 duration, T_FLOAT value_x);
EntityModifier* TranslateByY(T_UINT32 duration, T_FLOAT value_y);

EntityModifier* TranslateTo(T_UINT32 duration, const TVec2f& to);
EntityModifier* TranslateTo(T_UINT32 duration, T_FLOAT to);
EntityModifier* TranslateTo(T_UINT32 duration, T_FLOAT to_x, T_FLOAT to_y);
EntityModifier* TranslateToX(T_UINT32 duration, T_FLOAT to_x);
EntityModifier* TranslateToY(T_UINT32 duration, T_FLOAT to_y);

EntityModifier* TranslateFromBy(T_UINT32 duration, const TVec2f& from, const TVec2f& value);
EntityModifier* TranslateFromBy(T_UINT32 duration, T_FLOAT from_x, T_FLOAT from_y, T_FLOAT value_x, T_FLOAT value_y);
EntityModifier* TranslateFromByX(T_UINT32 duration, T_FLOAT from_x, T_FLOAT value_x);
EntityModifier* TranslateFromByY(T_UINT32 duration, T_FLOAT from_y, T_FLOAT value_y);

EntityModifier* TranslateFromTo(T_UINT32 duration, const TVec2f& from, const TVec2f& to);
EntityModifier* TranslateFromTo(T_UINT32 duration, T_FLOAT from_x, T_FLOAT from_y, T_FLOAT to_x, T_FLOAT to_y);
EntityModifier* TranslateFromToX(T_UINT32 duration, T_FLOAT from_x, T_FLOAT to_x);
EntityModifier* TranslateFromToY(T_UINT32 duration, T_FLOAT from_y, T_FLOAT to_y);

//=======================================================================
// Rotation
//=======================================================================
EntityModifier* RotationBy(T_UINT32 duration, T_FLOAT value);

EntityModifier* RotationTo(T_UINT32 duration, T_FLOAT to);

EntityModifier* RotationFromBy(T_UINT32 duration, T_FLOAT from, T_FLOAT value);

EntityModifier* RotationFromTo(T_UINT32 duration, T_FLOAT from, T_FLOAT to);

//=======================================================================
// Color
//=======================================================================
EntityModifier* ColorBy(T_UINT32 duration, const Color& value);
EntityModifier* ColorBy(T_UINT32 duration, T_INT16 value_r, T_INT16 value_g, T_INT16 value_b, T_INT16 value_a);
EntityModifier* ColorByRed(T_UINT32 duration, T_INT16 value_r);
EntityModifier* ColorByGreen(T_UINT32 duration, T_INT16 value_g);
EntityModifier* ColorByBlue(T_UINT32 duration, T_INT16 value_b);
EntityModifier* ColorByAlpha(T_UINT32 duration, T_INT16 value_a);

EntityModifier* ColorTo(T_UINT32 duration, const Color& to);
EntityModifier* ColorTo(T_UINT32 duration, T_UINT8 to_r, T_UINT8 to_g, T_UINT8 to_b, T_UINT8 to_a);
EntityModifier* ColorToRed(T_UINT32 duration, T_UINT8 to_r);
EntityModifier* ColorToGreen(T_UINT32 duration, T_UINT8 to_g);
EntityModifier* ColorToBlue(T_UINT32 duration, T_UINT8 to_b);
EntityModifier* ColorToAlpha(T_UINT32 duration, T_UINT8 to_a);

EntityModifier* ColorFromBy(T_UINT32 duration, const Color& from, const Color& value);
EntityModifier* ColorFromBy(T_UINT32 duration, T_UINT8 from_r, T_UINT8 from_g, T_UINT8 from_b, T_UINT8 from_a, T_INT16 value_r, T_INT16 value_g, T_INT16 value_b, T_INT16 value_a);
EntityModifier* ColorFromByRed(T_UINT32 duration, T_UINT8 from_r, T_INT16 value_r);
EntityModifier* ColorFromByGreen(T_UINT32 duration, T_UINT8 from_g, T_INT16 value_g);
EntityModifier* ColorFromByBlue(T_UINT32 duration, T_UINT8 from_b, T_INT16 value_b);
EntityModifier* ColorFromByAlpha(T_UINT32 duration, T_UINT8 from_a, T_INT16 value_a);

EntityModifier* ColorFromTo(T_UINT32 duration, const Color& from, const Color& to);
EntityModifier* ColorFromTo(T_UINT32 duration, T_UINT8 from_r, T_UINT8 from_g, T_UINT8 from_b, T_UINT8 from_a, T_UINT8 to_r, T_UINT8 to_g, T_UINT8 to_b, T_UINT8 to_a);
EntityModifier* ColorFromToRed(T_UINT32 duration, T_UINT8 from_r, T_UINT8 to_r);
EntityModifier* ColorFromToGreen(T_UINT32 duration, T_UINT8 from_g, T_UINT8 to_g);
EntityModifier* ColorFromToBlue(T_UINT32 duration, T_UINT8 from_b, T_UINT8 to_b);
EntityModifier* ColorFromToAlpha(T_UINT32 duration, T_UINT8 from_a, T_UINT8 to_a);

}
