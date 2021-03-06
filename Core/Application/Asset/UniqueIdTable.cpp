#include "UniqueIdTable.h"

// =================================================================
// Methods
// =================================================================
T_UINT32 UniqueIdTable::Publish(const std::string& path)
{
  // ID発行済みのpathだった場合それを返す
  const auto& itr = this->table_.find(path);
  if (itr != this->table_.end())
  {
    return itr->second;
  }
  // 未使用のIDを検索する, 0は予約済み
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