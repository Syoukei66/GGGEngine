#pragma once

#include "IAssetContainer.h"
#include "../Core/NativeAssert.h"

//TODO:AssetBundle�ASize�AOffset�Ȃǂ��Z�b�g���ă��[�h���ŏ����ɗ}����
template<class T>
class AssetContainer : public IAssetContainer
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static AssetContainer<T>* Create(const std::string& path)
  {
    //�t�@�C���̑��݂��m�F����Ɠ����Ƀt�@�C���T�C�X���擾����
    std::ifstream ifs(path, std::ifstream::ate | std::ifstream::binary);
    NATIVE_ASSERT(ifs.is_open(), "�t�@�C���p�X���ԈႦ�Ă��܂�");
    return new AssetContainer<T>(path, (T_UINT32)ifs.tellg());
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
private:
  AssetContainer(const std::string& path, T_UINT32 size)
    : path_(path)
    , size_(size)
    , reference_count_(0)
    , obj_(nullptr)
  {}
  // =================================================================
  // Operator
  // =================================================================
public:
  operator T*() const
  {
    return this->obj_;
  }

  // =================================================================
  // Methods
  // =================================================================
public:
  inline void Retain() override
  {
    if (this->reference_count_ == 0)
    {
      this->Load();
    }
    this->reference_count_++;
  }

  inline void Release() override
  {
    if (this->reference_count_ == 0)
    {
      return;
    }
    this->reference_count_--;
    if (this->reference_count_ == 0)
    {
      this->Unload();
    }
  }

private:
  void Load()
  {
    if (this->IsLoaded())
    {
      return;
    }
    this->obj_ = T::Create(this->path_.c_str());
  }

  void Unload()
  {
    if (!this->IsLoaded())
    {
      return;
    }
    this->obj_->Release();
    this->obj_ = nullptr;
  }

  inline bool IsLoaded() const
  {
    return this->obj_;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline T_INT16 GetReferenceCount() const override
  {
    return this->reference_count_;
  }

  inline T_UINT32 GetSize() const override
  {
    return this->size_;
  }

  inline T* GetContents() const
  {
    NATIVE_ASSERT(this->obj_, "�Q�ƃJ�E���g��0�ł��B�g�p�O��Retain()���Ăяo���Ă��������B");
    return this->obj_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::string path_;
  T_UINT32 size_;
  T_INT16 reference_count_;
  T* obj_;

};