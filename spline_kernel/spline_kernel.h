// spline_kernel.h - Contains declarations of math functions
#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

// Get the position of the current value in the sequence.
extern "C" MATHLIBRARY_API unsigned meaning_of_life();