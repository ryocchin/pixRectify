/********************************************************************************
** Form generated from reading UI file 'sequence_select_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEQUENCE_SELECT_DIALOG_H
#define UI_SEQUENCE_SELECT_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_sequence_select_dialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *m_Group0Box;
    QGridLayout *gridLayout;
    QLabel *m_File0Label;
    QHBoxLayout *horizontalLayout;
    QComboBox *m_File0Combo;
    QPushButton *m_Brows0Button;
    QLabel *m_Template0Label;
    QLineEdit *m_Template0Edit;
    QLabel *m_Pattern0Label;
    QLineEdit *m_Pattern0Edit;
    QLabel *m_Frames0Label;
    QLineEdit *m_Frames0Edit;
    QGroupBox *m_Group1Box;
    QGridLayout *gridLayout_2;
    QLabel *m_File1Label;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *m_File1Combo;
    QPushButton *m_Brows1Button;
    QLabel *m_Template1Label;
    QLineEdit *m_Template1Edit;
    QLabel *m_Pattern1Label;
    QLineEdit *m_Pattern1Edit;
    QLabel *m_Frames1Label;
    QLineEdit *m_Frames1Edit;
    QSpacerItem *verticalSpacer;
    QLabel *_MessageLabel;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *m_OkButton;
    QPushButton *m_CancelButton;
    QPushButton *m_DummyButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_ClearHistoryButton;

    void setupUi(QDialog *sequence_select_dialog)
    {
        if (sequence_select_dialog->objectName().isEmpty())
            sequence_select_dialog->setObjectName(QStringLiteral("sequence_select_dialog"));
        sequence_select_dialog->resize(555, 303);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/ehagaki2_bagster.png"), QSize(), QIcon::Normal, QIcon::Off);
        sequence_select_dialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(sequence_select_dialog);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_Group0Box = new QGroupBox(sequence_select_dialog);
        m_Group0Box->setObjectName(QStringLiteral("m_Group0Box"));
        gridLayout = new QGridLayout(m_Group0Box);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(2, 2, 2, 2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        m_File0Label = new QLabel(m_Group0Box);
        m_File0Label->setObjectName(QStringLiteral("m_File0Label"));
        m_File0Label->setFrameShape(QFrame::NoFrame);

        gridLayout->addWidget(m_File0Label, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_File0Combo = new QComboBox(m_Group0Box);
        m_File0Combo->setObjectName(QStringLiteral("m_File0Combo"));

        horizontalLayout->addWidget(m_File0Combo);

        m_Brows0Button = new QPushButton(m_Group0Box);
        m_Brows0Button->setObjectName(QStringLiteral("m_Brows0Button"));
        m_Brows0Button->setMaximumSize(QSize(30, 16777215));
        m_Brows0Button->setFlat(false);

        horizontalLayout->addWidget(m_Brows0Button);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        m_Template0Label = new QLabel(m_Group0Box);
        m_Template0Label->setObjectName(QStringLiteral("m_Template0Label"));
        m_Template0Label->setFrameShape(QFrame::NoFrame);

        gridLayout->addWidget(m_Template0Label, 1, 0, 1, 1);

        m_Template0Edit = new QLineEdit(m_Group0Box);
        m_Template0Edit->setObjectName(QStringLiteral("m_Template0Edit"));

        gridLayout->addWidget(m_Template0Edit, 1, 1, 1, 1);

        m_Pattern0Label = new QLabel(m_Group0Box);
        m_Pattern0Label->setObjectName(QStringLiteral("m_Pattern0Label"));
        m_Pattern0Label->setFrameShape(QFrame::NoFrame);

        gridLayout->addWidget(m_Pattern0Label, 2, 0, 1, 1);

        m_Pattern0Edit = new QLineEdit(m_Group0Box);
        m_Pattern0Edit->setObjectName(QStringLiteral("m_Pattern0Edit"));
        m_Pattern0Edit->setReadOnly(true);

        gridLayout->addWidget(m_Pattern0Edit, 2, 1, 1, 1);

        m_Frames0Label = new QLabel(m_Group0Box);
        m_Frames0Label->setObjectName(QStringLiteral("m_Frames0Label"));
        m_Frames0Label->setFrameShape(QFrame::NoFrame);

        gridLayout->addWidget(m_Frames0Label, 3, 0, 1, 1);

        m_Frames0Edit = new QLineEdit(m_Group0Box);
        m_Frames0Edit->setObjectName(QStringLiteral("m_Frames0Edit"));
        m_Frames0Edit->setReadOnly(true);

        gridLayout->addWidget(m_Frames0Edit, 3, 1, 1, 1);


        verticalLayout->addWidget(m_Group0Box);

        m_Group1Box = new QGroupBox(sequence_select_dialog);
        m_Group1Box->setObjectName(QStringLiteral("m_Group1Box"));
        gridLayout_2 = new QGridLayout(m_Group1Box);
        gridLayout_2->setSpacing(2);
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        m_File1Label = new QLabel(m_Group1Box);
        m_File1Label->setObjectName(QStringLiteral("m_File1Label"));
        m_File1Label->setFrameShape(QFrame::NoFrame);

        gridLayout_2->addWidget(m_File1Label, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 2, -1, -1);
        m_File1Combo = new QComboBox(m_Group1Box);
        m_File1Combo->setObjectName(QStringLiteral("m_File1Combo"));

        horizontalLayout_2->addWidget(m_File1Combo);

        m_Brows1Button = new QPushButton(m_Group1Box);
        m_Brows1Button->setObjectName(QStringLiteral("m_Brows1Button"));
        m_Brows1Button->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_2->addWidget(m_Brows1Button);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 1, 1, 1);

        m_Template1Label = new QLabel(m_Group1Box);
        m_Template1Label->setObjectName(QStringLiteral("m_Template1Label"));
        m_Template1Label->setFrameShape(QFrame::NoFrame);

        gridLayout_2->addWidget(m_Template1Label, 1, 0, 1, 1);

        m_Template1Edit = new QLineEdit(m_Group1Box);
        m_Template1Edit->setObjectName(QStringLiteral("m_Template1Edit"));

        gridLayout_2->addWidget(m_Template1Edit, 1, 1, 1, 1);

        m_Pattern1Label = new QLabel(m_Group1Box);
        m_Pattern1Label->setObjectName(QStringLiteral("m_Pattern1Label"));
        m_Pattern1Label->setFrameShape(QFrame::NoFrame);

        gridLayout_2->addWidget(m_Pattern1Label, 2, 0, 1, 1);

        m_Pattern1Edit = new QLineEdit(m_Group1Box);
        m_Pattern1Edit->setObjectName(QStringLiteral("m_Pattern1Edit"));
        m_Pattern1Edit->setReadOnly(true);

        gridLayout_2->addWidget(m_Pattern1Edit, 2, 1, 1, 1);

        m_Frames1Label = new QLabel(m_Group1Box);
        m_Frames1Label->setObjectName(QStringLiteral("m_Frames1Label"));
        m_Frames1Label->setFrameShape(QFrame::NoFrame);

        gridLayout_2->addWidget(m_Frames1Label, 3, 0, 1, 1);

        m_Frames1Edit = new QLineEdit(m_Group1Box);
        m_Frames1Edit->setObjectName(QStringLiteral("m_Frames1Edit"));
        m_Frames1Edit->setReadOnly(true);

        gridLayout_2->addWidget(m_Frames1Edit, 3, 1, 1, 1);


        verticalLayout->addWidget(m_Group1Box);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        _MessageLabel = new QLabel(sequence_select_dialog);
        _MessageLabel->setObjectName(QStringLiteral("_MessageLabel"));
        _MessageLabel->setFrameShape(QFrame::StyledPanel);
        _MessageLabel->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(_MessageLabel);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        m_OkButton = new QPushButton(sequence_select_dialog);
        m_OkButton->setObjectName(QStringLiteral("m_OkButton"));

        horizontalLayout_3->addWidget(m_OkButton);

        m_CancelButton = new QPushButton(sequence_select_dialog);
        m_CancelButton->setObjectName(QStringLiteral("m_CancelButton"));

        horizontalLayout_3->addWidget(m_CancelButton);

        m_DummyButton = new QPushButton(sequence_select_dialog);
        m_DummyButton->setObjectName(QStringLiteral("m_DummyButton"));

        horizontalLayout_3->addWidget(m_DummyButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        m_ClearHistoryButton = new QPushButton(sequence_select_dialog);
        m_ClearHistoryButton->setObjectName(QStringLiteral("m_ClearHistoryButton"));

        horizontalLayout_3->addWidget(m_ClearHistoryButton);


        verticalLayout->addLayout(horizontalLayout_3);

        QWidget::setTabOrder(m_OkButton, m_CancelButton);
        QWidget::setTabOrder(m_CancelButton, m_ClearHistoryButton);
        QWidget::setTabOrder(m_ClearHistoryButton, m_DummyButton);

        retranslateUi(sequence_select_dialog);

        QMetaObject::connectSlotsByName(sequence_select_dialog);
    } // setupUi

    void retranslateUi(QDialog *sequence_select_dialog)
    {
        sequence_select_dialog->setWindowTitle(QApplication::translate("sequence_select_dialog", "Dialog", Q_NULLPTR));
        m_Group0Box->setTitle(QApplication::translate("sequence_select_dialog", "First Sequence", Q_NULLPTR));
        m_File0Label->setText(QApplication::translate("sequence_select_dialog", "File", Q_NULLPTR));
        m_Brows0Button->setText(QApplication::translate("sequence_select_dialog", "...", Q_NULLPTR));
        m_Template0Label->setText(QApplication::translate("sequence_select_dialog", "Template", Q_NULLPTR));
        m_Pattern0Label->setText(QApplication::translate("sequence_select_dialog", "Pattern", Q_NULLPTR));
        m_Frames0Label->setText(QApplication::translate("sequence_select_dialog", "Frame", Q_NULLPTR));
        m_Group1Box->setTitle(QApplication::translate("sequence_select_dialog", "Second Sequence", Q_NULLPTR));
        m_File1Label->setText(QApplication::translate("sequence_select_dialog", "File", Q_NULLPTR));
        m_Brows1Button->setText(QApplication::translate("sequence_select_dialog", "...", Q_NULLPTR));
        m_Template1Label->setText(QApplication::translate("sequence_select_dialog", "Template", Q_NULLPTR));
        m_Pattern1Label->setText(QApplication::translate("sequence_select_dialog", "Pattern", Q_NULLPTR));
        m_Frames1Label->setText(QApplication::translate("sequence_select_dialog", "Frame", Q_NULLPTR));
        _MessageLabel->setText(QApplication::translate("sequence_select_dialog", "Select Sequence", Q_NULLPTR));
        m_OkButton->setText(QApplication::translate("sequence_select_dialog", "OK", Q_NULLPTR));
        m_CancelButton->setText(QApplication::translate("sequence_select_dialog", "Cancel", Q_NULLPTR));
        m_DummyButton->setText(QApplication::translate("sequence_select_dialog", "Dummy", Q_NULLPTR));
        m_ClearHistoryButton->setText(QApplication::translate("sequence_select_dialog", "Clear History", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class sequence_select_dialog: public Ui_sequence_select_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEQUENCE_SELECT_DIALOG_H
