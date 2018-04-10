#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "pixq_page_image_options.h"

pixq_page_image_options::pixq_page_image_options(void)
{
   return;
}

pixq_page_image_options::~pixq_page_image_options(void)
{
   return;
}

void pixq_page_image_options::Store(pixq_Properties *pEnv)
{
   _pTmpEnv = pEnv; 

   setData( );

   return;
}
