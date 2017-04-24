#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(GRAPHICS_LIB)
#  define GRAPHICS_EXPORT Q_DECL_EXPORT
# else
#  define GRAPHICS_EXPORT Q_DECL_IMPORT
# endif
#else
# define GRAPHICS_EXPORT
#endif
