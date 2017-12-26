#pragma once
#include <vector>
#include "NativeType.h"

class CSVToken
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  CSVToken(T_UINT32 line_index, T_UINT16 token_index, const char* str, T_UINT8 len);
  ~CSVToken();

  // =================================================================
  // Method
  // =================================================================
private:
  void ThrowException(const char* message);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  T_INT32 GetInt32();
  T_INT64 GetInt64();
  T_FLOAT GetFloat();
  T_DOUBLE GetDouble();
  const char* GetString();
  void SetException(void(*exception)(CSVToken*, const char* message));

  // =================================================================
  // Data Member
  // =================================================================
private:
  char* str_;
  char* trimed_str_;
  T_UINT32 line_index_;
  T_UINT16 token_index_;
  void(*exception_)(CSVToken*, const char* message);
};

class CSVTokenizer
{
  // =================================================================
  // Method
  // =================================================================
public:
  void Prepare(T_UINT32 line_index, const char* txt);
  bool HasNextToken();
  CSVToken* NextToken();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline std::vector<CSVToken*>::iterator Begin()
  {
    return this->tokens_.begin();
  }

  inline std::vector<CSVToken*>::iterator End()
  {
    return this->tokens_.end();
  }

  inline size_t GetSize() const
  {
    return this->tokens_.size();
  }

  inline void SetException(void(*exception)(CSVToken*, const char* message))
  {
    this->exception_ = exception;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::vector<CSVToken*> tokens_;
  T_UINT16 now_token_index_;
  void(*exception_)(CSVToken*, const char* message);
};
