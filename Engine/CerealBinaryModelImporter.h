#pragma once

#include "ModelData.h"

namespace ModelImporter
{

namespace Cereal
{

namespace Binary
{

ModelData* Import(const char* path);

}

}

}