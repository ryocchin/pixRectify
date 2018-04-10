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

#include <piximglib_global.h>
#include <piximglib_def.h>

class PIXIMGLIB_EXPORT PixImgLib
{
public:
    PixImgLib();
    ~PixImgLib();

private:

public:
   static QString getImageLibLabel( const QString strClass, 
      const QString strName, 
      const QString strDefault,
      int iLanguage = QLocale::English);
   
   static QString getImageLibLabel( const QString strClass, 
      const QString strName,
      int iLanguage = QLocale::English);
};

//
// classes
//

// Image and texture

#include <pix_DualTexture.h>
#include <pix_PaneTexture.h>
#include <pix_FlipPara.h>
#include <pix_PanePara.h>
#include <pix_ScreenPara.h>
#include <pix_ImgSequence.h>
#include <pix_DepthTexture.h>
#include <pix_ImageMatrix.h>
#include <pix_FrameImageStat.h>
#include <pix_TextureBuffer.h>

#include <pix_ImageAccess.h>

#include <pix_ImageSingleSet.h>
#include <pix_ImageDualSet.h>

#include <pix_ImageInfo.h>
#include <pix_ImageOp.h>
#include <pix_ImageOpGray.h>
#include <pix_ImageOpProjective.h>

#include <pix_FringeTag.h>
#include <pix_FringesTag.h>

// common api functions

#include <piximglib_ext.h>
