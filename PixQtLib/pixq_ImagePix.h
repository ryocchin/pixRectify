#pragma once

namespace _pix_plot_qt_framework {

#include <pixqtlib_global.h>

//
// whole image data 
// mostly read through imagemagick
//

class PIXQTLIB_EXPORT pixq_ImagePix
{
public:

public:
   pixq_ImagePix(void);
   ~pixq_ImagePix(void);

private:
   // Filename
   QString _strFile;

   // image data loaded from file
   
   // image data normaized to 16-bit integer for display
   pixq_Matrix<unsigned short> _usRed;
   pixq_Matrix<unsigned short> _usGrn; 
   pixq_Matrix<unsigned short> _usBlu;

   // image parameters read thru imagemagick
   int _iDensity;

public:
   void Clear( void );
};

} // namespace 

