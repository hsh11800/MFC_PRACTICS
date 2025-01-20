#pragma once
#if !defined(_M_IX86)
#define MY_ASSERT(expr) \
if (!(expr)) \
{\
	__debugbreak();\
}
#else
#define MY_ASSERT(expr) \
if (!(expr)) \
{\
	__asm {\
		int 3\
	}\
}
#endif