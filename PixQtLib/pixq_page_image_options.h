#pragma once

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

class pixq_page_image_options : public pixq_page_options
{
private:
   pixq_Properties *_pTmpEnv;

public:
   pixq_page_image_options(void);
   virtual ~pixq_page_image_options(void);

public:
   void Store( pixq_Properties *pEnv );
   pixq_Properties *getEnv(void) { return _pTmpEnv; }
  
};