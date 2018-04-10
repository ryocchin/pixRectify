#include <pixqt_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#ifdef _WIN32
#else // _WIN32
#include <time.h>
#endif // _WIN32

#include "pixq_StopWatch.h"

pixq_StopWatch::pixq_StopWatch(void)
{
   // empty
}

pixq_StopWatch::~pixq_StopWatch(void)
{
   // empty
}

void pixq_StopWatch::SetTime(int iPos, long lElapsed)
{
   _lTimes[iPos] = lElapsed; 
}

void pixq_StopWatch::AddTime(int iPos, long lElapsed)
{
   _lTimes[iPos] = _lTimes[iPos] + lElapsed; 
}

void pixq_StopWatch::InitTime(void)
{
   for( int i = 0 ; i < MAXTIMEDATA ; i++ ) {
      _lTimes[i] = 0; 
      _strLabels[i].clear( );
   }
}

void pixq_StopWatch::ResetTime(void)
{
#ifdef WIN32
   _lStartTime = GetTickCount( );
#else
   _lStartTime = (long)time(NULL);
#endif
}

void pixq_StopWatch::ResetAllTime(void)
{
#ifdef WIN32
   _lStartAllTime = GetTickCount( );
#else
   _lStartAllTime = time(NULL);
#endif
}

void pixq_StopWatch::AddElapsed(int iPos)
{
#ifdef WIN32
   long lCurTime = GetTickCount( );
#else
   long lCurTime = (long)time(NULL);
#endif
   long lElapsed = lCurTime - _lStartTime;
   AddTime( iPos, lElapsed );

   ResetTime( );
}

void pixq_StopWatch::SetElapsed(int iPos)
{
#ifdef WIN32
   long lCurTime = GetTickCount( );
#else
   long lCurTime = (long)time(NULL);
#endif
   long lElapsed = lCurTime - _lStartTime;
   SetTime( iPos, lElapsed );

   ResetTime( );
}

void pixq_StopWatch::SetAllElapsed(int iPos)
{
#ifdef WIN32
   long lCurTime = GetTickCount( );
#else
   long lCurTime = (long)time(NULL);
#endif
   long lElapsed = lCurTime - _lStartAllTime;
   SetTime( iPos, lElapsed );

   ResetTime( );
}

void pixq_StopWatch::SetLabel(int iPos, QString strLabel)
{
   _strLabels[iPos] = strLabel;
}

void pixq_StopWatch::PrintTime(char *szFile,
                              int nTimeData ) // [i] = MAXTIMEDATA)
{
   FILE *fp = NULL;

   fp = fopen( szFile, "w" );
   if( !fp  ) {
      fprintf( stderr, "Failed to Open Log File %s", szFile );
      goto PIX_EXIT;
   }

   PrintTime( fp, nTimeData );

PIX_EXIT:
   if( fp ) { 
      fclose( fp ); 
      fp = NULL; 
   }
   return;
}

void pixq_StopWatch::PrintTime(FILE *fp,
                              int nTimeData ) // [i] = MAXTIMEDATA
{
   QString strLabel;
   QByteArray buf;
   
   if( 0 > nTimeData || nTimeData >= MAXTIMEDATA ) {
      nTimeData = MAXTIMEDATA;
   }

   fprintf( fp, "\n" );
   fprintf( fp, "+++ Time Log Summary +++\n" );
   for( int i = 0 ; i < nTimeData ; i++ ) {
      fprintf( fp, "time(%02d): %10ld(msec): ", i, _lTimes[i] );
      strLabel = _strLabels[i];
      if( !strLabel.isEmpty( ) ) {
         buf = strLabel.toLatin1( );
         fprintf( fp, "%s.", buf.data( ) );
      }
      fprintf( fp, "\n" );
   }

   return;
}


void pixq_StopWatch::PrintTime(QStringList &strList,
                              int nTimeData ) // [i] = MAXTIMEDATA
{
   QString strBuffer;
   
   if( 0 > nTimeData || nTimeData >= MAXTIMEDATA ) {
      nTimeData = MAXTIMEDATA;
   }

   strList.clear(  );
   for( int i = 0 ; i < nTimeData ; i++ ) {
      strBuffer.sprintf( "Time(%02d): %10ld(msec): ", i, _lTimes[i] );
      strBuffer = strBuffer + _strLabels[i];
      strList.push_back( strBuffer );
   }

   return;
}

void pixq_StopWatch::PrintTime(int iPos,
                              QString *strLabel ) // [o] label
{
   char szLabel[RECORD_SIZE];
   QByteArray buf;

   if( 0 > iPos || iPos >= MAXTIMEDATA ) {
      sprintf( szLabel, "Wrong Time Tag(%d)", iPos );
      *strLabel = szLabel;
      goto PIX_EXIT;
   }
   
   buf = _strLabels[iPos].toLatin1( );
   sprintf( szLabel, "%s(%d): %.2f(sec).", buf.data( ),
      iPos, 
      (double)_lTimes[iPos] / 1000 );

   *strLabel = szLabel;

PIX_EXIT:
   return;
}

void pixq_StopWatch::PrintSpeed(FILE *fp,
                               int iTimePos,
                               int nFrames,
                               char *szComment ) // = NULL
{
   float fTime = (float)lGetTime( iTimePos ) / 1000;
   if( 0.0 < fTime && 0 < nFrames ) {
      
      float fFps = (float)nFrames / fTime;
      float fSpeed = fTime / (float)nFrames * 1000.0f;
      if( szComment ) {
         fprintf( fp, "*** %s\n", szComment );
      }

      fprintf( fp, "*** %dframes/%.2fsec = %.1fFPS(%.1fms/f)\n", nFrames, fTime, fFps, fSpeed );
   }

   return;
}
