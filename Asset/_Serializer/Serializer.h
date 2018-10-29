#pragma once

struct TextureAtlasData;

namespace Serializer
{
// TextureAtlasData
void Load(const std::string& path, TextureAtlasData* dest);
void Save(const std::string& path, TextureAtlasData* data, bool test = false);



};