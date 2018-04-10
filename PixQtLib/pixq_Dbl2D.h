#pragma once

namespace _pix_plot_qt_framework {

#include <pixqtlib_global.h>

class pixq_Dbl3D;

class PIXQTLIB_EXPORT pixq_Dbl2D
{
private:
   int		_iID;
   double	_dX;
   double	_dY;

public:
   pixq_Dbl2D(void); 
   pixq_Dbl2D(double, double);
   pixq_Dbl2D(int, double, double);
   pixq_Dbl2D(pixq_Dbl2D*);
   pixq_Dbl2D(pixq_Dbl3D*);

	void	Clear( void );

   int getID(void ) const { return _iID; };
   double getX(void ) const { return _dX; };
   double getY(void) const { return  _dY; };

	void	Set( double, double );
	void	Set( int, double, double );
   void	Set(pixq_Dbl2D*);
   void	Set(pixq_Dbl3D*);
   void	Set(pixq_Int2D*);

   void	setID(int iId) { _iID = iId; };
   void	setX(double dVal) { _dX = dVal; };
   void	setY(double dVal) { _dY = dVal; };

   void	Center(pixq_Dbl2D *p0, pixq_Dbl2D *p1);
   void	Center(pixq_Dbl3D *p0, pixq_Dbl3D *p1);
   void	Center(const pixq_Dbl2D p0, const pixq_Dbl2D p1);
   void	Center(const pixq_Dbl3D p0, const pixq_Dbl3D p1);
   
   void	Min(pixq_Dbl2D, pixq_Dbl2D);
   void	Max(pixq_Dbl2D, pixq_Dbl2D);
   bool  bNull(void) { return (1 == _iID) ? false : true; }

	void	shift( double, double );
   void	shift(pixq_Dbl2D, double, double);
   double	distance(pixq_Dbl2D*);
   double	distance(pixq_Dbl3D*);
   double	getAngleAtan_PC(pixq_Dbl2D*);
   double	get3Angle_PC(pixq_Dbl2D*, pixq_Dbl2D*);
   pixq_Dbl2D	affin(double **affin);

   //int encho(pixq_Dbl2D *pa, pixq_Dbl2D *pb, double dist);
 
   bool	operator==(pixq_Dbl2D);
   bool	operator!=(pixq_Dbl2D);
   pixq_Dbl2D	operator+(pixq_Dbl2D);
   pixq_Dbl2D	operator-(pixq_Dbl2D);
   pixq_Dbl2D	operator/(double);
   pixq_Dbl2D	operator*(double);

   pixq_Dbl2D &operator=(const pixq_Dbl2D &that);
   bool operator=(pixq_Dbl3D);
   bool operator=(pixq_Int2D);

};

} // _pix_plot_qt_framework 
