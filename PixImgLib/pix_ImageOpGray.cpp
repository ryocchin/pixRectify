#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "pix_ImageOp.h"
#include "pix_ImageOpGray.h"

pixq_ImageOpGray::pixq_ImageOpGray(void)
{
   return;
}

pixq_ImageOpGray::~pixq_ImageOpGray(void)
{
   return;
}

bool pixq_ImageOpGray::procCpu(void)
{
   bool bRetCode = false;
   int i, j, nWidth, nHeight;
   unsigned short usGray, usRed, usGrn, usBlu;

   nWidth = _pIn16[0]->getWidth();
   nHeight = _pIn16[0]->getHeight();

   // create grayscale matrix in the matrix 2

   for (i = 0; i < nHeight; i++) {
      for (j = 0; j < nWidth; j++) {
         usRed = _pIn16[0]->Get(i, j);
         usGrn = _pIn16[1]->Get(i, j);
         usBlu = _pIn16[2]->Get(i, j);
         usGray = grayFromRgb_PI(usRed, usGrn, usBlu);
         _pOut16[0]->Set(i, j, usGray);
         _pOut16[1]->Set(i, j, usGray);
         _pOut16[2]->Set(i, j, usGray);
      }
   }

   // --- Done ---
   bRetCode = true;
//PIX_EXIT:
   return bRetCode;
}

bool pixq_ImageOpGray::procCuda(void)
{
   bool bRetCode = false;

   if (!procCpu()) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool pixq_ImageOpGray::Proc(void)
{
   bool bRetCode = false;
   bool bUseCuda = false;

   if (bUseCuda) {
      if (!procCuda()) {
         goto PIX_EXIT;
      }
   }
   else {
      if (!procCpu()) {
         goto PIX_EXIT;
      }
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}
