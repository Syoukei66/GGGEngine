#pragma once

#include <string>

#include "Cereal\cereal.hpp"
#include "Cereal\types\string.hpp"
#include "Cereal\types\common.hpp"

#include "../Common/NativeType.h"


struct Setting
{
  Setting() = default;

  static Setting* Create();

  template<class Archive>
  void serialize(Archive& ar, std::uint32_t const version)
  {
    if (version > 1)
    {
      ar(CEREAL_NVP(engine_name));
    }
    ar(CEREAL_NVP(input_path));
    ar(CEREAL_NVP(output_path));
  }

  std::string engine_name;
  std::string input_path;
  std::string output_path;

};
CEREAL_CLASS_VERSION(Setting, 2);