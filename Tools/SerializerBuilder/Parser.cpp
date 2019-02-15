#include "Parser.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Parser::Parser()
  : parent_()
  , children_()
{
}

Parser::~Parser()
{
  for (Parser* child : this->children_)
  {
    delete child;
  }
}

// =================================================================
// Methods
// =================================================================
void Parser::AddChild(Parser* child)
{
  this->children_.push_back(child);
}
