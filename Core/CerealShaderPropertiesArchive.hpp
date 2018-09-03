#pragma once

#include "ShaderProperties.h"
#include "CerealStructArchive.hpp"
#include "CerealArchiveMacro.hpp"
#include "CerealIO.h"
#include "SerealizerTester.h"
#include "SerealizerTestMacro.hpp"

#include "cereal/types/polymorphic.hpp"

#include "Cereal/archives/binary.hpp"
#include "Cereal/archives/xml.hpp"
#include "Cereal/archives/json.hpp"

// =================================================================
// primitive
// =================================================================
template <class Archive>
void serialize(Archive& ar, ShaderProperty_bool& value)
{
  ar(value.value_);
}

template <class Archive>
void serialize(Archive& ar, ShaderProperty_int& value)
{
  ar(value.value_);
}

template <class Archive>
void serialize(Archive& ar, ShaderProperty_float& value)
{
  ar(value.value_);
}

// =================================================================
// struct
// =================================================================
template <class Archive>
void serialize(Archive& ar, ShaderProperty_vec2f& value)
{
  ar(value.value_);
}

template <class Archive>
void serialize(Archive& ar, ShaderProperty_vec3f& value)
{
  ar(value.value_);
}

template <class Archive>
void serialize(Archive& ar, ShaderProperty_vec4f& value)
{
  ar(value.value_);
}

template <class Archive>
void serialize(Archive& ar, ShaderProperty_color& value)
{
  ar(value.value_);
}

template <class Archive>
void serialize(Archive& ar, ShaderProperty_matrix& value)
{
  ar(value.value_);
}

// =================================================================
// resource
// =================================================================
template <class Archive>
void serialize(Archive& ar, ShaderProperty_texture& value)
{
  ar(value.value_);
}

CEREAL_REGISTER_POLYMORPHIC_RELATION(ShaderProperty, ShaderProperty_bool)
CEREAL_REGISTER_POLYMORPHIC_RELATION(ShaderProperty, ShaderProperty_int)
CEREAL_REGISTER_POLYMORPHIC_RELATION(ShaderProperty, ShaderProperty_float)
CEREAL_REGISTER_POLYMORPHIC_RELATION(ShaderProperty, ShaderProperty_vec2f)
CEREAL_REGISTER_POLYMORPHIC_RELATION(ShaderProperty, ShaderProperty_vec3f)
CEREAL_REGISTER_POLYMORPHIC_RELATION(ShaderProperty, ShaderProperty_vec4f)
CEREAL_REGISTER_POLYMORPHIC_RELATION(ShaderProperty, ShaderProperty_color)
CEREAL_REGISTER_POLYMORPHIC_RELATION(ShaderProperty, ShaderProperty_matrix)
CEREAL_REGISTER_POLYMORPHIC_RELATION(ShaderProperty, ShaderProperty_texture)
