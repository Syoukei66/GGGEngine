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
  ////�C�x���g���󗝂���(�߂�l��true���A���Ă���)Converter�ɑ΂��Ă̂ݏ������s��
  //bool Fire(const std::function<bool(AssetConverter*)>& func);

  ////�S�Ă�Converter�ɑ΂��ď������s��
  //void VisitAll(const std::function<void(AssetConverter*)>& func);
  //void VisitAll(const std::function<void(const AssetConverter*)>& func) const;

  //void VisitAllEntity(const std::function<void(const SharedRef<AssetEntity>&)>& func);
  //SharedRef<AssetEntity> FindAllEntity(const std::function<bool(const SharedRef<AssetEntity>&)>& func);

  ////�l���A���Ă���܂Ō�������
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
