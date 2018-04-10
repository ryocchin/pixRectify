/********************************************************************************
** Form generated from reading UI file 'rectify_window.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECTIFY_WINDOW_H
#define UI_RECTIFY_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_rectify_window
{
public:
    QAction *action_file_properties;
    QAction *action_file_exit;
    QAction *action_view_first_image;
    QAction *action_view_second_image;
    QAction *action_help_about;
    QAction *action_file_select_image_pair;
    QAction *action_zoom_real_size;
    QAction *action_zoom_recneter;
    QAction *action_zoom_zoom_up;
    QAction *action_zoom_zoom_down;
    QAction *action_zoom_scroll_up;
    QAction *action_zoom_scroll_down;
    QAction *action_zoom_scroll_left;
    QAction *action_zoom_scroll_right;
    QAction *action_rectify_generate_control_points;
    QAction *action_rectify_stereo_rectification;
    QAction *action_rectify_show_control_points;
    QAction *action_view_original_image;
    QAction *action_view_rectified_images;
    QAction *action_rectify_horizontal_check_line;
    QAction *action_file_save_image_pair;
    QAction *action_file_save_anaglyph;
    QAction *action_rectify_all_rectification;
    QAction *action_rectify_hit_and_match;
    QAction *action_help_help;
    QWidget *centralwidget;
    QStatusBar *statusbar;
    QToolBar *mainToolBar;
    QToolBar *viewToolBar;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuHelp;
    QMenu *menuControl;
    QMenu *menuZoom;
    QMenu *menuRectify;
    QMenu *menuRectifyAnalyze;
    QToolBar *zoomFrameToolBar;

    void setupUi(QMainWindow *rectify_window)
    {
        if (rectify_window->objectName().isEmpty())
            rectify_window->setObjectName(QStringLiteral("rectify_window"));
        rectify_window->resize(561, 418);
        QFont font;
        font.setFamily(QString::fromUtf8("\343\203\241\343\202\244\343\203\252\343\202\252"));
        rectify_window->setFont(font);
        rectify_window->setAcceptDrops(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/rectify1.png"), QSize(), QIcon::Normal, QIcon::Off);
        rectify_window->setWindowIcon(icon);
        action_file_properties = new QAction(rectify_window);
        action_file_properties->setObjectName(QStringLiteral("action_file_properties"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/file_options.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_file_properties->setIcon(icon1);
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        action_file_properties->setFont(font1);
        action_file_exit = new QAction(rectify_window);
        action_file_exit->setObjectName(QStringLiteral("action_file_exit"));
        action_file_exit->setFont(font1);
        action_view_first_image = new QAction(rectify_window);
        action_view_first_image->setObjectName(QStringLiteral("action_view_first_image"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/show_first.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_view_first_image->setIcon(icon2);
        action_view_second_image = new QAction(rectify_window);
        action_view_second_image->setObjectName(QStringLiteral("action_view_second_image"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/show_second.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_view_second_image->setIcon(icon3);
        action_help_about = new QAction(rectify_window);
        action_help_about->setObjectName(QStringLiteral("action_help_about"));
        action_file_select_image_pair = new QAction(rectify_window);
        action_file_select_image_pair->setObjectName(QStringLiteral("action_file_select_image_pair"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/file_open_files.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_file_select_image_pair->setIcon(icon4);
        action_file_select_image_pair->setFont(font1);
        action_zoom_real_size = new QAction(rectify_window);
        action_zoom_real_size->setObjectName(QStringLiteral("action_zoom_real_size"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/zoom_real.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_zoom_real_size->setIcon(icon5);
        action_zoom_recneter = new QAction(rectify_window);
        action_zoom_recneter->setObjectName(QStringLiteral("action_zoom_recneter"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/zoom_recenter.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_zoom_recneter->setIcon(icon6);
        action_zoom_zoom_up = new QAction(rectify_window);
        action_zoom_zoom_up->setObjectName(QStringLiteral("action_zoom_zoom_up"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/zoom_up.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_zoom_zoom_up->setIcon(icon7);
        action_zoom_zoom_down = new QAction(rectify_window);
        action_zoom_zoom_down->setObjectName(QStringLiteral("action_zoom_zoom_down"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/zoom_down.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_zoom_zoom_down->setIcon(icon8);
        action_zoom_scroll_up = new QAction(rectify_window);
        action_zoom_scroll_up->setObjectName(QStringLiteral("action_zoom_scroll_up"));
        action_zoom_scroll_down = new QAction(rectify_window);
        action_zoom_scroll_down->setObjectName(QStringLiteral("action_zoom_scroll_down"));
        action_zoom_scroll_left = new QAction(rectify_window);
        action_zoom_scroll_left->setObjectName(QStringLiteral("action_zoom_scroll_left"));
        action_zoom_scroll_right = new QAction(rectify_window);
        action_zoom_scroll_right->setObjectName(QStringLiteral("action_zoom_scroll_right"));
        action_rectify_generate_control_points = new QAction(rectify_window);
        action_rectify_generate_control_points->setObjectName(QStringLiteral("action_rectify_generate_control_points"));
        action_rectify_stereo_rectification = new QAction(rectify_window);
        action_rectify_stereo_rectification->setObjectName(QStringLiteral("action_rectify_stereo_rectification"));
        action_rectify_show_control_points = new QAction(rectify_window);
        action_rectify_show_control_points->setObjectName(QStringLiteral("action_rectify_show_control_points"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/images/show_wiper_tags.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_rectify_show_control_points->setIcon(icon9);
        action_view_original_image = new QAction(rectify_window);
        action_view_original_image->setObjectName(QStringLiteral("action_view_original_image"));
        action_view_original_image->setIcon(icon2);
        action_view_rectified_images = new QAction(rectify_window);
        action_view_rectified_images->setObjectName(QStringLiteral("action_view_rectified_images"));
        action_view_rectified_images->setIcon(icon3);
        action_rectify_horizontal_check_line = new QAction(rectify_window);
        action_rectify_horizontal_check_line->setObjectName(QStringLiteral("action_rectify_horizontal_check_line"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/images/show_wiper_hor.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_rectify_horizontal_check_line->setIcon(icon10);
        action_file_save_image_pair = new QAction(rectify_window);
        action_file_save_image_pair->setObjectName(QStringLiteral("action_file_save_image_pair"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/images/file_save_files.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_file_save_image_pair->setIcon(icon11);
        action_file_save_anaglyph = new QAction(rectify_window);
        action_file_save_anaglyph->setObjectName(QStringLiteral("action_file_save_anaglyph"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/images/file_save_anaglyph.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_file_save_anaglyph->setIcon(icon12);
        action_rectify_all_rectification = new QAction(rectify_window);
        action_rectify_all_rectification->setObjectName(QStringLiteral("action_rectify_all_rectification"));
        action_rectify_hit_and_match = new QAction(rectify_window);
        action_rectify_hit_and_match->setObjectName(QStringLiteral("action_rectify_hit_and_match"));
        action_help_help = new QAction(rectify_window);
        action_help_help->setObjectName(QStringLiteral("action_help_help"));
        centralwidget = new QWidget(rectify_window);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        rectify_window->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(rectify_window);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\357\274\255\357\274\263 \357\274\260\343\202\264\343\202\267\343\203\203\343\202\257"));
        statusbar->setFont(font2);
        rectify_window->setStatusBar(statusbar);
        mainToolBar = new QToolBar(rectify_window);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        rectify_window->addToolBar(Qt::TopToolBarArea, mainToolBar);
        viewToolBar = new QToolBar(rectify_window);
        viewToolBar->setObjectName(QStringLiteral("viewToolBar"));
        viewToolBar->setFont(font2);
        rectify_window->addToolBar(Qt::TopToolBarArea, viewToolBar);
        menubar = new QMenuBar(rectify_window);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 561, 21));
        menubar->setFont(font1);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuFile->setFont(font1);
        menuView = new QMenu(menubar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuControl = new QMenu(menubar);
        menuControl->setObjectName(QStringLiteral("menuControl"));
        menuZoom = new QMenu(menubar);
        menuZoom->setObjectName(QStringLiteral("menuZoom"));
        menuRectify = new QMenu(menubar);
        menuRectify->setObjectName(QStringLiteral("menuRectify"));
        menuRectifyAnalyze = new QMenu(menuRectify);
        menuRectifyAnalyze->setObjectName(QStringLiteral("menuRectifyAnalyze"));
        rectify_window->setMenuBar(menubar);
        zoomFrameToolBar = new QToolBar(rectify_window);
        zoomFrameToolBar->setObjectName(QStringLiteral("zoomFrameToolBar"));
        zoomFrameToolBar->setFont(font2);
        rectify_window->addToolBar(Qt::TopToolBarArea, zoomFrameToolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuZoom->menuAction());
        menubar->addAction(menuRectify->menuAction());
        menubar->addAction(menuControl->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(action_file_select_image_pair);
        menuFile->addAction(action_file_save_image_pair);
        menuFile->addAction(action_file_save_anaglyph);
        menuFile->addSeparator();
        menuFile->addAction(action_file_properties);
        menuFile->addAction(action_file_exit);
        menuFile->addSeparator();
        menuView->addAction(action_view_original_image);
        menuView->addAction(action_view_rectified_images);
        menuHelp->addAction(action_help_help);
        menuHelp->addAction(action_help_about);
        menuZoom->addAction(action_zoom_recneter);
        menuZoom->addAction(action_zoom_real_size);
        menuZoom->addSeparator();
        menuZoom->addAction(action_zoom_zoom_up);
        menuZoom->addAction(action_zoom_zoom_down);
        menuZoom->addSeparator();
        menuZoom->addAction(action_zoom_scroll_up);
        menuZoom->addAction(action_zoom_scroll_down);
        menuZoom->addAction(action_zoom_scroll_left);
        menuZoom->addAction(action_zoom_scroll_right);
        menuRectify->addAction(action_rectify_all_rectification);
        menuRectify->addSeparator();
        menuRectify->addAction(action_rectify_show_control_points);
        menuRectify->addAction(action_rectify_horizontal_check_line);
        menuRectify->addAction(menuRectifyAnalyze->menuAction());
        menuRectifyAnalyze->addAction(action_rectify_generate_control_points);
        menuRectifyAnalyze->addAction(action_rectify_stereo_rectification);
        menuRectifyAnalyze->addSeparator();
        menuRectifyAnalyze->addAction(action_rectify_hit_and_match);

        retranslateUi(rectify_window);

        QMetaObject::connectSlotsByName(rectify_window);
    } // setupUi

    void retranslateUi(QMainWindow *rectify_window)
    {
        rectify_window->setWindowTitle(QApplication::translate("rectify_window", "pixPLOT - Rectification", Q_NULLPTR));
        action_file_properties->setText(QApplication::translate("rectify_window", "Properties", Q_NULLPTR));
        action_file_properties->setShortcut(QApplication::translate("rectify_window", "F8", Q_NULLPTR));
        action_file_exit->setText(QApplication::translate("rectify_window", "Exit", Q_NULLPTR));
        action_view_first_image->setText(QApplication::translate("rectify_window", "Left Image", Q_NULLPTR));
        action_view_first_image->setShortcut(QApplication::translate("rectify_window", "F", Q_NULLPTR));
        action_view_second_image->setText(QApplication::translate("rectify_window", "Right Image", Q_NULLPTR));
        action_view_second_image->setShortcut(QApplication::translate("rectify_window", "S", Q_NULLPTR));
        action_help_about->setText(QApplication::translate("rectify_window", "About pixRectify", Q_NULLPTR));
        action_file_select_image_pair->setText(QApplication::translate("rectify_window", "Select Images", Q_NULLPTR));
        action_zoom_real_size->setText(QApplication::translate("rectify_window", "Real Size", Q_NULLPTR));
        action_zoom_real_size->setShortcut(QApplication::translate("rectify_window", "0", Q_NULLPTR));
        action_zoom_recneter->setText(QApplication::translate("rectify_window", "Show the Whole Image", Q_NULLPTR));
        action_zoom_recneter->setShortcut(QApplication::translate("rectify_window", "5", Q_NULLPTR));
        action_zoom_zoom_up->setText(QApplication::translate("rectify_window", "Zoom +", Q_NULLPTR));
        action_zoom_zoom_up->setShortcut(QApplication::translate("rectify_window", "+", Q_NULLPTR));
        action_zoom_zoom_down->setText(QApplication::translate("rectify_window", "Zoom -", Q_NULLPTR));
        action_zoom_zoom_down->setShortcut(QApplication::translate("rectify_window", "-", Q_NULLPTR));
        action_zoom_scroll_up->setText(QApplication::translate("rectify_window", "Above", Q_NULLPTR));
        action_zoom_scroll_up->setShortcut(QApplication::translate("rectify_window", "8", Q_NULLPTR));
        action_zoom_scroll_down->setText(QApplication::translate("rectify_window", "Bottom", Q_NULLPTR));
        action_zoom_scroll_down->setShortcut(QApplication::translate("rectify_window", "2", Q_NULLPTR));
        action_zoom_scroll_left->setText(QApplication::translate("rectify_window", "Left", Q_NULLPTR));
        action_zoom_scroll_left->setShortcut(QApplication::translate("rectify_window", "4", Q_NULLPTR));
        action_zoom_scroll_right->setText(QApplication::translate("rectify_window", "Right", Q_NULLPTR));
        action_zoom_scroll_right->setShortcut(QApplication::translate("rectify_window", "6", Q_NULLPTR));
        action_rectify_generate_control_points->setText(QApplication::translate("rectify_window", "[1] Compute Rectification", Q_NULLPTR));
        action_rectify_stereo_rectification->setText(QApplication::translate("rectify_window", "[2] Stereo Rectification", Q_NULLPTR));
        action_rectify_show_control_points->setText(QApplication::translate("rectify_window", "Show Control Points", Q_NULLPTR));
        action_view_original_image->setText(QApplication::translate("rectify_window", "Original Images", Q_NULLPTR));
        action_view_rectified_images->setText(QApplication::translate("rectify_window", "Rectified Images", Q_NULLPTR));
        action_rectify_horizontal_check_line->setText(QApplication::translate("rectify_window", "Show Epipolar LIne", Q_NULLPTR));
        action_file_save_image_pair->setText(QApplication::translate("rectify_window", "Save Rectified Right Image", Q_NULLPTR));
        action_file_save_anaglyph->setText(QApplication::translate("rectify_window", "Create Anaglyph Image", Q_NULLPTR));
        action_rectify_all_rectification->setText(QApplication::translate("rectify_window", " Rectification", Q_NULLPTR));
        action_rectify_hit_and_match->setText(QApplication::translate("rectify_window", "Hit and Match", Q_NULLPTR));
        action_help_help->setText(QApplication::translate("rectify_window", "Help", Q_NULLPTR));
        mainToolBar->setWindowTitle(QApplication::translate("rectify_window", "toolBar", Q_NULLPTR));
        viewToolBar->setWindowTitle(QApplication::translate("rectify_window", "toolBar", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("rectify_window", "File", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("rectify_window", "View", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("rectify_window", "Help", Q_NULLPTR));
        menuControl->setTitle(QApplication::translate("rectify_window", "Control", Q_NULLPTR));
        menuZoom->setTitle(QApplication::translate("rectify_window", "Zoom", Q_NULLPTR));
        menuRectify->setTitle(QApplication::translate("rectify_window", "Rectify", Q_NULLPTR));
        menuRectifyAnalyze->setTitle(QApplication::translate("rectify_window", "Analyze", Q_NULLPTR));
        zoomFrameToolBar->setWindowTitle(QApplication::translate("rectify_window", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class rectify_window: public Ui_rectify_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECTIFY_WINDOW_H
