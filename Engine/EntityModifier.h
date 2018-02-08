#pragma once

#include <vector>
#include "UpdateEvent.h"
#include "EasingFunction.h"
#include "EntityModifierAttribute.h"
#include "PoolAllocator.h"

class GameObject2D;
class EntityModifier;
class EntityModifierRoot;

class IEntityModifierListener
{
public:
  virtual void OnModifierFinished(EntityModifierRoot* root, GameObject2D* target) = 0;
};

//=========================================================================
// EntityModifierRoot
// EntityModifier�̃c���[�̃��[�g�ɓ����镔��
//=========================================================================
class EntityModifierRoot : public IPoolAllocatable
{
public:
  virtual void OnAllocated();
  virtual void OnFree();
  virtual bool OnUpdate(T_UINT16 frame_elapsed);
  void OnUpdateFinish();
  void Prepare(EntityModifier* modifier);
  void OnAttached(GameObject2D* target);
  void OnDetached();
  inline void Retain()
  {
    this->reference_count_++;
  }
  void Release();
  void OnRelease();
  void OnFinish();

  void Play();
  void Reverse();
  void Pause();
  void Resume();
  void Stop();

public:
  void AddEntityModifierListener(IEntityModifierListener* listener);
  void RemoveEntityModifierListener(IEntityModifierListener* listener);
  void ClearEntityModifierListener();

public:
  bool IsFinished();
  inline const GameObject2D* GetTargetEntity() const
  {
    return this->target_;
  }
  bool IsAttached() const
  {
    return this->target_ != NULL;
  }
  inline void SetLoop(bool loop)
  {
    this->is_loop_ = loop;
  }

private:
  GameObject2D* target_;
  EntityModifier* modifier_;

  bool is_loop_;
  bool is_pause_;
  bool is_reverse_;
  T_UINT16 duration_;
  T_UINT16 duration_rest_;

  T_UINT8 reference_count_;
  std::deque<IEntityModifierListener*> listeners_;
};

//=========================================================================
// EntityModifier
// Entity�ɑ΂��Ă̕ύX���A�b�v�f�[�g���Ɏ����I�ɍs��
//=========================================================================
class EntityModifier : public IPoolAllocatable
{
public:
  //�C���X�^���X�̏�����
  virtual void OnAllocated();
  virtual void Free() = 0;
  virtual void OnUpdate(GameObject2D* target, T_FLOAT progress);
  
protected:
  //�h���N���X��Prepare���\�b�h�ŕK���Ăяo��
  virtual void BasePrepare(T_UINT16 duration);

protected:
  virtual void OnTimelineUpdate(GameObject2D* target, T_FLOAT progress) = 0;
  
public:
  inline void SetEasingFunction(T_UINT8 func, T_UINT8 op)
  {
    this->easing_func_ = func;
    this->easing_operator_ = op;
  }
  inline T_UINT16 GetDuration() const
  {
    return this->duration_;
  }

private:
  T_UINT16 duration_;

  T_UINT8 easing_func_;
  T_UINT8 easing_operator_;
};

//=========================================================================
// DelayEntityModifier
// duration�̊ԉ������Ȃ�
//=========================================================================
class DelayEntityModifier : public EntityModifier
{
public:
  virtual void OnFree() override;
  virtual void Free() override;

protected:
  virtual void OnTimelineUpdate(GameObject2D* target, T_FLOAT progress) override;

public:
  void Prepare(T_UINT16 duration);
};

//=========================================================================
// SequenceEntityModifier
// ������Modifier��z��œn���A���ԂɎ��s����
//=========================================================================
class SequenceEntityModifier : public EntityModifier
{
public:
  virtual void OnAllocated() override;
  virtual void OnFree() override;
  virtual void Free() override;

protected:
  virtual void OnTimelineUpdate(GameObject2D* target, T_FLOAT progress) override;

public:
  void Register(EntityModifier* modifier);
  void Prepare();

private:
  std::vector<EntityModifier*> modifiers_;
};

//=========================================================================
// SynchronizedEntityModifier
// ������Modifier��n���A�����Ɏ��s����
//=========================================================================
class SynchronizedEntityModifier : public EntityModifier
{
public:
  virtual void OnAllocated() override;
  virtual void OnFree() override;
  virtual void Free() override;

protected:
  virtual void OnTimelineUpdate(GameObject2D* target, T_FLOAT progress) override;

public:
  void Register(EntityModifier* modifier);
  void Prepare();

private:
  std::vector<EntityModifier*> modifiers_;
};

//=========================================================================
// LoopEntityModifier
// �Z�b�g����Modifier���w�肵���񐔂������s����
// �������[�v�̃T�|�[�g�͍s��Ȃ��B�������[�v���s�������ꍇ��
// EntityModifierRoot��SetLoop()���\�b�h���Ăяo���B
//=========================================================================
class LoopEntityModifier : public EntityModifier
{
public:
  virtual void OnAllocated() override;
  virtual void OnFree() override;
  virtual void Free() override;

protected:
  virtual void OnTimelineUpdate(GameObject2D* target, T_FLOAT progress) override;

public:
  void Prepare(EntityModifier* modifier, T_UINT8 loop_count);

private:
  EntityModifier* modifier_;
  T_UINT8 loop_count_;
};

//=========================================================================
// RoundEntityModifier
// Modifier�����s������A�t�Đ��ōĎ��s����
//=========================================================================
class RoundEntityModifier : public EntityModifier
{
public:
  virtual void OnAllocated() override;
  virtual void OnFree() override;
  virtual void Free() override;

protected:
  virtual void OnTimelineUpdate(GameObject2D* target, T_FLOAT progress) override;

public:
  void Prepare(EntityModifier* modifier);

private:
  EntityModifier* modifier_;
};

//=========================================================================
// AttributeEntityModifier
// �w�肵��Attribute����p����Entity�̏�Ԃ����ۂɕω������Ă���Modifier
//=========================================================================
class AttributeEntityModifier : public EntityModifier
{
public:
  enum OperatorID
  {
    //arg0 = 0, arg1 = val
    MODIFIER_OP_BY,
    //arg0 = 0, arg1 = to
    MODIFIER_OP_TO,
    //arg0 = from, arg1 = val
    MODIFIER_OP_FROM_BY,
    //arg0 = from, arg1 = to
    MODIFIER_OP_FROM_TO,
    //arg0 = from, arg1 = val
    MODIFIER_OP_ADD,
    //arg0 = from, arg1 = val
    MODIFIER_OP_SUB,
    //arg0 = from, arg1 = val
    MODIFIER_OP_MUL,
    //arg0 = from, arg1 = val
    MODIFIER_OP_DIV,

    MODIFIER_OP_DATANUM,
  };

public:
  virtual void OnAllocated() override;
  virtual void OnFree() override;
  virtual void Free() override;

protected:
  virtual void OnTimelineUpdate(GameObject2D* target, T_FLOAT progress) override;

public:
  void Prepare(T_UINT16 duration, T_FLOAT arg0, T_FLOAT arg1, const EntityModifierAttribute* attr, T_UINT8 op);

protected:
  T_FLOAT arg0_;
  T_FLOAT arg1_;

  const EntityModifierAttribute* attribute_;
  T_UINT8 rate_operator_;
};

//=========================================================================
// AttributeEntityModifierEX
// �w�肵��Attribute����p����Entity�̏�Ԃ����ۂɕω������Ă���Modifier
// �ɍX�ɑ�Entity�̒l�𗘗p����to�̒l��ω������Ă����@�\��ǉ���������
//=========================================================================
class AttributeEntityModifierEx : public AttributeEntityModifier
{
public:
  AttributeEntityModifierEx();

public:
  virtual void OnAllocated() override;
  virtual void OnFree() override;
  virtual void Free() override;

protected:
  virtual void OnTimelineUpdate(GameObject2D* target, T_FLOAT progress);

public:
  void Prepare(T_UINT16 duration, T_FLOAT arg0, T_FLOAT arg1, const EntityModifierAttribute* attr, T_UINT8 op, GameObject2D* other, const EntityModifierAttribute* other_attr);

protected:
  GameObject2D* other_;
  const EntityModifierAttribute* other_attribute_;
};

