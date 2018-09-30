#pragma once

#include <list>

class Resource;

class ResourceManager
{
private:
  // =================================================================
  // Constructor / Destructor
  // =================================================================
  static inline ResourceManager* GetInstance()
  {
    static ResourceManager self;
    return &self;
  }

  ResourceManager() = default;
  ~ResourceManager() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  static void Init();
  static void Uninit();
  static void Update();

  static inline void Manage(Resource* resource)
  {
    GetInstance()->resources_.emplace_back(resource);
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  static size_t GetMemorySize();
  static size_t GetVideoMemorySize();

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::list<Resource*> resources_;
};