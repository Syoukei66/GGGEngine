#include "AssetConverterManager.h"
#include <Entity/AssetEntity.h>

#include <Converter/AssetConverter.h>

// =================================================================
// Constructor / Destructor
// =================================================================
AssetConverterManager::AssetConverterManager()
  :converter_map_()
{
}

AssetConverterManager::~AssetConverterManager()
{
  for (auto& pair : this->converter_map_)
  {
    delete pair.second;
  }
}

// =================================================================
// Methods
// =================================================================
//bool AssetConverterManager::Fire(const std::function<bool(AssetConverter*)>& func)
//{
//  for (AssetConverter* converter : this->converter_map_)
//  {
//    if (func(converter))
//    {
//      return true;
//    }
//  }
//  return false;
//}
//
//void AssetConverterManager::VisitAll(const std::function<void(AssetConverter*)>& func)
//{
//  for (AssetConverter* converter : this->converter_map_)
//  {
//    func(converter);
//  }
//}
//
//void AssetConverterManager::VisitAll(const std::function<void(const AssetConverter*)>& func) const
//{
//  for (AssetConverter* converter : this->converter_map_)
//  {
//    func(converter);
//  }
//}
//
//
//void AssetConverterManager::VisitAllEntity(const std::function<void(const SharedRef<AssetEntity>&)>& func)
//{
//  for (AssetConverter* converter : this->converter_map_)
//  {
//    converter->VisitAllEntity(func);
//  }
//}
//
//SharedRef<AssetEntity> AssetConverterManager::FindAllEntity(const std::function<bool(const SharedRef<AssetEntity>&)>& func)
//{
//  for (AssetConverter* converter : this->converter_map_)
//  {
//    SharedRef<AssetEntity> entity = converter->FindAllEntity(func);
//    if (entity)
//    {
//      return entity;
//    }
//  }
//  return nullptr;
//}
//
//SharedRef<AssetEntity> AssetConverterManager::Find(const std::function<SharedRef<AssetEntity>(AssetConverter*)>& func)
//{
//  for (AssetConverter* converter : this->converter_map_)
//  {
//    SharedRef<AssetEntity> val = func(converter);
//    if (val)
//    {
//      return val;
//    }
//  }
//  return nullptr;
//}
