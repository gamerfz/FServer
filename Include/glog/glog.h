#pragma once

#undef GOOGLE_GLOG_DLL_DECL
#define GOOGLE_GLOG_DLL_DECL
#undef GLOG_NO_ABBREVIATED_SEVERITIES
#define GLOG_NO_ABBREVIATED_SEVERITIES

/* user-defined */
#define LogBrace(s) "[" << s << "]"
#define LogParam(s,p) " " << s << LogBrace(p)
#define LogValue(s, p) " " << s << ":" << p

#include "glog/logging.h"