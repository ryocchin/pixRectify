#include <pixqt_common.h>
#include <piximg_common.h>
 
#include <pixqtlib.h>
using namespace _pix_plot_qt_framework;

#include <piximglib.h>
using namespace _pix_plot_img_framework;

#include "rectify_common.h"
#include "rectify_dock.h"
#include "rectify_window.h"
#include "rectify_pane.h"
#include "rectify_table.h"

#include "rectify_progress_dialog.h"
#include "rectify_search_thread.h"

rectify_table::rectify_table(QWidget *parent)
    : QTableWidget(parent)
{
   _bTableInitialized = false;
   _bCellSlotSet = false;

   setTableContents( );
   
   return;
}

//
// two image panes must be of same width!
//
void rectify_table::resizeEvent(QResizeEvent * /*ev*/)
{
   int iRow, nRows;

   if( !_bTableInitialized ) {
      goto PIX_EXIT;
   }

   setTableColumns();
   
   nRows = rowCount( );
   for( iRow = 0 ; iRow < nRows ; iRow++ ) {
      resizeRowToContents( iRow ); 
   }
      
   resizeRowsToContents( );
      
PIX_EXIT:
   return;
}

void rectify_table::showEvent(QShowEvent * /*eve*/)
{
   if( _bTableInitialized ) {
      goto PIX_EXIT;
   }

   _bTableInitialized = true;
   
   setTableContents( );
   
PIX_EXIT:
   return;
}

void rectify_table::setTableColumns(void)
{
   int k, nTableWidth, nColWidth, nCols, nScrollWidth;
   QSize sz, scroll_sz;
   QScrollBar *vert;
   double dRatioWidth, dSumWidth, dActiveWidth;
   vector<double> vdWidth;
   
   // scroll bar

   setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
   setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );

   vert = verticalScrollBar( );
   scroll_sz = vert->size( );
   nScrollWidth = scroll_sz.width( );

   //
   
   vdWidth.clear( );
   vdWidth.push_back(5.0);    // ID
   vdWidth.push_back(15.0);   // Left X
   vdWidth.push_back(15.0);   // Left Y
   vdWidth.push_back(15.0);   // Right X
   vdWidth.push_back(15.0);   // Right Y
   vdWidth.push_back(15.0);   // Stat
   vdWidth.push_back(10.0);   // Used
   vdWidth.push_back(15.0);   // Corr
   vdWidth.push_back(7.5);   // Outlier
   vdWidth.push_back(15.0);   // Right.X
   vdWidth.push_back(15.0);   // Right.Y
   vdWidth.push_back(15.0);   // Disparity X
   vdWidth.push_back(15.0);   // Disparity Y
   
   nCols = (int)vdWidth.size( );
   setColumnCount( nCols );
      
   // set table width
   
   sz = size( );
   nTableWidth = sz.width( );
   dActiveWidth = (double)( nTableWidth - nScrollWidth ) * 0.925;

   // set width of each column

   dSumWidth = 0.0;
   for( k = 0 ; k < nCols ; k++ ) {
      dSumWidth = dSumWidth + vdWidth.at( k );
   }

   for( k = 0 ; k < nCols ; k++ ) {
      dRatioWidth = vdWidth.at( k ) / dSumWidth;
      nColWidth = (int)( dActiveWidth * dRatioWidth );
      setColumnWidth( k, nColWidth );
   }

   //
   
   setTableStyles();
   setShowGrid( true );

   return;
}
   
void rectify_table::setTableStyles(void)
{
   QString style;

   // set table style
   
   style = "QTableWidget::item { ";
   style += " padding-bottom:2px; ";
   style += " padding-top:2px; ";
   style += " padding-left:2px; ";
   style += " padding-right:2px; ";
   //style += " background-color: green; ";
   //style += " selection-color: yellow; ";
   style += "color: black; ";
   style += " background-color: rgb( 191, 191, 191 ); ";
   style += " }";

   setStyleSheet( style );

   style = "QTableWidget::item:hover { ";
   style += "color: black; ";
   style += " background-color: rgb( 191, 191, 255 ); ";
   style += " }";

   style += "QTableWidget::item:selected { ";
   style += "color: white; ";
   style += "background-color: rgb( 127, 127, 127 ); ";
   style += " }";
   
   setStyleSheet( style );

   return;
}

void rectify_table::setTableContents(void)
{
   rectify_window *pMain = getParent();
   QString strLabel;

   if( !_bTableInitialized ) {
      goto PIX_EXIT;
   }
   
QApplication::setOverrideCursor(QCursor(Qt::BusyCursor)); 

   _iUsedCol = -1;

   setRectifyTags();

   //scrollToTop();
   setCellSlot();

   pMain->setRectifyMenuState();

PIX_EXIT:
QApplication::restoreOverrideCursor(); 
   return;
}

void rectify_table::setRectifyTags(void)
{
   rectify_window *pMain = getParent();
   bool bOutLier, bSelected, bUsed;
   int nCols, iCol, i, nRowHeight;
   QString strValue;
   QStringList strHeaderLabel;
   pixq_FringeTag *pTag;
   pixq_Dbl2D d2Resi;

   double dU, dV, dCorr;
   int iX, iY, iU, iV;
   QFont fn, fn_bold;

   pixq_FringesTag *pTags = pMain->getRectifyTag();
   int nTags = pTags->getTags();

   QBrush CellBrush, TextBrush;

   int iTransform = pTags->getTransform();

   //
   
   fn = font();
   fn.setBold(false);
   fn_bold = font();
   fn_bold.setBold(true);

   // *** set header ***

   setRowCount(nTags);
   setSelectionMode(QAbstractItemView::SingleSelection);

   //
   // columns
   //

   strHeaderLabel.clear();
   strHeaderLabel.push_back(pMain->getRectifyLabel("Table", "ID"));               // 0 
   strHeaderLabel.push_back(pMain->getRectifyLabel("Table", "Left X"));           // 1
   strHeaderLabel.push_back(pMain->getRectifyLabel("Table", "Left Y"));           // 2
   strHeaderLabel.push_back(pMain->getRectifyLabel("Table", "Right X"));          // 3
   strHeaderLabel.push_back(pMain->getRectifyLabel("Table", "Right Y"));          // 4
   strHeaderLabel.push_back(pMain->getRectifyLabel("Table", "Stat"));             // 5
   strHeaderLabel.push_back(pMain->getRectifyLabel("Table", "Used"));             // 6
                                                                                 
   strHeaderLabel.push_back(pMain->getRectifyLabel("Table", "Corr"));             // 7
   strHeaderLabel.push_back(pMain->getRectifyLabel("Table", "Outlier"));          // 8
   strHeaderLabel.push_back(pMain->getRectifyLabel("Table", "Right.X"));          // 9
   strHeaderLabel.push_back(pMain->getRectifyLabel("Table", "Right.Y"));          // 10
   strHeaderLabel.push_back(pMain->getRectifyLabel("Table", "Disparity.X"));      // 11
   strHeaderLabel.push_back(pMain->getRectifyLabel("Table", "Disparity.Y"));      // 12

   nCols = strHeaderLabel.size();

   setColumnCount(13);
   nCols = columnCount();

   for (i = 0; i < nCols; i++) {
      QTableWidgetItem *header = new QTableWidgetItem();
      strValue = strHeaderLabel.at(i);
      header->setText(strValue);
      setHorizontalHeaderItem(i, header);

      //horizontalHeader()->setResizeMode( i, QHeaderView::Fixed );
      horizontalHeader()->setSectionResizeMode(i, QHeaderView::Fixed);
   }

   horizontalHeader()->setDefaultSectionSize(90);
   //horizontalHeader()->setResizeMode( 0, QHeaderView::Stretch );
   horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

   horizontalHeader()->show();
   verticalHeader()->hide();

   if (0 >= nTags) {
      setRowCount(0);
      goto PIX_EXIT;
   }

   // *** table befavior ***

   setSelectionMode(QAbstractItemView::SingleSelection);
   setSelectionBehavior(QAbstractItemView::SelectRows);

   //clearSelection();

   // *** set tags ***

   nRowHeight = 25;
   _iUsedCol = -1;
   
   for (i = 0; i < nTags; i++) {
      QTableWidgetItem *itemID = new QTableWidgetItem();
      QTableWidgetItem *itemLeftX = new QTableWidgetItem();
      QTableWidgetItem *itemLeftY = new QTableWidgetItem();
      QTableWidgetItem *itemInRightX = new QTableWidgetItem();
      QTableWidgetItem *itemInRightY = new QTableWidgetItem();
      QTableWidgetItem *itemStatus = new QTableWidgetItem();
      QTableWidgetItem *itemUsed = new QTableWidgetItem();
      QTableWidgetItem *itemCorr = new QTableWidgetItem();
      QTableWidgetItem *itemOutlier = new QTableWidgetItem();
      QTableWidgetItem *itemOutRightX = new QTableWidgetItem();
      QTableWidgetItem *itemOutRightY = new QTableWidgetItem();
      QTableWidgetItem *itemDisparityX = new QTableWidgetItem();
      QTableWidgetItem *itemDisparityY = new QTableWidgetItem();
      
      //

      itemID->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
      itemLeftX->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
      itemLeftY->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
      itemInRightX->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
      itemInRightY->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
      itemStatus->setTextAlignment(Qt::AlignVCenter | Qt::AlignCenter);
      itemUsed->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
      itemCorr->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);

      itemOutlier->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
      itemOutRightX->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
      itemOutRightY->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
      itemDisparityX->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
      itemDisparityY->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);

      //

      itemID->setFlags(itemID->flags() & ~Qt::ItemIsEditable);
      itemLeftX->setFlags(itemLeftX->flags() & ~Qt::ItemIsEditable);
      itemLeftY->setFlags(itemLeftY->flags() & ~Qt::ItemIsEditable);
      itemInRightX->setFlags(itemInRightX->flags() & ~Qt::ItemIsEditable);
      itemInRightY->setFlags(itemInRightY->flags() & ~Qt::ItemIsEditable);
      itemStatus->setFlags(itemStatus->flags() & ~Qt::ItemIsEditable);
      itemUsed->setFlags(itemUsed->flags() & Qt::ItemIsUserCheckable & ~Qt::ItemIsEditable);
      itemCorr->setFlags(itemCorr->flags() & ~Qt::ItemIsEditable);

      itemOutlier->setFlags(itemOutlier->flags() & ~Qt::ItemIsEditable);
      itemOutRightX->setFlags(itemOutRightX->flags() & ~Qt::ItemIsEditable);
      itemOutRightY->setFlags(itemOutRightY->flags() & ~Qt::ItemIsEditable);
      itemDisparityX->setFlags(itemDisparityX->flags() & ~Qt::ItemIsEditable);
      itemDisparityY->setFlags(itemDisparityY->flags() & ~Qt::ItemIsEditable);
      
      //

      pTag = pTags->getNthTag(i);

      iX = pTag->getXTag();
      iY = pTag->getYTag();
      iU = pTag->getRightXTag();
      iV = pTag->getRightYTag();

      //

      strValue.sprintf("%d", i + 1);
      itemID->setText(strValue);

      strValue.sprintf("%d", iX);
      itemLeftX->setText(strValue);

      strValue.sprintf("%d", iY);
      itemLeftY->setText(strValue);

      strValue.sprintf("%d", iU);
      itemInRightX->setText(strValue);

      strValue.sprintf("%d", iV);
      itemInRightY->setText(strValue);

      strValue = pTag->getMatchStatusString();
      itemStatus->setText(strValue);

      bUsed = pTag->getUsed();
      if (bUsed) {
         itemUsed->setCheckState(Qt::Checked);
         itemUsed->setText("Used");
      }
      else {
         itemUsed->setCheckState(Qt::Unchecked);
         itemUsed->setText("Removed");
      }

      dCorr = pTag->getCorrVal();
      if (bUsed) {
         strValue.sprintf("%.2f", pTag->getCorrVal());
      }
      else {
         strValue.sprintf("---");
      }
      itemCorr->setText(strValue);
      
      // set residuals after affine trasnformation

      switch (iTransform) {
      case pixq_Properties::TransformationRectification:
         //
         // stereo rectification
         //
         bUsed = pTag->getUsed();
         if (bUsed) {
            bOutLier = pTag->GetRotOutlier();
            strValue.sprintf(bOutLier ? "Yes" : "No");
            itemOutlier->setText(strValue);

            pTags->getRectifySide(1, iU, iV, dU, dV);
            strValue.sprintf("%.2f", dU);
            itemOutRightX->setText(strValue);

            strValue.sprintf("%.2f", dV);
            itemOutRightY->setText(strValue);

            d2Resi = pTags->getRectifyDisparity(iX, iY, iU, iV);
            strValue.sprintf("%.2f", d2Resi.getX());
            itemDisparityX->setText(strValue);

            strValue.sprintf("%.2f", d2Resi.getY());
            itemDisparityY->setText(strValue);
         }
         else {
            strValue.sprintf("---");
            itemOutlier->setText(strValue);
            itemOutRightX->setText(strValue);
            itemOutRightY->setText(strValue);
            itemDisparityX->setText(strValue);
            itemDisparityY->setText(strValue);
         }
         break;
         
      default:
         strValue.sprintf("---");
         itemOutlier->setText(strValue);
         itemOutRightX->setText(strValue);
         itemOutRightY->setText(strValue);
         itemDisparityX->setText(strValue);
         itemDisparityY->setText(strValue);
         break;
      }
      
      //

      setRowHeight(i, nRowHeight);

      // colors

      CellBrush.setColor(QColor(Qt::white));
      TextBrush.setColor(QColor(Qt::black));

      itemID->setBackground(CellBrush);
      itemLeftX->setBackground(CellBrush);
      itemLeftY->setBackground(CellBrush);
      itemInRightX->setBackground(CellBrush);
      itemInRightY->setBackground(CellBrush);
      itemStatus->setBackground(CellBrush);
      itemUsed->setBackground(CellBrush);
      itemCorr->setBackground(CellBrush);

      itemOutlier->setBackground(CellBrush);
      itemOutRightX->setBackground(CellBrush);
      itemOutRightY->setBackground(CellBrush);
      itemDisparityX->setBackground(CellBrush);
      itemDisparityY->setBackground(CellBrush);
      
      itemID->setForeground(TextBrush);
      itemLeftX->setForeground(TextBrush);
      itemLeftY->setForeground(TextBrush);
      itemInRightX->setForeground(TextBrush);
      itemInRightY->setForeground(TextBrush);
      itemStatus->setForeground(TextBrush);
      itemUsed->setForeground(TextBrush);
      itemCorr->setForeground(TextBrush);

      itemOutlier->setForeground(TextBrush);
      itemOutRightX->setForeground(TextBrush);
      itemOutRightY->setForeground(TextBrush);
      itemDisparityX->setForeground(TextBrush);
      itemDisparityY->setForeground(TextBrush);

      // Tag Selected?

      bSelected = pTag->getSelected();
      if (bSelected) {
         itemID->setFont(fn_bold);
         itemLeftX->setFont(fn_bold);
         itemLeftY->setFont(fn_bold);
         itemInRightX->setFont(fn_bold);
         itemInRightY->setFont(fn_bold);
         itemStatus->setFont(fn_bold);
         itemUsed->setFont(fn_bold);
         itemCorr->setFont(fn_bold);
         itemOutlier->setFont(fn_bold);
         itemOutRightX->setFont(fn_bold);
         itemOutRightY->setFont(fn_bold);
         itemDisparityX->setFont(fn_bold);
         itemDisparityY->setFont(fn_bold);
      }
      else {
         itemID->setFont(fn);
         itemLeftX->setFont(fn);
         itemLeftY->setFont(fn);
         itemInRightX->setFont(fn);
         itemInRightY->setFont(fn);
         itemStatus->setFont(fn);
         //itemUsed->setFont(fn);
         itemCorr->setFont(fn);
         itemOutlier->setFont(fn);
         itemOutRightX->setFont(fn);
         itemOutRightY->setFont(fn);
         itemDisparityX->setFont(fn);
         itemDisparityY->setFont(fn);
      }

      //

      iCol = 0;
      setItem(i, iCol, itemID);

      iCol++;
      setItem(i, iCol, itemLeftX);

      iCol++;
      setItem(i, iCol, itemLeftY);

      iCol++;
      setItem(i, iCol, itemInRightX);

      iCol++;
      setItem(i, iCol, itemInRightY);

      iCol++;
      setItem(i, iCol, itemStatus);

      iCol++;
      setItem(i, iCol, itemUsed);
      if (0 > _iUsedCol) {
         _iUsedCol = iCol;
      }

      iCol++;
      setItem(i, iCol, itemCorr);

      iCol++;
      setItem(i, iCol, itemOutlier);

      iCol++;
      setItem(i, iCol, itemOutRightX);

      iCol++;
      setItem(i, iCol, itemOutRightY);

      iCol++;
      setItem(i, iCol, itemDisparityX);

      iCol++;
      setItem(i, iCol, itemDisparityY);

      resizeRowToContents(i);

      //

      //itemUsed->setFlags( itemUsed->flags() & Qt::ItemIsEditable );
   }

   // resize columns

   resizeRowsToContents();
   setTableColumns();
   //scrollToTop();
   //  setCellSlot();

   // --- Done ---
PIX_EXIT:
   return;
}


void rectify_table::setCellSlot(void)
{
   //int xx = QApplication::doubleClickInterval();
   
   if (_bCellSlotSet) {
      goto PIX_EXIT;
   }

  connect(this, SIGNAL(cellClicked(int, int)), this,
     SLOT(rectifyCellClicked(int, int)));

   connect(this, SIGNAL(cellDoubleClicked(int, int)), this,
      SLOT(rectifyCellDblClicked(int, int)));

   _bCellSlotSet = true;

PIX_EXIT:
   return;
} 


void rectify_table::rectifyCellClicked(int row, int column)
{
   rectify_window *pMain = (rectify_window*)getParent();
   pixq_FringesTag *pTags = pMain->getRectifyTag();
   int nTags = pTags->getTags();
   int iTag;

   if (0 > row || nTags <= row) {
      goto PIX_EXIT;
   }

   // " Used Column"

   if (_iUsedCol == column) {
      // just change the status
      iTag = row;
      pTags->flipUsedStatus(iTag);
      pMain->rectifyAnalyzeTagPoints(false);
   }
   else {
      // other wise change the selection status   
      pTags->flipReselectTag(row);
   }

   pMain->refreshPanes();

   // --- Done ---
PIX_EXIT:
   return;
}

void rectify_table::rectifyCellDblClicked(int row, int column)
{
   rectify_window *pMain = (rectify_window*)getParent();
   pixq_FringesTag *pTags = pMain->getRectifyTag();
   int nTags = pTags->getTags();
   int iTag;

   if (0 > row || nTags <= row) {
      goto PIX_EXIT;
   }

   // " Used Column"

   if (_iUsedCol == column) {
      // just change the status
      pTags->flipUsedStatus(row);
      pTags->flipReselectTag(row);
      pMain->rectifyAnalyzeTagPoints(false);
   }
   else {
      // other wise change the selection status   
      pTags->flipReselectTag(row);
   }

   // show the tag at the center
   
   iTag = row;
   pMain->centerToTag(iTag);

   // --- Done ---
PIX_EXIT:
   return;
}
