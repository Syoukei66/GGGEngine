#include "AssetProgramGenerator_identifier.h"
#include <regex>

// =================================================================
// Constructor / Destructor
// =================================================================
IdentifierGenerator::IdentifierGenerator(T_UINT32 skip_head, T_UINT32 skip_tail)
  : skip_head_(skip_head)
  , skip_tail_(skip_tail)
  , cache_()
{
}

// =================================================================
// Methods
// =================================================================
std::string IdentifierGenerator::CreateIdentifier(const AssetInfo* info) const
{
  const auto& itr = this->cache_.find(info);
  if (itr != this->cache_.end())
  {
    return itr->second;
  }
  //�t�@�C�������L�����������������ꍇ�X�l�[�N�����ɕύX
  std::string snake_filename = info->GetURI().GetFullPath();
  snake_filename = std::regex_replace(snake_filename, std::regex("([a-z])([A-Z])"), "$1_$2");

  //�t�@�C������啶���ɕϊ�
  std::string upper_filename = snake_filename;
  std::transform(upper_filename.begin(), upper_filename.end(), upper_filename.begin(), ::toupper);

  //�t�@�C��������g���q����菜��
  std::string::size_type pos;
  pos = upper_filename.find_last_of(".");
  upper_filename = upper_filename.substr(0, pos);

  //�v���O�����������̖��O(ID)�̍쐬
  //�v���O�����Ŏg�p�ł��Ȃ�������ϊ�
  std::string id = std::regex_replace(upper_filename, std::regex("[^a-zA-Z0-9]+"), "_");

  //�ŏ��̃f�B���N�g�����ʎq���폜
  for (T_UINT8 i = 0; i < this->skip_head_; ++i)
  {
    std::string::size_type cut_pos = id.find_first_of("_");
    id = id.substr(cut_pos + 1, id.length() - cut_pos - 1);
  }

  //�����̃f�B���N�g�����ʎq���폜
  for (T_UINT8 i = 0; i < this->skip_tail_; ++i)
  {
    std::string::size_type cut_pos = id.find_last_of("_");
    id = id.substr(0, cut_pos);
  }
  const_cast<IdentifierGenerator*>(this)->cache_[info] = id;
  return id;
}
