#include <php.h>
#include "php_helloworld.h"

zend_function_entry helloworld_php_functions[] = {
	PHP_FE(helloworld_php, NULL)
	{NULL, NULL, NULL}
};

zend_module_entry helloworld_php_module_entry = {
	STANDARD_MODULE_HEADER,
	PHP_HELLOWORLD_EXTNAME,
	helloworld_php_functions,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	PHP_HELLOWORLD_VERSION,
	STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(helloworld_php)

PHP_FUNCTION(helloworld_php) {
	php_printf("Hello World! (from da extension)\n");
}
