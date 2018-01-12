#include "DirectXNativeImplements.h"
#include <XInput.h>

#include "DirectXInputDevice_Keyboard.h"
#include "DirectXInputDevice_XInput.h"
#include "DirectXInputDevice_Mouse.h"

using namespace EngineInput;

enum { KEYBOARD_INPUT_MAX = 26 };

static const DirectXInputDevice_KeyBoard::KeyboardInput KEYBOARD_INPUTS[KEYBOARD_INPUT_MAX] =
{
  { Digital::ID_A, DIK_L },
  { Digital::ID_B, DIK_SEMICOLON },
  { Digital::ID_X, DIK_K },
  { Digital::ID_Y, DIK_O },

  { Digital::ID_L1, DIK_I },
  { Digital::ID_R1, DIK_P },

  { Digital::ID_LEFT, DIK_A },
  { Digital::ID_RIGHT, DIK_D },
  { Digital::ID_UP, DIK_W },
  { Digital::ID_DOWN, DIK_S },

  { Digital::ID_LEFT, DIK_LEFT },
  { Digital::ID_RIGHT, DIK_RIGHT },
  { Digital::ID_UP, DIK_UP },
  { Digital::ID_DOWN, DIK_DOWN },

  { Digital::ID_S0, DIK_Q },
  { Digital::ID_S1, DIK_E },

  { Digital::ID_F1, DIK_1 },
  { Digital::ID_F2, DIK_2 },
  { Digital::ID_F3, DIK_3 },
  { Digital::ID_F4, DIK_4 },
  { Digital::ID_F5, DIK_5 },
  { Digital::ID_F6, DIK_6 },
  { Digital::ID_F7, DIK_7 },
  { Digital::ID_F8, DIK_8 },
  { Digital::ID_F9, DIK_9 },
  { Digital::ID_F10, DIK_0 },
};

enum { XINPUT_INPUT_MAX = 12 };

static const DirectXInputDevice_XInput::XInputInput XINPUT_INPUTS[XINPUT_INPUT_MAX] =
{
  { Digital::ID_A, XINPUT_GAMEPAD_A },
  { Digital::ID_B, XINPUT_GAMEPAD_B },
  { Digital::ID_X, XINPUT_GAMEPAD_X },
  { Digital::ID_Y, XINPUT_GAMEPAD_Y },

  { Digital::ID_L1, XINPUT_GAMEPAD_LEFT_SHOULDER },
  { Digital::ID_R1, XINPUT_GAMEPAD_RIGHT_SHOULDER },

  { Digital::ID_LEFT,   XINPUT_GAMEPAD_DPAD_LEFT },
  { Digital::ID_RIGHT,  XINPUT_GAMEPAD_DPAD_RIGHT },
  { Digital::ID_UP,     XINPUT_GAMEPAD_DPAD_UP },
  { Digital::ID_DOWN,   XINPUT_GAMEPAD_DPAD_DOWN },

  { Digital::ID_S0, XINPUT_GAMEPAD_BACK },
  { Digital::ID_S1, XINPUT_GAMEPAD_START },
};

enum { MOUSE_INPUT_MAX = 1 };
static const DirectXInputDevice_Mouse::MouseInput MOUSE_INPUTS[XINPUT_INPUT_MAX] =
{
  { Digital::ID_X, DirectXInputDevice_Mouse::MOUSE_RGB_BUTTON_LEFT }
};

void DirectXNativeImplements::SetupInputDevices(DirectXInputDeviceManager* manager)
{
  //キーボードは1Pに対応
  manager->LoadDevice(new DirectXInputDevice_KeyBoard(0, KEYBOARD_INPUTS, KEYBOARD_INPUT_MAX));
  manager->LoadDevice(new DirectXInputDevice_Mouse(0, MOUSE_INPUTS, 1, Analog::ID_SCREEN_1_XY, Analog::ID_SCREEN_0_XY));

  //ジョイスティックは(1P～4P)
  manager->LoadDevice(new DirectXInputDevice_XInput(0, 0, XINPUT_INPUTS, XINPUT_INPUT_MAX, Analog::ID_L_0_XY, Analog::ID_R_0_XY, Analog::ID_C_0_XY));
  manager->LoadDevice(new DirectXInputDevice_XInput(1, 1, XINPUT_INPUTS, XINPUT_INPUT_MAX, Analog::ID_L_0_XY, Analog::ID_R_0_XY, Analog::ID_C_0_XY));
  manager->LoadDevice(new DirectXInputDevice_XInput(2, 2, XINPUT_INPUTS, XINPUT_INPUT_MAX, Analog::ID_L_0_XY, Analog::ID_R_0_XY, Analog::ID_C_0_XY));
  manager->LoadDevice(new DirectXInputDevice_XInput(3, 3, XINPUT_INPUTS, XINPUT_INPUT_MAX, Analog::ID_L_0_XY, Analog::ID_R_0_XY, Analog::ID_C_0_XY));
}

