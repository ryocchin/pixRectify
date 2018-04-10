#pragma once

namespace _pix_plot_qt_framework {

#include <pixqtlib_global.h>

class pixq_Dbl2D;

class PIXQTLIB_EXPORT pixq_Int2D
{
private:
   int _iID;
   int _iX;
   int _iY;

public:
   pixq_Int2D(void);

   pixq_Int2D(int, int);
   pixq_Int2D(int, int, int);

public:
	void set( int, int );
	void set( int, int, int );
	void set( int, double, double );
	void clear( void );

   int getID(void) const { return _iID; }
   int getX(void) const { return _iX; }
   int getY(void) const { return _iY; }

   bool operator=(pixq_Dbl2D);
   pixq_Int2D operator+(pixq_Int2D);
   pixq_Int2D operator-(pixq_Int2D);
   pixq_Int2D operator/(int);
   pixq_Int2D operator*(int);
};

} // namespace  _pix_plot_qt_framework


