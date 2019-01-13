#pragma once

#include "AssetConverter.h"

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
  ////イベントを受理した(戻り値にtrueが帰ってきた)Converterに対してのみ処理を行う
  //bool Fire(const std::function<bool(AssetConverter*)>& func);

  ////全てのConverterに対して処理を行う
  //void VisitAll(const std::function<void(AssetConverter*)>& func);
  //void VisitAll(const std::function<void(const AssetConverter*)>& func) const;

  //void VisitAllEntity(const std::function<void(const SharedRef<AssetEntity>&)>& func);
  //SharedRef<AssetEntity> FindAllEntity(const std::function<bool(const SharedRef<AssetEntity>&)>& func);

  ////値が帰ってくるまで検索する
  //SharedRef<AssetEntity> Find(const std::function<SharedRef<AssetEntity>(AssetConverter*)>& func);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline void AddConverter(AssetConverter* converter)
  {
    this->converter_map_[converter->GetId()] =  converter;
  }

  inline AssetConverter* GetConverter(const std::string& id)
  {
    return this->converter_map_[id];
  }

  inline const AssetConverter* GetConverter(const std::string& id) const
  {
    return this->converter_map_.at(id);
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::unordered_map<std::string, AssetConverter*> converter_map_;

};
