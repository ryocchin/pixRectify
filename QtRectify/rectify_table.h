#pragma once

#include <pixqt_common.h>
#include <piximg_common.h>

#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

class rectify_window;

class rectify_table : public QTableWidget
{
   Q_OBJECT
    
private:
   bool _bTableInitialized;
   rectify_window *_pParent;

   bool _bCellSlotSet;

   // column number for "Used"
   int _iUsedCol;
   
public:
   rectify_table(QWidget *parent = 0);

   void setParent(rectify_window *pParent) { _pParent = pParent; }
   rectify_window *getParent(void) const { return _pParent; }
     
   void setTableContents( void );
   
public:
   void setRectifyTags(void);

private:
   void setTableColumns(void);
   void setTableStyles( void );   

private slots:
   void rectifyCellClicked(int row, int column);
   void rectifyCellDblClicked(int row, int column);
   
private:
   void setCellSlot(void);

protected:  
   void showEvent( QShowEvent *eve );
   void resizeEvent( QResizeEvent* );
};
