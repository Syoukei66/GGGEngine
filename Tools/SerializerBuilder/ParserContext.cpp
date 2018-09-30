#include "ParserContext.h"
#include "Parser.h"

// =================================================================
// Constructor / Destructor
// =================================================================
ParserContext::ParserContext(Parser* root)
  : root_(root)
{
}

ParserContext::~ParserContext()
{
  delete this->root_;
}

// =================================================================
// Methods
// =================================================================
void ParserContext::PushParser(Parser* parser)
{
  this->current_->AddChild(parser);
  parser->SetParent(this->current_);
  this->current_ = parser;
}

void ParserContext::PopParser()
{
  this->current_ = this->current_->GetParent();
}
