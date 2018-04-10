#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

//
// compress file and create compressed file
//
// notes:
// iCompressionLevel must be -1 or value between 0 and 9
// 
// The compressionLevel parameter specifies how much compression should be used.
// Valid values are between 0 and 9,
// with 9 corresponding to the greatest compression (i.e. smaller compressed data)
// at the cost of using a slower algorithm. 
// Smaller values (8, 7, ..., 1) provide successively less compression at slightly faster speeds.
// The value 0 corresponds to no compression at all. 
// The default value is -1, which specifies zlib's default compression.
//
bool FileCompress_PC( const QString strInFile, // [i] input file name
                     const QString strCmpFile, // [i] compressed file name
                     int iCompressionLevel ) // [i]
{
   bool bRetCode = false;
   int iLevel;
   long lSize, lIn, lOut;
   QFile in, out;
   QByteArray in_array, out_array;
#ifdef _DEBUG
   QFile chk;
   QByteArray check_array;
#endif // _DEBUG

   //

   if( -1 == iCompressionLevel ) {
      iLevel = iCompressionLevel;
   } else if( 0 > iCompressionLevel ) {
      iLevel = 0;
   } else if( 9 < iCompressionLevel ) {
      iLevel = 9;
   } else {
      iLevel = iCompressionLevel;
   }

   //

   in.setFileName( strInFile );
   if( !in.open( QIODevice::ReadOnly ) ) {
      // failed to open input file 
      goto PIX_EXIT; 
   }

   in_array = in.readAll( );
   in.close( );
   lIn = (long)in_array.size( );
   
   out_array = qCompress( in_array, iLevel );
   lOut = (long)out_array.size( );
   
   out.setFileName( strCmpFile );
   if( !out.open( QIODevice::WriteOnly ) ) {
      // failed to open output(compressed) file 
      goto PIX_EXIT; 
   }  

   lSize = out.write( out_array );
   out.close( );
   
   if( lSize != lOut ) {
      // all data could not be written
      goto PIX_EXIT;
   }  

#ifdef _DEBUG
   check_array = qUncompress( out_array );
   chk.setFileName( "c:\\agent\\test.xml" );
   chk.open( QIODevice::WriteOnly );   
   chk.write( check_array );
   chk.close( );
#endif // _DEBUG

   // --- DONE ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}

//
//
//
bool FileUnCompress_PC( const QString strCmpFile, // [i] compressed file name
                        const QString strOutFile ) // [i] uncompressed file name
{
   bool bRetCode = false;
   QFile in, out;
   QByteArray in_array, out_array;
   long lSize, lIn, lOut;
   
   in.setFileName( strCmpFile );
   if( !in.open( QIODevice::ReadOnly ) ) {
      // failed to open compressed file
      goto PIX_EXIT;
   }

   in_array = in.readAll( );
   in.close( );
   lIn = (long)in_array.size( );

   out_array = qUncompress( in_array );
   lOut = (long)out_array.size( );
   
   out.setFileName( strOutFile );
   if( !out.open( QIODevice::WriteOnly ) ) {
      // failed to open output file
      goto PIX_EXIT;
   }  

   lSize = out.write( out_array );
   out.close( );

   if( lSize != lOut ) {
      // all data could not be written
      goto PIX_EXIT;
   }  

   // --- DONE ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}   

