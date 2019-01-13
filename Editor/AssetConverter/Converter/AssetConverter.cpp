#include "AssetConverter.h"
#include "AssetConverterContext.h"

// =================================================================
// Constructor / Destructor
// =================================================================
AssetConverter::AssetConverter(const std::string& id, AssetImporter* importer, AssetExporter* exporter, AssetProgramGenerator* program_generator)
  : id_(id)
  , importer_(importer)
  , exporter_(exporter)
  , program_generator_(program_generator)
{}

AssetConverter::~AssetConverter()
{
  delete this->importer_;
  delete this->exporter_;
  delete this->program_generator_;
}

// =================================================================
// Methods
// =================================================================
void* AssetConverter::ImportImmediately(AssetMetaData* meta_data, AssetConverterContext* context)
{
  if (!this->importer_)
  {
    return nullptr;
  }
  return this->importer_->ImportImmediately(meta_data, context);
}

void AssetConverter::ExportImmediately(AssetMetaData* meta_data, const AssetConverterContext* context) const
{
  this->exporter_->Export(meta_data, context);
}

void AssetConverter::CreateProgram(const std::vector<SharedRef<AssetEntity>>& entities, std::string * cpp, std::string * header) const
{
  if (!this->program_generator_)
  {
    return;
  }
  this->program_generator_->CreateHeaderProgram(entities, header);
  this->program_generator_->CreateCppProgram(entities, cpp);
}
