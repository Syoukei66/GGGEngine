#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "../Common/NativeType.h"
#include "../Common/NativeAssert.h"
#include "ResourceLoader.h"
#include "FileLoader.h"

#ifdef _DEBUG
#include <fstream>
#endif

class IResourceLoadingListener
{
public:
  virtual void OnLoadingInit() {}
  virtual void OnLoadingStarted() {}
  virtual void OnLoadingReserved(const std::string& category, T_UINT8 weight) {}
  virtual void OnLoadingProgressed(const std::string& category, T_UINT8 weight) {}
  virtual void OnLoadingFinished() {}
};

class IResourceLoadReserver
{
public:
  virtual void ReserveLoad(const FileLoader& resource) = 0;
};

class ResourcePool : public IResourceLoadReserver
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ResourcePool();
  virtual ~ResourcePool();

  // =================================================================
  // Methods
  // =================================================================
public:
  void Init();
  void Uninit();

  void Update();

  //���[�h�\����s��
  void ReserveLoad(const FileLoader& resource) override;
  //���[�h/�A�����[�h�\����쐬
  //loaded_resources_release �c ���Ƀ��[�h�ς݂̃��\�[�X���������ꍇtrue
  void PreRealize(IResourceLoadingListener* listener, bool loaded_resources_release = true);
  //�\�����Ƀ��[�h/�A�����[�h�������s��
  void Realize(IResourceLoadingListener* listener);

  template<class T>
  T* DynamicLoad(const char* path)
  {
    T* ret = (T*)this->dynamic_resources_[path];
    if (!ret)
    {
#ifdef _DEBUG
      std::ifstream ifs(path);
      NATIVE_ASSERT(ifs.is_open(), "�t�@�C���p�X���ԈႦ�Ă��܂�");
#endif
      ret = new T(path);
      ret->Load();
      this->dynamic_resources_[path] = ret;
    }
    ret->Retain();
    return ret;
  }

private:
  std::unordered_map<std::string, FileLoader*> resources_;
  std::unordered_map<std::string, std::unordered_set<FileLoader*>> load_reserve_;
  std::unordered_map<std::string, std::unordered_set<FileLoader*>> unload_reserve_;

  //���I���\�[�X�͓��I���������ׁAdelete����K�v������
  std::unordered_map<std::string, FileLoader*> dynamic_resources_;
};
