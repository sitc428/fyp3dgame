/**
  Check is like an assert.  If a condition wrapped with a check evaluates to false,
  the application will halt execution signaling an error.  If the debugger is present the check will trigger 
  a breakpoint halt in the place where the check failed.  Checks are only defined in the debug build, in retail they 
  will automatically compile out.
  */

#ifndef __CHECK_HPP__
#define __CHECK_HPP__

#ifdef _DEBUG
#define CHECKS_ON
#endif

#ifdef CHECKS_ON 

#include <windows.h>

#define ERROR_DISP(msg)                                                       \
{                                                                             \
	printf("ERROR: %s (file:%s line:%d)\n", #msg, __FILE__, __LINE__);      \
	abort();                                                              \
}

#define check(cond)                       \
{                                         \
	if ((cond) == false)                \
	{                                   \
		ERROR_DISP(cond)              \
	}                                   \
}

#else

#define ERROR_DISP(msg) {}

#define check(cond) {}

#endif //CHECKS_ON

#endif //__CHECK_HPP__
