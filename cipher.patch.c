--- ./opensshlib/cipher.c
+++ ./opensshlib/cipher.c
@@ -363,7 +363,6 @@
 			goto bad;
 		}
 		ret = EVP_Cipher(&cc->evp, discard, junk, cipher->discard_len);
-		explicit_bzero(discard, cipher->discard_len);
 		free(junk);
 		free(discard);
 		if (ret != 1) {
@@ -469,11 +468,9 @@
 	if (cc == NULL || cc->cipher == NULL)
 		return 0;
 	if ((cc->cipher->flags & CFLAG_CHACHAPOLY) != 0)
-		explicit_bzero(&cc->cp_ctx, sizeof(cc->cp_ctx));
-	else if ((cc->cipher->flags & CFLAG_AESCTR) != 0)
-		explicit_bzero(&cc->ac_ctx, sizeof(cc->ac_ctx));
+	if ((cc->cipher->flags & CFLAG_AESCTR) != 0)
 #ifdef WITH_OPENSSL
-	else if (EVP_CIPHER_CTX_cleanup(&cc->evp) == 0)
+        if (EVP_CIPHER_CTX_cleanup(&cc->evp) == 0)
 		return SSH_ERR_LIBCRYPTO_ERROR;
 #endif
 	return 0;
@@ -497,7 +494,6 @@
 
 	r = cipher_init(cc, cipher, digest, 16, NULL, 0, do_encrypt);
  out:
-	explicit_bzero(digest, sizeof(digest));
 	return r;
 }
 
