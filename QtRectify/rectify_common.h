// 
// *** MainWindow ***
//
#pragma once

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//
// use image magick
//
#include <Magick++.h>
using namespace Magick;

#ifdef _DEBUG
#pragma comment (lib, "CORE_DB_Magick++_.lib") 
#else // _DEBUG
#pragma comment (lib, "CORE_RL_Magick++_.lib") 
#endif // _DEBUG

//
// external functions
//

int selectMatchFeature(
   int *pLuminance,
   unsigned char *pFeatureMap,
   int *iMap,
   int Width,
   int Height,
   int hWinSize,
   int vWinSize,     // match window size
   int minDist,      // minimum distance
   int minValue,		// minimum gradient value (I find it not quite useful.)  
   float percent);  // percentage of #Feature vs. #Pixles (I find this is a easy for global control.)  

pixq_Version Version( void );



static bool getResampledValue(int iLevel,
   int nInValue,
   int &nResampledValue)
{
   bool bRetCode = false;
   int nResample, nValue;

   switch (iLevel) {
   case 0:
      nValue = nInValue;
      break;

   case 1:
      nResample = 2;
      nValue = (int)ceil((double)nInValue / (double)nResample);
      break;

   case 2:
      nResample = 4;
      nValue = (int)ceil((double)nInValue / (double)nResample);
      break;

   case 3:
      nResample = 8;
      nValue = (int)ceil((double)nInValue / (double)nResample);
      break;

   default:
      // wrong resampling rate
      goto PIX_EXIT;
      break;
   }

   if (0 >= nValue) {
      goto PIX_EXIT;
   }

   nResampledValue = nValue;

   // --- Done ---
   bRetCode = true;
PIX_EXIT:
   return bRetCode;
}