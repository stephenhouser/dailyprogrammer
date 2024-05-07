#if !defined(COMMON_H)
#define COMMON_H

/* http://stackoverflow.com/questions/2115867/is-there-a-define-for-c99 */
#if defined(__STDC__)
# define C89
# if defined(__STDC_VERSION__)
#  define C90
#  if (__STDC_VERSION__ >= 199409L)
#   define C94
#  endif
#  if (__STDC_VERSION__ >= 199901L)
#   define C99
#  endif
# endif
#endif

typedef enum {
	SUCCESS = 0,
	FAILURE = 1,
	ALLOC_ERROR = 2
} cb_status;

#endif