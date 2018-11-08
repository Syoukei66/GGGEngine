#pragma once

#include <Native/Windows/PlatformMacro.h>

#if GG_GRAPHICS_API_DX9
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "xinput.lib")
#pragma comment(lib, "dxguid.lib")
#include <Native/Windows/API/Graphics/DX9/DX9GraphicsAPI.h>
#else

#endif