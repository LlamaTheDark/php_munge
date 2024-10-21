#define PHP_MUNGE_EXTNAME "php_munge"
#define PHP_MUNGE_VERSION "0.0.1"

PHP_FUNCTION(munge_php);
PHP_FUNCTION(unmunge_php);

ZEND_BEGIN_ARG_INFO_EX(arginfo_munge_php, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, payload, IS_STRING, 0) // First argument is a string
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(arginfo_unmunge_php, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, munge_token, IS_STRING, 0) // First argument is a string
ZEND_END_ARG_INFO()
