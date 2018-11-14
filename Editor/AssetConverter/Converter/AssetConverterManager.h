#pragma once

class IAssetConverter;
template<class Entity_>
class AssetConverter;

class AssetEntity;

class AssetConverterManager
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetConverterManager();
  ~AssetConverterManager();

  // =================================================================
  // Methods
  // =================================================================
public:
  //イベントを受理した(戻り値にtrueが帰ってきた)Converterに対してのみ処理を行う
  bool Fire(const std::function<bool(IAssetConverter*)>& func);

  template <class Entity_>
  bool Fire(const std::function<bool(AssetConverter<Entity_>*)>& func);

  //全てのConverterに対して処理を行う
  void VisitAll(const std::function<void(IAssetConverter*)>& func);
  void VisitAll(const std::function<void(const IAssetConverter*)>& func) const;

  template <class Entity_>
  void VisitAll(const std::function<void(AssetConverter<Entity_>*)>& func);

  template <class Entity_>
  void VisitAll(const std::function<void(const AssetConverter<Entity_>*)>& func) const;

  void VisitAllEntity(const std::function<void(AssetEntity*)>& func);
  AssetEntity* FindAllEntity(const std::function<bool(AssetEntity*)>& func);

  //値が帰ってくるまで検索する
  template <class Type_>
  Type_* Find(const std::function<Type_*(IAssetConverter*)>& func);
  AssetEntity* Find(const std::function<AssetEntity*(IAssetConverter*)>& func);

  template <class Type_, class Entity_>
  Type_* Find(const std::function<Type_*(AssetConverter<Entity_>*)>& func);

  inline void AddConverter(IAssetConverter* converter);

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::unordered_map<T_UINT32, IAssetConverter*> converter_map_;

};

#include <Converter/AssetConverter.h>

//イベントを受理した(戻り値にtrueが帰ってきた)Converterに対してのみ処理を行う
template<class Entity_>
inline bool AssetConverterManager::Fire(const std::function<bool(AssetConverter<Entity_>*)>& func)
{
  return func((AssetConverter<Entity_>*)this->converter_map_.at(Entity_::ID));
}

//全てのConverterに対して処理を行う
template<class Entity_>
inline void AssetConverterManager::VisitAll(const std::function<void(AssetConverter<Entity_>*)>& func)
{
  func((AssetConverter<Entity_>*)this->converter_map_.at(Entity_::ID));
}

template<class Entity_>
inline void AssetConverterManager::VisitAll(const std::function<void(const AssetConverter<Entity_>*)>& func) const
{
  func((AssetConverter<Entity_>*)this->converter_map_.at(Entity_::ID));
}

//値が帰ってくるまで検索する
template<class Type_>
inline Type_* AssetConverterManager::Find(const std::function<Type_*(IAssetConverter*)>& func)
{
  for (auto& pair : this->converter_map_)
  {
    Type_* val = func(pair.second);
    if (val)
    {
      return val;
    }
  }
  return nullptr;
}

template<class Type_, class Entity_>
inline Type_* AssetConverterManager::Find(const std::function<Type_*(AssetConverter<Entity_>*)>& func)
{
  return func((AssetConverter<Entity_>*)this->converter_map_.at(Entity_::ID));
}

inline void AssetConverterManager::AddConverter(IAssetConverter* converter)
{
  GG_ASSERT(this->converter_map_.find(converter->GetID()) == this->converter_map_.end(), "同じAssetEntityを対象とする複数のコンバーターが存在します");
  this->converter_map_[converter->GetID()] = converter;
}
