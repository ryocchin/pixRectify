/********************************************************************************
** Form generated from reading UI file 'props_page_system.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPS_PAGE_SYSTEM_H
#define UI_PROPS_PAGE_SYSTEM_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_props_page_system
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QRadioButton *language_english_radio;
    QRadioButton *language_japanese_radio;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *fullscreen_side_left_radio;
    QRadioButton *fullscreen_side_right_radio;
    QSpacerItem *horizontalSpacer_4;
    QLabel *fullscreen_side_label;
    QSpacerItem *horizontalSpacer;
    QLabel *language_label;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QButtonGroup *language_button_group;
    QButtonGroup *fullscreen_side_button_group;

    void setupUi(QWidget *props_page_system)
    {
        if (props_page_system->objectName().isEmpty())
            props_page_system->setObjectName(QStringLiteral("props_page_system"));
        props_page_system->resize(212, 79);
        gridLayout = new QGridLayout(props_page_system);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(2);
        gridLayout->setContentsMargins(4, 4, 4, 4);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        language_english_radio = new QRadioButton(props_page_system);
        language_button_group = new QButtonGroup(props_page_system);
        language_button_group->setObjectName(QStringLiteral("language_button_group"));
        language_button_group->addButton(language_english_radio);
        language_english_radio->setObjectName(QStringLiteral("language_english_radio"));

        verticalLayout->addWidget(language_english_radio);

        language_japanese_radio = new QRadioButton(props_page_system);
        language_button_group->addButton(language_japanese_radio);
        language_japanese_radio->setObjectName(QStringLiteral("language_japanese_radio"));

        verticalLayout->addWidget(language_japanese_radio);


        gridLayout->addLayout(verticalLayout, 0, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        fullscreen_side_left_radio = new QRadioButton(props_page_system);
        fullscreen_side_button_group = new QButtonGroup(props_page_system);
        fullscreen_side_button_group->setObjectName(QStringLiteral("fullscreen_side_button_group"));
        fullscreen_side_button_group->addButton(fullscreen_side_left_radio);
        fullscreen_side_left_radio->setObjectName(QStringLiteral("fullscreen_side_left_radio"));

        horizontalLayout_2->addWidget(fullscreen_side_left_radio);

        fullscreen_side_right_radio = new QRadioButton(props_page_system);
        fullscreen_side_button_group->addButton(fullscreen_side_right_radio);
        fullscreen_side_right_radio->setObjectName(QStringLiteral("fullscreen_side_right_radio"));

        horizontalLayout_2->addWidget(fullscreen_side_right_radio);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_2, 1, 2, 1, 1);

        fullscreen_side_label = new QLabel(props_page_system);
        fullscreen_side_label->setObjectName(QStringLiteral("fullscreen_side_label"));
        fullscreen_side_label->setFrameShape(QFrame::NoFrame);
        fullscreen_side_label->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(fullscreen_side_label, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 3, 1, 1);

        language_label = new QLabel(props_page_system);
        language_label->setObjectName(QStringLiteral("language_label"));
        language_label->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        language_label->setFrameShape(QFrame::NoFrame);
        language_label->setFrameShadow(QFrame::Raised);
        language_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout->addWidget(language_label, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 1, 1, 1);


        retranslateUi(props_page_system);

        QMetaObject::connectSlotsByName(props_page_system);
    } // setupUi

    void retranslateUi(QWidget *props_page_system)
    {
        props_page_system->setWindowTitle(QApplication::translate("props_page_system", "Form", Q_NULLPTR));
        language_english_radio->setText(QApplication::translate("props_page_system", "English", Q_NULLPTR));
        language_japanese_radio->setText(QApplication::translate("props_page_system", "Japanese", Q_NULLPTR));
        fullscreen_side_left_radio->setText(QApplication::translate("props_page_system", "Left", Q_NULLPTR));
        fullscreen_side_right_radio->setText(QApplication::translate("props_page_system", "Right", Q_NULLPTR));
        fullscreen_side_label->setText(QApplication::translate("props_page_system", "Monitor for Fullscreen", Q_NULLPTR));
        language_label->setText(QApplication::translate("props_page_system", "Language", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class props_page_system: public Ui_props_page_system {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPS_PAGE_SYSTEM_H
