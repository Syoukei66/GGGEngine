#include "BaseConverter.h"

#include "../Asset/CerealIO.h"
#include "FileUtil.h"
#include "Logger.h"

BaseConverter::BaseConverter()
  : program_generator_()
{
}

BaseConverter::~BaseConverter()
{
}

void BaseConverter::Convert() const
{
  for (AssetInfo* info : this->target_infomations_)
  {
    //変換後ファイルが消えているか
    const bool output_file_exists = std::ifstream(info->output_path).is_open();

    //変換対象ファイルのタイムスタンプが一致しているか
    const std::string time_stamp = Util::File::GetTimeStamp(info->full_path);
    const bool asset_changed = info->meta_data->time_stamp != time_stamp;

    if (output_file_exists && !asset_changed)
    {
      Logger::SkipAssetLog(info);
      continue;
    }

    this->ConvertProcess(info);
    info->meta_data->time_stamp = time_stamp;
  }
}

std::string BaseConverter::CreateHeaderProgram() const
{
  return this->program_generator_.CreateProgram([&](const AssetProgram::DefinitionGenerator& generator)
  {
    std::string ret;
    for (AssetInfo* info : this->target_infomations_)
    {
      ret.append(generator.CreateHeaderProgram(info));
    }
    return ret;
  });
}

std::string BaseConverter::CreateCppProgram() const
{
  return this->program_generator_.CreateProgram([&](const AssetProgram::DefinitionGenerator& generator)
  {
    std::string ret;
    for (AssetInfo* info : this->target_infomations_)
    {
      ret.append(generator.CreateCppProgram(info));
    }
    return ret;
  });
}

void BaseConverter::AddTargetAsset(AssetInfo* info)
{
  if (!this->IsTarget(info->extension))
  {
    return;
  }
  this->target_infomations_.push_back(info);
}

void BaseConverter::RemoveTargetAsset(AssetInfo* info)
{
  if (!this->IsTarget(info->extension))
  {
    return;
  }
  for (std::vector<AssetInfo*>::iterator itr = this->target_infomations_.begin(), end = this->target_infomations_.end(); itr != end; ++itr)
  {
    if ((*itr) == info)
    {
      this->target_infomations_.erase(itr);
      return;
    }
  }
}

void BaseConverter::ClearTargetAsset()
{
  this->target_infomations_.clear();
}
