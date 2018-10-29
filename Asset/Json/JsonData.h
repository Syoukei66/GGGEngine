#pragma once

#include "Resource.h"
#include "JsonParser.h"

class rcJsonData : public GGAssetObject
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcJsonData> CreateFromFile(const char* path);

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
  GG_INLINE virtual const char* GetResourceName() override
  {
    return "JsonData";
  }

  GG_INLINE JsonNode* GetRoot() const
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