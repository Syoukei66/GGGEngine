#include "MaterialData.h"
#include "CerealStructArchive.hpp"
#include "CerealArchiveMacro.hpp"
#include "CerealIO.h"
#include "SerealizerTester.h"
#include "SerealizerTestMacro.hpp"

#include "Cereal/types/unordered_map.hpp"

#include "CerealShaderPropertiesArchive.hpp"

//=============================================================================
// Cereal Archive
//=============================================================================
template <class Archive>
void serialize(Archive& ar, MaterialData& value)
{
  ar(value.shader_id_);
  ar(value.protect_);
  ar(value.properties_);
}

//=============================================================================
// Serealizer Test
//=============================================================================
class MaterialDataSerealizerTester : public SerealizerTester
{
public:
  using SerealizerTester::Compare;
  void Compare(const MaterialData& a, const MaterialData& b)
  {
    PushState("StaticModelData");
    COMPARE_ATTR(shader_id_);
    COMPARE_ATTR(protect_);
    for (const auto& pair : a.properties_)
    {
      COMPARE_VALUE(pair.second, b.properties_.at(pair.first), ShaderProperty*);
    }
    PopState();
  }
};

//=============================================================================
// Serealizer / Deserealizer
//=============================================================================
MaterialData* MaterialData::Deserealize(const std::string& path)
{
  return CerealIO::Binary::Import<MaterialData>(path.c_str());
}

void MaterialData::Serealize(const std::string& path, bool test)
{
  CerealIO::Binary::Export<MaterialData>(path.c_str(), this);
  if (test)
  {
    MaterialDataSerealizerTester tester;
    MaterialData* data = Deserealize(path);
    tester.Compare(*this, *data);
    delete data;
  }
}
