#pragma once

#include <map>
#include <string>
#include <vector>

#include "NativeAssert.h"
#include "NativeType.h"

//=============================================================================
// JsonBase
//=============================================================================
class JsonBase
{
public:
  JsonBase(T_UINT8 depth);
  virtual ~JsonBase() {}

public:
  virtual const std::string ToString() const = 0;

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

public:
  operator const std::string () const
  {
    return this->StringValue();
  }

public:
  const std::string& StringValue() const;

public:
  virtual const std::string ToString() const override;

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

public:
  operator T_INT32() const
  {
    return this->IntValue();
  }
  operator T_FLOAT() const
  {
    return this->FloatValue();
  }

public:
  T_INT32 IntValue() const;
  T_FLOAT FloatValue() const;

public:
  virtual const std::string ToString() const override;

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

  JsonNode* GetNode(const std::string& key);
  const JsonNode* GetNode(const std::string& key) const;

  JsonList* GetList(const std::string& key);
  const JsonList* GetList(const std::string& key) const;

  JsonString* GetString(const std::string& key);
  const JsonString* GetString(const std::string& key) const;

  JsonValue* GetValue(const std::string& key);
  const JsonValue* GetValue(const std::string& key) const;

public:
  virtual const std::string ToString() const override;

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

  JsonNode* GetNode(T_UINT16 index);
  const JsonNode* GetNode(T_UINT16 index) const;

  JsonList* GetList(T_UINT16 index);
  const JsonList* GetList(T_UINT16 index) const;

  JsonString* GetString(T_UINT16 index);
  const JsonString* GetString(T_UINT16 index) const;

  JsonValue* GetValue(T_UINT16 index);
  const JsonValue* GetValue(T_UINT16 index) const;

  const size_t GetSize() const
  {
    return this->value_list_.size();
  }

public:
  virtual const std::string ToString() const override;

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

