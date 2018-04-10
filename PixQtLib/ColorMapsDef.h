#pragma once

//----------------------------------------------------------------------
// カラーマップの定義
//----------------------------------------------------------------------

#define COLMAP_STANDARD_TOPO     0
#define COLMAP_STANDARD_ASPECT   1
#define COLMAP_BLUE              2
#define COLMAP_STANDARD_SLOPE    3
#define COLMAP_MARS_TOPO		   4
#define COLMAP_YELLOW_TOPO		   5

//----------------------------------------------------------------------
// COLMAP_STANDARD_TOPO
// standard topography map by elevation
//----------------------------------------------------------------------

#define STANDARD_COLORS		( 18 )

#define STANDARD_COL00	RGB(  89, 157,  86 )
#define STANDARD_COL01	RGB( 105, 166,  96 )
#define STANDARD_COL02	RGB( 120, 175, 106 )
#define STANDARD_COL03	RGB( 136, 185, 117 )
#define STANDARD_COL04	RGB( 152, 194, 127 )
#define STANDARD_COL05	RGB( 167, 203, 137 )
#define STANDARD_COL06	RGB( 183, 212, 147 )
#define STANDARD_COL07	RGB( 199, 222, 158 )
#define STANDARD_COL08	RGB( 214, 231, 168 )
#define STANDARD_COL09	RGB( 230, 240, 178 )
#define STANDARD_COL10	RGB( 244, 223, 158 )
#define STANDARD_COL11	RGB( 255, 211, 143 )
#define STANDARD_COL12	RGB( 242, 195, 124 )
#define STANDARD_COL13	RGB( 236, 188, 116 )
#define STANDARD_COL14	RGB( 231, 180, 109 )
#define STANDARD_COL15	RGB( 216, 165,  97 )
#define STANDARD_COL16	RGB( 201, 151,  84 )
#define STANDARD_COL17	RGB( 187, 136,  72 )

//----------------------------------------------------------------------
// COLMAP_STANDARD_ASPECT
// standard aspect map
//----------------------------------------------------------------------

#define STANDARD_ASPECT_COLORS		( 16 )

#define STANDARD_ASPECT_COL00	RGB( 255,   0,   0 )
#define STANDARD_ASPECT_COL01	RGB( 127,   0, 127 )
#define STANDARD_ASPECT_COL02	RGB( 127,   0, 127 )
#define STANDARD_ASPECT_COL03	RGB(   0,   0, 255 )
#define STANDARD_ASPECT_COL04	RGB(   0,   0, 255 )
#define STANDARD_ASPECT_COL05	RGB(   0, 127, 255 )
#define STANDARD_ASPECT_COL06	RGB(   0, 127, 255 )
#define STANDARD_ASPECT_COL07	RGB(   0, 255, 255 )
#define STANDARD_ASPECT_COL08	RGB(   0, 255, 255 )
#define STANDARD_ASPECT_COL09	RGB(   0, 255, 127 )
#define STANDARD_ASPECT_COL10	RGB(   0, 255, 127 )
#define STANDARD_ASPECT_COL11	RGB(   0, 255,   0 )
#define STANDARD_ASPECT_COL12	RGB(   0, 255,   0 )
#define STANDARD_ASPECT_COL13	RGB( 127, 127,   0 )
#define STANDARD_ASPECT_COL14	RGB( 127, 127,   0 )
#define STANDARD_ASPECT_COL15	RGB( 255,   0,   0 )

//----------------------------------------------------------------------
// COLMAP_BLUE
// standard topography map by elevation
//----------------------------------------------------------------------

#define STANDARD_BLUE_COLORS		( 9 )

#define STANDARD_BLUE_COL00	RGB( 255, 255, 255 )
#define STANDARD_BLUE_COL01	RGB( 191, 191, 255 )
#define STANDARD_BLUE_COL02	RGB( 127, 127, 255 )
#define STANDARD_BLUE_COL03	RGB( 63, 63, 255 )
#define STANDARD_BLUE_COL04	RGB( 0, 0, 255 )
#define STANDARD_BLUE_COL05	RGB( 0, 0, 191 )
#define STANDARD_BLUE_COL06	RGB( 0, 0, 127 )
#define STANDARD_BLUE_COL07	RGB( 0, 0, 63 )
#define STANDARD_BLUE_COL08	RGB( 0, 0, 1 )

//----------------------------------------------------------------------
// COLMAP_STANDARD_SLOPE
// standard topography map by elevation
//----------------------------------------------------------------------

#define STANDARD_SLOPE_COLORS		( 9 )

#define STANDARD_BLUEGREEN_COL00	RGB(   127, 255, 127 )
#define STANDARD_BLUEGREEN_COL01	RGB(   127, 223, 159 )
#define STANDARD_BLUEGREEN_COL02	RGB(   127, 191, 191 )
#define STANDARD_BLUEGREEN_COL03	RGB(   127, 159, 223 )
#define STANDARD_BLUEGREEN_COL04	RGB( 127, 127, 255 )
#define STANDARD_BLUEGREEN_COL05	RGB( 159,   127, 223 )
#define STANDARD_BLUEGREEN_COL06	RGB( 191,   127, 191 )
#define STANDARD_BLUEGREEN_COL07	RGB( 223,   127, 159 )
#define STANDARD_BLUEGREEN_COL08	RGB( 255,   127, 127 )

#define COLMAP_MIN_SLOPE  0.0
#define COLMAP_MAX_SLOPE  30.0

//----------------------------------------------------------------------
// COLMAP_MARS_TOPO
// mars topography map
//----------------------------------------------------------------------

#define STANDARD_MARS_TOPO ( 9 )

#define STANDARD_MARS_TOPO_COL00	RGB( 255, 000, 255 )
#define STANDARD_MARS_TOPO_COL01	RGB( 000, 000, 255 )
#define STANDARD_MARS_TOPO_COL02	RGB( 000, 000, 255 )
#define STANDARD_MARS_TOPO_COL03	RGB( 000, 255, 0 )
#define STANDARD_MARS_TOPO_COL04	RGB( 000, 255, 0 )
#define STANDARD_MARS_TOPO_COL05	RGB( 255, 255, 000 )
#define STANDARD_MARS_TOPO_COL06	RGB( 255, 255, 000 )
#define STANDARD_MARS_TOPO_COL07	RGB( 255, 000, 000 )
#define STANDARD_MARS_TOPO_COL08	RGB( 255, 000, 000 )

//----------------------------------------------------------------------
// COLMAP_YELLOW_TOPO
// yellow only topography map
//----------------------------------------------------------------------

#define STANDARD_YELLOW_TOPO ( 5 )

#define STANDARD_YELLOW_TOPO_COL00	RGB( 222, 153, 86 )
#define STANDARD_YELLOW_TOPO_COL01	RGB( 222, 153, 86 )
#define STANDARD_YELLOW_TOPO_COL02	RGB( 222, 153, 86 )
#define STANDARD_YELLOW_TOPO_COL03	RGB( 222, 153, 86 )
#define STANDARD_YELLOW_TOPO_COL04	RGB( 222, 153, 86 )

//----------------------------------------------------------------------
// Common definition
//----------------------------------------------------------------------
#define STANDARD_SEA	RGB( 176, 247, 237 )    // 海の色
//#define STANDARD_SEA	RGB( 25, 212, 212 ) // 海の色
#define STANDARD_BACK	RGB( 22, 72, 72 ) // 裏側が見えている面の色
