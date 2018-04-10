#pragma once

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

//
// define this to use xml file
//
#define _USE_BAGSTER_XML

#include <pixqtlib_global.h>
#include <pixqtlib_def.h>

class PIXQTLIB_EXPORT PixQtLib
{
public:
    PixQtLib();
    ~PixQtLib();
    
};

//
// classes
//

#include <pixq_Version.h>
#include <pixq_version_update.h>

#include <pixq_Matrix.h>

#include <pixq_EnvItem.h>
#include <pixq_ImagePix.h>
#include <pixq_Properties.h>

#include <pixq_HelpBrowser.h>
#include <pixq_HelpViewer.h>

#include <pixq_Int2D.h>
#include <pixq_Dbl2D.h>
#include <pixq_Dbl3D.h>

#include <pixq_PntMatrix.h>
#include <pixq_CooMatrix.h>

#include <pixq_StopWatch.h>

#include <pixq_page_options.h>

// common api functions

#include <pixqtlib_ext.h>

