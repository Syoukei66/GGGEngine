#pragma once

#include <string>
#include <unordered_map>

#include "NativeType.h"
#include "Cereal\cereal.hpp"
#include "Cereal\archives\json.hpp"
#include "Cereal\types\string.hpp"
#include "Cereal\types\unordered_map.hpp"
#include "Cereal\types\utility.hpp"

class UniqueIdTable
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  UniqueIdTable() = default;
  ~UniqueIdTable() = default;

public:
  T_UINT32 Publish(const std::string& path)
  {
    const auto& itr = this->table_.find(path);
    if (itr != this->table_.end())
    {
      return itr->second;
    }
    //–¢Žg—p‚ÌID‚ðŒŸõ‚·‚é, 0‚Í—\–ñÏ‚Ý
    T_UINT32 id = 1;
    while (true)
    {
      bool used = false;
      for (auto& pair : this->table_)
      {
        if (id == pair.second)
        {
          used = true;
          break;
        }
      }
      if (!used)
      {
        break;
      }
      ++id;
    }
    return this->table_[path] = id;
  }

  T_UINT32 GetID(const std::string& path) const
  {
    return this->table_.at(path);
  }

public:
  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    ar(cereal::make_nvp("Table", this->table_));
  }

private:
  std::unordered_map<std::string, T_UINT32> table_;

};
CEREAL_CLASS_VERSION(UniqueIdTable, 1);
