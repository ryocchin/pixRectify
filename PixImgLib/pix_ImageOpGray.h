#pragma once

//
// create grayscale image from the input image
//

namespace _pix_plot_img_framework {

class PIXIMGLIB_EXPORT pixq_ImageOpGray : public pixq_ImageOp
{
public:
   pixq_ImageOpGray(void);
   ~pixq_ImageOpGray(void);
   
public:
   bool Proc( void );
   bool procCpu(void);
   bool procCuda(void);
};

} // namespace _pix_plot_img_framework 
