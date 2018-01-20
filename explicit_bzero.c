/*
 * Public domain.
 * Written by Ted Unangst
 */

#include "includes.h"

/*
 */

#ifndef HAVE_EXPLICIT_BZERO

#ifdef HAVE_MEMSET_S

void
{
	(void)memset_s(p, n, 0, n);
}

#else /* HAVE_MEMSET_S */

/*
 * Indirect bzero through a volatile pointer to hopefully avoid
 * dead-store optimisation eliminating the call.
 */

#endif /* HAVE_MEMSET_S */

#endif /* HAVE_EXPLICIT_BZERO */
