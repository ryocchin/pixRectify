/********************************************************************************
** Form generated from reading UI file 'props_page_image.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPS_PAGE_IMAGE_H
#define UI_PROPS_PAGE_IMAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_props_page_image
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *nearest_radio;
    QRadioButton *bilinear_radio;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QLabel *image_stat_interval_label;
    QLineEdit *image_stat_interval_edit;
    QSpacerItem *verticalSpacer;
    QLabel *resample_label;
    QSpacerItem *horizontalSpacer_3;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *props_page_image)
    {
        if (props_page_image->objectName().isEmpty())
            props_page_image->setObjectName(QStringLiteral("props_page_image"));
        props_page_image->resize(257, 55);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(9);
        font.setBold(false);
        font.setWeight(50);
        props_page_image->setFont(font);
        gridLayout = new QGridLayout(props_page_image);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(4);
        gridLayout->setVerticalSpacing(2);
        gridLayout->setContentsMargins(4, 4, 4, 4);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        nearest_radio = new QRadioButton(props_page_image);
        buttonGroup = new QButtonGroup(props_page_image);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(nearest_radio);
        nearest_radio->setObjectName(QStringLiteral("nearest_radio"));

        horizontalLayout->addWidget(nearest_radio);

        bilinear_radio = new QRadioButton(props_page_image);
        buttonGroup->addButton(bilinear_radio);
        bilinear_radio->setObjectName(QStringLiteral("bilinear_radio"));

        horizontalLayout->addWidget(bilinear_radio);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 2, 1);

        image_stat_interval_label = new QLabel(props_page_image);
        image_stat_interval_label->setObjectName(QStringLiteral("image_stat_interval_label"));
        image_stat_interval_label->setFrameShape(QFrame::NoFrame);

        gridLayout->addWidget(image_stat_interval_label, 1, 0, 1, 1);

        image_stat_interval_edit = new QLineEdit(props_page_image);
        image_stat_interval_edit->setObjectName(QStringLiteral("image_stat_interval_edit"));
        image_stat_interval_edit->setMinimumSize(QSize(80, 0));
        image_stat_interval_edit->setMaximumSize(QSize(16777215, 16777215));
        image_stat_interval_edit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(image_stat_interval_edit, 1, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        resample_label = new QLabel(props_page_image);
        resample_label->setObjectName(QStringLiteral("resample_label"));
        resample_label->setFrameShape(QFrame::NoFrame);

        gridLayout->addWidget(resample_label, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 1, 1, 1);


        retranslateUi(props_page_image);

        QMetaObject::connectSlotsByName(props_page_image);
    } // setupUi

    void retranslateUi(QWidget *props_page_image)
    {
        props_page_image->setWindowTitle(QApplication::translate("props_page_image", "Form", Q_NULLPTR));
        nearest_radio->setText(QApplication::translate("props_page_image", "\346\234\200\350\277\221\351\232\243\346\263\225", Q_NULLPTR));
        bilinear_radio->setText(QApplication::translate("props_page_image", "\345\217\214\347\267\232\345\275\242\350\243\234\351\226\223", Q_NULLPTR));
        image_stat_interval_label->setText(QApplication::translate("props_page_image", "\343\202\265\343\203\263\343\203\227\343\203\252\343\203\263\343\202\260\351\226\223\351\232\224", Q_NULLPTR));
        resample_label->setText(QApplication::translate("props_page_image", "Resampling", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class props_page_image: public Ui_props_page_image {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPS_PAGE_IMAGE_H
