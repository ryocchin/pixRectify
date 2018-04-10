#pragma once

namespace _pix_plot_qt_framework {

#include <pixqtlib_global.h>
   	
class PIXQTLIB_EXPORT pixq_Dbl3D
{
public:
   int		_iID;
   double	_dX;
   double	_dY;
   double	_dZ;

public:
   pixq_Dbl3D(void);
   pixq_Dbl3D(double, double, double);
   pixq_Dbl3D(int, double, double, double);
   pixq_Dbl3D(int, double*);
   pixq_Dbl3D(pixq_Dbl3D*);

	void	Set( double, double, double );
	void	Set( int, double, double, double  );
	void	Set( pixq_Dbl2D* );
   void	Center(const pixq_Dbl3D p0, const pixq_Dbl3D p1);

   pixq_Dbl3D &operator=(const pixq_Dbl2D &that);
   pixq_Dbl3D &operator=(const pixq_Dbl3D &that);
   bool operator==(pixq_Dbl3D that);
   
   void	Min(pixq_Dbl3D, pixq_Dbl3D);
   void	Max(pixq_Dbl3D, pixq_Dbl3D);
   bool bNull(void) { return (1 == _iID) ? false : true; }
};

} // namespace 
