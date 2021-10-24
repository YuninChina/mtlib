#ifndef __PLATFORM_OS_H
#define __PLATFORM_OS_H


#if defined(CONFIG_OS_FREERTOS)
#include "os_freertos.h"
#else
#include "os_linux.h"
#endif


#endif

