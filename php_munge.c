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
	char *payload = NULL;
	int payload_len;

	int return_code; // return code
	char err_buffer[256];

	if(zend_parse_parameters(ZEND_NUM_ARGS(), "s", &payload, &payload_len) == FAILURE){
		snprintf(err_buffer, sizeof(err_buffer), "Failed to parse parameters. return_code was %d", return_code);
		zend_throw_error(NULL, err_buffer, 0);
		RETURN_FALSE;
	}

	return_code = munge_encode(&munge_cred, NULL, (void**)payload, sizeof(char)*payload_len);
	if (return_code != EMUNGE_SUCCESS) {
		snprintf(err_buffer, sizeof(err_buffer), "Failed to munge. return_code was %d", return_code);
		zend_throw_error(NULL, err_buffer, 0);
		RETURN_FALSE;
	}
	
	RETURN_STRING(munge_cred);

	free(munge_cred);
}

PHP_FUNCTION(unmunge_php) {
	char *munge_cred; // Replace with your actual munged token
	int cred_len;

	void *payload;
	int payload_len;

	uid_t uid;
	gid_t gid;
	time_t encode_time;
	time_t decode_time;

	int return_code;
	char err_buffer[256];

	munge_ctx_t ctx = munge_ctx_create();
	if(!ctx){
		snprintf(err_buffer, sizeof(err_buffer), "Failed to create MUNGE context. return_code was %d", return_code);
		zend_throw_error(NULL, err_buffer, 0);
		RETURN_FALSE;
	}

	if(zend_parse_parameters(ZEND_NUM_ARGS(), "s", &munge_cred, &cred_len) == FAILURE){
		snprintf(err_buffer, sizeof(err_buffer), "Failed to parse parameters. return_code was %d", return_code);
		zend_throw_error(NULL, err_buffer, 0);
		RETURN_FALSE;
	}

 	// Unmunge the credential
 	return_code = munge_decode(munge_cred, ctx, &payload, &payload_len, &uid, &gid);
	if(return_code != EMUNGE_SUCCESS){
		snprintf(err_buffer, sizeof(err_buffer), "Failed to decode MUNGE token. return_code was %d. More detail:\n%s", return_code, munge_ctx_strerror(ctx));
		zend_throw_error(NULL, err_buffer, 0);
		RETURN_FALSE;
	}
	
	return_code = munge_ctx_get(ctx, MUNGE_OPT_ENCODE_TIME, &encode_time);
	if(return_code != EMUNGE_SUCCESS){
		snprintf(err_buffer, sizeof(err_buffer), "Failed to obtain encode time. return_code was %d", return_code);
		zend_throw_error(NULL, err_buffer, 0);
		RETURN_FALSE;
	}

	return_code = munge_ctx_get(ctx, MUNGE_OPT_DECODE_TIME, &decode_time);
	if(return_code != EMUNGE_SUCCESS){
		snprintf(err_buffer, sizeof(err_buffer), "Failed to obtain decode time. return_code was %d", return_code);
		zend_throw_error(NULL, err_buffer, 0);
		RETURN_FALSE;
	}

	// get username associated with uid
	struct passwd *user_info = getpwuid(uid);
	char *username = user_info ? user_info->pw_name : "unknown";

	// `return_value` is automatically returned
	array_init(return_value);

	add_assoc_long(return_value, "encode_time", encode_time);
	add_assoc_long(return_value, "decode_time", decode_time); /* empty, TODO: maybe creating a new context will solve this? */
	add_assoc_long(return_value, "uid", uid);
	add_assoc_long(return_value, "gid", gid);
	add_assoc_string(return_value, "payload", (char*)payload);
	add_assoc_string(return_value, "username", username);

	// Free the context when done
	munge_ctx_destroy(ctx);
}
