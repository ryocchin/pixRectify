#pragma once

#ifdef WIN32
#include <iostream>
#endif

namespace _pix_plot_qt_framework {

// +++ data monitoring +++
#define MAXTIMEDATA 20

// time(0): preprocessing
// time(1): load image
// time(2): noise calc
// time(3): contrast calc
// time(4): gray image
// time(6): blur filter
// time(7): final filter
// time(5): save image
// time(8): display time
// time(9): total time

class PIXQTLIB_EXPORT pixq_StopWatch
{
public:
   pixq_StopWatch(void);
   ~pixq_StopWatch(void);

private:
   long _lTimes[MAXTIMEDATA];
   QString _strLabels[MAXTIMEDATA];
   long _lStartTime;
   long _lStartAllTime;

public:
   void SetLabel( int iPos, QString strLabel );
   long lGetTime( int iPos ) { return _lTimes[iPos]; }
   QString getStringLabel(int iPos) { return _strLabels[iPos]; }
   void ResetTime( void );
   void ResetAllTime( void );
   void SetTime( int iPos, long lElapsed );
   void SetElapsed( int iPos );
   void SetAllElapsed( int iPos );
   void AddTime( int iPos, long lElapsed );
   void AddElapsed( int iPos );
   void InitTime( void );
   
   void PrintSpeed( FILE *fp, int iTimePos, int nFrames, char *szComment = NULL );

   void PrintTime( FILE *fp, int nTimeData = MAXTIMEDATA );
   void PrintTime( char *szFile, int nTimeData = MAXTIMEDATA );
   void PrintTime( QStringList &strList, int nTimeData = MAXTIMEDATA );
   void PrintTime( int iPos, QString *strLabel );

   // *** special timer for sharping ***
public:
   void PrintSharPingTime( FILE *fp );
};

} // namespace _pix_plot_qt_framework 

