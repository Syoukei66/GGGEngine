#pragma once

#include "Resource.h"
#include "JsonParser.h"

class rcJsonData : public Resource
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueResource<rcJsonData> CreateFromFile(const char* path);

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
  inline virtual const char* GetResourceName() override
  {
    return "JsonData";
  }

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