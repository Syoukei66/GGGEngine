#include "CerealBinaryModelImporter.h"
#include "CerealBinaryModelArchive.h"
#include "CerealIO.h"

ModelData* ModelImporter::Cereal::Binary::Import(const char* path)
{
  return CerealIO::Binary::Import<ModelData>(path);
}
