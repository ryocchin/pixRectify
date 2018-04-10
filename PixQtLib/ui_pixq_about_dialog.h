/********************************************************************************
** Form generated from reading UI file 'pixq_about_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIXQ_ABOUT_DIALOG_H
#define UI_PIXQ_ABOUT_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <website_label_widget.h>

QT_BEGIN_NAMESPACE

class Ui_pixq_about_dialog
{
public:
    QGraphicsView *logo_view;
    QLabel *application_label;
    QLabel *release_date_label;
    QLabel *description_label;
    QLabel *company_label;
    QGroupBox *groupBox;
    QLabel *contact_title_label;
    website_label_widget *contact_label;
    QLabel *website_title_label;
    website_label_widget *website_label;
    QLabel *blog_title_label;
    website_label_widget *devblog_label;
    QPushButton *ok_button;

    void setupUi(QDialog *pixq_about_dialog)
    {
        if (pixq_about_dialog->objectName().isEmpty())
            pixq_about_dialog->setObjectName(QStringLiteral("pixq_about_dialog"));
        pixq_about_dialog->resize(322, 357);
        QFont font;
        font.setFamily(QString::fromUtf8("\357\274\255\357\274\263 \357\274\260\343\202\264\343\202\267\343\203\203\343\202\257"));
        pixq_about_dialog->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/ehagaki2_bagster.png"), QSize(), QIcon::Normal, QIcon::Off);
        pixq_about_dialog->setWindowIcon(icon);
        logo_view = new QGraphicsView(pixq_about_dialog);
        logo_view->setObjectName(QStringLiteral("logo_view"));
        logo_view->setEnabled(false);
        logo_view->setGeometry(QRect(15, 15, 291, 106));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(logo_view->sizePolicy().hasHeightForWidth());
        logo_view->setSizePolicy(sizePolicy);
        logo_view->setFrameShape(QFrame::Box);
        logo_view->setFrameShadow(QFrame::Sunken);
        logo_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        logo_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        logo_view->setForegroundBrush(brush);
        application_label = new QLabel(pixq_about_dialog);
        application_label->setObjectName(QStringLiteral("application_label"));
        application_label->setGeometry(QRect(15, 130, 291, 31));
        sizePolicy.setHeightForWidth(application_label->sizePolicy().hasHeightForWidth());
        application_label->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        application_label->setFont(font1);
        application_label->setFrameShape(QFrame::Box);
        application_label->setFrameShadow(QFrame::Sunken);
        application_label->setAlignment(Qt::AlignCenter);
        release_date_label = new QLabel(pixq_about_dialog);
        release_date_label->setObjectName(QStringLiteral("release_date_label"));
        release_date_label->setGeometry(QRect(15, 160, 296, 16));
        QPalette palette;
        QBrush brush1(QColor(0, 0, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(127, 127, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(63, 63, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(0, 0, 127, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(0, 0, 170, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        QBrush brush7(QColor(0, 0, 0, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush7);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush7);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush2);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush7);
        release_date_label->setPalette(palette);
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(8);
        font2.setBold(false);
        font2.setWeight(50);
        release_date_label->setFont(font2);
        release_date_label->setFrameShape(QFrame::NoFrame);
        release_date_label->setFrameShadow(QFrame::Sunken);
        release_date_label->setAlignment(Qt::AlignCenter);
        release_date_label->setWordWrap(false);
        description_label = new QLabel(pixq_about_dialog);
        description_label->setObjectName(QStringLiteral("description_label"));
        description_label->setGeometry(QRect(15, 185, 296, 21));
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(9);
        font3.setBold(true);
        font3.setWeight(75);
        description_label->setFont(font3);
        description_label->setFrameShape(QFrame::NoFrame);
        description_label->setFrameShadow(QFrame::Sunken);
        description_label->setAlignment(Qt::AlignCenter);
        company_label = new QLabel(pixq_about_dialog);
        company_label->setObjectName(QStringLiteral("company_label"));
        company_label->setGeometry(QRect(15, 205, 296, 16));
        QFont font4;
        font4.setFamily(QStringLiteral("Arial"));
        font4.setBold(true);
        font4.setWeight(75);
        company_label->setFont(font4);
        company_label->setFrameShape(QFrame::NoFrame);
        company_label->setFrameShadow(QFrame::Sunken);
        company_label->setAlignment(Qt::AlignCenter);
        groupBox = new QGroupBox(pixq_about_dialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(15, 230, 296, 81));
        contact_title_label = new QLabel(groupBox);
        contact_title_label->setObjectName(QStringLiteral("contact_title_label"));
        contact_title_label->setGeometry(QRect(10, 10, 51, 16));
        QFont font5;
        font5.setFamily(QStringLiteral("Arial"));
        contact_title_label->setFont(font5);
        contact_label = new website_label_widget(groupBox);
        contact_label->setObjectName(QStringLiteral("contact_label"));
        contact_label->setGeometry(QRect(65, 10, 221, 16));
        QFont font6;
        font6.setFamily(QStringLiteral("Arial"));
        font6.setBold(false);
        font6.setWeight(50);
        contact_label->setFont(font6);
        contact_label->setFrameShape(QFrame::Panel);
        contact_label->setFrameShadow(QFrame::Sunken);
        contact_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        website_title_label = new QLabel(groupBox);
        website_title_label->setObjectName(QStringLiteral("website_title_label"));
        website_title_label->setGeometry(QRect(10, 30, 51, 16));
        website_title_label->setFont(font5);
        website_label = new website_label_widget(groupBox);
        website_label->setObjectName(QStringLiteral("website_label"));
        website_label->setGeometry(QRect(65, 30, 221, 16));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        QBrush brush9(QColor(106, 104, 100, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush9);
        website_label->setPalette(palette1);
        website_label->setFont(font6);
        website_label->setFrameShape(QFrame::Panel);
        website_label->setFrameShadow(QFrame::Sunken);
        website_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        blog_title_label = new QLabel(groupBox);
        blog_title_label->setObjectName(QStringLiteral("blog_title_label"));
        blog_title_label->setGeometry(QRect(10, 55, 51, 16));
        blog_title_label->setFont(font5);
        devblog_label = new website_label_widget(groupBox);
        devblog_label->setObjectName(QStringLiteral("devblog_label"));
        devblog_label->setGeometry(QRect(65, 55, 221, 16));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush9);
        devblog_label->setPalette(palette2);
        devblog_label->setFont(font6);
        devblog_label->setFrameShape(QFrame::Panel);
        devblog_label->setFrameShadow(QFrame::Sunken);
        devblog_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ok_button = new QPushButton(pixq_about_dialog);
        ok_button->setObjectName(QStringLiteral("ok_button"));
        ok_button->setGeometry(QRect(245, 320, 61, 21));
        ok_button->setFont(font5);

        retranslateUi(pixq_about_dialog);

        QMetaObject::connectSlotsByName(pixq_about_dialog);
    } // setupUi

    void retranslateUi(QDialog *pixq_about_dialog)
    {
        pixq_about_dialog->setWindowTitle(QApplication::translate("pixq_about_dialog", "PixTOPO Tool", Q_NULLPTR));
        application_label->setText(QApplication::translate("pixq_about_dialog", "Application", Q_NULLPTR));
        release_date_label->setText(QApplication::translate("pixq_about_dialog", "Release Date", Q_NULLPTR));
        description_label->setText(QApplication::translate("pixq_about_dialog", "Description", Q_NULLPTR));
        company_label->setText(QApplication::translate("pixq_about_dialog", "Company", Q_NULLPTR));
        groupBox->setTitle(QString());
        contact_title_label->setText(QApplication::translate("pixq_about_dialog", "Contact:", Q_NULLPTR));
        contact_label->setText(QApplication::translate("pixq_about_dialog", "Contact", Q_NULLPTR));
        website_title_label->setText(QApplication::translate("pixq_about_dialog", "Website:", Q_NULLPTR));
        website_label->setText(QApplication::translate("pixq_about_dialog", "Website", Q_NULLPTR));
        blog_title_label->setText(QApplication::translate("pixq_about_dialog", "Blog", Q_NULLPTR));
        devblog_label->setText(QApplication::translate("pixq_about_dialog", "Blog", Q_NULLPTR));
        ok_button->setText(QApplication::translate("pixq_about_dialog", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class pixq_about_dialog: public Ui_pixq_about_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIXQ_ABOUT_DIALOG_H
