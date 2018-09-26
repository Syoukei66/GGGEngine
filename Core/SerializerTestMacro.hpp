#pragma once

//ヘッダー側でインクルードしない

#define COMPARE_VALUE(a, b, type) if (a != b) { PushState(#type); AddMessage(#type); PopState(); }

#define COMPARE(type) if (a != b) { PushState(#type); AddMessage(a, b); PopState(); }
#define COMPARE_ATTR(name) PushState(#name); Compare(a.##name, b.##name); PopState();
#define COMPARE_ATTRS(name, count) for (T_UINT32 i = 0; i < a.##count; ++i) { COMPARE_ATTR(name##[i]) }
#define COMPARE_ATTRMAP(name, type) for (const auto& pair : a.##name) { COMPARE_VALUE(pair.second, b.##name.at(pair.first), type*); }