#include "UniqueIdTable.h"

// =================================================================
// Methods
// =================================================================
T_UINT32 UniqueIdTable::Publish(const std::string & path)
{
  const auto& itr = this->table_.find(path);
  if (itr != this->table_.end())
  {
    return itr->second;
  }
  //–¢g—p‚ÌID‚ğŒŸõ‚·‚é, 0‚Í—\–ñÏ‚İ
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

T_UINT32 UniqueIdTable::GetID(const std::string & path) const
{
  const auto& itr = this->table_.find(path);
  if (itr != this->table_.end())
  {
    return itr->second;
  }
  return 0;
}
