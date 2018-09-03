#pragma once

#include "Resource.h"
#include "JsonParser.h"

class rcJsonData : public Resource
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static rcJsonData* CreateFromFile(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcJsonData(const char* path);
  ~rcJsonData();

  // =================================================================
  // Methods
  // =================================================================
public:
  void Write(const char* path);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline JsonNode* GetRoot() const
  {
    return this->root_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::string path_;
  JsonNode* root_;

};