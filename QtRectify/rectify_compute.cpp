#include <stdlib.h>
#include <string.h>
#include <assert.h>

//! gradient normalization factors

const int iNormShar  = 32;
const int iNormSobel =  8; 

// Sobel gradient

static int coreGradientISobel( int *pImg, 
                        int *pGradIx,
                        int *pGradIy,
                        int Width, 
                        int Height )
{
   int dx,dy, i, j, pos;
   int nw, ne, sw, se, w, n, s, e;
	
	memset( pGradIx, 0, Width*Height*sizeof(int) );
	memset( pGradIy, 0, Width*Height*sizeof(int) );
	
   for( i=1; i+1<Height; i++ ) {
		int posRow = i*Width;
		for( j=1; j+1<Width; j++ ) {
			pos = posRow + j;
			
         nw = pImg[pos-Width-1];
         n = pImg[pos-Width];
         ne = pImg[pos-Width+1];
			w = pImg[pos-1];
         e = pImg[pos+1]; 
			sw = pImg[pos+Width-1];
         s = pImg[pos+Width]; 
         se = pImg[pos+Width+1];
			
         dx = (ne-nw) + 2*(e-w) + (se-sw);
			dy = (sw-nw) + 2*(s-n) + (se-ne);
			
         pGradIx[pos] = dx;
			pGradIy[pos] = dy;
		}
	}
	
   return 0;
}

//! The following codes are modified from Birchfield KLT implementaion

#define SWAP3(list, i, j)			\
{	register int *pi, *pj, tmp;     \
    pi=list+3*(i); pj=list+3*(j);   \
                                    \
    tmp=*pi;	\
    *pi++=*pj;  \
    *pj++=tmp;  \
                \
    tmp=*pi;    \
    *pi++=*pj;  \
    *pj++=tmp;  \
                \
    tmp=*pi;    \
    *pi=*pj;    \
    *pj=tmp;    \
}

static void swap3(int *list, int i, int j)
{
   register int tmp;       
   register int *pi = list + 3 * (i);
   register int *pj = list + 3 * (j);
      
   tmp = *pi;	
   *pi++ = *pj;
   *pj++ = tmp;
   
   tmp = *pi;  
   *pi++ = *pj;
   *pj++ = tmp;
   
   tmp = *pi;  
   *pi = *pj;  
   *pj = tmp;  

   return;
}

static void _quicksort( int *pointlist, int n )
{
	unsigned int i, j, ln, rn;

	while (n > 1) {

		SWAP3(pointlist, 0, n/2);

		for( i = 0, j = n; ; ) {
         do {
            --j;
         } while (pointlist[3 * j + 2] < pointlist[2]);
			
         do {
            ++i;
         }  while (i < j && pointlist[3 * i + 2] > pointlist[2]);
			
         if (i >= j) {
            break;
         }

         SWAP3(pointlist, i, j);
		}

		SWAP3(pointlist, j, 0);
		
      ln = j;
		rn = n - ++j;
		
      if (ln < rn) {
			_quicksort(pointlist, ln);
			pointlist += 3*j;
			n = rn;
		}
		else {
			_quicksort(pointlist + 3*j, rn);
			n = ln;
		}
	}

   return;
}
#undef SWAP3


static void fillStereoMap(
      int x,
      int y,
      unsigned char *featuremap,
      int mindist,
      int ncols, 
      int nrows )
{
	int ix, iy;

   for (iy = y - 0; iy <= y + 0; iy++) {
      for (ix = x - mindist; ix <= x + mindist; ix++) {
         if (ix >= 0 && ix < ncols && iy >= 0 && iy < nrows) {
            featuremap[iy*ncols + ix] = 1;
         }
      }
   }

   return;
}

static void enforceHorizontalDistance( 
      int *pointlist,
      int npoints, 
      unsigned char *pFeatureMap,
      int *iMap,
      int ncols,
      int nrows, 
      int mindist, 
      int min_value )
{
	int indx;          //!< Index into features 
	int x, y, val;     //!< Location and trackability of pixel under consideration 
	int iPos;
   int *ptr;
	unsigned char *pMap = NULL;
	
   if( min_value<1 ) min_value = 1;

	memset( pFeatureMap, 0, ncols*nrows );
	
   pMap = (unsigned char*) calloc( ncols*nrows, sizeof(unsigned char) );
	
   //! For each feature point, in descending order of importance, do ... 
	
   ptr = pointlist;
	indx = 0;
	while( 1 ) {
		if( ptr >= pointlist + 3*npoints ) {
			break;
		}
		x = *ptr++;
		y = *ptr++;
		val = *ptr++;

		//! Ensure that feature is in-bounds 
		
      assert( x>=0 );
		assert( x<ncols );
		assert( y>=0 );
		assert( y<nrows );
	   
      //! If no neighbor has been selected, and if the minimum eigenvalue is large enough, then add feature to the current list 

      iPos = y*ncols+x;
      
      if( !pMap[iPos] && val>=min_value ) {

			pFeatureMap[iPos] = 1;
			indx +=1;
			
         //! Fill in surrounding region of feature map, but make sure that pixels are in-bounds 
			fillStereoMap( x, y, pMap, mindist, ncols, nrows );
		}

      iMap[iPos] = val;
   }

   free(pMap);
   return;
}

static void sortPointList( int *pointlist, int npoints )
{
	_quicksort( pointlist, npoints );
}

static int selectGoodStereoFeature( int *pDescriptor, 
                            unsigned char *pFeatureMap, 
                            int *iMap, 
                            int width,
                            int height, 
                            int minDist,
                            int minValue,
                            float percent )
{
	int *pointlist = NULL;
	int npoints = 0;
   int nWanted, i, j;

	pointlist = (int*) calloc( width*height*3, sizeof(int) );
	
   for( i=0; i<height; i++ ) {
		for( j=0; j<width; j++ ) {
			int pos = i*width + j;
			pointlist[3*npoints+0] = j;
			pointlist[3*npoints+1] = i;
			pointlist[3*npoints+2] = pDescriptor[pos];
			npoints += 1;
		}
	}

   sortPointList(pointlist, npoints);
	
   if (percent < 0 || percent>100) {
      percent = 100;
   }
   
   nWanted = (int)(npoints*percent / 100.0);

	enforceHorizontalDistance( pointlist, nWanted, pFeatureMap, iMap,
      width, height, minDist, minValue );
	
   free(pointlist);

	return 0;
}

int selectMatchFeature(
	int *pLuminance,			
	unsigned char *pFeatureMap, //! stereo features
	int *iMap, 
	int Width,     // [i] image width
   int Height,    // [i] image height
	int hRadius,   // [i] match window radius, height
   int vRadius,	// [i] match window radius, width
	int minDist,   // [i] minimum distance between features
	int minValue,               //!< 
	float percent ) // [i] percentage of features 
{
	int *pGradIx = NULL;
	int *pGradIy = NULL;
	int hSize, vSize;
	int i, j;

   if (hRadius < 0) {
      hSize = 3;
   }
   else {
      hSize = hRadius;
   }
   
   if (vRadius < 0) {
      vSize = 3;
   }
   else {
      vSize = vRadius;
   }

	pGradIx = (int*) calloc( Width*Height, sizeof(int) );
	pGradIy = (int*) calloc( Width*Height, sizeof(int) );
	
	coreGradientISobel( pLuminance, pGradIx, pGradIy, Width, Height );
	
	int *pDescriptor = pGradIy;
	
	//! very slow now

	for( i=0; i<Height; i++ ) {
		for( j=0; j<Width; j++ ) {
			int pos = i*Width + j;
			int _nCount = 0;
			double _Gxx = 0;
			for( int m=-vSize; m<=vSize; m++ ) {
				for( int n = -hSize; n<=hSize; n++ ) {
					if( i+m<0 || i+m>=Height || j+n<0 || j+n>=Width ) {
						continue;
					}
					else {
						int posw = (i+m)*Width + (j+n);
						int _gx = pGradIx[posw];
						_Gxx += _gx*_gx;	//!< becareful of integer overflow 
						_nCount += 1;
					}
				}
			}

			if( _nCount > 0 ) {
				_Gxx = _Gxx / _nCount;
			}
			
         pDescriptor[pos] = (int)(_Gxx+0.5);  
		}
	}
	
	selectGoodStereoFeature( pDescriptor, pFeatureMap, iMap, 
      Width, Height, minDist, minValue, percent );
   
	free(pGradIx);
	free(pGradIy);
	
   return 0;	
}