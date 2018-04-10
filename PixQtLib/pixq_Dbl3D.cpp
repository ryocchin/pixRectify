#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework; 

#include "pixq_Dbl3D.h"

pixq_Dbl3D::pixq_Dbl3D(void)
{
   _iID = 0;
   _dX = NODATA;
   _dY = NODATA;
   _dZ = NODATA;
	return;
}

pixq_Dbl3D::pixq_Dbl3D(double	xx,
					double	yy,
					double	zz )
{
	Set( xx, yy, zz );
	return;
}

pixq_Dbl3D::pixq_Dbl3D(int		idx,
					double	xx,
					double	yy,
					double	zz )
{
	Set( idx, xx, yy, zz );

	return;
}

pixq_Dbl3D::pixq_Dbl3D(int		idx,
					   double	*value )
{
	Set( idx, value[0], value[1], value[2] );

	return;
}

pixq_Dbl3D::pixq_Dbl3D(pixq_Dbl3D *coo)
{
   Set(coo->_iID, coo->_dX, coo->_dY, coo->_dZ);
	return;
}

//void pixq_Dbl3D::Set( pixq_Dbl2D *ep2 )
//{
//	Set( ep2->_iID, ep2->_dX, ep2->_dY, 0.0 );
//	return;
//}

void pixq_Dbl3D::Set(double	xx,
					double	yy,
					double	zz )
{
	Set( 0, xx, yy, zz );
	return;
}

void pixq_Dbl3D::Set(int		idx,
					double	xx,
					double	yy,
					double	zz  )
{
   _iID = idx;
   _dX = xx;
   _dY = yy;
   _dZ = zz;

	return;
}


void pixq_Dbl3D::Center(const pixq_Dbl3D p0, const pixq_Dbl3D p1)
{
   _iID = (p0._iID + p1._iID) / 2;
   _dX = (p0._dX + p1._dX) / 2.0;
   _dY = (p0._dY + p1._dY) / 2.0;
   _dZ = (p0._dZ + p1._dZ) / 2.0;

	return;
}


void pixq_Dbl3D::Min(const pixq_Dbl3D p0, const pixq_Dbl3D p1)
{
   _iID = p0._iID;
   _dX = min(p0._dX, p1._dX);
   _dY = min(p0._dY, p1._dY);
   _dZ = min(p0._dZ, p1._dZ);

	return;
}


void pixq_Dbl3D::Max(const pixq_Dbl3D p0, const pixq_Dbl3D p1)
{
   _iID = p0._iID;
   _dX = max(p0._dX, p1._dX);
   _dY = max(p0._dY, p1._dY);
   _dZ = max(p0._dZ, p1._dZ);

	return;
}


bool pixq_Dbl3D::operator==(pixq_Dbl3D that)
{
   if (ACCURACY < fabs(_dX - that._dX)) return false;
   if (ACCURACY < fabs(_dY - that._dY)) return false;
   if (ACCURACY < fabs(_dZ - that._dZ)) return false;
	return true;
}


pixq_Dbl3D &pixq_Dbl3D::operator=(const pixq_Dbl2D &that)
{
   _iID = that.getID();
   _dX = that.getX();
   _dY = that.getY();
   _dZ = 0.0;

	return *this;
}


pixq_Dbl3D &pixq_Dbl3D::operator=(const pixq_Dbl3D &that)
{
   _iID = that._iID;
   _dX = that._dX;
   _dY = that._dY;
   _dZ = that._dZ;

	return *this;
}
