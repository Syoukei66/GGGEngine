#pragma once

#include <Cereal/types/string.hpp>
#include <Cereal/types/polymorphic.hpp>
#include <Cereal/archives/binary.hpp>
#include <Cereal/archives/json.hpp>

#include "CerealIO.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "Color.h"
#include "Bounds.h"

#include "ShaderProperties.h"

template <class Archive>
void serialize(Archive& archive, TVec2f& value)
{
  archive(cereal::binary_data(value.data, sizeof(T_FLOAT) * 2));
}

template <class Archive>
void serialize(Archive& archive, TVec3f& value)
{
  archive(cereal::binary_data(value.data, sizeof(T_FLOAT) * 3));
}

template <class Archive>
void serialize(Archive& archive, TVec4f& value)
{
  archive(cereal::binary_data(value.data, sizeof(T_FLOAT) * 4));
}

template <class Archive>
void serialize(Archive& archive, TColor& value)
{
  archive(cereal::binary_data(value.data, sizeof(T_FLOAT) * 4));
}

template <class Archive>
void serialize(Archive& archive, Matrix4x4& value)
{
  archive(cereal::binary_data(value.data, sizeof(T_FLOAT) * 16));
}

template <class Archive>
void serialize(Archive& archive, Bounds& data)
{
  archive(data.center);
  archive(data.extents);
}

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


#define ARRAY_ARCHIVE(var, value, size) if (!var)\
{\
  var = new value[size]();\
}\
archive(cereal::binary_data(var, sizeof(value) * (size)));

#define SERIALIZE_METHOD(type)\
public:\
  static type* Deserialize(const std::string& path);\
  void Serialize(const std::string& path, bool test = false) const;

#define SERIALIZABLE(type)\
SERIALIZE_METHOD(type)\
template <class Archive>\
void serialize(Archive& ar, ShaderProperty_bool& value)

#define SERIALIZER_IMPL(type)\
type* type::Deserialize(const std::string& path)\
{\
  return CerealIO::Binary::Import<type>(path.c_str());\
}\
\
void type::Serialize(const std::string& path, bool test) const\
{\
  CerealIO::Binary::Export<type>(path.c_str(), this);\
  if (test)\
  {\
    type##SerializerTester tester;\
    type* data = Deserialize(path);\
    tester.Compare(*this, *data);\
    delete data;\
  }\
}