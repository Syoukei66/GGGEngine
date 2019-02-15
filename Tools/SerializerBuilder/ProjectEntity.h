#pragma once

#include <string>
#include <unordered_set>
#include <vector>

class ProjectEntity
{
public:
  ProjectEntity(const std::string& path);
  ~ProjectEntity();

public:
  void CreateProgram(std::string* header, std::string* cpp) const;

  void Crawl(const std::string& path, std::vector<std::string>* dest) const;

private:
  std::string path_;
  std::unordered_set<std::string> ignores_;
  std::unordered_set<std::string> specials_;

};
