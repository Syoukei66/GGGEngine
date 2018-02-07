#pragma once
#include <vector>
#include <string>
#include "NativeType.h"

class CSVToken
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static CSVToken Create(const std::string& str);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  CSVToken(const std::string& str);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  T_INT32 ToInt32() const;
  T_INT64 ToInt64() const;
  T_FLOAT ToFloat() const;
  T_DOUBLE ToDouble() const;
  const std::string& ToString() const;
  
  // =================================================================
  // Data Member
  // =================================================================
private:
  const std::string str_;
};

class CSVTokenizer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  CSVTokenizer(const std::string& str);
  CSVTokenizer(const CSVTokenizer& other);
  ~CSVTokenizer();

  // =================================================================
  // Method
  // =================================================================
public:
  void Reset();
  bool HasNextToken();
  const CSVToken& NextToken();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline std::vector<CSVToken>::iterator Begin()
  {
    return this->tokens_.begin();
  }

  inline std::vector<CSVToken>::iterator End()
  {
    return this->tokens_.end();
  }

  inline size_t GetSize() const
  {
    return this->tokens_.size();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::vector<CSVToken> tokens_;
  T_UINT16 now_token_index_;
};
