#pragma once

namespace _pix_plot_qt_framework {

//
// global definition
//

#ifndef LEFT
#define LEFT 0
#endif // LEFT

#ifndef RIGHT
#define RIGHT 1
#endif // RIGHT

#ifndef UPPER
#define UPPER  2 
#endif // UPPER

#ifndef LOWER
#define LOWER  3 
#endif // LOWER

#ifndef RENDERED
#define RENDERED 2
#endif // RENDERED

#ifndef ACCURACY
#define ACCURACY ( 0.1e-6 )
#endif // ACCURACY

#ifndef STANDARD_BUFFER_SIZE
#define STANDARD_BUFFER_SIZE	( 2048 )
#endif // STANDARD_BUFFER_SIZE

#ifndef FILE_NAME_SIZE
#define FILE_NAME_SIZE	1024
#endif // FILE_NAME_SIZE

#ifndef RECORD_SIZE
#define RECORD_SIZE	2048
#endif // RECORD_SIZE

   //
   // definition
   //

#ifndef NODATA
#define NODATA -99999999.0
#endif // NODATA

#ifndef ACCURACY
#define ACCURACY ( 0.1e-6 )
#endif // ACCURACY

#ifndef PIE
#define PIE 3.1415926535898
#endif // PIE

#ifndef PIE05
#define PIE05 1.5707963267949
#endif // PIE05

#ifndef PIE2
#define PIE2 6.2831853071796
#endif // PIE2

#ifndef PIE15
#define PIE15 4.7123889803847
#endif // PIE15

#ifndef RAD
#define RAD 180.0
#endif // RAD

#ifndef PIE_RAD
#define PIE_RAD 0.0174532925199  // PIE / RAD
#endif // PIE_RAD

#ifndef RAD_PIE
#define RAD_PIE 57.2957795130823  // PIE / RAD
#endif // RAD_PIE
   
#define MAX_PARAMS_IN_RECORD	( 256 )  // 一レコードに含まれる（カンマで区切られた）データ項目数の最大値

#define ESCAPE_FLOAT_Z2    "tz2"
#define ESCAPE_FLOAT_XY2   "xy2"

//
// conversion between geographic coordinate systems
// 

#define LATSTEP_25000D 0     // Japan 25000 Map Length of Single sheet in Latitude degree
#define LATSTEP_25000M 5     // Japan 25000 Map Length of Single sheet in Latitude minuite
#define LATSTEP_25000S 0.0 // Japan 25000 Map Length of Single sheet in Latitude second
#define LONSTEP_25000D 0     // Japan 25000 Map Length of Single sheet in Longitude degree
#define LONSTEP_25000M 7     // Japan 25000 Map Length of Single sheet in Longitude minuite
#define LONSTEP_25000S 30.0  // Japan 25000 Map Length of Single sheet in Longitude second

#define LATSTEP_50000D 0     // Japan 50000 Map Length of Single sheet in Latitude degree
#define LATSTEP_50000M 10  // Japan 50000 Map Length of Single sheet in Latitude minuite
#define LATSTEP_50000S 0.0  // Japan 50000 Map Length of Single sheet in Latitude second
#define LONSTEP_50000D 0     // Japan 50000 Map Length of Single sheet in Longitude degree
#define LONSTEP_50000M 15  // Japan 50000 Map Length of Single sheet in Longitude minuite
#define LONSTEP_50000S 0.0  // Japan 50000 Map Length of Single sheet in Longitude second

#define LATBASE_25000D 36  // Japan 25000 Map Origin Latitude degree
#define LATBASE_25000M 0     // Japan 25000 Map Origin Latitude minuite
#define LATBASE_25000S 0.0  // Japan 25000 Map Origin Latitude second
#define LONBASE_25000D 140  // Japan 25000 Map Origin Longitude degree
#define LONBASE_25000M 0     // Japan 25000 Map Origin Longitude minuite
#define LONBASE_25000S 0.0  // Japan 25000 Map Origin Longitude second

   // 一次メッシュ＝20万地形図
#define LATSTEP_ITIJID 0     // ichiji mesh, width in lattitude degree
#define LATSTEP_ITIJIM 40    // ichiji mesh, width in lattitude minuite
#define LATSTEP_ITIJIS 0.0  // ichiji mesh, width in lattitude second
#define LONSTEP_ITIJID 1     // ichiji mesh, width in Longitude degree
#define LONSTEP_ITIJIM 0     // ichiji mesh, width in Longitude minuite
#define LONSTEP_ITIJIS 0.0  // ichiji mesh, width in Longitude second

#define LATBASE_ITIJID 0     // ichiji mesh, origin in lattitude degree
#define LATBASE_ITIJIM 0     // ichiji mesh, origin in lattitude minuite
#define LATBASE_ITIJIS 0.0  // ichiji mesh, origin in lattitude second
#define LONBASE_ITIJID 0     // ichiji mesh, origin in Longitude degree
#define LONBASE_ITIJIM 0     // ichiji mesh, origin in Longitude minuite
#define LONBASE_ITIJIS 0.0  // ichiji mesh, origin in Longitude second

// ベッセル楕円体の地心座標と緯度経度標高

#define BESSELS_A  6377397.155 // 楕円体の長軸 
#define BESSELS_F  299.152813 // 楕円体の偏平率

#define GCP_NAME_SIZE  32  // 地表基準点の名称 

//
// 緯度経度→測量座標系XY座標への変換
//

#define MODE_XY_TO_BL  ( 1 )
#define MODE_BL_TO_XY  ( 2 )

#ifndef DELIMITOUT_SIZE
#define DELIMITOUT_SIZE 200
#endif // DELIMITOUT_SIZE

//
// *** Should be conveted to inline functions ***
//

#ifndef vgiven
#define vgiven(x)	( (x) > NODATA + 10)
#endif // vgiven

// 
// deg2rad(a)  given angle in DEGREE, return the value in RADIAN.     
// rad2deg(a)  given angle in RADIAN, return the value in DEGREE.
//

#ifndef deg2rad
#define deg2rad( a ) ( PIE_RAD * ( a ) )
#endif // deg2rad

#ifndef rad2deg
#define rad2deg(a) ( RAD_PIE * ( a ) )
#endif // rad2deg


// --- environmental setting type ---

typedef enum {
   EnvModeBagster = 1, // Daily Light
   EnvModeHikari = 2, // Hikari
   //
   EnvModeScope = 11,
   EnvModeRectify = 12,
   EnvModeSampler = 13,
   EnvModeOrtho = 15,
} PixEnvModeSetting;

} // namespace  
