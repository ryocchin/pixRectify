#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

//
// create gray color from RGB colors
//
float grayFromRgb_PI(float fRed,
                       float fGrn,
                       float fBlu )
{
   float fValue = 0.299f * fRed + 0.587f * fGrn + 0.114f * fBlu;
	return fValue;
}


unsigned short grayFromRgb_PI(unsigned short usRed,
   unsigned short usGrn,
   unsigned short usBlu)
{
   unsigned short usGray;
   double dValue = 0.299 * (double)usRed + 0.587 * (double)usGrn + 0.114 * (double)usBlu;

   dValue = min(dValue, 65535.0);

   usGray = static_cast<unsigned short>(dValue);

   return usGray;
}
