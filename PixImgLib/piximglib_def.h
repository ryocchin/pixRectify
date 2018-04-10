#pragma once

namespace _pix_plot_img_framework {

//
// Display Image Color Mode
//
typedef enum {
	PixImageDisplayColorRgb = 0,       // Full Color(RGB)
	PixImageDisplayColorRed,           // Red Channel
	PixImageDisplayColorGreen,         // Green Channel
	PixImageDisplayColorBlue,          // Blue Channel
	PixImageDisplayColorPseudoRed,     // Red Channel in Pseudo Color
	PixImageDisplayColorPseudoGreen,   // Green Channel in Pseudo Color
	PixImageDisplayColorPseudoBlue,    // Blue Channel in Pseudo Color
} PixTOPOImageDisplayColor;

} // namespace  