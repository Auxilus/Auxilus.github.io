--- explicit_bzero.c
+++ explicit_bzero
@@ -1,5 +1,3 @@
-/* OPENBSD ORIGINAL: lib/libc/string/explicit_bzero.c */
-/*	$OpenBSD: explicit_bzero.c,v 1.1 2014/01/22 21:06:45 tedu Exp $ */
 /*
  * Public domain.
  * Written by Ted Unangst
@@ -8,7 +6,6 @@
 #include "includes.h"
 
 /*
- * explicit_bzero - don't let the compiler optimize away bzero
  */
 
 #ifndef HAVE_EXPLICIT_BZERO
@@ -16,7 +13,6 @@
 #ifdef HAVE_MEMSET_S
 
 void
-explicit_bzero(void *p, size_t n)
 {
 	(void)memset_s(p, n, 0, n);
 }
@@ -27,21 +23,6 @@
  * Indirect bzero through a volatile pointer to hopefully avoid
  * dead-store optimisation eliminating the call.
  */
-#ifndef WIN32
-static void (* volatile ssh_bzero)(void *, size_t) = bzero;
-
-void
-explicit_bzero(void *p, size_t n)
-{
-	ssh_bzero(p, n);
-}
-#else 
-void
-explicit_bzero(void *p, size_t n)
-{
-	(void)memset(p, 0, n);
-}
-#endif // WIN32
 
 #endif /* HAVE_MEMSET_S */
 
