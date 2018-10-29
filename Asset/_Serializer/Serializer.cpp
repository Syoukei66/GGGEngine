#include "Serializer.h"

#include <Cereal/cereal.hpp>
#include <Cereal/archives/binary.hpp>

#include <Cereal/types/string.hpp>
#include <Cereal/types/vector.hpp>
#include <Cereal/types/list.hpp>
#include <Cereal/types/deque.hpp>
#include <Cereal/types/unordered_map.hpp>

#include <Cereal/types/polymorphic.hpp>

#include <Asset/TextureAtlas/TextureAtlasData.h>

using namespace std;

namespace Serializer
{
// =================================================================
// SerializeImplements
// =================================================================
//TextureAtlasData
template <class Archive>
void serialize(Archive& ar, TextureAtlasData& value)
{
  ar(value.texture_unique_id_);
  ar(value.texture_indices_);
}

// =================================================================
// SerializeFunctions
// =================================================================
template <typename Type_>
GG_INLINE void Deserialize(const std::string& path, Type_* dest)
{
  ifstream ifs(path, ios::in | ios::binary);
  if (ifs.is_open())
  {
    ::cereal::BinaryInputArchive(ifs)(*dest);
  }
}

template <typename Type_>
GG_INLINE void Serialize(const std::string& path, Type_* data, bool test)
{
  ofstream ofs(path, ios::out | ios::binary | ios::trunc);
  if (ofs.is_open())
  {
    ::cereal::BinaryOutputArchive(ofs)(*data);
  }
}

// =================================================================
// SerializeFunctions
// =================================================================
// TextureAtlasData
void Load(const std::string& path, TextureAtlasData* dest) { Deserialize(path, dest); }
void Save(const std::string& path, TextureAtlasData* data, bool test) { Serialize(path, data, test); }


} // namespace Serializer
