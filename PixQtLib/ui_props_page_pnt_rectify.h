/********************************************************************************
** Form generated from reading UI file 'props_page_pnt_rectify.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPS_PAGE_PNT_RECTIFY_H
#define UI_PROPS_PAGE_PNT_RECTIFY_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_props_page_pnt_rectify
{
public:
    QGridLayout *gridLayout;
    QGroupBox *control_points_group_box;
    QGridLayout *gridLayout_2;
    QLabel *rectify_point_number_label;
    QSpacerItem *horizontalSpacer_1;
    QLineEdit *rectify_point_number_edit;
    QLabel *rectify_snap_feature_point_label;
    QCheckBox *rectify_snap_feature_point_check;
    QLabel *rectify_feature_search_range_label;
    QLineEdit *rectify_feature_search_range_edit;
    QGroupBox *matching_group_box;
    QGridLayout *gridLayout_3;
    QLabel *rectify_use_pyramid_label;
    QCheckBox *rectify_use_pyramid_check;
    QLabel *rectify_soukan_mado_radius_label;
    QLineEdit *rectify_soukan_mado_radius_edit;
    QLabel *rectify_min_stdev_label;
    QLineEdit *rectify_min_stdev_edit;
    QLabel *rectify_gray_scale_label;
    QCheckBox *rectify_gray_scale_check;
    QLabel *rectify_soukan_high_bnd_label;
    QLineEdit *rectify_soukan_high_bnd_edit;
    QLabel *rectify_max_hor_disparity_label;
    QLineEdit *rectify_max_hor_disparity_edit;
    QLabel *rectify_max_ver_disparity_label;
    QLineEdit *rectify_max_ver_disparity_edit;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *props_page_pnt_rectify)
    {
        if (props_page_pnt_rectify->objectName().isEmpty())
            props_page_pnt_rectify->setObjectName(QStringLiteral("props_page_pnt_rectify"));
        props_page_pnt_rectify->resize(266, 273);
        props_page_pnt_rectify->setMaximumSize(QSize(320, 16777215));
        props_page_pnt_rectify->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        gridLayout = new QGridLayout(props_page_pnt_rectify);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(8);
        gridLayout->setContentsMargins(4, 4, 4, 4);
        control_points_group_box = new QGroupBox(props_page_pnt_rectify);
        control_points_group_box->setObjectName(QStringLiteral("control_points_group_box"));
        control_points_group_box->setFlat(false);
        gridLayout_2 = new QGridLayout(control_points_group_box);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(8);
        gridLayout_2->setVerticalSpacing(2);
        gridLayout_2->setContentsMargins(4, 4, 4, 4);
        rectify_point_number_label = new QLabel(control_points_group_box);
        rectify_point_number_label->setObjectName(QStringLiteral("rectify_point_number_label"));
        rectify_point_number_label->setFrameShape(QFrame::NoFrame);
        rectify_point_number_label->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(rectify_point_number_label, 0, 0, 1, 1);

        horizontalSpacer_1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_1, 0, 1, 1, 1);

        rectify_point_number_edit = new QLineEdit(control_points_group_box);
        rectify_point_number_edit->setObjectName(QStringLiteral("rectify_point_number_edit"));
        rectify_point_number_edit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(rectify_point_number_edit, 0, 2, 1, 1);

        rectify_snap_feature_point_label = new QLabel(control_points_group_box);
        rectify_snap_feature_point_label->setObjectName(QStringLiteral("rectify_snap_feature_point_label"));
        rectify_snap_feature_point_label->setFrameShape(QFrame::NoFrame);
        rectify_snap_feature_point_label->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(rectify_snap_feature_point_label, 1, 0, 1, 1);

        rectify_snap_feature_point_check = new QCheckBox(control_points_group_box);
        rectify_snap_feature_point_check->setObjectName(QStringLiteral("rectify_snap_feature_point_check"));

        gridLayout_2->addWidget(rectify_snap_feature_point_check, 1, 2, 1, 1);

        rectify_feature_search_range_label = new QLabel(control_points_group_box);
        rectify_feature_search_range_label->setObjectName(QStringLiteral("rectify_feature_search_range_label"));
        rectify_feature_search_range_label->setFrameShape(QFrame::NoFrame);
        rectify_feature_search_range_label->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(rectify_feature_search_range_label, 2, 0, 1, 1);

        rectify_feature_search_range_edit = new QLineEdit(control_points_group_box);
        rectify_feature_search_range_edit->setObjectName(QStringLiteral("rectify_feature_search_range_edit"));
        rectify_feature_search_range_edit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(rectify_feature_search_range_edit, 2, 2, 1, 1);


        gridLayout->addWidget(control_points_group_box, 0, 0, 1, 1);

        matching_group_box = new QGroupBox(props_page_pnt_rectify);
        matching_group_box->setObjectName(QStringLiteral("matching_group_box"));
        matching_group_box->setFlat(false);
        gridLayout_3 = new QGridLayout(matching_group_box);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(8);
        gridLayout_3->setVerticalSpacing(2);
        gridLayout_3->setContentsMargins(4, 4, 4, 4);
        rectify_use_pyramid_label = new QLabel(matching_group_box);
        rectify_use_pyramid_label->setObjectName(QStringLiteral("rectify_use_pyramid_label"));
        rectify_use_pyramid_label->setFrameShape(QFrame::NoFrame);
        rectify_use_pyramid_label->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(rectify_use_pyramid_label, 0, 0, 1, 1);

        rectify_use_pyramid_check = new QCheckBox(matching_group_box);
        rectify_use_pyramid_check->setObjectName(QStringLiteral("rectify_use_pyramid_check"));

        gridLayout_3->addWidget(rectify_use_pyramid_check, 0, 2, 1, 1);

        rectify_soukan_mado_radius_label = new QLabel(matching_group_box);
        rectify_soukan_mado_radius_label->setObjectName(QStringLiteral("rectify_soukan_mado_radius_label"));
        rectify_soukan_mado_radius_label->setFrameShape(QFrame::NoFrame);
        rectify_soukan_mado_radius_label->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(rectify_soukan_mado_radius_label, 1, 0, 1, 1);

        rectify_soukan_mado_radius_edit = new QLineEdit(matching_group_box);
        rectify_soukan_mado_radius_edit->setObjectName(QStringLiteral("rectify_soukan_mado_radius_edit"));
        rectify_soukan_mado_radius_edit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(rectify_soukan_mado_radius_edit, 1, 2, 1, 1);

        rectify_min_stdev_label = new QLabel(matching_group_box);
        rectify_min_stdev_label->setObjectName(QStringLiteral("rectify_min_stdev_label"));
        rectify_min_stdev_label->setFrameShape(QFrame::NoFrame);
        rectify_min_stdev_label->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(rectify_min_stdev_label, 2, 0, 1, 1);

        rectify_min_stdev_edit = new QLineEdit(matching_group_box);
        rectify_min_stdev_edit->setObjectName(QStringLiteral("rectify_min_stdev_edit"));
        rectify_min_stdev_edit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(rectify_min_stdev_edit, 2, 2, 1, 1);

        rectify_gray_scale_label = new QLabel(matching_group_box);
        rectify_gray_scale_label->setObjectName(QStringLiteral("rectify_gray_scale_label"));
        rectify_gray_scale_label->setFrameShape(QFrame::NoFrame);
        rectify_gray_scale_label->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(rectify_gray_scale_label, 3, 0, 1, 1);

        rectify_gray_scale_check = new QCheckBox(matching_group_box);
        rectify_gray_scale_check->setObjectName(QStringLiteral("rectify_gray_scale_check"));

        gridLayout_3->addWidget(rectify_gray_scale_check, 3, 2, 1, 1);

        rectify_soukan_high_bnd_label = new QLabel(matching_group_box);
        rectify_soukan_high_bnd_label->setObjectName(QStringLiteral("rectify_soukan_high_bnd_label"));
        rectify_soukan_high_bnd_label->setFrameShape(QFrame::NoFrame);
        rectify_soukan_high_bnd_label->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(rectify_soukan_high_bnd_label, 4, 0, 1, 1);

        rectify_soukan_high_bnd_edit = new QLineEdit(matching_group_box);
        rectify_soukan_high_bnd_edit->setObjectName(QStringLiteral("rectify_soukan_high_bnd_edit"));
        rectify_soukan_high_bnd_edit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(rectify_soukan_high_bnd_edit, 4, 2, 1, 1);

        rectify_max_hor_disparity_label = new QLabel(matching_group_box);
        rectify_max_hor_disparity_label->setObjectName(QStringLiteral("rectify_max_hor_disparity_label"));
        rectify_max_hor_disparity_label->setFrameShape(QFrame::NoFrame);
        rectify_max_hor_disparity_label->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(rectify_max_hor_disparity_label, 5, 0, 1, 1);

        rectify_max_hor_disparity_edit = new QLineEdit(matching_group_box);
        rectify_max_hor_disparity_edit->setObjectName(QStringLiteral("rectify_max_hor_disparity_edit"));
        rectify_max_hor_disparity_edit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(rectify_max_hor_disparity_edit, 5, 2, 1, 1);

        rectify_max_ver_disparity_label = new QLabel(matching_group_box);
        rectify_max_ver_disparity_label->setObjectName(QStringLiteral("rectify_max_ver_disparity_label"));
        rectify_max_ver_disparity_label->setFrameShape(QFrame::NoFrame);
        rectify_max_ver_disparity_label->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(rectify_max_ver_disparity_label, 6, 0, 1, 1);

        rectify_max_ver_disparity_edit = new QLineEdit(matching_group_box);
        rectify_max_ver_disparity_edit->setObjectName(QStringLiteral("rectify_max_ver_disparity_edit"));
        rectify_max_ver_disparity_edit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(rectify_max_ver_disparity_edit, 6, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 1, 1, 1, 1);


        gridLayout->addWidget(matching_group_box, 1, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        matching_group_box->raise();
        control_points_group_box->raise();
#ifndef QT_NO_SHORTCUT
        rectify_point_number_label->setBuddy(rectify_point_number_edit);
        rectify_feature_search_range_label->setBuddy(rectify_point_number_edit);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(rectify_point_number_edit, rectify_soukan_mado_radius_edit);
        QWidget::setTabOrder(rectify_soukan_mado_radius_edit, rectify_min_stdev_edit);
        QWidget::setTabOrder(rectify_min_stdev_edit, rectify_gray_scale_check);
        QWidget::setTabOrder(rectify_gray_scale_check, rectify_soukan_high_bnd_edit);
        QWidget::setTabOrder(rectify_soukan_high_bnd_edit, rectify_max_hor_disparity_edit);
        QWidget::setTabOrder(rectify_max_hor_disparity_edit, rectify_max_ver_disparity_edit);

        retranslateUi(props_page_pnt_rectify);

        QMetaObject::connectSlotsByName(props_page_pnt_rectify);
    } // setupUi

    void retranslateUi(QWidget *props_page_pnt_rectify)
    {
        props_page_pnt_rectify->setWindowTitle(QApplication::translate("props_page_pnt_rectify", "Form", Q_NULLPTR));
        control_points_group_box->setTitle(QApplication::translate("props_page_pnt_rectify", "Control Points", Q_NULLPTR));
        rectify_point_number_label->setText(QApplication::translate("props_page_pnt_rectify", "Ideal Points Number", Q_NULLPTR));
        rectify_snap_feature_point_label->setText(QApplication::translate("props_page_pnt_rectify", "Before Matching...", Q_NULLPTR));
        rectify_snap_feature_point_check->setText(QApplication::translate("props_page_pnt_rectify", "Snap to Feature Point", Q_NULLPTR));
        rectify_feature_search_range_label->setText(QApplication::translate("props_page_pnt_rectify", "Search Range", Q_NULLPTR));
        rectify_feature_search_range_edit->setText(QString());
        matching_group_box->setTitle(QApplication::translate("props_page_pnt_rectify", "Matching Conditions", Q_NULLPTR));
        rectify_use_pyramid_label->setText(QApplication::translate("props_page_pnt_rectify", "Use Image Pyramid", Q_NULLPTR));
        rectify_use_pyramid_check->setText(QApplication::translate("props_page_pnt_rectify", "Yes", Q_NULLPTR));
        rectify_soukan_mado_radius_label->setText(QApplication::translate("props_page_pnt_rectify", "Corr. Window Radius", Q_NULLPTR));
        rectify_min_stdev_label->setText(QApplication::translate("props_page_pnt_rectify", "Min Standard Deviation", Q_NULLPTR));
        rectify_gray_scale_label->setText(QApplication::translate("props_page_pnt_rectify", "Use Gray/Colors", Q_NULLPTR));
        rectify_gray_scale_check->setText(QApplication::translate("props_page_pnt_rectify", "Yes", Q_NULLPTR));
        rectify_soukan_high_bnd_label->setText(QApplication::translate("props_page_pnt_rectify", "Correlation Threshold", Q_NULLPTR));
        rectify_max_hor_disparity_label->setText(QApplication::translate("props_page_pnt_rectify", "Max Disparity: Horizontal", Q_NULLPTR));
        rectify_max_ver_disparity_label->setText(QApplication::translate("props_page_pnt_rectify", "Max Disparity: Vertical", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class props_page_pnt_rectify: public Ui_props_page_pnt_rectify {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPS_PAGE_PNT_RECTIFY_H
