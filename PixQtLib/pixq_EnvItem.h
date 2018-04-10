#pragma once

namespace _pix_plot_qt_framework {

#include <pixqtlib_global.h>

class PIXQTLIB_EXPORT pixq_EnvItem
{
public:
   enum {
      ItemBool = 0,
      ItemInt = 1,
      ItemDouble = 2,
      ItemString = 3, // QString
      ItemColor = 4, // QColor(long)
      ItemFont = 5, // QFontInfo
      // to initialize
      ItemUnknown = -1,
   } pixq_EnvItemType;
   
public:
   pixq_EnvItem(void);
   ~pixq_EnvItem(void);

   // copy constructor
	pixq_EnvItem &operator=( const pixq_EnvItem &that );
   pixq_EnvItem &operator=( const QColor &that );
   pixq_EnvItem &operator=( const QFont &that );

	bool operator==( const pixq_EnvItem& that );
   
	pixq_EnvItem &CopyValue( const pixq_EnvItem &that );

private:
   // Registry key
   QString _strRegField;

   // item type
   char _cItemType;

   // value for string
   QString _strValue;

   // value for bool, int, double
   void *_Value;

   // value range for int and double
   void *_minValue;
   void *_maxValue;
   bool _bRange;

   // item category
   // must be one of ItfEnvItemCategory
   
   short _sCategory;

public:
   // boolean
   void Set( short sCategory, bool bValue, QString strReg );

   // integer
   void Set( short sCategory, int iValue, QString strReg );
   void Set( short sCategory, int iValue, QString strReg, int iMinValue, int nMaxValue );
   void SetRange( int iMinValue, int nMaxValue );

   // double
   void Set( short sCategory, double dValue, QString strReg );
   void Set( short sCategory, double dValue, QString strReg, double dMinValue, double dMaxValue );
   void SetRange( double dMinValue, double dMaxValue );

   // string
   void Set( short sCategory, QString strValue, QString strReg );
   
   // color
   void Set( short sCategory, QColor colValue, QString strReg );
   
   // font
   void Set( short sCategory, QFont lfValue, QString strReg );
   
   // reset value
   void Set( bool bValue );
   void Set( int iValue );
   void Set( double dValue );
   void Set( QString strValue );
   void Set( QColor colValue );
   void Set( QFont lfValue );

   void GetReg( QString strOrg, QString strApp );
   void SetReg( QString strOrg, QString strApp );
   void RemoveReg( QString strOrg, QString strApp );

   void Clear( void );

   bool CompareItem( const pixq_EnvItem &Item ) const;

   // get values

   bool getBool( void ) const;
   int getInteger(void) const;
   double getDouble( void ) const;
   QString getString( void ) const;
   QColor getColor( void ) const;
   QFont getFont( void ) const;
   
   // get range

   bool getRange( void ) const { return _bRange; }
   int getIntMin(void) const;
   int getIntMax(void) const;
   double getDoubleMin(void) const;
   double getDoubleMax(void) const;

   bool checkIntegerRange(int iValue) const;

public:
   char GetItemType( void ) const { return _cItemType; }
   QString GetRegField( void ) const { return _strRegField; }
   
   short GetCategory( void ) const { return _sCategory; }
   void SetCategory( short sCategory ) { _sCategory = sCategory; }
};

} // namespace 

