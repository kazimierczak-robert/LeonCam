/********************************************************************************
** Form generated from reading UI file 'CameraPreview.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAPREVIEW_H
#define UI_CAMERAPREVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraPreview
{
public:
    QLabel *LCameraDetails;
    QPushButton *PBRecognize;
    QPushButton *PBEdit;
    QPushButton *PBSnapshot;
    QPushButton *PBHome;
    QPushButton *PBUp;
    QPushButton *PBRight;
    QPushButton *PBDown;
    QPushButton *PBLeft;
    QPushButton *PBSavePreset;
    QComboBox *CBPresets;
    QPushButton *PBBack;
    QPushButton *PBCameraOnOff;
    QPushButton *PBGoToPreset;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *CameraPreview)
    {
        if (CameraPreview->objectName().isEmpty())
            CameraPreview->setObjectName(QStringLiteral("CameraPreview"));
        CameraPreview->resize(800, 600);
        CameraPreview->setMinimumSize(QSize(800, 600));
        CameraPreview->setMaximumSize(QSize(800, 600));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/Images/logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        CameraPreview->setWindowIcon(icon);
        CameraPreview->setStyleSheet(QLatin1String("#CameraPreview\n"
"{\n"
"	background-image: url(:/Resources/Images/backgroundMain.png);\n"
"}"));
        LCameraDetails = new QLabel(CameraPreview);
        LCameraDetails->setObjectName(QStringLiteral("LCameraDetails"));
        LCameraDetails->setGeometry(QRect(130, 450, 261, 21));
        LCameraDetails->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: transparent;\n"
"font-weight:600;"));
        PBRecognize = new QPushButton(CameraPreview);
        PBRecognize->setObjectName(QStringLiteral("PBRecognize"));
        PBRecognize->setGeometry(QRect(530, 490, 40, 40));
        PBRecognize->setStyleSheet(QLatin1String("QPushButton{background-image: url(:/Resources/Images/recognizeOn.png); border: none; margin: 0px; padding: 0px;} \n"
"QPushButton:hover{background-image: url(:/Resources/Images/recognizeOnHover.png);}\n"
"		"));
        PBRecognize->setFlat(true);
        PBEdit = new QPushButton(CameraPreview);
        PBEdit->setObjectName(QStringLiteral("PBEdit"));
        PBEdit->setGeometry(QRect(580, 490, 40, 40));
        PBEdit->setStyleSheet(QLatin1String("QPushButton{background-image: url(:/Resources/Images/edit.png);border: none; margin: 0px; padding: 0px;} \n"
"QPushButton:hover{background-image: url(:/Resources/Images/editHover.png);}\n"
"		"));
        PBEdit->setFlat(true);
        PBSnapshot = new QPushButton(CameraPreview);
        PBSnapshot->setObjectName(QStringLiteral("PBSnapshot"));
        PBSnapshot->setGeometry(QRect(480, 490, 40, 40));
        PBSnapshot->setStyleSheet(QLatin1String("#PBSnapshot{\n"
"background-image: url(:/Resources/Images/snapshot.png);\n"
"border: none;\n"
"margin: 0px;\n"
"padding: 0px;\n"
"}\n"
"\n"
"#PBSnapshot:hover{\n"
"background-image: url(:/Resources/Images/snapshotHover.png);\n"
"}"));
        PBSnapshot->setFlat(true);
        PBHome = new QPushButton(CameraPreview);
        PBHome->setObjectName(QStringLiteral("PBHome"));
        PBHome->setGeometry(QRect(653, 490, 40, 40));
        PBHome->setStyleSheet(QLatin1String("#PBHome{\n"
"background-image: url(:/Resources/Images/home.png);\n"
"border: none;\n"
"margin: 0px;\n"
"padding: 0px;\n"
"}\n"
"\n"
"#PBHome:hover{\n"
"background-image: url(:/Resources/Images/homeHover.png);\n"
"}"));
        PBHome->setFlat(true);
        PBUp = new QPushButton(CameraPreview);
        PBUp->setObjectName(QStringLiteral("PBUp"));
        PBUp->setGeometry(QRect(658, 467, 30, 23));
        PBUp->setStyleSheet(QLatin1String("#PBUp {\n"
"background-image: url(:/Resources/Images/up.png);\n"
"border: none;\n"
"margin: 0px;\n"
"padding: 0px;}\n"
"#PBUp:hover{\n"
"background-image: url(:/Resources/Images/upHover.png);}"));
        PBUp->setFlat(true);
        PBRight = new QPushButton(CameraPreview);
        PBRight->setObjectName(QStringLiteral("PBRight"));
        PBRight->setGeometry(QRect(693, 495, 23, 30));
        PBRight->setStyleSheet(QLatin1String("#PBRight {\n"
"background-image: url(:/Resources/Images/right.png);\n"
"border: none;\n"
"margin: 0px;\n"
"padding: 0px;}\n"
"#PBRight:hover{\n"
"background-image: url(:/Resources/Images/rightHover.png);}"));
        PBRight->setFlat(true);
        PBDown = new QPushButton(CameraPreview);
        PBDown->setObjectName(QStringLiteral("PBDown"));
        PBDown->setGeometry(QRect(658, 530, 30, 23));
        PBDown->setStyleSheet(QLatin1String("#PBDown {\n"
"background-image: url(:/Resources/Images/down.png);\n"
"border: none;\n"
"margin: 0px;\n"
"padding: 0px;}\n"
"#PBDown:hover{\n"
"background-image: url(:/Resources/Images/downHover.png);}"));
        PBDown->setFlat(true);
        PBLeft = new QPushButton(CameraPreview);
        PBLeft->setObjectName(QStringLiteral("PBLeft"));
        PBLeft->setGeometry(QRect(630, 495, 23, 30));
        PBLeft->setStyleSheet(QLatin1String("#PBLeft {\n"
"background-image: url(:/Resources/Images/left.png);\n"
"border: none;\n"
"margin: 0px;\n"
"padding: 0px;}\n"
"#PBLeft:hover{\n"
"background-image: url(:/Resources/Images/leftHover.png);}"));
        PBLeft->setFlat(true);
        PBSavePreset = new QPushButton(CameraPreview);
        PBSavePreset->setObjectName(QStringLiteral("PBSavePreset"));
        PBSavePreset->setGeometry(QRect(430, 490, 40, 40));
        PBSavePreset->setStyleSheet(QLatin1String("QPushButton{background-image: url(:/Resources/Images/savePreset.png);border: none; margin: 0px; padding: 0px;}\n"
"QPushButton:hover{background-image: url(:/Resources/Images/savePresetHover.png);}"));
        PBSavePreset->setFlat(true);
        CBPresets = new QComboBox(CameraPreview);
        CBPresets->setObjectName(QStringLiteral("CBPresets"));
        CBPresets->setGeometry(QRect(300, 500, 71, 21));
        PBBack = new QPushButton(CameraPreview);
        PBBack->setObjectName(QStringLiteral("PBBack"));
        PBBack->setGeometry(QRect(20, 560, 61, 23));
        PBBack->setStyleSheet(QLatin1String("#PBBack{\n"
"color:rgb(255, 255, 255);\n"
"background-color: rgb(255, 77, 61);}\n"
"#PBBack:hover{\n"
"background-color: rgb(255, 87, 58);\n"
"}\n"
"/*border: none;\n"
"margin: 0px;\n"
"padding: 0px;\n"
"background-color:none*/"));
        PBCameraOnOff = new QPushButton(CameraPreview);
        PBCameraOnOff->setObjectName(QStringLiteral("PBCameraOnOff"));
        PBCameraOnOff->setGeometry(QRect(80, 440, 40, 40));
        PBCameraOnOff->setStyleSheet(QStringLiteral("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}"));
        PBGoToPreset = new QPushButton(CameraPreview);
        PBGoToPreset->setObjectName(QStringLiteral("PBGoToPreset"));
        PBGoToPreset->setGeometry(QRect(380, 490, 40, 40));
        PBGoToPreset->setStyleSheet(QLatin1String("QPushButton{background-image: url(:/Resources/Images/goToPreset.png);border: none; margin: 0px; padding: 0px;}\n"
"QPushButton:hover{background-image: url(:/Resources/Images/goToPresetHover.png);}"));
        PBGoToPreset->setFlat(true);
        verticalLayoutWidget = new QWidget(CameraPreview);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(80, 70, 641, 361));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        QWidget::setTabOrder(PBCameraOnOff, CBPresets);
        QWidget::setTabOrder(CBPresets, PBGoToPreset);
        QWidget::setTabOrder(PBGoToPreset, PBSavePreset);
        QWidget::setTabOrder(PBSavePreset, PBRecognize);
        QWidget::setTabOrder(PBRecognize, PBEdit);
        QWidget::setTabOrder(PBEdit, PBSnapshot);
        QWidget::setTabOrder(PBSnapshot, PBHome);
        QWidget::setTabOrder(PBHome, PBUp);
        QWidget::setTabOrder(PBUp, PBLeft);
        QWidget::setTabOrder(PBLeft, PBRight);
        QWidget::setTabOrder(PBRight, PBDown);
        QWidget::setTabOrder(PBDown, PBBack);

        retranslateUi(CameraPreview);

        QMetaObject::connectSlotsByName(CameraPreview);
    } // setupUi

    void retranslateUi(QDialog *CameraPreview)
    {
        CameraPreview->setWindowTitle(QApplication::translate("CameraPreview", "LeonCam", Q_NULLPTR));
        LCameraDetails->setText(QApplication::translate("CameraPreview", "Camera details", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        PBRecognize->setToolTip(QApplication::translate("CameraPreview", "Recognation mode: On", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBRecognize->setText(QString());
#ifndef QT_NO_TOOLTIP
        PBEdit->setToolTip(QApplication::translate("CameraPreview", "Edit camera", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBEdit->setText(QString());
#ifndef QT_NO_TOOLTIP
        PBSnapshot->setToolTip(QApplication::translate("CameraPreview", "Take a snapshot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBSnapshot->setText(QString());
#ifndef QT_NO_TOOLTIP
        PBHome->setToolTip(QApplication::translate("CameraPreview", "Go to home position", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBHome->setText(QString());
#ifndef QT_NO_TOOLTIP
        PBUp->setToolTip(QApplication::translate("CameraPreview", "Move the camera up", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBUp->setText(QString());
#ifndef QT_NO_TOOLTIP
        PBRight->setToolTip(QApplication::translate("CameraPreview", "Move the camera right", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBRight->setText(QString());
#ifndef QT_NO_TOOLTIP
        PBDown->setToolTip(QApplication::translate("CameraPreview", "Move the camera down", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBDown->setText(QString());
#ifndef QT_NO_TOOLTIP
        PBLeft->setToolTip(QApplication::translate("CameraPreview", "Move the camera left", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBLeft->setText(QString());
#ifndef QT_NO_TOOLTIP
        PBSavePreset->setToolTip(QApplication::translate("CameraPreview", "Save selected preset", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBSavePreset->setText(QString());
        PBBack->setText(QApplication::translate("CameraPreview", "Back", Q_NULLPTR));
        PBCameraOnOff->setText(QApplication::translate("CameraPreview", "Off", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        PBGoToPreset->setToolTip(QApplication::translate("CameraPreview", "Go to selected preset", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBGoToPreset->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CameraPreview: public Ui_CameraPreview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAPREVIEW_H
