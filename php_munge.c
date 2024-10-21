// TODO: add error handling

#include <php.h>
#include <munge.h>
#include <time.h>

#include "php_munge.h"

zend_function_entry munge_php_functions[] = {
	PHP_FE(munge_php, arginfo_munge_php)
	PHP_FE(unmunge_php, arginfo_unmunge_php)
	PHP_FE_END
};

zend_module_entry munge_php_module_entry = {
	STANDARD_MODULE_HEADER,
	PHP_MUNGE_EXTNAME,
	munge_php_functions,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	PHP_MUNGE_VERSION,
	STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(munge_php)

PHP_FUNCTION(munge_php) {
	char *munge_cred = NULL;
	int ret; // return code
	char *payload = NULL;
	int payload_len;

	if(zend_parse_parameters(ZEND_NUM_ARGS(), "s", &payload, &payload_len) == FAILURE){
		RETURN_FALSE;
	}

	php_printf("Payload to pass: %s\n", payload);

	ret = munge_encode(&munge_cred, NULL, (void**)payload, sizeof(char)*payload_len);
	if (ret != EMUNGE_SUCCESS) {
		// TODO: add useful error messages
		RETURN_FALSE;
	}
	
	RETURN_STRING(munge_cred);

	free(munge_cred);
}

PHP_FUNCTION(unmunge_php) {
	char *munge_cred; // Replace with your actual munged token
	int cred_len;
	munge_ctx_t ctx/* = munge_ctx_create()*/;
	uid_t uid;
	gid_t gid;

	/*char *host = NULL, *ip = NULL,*/ 
	time_t encode_time;
	time_t decode_time;
	void *payload;
	int payload_len;
	int ret;

	if(zend_parse_parameters(ZEND_NUM_ARGS(), "s", &munge_cred, &cred_len) == FAILURE){
		RETURN_FALSE;
	}

 	// Unmunge the credential
 	ret = munge_decode(munge_cred, ctx, &payload, &payload_len, &uid, &gid);
	
	ret = munge_ctx_get(ctx, MUNGE_OPT_ENCODE_TIME, &encode_time);
	ret = munge_ctx_get(ctx, MUNGE_OPT_DECODE_TIME, &decode_time);

	// `return_value` is automatically returned
	array_init(return_value);

	add_assoc_long(return_value, "encode_time", encode_time);
	add_assoc_long(return_value, "uid", uid);
	add_assoc_long(return_value, "gid", gid);
	add_assoc_string(return_value, "payload", (char*)payload);

	// Free the context when done
	munge_ctx_destroy(ctx);
}
