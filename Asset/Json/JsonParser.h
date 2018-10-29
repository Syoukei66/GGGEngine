#pragma once

#include <map>
#include <string>
#include <vector>

#include "../Core/NativeAssert.h"
#include <Core/NativeType.h>

//=============================================================================
// JsonBase
//=============================================================================
class JsonBase
{
protected:
  JsonBase(T_UINT8 depth);
  virtual ~JsonBase() {}

public:
  void Release();
  virtual const std::string ToString() const = 0;

protected:
  void ApplyDepth(std::string& str, T_UINT8 depth) const;

protected:
  const T_UINT8 depth_;
};

//=============================================================================
// JsonString
//=============================================================================
class JsonString : public JsonBase
{
public:
  GG_INLINE static JsonString* Create(T_UINT8 depth)
  {
    return new JsonString("", depth);
  }
  GG_INLINE static JsonString* Create(const std::string& text, T_UINT8 depth)
  {
    return new JsonString(text, depth);
  }

private:
  JsonString(const std::string& text, T_UINT8 depth);

public:
  operator const std::string() const
  {
    return this->StringValue();
  }
  JsonString& operator = (const std::string& s)
  {
    this->text_ = s;
    return *this;
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
  GG_INLINE static JsonValue* Create(T_UINT8 depth)
  {
    return new JsonValue("", depth);
  }
  GG_INLINE static JsonValue* Create(const std::string& text, T_UINT8 depth)
  {
    return new JsonValue(text, depth);
  }

private:
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
  operator bool() const
  {
    return this->BoolValue();
  }

  JsonValue& operator = (const T_INT32& i)
  {
    this->text_ = std::to_string(i);
    return *this;
  }
  JsonValue& operator = (const T_FLOAT& f)
  {
    this->text_ = std::to_string(f);
    return *this;
  }
  JsonValue& operator = (const bool& b)
  {
    this->text_ = std::to_string(b);
    return *this;
  }

public:
  T_INT32 IntValue(T_INT32 deflt = 0) const;
  T_FLOAT FloatValue(T_FLOAT deflt = 0.0f) const;
  bool BoolValue(bool deflt = false) const;

public:
  virtual const std::string ToString() const override;

private:
  std::string text_;
};

class JsonNode;

//=============================================================================
// JsonList
//=============================================================================
template <class T>
class JsonList : public JsonBase
{
public:
  GG_INLINE static JsonList<T>* Create(T_UINT8 depth)
  {
    return new JsonList<T>(depth);
  }

private:
  JsonList(T_UINT8 depth)
    : JsonBase(depth)
    , value_list_()
  {}
  virtual ~JsonList()
  {
    for (T* value : this->value_list_)
    {
      value->Release();
    }
  }

public:
  T* Add(T* value)
  {
    this->value_list_.emplace_back(value);
    return value;
  }

  T* Add()
  {
    T* ret = T::Create(this->depth_ + 1);
    this->value_list_.emplace_back(ret);
    return ret;
  }

  T* Get(T_UINT16 index) const
  {
    if (index >= this->value_list_.size())
    {
      return nullptr;
    }
    return this->value_list_[index];
  }
  T* Gain(T_UINT16 index)
  {
    if (index >= this->value_list_.size())
    {
      this->value_list_.emplace_back(T::Create(this->depth_ + 1));
    }
    return this->value_list_[index];
  }
  bool Gain(T_UINT16 index, T** dest)
  {
    bool created = false;
    while (index >= this->value_list_.size())
    {
      this->value_list_.emplace_back(T::Create(this->depth_ + 1));
      created = true;
    }
    *dest = this->value_list_[index];
    return created;
  }
  GG_INLINE const size_t GetSize() const
  {
    return this->value_list_.size();
  }

public:
  using iterator = typename std::vector<T*>::iterator;
  using const_iterator = typename std::vector<T*>::const_iterator;

  iterator begin() { return this->value_list_.begin(); }
  iterator end() { return this->value_list_.end(); }
  const_iterator begin() const { return this->value_list_.begin(); }
  const_iterator end() const { return this->value_list_.end(); }

public:
  virtual const std::string ToString() const override
  {
    std::string ret = std::string();
    ret.append("\n");
    this->ApplyDepth(ret, this->depth_);
    ret.append("[");
    bool first = true;
    for (T* value : this->value_list_)
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
      this->ApplyDepth(ret, this->depth_ + 1);
      ret.append(value->ToString());
    }
    ret.append("\n");
    ApplyDepth(ret, this->depth_);
    ret.append("]");
    return ret;
  }

private:
  std::vector<T*> value_list_;
};

//=============================================================================
// JsonNode
//=============================================================================
class JsonNode : public JsonBase
{
public:
  GG_INLINE static JsonNode* Create(T_UINT8 depth)
  {
    return new JsonNode(depth);
  }
  GG_INLINE static JsonNode* CreateRoot()
  {
    return new JsonNode(0);
  }

private:
  JsonNode(T_UINT8 depth);
  virtual ~JsonNode();

public:
  GG_INLINE JsonBase* Put(const std::string& key, JsonBase* base)
  {
    return this->Put<JsonBase>(key, base);
  }

  GG_INLINE JsonNode* PutNode(const std::string& key, JsonNode* node)
  {
    return this->Put<JsonNode>(key, node);
  }
  GG_INLINE JsonNode* PutNode(const std::string& key)
  {
    return this->Put<JsonNode>(key);
  }
  GG_INLINE JsonNode* GainNode(const std::string& key)
  {
    return this->Gain<JsonNode>(key);
  }
  GG_INLINE bool GainNode(const std::string& key, JsonNode** dest)
  {
    return this->Gain<JsonNode>(key, dest);
  }
  GG_INLINE JsonNode* GetNode(const std::string& key)
  {
    return this->Get<JsonNode>(key);
  }
  GG_INLINE const JsonNode* GetNode(const std::string& key) const
  {
    return this->Get<JsonNode>(key);
  }

  template <class T>
  GG_INLINE JsonList<T>* PutList(const std::string& key, JsonList<T>* list)
  {
    return this->Put<JsonList<T>>(key, list);
  }
  template <class T>
  GG_INLINE JsonList<T>* PutList(const std::string& key)
  {
    return this->Put<JsonList<T>>(key);
  }
  template <class T>
  GG_INLINE JsonList<T>* GainList(const std::string& key)
  {
    return Gain<JsonList<T>>(key);
  }
  template <class T>
  GG_INLINE bool GainList(const std::string& key, JsonList<T>** dest)
  {
    return Gain<JsonList<T>>(key, dest);
  }
  template <class T>
  GG_INLINE JsonList<T>* GetList(const std::string& key)
  {
    return Get<JsonList<T>>(key);
  }
  template <class T>
  GG_INLINE const JsonList<T>* GetList(const std::string& key) const
  {
    return Get<JsonList<T>>(key);
  }

  GG_INLINE JsonString* Put(const std::string& key, const std::string& value)
  {
    return &(*this->PutString(key) = value);
  }
  GG_INLINE JsonString* PutString(const std::string& key, JsonString* str)
  {
    return this->Put<JsonString>(key, str);
  }
  GG_INLINE JsonString* PutString(const std::string& key)
  {
    return this->Put<JsonString>(key);
  }
  GG_INLINE JsonString* GainString(const std::string& key)
  {
    return this->Gain<JsonString>(key);
  }
  GG_INLINE bool GainString(const std::string& key, JsonString** dest)
  {
    return this->Gain<JsonString>(key, dest);
  }
  GG_INLINE JsonString* GetString(const std::string& key)
  {
    return this->Get<JsonString>(key);
  }
  GG_INLINE const JsonString* GetString(const std::string& key) const
  {
    return this->Get<JsonString>(key);
  }

  GG_INLINE JsonValue* Put(const std::string& key, T_INT32 value)
  {
    return &(*this->PutValue(key) = value);
  }
  GG_INLINE JsonValue* Put(const std::string& key, T_FLOAT value)
  {
    return &(*this->PutValue(key) = value);
  }
  GG_INLINE JsonValue* Put(const std::string& key, bool value)
  {
    return &(*this->PutValue(key) = value);
  }
  GG_INLINE JsonValue* PutValue(const std::string& key, JsonValue* value)
  {
    return this->Put<JsonValue>(key, value);
  }
  GG_INLINE JsonValue* PutValue(const std::string& key)
  {
    return this->Put<JsonValue>(key);
  }
  GG_INLINE JsonValue* GainValue(const std::string& key)
  {
    return this->Gain<JsonValue>(key);
  }
  GG_INLINE bool GainValue(const std::string& key, JsonValue** dest)
  {
    return this->Gain<JsonValue>(key, dest);
  }
  GG_INLINE JsonValue* GetValue(const std::string& key)
  {
    return this->Get<JsonValue>(key);
  }
  GG_INLINE const JsonValue* GetValue(const std::string& key) const
  {
    return this->Get<JsonValue>(key);
  }

private:
  template <class T>
  T* Put(const std::string& key, T* value)
  {
    this->value_map_[key] = value;
    return value;
  }
  template <class T>
  T* Put(const std::string& key)
  {
    T* value = T::Create(this->depth_ + 1);
    this->value_map_[key] = value;
    return value;
  }
  template <class T>
  T* Gain(const std::string& key)
  {
    if (this->value_map_.find(key) == this->value_map_.end())
    {
      this->value_map_[key] = T::Create(this->depth_ + 1);
    }
    return (T*)this->value_map_.at(key);
  }
  template <class T>
  bool Gain(const std::string& key, T** dest)
  {
    bool created = false;
    if (this->value_map_.find(key) == this->value_map_.end())
    {
      this->value_map_[key] = T::Create(this->depth_ + 1);
      created = true;
    }
    *dest = (T*)this->value_map_.at(key);
    return created;
  }
  template <class T>
  T* Get(const std::string& key)
  {
    if (this->value_map_.find(key) == this->value_map_.end())
    {
      return nullptr;
    }
    return (T*)this->value_map_.at(key);
  }
  template <class T>
  const T* Get(const std::string& key) const
  {
    if (this->value_map_.find(key) == this->value_map_.end())
    {
      return nullptr;
    }
    return (T*)this->value_map_.at(key);
  }
public:
  virtual const std::string ToString() const override;

private:
  std::map<std::string, JsonBase*> value_map_;
};

//=============================================================================
// JsonParser
//=============================================================================
class JsonParser
{
public:
  JsonNode* Parse(const char* json_text);

};
