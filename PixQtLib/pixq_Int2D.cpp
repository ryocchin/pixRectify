#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "pixq_Int2D.h"

pixq_Int2D::pixq_Int2D(void)
{

   _iID = 0;
   _iX = 0;
   _iY = 0;
	return;
}

pixq_Int2D::pixq_Int2D(int	xx,
					   int	yy )
{
	set( xx, yy );
	return;
}

pixq_Int2D::pixq_Int2D(int	idx,
					   int	xx,
					   int	yy )
{
	set( idx, xx, yy );
	return;
}

void pixq_Int2D::clear(void)
{
	set( 0, 0, 0 );
	return;
}

void pixq_Int2D::set(int	xx,
					      int	yy )
{
   set(0, xx, yy);

	return;
}

void pixq_Int2D::set(int		idx,
					      int		xx,
					      int		yy )
{
   _iID = idx;
   _iX = xx;
   _iY = yy;

	return;
}

void pixq_Int2D::set(int idx, double dX, double dY)
{
   _iID = idx;
   _iX = (int)floor(dX + 0.5);
   _iY = (int)floor(dY + 0.5);

	return;
}

pixq_Int2D pixq_Int2D::operator+(pixq_Int2D that)
{
   int xx = _iX + that._iX;
   int yy = _iY + that._iY;
   pixq_Int2D answer(that._iID, xx, yy);

	return answer;
}

pixq_Int2D pixq_Int2D::operator-(pixq_Int2D that)
{
   int xx = _iX - that._iX;
   int yy = _iY - that._iY;
   pixq_Int2D answer(that._iID, xx, yy);

	return answer;
}

pixq_Int2D pixq_Int2D::operator/(int det)
{
   pixq_Int2D answer(0, 0, 0);

	if( 0.0 == det ) return answer;
   answer._iID = _iID;
   answer._iX = _iX / det;
   answer._iY = _iY / det;

	return answer;
}


pixq_Int2D pixq_Int2D::operator*(int det)
{
   pixq_Int2D answer(_iID, _iX * det, _iY * det);

	return answer;
}


bool pixq_Int2D::operator=(pixq_Dbl2D that)
{
   _iID = that.getID();
   _iX = (int)that.getX();
   _iY = (int)that.getY();

	return true;
}

