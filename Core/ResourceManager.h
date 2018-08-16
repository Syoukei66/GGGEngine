#pragma once

#include <functional>
#include <unordered_map>
#include <list>

class Resource;

class ResourceManager
{
public:
  static inline ResourceManager& GetInstance()
  {
    static ResourceManager self;
    return self;
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ResourceManager() = default;
  ~ResourceManager() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  void Init();
  void Uninit();

  inline void Manage(Resource* resource)
  {
    this->resources_.emplace_back(resource);
  }

  void Update();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  size_t GetMemorySize() const;

  size_t GetVideoMemorySize() const;

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::list<Resource*> resources_;
};