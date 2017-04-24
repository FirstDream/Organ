#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QORGAN_LIB)
#  define QORGAN_EXPORT Q_DECL_EXPORT
# else
#  define QORGAN_EXPORT Q_DECL_IMPORT
# endif
#else
# define QORGAN_EXPORT
#endif
