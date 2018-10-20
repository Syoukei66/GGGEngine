#pragma once

#include <string>
#include <vector>

enum class DoLevel
{
  NOT_DO,
  ON_DEBUG,
  ON_ANYTIME,
};

class LoggerBuilder
{
  struct LevelData
  {
    std::string name;
    DoLevel do_level;
    bool break_flag;
  };

public:
  LoggerBuilder() = default;

private:
  std::string CreateEnums();
  std::string CreateNames();
  std::string CreateLevelMethods(const std::string& name, DoLevel do_level, bool break_flag);
  std::string CreateMethods();

public:
  void CreateHeader();


public:
  inline void Add(const std::string& name, DoLevel do_level, bool break_flag)
  {
    levels_.push_back(LevelData{name, do_level, break_flag});
  }

private:
  std::vector<LevelData> levels_;

};
