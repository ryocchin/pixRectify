/********************************************************************************
** Form generated from reading UI file 'props_page_compare.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPS_PAGE_COMPARE_H
#define UI_PROPS_PAGE_COMPARE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_props_page_compare
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *WiperBoxFixedColorBox;
    QPushButton *WiperBoxFixedColorButton;
    QSpacerItem *horizontalSpacer_2;
    QLabel *line_fixed_color_label;
    QHBoxLayout *horizontalLayout_2;
    QLabel *WiperBoxColorBox;
    QPushButton *WiperBoxColorButton;
    QLineEdit *CompareBoxRadiusEdit;
    QSpacerItem *verticalSpacer;
    QCheckBox *DrawWipeBoxDrawCheck;
    QLabel *line_color_label;
    QLabel *scope_radius_label;
    QLabel *draw_line_label;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *props_page_compare)
    {
        if (props_page_compare->objectName().isEmpty())
            props_page_compare->setObjectName(QStringLiteral("props_page_compare"));
        props_page_compare->resize(213, 106);
        QFont font;
        font.setFamily(QString::fromUtf8("\357\274\255\357\274\263 \357\274\260\343\202\264\343\202\267\343\203\203\343\202\257"));
        font.setPointSize(9);
        props_page_compare->setFont(font);
        gridLayout = new QGridLayout(props_page_compare);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(8);
        gridLayout->setVerticalSpacing(2);
        gridLayout->setContentsMargins(4, 4, 4, 4);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(1);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        WiperBoxFixedColorBox = new QLabel(props_page_compare);
        WiperBoxFixedColorBox->setObjectName(QStringLiteral("WiperBoxFixedColorBox"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WiperBoxFixedColorBox->sizePolicy().hasHeightForWidth());
        WiperBoxFixedColorBox->setSizePolicy(sizePolicy);
        WiperBoxFixedColorBox->setMinimumSize(QSize(10, 0));
        WiperBoxFixedColorBox->setMaximumSize(QSize(16777215, 16777215));
        WiperBoxFixedColorBox->setFrameShape(QFrame::Panel);
        WiperBoxFixedColorBox->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(WiperBoxFixedColorBox);

        WiperBoxFixedColorButton = new QPushButton(props_page_compare);
        WiperBoxFixedColorButton->setObjectName(QStringLiteral("WiperBoxFixedColorButton"));
        WiperBoxFixedColorButton->setMinimumSize(QSize(20, 0));
        WiperBoxFixedColorButton->setMaximumSize(QSize(25, 16777215));

        horizontalLayout_3->addWidget(WiperBoxFixedColorButton);


        gridLayout->addLayout(horizontalLayout_3, 2, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 5, 1, 1);

        line_fixed_color_label = new QLabel(props_page_compare);
        line_fixed_color_label->setObjectName(QStringLiteral("line_fixed_color_label"));
        line_fixed_color_label->setFrameShape(QFrame::NoFrame);
        line_fixed_color_label->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_fixed_color_label, 2, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        WiperBoxColorBox = new QLabel(props_page_compare);
        WiperBoxColorBox->setObjectName(QStringLiteral("WiperBoxColorBox"));
        sizePolicy.setHeightForWidth(WiperBoxColorBox->sizePolicy().hasHeightForWidth());
        WiperBoxColorBox->setSizePolicy(sizePolicy);
        WiperBoxColorBox->setMinimumSize(QSize(10, 0));
        WiperBoxColorBox->setMaximumSize(QSize(16777215, 16777215));
        WiperBoxColorBox->setFrameShape(QFrame::Panel);
        WiperBoxColorBox->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(WiperBoxColorBox);

        WiperBoxColorButton = new QPushButton(props_page_compare);
        WiperBoxColorButton->setObjectName(QStringLiteral("WiperBoxColorButton"));
        WiperBoxColorButton->setMinimumSize(QSize(20, 0));
        WiperBoxColorButton->setMaximumSize(QSize(25, 16777215));

        horizontalLayout_2->addWidget(WiperBoxColorButton);


        gridLayout->addLayout(horizontalLayout_2, 1, 3, 1, 1);

        CompareBoxRadiusEdit = new QLineEdit(props_page_compare);
        CompareBoxRadiusEdit->setObjectName(QStringLiteral("CompareBoxRadiusEdit"));
        CompareBoxRadiusEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(CompareBoxRadiusEdit, 3, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 1, 1, 1);

        DrawWipeBoxDrawCheck = new QCheckBox(props_page_compare);
        DrawWipeBoxDrawCheck->setObjectName(QStringLiteral("DrawWipeBoxDrawCheck"));

        gridLayout->addWidget(DrawWipeBoxDrawCheck, 0, 3, 1, 1);

        line_color_label = new QLabel(props_page_compare);
        line_color_label->setObjectName(QStringLiteral("line_color_label"));
        line_color_label->setFrameShape(QFrame::NoFrame);
        line_color_label->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_color_label, 1, 0, 1, 1);

        scope_radius_label = new QLabel(props_page_compare);
        scope_radius_label->setObjectName(QStringLiteral("scope_radius_label"));
        scope_radius_label->setFrameShape(QFrame::NoFrame);
        scope_radius_label->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(scope_radius_label, 3, 0, 1, 2);

        draw_line_label = new QLabel(props_page_compare);
        draw_line_label->setObjectName(QStringLiteral("draw_line_label"));
        draw_line_label->setFrameShape(QFrame::NoFrame);
        draw_line_label->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(draw_line_label, 0, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

#ifndef QT_NO_SHORTCUT
        scope_radius_label->setBuddy(CompareBoxRadiusEdit);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(DrawWipeBoxDrawCheck, CompareBoxRadiusEdit);

        retranslateUi(props_page_compare);

        QMetaObject::connectSlotsByName(props_page_compare);
    } // setupUi

    void retranslateUi(QWidget *props_page_compare)
    {
        props_page_compare->setWindowTitle(QApplication::translate("props_page_compare", "Form", Q_NULLPTR));
        WiperBoxFixedColorBox->setText(QString());
        WiperBoxFixedColorButton->setText(QApplication::translate("props_page_compare", "....", Q_NULLPTR));
        line_fixed_color_label->setText(QApplication::translate("props_page_compare", "\347\267\232\343\201\256\350\211\262\357\274\210\345\233\272\345\256\232\357\274\211", Q_NULLPTR));
        WiperBoxColorBox->setText(QString());
        WiperBoxColorButton->setText(QApplication::translate("props_page_compare", "....", Q_NULLPTR));
        DrawWipeBoxDrawCheck->setText(QApplication::translate("props_page_compare", "\347\267\232\343\202\222\350\241\250\347\244\272", Q_NULLPTR));
        line_color_label->setText(QApplication::translate("props_page_compare", "\347\267\232\343\201\256\350\211\262", Q_NULLPTR));
        scope_radius_label->setText(QApplication::translate("props_page_compare", "\343\202\271\343\202\263\343\203\274\343\203\227\343\201\256\345\215\212\345\276\204(\347\224\273\351\235\242)", Q_NULLPTR));
        draw_line_label->setText(QApplication::translate("props_page_compare", "\343\203\257\343\202\244\343\203\221\343\203\274/\343\202\271\343\202\263\343\203\274\343\203\227", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class props_page_compare: public Ui_props_page_compare {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPS_PAGE_COMPARE_H
