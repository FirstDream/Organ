#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(GRAPHICSRENDER_LIB)
#  define GRAPHICSRENDER_EXPORT Q_DECL_EXPORT
# else
#  define GRAPHICSRENDER_EXPORT Q_DECL_IMPORT
# endif
#else
# define GRAPHICSRENDER_EXPORT
#endif
