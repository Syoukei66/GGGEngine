#include "JsonParser.h"

#include "NativeType.h"

//=============================================================================
// JsonBase
//=============================================================================
JsonBase::JsonBase(T_UINT8 depth)
  : depth_(depth)
{}

void JsonBase::Release()
{
  delete this;
}

void JsonBase::ApplyDepth(std::string& str, T_UINT8 depth) const
{
  for (T_UINT8 i = 0; i < depth; ++i)
  {
    str.append("  ");
  }
}

//=============================================================================
// JsonString
//=============================================================================
JsonString::JsonString(const std::string& text, T_UINT8 depth)
  : JsonBase(depth)
  , text_(text)
{}

const std::string& JsonString::StringValue() const
{
  return this->text_;
}

const std::string JsonString::ToString() const
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

T_INT32 JsonValue::IntValue(T_INT32 deflt) const
{
  if (this->text_.length() == 0)
  {
    return deflt;
  }
  return std::stoi(this->text_);
}

T_FLOAT JsonValue::FloatValue(T_FLOAT deflt) const
{
  if (this->text_.length() == 0)
  {
    return deflt;
  }
  return std::stof(this->text_);
}

bool JsonValue::BoolValue(bool deflt) const
{
  if (this->text_.length() == 0)
  {
    return deflt;
  }
  if (this->text_ == "true")
  {
    return true;
  }
  if (this->text_ == "false")
  {
    return false;
  }
  return std::stoi(this->text_) == 1;
}

const std::string JsonValue::ToString() const
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
    itr->second->Release();
  }
  this->value_map_.clear();
}

const std::string JsonNode::ToString() const
{
  std::string ret = std::string();
  ret.append("{");
  bool first = true;
  for (std::map<std::string, JsonBase*>::const_iterator itr = this->value_map_.begin(); itr != this->value_map_.end(); ++itr)
  {
    if (first)
    {
      first = false;
    }
    else
    {
      ret.append(",");
    }
    ret.append("\n");
    ApplyDepth(ret, this->depth_ + 1);
    ret.append("\"");
    ret.append(itr->first);
    ret.append("\"");
    ret.append(": ");
    ret.append(itr->second->ToString());
  }
  ret.append("\n");
  ApplyDepth(ret, this->depth_);
  ret.append("}");
  return ret;
}

//=============================================================================
// JsonParser
//=============================================================================
inline static bool EndOfFile(char c)
{
  return c == '\0';
}
inline static bool Escape(char c)
{
  return c == '\n' || c == '\t' || c == ' ';
}
inline static bool IsStringBracket(char c)
{
  return c == '\"';
}
inline static bool IsNumberBegin(char c)
{
  return ('0' <= c && c <= '9') || c == '.' || c == '-';
}
inline static bool IsComma(char c)
{
  return c == ',';
}
inline static bool IsValueSeparator(char c)
{
  return c == ':';
}
inline static bool IsListBracketLeft(char c)
{
  return c == '[';
}
inline static bool IsListBracketRight(char c)
{
  return c == ']';
}
inline static bool IsMapBracketLeft(char c)
{
  return c == '{';
}
inline static bool IsMapBracketRight(char c)
{
  return c == '}';
}

std::string ParseString(const char** p, T_UINT8 depth);
JsonBase* ParseValue(const char** p, T_UINT8 depth);
JsonString* ParseJsonString(const char** p, T_UINT8 depth);
JsonValue* ParseJsonValue(const char** p, T_UINT8 depth);
JsonNode* ParseJsonMap(const char** p, T_UINT8 depth);
JsonList<JsonBase>* ParseJsonList(const char** p, T_UINT8 depth);

static std::string ParseString(const char** p, T_UINT8 depth)
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

static JsonBase* ParseValue(const char** p, T_UINT8 depth)
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
      return ParseJsonValue(&(*p), depth);
    }
    if (IsStringBracket(**p))
    {
      ++(*p);
      return ParseJsonString(&(*p), depth);
    }
    if (IsMapBracketLeft(**p))
    {
      ++(*p);
      return ParseJsonMap(&(*p), depth);
    }
    if (IsListBracketLeft(**p))
    {
      ++(*p);
      return ParseJsonList(&(*p), depth);
    }
    ret.append(*p, 1);
    ++(*p);
  }
  NATIVE_ASSERT(false, "JsonParser::ParseValue() : 予期せぬEOFが検出されました。");
  return nullptr;
}

static JsonString* ParseJsonString(const char** p, T_UINT8 depth)
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
      return JsonString::Create(ret, depth);
    }
    ret.append(*p, 1);
    ++(*p);
  }
  NATIVE_ASSERT(false, "JsonParser::ParseJsonString() : 予期せぬEOFが検出されました。");
  return nullptr;
}

static JsonValue* ParseJsonValue(const char** p, T_UINT8 depth)
{
  std::string ret = std::string();
  while (!EndOfFile(**p))
  {
    if (Escape(**p))
    {
      ++(*p);
      return JsonValue::Create(ret, depth);
    }
    if (IsComma(**p))
    {
      return JsonValue::Create(ret, depth);
    }
    ret.append(*p, 1);
    ++(*p);
  }
  NATIVE_ASSERT(false, "JsonParser::ParseJsonValue() : 予期せぬEOFが検出されました。");
  return nullptr;
}

static JsonNode* ParseJsonMap(const char** p, T_UINT8 depth)
{
  JsonNode* ret = JsonNode::Create(depth);
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
      key = ParseString(&(*p), depth);
      continue;
    }
    if (IsValueSeparator(**p))
    {
      ++(*p);
      JsonBase* value = ParseValue(&(*p), depth);
      ret->Put(key, value);
      continue;
    }
    ++(*p);
  }
  if (depth == 0)
  {
    return ret;
  }
  NATIVE_ASSERT(false, "JsonParser::ParseJsonMap() : 予期せぬEOFが検出されました。");
  return ret;
}

static JsonList<JsonBase>* ParseJsonList(const char** p, T_UINT8 depth)
{
  JsonList<JsonBase>* ret = JsonList<JsonBase>::Create(depth);
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
      JsonBase* json_map = ParseJsonMap(&(*p), depth);
      ret->Add(json_map);
      continue;
    }
    if (IsListBracketLeft(**p))
    {
      ++(*p);
      JsonList<JsonBase>* json_list = ParseJsonList(&(*p), depth);
      ret->Add(json_list);
      continue;
    }
    if (!IsComma(**p))
    {
      JsonBase* value = ParseValue(&(*p), depth);
      ret->Add(value);
      continue;
    }
    ++(*p);
  }
  NATIVE_ASSERT(false, "JsonParser::ParseJsonList() : 予期せぬEOFが検出されました。");
  return ret;
}

JsonNode* JsonParser::Parse(const char* json_text)
{
  const char* p = &json_text[0];
  while (IsMapBracketLeft(*p))
  {
    p++;
  }
  p++;
  return ParseJsonMap(&p, 0);
}