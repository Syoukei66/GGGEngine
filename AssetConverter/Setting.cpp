#include "Setting.h"

Setting* Setting::Create()
{
  char input_path[256]{};
  char output_path[256]{};
  char extension[256]{};
  std::cout << "ConvertConfig.json�𐶐����܂�" << std::endl;
  std::cout << "�ϊ��Ώۃt�@�C��������f�B���N�g�����w�肵�Ă�������" << std::endl;
  std::cin >> input_path;
  std::cout << "�ϊ������t�@�C����ۑ�����f�B���N�g�����w�肵�Ă�������" << std::endl;
  std::cin >> output_path;

  Setting* ret = new Setting();
  ret->input_path = input_path;
  ret->output_path = output_path;
  return ret;
}