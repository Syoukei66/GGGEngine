#pragma once

#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include "../Core/NativeType.h"
#include "../Core/NativeAssert.h"
#include "../Core/HashUtil.h"

#include "AssetContainer.h"

class IAssetLoadingListener
{
public:
  virtual void OnLoadingInit() {}
  virtual void OnLoadingStarted() {}
  virtual void OnLoadingReserved(IAssetContainer* asset) {}
  virtual void OnLoadingProgressed(IAssetContainer* asset) {}
  virtual void OnLoadingFinished() {}
};

class IAssetLoadReserver
{
public:
  virtual void ReserveLoad(const IAssetContainer* resource) = 0;
};

//TODO: DynamicLoad��Load����ʂ��Ȃ��ōs�����@�͖�����
class OldAssetManager : public IAssetLoadReserver
{
public:
  static inline OldAssetManager& GetInstance()
  {
    static OldAssetManager self;
    return self;
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
private:
  OldAssetManager();
  virtual ~OldAssetManager();

  // =================================================================
  // Methods
  // =================================================================
public:
  void Uninit();
  void Update();

  template<class T>
  AssetContainer<T>* RegisterEngineAsset(T_UINT32 id, const std::string& extension)
  {
    AssetContainer<T>* ret = (AssetContainer<T>*)this->engine_assets_[id];
    if (!ret)
    {
      ret = AssetContainer<T>::Create(std::to_string(id) + "." + extension);
      this->engine_assets_.emplace(id, ret);
    }
    return ret;
  }

  template<class T>
  AssetContainer<T>* RegisterWithPath(const std::string& path)
  {
    const T_UINT32 id = Util::Hash::GetHash(path);
    AssetContainer<T>* ret = (AssetContainer<T>*)this->assets_[id];
    if (!ret)
    {
      ret = AssetContainer<T>::Create(path);
      this->assets_.emplace(id, ret);
    }
    return ret;
  }

  template<class T>
  AssetContainer<T>* Register(T_UINT32 id, const std::string& extension)
  {
    AssetContainer<T>* ret = (AssetContainer<T>*)this->assets_[id];
    if (!ret)
    {
      ret = AssetContainer<T>::Create(std::to_string(id) + "." + extension);
      this->assets_.emplace(id, ret);
    }
    return ret;
  }

  template<class T>
  AssetContainer<T>* Register(const char* path)
  {
    AssetContainer<T>* ret = (AssetContainer<T>*)this->dynamic_assets_[path];
    if (!ret)
    {
      ret = AssetContainer<T>::Create(path);
      this->dynamic_assets_.emplace(path, ret);
    }
    return ret;
  }

  //���[�h�\����s��
  void ReserveLoad(const IAssetContainer* asset) override;
  //���[�h/�A�����[�h�\����쐬
  //loaded_resources_release �c ���Ƀ��[�h�ς݂�Asset���������ꍇtrue
  void PreRealize(IAssetLoadingListener* listener, bool loaded_assets_release = true);
  //�\�����Ƀ��[�h/�A�����[�h�������s��
  void Realize(IAssetLoadingListener* listener);

  template<class T>
  inline AssetContainer<T>* GetAsset(T_UINT32 unique_id) const
  {
    if (this->assets_.find(unique_id) == this->assets_.end())
    {
      return nullptr;
    }
    return (AssetContainer<T>*)this->assets_.at(unique_id);
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::unordered_map<T_UINT32, IAssetContainer*> assets_;
  std::unordered_set<IAssetContainer*> loaded_assets_;
  std::unordered_set<IAssetContainer*> load_reserve_;
  std::unordered_set<IAssetContainer*> unload_reserve_;

  //Engine�̋N������I���܂ł����ƕێ������Asset
  std::unordered_map<T_UINT32, IAssetContainer*> engine_assets_;

  //���I���\�[�X�͓��I���������ׁAdelete����K�v������
  std::unordered_map<std::string, IAssetContainer*> dynamic_assets_;
};
