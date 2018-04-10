/********************************************************************************
** Form generated from reading UI file 'props_page_cv_rectify.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPS_PAGE_CV_RECTIFY_H
#define UI_PROPS_PAGE_CV_RECTIFY_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_props_page_cv_rectify
{
public:
    QGridLayout *gridLayout;
    QGroupBox *roration_group_box;
    QGridLayout *gridLayout_3;
    QLabel *radio_fundamental_method_label;
    QVBoxLayout *verticalLayout;
    QRadioButton *radio_fundamental_method_7_point;
    QRadioButton *radio_fundamental_method_8_point;
    QRadioButton *radio_fundamental_method_ransac;
    QRadioButton *radio_fundamental_method_lmeds;
    QLabel *max_distance_ransac_label;
    QLineEdit *max_distance_ransac_edit;
    QLabel *confidence_limit_ransac_label;
    QLineEdit *confidence_limit_ransac_edit;
    QLabel *disparity_threshold_label;
    QLineEdit *disparity_threshold_edit;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *files_group_box;
    QGridLayout *gridLayout_4;
    QLabel *image_file_suffix_label;
    QLineEdit *image_file_suffix_edit;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *props_page_cv_rectify)
    {
        if (props_page_cv_rectify->objectName().isEmpty())
            props_page_cv_rectify->setObjectName(QStringLiteral("props_page_cv_rectify"));
        props_page_cv_rectify->resize(235, 220);
        props_page_cv_rectify->setMaximumSize(QSize(320, 16777215));
        props_page_cv_rectify->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        gridLayout = new QGridLayout(props_page_cv_rectify);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(8);
        gridLayout->setVerticalSpacing(2);
        gridLayout->setContentsMargins(4, 4, 4, 4);
        roration_group_box = new QGroupBox(props_page_cv_rectify);
        roration_group_box->setObjectName(QStringLiteral("roration_group_box"));
        gridLayout_3 = new QGridLayout(roration_group_box);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(8);
        gridLayout_3->setVerticalSpacing(2);
        gridLayout_3->setContentsMargins(4, 4, 4, 4);
        radio_fundamental_method_label = new QLabel(roration_group_box);
        radio_fundamental_method_label->setObjectName(QStringLiteral("radio_fundamental_method_label"));
        radio_fundamental_method_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout_3->addWidget(radio_fundamental_method_label, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        radio_fundamental_method_7_point = new QRadioButton(roration_group_box);
        radio_fundamental_method_7_point->setObjectName(QStringLiteral("radio_fundamental_method_7_point"));

        verticalLayout->addWidget(radio_fundamental_method_7_point);

        radio_fundamental_method_8_point = new QRadioButton(roration_group_box);
        radio_fundamental_method_8_point->setObjectName(QStringLiteral("radio_fundamental_method_8_point"));

        verticalLayout->addWidget(radio_fundamental_method_8_point);

        radio_fundamental_method_ransac = new QRadioButton(roration_group_box);
        radio_fundamental_method_ransac->setObjectName(QStringLiteral("radio_fundamental_method_ransac"));

        verticalLayout->addWidget(radio_fundamental_method_ransac);

        radio_fundamental_method_lmeds = new QRadioButton(roration_group_box);
        radio_fundamental_method_lmeds->setObjectName(QStringLiteral("radio_fundamental_method_lmeds"));

        verticalLayout->addWidget(radio_fundamental_method_lmeds);


        gridLayout_3->addLayout(verticalLayout, 0, 2, 1, 1);

        max_distance_ransac_label = new QLabel(roration_group_box);
        max_distance_ransac_label->setObjectName(QStringLiteral("max_distance_ransac_label"));

        gridLayout_3->addWidget(max_distance_ransac_label, 1, 0, 1, 1);

        max_distance_ransac_edit = new QLineEdit(roration_group_box);
        max_distance_ransac_edit->setObjectName(QStringLiteral("max_distance_ransac_edit"));
        max_distance_ransac_edit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(max_distance_ransac_edit, 1, 2, 1, 1);

        confidence_limit_ransac_label = new QLabel(roration_group_box);
        confidence_limit_ransac_label->setObjectName(QStringLiteral("confidence_limit_ransac_label"));

        gridLayout_3->addWidget(confidence_limit_ransac_label, 2, 0, 1, 1);

        confidence_limit_ransac_edit = new QLineEdit(roration_group_box);
        confidence_limit_ransac_edit->setObjectName(QStringLiteral("confidence_limit_ransac_edit"));
        confidence_limit_ransac_edit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(confidence_limit_ransac_edit, 2, 2, 1, 1);

        disparity_threshold_label = new QLabel(roration_group_box);
        disparity_threshold_label->setObjectName(QStringLiteral("disparity_threshold_label"));

        gridLayout_3->addWidget(disparity_threshold_label, 3, 0, 1, 1);

        disparity_threshold_edit = new QLineEdit(roration_group_box);
        disparity_threshold_edit->setObjectName(QStringLiteral("disparity_threshold_edit"));
        disparity_threshold_edit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(disparity_threshold_edit, 3, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 1, 1, 1);


        gridLayout->addWidget(roration_group_box, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        files_group_box = new QGroupBox(props_page_cv_rectify);
        files_group_box->setObjectName(QStringLiteral("files_group_box"));
        gridLayout_4 = new QGridLayout(files_group_box);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(8);
        gridLayout_4->setVerticalSpacing(2);
        gridLayout_4->setContentsMargins(4, 4, 4, 4);
        image_file_suffix_label = new QLabel(files_group_box);
        image_file_suffix_label->setObjectName(QStringLiteral("image_file_suffix_label"));

        gridLayout_4->addWidget(image_file_suffix_label, 0, 0, 1, 1);

        image_file_suffix_edit = new QLineEdit(files_group_box);
        image_file_suffix_edit->setObjectName(QStringLiteral("image_file_suffix_edit"));
        image_file_suffix_edit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(image_file_suffix_edit, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_3, 0, 1, 1, 1);


        gridLayout->addWidget(files_group_box, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        roration_group_box->raise();
        files_group_box->raise();
        QWidget::setTabOrder(radio_fundamental_method_7_point, radio_fundamental_method_8_point);
        QWidget::setTabOrder(radio_fundamental_method_8_point, radio_fundamental_method_ransac);
        QWidget::setTabOrder(radio_fundamental_method_ransac, radio_fundamental_method_lmeds);
        QWidget::setTabOrder(radio_fundamental_method_lmeds, max_distance_ransac_edit);
        QWidget::setTabOrder(max_distance_ransac_edit, confidence_limit_ransac_edit);
        QWidget::setTabOrder(confidence_limit_ransac_edit, disparity_threshold_edit);

        retranslateUi(props_page_cv_rectify);

        QMetaObject::connectSlotsByName(props_page_cv_rectify);
    } // setupUi

    void retranslateUi(QWidget *props_page_cv_rectify)
    {
        props_page_cv_rectify->setWindowTitle(QApplication::translate("props_page_cv_rectify", "Form", Q_NULLPTR));
        roration_group_box->setTitle(QApplication::translate("props_page_cv_rectify", "Rotation Matrix", Q_NULLPTR));
        radio_fundamental_method_label->setText(QApplication::translate("props_page_cv_rectify", "Algorithms", Q_NULLPTR));
        radio_fundamental_method_7_point->setText(QApplication::translate("props_page_cv_rectify", "7-point", Q_NULLPTR));
        radio_fundamental_method_8_point->setText(QApplication::translate("props_page_cv_rectify", "8-point", Q_NULLPTR));
        radio_fundamental_method_ransac->setText(QApplication::translate("props_page_cv_rectify", "RANSAC", Q_NULLPTR));
        radio_fundamental_method_lmeds->setText(QApplication::translate("props_page_cv_rectify", "LMedS", Q_NULLPTR));
        max_distance_ransac_label->setText(QApplication::translate("props_page_cv_rectify", "Max Distance(RANSAC)", Q_NULLPTR));
        confidence_limit_ransac_label->setText(QApplication::translate("props_page_cv_rectify", "Confidence Limit(RANSAC)", Q_NULLPTR));
        disparity_threshold_label->setText(QApplication::translate("props_page_cv_rectify", "Disparity Threshold", Q_NULLPTR));
        files_group_box->setTitle(QApplication::translate("props_page_cv_rectify", "Files", Q_NULLPTR));
        image_file_suffix_label->setText(QApplication::translate("props_page_cv_rectify", "Image File Suffix", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class props_page_cv_rectify: public Ui_props_page_cv_rectify {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPS_PAGE_CV_RECTIFY_H
