#include "DirectInputDevice_Keyboard.h"
#include <Native/Windows/WindowsApplication.h>

DirectInputDevice_KeyBoard::DirectInputDevice_KeyBoard(T_UINT8 handler, const KeyboardInput* inputs, T_UINT8 inputs_count)
  : DirectInputDevice(handler)
  , inputs_(inputs)
  , inputs_count_(inputs_count)
  , diks_()
{}

bool DirectInputDevice_KeyBoard::Init(const SharedRef<Activity>& activity, LPDIRECTINPUT8 input)
{
  //DirectInputDevice�̏�����
  if (FAILED(input->CreateDevice(
    GUID_SysKeyboard,
    &this->device_,
    NULL
  )))
  {
    return false;
  }

  //�f�o�C�X���L�[�{�[�h�ɐݒ�
  if (FAILED(this->device_->SetDataFormat(&c_dfDIKeyboard)))
  {
    return false;
  }

  HWND hwnd = WindowsApplication::GetMainActivityContext().GetWindowHandle();

  //�������x���̐ݒ�
  if (FAILED(this->device_->SetCooperativeLevel(hwnd,
    DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
  {
    return false;
  }

  //�f�o�C�X���擾����
  this->device_->Acquire();

  return true;
}

bool DirectInputDevice_KeyBoard::Uninit(LPDIRECTINPUT8 input)
{
  if (this->device_)
  {
    this->device_->Release();
    this->device_ = NULL;
  }
  return true;
}


void DirectInputDevice_KeyBoard::InputProcess(T_UINT8 handler, const SharedRef<Activity>& activity, EngineInputState* state)
{
  if (FAILED(this->device_->GetDeviceState(sizeof(this->diks_), &this->diks_)))
  {
    this->device_->Acquire();
    return;
  }
}

void DirectInputDevice_KeyBoard::ApplyProcess(T_UINT8 handler, const SharedRef<Activity>& activity, EngineInputState * state)
{
  for (int i = 0; i < this->inputs_count_; ++i)
  {
    state->PreInputDigital(handler, this->inputs_[i].id);
    if (this->diks_[this->inputs_[i].input] & 0x80)
    {
      state->InputDigital(handler, this->inputs_[i].id);
    }
    state->PostInputDigital(handler, this->inputs_[i].id);
  }
}
