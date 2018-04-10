#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "pixq_Dbl2D.h"

pixq_Dbl2D::pixq_Dbl2D(void)
{
	// デフォルトのコンストラクター
   _iID = 0;
   _dX = NODATA;
   _dY = NODATA;
	return;
}

pixq_Dbl2D::pixq_Dbl2D(double xx, double	yy)
{
	// デフォルトのコンストラクター
	Set( xx, yy );
	return;
}

pixq_Dbl2D::pixq_Dbl2D(int		idx,
					   double	xx,
					   double	yy )
{
	// デフォルトのコンストラクター
	Set( idx, xx, yy );
	return;
}

pixq_Dbl2D::pixq_Dbl2D(pixq_Dbl2D *coo)
{
   Set(coo->_iID, coo->_dX, coo->_dY);
	return;
}

pixq_Dbl2D::pixq_Dbl2D(pixq_Dbl3D *coo)
{
   Set(coo->_iID, coo->_dX, coo->_dY);
	return;
}

void pixq_Dbl2D::Clear(void)
{
	Set( 0, 0.0, 0.0 );
	return;
}

void pixq_Dbl2D::Set(double xx, double yy)
{
	Set( 0, xx, yy );
	return;
}

void pixq_Dbl2D::Set(int idx, double xx, double yy)
{
   _iID = idx;
   _dX = xx;
   _dY = yy;
	return;
}

void pixq_Dbl2D::Set(pixq_Dbl2D *that)
{
   Set(that->_iID, that->_dX, that->_dY);
	return;
}


void pixq_Dbl2D::Center(pixq_Dbl2D *p0, pixq_Dbl2D *p1)
{
   _iID = (p0->_iID + p1->_iID) / 2;
   _dX = (p0->_dX + p1->_dX) / 2.0;
   _dY = (p0->_dY + p1->_dY) / 2.0;
	return;
}


void pixq_Dbl2D::Center(pixq_Dbl3D *p0, pixq_Dbl3D *p1)
{
   _iID = (p0->_iID + p1->_iID) / 2;
   _dX = (p0->_dX + p1->_dX) / 2.0;
   _dY = (p0->_dY + p1->_dY) / 2.0;
	return;
}

void pixq_Dbl2D::Center(const pixq_Dbl2D p0, const pixq_Dbl2D p1)
{
   _iID = (p0._iID + p1._iID) / 2;
   _dX = (p0._dX + p1._dX) / 2.0;
   _dY = (p0._dY + p1._dY) / 2.0;
	return;
}


void pixq_Dbl2D::Center(const pixq_Dbl3D p0, const pixq_Dbl3D p1)
{
   _iID = (p0._iID + p1._iID) / 2;
   _dX = (p0._dX + p1._dX) / 2.0;
   _dY = (p0._dY + p1._dY) / 2.0;
	return;
}


void pixq_Dbl2D::Min(const pixq_Dbl2D p0, const pixq_Dbl2D p1)
{
   _iID = p0._iID;
   _dX = min(p0._dX, p1._dX);
   _dY = min(p0._dY, p1._dY);
	return;
}


void pixq_Dbl2D::Max(const pixq_Dbl2D p0, const pixq_Dbl2D p1)
{
   _iID = p0._iID;
   _dX = max(p0._dX, p1._dX);
   _dY = max(p0._dY, p1._dY);
	return;
}

void pixq_Dbl2D::shift(double xx, double yy)
{
   _dX = _dX + xx;
   _dY = _dY + yy;
	return;
}

void pixq_Dbl2D::shift(pixq_Dbl2D	that,
						   double	xx,
						   double	yy )
{
   _dX = that._dX + xx;
   _dY = that._dY + yy;
	return;
}

double pixq_Dbl2D::distance(pixq_Dbl2D *pnt)
{
   double xd = pnt->_dX - _dX;
   double yd = pnt->_dY - _dY;
	double dd = sqrt( xd * xd + yd * yd );
	return dd;
}

double pixq_Dbl2D::distance(pixq_Dbl3D *pnt)
{
   double xd = pnt->_dX - _dX;
   double yd = pnt->_dY - _dY;
	double dd = sqrt( xd * xd + yd * yd );
	return dd;
}

double pixq_Dbl2D::getAngleAtan_PC(pixq_Dbl2D *pnt)
{
   if (_dX == pnt->_dX) {
      double ang = (pnt->_dY == _dY) ? 0.0 : (pnt->_dY < _dY) ? PIE15 : PIE05;
      ang = GoodRadian_PC(ang);
		return ang;
	}

   double ang1 = atan((pnt->_dY - _dY) / (pnt->_dX - _dX));
   double ang = (_dY < pnt->_dY) ?
      (_dX < pnt->_dX) ? ang1 : ang1 + PIE :
      (_dX < pnt->_dX) ? ang1 + PIE2 : ang1 + PIE;
   ang = GoodRadian_PC(ang);
	return ang;
}

double pixq_Dbl2D::get3Angle_PC(pixq_Dbl2D  *prev,
   pixq_Dbl2D	*next)
{
   double ang1 = prev->getAngleAtan_PC(this);
   double ang2 = getAngleAtan_PC(next);
	double ang = get_anglex_diff( ang1, ang2 );
   ang = GoodRadian_PC(ang);
	return ang;
}

pixq_Dbl2D pixq_Dbl2D::affin(double **affin)
{
   pixq_Dbl2D answer;
   answer._iID = _iID;
   answer._dX = _dX * affin[0][0] + _dY * affin[0][1] + affin[0][2];
   answer._dY = _dX * affin[1][0] + _dY * affin[1][1] + affin[1][2];
	return answer;
}

pixq_Dbl2D &pixq_Dbl2D::operator=(const pixq_Dbl2D &that)
{
   _iID = that._iID;
   _dX = that._dX;
   _dY = that._dY;
	return *this;
}

bool pixq_Dbl2D::operator=(pixq_Dbl3D that)
{
   _iID = that._iID;
   _dX = that._dX;
   _dY = that._dY;

	return true;
}

bool pixq_Dbl2D::operator=(pixq_Int2D that)
{
   _iID = that.getID();
   _dX = (int)that.getX();
   _dY = (int)that.getY();

	return true;
}

void pixq_Dbl2D::Set(pixq_Dbl3D *val)
{ 
   _iID = val->_iID;
   _dX = val->_dX;
   _dY = val->_dY;

	return;
}

void pixq_Dbl2D::Set(pixq_Int2D *val)
{ 
   _iID = val->getID();
   _dX = (double)val->getX();
   _dY = (double)val->getY();

	return;
}


bool pixq_Dbl2D::operator==(pixq_Dbl2D that)
{
   double dX = fabs(_dX - that._dX);
	if( dX > ACCURACY ) return false;
   double dY = fabs(_dY - that._dY);
	if( dY > ACCURACY ) return false;
	return true;
}

bool pixq_Dbl2D::operator!=(pixq_Dbl2D that)
{
   double dX = fabs(_dX - that._dX);
	if( dX > ACCURACY ) return true;
   double dY = fabs(_dY - that._dY);
	if( dY > ACCURACY ) return true;
	return false;
}

pixq_Dbl2D pixq_Dbl2D::operator+(pixq_Dbl2D that)
{
   double xx = _dX + that._dX;
   double yy = _dY + that._dY;
   pixq_Dbl2D answer(that._iID, xx, yy);
	return answer;
}

pixq_Dbl2D pixq_Dbl2D::operator-(pixq_Dbl2D that)
{
   double xx = _dX - that._dX;
   double yy = _dY - that._dY;
   pixq_Dbl2D answer(that._iID, xx, yy);
	return answer;
}

pixq_Dbl2D pixq_Dbl2D::operator/(double det)
{
   pixq_Dbl2D answer(0, 0, 0);
	if( 0.0 == det ) return answer;
   answer._iID = _iID;
   answer._dX = _dX / det;
   answer._dY = _dY / det;
	return answer;
}


pixq_Dbl2D pixq_Dbl2D::operator*(double det)
{
   pixq_Dbl2D answer(_iID, _dX * det, _dY * det);
	return answer;
}
