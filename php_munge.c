#include <php.h>
#include "php_munge.h"

zend_function_entry munge_php_functions[] = {
	PHP_FE(munge_php, NULL)
	{NULL, NULL, NULL}
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
	php_printf("Munge! (from da extension)\n");
}
