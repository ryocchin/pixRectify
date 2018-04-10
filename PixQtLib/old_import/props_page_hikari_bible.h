#pragma once

#include <QtCore>
#include <QtGui>

#include "pixq_options_page.h"

namespace Ui {
    class props_page_hikari_bible;
}

class props_page_hikari_bible : public QWidget, public pixq_options_page
{
    Q_OBJECT

public:
    explicit props_page_hikari_bible(QWidget *parent = 0);
    ~props_page_hikari_bible();

private:
    Ui::props_page_hikari_bible *ui;

private:
   void SetBibleVersion( void );
   void SetSecondBibleVersion( void );

public:
   void SetData( void );
   bool Check( void );

protected:
   void closeEvent(QCloseEvent *event);

private slots:    
    void on_hikari_version_kougo_radio_clicked();
    void on_hikari_version_shinkai2_radio_clicked();
    void on_hikari_version_shinkai3_radio_clicked();
    void on_hikari_version_kyoudou_radio_clicked();
    void on_hikari_version_bungo_radio_clicked();
    void on_hikari_version_raguet_radio_clicked();
    void on_hikari_version_tsukamoto_radio_clicked();
    void on_hikari_version_kjv_radio_clicked();
    void on_hikari_version_isv_radio_clicked();
        
    void on_hikari_2nd_version_kougo_radio_clicked();
    void on_hikari_2nd_version_shinkai2_radio_clicked();
    void on_hikari_2nd_version_shinkai3_radio_clicked();
    void on_hikari_2nd_version_kyoudou_radio_clicked();
    void on_hikari_2nd_version_bungo_radio_clicked();
    void on_hikari_2nd_version_raguet_radio_clicked();
    void on_hikari_2nd_version_tsukamoto_radio_clicked();
    void on_hikari_2nd_version_kjv_radio_clicked();
    void on_hikari_2nd_version_isv_radio_clicked();
    
    void on_hikari_version_akjv_radio_clicked();
    void on_hikari_2nd_version_akjv_radio_clicked();
};

