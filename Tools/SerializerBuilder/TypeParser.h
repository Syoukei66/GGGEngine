#pragma once

#include "Parser.h"

class TypeParser : public Parser
{
  enum State
  {
    STATE_NAME,
    STATE_TYPE_NAME,
    STATE_VARIANT_NAME,
  };

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual bool Eat(const std::string& token, ParserContext* context) override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  State state_;
  std::string name_;

  std::string type_name_buf_;
  std::string variant_name_buf_;

};