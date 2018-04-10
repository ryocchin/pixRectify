#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include "pixq_EnvItem.h"

//
// **** bool Value ****
//
// notes:
// bool values are stored as int
//
#ifdef _OLD
static bool GetRegData( QString strOrg,
                    QString strApp, 
                    QString strKey, 
                    bool *bValue, 
                    bool bDefault/*=0*/ )
{
	bool bRetCode = false;
   QSettings settings( strOrg, strApp );

	*bValue = (bool)settings.value( strKey, bDefault ).toBool( );

	// --- Done ---
	bRetCode = true;
//PIX_EXIT:
	return bRetCode;
}

static bool SetRegData( QString strOrg,
                           QString strApp, 
                           QString strKey, 
                           bool bValue )
{
	bool bRetCode = false;
   QSettings settings( strOrg, strApp );
   
   settings.setValue( strKey, bValue );

	// --- Done ---
	bRetCode = true;
//PIX_EXIT:
	return bRetCode;
}
#endif // _OLD

//
// **** int Value ****
//
static bool GetRegData( QString strOrg,
                    QString strApp, 
                    QString strKey, 
                    int *iValue, 
                    int iDefault )
{
	bool bRetCode = false;
   QSettings settings( strOrg, strApp );

	*iValue = settings.value( strKey, iDefault ).toInt( );

	// --- Done ---
	bRetCode = true;
//PIX_EXIT:
	return bRetCode;
}

static bool SetRegData( QString strOrg,
                    QString strApp, 
                    QString strKey, 
                    int iValue )
{
	bool bRetCode = false;
   QSettings settings( strOrg, strApp );
   
   settings.setValue( strKey, iValue );

	// --- Done ---
	bRetCode = true;
//PIX_EXIT:
	return bRetCode;
}

//
// **** Double Value ****
//
static bool GetRegData( QString strOrg, 
                    QString strApp, 
                    QString strKey, 
                    double *dValue,
                    double dDefault )
{
	bool bRetCode = false;
   QSettings settings( strOrg, strApp );

	*dValue = settings.value( strKey, dDefault ).toDouble( );

	// --- Done ---
	bRetCode = true;
//PIX_EXIT:
	return bRetCode;
}

bool SetRegData( QString strOrg, 
                    QString strApp, 
                    QString strKey, 
                    double dValue )
{
	bool bRetCode = false;
   QSettings settings( strOrg, strApp );
   
   settings.setValue( strKey, dValue );

	// --- Done ---
	bRetCode = true;
//PIX_EXIT:
	return bRetCode;
}

//
// **** String Value ****
//
static bool GetRegData( QString strOrg,
                    QString strApp, 
                    QString strKey, 
                    QString *strValue,
                    QString strDefault )
{
	bool bRetCode = false;
   QSettings settings( strOrg, strApp );
   
	*strValue = settings.value( strKey, strDefault ).toString( );

	// --- Done ---
	bRetCode = true;
//PIX_EXIT:
	return bRetCode;
}

static bool SetRegData( QString strOrg,
                    QString strApp, 
                    QString strKey, 
                    QString strValue )
{
	bool bRetCode = false;
   QSettings settings( strOrg, strApp );
   
   settings.setValue( strKey, strValue );

	// --- Done ---
	bRetCode = true;
//PIX_EXIT:
	return bRetCode;
}

//
// **** RGB Color Value ****
//
static bool GetRegData( QString strOrg,
                    QString strApp, 
                    QString strKey, 
                    QColor *rgb, 
                    QColor *def_rgb ) 
{
	bool bRetCode = false;
   QSettings settings( strOrg, strApp );   
   QString strKeyRed, strKeyGrn, strKeyBlu;
   int iRed, iGrn, iBlu;
   int iDefRed = def_rgb->red( );
   int iDefGrn = def_rgb->green( );
   int iDefBlu = def_rgb->blue( );

   strKeyRed = strKey;
   strKeyRed.append( ".red" );
	iRed = settings.value( strKeyRed, iDefRed ).toInt( );


   strKeyGrn = strKey;
   strKeyGrn.append( ".grn" );
	iGrn = settings.value( strKeyGrn, iDefGrn ).toInt( );

   strKeyBlu = strKey;
   strKeyBlu.append( ".blu" );
	iBlu = settings.value( strKeyBlu, iDefBlu ).toInt( );

   //
   // note: 
   // Because QVariant is part of the QtCore library, it cannot provide conversion 
   // functions to data types defined in QtGui, such as QColor, QImage, and QPixmap. 
   // In other words, there is no toColor() function. 
   //
   
   *rgb = QColor( iRed, iGrn, iBlu ); 

	// --- Done ---
	bRetCode = true;
//PIX_EXIT:
	return bRetCode;
}

static bool SetRegData( QString strOrg,
                       QString strApp, 
                       QString strKey, 
                       QColor rgb ) 
{
	bool bRetCode = false;
   QString strKeyRed, strKeyGrn, strKeyBlu;
   QSettings settings( strOrg, strApp );   
   int iRed = rgb.red( );
   int iGrn = rgb.green( );
   int iBlu = rgb.blue( );

   strKeyRed = strKey;
   strKeyRed.append( ".red" );
	settings.setValue( strKeyRed, iRed );

   strKeyGrn = strKey;
   strKeyGrn.append( ".grn" );
	settings.setValue( strKeyGrn, iGrn );

   strKeyBlu = strKey;
   strKeyBlu.append( ".blu" );
	settings.setValue( strKeyBlu, iBlu );

	// --- Done ---
	bRetCode = true;
//PIX_EXIT:
	return bRetCode;
}

pixq_EnvItem::pixq_EnvItem(void)
{
   _strValue.clear( ); 
   _cItemType = ItemUnknown;
   _sCategory = pixq_Properties::ItemCategoryUnknown;

   _Value = NULL;

   _minValue = NULL;
   _maxValue = NULL;
   _bRange = false;

   return;
}

pixq_EnvItem::~pixq_EnvItem(void)
{
   Clear( ); 

   return;
}

void pixq_EnvItem::Clear( void )
{
   _strRegField.clear( );
   _cItemType = ItemUnknown;
   _sCategory = pixq_Properties::ItemCategoryUnknown;

   if( _Value ) {
      free( _Value );
      _Value = NULL;
   }
   
   if( _minValue ) {
      free( _minValue );
      _minValue = NULL;
   }

   if( _maxValue ) {
      free( _maxValue );
      _maxValue = NULL;
   }

   _bRange = false;

	return;
}

//***********
//*** Set ***
//***********

//
// boolean value
//
// notes:
// no value range
//
void pixq_EnvItem::Set( short sCategory, 
                       bool bValue, 
                       QString strReg )
{
   int iTmp;

   _cItemType = ItemBool;
   _sCategory = sCategory;
 
   if( _Value ) {
      free( _Value );
      _Value = NULL;
   }

   iTmp = bValue ? 1 : 0;
   _Value = malloc( sizeof( int ) );
   memcpy( (char*)_Value, (char*)&iTmp, sizeof( int ) );

   _strRegField = strReg;

   return;
}

//
// integer value
//
// notes:
// value range can be set
//
void pixq_EnvItem::Set( short sCategory, 
                       int iValue,
                       QString strReg )
{
   _cItemType = ItemInt;
   _sCategory = sCategory;

   if( _Value ) {
      free( _Value );
      _Value = NULL;
   }
   _Value = malloc( sizeof( int ) );
   memcpy( (char*)_Value, (char*)&iValue, sizeof( int ) );

   _strRegField = strReg;

   // no value range

   if( _minValue ) {
      free( _minValue );
      _minValue = NULL;
   }
   
   if( _maxValue ) {
      free( _maxValue );
      _maxValue = NULL;
   }
      
   _bRange = false;

   return;
}

void pixq_EnvItem::Set( short sCategory, 
                       int iValue, 
                      QString strReg, 
                      int iMinValue,
                      int nMaxValue  )
{
   Set( sCategory, iValue, strReg );      
   SetRange( iMinValue, nMaxValue );
   
   return;
}

void pixq_EnvItem::SetRange( int iMinValue,
                            int nMaxValue )
{      
   if( _minValue ) {
      free( _minValue );
      _minValue = NULL;
   }

   _minValue = malloc( sizeof( int ) );
   memcpy( (char*)_minValue, (char*)&iMinValue, sizeof( int ) );

   if( _maxValue ) {
      free( _maxValue );
      _maxValue = NULL;
   }

   _maxValue = malloc( sizeof( int ) );
   memcpy( (char*)_maxValue, (char*)&nMaxValue, sizeof( int ) );

   _bRange = true;
   
   return;
}

//
// double value
//
// notes:
// value range can be set
//
void pixq_EnvItem::Set( short sCategory, 
                       double dValue,
                       QString strReg )
{
   _cItemType = ItemDouble;
   _sCategory = sCategory;
   
   if( _Value ) {
      free( _Value );
      _Value = NULL;
   }
   _Value = malloc( sizeof( double ) );
   memcpy( (char*)_Value, (char*)&dValue, sizeof( double ) );
   
   _strRegField = strReg;

   // no value range

   if( _minValue ) {
      free( _minValue );
      _minValue = NULL;
   }
   
   if( _maxValue ) {
      free( _maxValue );
      _maxValue = NULL;
   }
      
   _bRange = false;

   return;
}

void pixq_EnvItem::Set( short sCategory, 
                       double dValue, 
                      QString strReg,
                      double dMinValue,
                      double dMaxValue )
{
   Set( sCategory, dValue, strReg );
   SetRange( dMinValue, dMaxValue );
   
   return;
}

void pixq_EnvItem::SetRange( double dMinValue,
                            double dMaxValue )
{   
   if( _minValue ) {
      free( _minValue );
      _minValue = NULL;
   }

   _minValue = malloc( sizeof( double ) );
   memcpy( (char*)_minValue, (char*)&dMinValue, sizeof( double ) );

   if( _maxValue ) {
      free( _maxValue );
      _maxValue = NULL;
   }

   _maxValue = malloc( sizeof( double ) );
   memcpy( (char*)_maxValue, (char*)&dMaxValue, sizeof( double ) );

   _bRange = true;
   
   return;
}

//
// string value
//
// notes:
// value range can NOT be set
//
void pixq_EnvItem::Set( short sCategory, 
                       QString strValue, 
                       QString strReg )
{
   _cItemType = ItemString;
   _sCategory = sCategory;

   _strValue = strValue;
   _strRegField = strReg;
}

//
// COLOR Value
//
// notes:
// value range can NOT be set
//
void pixq_EnvItem::Set( short sCategory, 
                       QColor colValue,
                       QString strReg ) 
{
   int iColor[3];

   _cItemType = ItemColor;
   _sCategory = sCategory;
  
   if( _Value ) {
      free( _Value );
      _Value = NULL;
   }

   _Value = malloc( 3 * sizeof( int ) );
   iColor[0] = colValue.red( );
   iColor[1] = colValue.green( );
   iColor[2] = colValue.blue( );
   memcpy( (char*)_Value, (char*)&iColor, 3 * sizeof( int ) );

   _strRegField = strReg;

   return;
}
    
//
// QFont Value
//
// notes:
// value range can NOT be set
//
void pixq_EnvItem::Set( short sCategory, 
                       QFont lfValue,
                       QString strReg )
{
   _cItemType = ItemFont; 
   _sCategory = sCategory;

   _strValue = lfValue.toString( );
   _strRegField = strReg;

   return;
}

//***********
//*** Set ***
//***********

void pixq_EnvItem::Set( bool bValue ) 
{
   int iTmp;

   if( _Value ) {

      free( _Value );
      _Value = NULL;
   }

   iTmp = bValue ? 1 : 0;
   _Value = malloc( sizeof( int ) );
   memcpy( (char*)_Value, (char*)&iTmp, sizeof( int ) );

   return;
}

void pixq_EnvItem::Set( int iValue ) 
{ 
   if( _Value ) {
      free( _Value );
      _Value = NULL;
   }

   _Value = malloc( sizeof( int ) );
   memcpy( (char*)_Value, (char*)&iValue, sizeof( int ) );

#ifdef _DEBUG
   int ii;
   memcpy( (char*)&ii, (char*)_Value, sizeof( int ) );
#endif // _DEBUG

   return;
}

void pixq_EnvItem::Set( double dValue ) 
{ 
   if( _Value ) {
      free( _Value );
      _Value = NULL;
   }

   _Value = malloc( sizeof( double ) );
   memcpy( (char*)_Value, (char*)&dValue, sizeof( double ) );

#ifdef _DEBUG
   double dd;
   memcpy( (char*)&dd, (char*)_Value, sizeof( double ) );
#endif // _DEBUG

   return;
}

void pixq_EnvItem::Set( QString strValue ) 
{
   _strValue = strValue; 
}

void pixq_EnvItem::Set( QColor colValue ) 
{ 
   int iColor[3]; 
   
   if( _Value ) {
      free( _Value );
      _Value = NULL;
   }

   _Value = malloc( 3 * sizeof( int ) );
   iColor[0] = colValue.red( );
   iColor[1] = colValue.green( );
   iColor[2] = colValue.blue( );
   memcpy( (char*)_Value, (char*)&iColor, 3 * sizeof( int ) );

   return;
}

void pixq_EnvItem::Set( QFont lfValue ) 
{ 
   _strValue = lfValue.toString( ); 

   return;
}

//**************
//*** GetReg ***
//**************

void pixq_EnvItem::GetReg( QString strOrg, QString strApp )
{
   QString strField = _strRegField;
   int iValue, iColor[3], iDefault;
   QString strFont, strValue, strDefault;
   double dDefault;
   double dValue;
   QColor rgb, rgb_default; 

   switch( _cItemType ) {
   case ItemBool:
      memcpy( (char*)&iDefault, (char*)_Value, sizeof( int ) );
      if( GetRegData( strOrg, strApp, strField, &iValue, iDefault ) ) {
         memcpy( (char*)_Value, (char*)&iValue, sizeof( int ) ); 
      }
      break;

   case ItemInt:
      memcpy( (char*)&iDefault, (char*)_Value, sizeof( int ) );
      if( GetRegData( strOrg, strApp, strField, &iValue, iDefault ) ) {
         memcpy( (char*)_Value, (char*)&iValue, sizeof( int ) );    
      }
      break;

   case ItemDouble:
      memcpy( (char*)&dDefault, (char*)_Value, sizeof( double ) );
      if( GetRegData( strOrg, strApp, strField, &dValue, dDefault ) ) {
         memcpy( (char*)_Value, (char*)&dValue, sizeof( double ) );
      }
      break;

   case ItemString:
      strDefault = _strValue;
      if( GetRegData( strOrg, strApp, strField, &strValue, strDefault ) ) {
         _strValue = strValue;
      }
      break;

   case ItemColor:

      memcpy( (char*)&iColor, (char*)_Value, 3 * sizeof( int ) );

      rgb_default.setRed( iColor[0] );
      rgb_default.setGreen( iColor[1] );
      rgb_default.setBlue( iColor[2] );
      if( GetRegData( strOrg, strApp, strField, &rgb, &rgb_default ) ) {
         iColor[0] = rgb.red( );
         iColor[1] = rgb.green( );
         iColor[2] = rgb.blue( );
         memcpy( (char*)_Value, (char*)&iColor, sizeof( int ) * 3 );
      }
      break;

   case ItemFont: 
      strDefault = _strValue;
      if( GetRegData( strOrg, strApp, strField, &strValue, strDefault ) ) {
         _strValue = strValue;
      }
      break;
   }

   return;
}

//**************
//*** SetReg ***
//**************

void pixq_EnvItem::SetReg( QString strOrg,
                          QString strApp )
{
   QString strField = _strRegField;
   int iColor[3], iValue;
   double dValue;
   QString strValue, strFont;
   QColor colValue; 

   switch( _cItemType ) {
   case ItemBool:
      memcpy( (char*)&iValue, (char*)_Value, sizeof( int ) );
      SetRegData( strOrg, strApp, strField, iValue );
      break;

   case ItemInt:
      memcpy( (char*)&iValue, (char*)_Value, sizeof( int ) );
      SetRegData( strOrg, strApp, strField, iValue );
      break;

   case ItemDouble:     
      memcpy( (char*)&dValue, (char*)_Value, sizeof( double ) );
      SetRegData( strOrg, strApp, strField, dValue );
      break;

   case ItemString:
      strValue = _strValue;
      SetRegData( strOrg, strApp, strField, strValue );
      break;

   case ItemColor:
      memcpy( (char*)&iColor, (char*)_Value, 3 * sizeof( int ) );
      colValue.setRed( iColor[0] );
      colValue.setGreen( iColor[1] );
      colValue.setBlue( iColor[2] );
      SetRegData( strOrg, strApp, strField, colValue );
      break;

   case ItemFont: 
      strFont = _strValue;
      SetRegData( strOrg, strApp, strField, strFont );
      break;
   }

   return;
}

void pixq_EnvItem::RemoveReg( QString strOrg,
                             QString strApp )
{
   QString strField = _strRegField;
   QSettings settings( strOrg, strApp );   
   settings.remove( strField );

   return;
}

//*****************
//*** Get Value ***
//*****************

bool pixq_EnvItem::getBool(void) const
{ 
   int iTmp;
   bool bValue;

   memcpy( (char*)&iTmp, (char*)_Value, sizeof( int ) );
   
   bValue = ( 1 == iTmp ) ? true : false;

   return bValue; 
}

int pixq_EnvItem::getInteger(void) const
{ 
   int iValue;

   memcpy( (char*)&iValue, (char*)_Value, sizeof( int ) );

   return iValue; 
}

double pixq_EnvItem::getDouble(void) const
{   
   double dValue;

   memcpy( (char*)&dValue, (char*)_Value, sizeof( double ) );
   return dValue; 
}

QString pixq_EnvItem::getString(void) const
{ 
   return _strValue; 
}

QColor pixq_EnvItem::getColor(void) const
{  
   int iColor[3];
   QString strValue;
   QColor colValue; 
   memcpy( (char*)&iColor, (char*)_Value, 3 * sizeof( int ) );

   colValue.setRed( iColor[0] );
   colValue.setGreen( iColor[1] );
   colValue.setBlue( iColor[2] );

   return colValue; 
}

QFont pixq_EnvItem::getFont(void) const
{ 
   QFont lf;
   lf.fromString( _strValue );
   return lf; 
}

//*****************
//*** Get Range ***
//*****************

int pixq_EnvItem::getIntMin(void) const
{ 
   int iMinValue;

   if( _bRange ) {
      memcpy( (char*)&iMinValue, (char*)_minValue, sizeof( int ) );
   } else {
      iMinValue = 0;
   }

   return iMinValue; 
}

int pixq_EnvItem::getIntMax(void) const
{ 
   int nMaxValue;

   if( _bRange ) {
      memcpy( (char*)&nMaxValue, (char*)_maxValue, sizeof( int ) );
   } else {
      nMaxValue = 0;
   }

   return nMaxValue; 
}

double pixq_EnvItem::getDoubleMin(void) const
{ 
   double dMinValue;

   if( _bRange ) { 
      memcpy( (char*)&dMinValue, (char*)_minValue, sizeof( double ) );
   } else {
      dMinValue = 0.0;
   }
   
   return dMinValue; 
}

double pixq_EnvItem::getDoubleMax(void) const
{ 
   double dMaxValue;

   if( _bRange ) { 
      memcpy( (char*)&dMaxValue, (char*)_maxValue, sizeof( double ) );
   } else {
      dMaxValue = 0.0;
   }
   
   return dMaxValue; 
}

//
// check whether integer value is within the range
//
// returns:
// true: not integer type.
// true: range is not set
// true: value within the range
//  
//
bool pixq_EnvItem::checkIntegerRange(int iValue) const
{
   bool bRetCode = false;
   int iMinValue, iMaxValue;
      
   if (ItemInt != _cItemType) {
      bRetCode = true;
      goto PIX_EXIT;
   }
      
   if (!_bRange) {
      bRetCode = true;
      goto PIX_EXIT;
   }
   
   memcpy((char*)&iMinValue, (char*)_minValue, sizeof(int));
   memcpy((char*)&iMaxValue, (char*)_maxValue, sizeof(int));

   if (iValue < iMinValue) {
      goto PIX_EXIT;
   }

   if (iValue > iMaxValue) {
      goto PIX_EXIT;
   }

   //
   //
   //
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
// copy constructor
//
pixq_EnvItem &pixq_EnvItem::operator=( const pixq_EnvItem &that )
{
   int iValue, iColor[3];
   double dValue;
   QColor colValue; 

   _strRegField = that._strRegField;
   _cItemType = that._cItemType;
   _sCategory = that._sCategory;

   switch( _cItemType ) {
   case ItemBool:
      memcpy( (char*)&iValue, (char*)that._Value, sizeof( int ) );
      if( _Value ) {
         free( _Value );
         _Value = NULL;
      }
      _Value = malloc( sizeof( int ) );
      memcpy( (char*)_Value, (char*)&iValue, sizeof( int ) );
      break;

   case ItemInt:
      memcpy( (char*)&iValue, (char*)that._Value, sizeof( int ) );
      if( _Value ) {
         free( _Value );
         _Value = NULL;
      }
      _Value = malloc( sizeof( int ) );
      memcpy( (char*)_Value, (char*)&iValue, sizeof( int ) );
      //
      _bRange = that._bRange;
      //
      if( _maxValue ) {
         free( _maxValue );
         _maxValue = NULL;
      }
      if( _minValue ) {
         free( _minValue );
         _minValue = NULL;
      }
      //
      if( _bRange ) {
         memcpy( (char*)&iValue, (char*)that._minValue, sizeof( int ) );
         _minValue = malloc( sizeof( int ) );
         memcpy( (char*)_minValue, (char*)&iValue, sizeof( int ) );
         //
         memcpy( (char*)&iValue, (char*)that._maxValue, sizeof( int ) );
         _maxValue = malloc( sizeof( int ) );
         memcpy( (char*)_maxValue, (char*)&iValue, sizeof( int ) );
      }
      break;

   case ItemDouble:
      //m_dValue = that.m_dValue;     
      memcpy( (char*)&dValue, (char*)that._Value, sizeof( double ) );
      if( _Value ) {
         free( _Value );
         _Value = NULL;
      }
      _Value = malloc( sizeof( double ) );
      memcpy( (char*)_Value, (char*)&dValue, sizeof( double ) );
      //
      _bRange = that._bRange;
      //
      if( _minValue ) {
         free( _minValue );
         _minValue = NULL;
      }
      if( _maxValue ) {
         free( _maxValue );
         _maxValue = NULL;
      }
      //
      if( _bRange ) {
         memcpy( (char*)&dValue, (char*)that._minValue, sizeof( double ) );
         _minValue = malloc( sizeof( double ) );
         memcpy( (char*)_minValue, (char*)&dValue, sizeof( double ) );
         //
         memcpy( (char*)&dValue, (char*)that._maxValue, sizeof( double ) );
         _maxValue = malloc( sizeof( double ) );
         memcpy( (char*)_maxValue, (char*)&dValue, sizeof( double ) );
      }
      break;

   case ItemString:
      _strValue = that._strValue;
      break;

   case ItemColor:
      //m_colValue = that.m_colValue;         
      memcpy( (char*)&iColor, (char*)that._Value, 3 * sizeof( int ) );
      if( _Value ) {
         free( _Value );
         _Value = NULL;
      }
      _Value = malloc( 3 * sizeof( int ) );
      memcpy( (char*)_Value, (char*)&iColor, 3 * sizeof( int ) );
      break;

   case ItemFont: 
      _strValue = that._strValue;
      break;
   }

	return *this;
}

//
// copy value
//
// notes:
// unlike copy constructor, copy value only, but not value range 
//
pixq_EnvItem &pixq_EnvItem::CopyValue( const pixq_EnvItem &that )
{
   int iColor[3], iValue;
   double dValue;
   QColor colValue; 

   _strRegField = that._strRegField;
   _cItemType = that._cItemType;
   _sCategory = that._sCategory;

   switch( _cItemType ) {
   case ItemBool:
      memcpy( (char*)&iValue, (char*)that._Value, sizeof( int ) );
      if( _Value ) {
         free( _Value );
         _Value = NULL;
      }
      _Value = malloc( sizeof( int ) );
      memcpy( (char*)_Value, (char*)&iValue, sizeof( int ) );
      break;

   case ItemInt:
      //m_iValue = that.m_iValue;
      memcpy( (char*)&iValue, (char*)that._Value, sizeof( int ) );
      if( _Value ) {
         free( _Value );
         _Value = NULL;
      }
      _Value = malloc( sizeof( int ) );
      memcpy( (char*)_Value, (char*)&iValue, sizeof( int ) );
      break;

   case ItemDouble:
      //m_dValue = that.m_dValue;     
      memcpy( (char*)&dValue, (char*)that._Value, sizeof( double ) );
      if( _Value ) {
         free( _Value );
         _Value = NULL;
      }
      _Value = malloc( sizeof( double ) );
      memcpy( (char*)_Value, (char*)&dValue, sizeof( double ) );
      break;

   case ItemString:
      _strValue = that._strValue;
      break;

   case ItemColor:
      //m_colValue = that.m_colValue;         
      memcpy( (char*)&iColor, (char*)that._Value, sizeof( int ) * 3 );
      if( _Value ) {
         free( _Value );
         _Value = NULL;
      }
      _Value = malloc( sizeof( int ) * 3 );
      memcpy( (char*)_Value, (char*)&iColor, sizeof( int ) * 3 );
      break;

   case ItemFont: 
      _strValue = that._strValue;
      break;
   }

	return *this;
}

//
// check if two env item are same type and same kind
//
// notes:
// this does not check value
//
bool pixq_EnvItem::operator==(const pixq_EnvItem &that)
{
   bool bRetCode = false;

   // item type

   if( _cItemType != that._cItemType ) {
      goto PIX_EXIT;
   }

   if( 0 != _strRegField.compare( that._strRegField ) ) {
      goto PIX_EXIT;
   }

   if( _sCategory != that._sCategory ) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

pixq_EnvItem &pixq_EnvItem::operator=( const QColor &that ) 
{   
   if( _Value ) {
      free( _Value );
      _Value = NULL;
   }
   _Value = malloc( 3 * sizeof( int ) );

	memcpy( (char*)_Value, (char*)&that, 3 * sizeof( int ) );
   
   return *this;
}

pixq_EnvItem &pixq_EnvItem::operator=( const QFont &that )
{   
   _strValue = that.toString( );
   
   return *this;
}

//
// Check if two items are of same kind
//
// note:
// only checks item name and type
// values are not chekd
//
bool pixq_EnvItem::CompareItem( const pixq_EnvItem &Item ) const
{
   bool bRetCode = false;

   if( _strRegField != Item._strRegField ) {
      goto PIX_EXIT;
   }

   if( _cItemType != Item._cItemType ) {
      goto PIX_EXIT;
   }

   if( _sCategory != Item._sCategory ) {
      goto PIX_EXIT;
   }

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}
