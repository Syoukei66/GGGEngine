#pragma once

#include <string>
#include <unordered_map>

#include <Cereal/cereal.hpp>
#include <Cereal/archives/json.hpp>
#include <Cereal/types/string.hpp>
#include <Cereal/types/unordered_map.hpp>
#include <Cereal/types/utility.hpp>
#include <Core/NativeType.h>

class UniqueIdTable
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  UniqueIdTable() = default;
  ~UniqueIdTable() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  T_UINT32 Publish(const std::string& path);
  T_UINT32 GetID(const std::string& path) const;

  // =================================================================
  // Serialize Method
  // =================================================================
public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(cereal::make_nvp("Table", this->table_));
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::unordered_map<std::string, T_UINT32> table_;

};
CEREAL_CLASS_VERSION(UniqueIdTable, 1);
