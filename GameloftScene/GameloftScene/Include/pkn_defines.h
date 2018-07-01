#pragma once
//Debug Macros
#if defined(_DEBUG) || defined(DEBUG)	
# define PKN_DEBUG_MODE 1			  //Debug mode is on		  
#else
# define PKN_DEBUG_MODE 0			  //Debug mode is off
#endif

#if DR_DEBUG_MODE
# define PKN_ASSERT(x) assert(x)		  
# define PKN_DEBUG_ONLY(x) x
# define PKN_DEBUG_ONLY_PARAM(x) ,x
#else
# define PKN_ASSERT(x) 
# define PKN_DEBUG_ONLY(x)
# define PKN_DEBUG_ONLY_PARAM(x)
#endif