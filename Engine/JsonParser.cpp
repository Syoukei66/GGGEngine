#include "JsonParser.h"

#include "NativeType.h"

static void ApplyDepth(std::string& str, T_UINT8 depth)
{
  for (T_UINT8 i = 0; i < depth; ++i)
  {
    str.append("  ");
  }
}

JsonBase::JsonBase(T_UINT8 depth)
  : depth_(depth)
{}

//=============================================================================
// JsonString
//=============================================================================
JsonString::JsonString(const std::string& text, T_UINT8 depth)
  : JsonBase(depth)
  , text_(text)
{}

JsonString::~JsonString()
{
}

const char* JsonString::StringValue()
{
  return this->text_.c_str();
}

std::string JsonString::ToString()
{
  std::string ret = std::string();
  ret.append("\"");
  ret.append(this->text_);
  ret.append("\"");
  return ret;
}

//=============================================================================
// JsonValue
//=============================================================================
JsonValue::JsonValue(const std::string& text, T_UINT8 depth)
  : JsonBase(depth)
  , text_(text)
{}

JsonValue::~JsonValue()
{}

T_INT32 JsonValue::IntValue()
{
  return std::stoi(this->text_);
}

T_FLOAT JsonValue::FloatValue()
{
  return std::stof(this->text_);
}

std::string JsonValue::ToString()
{
  return this->text_;
}

//=============================================================================
// JsonNode
//=============================================================================
JsonNode::JsonNode(T_UINT8 depth)
  : JsonBase(depth)
{}

JsonNode::~JsonNode()
{
  for (std::map<std::string, JsonBase*>::iterator itr = this->value_map_.begin(); itr != this->value_map_.end(); ++itr)
  {
    delete itr->second;
  }
  this->value_map_.clear();
}

std::string JsonNode::ToString()
{
  std::string ret = std::string();
  ApplyDepth(ret, this->depth_);
  ret.append("{");
  bool first = true;
  for (std::map<std::string, JsonBase*>::iterator itr = this->value_map_.begin(); itr != this->value_map_.end(); ++itr)
  {
    if (first)
    {
      first = false;
    }
    else
    {
      ret.append(",");
    }
    ApplyDepth(ret, this->depth_ + 1);
    ret.append("\"");
    ret.append(itr->first);
    ret.append("\"");
    ret.append(": ");
    ret.append(itr->second->ToString());
  }
  ApplyDepth(ret, this->depth_);
  ret.append("}\n");
  return ret;
}

//=============================================================================
// JsonList
//=============================================================================
JsonList::JsonList(T_UINT8 depth)
  : JsonBase(depth)
{}


JsonList::~JsonList()
{
  for (std::vector<JsonBase*>::iterator itr = this->value_list_.begin(); itr != this->value_list_.end(); ++itr)
  {
    delete (*itr);
  }
  this->value_list_.clear();
}

std::string JsonList::ToString()
{
  std::string ret = std::string();
  ApplyDepth(ret, this->depth_);
  ret.append("[\n");
  bool first = true;
  for (std::vector<JsonBase*>::iterator itr = this->value_list_.begin(); itr != this->value_list_.end(); ++itr)
  {
    ApplyDepth(ret, this->depth_);
    if (first)
    {
      first = false;
    }
    else
    {
      ret.append(",\n");
    }
    ret.append((*itr)->ToString());
  }
  ret.append("]");
  return ret;
}

//=============================================================================
// JsonParser
//=============================================================================
static bool EndOfFile(char c)
{
  return c == '\0';
}

static bool Escape(char c)
{
  return c == '\n' || c == '\t' || c == ' ';
}

static bool IsStringBracket(char c)
{
  return c == '\"';
}

static bool IsNumberBegin(char c)
{
  return ('0' <= c && c <= '9') || c == '.' || c == '-';
}

static bool IsComma(char c)
{
  return c == ',';
}

static bool IsValueSeparator(char c)
{
  return c == ':';
}

static bool IsListBracketLeft(char c)
{
  return c == '[';
}

static bool IsListBracketRight(char c)
{
  return c == ']';
}

static bool IsMapBracketLeft(char c)
{
  return c == '{';
}

static bool IsMapBracketRight(char c)
{
  return c == '}';
}

JsonNode* JsonParser::Parse(const char* json_text)
{
  const char* p = &json_text[0];
  while (IsMapBracketLeft(*p))
  {
    p++;
  }
  p++;
  return this->ParseJsonMap(&p, 0);
}

std::string JsonParser::ParseString(const char** p, T_UINT8 depth)
{
  std::string ret = std::string();
  while (!EndOfFile(**p))
  {
    if (IsStringBracket(**p))
    {
      ++(*p);
      return ret;
    }
    ret.append(*p, 1);
    ++(*p);
  }
  NATIVE_ASSERT(false, "JsonParser::ParseString() : 予期せぬEOFが検出されました。");
  return ret;
}

JsonBase* JsonParser::ParseValue(const char ** p, T_UINT8 depth)
{
  std::string ret = std::string();
  while (!EndOfFile(**p))
  {
    if (Escape(**p))
    {
      ++(*p);
      continue;
    }
    if (IsNumberBegin(**p))
    {
      return this->ParseJsonValue(&(*p), depth);
    }
    if (IsStringBracket(**p))
    {
      ++(*p);
      return this->ParseJsonString(&(*p), depth);
    }
    if (IsMapBracketLeft(**p))
    {
      ++(*p);
      return this->ParseJsonMap(&(*p), depth);
    }
    if (IsListBracketLeft(**p))
    {
      ++(*p);
      return this->ParseJsonList(&(*p), depth);
    }
    ret.append(*p, 1);
    ++(*p);
  }
  return nullptr;
}

JsonString* JsonParser::ParseJsonString(const char** p, T_UINT8 depth)
{
  std::string ret = std::string();
  while (!EndOfFile(**p))
  {
    if (Escape(**p))
    {
      ++(*p);
      continue;
    }
    if (IsStringBracket(**p))
    {
      ++(*p);
      return new JsonString(ret, depth);
    }
    ret.append(*p, 1);
    ++(*p);
  }
  NATIVE_ASSERT(false, "JsonParser::ParseJsonString() : 予期せぬEOFが検出されました。");
  return nullptr;
}

JsonValue* JsonParser::ParseJsonValue(const char** p, T_UINT8 depth)
{
  std::string ret = std::string();
  while (!EndOfFile(**p))
  {
    if (Escape(**p))
    {
      ++(*p);
      return new JsonValue(ret, depth);
    }
    if (IsComma(**p))
    {
      return new JsonValue(ret, depth);
    }
    ret.append(*p, 1);
    ++(*p);
  }
  NATIVE_ASSERT(false, "JsonParser::ParseJsonValue() : 予期せぬEOFが検出されました。");
  return nullptr;
}

JsonNode* JsonParser::ParseJsonMap(const char** p, T_UINT8 depth)
{
  JsonNode* ret = new JsonNode(depth);
  std::string key = std::string();
  while (!EndOfFile(**p))
  {
    if (Escape(**p))
    {
      ++(*p);
      continue;
    }
    if (IsComma(**p))
    {
      ++(*p);
      continue;
    }
    if (IsMapBracketRight(**p))
    {
      ++(*p);
      return ret;
    }
    if (IsStringBracket(**p))
    {
      ++(*p);
      key = this->ParseString(&(*p), depth);
      continue;
    }
    if (IsValueSeparator(**p))
    {
      ++(*p);
      JsonBase* value = this->ParseValue(&(*p), depth);
      ret->Set(key, value);
      continue;
    }
    ++(*p);
  }
  NATIVE_ASSERT(false, "JsonParser::ParseJsonMap() : 予期せぬEOFが検出されました。");
  return nullptr;
}

JsonList* JsonParser::ParseJsonList(const char** p, T_UINT8 depth)
{
  JsonList* ret = new JsonList(depth);
  while (!EndOfFile(**p))
  {
    if (Escape(**p))
    {
      ++(*p);
      continue;
    }
    if (IsListBracketRight(**p))
    {
      ++(*p);
      return ret;
    }
    if (IsMapBracketLeft(**p))
    {
      ++(*p);
      JsonNode* json_map = this->ParseJsonMap(&(*p), depth);
      ret->Add(json_map);
      continue;
    }
    if (IsListBracketLeft(**p))
    {
      ++(*p);
      JsonList* json_list = this->ParseJsonList(&(*p), depth);
      ret->Add(json_list);
      continue;
    }
    ++(*p);
  }
  NATIVE_ASSERT(false, "JsonParser::ParseJsonList() : 予期せぬEOFが検出されました。");
  return nullptr;
}
