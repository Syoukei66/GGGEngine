#pragma once

#include <functional>
#include "Setting.h"

class IAssetConverter;
template<class Entity_>
class AssetConverter;

class AssetConverterManager
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetConverterManager(const Setting* setting);
  ~AssetConverterManager();

  // =================================================================
  // Methods
  // =================================================================
public:
  //�C�x���g���󗝂���(�߂�l��true���A���Ă���)Converter�ɑ΂��Ă̂ݏ������s��
  bool Fire(const std::function<bool(IAssetConverter*)>& func);

  template <class Entity_>
  bool Fire(const std::function<bool(AssetConverter<Entity_>*)>& func);

  //�S�Ă�Converter�ɑ΂��ď������s��
  void VisitAll(const std::function<void(IAssetConverter*)>& func);
  void VisitAll(const std::function<void(const IAssetConverter*)>& func) const;

  template <class Entity_>
  void VisitAll(const std::function<void(AssetConverter<Entity_>*)>& func);

  template <class Entity_>
  void VisitAll(const std::function<void(const AssetConverter<Entity_>*)>& func) const;

  //�l���A���Ă���܂Ō�������
  template <class Type_>
  Type_* Find(const std::function<Type_*(IAssetConverter*)>& func);

  template <class Type_, class Entity_>
  Type_* Find(const std::function<Type_*(AssetConverter<Entity_>*)>& func);


private:
  inline void AddConverter(IAssetConverter* converter);

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::unordered_map<T_UINT32, std::vector<IAssetConverter*>> converters_map_;

};

#include "AssetConverter.h"

//�C�x���g���󗝂���(�߂�l��true���A���Ă���)Converter�ɑ΂��Ă̂ݏ������s��
template<class Entity_>
inline bool AssetConverterManager::Fire(const std::function<bool(AssetConverter<Entity_>*)>& func)
{
  const std::vector<IAssetConverter*>& converters = this->converters_map_.at(Entity_::ID);
  for (IAssetConverter* converter : converters)
  {
    if (func(converter))
    {
      return true;
    }
  }
  return false;
}

//�S�Ă�Converter�ɑ΂��ď������s��
template<class Entity_>
inline void AssetConverterManager::VisitAll(const std::function<void(AssetConverter<Entity_>*)>& func)
{
  const std::vector<IAssetConverter*>& converters = this->converters_map_.at(Entity_::ID);
  for (IAssetConverter* converter : converters)
  {
    func((AssetConverter<Entity_>*)converter);
  }
}

template<class Entity_>
inline void AssetConverterManager::VisitAll(const std::function<void(const AssetConverter<Entity_>*)>& func) const
{
  const std::vector<IAssetConverter*>& converters = this->converters_map_.at(Entity_::ID);
  for (IAssetConverter* converter : converters)
  {
    func((AssetConverter<Entity_>*)converter);
  }
}

//�l���A���Ă���܂Ō�������
template<class Type_>
inline Type_* AssetConverterManager::Find(const std::function<Type_*(IAssetConverter*)>& func)
{
  for (auto& pair : this->converters_map_)
  {
    for (IAssetConverter* converter : pair.second)
    {
      Type_* val = func(converter);
      if (val)
      {
        return val;
      }
    }
  }
  return nullptr;
}

template<class Type_, class Entity_>
inline Type_* AssetConverterManager::Find(const std::function<Type_*(AssetConverter<Entity_>*)>& func)
{
  const std::vector<IAssetConverter*>& converters = this->converters_map_.at(Entity_::ID);
  for (IAssetConverter* converter : converters)
  {
    Type_* val = func(converter);
    if (val)
    {
      return val;
    }
  }
  return nullptr;
}

inline void AssetConverterManager::AddConverter(IAssetConverter* converter)
{
  this->converters_map_[converter->GetID()].emplace_back(converter);
}
