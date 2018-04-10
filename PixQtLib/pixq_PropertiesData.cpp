#include <pixqt_common.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

#include <limits.h>
#include <signal.h>
#include <stddef.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "pixq_EnvItem.h"
#include "pixq_Properties.h"

//
// returns opencv fundamental matrix method name
//
string pixq_Properties::fundamentalMethodName(void)
{
   string strMethod;

   int iMethod = _RectifyCvFundamentalMethod.getInteger();
   switch (iMethod) {
   case FundamentalMethod7Point:
      strMethod = "7-Point Algorithm. Requires 7 Points.";
      break;

   case FundamentalMethod8Point:
      // grayscale 
      strMethod = "8-Point Algorithm. Requires 8 or more Points.";
      break;

   case FundamentalMethodRansac:
      strMethod = "RANSAC Algorithm. Requires 8 or more Points.";
      break;

   case FundamentalMethodLmeds:
      strMethod = "LMedS Algorithm. Requires 8 or more Points.";
      break;

   default:
      strMethod = "Unknown";
      break;
   }

   return strMethod;
}
