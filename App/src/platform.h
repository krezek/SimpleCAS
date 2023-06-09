#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <objbase.h>
#include <UIRibbon.h>
#include <initguid.h>
#include <propvarutil.h>
#include "strsafe.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <tchar.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


#ifdef _DEBUG
#include <crtdbg.h>
#endif

#endif /* _PLATFORM_H_ */

