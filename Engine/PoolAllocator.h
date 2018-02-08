#pragma once

#include <list>
#include <deque>
#include <functional>
#include "NativeType.h"

//=======================================================================================
// PoolAllocator���g�p����ׂ̗v��
// (1) ���������̃R���X�g���N�^���p�ӂ���Ă���
// (2) new T()���\ (���ۃN���X�ł͂Ȃ�)
// (3) �C���X�^���X�������p�֐� void OnAllocated() ���p�ӂ���Ă���
// (4) �C���X�^���X�I�������֐� void OnFree() ���p�ӂ���Ă���
// (3)(4)�ɂ��Ă͎����ׂ̈̃C���^�[�t�F�[�X��p�ӂ����̂ŗ��p����悤��
//=======================================================================================
class IPoolAllocatable
{
public:
  virtual void OnAllocated() = 0;
  virtual void OnFree() = 0;
};



template<class T>
class PoolAllocator
{
// �����ɃR���N�V�����̌^��ύX�ł��違
// ���p���Ă���R�[�h�ɉe����^���Ȃ��悤��
// �R���N�V�����̌^��typedef���Ă����̂�����
// public:
//  typedef std::vector<T> PoolList;
//  typedef std::vector<T> AllocatedList;
//
public:
  PoolAllocator(T_UINT16 count)
    : pool_(count)
    , allocated_()
  {
    for (T_UINT16 i = 0; i < count; ++i)
    {
      this->pool_[i] = new T();
    }
  }

  ~PoolAllocator()
  {
    for (typename std::list<T*>::iterator itr = this->allocated_.begin(); itr != this->allocated_.end(); ++itr)
    {
      (*itr)->OnFree();
      delete (*itr);
    }
    this->allocated_.clear();
    for (typename std::deque<T*>::iterator itr = this->pool_.begin(); itr != this->pool_.end(); ++itr)
    {
      delete (*itr);
    }
    this->pool_.clear();
  }
  T* Allocate()
  {
    if (this->pool_.size() == 0)
    {
      return nullptr;
    }
    T* ret = this->pool_.back();
    this->pool_.pop_back();
    this->allocated_.push_back(ret);
    ret->OnAllocated();
    return ret;
  }
  void Free(T* p)
  {
    for (typename std::list<T*>::iterator itr = this->allocated_.begin(); itr != this->allocated_.end(); ++itr)
    {
      if ((*itr) != p)
      {
        continue;
      }
      this->allocated_.erase(itr);
      p->OnFree();
      this->pool_.push_back(p);
      return;
    }
  }
  void Clear()
  {
    for (typename std::list<T*>::iterator itr = this->allocated_.begin(); itr != this->allocated_.end(); ++itr)
    {
      (*itr)->OnFree();
      this->pool_.push_back((*itr));
    }
    this->allocated_.clear();
  }
  T* front()
  {
    return this->allocated_.front();
  }
  T* back()
  {
    return this->allocated_.back();
  }
  typename std::list<T*>::iterator begin()
  {
    return this->allocated_.begin();
  }
  typename std::list<T*>::iterator end()
  {
    return this->allocated_.end();
  }
  typename std::list<T*>::const_iterator begin() const
  {
    return this->allocated_.begin();
  }
  typename std::list<T*>::const_iterator end() const
  {
    return this->allocated_.end();
  }
  typename std::list<T*>::iterator erase(typename std::list<T*>::iterator itr)
  {
    T* p = (*itr);
    std::list<T*>::iterator ret = this->allocated_.erase(itr);
    p->OnFree();
    this->pool_.push_back(p);
    return ret;
  }
  typename std::deque<T*>::iterator PoolBegin()
  {
    return this->pool_.begin();
  }
  typename std::deque<T*>::iterator PoolEnd()
  {
    return this->pool_.end();
  }
  typename std::deque<T*>::const_iterator PoolBegin() const
  {
    return this->pool_.begin();
  }
  typename std::deque<T*>::const_iterator PoolEnd() const
  {
    return this->pool_.end();
  }
  inline T_UINT16 GetPoolSize() const
  {
    return (T_UINT16)(this->pool_.size() + this->allocated_.size());
  }
  inline T_UINT16 GetAllocatedCount() const
  {
    return (T_UINT16)this->allocated_.size();
  }
private:
  //
  typename std::deque<T*> pool_;
  //�Q�[�����͓r�������̗v�f�̍폜���p�ɂɍs�����
  typename std::list<T*> allocated_;
};

