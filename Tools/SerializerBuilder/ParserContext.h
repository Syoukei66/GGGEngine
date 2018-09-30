#pragma once

class Parser;
class TypeEntity;

class ParserContext
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ParserContext(Parser* root);
  ~ParserContext();

  // =================================================================
  // Methods
  // =================================================================
public:
  void PushParser(Parser* parser);
  void PopParser();

  inline void AddSerializableType(const TypeEntity& entity)
  {
    this->serializable_types_.emplace_back(entity);
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline Parser* CurrentParser()
  {
    return this->current_;
  }

  // =================================================================
  // Data Members
  // =================================================================
public:
  Parser* root_;
  Parser* current_;

  std::vector<TypeEntity> serializable_types_;

};