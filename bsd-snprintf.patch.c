--- ./opensshlib/bsd-snprintf.c
+++ ./opensshlib/bsd-snprintf
@@ -869,24 +869,3 @@
 }
 #endif /* !defined(HAVE_SNPRINTF) || !defined(HAVE_VSNPRINTF) */
 
-#if !defined(HAVE_VSNPRINTF)
-int
-vsnprintf (char *str, size_t count, const char *fmt, va_list args)
-{
-	return dopr(str, count, fmt, args);
-}
-#endif
-
-#if !defined(HAVE_SNPRINTF)
-int
-snprintf(char *str, size_t count, SNPRINTF_CONST char *fmt, ...)
-{
-	size_t ret;
-	va_list ap;
-
-	va_start(ap, fmt);
-	ret = vsnprintf(str, count, fmt, ap);
-	va_end(ap);
-	return ret;
-}
-#endif
