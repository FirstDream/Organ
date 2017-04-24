#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DICOMIO_LIB)
#  define DICOMIO_EXPORT Q_DECL_EXPORT
# else
#  define DICOMIO_EXPORT Q_DECL_IMPORT
# endif
#else
# define DICOMIO_EXPORT
#endif
