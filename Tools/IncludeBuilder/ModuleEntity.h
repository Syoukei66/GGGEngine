#pragma once

#include <string>
#include <unordered_set>

class ModuleEntity
{
public:
  ModuleEntity(const std::string& path);

public:
  ModuleEntity* AddIgnore(const std::string& ignore)
  {
    this->ignores_.emplace(ignore);
    return this;
  }
  ModuleEntity* AddSpecial(const std::string& special)
  {
    this->specials_.emplace(special);
    return this;
  }

  void CreateHeaderProgram() const;

  void Crawl(const std::string& path, std::vector<std::string>* dest) const;

private:
  std::string path_;
  std::unordered_set<std::string> ignores_;
  std::unordered_set<std::string> specials_;

};