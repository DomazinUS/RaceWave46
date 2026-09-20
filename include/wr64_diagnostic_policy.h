#pragma once

// Diagnostics are disabled by default and require an explicit build option.
#ifndef WR64_ENABLE_DIAGNOSTICS
#define WR64_ENABLE_DIAGNOSTICS 0
#endif

#define WR64_DIAGNOSTIC_ENABLED (WR64_ENABLE_DIAGNOSTICS != 0)

// Keep diagnostic argument evaluation and formatting out of clean builds.
#if WR64_ENABLE_DIAGNOSTICS
#define WR64_DIAGNOSTIC_LOG(...) do { __VA_ARGS__; } while (0)
#define WR64_DIAGNOSTIC_ENV(expression) (expression)
#else
#define WR64_DIAGNOSTIC_LOG(...) do { } while (0)
#define WR64_DIAGNOSTIC_ENV(expression) ((char *)0)
#endif
