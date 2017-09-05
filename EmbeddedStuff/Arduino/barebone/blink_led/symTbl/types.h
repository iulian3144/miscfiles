#ifndef __INCvxTypesh
#define __INCvxTypesh

#ifdef _WRS_KERNEL
#include <types/vxANSI.h>	/* includes kernel's stdint.h */
#else
#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
/*
 * The definitions brought by stdint.h may not be made visible through the
 * inclusion of many POSIX header files, including a number which - usually
 * indirectly - include types/vxTypes.h for some other reason. So we do _not_
 * include stdint.h when the application declares itself POSIX conforming.
 */
#include <stdint.h>	/* ANSI C / POSIX.1 type definitions */
#endif  /* _POSIX_xxx_SOURCE */
#endif /* _WRS_KERNEL */

/* typedef ssize_t */
// #include <base/b_ssize_t.h>

/* typedef cpuset_t is not required for POSIX */

// #include <base/b_cpuset_t.h>

/* typedef phys_cpuset_t is not required for POSIX nor RTPs */

#if !defined(__RTP__)  /* define only if not RTP */
// #include <base/b_phys_cpuset_t.h>
#endif /* __RTP__ */

/* typedef atomic_t is not required for POSIX */

// #include <base/b_atomic_t.h>

#if !defined(__RTP__)  /* define only if not RTP */
/* typedef time_t */
// #include <base/b_time_t.h>
#endif /* __RTP__ */

/* POSIX required */

/* typedef dev_t */
// #include <base/b_dev_t.h>

/* typedef gid_t */
// #include <base/b_gid_t.h>

/* typedef ino_t */
// #include <base/b_ino_t.h>

/* typedef mode_t */
// #include <base/b_mode_t.h>

/* typedef nlink_t */
// #include <base/b_nlink_t.h>

/* typedef off_t */
// #include <base/b_off_t.h>

/* typedef pid_t.h */
// #include <base/b_pid_t.h>

/* typedef uid_t */
// #include <base/b_uid_t.h>

/* typedef blksize_t */
// #include <base/b_blksize_t.h>

/* typedef blkcnt_t */
// #include <base/b_blkcnt_t.h>

/* This is for VSB option _WRS_CONFIG_LP64 */
// #include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__RTP__)
#ifdef _TYPE_fpos_t
#define _FPOS_T
_TYPE_fpos_t;
#undef _TYPE_fpos_t
#endif
#endif /* __RTP__ */

typedef unsigned long int ULONG;
typedef unsigned short int UINT16;
typedef unsigned int BOOL;
typedef int STATUS;
#define IMPORT extern

/* The following types have been added to support the dual-stack */
#ifdef _TYPE_u_int8_t
_TYPE_u_int8_t;
#undef _TYPE_u_int8_t
#endif

#ifdef _TYPE_u_int16_t
_TYPE_u_int16_t;
#undef _TYPE_u_int16_t
#endif

#ifdef _TYPE_u_int32_t
_TYPE_u_int32_t;
#undef _TYPE_u_int32_t
#endif

#ifdef _TYPE_u_int64_t
_TYPE_u_int64_t;
#undef _TYPE_u_int64_t
#endif

#ifdef _TYPE_u_quad_t
_TYPE_u_quad_t;
#undef _TYPE_u_quad_t
#endif

#ifdef _TYPE_quad_t
_TYPE_quad_t;
#undef _TYPE_quad_t
#endif

/* old Berkeley definitions */

typedef unsigned char	uchar_t;
typedef unsigned short	ushort_t;
typedef unsigned int	uint_t;
typedef unsigned long	ulong_t;

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
typedef	struct	_quad { long val[2]; } quad;
#endif  /* _POSIX_xxx_SOURCE */
typedef	long	daddr_t;
typedef	char *	caddr_t;
typedef	char *	addr_t;
typedef	long	swblk_t;

/* Type for arbitrary user-supplied argument to a user-supplied routine. */
#ifdef _WRS_CONFIG_LP64
typedef long _Vx_usr_arg_t;
#else
typedef int _Vx_usr_arg_t;
#endif /* _WRS_CONFIG_LP64 */

typedef unsigned int _Vx_ticks_t;
typedef unsigned long long _Vx_ticks64_t;

#ifdef _WRS_CONFIG_LP64
typedef long _Vx_exit_code_t;
#else
typedef int  _Vx_exit_code_t;
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCvxTypesh */
