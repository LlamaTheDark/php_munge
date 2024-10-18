PHP_ARG_ENABLE(php_munge, Whether to enable the MungePHP extension [ --enable-munge-php MungePHP])

if test "$PHP_MUNGE" != "no"; then
	PHP_NEW_EXTENSION(php_munge, php_munge.c, $ext_shared)
fi
