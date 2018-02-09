#pragma once

#include <vector>
#include "UpdateEvent.h"
#include "EasingFunction.h"
#include "EntityModifierAttribute.h"
#include "PoolAllocator.h"

class GameObject2D;
class EntityModifier;

//=========================================================================
// EntityModifierRoot
// EntityModifierのツリーのルートに当たる部分
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
  void AddEntityModifierListener(std::function<void()> listener);
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
  std::deque<std::function<void()>> listeners_;
};

//=========================================================================
// EntityModifier
// Entityに対しての変更をアップデート時に自動的に行う
//=========================================================================
class EntityModifier : public IPoolAllocatable
{
public:
  //インスタンスの初期化
  virtual void OnAllocated();
  virtual void Free() = 0;
  virtual void OnUpdate(GameObject2D* target, T_FLOAT progress);
  
protected:
  //派生クラスのPrepareメソッドで必ず呼び出す
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
// durationの間何もしない
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
// 複数のModifierを配列で渡し、順番に実行する
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
// 複数のModifierを渡し、同時に実行する
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
// セットしたModifierを指定した回数だけ実行する
// 無限ループのサポートは行わない。無限ループを行いたい場合は
// EntityModifierRootでSetLoop()メソッドを呼び出す。
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
// Modifierを実行した後、逆再生で再実行する
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
// 指定したAttribute等を用いてEntityの状態を実際に変化させていくModifier
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
// 指定したAttribute等を用いてEntityの状態を実際に変化させていくModifier
// に更に他Entityの値を利用してtoの値を変化させていく機能を追加したもの
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

