#pragma once

//ヘッダー側でインクルードしない

#define COMPARE(type) if (a != b) { PushState(#type); AddMessage(a, b); PopState(); }
#define COMPARE_ATTR(name) PushState(#name); Compare(a.##name, b.##name); PopState();
#define COMPARE_ATTRS(name, count) for (int i = 0; i < a.##count; ++i) { COMPARE_ATTR(name##[i]) }