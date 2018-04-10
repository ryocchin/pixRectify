#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;



//
// ふたつの3次元ベクトルの差ベクトル（第1の点から第2の点へ向かうベ
// クトル）
//
// 引数：
// pixq_Dbl3D	*val0	i	第1のベクトル
// pixq_Dbl3D	*val1	i	第2のベクトル
//
// 返値：
// pixq_Dbl3D
// 差ベクトル
//
// 外部変数：
// なし
//
// 注意事項：
// なし
//

pixq_Dbl3D PixVectorDiff3(pixq_Dbl3D *val0,
   pixq_Dbl3D *val1)
{
   pixq_Dbl3D diff;
   diff._dX = val1->_dX - val0->_dX;
   diff._dY = val1->_dY - val0->_dY;
   diff._dZ = val1->_dZ - val0->_dZ;
   return diff;
}


// 3次元空間内の2ベクトルAとBの外積opを求める
//
// 引数：
// pixq_Dbl3D	*val0	i	第1の3次元ベクトル
// pixq_Dbl3D	*val1	i	第2の3次元ベクトル
//
// 返値：
// pixq_Dbl3D
// 外積
//
// 外部変数：
// なし
//
// 注意事項：
// 2つの3次元ベクトル[x0, y0, z0]と[x1, y1, z1]に対して外積は[y0*z1-z0*y1,
// z0x1-x0*z1, x0*y1-y0*x1]で求められる。
//

pixq_Dbl3D PixOuterProduct3(
   pixq_Dbl3D *val0,
   pixq_Dbl3D *val1)
{
   pixq_Dbl3D op;
   op._dX = val0->_dY * val1->_dZ - val0->_dZ * val1->_dY;
   op._dY = val0->_dZ * val1->_dX - val0->_dX * val1->_dZ;
   op._dZ = val0->_dX * val1->_dY - val0->_dY * val1->_dX;
   return op;
}

//
// 機能：
// 3次元空間内で三点が与えられた三角形の法線ベクトルを求めて返す
//
// 引数：
// pixq_Dbl3D	*vtx0	i	三角形の第1の点
// pixq_Dbl3D	*vtx1	i	三角形の第2の点
// pixq_Dbl3D	*vtx2	i	三角形の第3の点
//
// 返値：
// pixq_Dbl3D
// 三角形の法線ベクトル
//
// 外部変数：
// なし
//
// 注意事項：
// 三角形は時計回り
//

pixq_Dbl3D PixTriNormalVector3(
   pixq_Dbl3D	*vtx0,
   pixq_Dbl3D	*vtx1,
   pixq_Dbl3D	*vtx2,
   double	   *en)	// [o] normal vector in vector form
{
   pixq_Dbl3D normal = PixTriNormalVector3(vtx0, vtx1, vtx2);
   en[0] = normal._dX;
   en[1] = normal._dY;
   en[2] = normal._dZ;
   return normal;
}

pixq_Dbl3D PixTriNormalVector3(
   pixq_Dbl3D	*vtx0,
   pixq_Dbl3D	*vtx1,
   pixq_Dbl3D	*vtx2)
{
   pixq_Dbl3D diff10 = PixVectorDiff3(vtx1, vtx0);
   pixq_Dbl3D diff21 = PixVectorDiff3(vtx2, vtx1);
   pixq_Dbl3D normal = PixOuterProduct3(&diff10, &diff21);

   double vsize = normal._dX * normal._dX + normal._dY * normal._dY + normal._dZ * normal._dZ;

   if (vsize > 0) {
      vsize = sqrt(vsize);
      normal._dX = normal._dX / vsize;
      normal._dY = normal._dY / vsize;
      normal._dZ = normal._dZ / vsize;
   }
   else {
      normal._dX = NODATA;
      normal._dY = NODATA;
      normal._dZ = NODATA;
   }

   return normal;
}

//
// 直線上の2点の位置とそれらの地点における属性値が与えられている
// とき、その直線上で与えられた別の位置における属性値を線形補間に
// よって求めて返す
//
// 引数：
// double	coo0	i	線上の点
// double	coo1	i	線上の点
// double	val0	i	coo0における属性値
// double	val1	i	coo1における属性値
// double	coo		i	線上の与えられた位置
//
// 返値：
// double
// 求められた値
// 求められなかった場合はNODATAが返る。これは2地点の位置が同じだった
// 場合に起こる。
//
// 外部変数：
// なし.
//
// 注意事項：
// 2地点の位置が同じではいけない
//
double value_segment(double		loc0,
   double		loc1,
   double		val0,
   double		val1,
   double		loc)
{
   double ldiff = loc1 - loc0;
   if (ldiff == 0.0) return NODATA;
   double vdiff = val1 - val0;
   double val = vdiff / ldiff * (loc - loc0) + val0;
   return val;
}

double value_segment(int		loc0,
   int		loc1,
   double	val0,
   double	val1,
   int		loc)
{
   int ldiff = loc1 - loc0;
   if (ldiff == 0) return NODATA;

   int ldiff2 = loc - loc0;
   double val = (val1 - val0) / (double)ldiff * (double)ldiff2 + val0;
   return val;
}

double value_segment(int		loc0,
   int		loc1,
   int		val0,
   int		val1,
   int		loc)
{
   double dloc0 = (double)loc0;
   double dloc1 = (double)loc1;
   double dval0 = (double)val0;
   double dval1 = (double)val1;
   double dloc = (double)loc;
   return value_segment(dloc0, dloc1, dval0, dval1, dloc);
}

//
// 平面上の2点の位置とその地点における属性値が与えられているとき、2
// 点を結ぶ直線上の与えられた位置における属性値を線形補間によって求め
// て返す
//
// 引数：
// pixq_Dbl2D	*coo0	i	平面上の点
// pixq_Dbl2D	*coo1	i	平面上の点
// double		val0	i	coo0における属性値
// double		val1	i	coo1における属性値
// pixq_Dbl2D	*coo	i	与えられた位置
//
// 返値：
// double
// 求められた値
// 求められなかった場合はNODATAが返る。これは2地点の位置が同じだった
// 場合に起こる。
//
// 外部変数：
// なし.
//
// 注意事項：
// 値を求める点は2点を結ぶ直線上になければならない。このチェックは
// ルーチンないでは行わない。これが満たされない場合は返値は求める答
// にはならないことがある2地点の位置が同じではいけない
//
double value_segment(pixq_Dbl2D	*	coo0,
   pixq_Dbl2D	*	coo1,
   double		val0,
   double		val1,
   pixq_Dbl2D	*	coo)
{
   double	val;
   double ldiff = coo1->getX() - coo0->getX();
   double vdiff = val1 - val0;

   if (ldiff == 0.0) {
      ldiff = coo1->getY() - coo0->getY();
      if (ldiff == 0.0) {
         return NODATA;
      }

      val = vdiff / ldiff * (coo->getY() - coo0->getY()) + val0;
      return val;
   }
   else {
      val = vdiff / ldiff * (coo->getX() - coo0->getX()) + val0;
      return val;
   }
}

//
// get_anglex_diff
//
// 呼出系列：
// double get_anglex_diff( angle1, angle2 )
//
// 機能：
// ＜幾何演算＞2つの角度（傾き）の間の差を求める。2つの角度はX軸から
// 反時計周りに計られたものである。
// get the diference between two angles measured in the
// counter-clockwise direction ( as in getAngleAtan_PC ).
//
// 引数：
// angle1	double	i	第1の角度
// angle2	double	i	第2の角度.
//
// 返値：
// double
// 角度
//
// 外部関数：
// なし
//
// 注意事項：
// angle is obtained as follows:
//                                * C
//                               /
//                              /^
//                           B / | angle2
//              --------------*---------------------------
//                             ･
//                              ･        angle1
//                               ･ ----+
//                              A ･    |
//              -------------------*-----------------------
// as shown, it is calculated in the counter-clockwise direction in
// RADIAN. this routine can be used to get the angle defined by three
// points A, B and C as shown. this typically used when "angle1" is
// known instead of  "get3Angle_PC".
// 角度は0～2π（360度）の間に正規化される
//
//
//
//
double get_anglex_diff(double angle1, double angle2)
{
   double ang;

   /* ang = angle2 - angle1 + PIE + PIE; */
   ang = angle2 - angle1 + PIE;
   ang = GoodRadian_PC(ang);
   return ang;
}

double GoodRadian_PC(double angle0)
{
   double angle1;
   angle1 = angle0;

#ifdef DBG2
   fprintf(stdout, "InPUT Angle dGoodRadian_PC %f\n", angle0);
#endif DBG2

   while (angle1 < 0) {
      angle1 += PIE2;
   }

   while (angle1 >= PIE2) {
      angle1 -= PIE2;
   }

#ifdef DBG2
   fprintf(stdout, "OUTPUT Angle GoodRadian_PC %f\n", angle1);
#endif DBG2

   return angle1;
}

void ClearStrings_PC(char *str, int len)
{
   memset((char*)str, 0x00, len);
}

int delimitStr_PC(
   char	*buff,         // [i] バッファー
   char	*str[], 	      // [i] デリミッター
   char	dli,	         // [o] 分解後のアドレス格納エリア
   int   iBuffSize /* =DELIMITOUT_SIZE */)
{
   int i = 0;
   char *p = buff;
   while (*p == ' ' || *p == '\t') p++;
   if (*p == 0) {
      str[i] = 0;
      return i;
   }

   str[i] = p;
   i++;
   while (*p != 0) {
      if (*p == dli) {
         *p = 0;
         p++;
         while (*p == ' ' || *p == '\t') p++;
         if (i < iBuffSize) str[i] = p;
         i++;
      }
      else {
         p++;
      }
   }

   if (i < iBuffSize) {
      str[i] = 0;
   }
   
   return i;
}


void ChrTranslate_PC(
   char	*str,
   char	chr0,
   char	chr1)
{
   char	*cp;
   cp = str;
   for (;;) {
      cp = strchr(cp, chr0);
      if (cp == NULL) return;
      *cp = chr1;
   }

   return;
}


void ChrTranslate_PC( 
      QString *str, 
		QChar	chr )
{
	QChar	cp = QChar::Null;
	str->replace( chr, cp, Qt::CaseInsensitive );
}

void ChrTranslate_PC( 
      QString	*str, 
		QChar	chr0, 
		QChar	chr1 )
{
	str->replace( chr0, chr1, Qt::CaseInsensitive );
}

bool IsIntNumber_PC( const QString strValue )
{
   bool bRetCode = false;
	QChar c;
   int i, nLen;

	// 文字列の長さが0より大

   nLen = strValue.size( );
	if( 0 >= nLen ) {
		goto PIX_EXIT;
	}

	// 第1文字目が数値または-
	c = strValue.at( 0 );
   if( !c.isDigit( ) && c != QChar('-') ) {
		goto PIX_EXIT;
	}

	// 2文字目以降がすべて数字
	for ( i = 1; i < nLen; i++ ) {
		c = strValue.at( i );
      if( !c.isDigit( ) ) {
			goto PIX_EXIT;
		}
	}

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

bool IsPositiveIntNumber_PC( const QString strValue ) 
{
   bool bRetCode = false;
	QChar c;
   int i, nLen;

	// 文字列の長さが0より大
   
   nLen = strValue.size( );
	if( 0 >= nLen ) {
		goto PIX_EXIT;
	}

	// 2文字目以降がすべて数字

	for ( i = 0 ; i < nLen ; i++ ) {
		c = strValue.at( i );
      if( !c.isDigit( ) ) {
			goto PIX_EXIT;
		}
	}

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// decide the largest value from the araay of value and return the sequence number of the largest
//
int getMaxValue_PC(int nSize, // [i] size of the array
                    double *dArray, // [i] data array
                    double *dMaxVal  ) // [o] largest value
{
   int nMaxPos = -1;
   int i;
   double dValue, dMax;
   
   if( 0 >= nSize ) goto PIX_EXIT;

   i = 0;
   dMax = dArray[i];
   nMaxPos = i;
   
   for( i = 1 ; i < nSize ; i++ ) {
      dValue = dArray[i];
      if( dValue > dMax ) {
         dMax = dArray[i];
         nMaxPos = i;
      }
   }

   *dMaxVal = dMax;
   
   // --- Done ---
PIX_EXIT:
	return nMaxPos;
}

//
// Determines whether an expression is a valid real number type.
//
bool isFloatNumber_PC(char *szBuff)
{
   bool bRetCode = false;
	bool bDecimalPointFlag;
   int i, iLen;

	iLen = (int)strlen( szBuff );
	if( iLen <= 0 ) return false;

   if ( !isdigit( szBuff[0] ) && szBuff[0] != '-' ) {
      goto PIX_EXIT;
   }

	bDecimalPointFlag = false;
	for ( i = 1; i < iLen; i++ ) {
		if ( isdigit( szBuff[i] ) ) continue;
		if( szBuff[i] != '.' ) return false;

		if( bDecimalPointFlag == true ) {
			return false;
		} else {
			bDecimalPointFlag = true;
		}
	}

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}


//
// check if the number if power of two
// 
// notes:
// 
bool IsPowerOfTwo_PC( int iValue, // [i] input value
                       int *iPower ) // [i] if input value is power of two, it is 2**iPower
{
   int i = 0;   
   while( (1<<i) < iValue ) {
      i++;
   }

   if( iValue == (1<<i) ) {
      *iPower = i;
      return true;
   } else {
      *iPower = 0;
      return false;
   }
}

//
// get file name for the file
//
// example
// on Window,
// for "C:\\Hub\\sh1901\\right\\sh1901_v01.0012.cin",
// returns "sh1901_v01.0012.cin"
// 
// on Linux,
// for "/home/user/Hubsh1901/right/sh1901_v01.0012.cin",
// returns "sh1901_v01.0012.cin"
//
void getFileName_PC(const QString szFile, // [i] input file name
                     QString *szName ) // [i] file name portion
{
   QFileInfo file;
  
   file.setFile( szFile );

   *szName = file.fileName( );

	return;
}


//
// convert QString to C character
//
void stringToSzBuffer_PC(
   const QString strBuff, // [i] Qt string
   char *szBuff,	// [o]
   int nSize) // [i] max size of the string buffer 
{
   //QByteArray buf = strBuff.toLatin1();
   QByteArray buf = strBuff.toUtf8();
   int nBuffer;

   int nLength = strBuff.size();
   
   if (nLength > nSize) {
      nBuffer = nSize;
      strncpy(szBuff, buf.data(), nSize);
   }
   else {
      strcpy(szBuff, buf.data());
   }

   return;
}

//
// convert the selected QString in the straing array to C character
//
void stringToSzBuffer_PC(
   const QStringList	aryBuff, // [i] Qt string arrays
   int iLoc, // [i] which string in the array to convert
   char *szBuff,
   int nSize)
{
   QString strBuff;
   int nLength = aryBuff.size();

   if (0 > iLoc || nLength <= iLoc) {
      return;
   }

   strBuff = aryBuff.at(iLoc);

   stringToSzBuffer_PC(strBuff, szBuff, nSize);

   return;
}

