#include "UniqueIdTable.h"

// =================================================================
// Methods
// =================================================================
T_UINT32 UniqueIdTable::Publish(const std::string& path)
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

T_UINT32 UniqueIdTable::GetID(const std::string& path) const
{
  const auto& itr = this->table_.find(path);
  if (itr != this->table_.end())
  {
    return itr->second;
  }
  return 0;
}

const std::string& UniqueIdTable::GetPath(T_UINT32 uid) const
{
  for (auto& pair : this->table_)
  {
    if (uid == pair.second)
    {
      return pair.first;
    }
  }
  static std::string NULL_PATH = "";
  return NULL_PATH;
}