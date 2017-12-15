#pragma once

#include "ParticleData.h"
#include "TextureAtlas.h"

namespace ParticleDataLoader
{

ParticleData* LoadParticleData(const char* path, TextureAtlas* atlas);

}