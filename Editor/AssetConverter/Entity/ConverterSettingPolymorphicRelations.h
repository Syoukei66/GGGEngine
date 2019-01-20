#pragma once

#include <Entity/File/Material/MaterialAssetConverterSetting.h>
CEREAL_REGISTER_TYPE(MaterialAssetConverterSetting);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ConverterSetting, MaterialAssetConverterSetting);

#include <Entity/File/Mesh/MeshAssetConverterSetting.h>
CEREAL_REGISTER_TYPE(MeshAssetConverterSetting);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ConverterSetting, MeshAssetConverterSetting);

#include <Entity/File/Model/CharacterModel/CharacterModelConverterSetting.h>
CEREAL_REGISTER_TYPE(CharacterModelAssetConverterSetting);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ConverterSetting, CharacterModelAssetConverterSetting);

#include <Entity/File/Model/StaticModel/StaticModelConverterSetting.h>
CEREAL_REGISTER_TYPE(StaticModelAssetConverterSetting);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ConverterSetting, StaticModelAssetConverterSetting);

#include <Entity/File/Raw/RawAssetConverterSetting.h>
CEREAL_REGISTER_TYPE(RawAssetConverterSetting);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ConverterSetting, RawAssetConverterSetting);

#include <Entity/File/Texture/TextureAssetConverterSetting.h>
CEREAL_REGISTER_TYPE(TextureAssetConverterSetting);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ConverterSetting, TextureAssetConverterSetting);

#include <Entity/File/Shader/ShaderAssetConverterSetting.h>
CEREAL_REGISTER_TYPE(ShaderAssetConverterSetting);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ConverterSetting, ShaderAssetConverterSetting);
