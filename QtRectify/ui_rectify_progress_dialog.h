/********************************************************************************
** Form generated from reading UI file 'rectify_progress_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECTIFY_PROGRESS_DIALOG_H
#define UI_RECTIFY_PROGRESS_DIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_rectify_progress_dialog
{
public:
    QVBoxLayout *verticalLayout;
    QProgressBar *progress_bar;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *loading_frame_label;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *progress_stop_button;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *rectify_progress_dialog)
    {
        if (rectify_progress_dialog->objectName().isEmpty())
            rectify_progress_dialog->setObjectName(QStringLiteral("rectify_progress_dialog"));
        rectify_progress_dialog->resize(387, 133);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/rectify1.png"), QSize(), QIcon::Normal, QIcon::Off);
        rectify_progress_dialog->setWindowIcon(icon);
        rectify_progress_dialog->setLocale(QLocale(QLocale::English, QLocale::Canada));
        verticalLayout = new QVBoxLayout(rectify_progress_dialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        progress_bar = new QProgressBar(rectify_progress_dialog);
        progress_bar->setObjectName(QStringLiteral("progress_bar"));
        progress_bar->setMinimumSize(QSize(0, 21));
        progress_bar->setMaximumSize(QSize(16777215, 21));
        progress_bar->setValue(24);
        progress_bar->setTextVisible(false);

        verticalLayout->addWidget(progress_bar);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        loading_frame_label = new QLabel(rectify_progress_dialog);
        loading_frame_label->setObjectName(QStringLiteral("loading_frame_label"));
        loading_frame_label->setMinimumSize(QSize(160, 0));
        loading_frame_label->setFrameShape(QFrame::Panel);
        loading_frame_label->setFrameShadow(QFrame::Sunken);
        loading_frame_label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(loading_frame_label);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        progress_stop_button = new QPushButton(rectify_progress_dialog);
        progress_stop_button->setObjectName(QStringLiteral("progress_stop_button"));
        progress_stop_button->setMinimumSize(QSize(61, 0));

        horizontalLayout->addWidget(progress_stop_button);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(rectify_progress_dialog);

        QMetaObject::connectSlotsByName(rectify_progress_dialog);
    } // setupUi

    void retranslateUi(QDialog *rectify_progress_dialog)
    {
        rectify_progress_dialog->setWindowTitle(QApplication::translate("rectify_progress_dialog", "Matching Points....", Q_NULLPTR));
        loading_frame_label->setText(QApplication::translate("rectify_progress_dialog", "Loading", Q_NULLPTR));
        progress_stop_button->setText(QApplication::translate("rectify_progress_dialog", "Stop", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class rectify_progress_dialog: public Ui_rectify_progress_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECTIFY_PROGRESS_DIALOG_H
