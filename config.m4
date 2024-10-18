PHP_ARG_ENABLE(php_munge, Whether to enable the MungePHP extension [ --enable-munge-php MungePHP])

if test "$PHP_MUNGE" != "no"; then
	PHP_NEW_EXTENSION(php_munge, php_munge.c, $ext_shared)
fi

dnl config.m4 for PHP munge extension

PHP_ARG_WITH(munge, for Munge support,
[  --with-munge=DIR  Include Munge support])

if test "$with_munge" != "no"; then
	dnl Check if the munge library exists
	AC_CHECK_LIB(munge, munge_encode, [
		AC_DEFINE([HAVE_LIBMUNGE], [1], [Define if libmunge is available])
		AC_MSG_NOTICE([libmunge found.])
		EXTRA_LDFLAGS="$EXTRA_LDFLAGS -lmunge"
	], [
		AC_MSG_ERROR([libmunge not found. Please install libmunge.])
	])
fi

PHP_ADD_LIBRARY_WITH_PATH(munge, $PHP_MUNGE, MUNGE_SHARED_LIBADD)
PHP_SUBST(MUNGE_SHARED_LIBADD)

