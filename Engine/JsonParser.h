#pragma once

#include <map>
#include <string>
#include <vector>

#include "NativeType.h"

//=============================================================================
// JsonBase
// デストラクタ呼び出しの為など
//=============================================================================
class JsonBase
{
public:
  JsonBase(T_UINT8 depth);
  virtual ~JsonBase() {}

public:
  virtual std::string ToString() = 0;

protected:
  const T_UINT8 depth_;
};

//=============================================================================
// JsonString
//=============================================================================
class JsonString : public JsonBase
{
public:
  JsonString(const std::string& text, T_UINT8 depth);
  ~JsonString();

public:
  const char* StringValue();

public:
  virtual std::string ToString() override;

private:
  std::string text_;

};

//=============================================================================
// JsonValue
//=============================================================================
class JsonValue : public JsonBase
{
public:
  JsonValue(const std::string& text, T_UINT8 depth);
  ~JsonValue();

public:
  T_INT32 IntValue();
  T_FLOAT FloatValue();

public:
  virtual std::string ToString() override;

private:
  std::string text_;
};

class JsonNode;
class JsonList;

//=============================================================================
// JsonNode
//=============================================================================
class JsonNode : public JsonBase
{
public:  
  JsonNode(T_UINT8 depth);
  virtual ~JsonNode();

public:
  void Set(const std::string& key, JsonBase* value)
  {
    this->value_map_[key] = value;
  }

  JsonString* GetString(const std::string& key) const
  {
    return (JsonString*)this->value_map_.at(key);
  }
  JsonValue* GetValue(const std::string& key) const
  {
    return (JsonValue*)this->value_map_.at(key);
  }

  JsonNode* GetNode(const std::string& key) const
  {
    return (JsonNode*)this->value_map_.at(key);
  }

  JsonList* GetList(const std::string& key) const
  {
    return (JsonList*)this->value_map_.at(key);
  }

public:
  virtual std::string ToString() override;

private:
  std::map<std::string, JsonBase*> value_map_;
};

//=============================================================================
// JsonList
//=============================================================================
class JsonList : public JsonBase
{
public:
  JsonList(T_UINT8 depth);
  virtual ~JsonList();

public:
  void Add(JsonBase* value)
  {
    this->value_list_.push_back(value);
  }

  const JsonValue* GetValue(T_UINT16 index) const
  {
    return (JsonValue*)this->value_list_[index];
  }

  const JsonNode* GetNode(T_UINT16 index) const
  {
    return (JsonNode*)this->value_list_[index];
  }

  const JsonList* GetList(T_UINT16 index) const
  {
    return (JsonList*)this->value_list_[index];
  }

  const size_t GetSize()
  {
    return this->value_list_.size();
  }

public:
  virtual std::string ToString() override;

private:
  std::vector<JsonBase*> value_list_;
};

//=============================================================================
// JsonParser
//=============================================================================
class JsonParser
{
public:
  JsonNode* Parse(const char* json_text);

protected:
  std::string ParseString(const char** p, T_UINT8 depth);
  JsonBase* ParseValue(const char** p, T_UINT8 depth);
  JsonString* ParseJsonString(const char** p, T_UINT8 depth);
  JsonValue* ParseJsonValue(const char** p, T_UINT8 depth);
  JsonNode* ParseJsonMap(const char** p, T_UINT8 depth);
  JsonList* ParseJsonList(const char** p, T_UINT8 depth);
};

