#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "pix_ImageOp.h"

pixq_ImageOp::pixq_ImageOp(void)
{
   _pDepthEnv = (pixq_Properties*)NULL;

   _strErrorMsg.clear( );

   return;
}

pixq_ImageOp::~pixq_ImageOp( void )
{   
   return;
}

//
// copy constructor
//
pixq_ImageOp &pixq_ImageOp::operator=( const pixq_ImageOp &that )
{      
   _pDepthEnv    = that._pDepthEnv;

   // --- Done ---
	return *this;
}

//
// store pointer to the input images
//
void pixq_ImageOp::storeIn(int kPos, pixq_ImageMatrix *p16)
{   
   _pIn16[kPos] = p16;

   return;
}

void pixq_ImageOp::storeIn(pixq_ImageMatrix p16[])
{   
   storeIn(0, &p16[0]);
   storeIn(1, &p16[1]);
   storeIn(2, &p16[2]);

   return;
}

//
// store pointer to the second input images
//
void pixq_ImageOp::storeIn2(int kPos, pixq_ImageMatrix *p16)
{   
   _pIn2_16[kPos] = p16;

   return;
}

void pixq_ImageOp::storeIn2(pixq_ImageMatrix p16[])
{   
   storeIn2(0, &p16[0]);
   storeIn2(1, &p16[1]);
   storeIn2(2, &p16[2]);

   return;
}

//
// store pointer to the output images
//
void pixq_ImageOp::storeOut(int kPos, pixq_ImageMatrix *p16)
{   
   _pOut16[kPos] = p16;

   return;
}

void pixq_ImageOp::storeOut(pixq_ImageMatrix p16[])
{   
   storeOut(0, &p16[0]);
   storeOut(1, &p16[1]);
   storeOut(2, &p16[2]);

   return;
}
