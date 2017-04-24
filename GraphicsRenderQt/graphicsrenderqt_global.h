#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(GRAPHICSRENDERQT_LIB)
#  define GRAPHICSRENDERQT_EXPORT Q_DECL_EXPORT
# else
#  define GRAPHICSRENDERQT_EXPORT Q_DECL_IMPORT
# endif
#else
# define GRAPHICSRENDERQT_EXPORT
#endif
