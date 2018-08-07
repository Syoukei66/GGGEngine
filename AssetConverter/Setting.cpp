#include "Setting.h"

Setting* Setting::Create()
{
  char input_path[256]{};
  char output_path[256]{};
  char extension[256]{};
  std::cout << "ConvertConfig.jsonを生成します" << std::endl;
  std::cout << "変換対象ファイルがあるディレクトリを指定してください" << std::endl;
  std::cin >> input_path;
  std::cout << "変換したファイルを保存するディレクトリを指定してください" << std::endl;
  std::cin >> output_path;

  Setting* ret = new Setting();
  ret->input_path = input_path;
  ret->output_path = output_path;
  return ret;
}