#pragma once

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
    for (T* p : this->allocated_)
    {
      p->OnFree();
      delete p;
    }
    this->allocated_.clear();
    for (T* p : this->pool_)
    {
      delete p;
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
    this->allocated_.emplace_back(ret);
    ret->OnAllocated();
    return ret;
  }
  void Free(T* p)
  {
    for (typename std::list<T*>::iterator& itr = this->allocated_.begin(); itr != this->allocated_.end(); ++itr)
    {
      if ((*itr) != p)
      {
        continue;
      }
      this->allocated_.erase(itr);
      p->OnFree();
      this->pool_.emplace_back(p);
      return;
    }
  }
  void Clear()
  {
    for (T* p : this->allocated_)
    {
      p->OnFree();
      this->pool_.emplace_back(p);
    }
    this->allocated_.clear();
  }
  typename std::list<T*>::iterator erase(typename std::list<T*>::iterator itr)
  {
    T* p = (*itr);
    typename std::list<T*>::iterator ret = this->allocated_.erase(itr);
    p->OnFree();
    this->pool_.emplace_back(p);
    return ret;
  }
  void Loop(std::function<void(T*)> func)
  {
    for (T* p : this->allocated_)
    {
      func(p);
    }
  }
  void LoopIncludingPool(std::function<void(T*)> func)
  {
    for (T* p : this->allocated_)
    {
      func(p);
    }
    for (T* p : this->pool_)
    {
      func(p);
    }
  }
  T* Select(std::function<bool(T*)> condition)
  {
    for (T* p : this->allocated_)
    {
      if (condition(p))
      {
        return p;
      }
    }
    return nullptr;
  }
  void SelectAll(std::deque<T*>* dest, std::function<bool(T*)> condition)
  {
    for (T* p : this->allocated_)
    {
      if (condition(p))
      {
        dest->emplace_back(p);
      }
    }
  }
  void RemoveIf(std::function<bool(T*)> condition)
  {
    for (typename std::list<T*>::iterator itr = this->allocated_.begin(); itr != this->allocated_.end();)
    {
      if (condition((*itr)))
      {
        ++itr;
        continue;
      }
      itr = this->allocated_.erase(itr);
    }
  }
  GG_INLINE T_UINT16 GetPoolSize() const
  {
    return (T_UINT16)(this->pool_.size() + this->allocated_.size());
  }
  GG_INLINE T_UINT16 GetAllocatedCount() const
  {
    return (T_UINT16)this->allocated_.size();
  }
private:
  //
  typename std::deque<T*> pool_;
  //�Q�[�����͓r�������̗v�f�̍폜���p�ɂɍs�����
  typename std::list<T*> allocated_;
};

