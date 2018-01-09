#pragma once

#include <string>

class ResourceLoader
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ResourceLoader(const std::string& category, const std::string& path);
  virtual ~ResourceLoader() {}

  // =================================================================
  // Methods
  // =================================================================
public:
  void Load();
  void Unload();

protected:
  virtual void LoadProcess(const std::string& path) = 0;
  virtual void UnloadProcess() = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  virtual bool IsLoaded() const = 0;

  inline const std::string& GetCategory() const
  {
    return this->category_;
  }
  inline const std::string& GetPath() const
  {
    return this->path_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  const std::string category_;
  const std::string path_;
};