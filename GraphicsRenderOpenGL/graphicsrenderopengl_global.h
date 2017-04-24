#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(GRAPHICSRENDEROPENGL_LIB)
#  define GRAPHICSRENDEROPENGL_EXPORT Q_DECL_EXPORT
# else
#  define GRAPHICSRENDEROPENGL_EXPORT Q_DECL_IMPORT
# endif
#else
# define GRAPHICSRENDEROPENGL_EXPORT
#endif
