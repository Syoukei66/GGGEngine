#pragma once

#include "Parser.h"

class ProgramParser : public Parser
{
  // =================================================================
  // Methods
  // =================================================================
public:
  virtual bool Eat(const std::string& token, ParserContext* context) override;

};