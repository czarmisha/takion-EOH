#pragma once

#define T_STR(value) #value
#define T_STRINGIZE(value) T_STR(value)

#ifdef _WIN64
#define TakionPlatform x64
#else
#define TakionPlatform x32
#endif

#ifdef _DEBUG
#define TakionConfiguration Debug
#else
#ifdef T_RELEASED
#define TakionConfiguration ReleaseD
#else
#define TakionConfiguration Release
#endif
#endif

#define TakionProductName Takion
#define TakionProductNameStr T_STRINGIZE(TakionProductName)
#define TakionFileNameStr T_STRINGIZE(TakionProductName.exe)

#define TakionCompanyName Takion Technologies LLC
#define TakionCompanyNameStr T_STRINGIZE(TakionCompanyName)

#define TakionLegalCopyright TakionCompanyName. All rights reserved.
#define TakionLegalCopyrightStr T_STRINGIZE(TakionLegalCopyright)

