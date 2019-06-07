#pragma once

#include "EntityModifier.h"

namespace EntityModifierFactory
{
//=======================================================================
// Root
//=======================================================================
EntityModifierRoot* Root(EntityModifier* modifier);

//=======================================================================
// Sequence
// �n���ꂽModifier�����ԂɎ��s
//=======================================================================
EntityModifier* Sequence(EntityModifier* m0, EntityModifier* m1);
EntityModifier* Sequence(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2);
EntityModifier* Sequence(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2, EntityModifier* m3);
EntityModifier* Sequence(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2, EntityModifier* m3, EntityModifier* m4);

//=======================================================================
// Synchronized
// �n���ꂽModifier�����Ɏ��s
//=======================================================================
EntityModifier* Synchronized(EntityModifier* m0, EntityModifier* m1);
EntityModifier* Synchronized(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2);
EntityModifier* Synchronized(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2, EntityModifier* m3);
EntityModifier* Synchronized(EntityModifier* m0, EntityModifier* m1, EntityModifier* m2, EntityModifier* m3, EntityModifier* m4);

//=======================================================================
// Loop
// �n���ꂽModifier���w�肵���񐔂������[�v
//=======================================================================
EntityModifier* Loop(EntityModifier* target, T_UINT8 loop_count);

//=======================================================================
// Delay
// duration�b�Ȃɂ����Ȃ�
//=======================================================================
EntityModifier* Delay(T_FLOAT duration);

//=======================================================================
// Round
// �n���ꂽModifier���Đ���A�t�Đ�����
//=======================================================================
EntityModifier* Round(EntityModifier* target);

//=======================================================================
// ScaleBy
// ���݂̃X�P�[������duration�b������value�����X�P�[�����O
//=======================================================================
EntityModifier* ScaleBy(T_FLOAT duration, T_FLOAT value);
EntityModifier* ScaleBy(T_FLOAT duration, const TVec2f& value);
EntityModifier* ScaleBy(T_FLOAT duration, const TVec3f& value);
EntityModifier* ScaleByX(T_FLOAT duration, T_FLOAT value_x);
EntityModifier* ScaleByY(T_FLOAT duration, T_FLOAT value_y);
EntityModifier* ScaleByZ(T_FLOAT duration, T_FLOAT value_z);

//=======================================================================
// ScaleTo
// ���݂̃X�P�[������duration�b������to�փX�P�[�����O
//=======================================================================
EntityModifier* ScaleTo(T_FLOAT duration, T_FLOAT to);
EntityModifier* ScaleTo(T_FLOAT duration, const TVec2f& to);
EntityModifier* ScaleTo(T_FLOAT duration, const TVec3f& to);
EntityModifier* ScaleToX(T_FLOAT duration, T_FLOAT to_x);
EntityModifier* ScaleToY(T_FLOAT duration, T_FLOAT to_y);
EntityModifier* ScaleToZ(T_FLOAT duration, T_FLOAT to_z);

//=======================================================================
// ScaleFromBy
// from�X�P�[������duration�b������value�����X�P�[�����O
//=======================================================================
EntityModifier* ScaleFromBy(T_FLOAT duration, T_FLOAT from, T_FLOAT value);
EntityModifier* ScaleFromBy(T_FLOAT duration, const TVec2f& from, const TVec2f& value);
EntityModifier* ScaleFromBy(T_FLOAT duration, const TVec3f& from, const TVec3f& value);
EntityModifier* ScaleFromByX(T_FLOAT duration, T_FLOAT from_x, T_FLOAT value_x);
EntityModifier* ScaleFromByY(T_FLOAT duration, T_FLOAT from_y, T_FLOAT value_y);
EntityModifier* ScaleFromByZ(T_FLOAT duration, T_FLOAT from_z, T_FLOAT value_z);

//=======================================================================
// ScaleFromTo
// from�X�P�[������duration�b������To�փX�P�[�����O
//=======================================================================
EntityModifier* ScaleFromTo(T_FLOAT duration, T_FLOAT from, T_FLOAT to);
EntityModifier* ScaleFromTo(T_FLOAT duration, const TVec2f& from, const TVec2f& to);
EntityModifier* ScaleFromTo(T_FLOAT duration, const TVec3f& from, const TVec3f& to);
EntityModifier* ScaleFromToX(T_FLOAT duration, T_FLOAT from_x, T_FLOAT to_x);
EntityModifier* ScaleFromToY(T_FLOAT duration, T_FLOAT from_y, T_FLOAT to_y);
EntityModifier* ScaleFromToZ(T_FLOAT duration, T_FLOAT from_z, T_FLOAT to_z);

//=======================================================================
// TranslateBy
// ���݂̈ʒu����duration�b������value�����ړ�
//=======================================================================
EntityModifier* TranslateBy(T_FLOAT duration, const TVec2f& value);
EntityModifier* TranslateBy(T_FLOAT duration, const TVec3f& value);
EntityModifier* TranslateByX(T_FLOAT duration, T_FLOAT value_x);
EntityModifier* TranslateByY(T_FLOAT duration, T_FLOAT value_y);
EntityModifier* TranslateByZ(T_FLOAT duration, T_FLOAT value_z);

//=======================================================================
// TranslateTo
// ���݂̈ʒu����duration�b������to�ֈړ�
//=======================================================================
EntityModifier* TranslateTo(T_FLOAT duration, const TVec2f& to);
EntityModifier* TranslateTo(T_FLOAT duration, const TVec3f& to);
EntityModifier* TranslateToX(T_FLOAT duration, T_FLOAT to_x);
EntityModifier* TranslateToY(T_FLOAT duration, T_FLOAT to_y);
EntityModifier* TranslateToZ(T_FLOAT duration, T_FLOAT to_z);

//=======================================================================
// TranslateFromBy
// from�ʒu����duration�b������value�����ړ�
//=======================================================================
EntityModifier* TranslateFromBy(T_FLOAT duration, const TVec2f& from, const TVec2f& value);
EntityModifier* TranslateFromBy(T_FLOAT duration, const TVec3f& from, const TVec3f& value);
EntityModifier* TranslateFromByX(T_FLOAT duration, T_FLOAT from_x, T_FLOAT value_x);
EntityModifier* TranslateFromByY(T_FLOAT duration, T_FLOAT from_y, T_FLOAT value_y);
EntityModifier* TranslateFromByZ(T_FLOAT duration, T_FLOAT from_z, T_FLOAT value_z);

//=======================================================================
// TranslateFromTo
// from�ʒu����duration�b������To�ֈړ�
//=======================================================================
EntityModifier* TranslateFromTo(T_FLOAT duration, const TVec2f& from, const TVec2f& to);
EntityModifier* TranslateFromTo(T_FLOAT duration, const TVec3f& from, const TVec3f& to);
EntityModifier* TranslateFromToX(T_FLOAT duration, T_FLOAT from_x, T_FLOAT to_x);
EntityModifier* TranslateFromToY(T_FLOAT duration, T_FLOAT from_y, T_FLOAT to_y);
EntityModifier* TranslateFromToZ(T_FLOAT duration, T_FLOAT from_z, T_FLOAT to_z);

//=======================================================================
// RotationBy
// ���݂̊p�x����duration�b������value�x������]
//=======================================================================
EntityModifier* RotationBy(T_FLOAT duration, const TVec2f& value);
EntityModifier* RotationBy(T_FLOAT duration, const TVec3f& value);
EntityModifier* RotationByX(T_FLOAT duration, T_FLOAT value_x);
EntityModifier* RotationByY(T_FLOAT duration, T_FLOAT value_y);
EntityModifier* RotationByZ(T_FLOAT duration, T_FLOAT value_z);

//=======================================================================
// RotationTo
// ���݂̊p�x����duration�b������to�x�։�]
//=======================================================================
EntityModifier* RotationTo(T_FLOAT duration, const TVec2f& to);
EntityModifier* RotationTo(T_FLOAT duration, const TVec3f& to);
EntityModifier* RotationToX(T_FLOAT duration, T_FLOAT to_x);
EntityModifier* RotationToY(T_FLOAT duration, T_FLOAT to_y);
EntityModifier* RotationToZ(T_FLOAT duration, T_FLOAT to_z);

//=======================================================================
// RotationFromBy
// from�p�x����duration�b������value�x������]
//=======================================================================
EntityModifier* RotationFromBy(T_FLOAT duration, const TVec2f& from, const TVec2f& value);
EntityModifier* RotationFromBy(T_FLOAT duration, const TVec3f& from, const TVec3f& value);
EntityModifier* RotationFromByX(T_FLOAT duration, T_FLOAT from_x, T_FLOAT value_x);
EntityModifier* RotationFromByY(T_FLOAT duration, T_FLOAT from_y, T_FLOAT value_y);
EntityModifier* RotationFromByZ(T_FLOAT duration, T_FLOAT from_z, T_FLOAT value_z);

//=======================================================================
// RotationFromTo
// from�p�x����duration�b������To�x�։�]
//=======================================================================
EntityModifier* RotationFromTo(T_FLOAT duration, const TVec2f& from, const TVec2f& to);
EntityModifier* RotationFromTo(T_FLOAT duration, const TVec3f& from, const TVec3f& to);
EntityModifier* RotationFromToX(T_FLOAT duration, T_FLOAT from_x, T_FLOAT to_x);
EntityModifier* RotationFromToY(T_FLOAT duration, T_FLOAT from_y, T_FLOAT to_y);
EntityModifier* RotationFromToZ(T_FLOAT duration, T_FLOAT from_z, T_FLOAT to_z);

//=======================================================================
// ColorBy
//=======================================================================
EntityModifier* ColorBy(T_FLOAT duration, const TColor& value);
EntityModifier* ColorBy(T_FLOAT duration, T_FLOAT value_r, T_FLOAT value_g, T_FLOAT value_b, T_FLOAT value_a);
EntityModifier* ColorByRed(T_FLOAT duration, T_FLOAT value_r);
EntityModifier* ColorByGreen(T_FLOAT duration, T_FLOAT value_g);
EntityModifier* ColorByBlue(T_FLOAT duration, T_FLOAT value_b);
EntityModifier* ColorByAlpha(T_FLOAT duration, T_FLOAT value_a);

//=======================================================================
// ColorTo
//=======================================================================
EntityModifier* ColorTo(T_FLOAT duration, const TColor& to);
EntityModifier* ColorTo(T_FLOAT duration, T_FLOAT to_r, T_FLOAT to_g, T_FLOAT to_b, T_FLOAT to_a);
EntityModifier* ColorToRed(T_FLOAT duration, T_FLOAT to_r);
EntityModifier* ColorToGreen(T_FLOAT duration, T_FLOAT to_g);
EntityModifier* ColorToBlue(T_FLOAT duration, T_FLOAT to_b);
EntityModifier* ColorToAlpha(T_FLOAT duration, T_FLOAT to_a);

//=======================================================================
// ColorFromBy
//=======================================================================
EntityModifier* ColorFromBy(T_FLOAT duration, const TColor& from, const TColor& value);
EntityModifier* ColorFromBy(T_FLOAT duration, T_FLOAT from_r, T_FLOAT from_g, T_FLOAT from_b, T_FLOAT from_a, T_FLOAT value_r, T_FLOAT value_g, T_FLOAT value_b, T_FLOAT value_a);
EntityModifier* ColorFromByRed(T_FLOAT duration, T_FLOAT from_r, T_FLOAT value_r);
EntityModifier* ColorFromByGreen(T_FLOAT duration, T_FLOAT from_g, T_FLOAT value_g);
EntityModifier* ColorFromByBlue(T_FLOAT duration, T_FLOAT from_b, T_FLOAT value_b);
EntityModifier* ColorFromByAlpha(T_FLOAT duration, T_FLOAT from_a, T_FLOAT value_a);

//=======================================================================
// ColorFromTo
//=======================================================================
EntityModifier* ColorFromTo(T_FLOAT duration, const TColor& from, const TColor& to);
EntityModifier* ColorFromTo(T_FLOAT duration, T_FLOAT from_r, T_FLOAT from_g, T_FLOAT from_b, T_FLOAT from_a, T_FLOAT to_r, T_FLOAT to_g, T_FLOAT to_b, T_FLOAT to_a);
EntityModifier* ColorFromToRed(T_FLOAT duration, T_FLOAT from_r, T_FLOAT to_r);
EntityModifier* ColorFromToGreen(T_FLOAT duration, T_FLOAT from_g, T_FLOAT to_g);
EntityModifier* ColorFromToBlue(T_FLOAT duration, T_FLOAT from_b, T_FLOAT to_b);
EntityModifier* ColorFromToAlpha(T_FLOAT duration, T_FLOAT from_a, T_FLOAT to_a);

}
