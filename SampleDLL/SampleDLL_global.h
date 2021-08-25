#ifndef SAMPLEDLL_GLOBAL_H
#define SAMPLEDLL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SAMPLEDLL_LIBRARY)
#  define SAMPLEDLL_EXPORT Q_DECL_EXPORT
#else
#  define SAMPLEDLL_EXPORT Q_DECL_IMPORT
#endif

#endif // SAMPLEDLL_GLOBAL_H
