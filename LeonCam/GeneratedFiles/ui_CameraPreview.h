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

QT_BEGIN_NAMESPACE

class Ui_CameraPreview
{
public:
    QLabel *LCameraDetails;
    QPushButton *PBPatrol;
    QPushButton *PBRecognize;
    QPushButton *PBEdit;
    QPushButton *PBSnapshot;
    QLabel *LPreviewScreen;
    QLabel *LDetectedPeople;
    QPushButton *PBHome;
    QPushButton *PBUp;
    QPushButton *PBRight;
    QPushButton *PBDown;
    QPushButton *PBLeft;
    QPushButton *PBSavePreset;
    QComboBox *CBPresets;
    QPushButton *PBBack;
    QPushButton *PBCameraOnOff;

    void setupUi(QDialog *CameraPreview)
    {
        if (CameraPreview->objectName().isEmpty())
            CameraPreview->setObjectName(QStringLiteral("CameraPreview"));
        CameraPreview->resize(800, 500);
        CameraPreview->setMinimumSize(QSize(800, 500));
        CameraPreview->setMaximumSize(QSize(800, 500));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/Images/logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        CameraPreview->setWindowIcon(icon);
        CameraPreview->setStyleSheet(QLatin1String("#CameraPreview\n"
"{\n"
"	background-image: url(:/Resources/Images/backgroundMain.png);\n"
"}"));
        LCameraDetails = new QLabel(CameraPreview);
        LCameraDetails->setObjectName(QStringLiteral("LCameraDetails"));
        LCameraDetails->setGeometry(QRect(160, 420, 101, 21));
        PBPatrol = new QPushButton(CameraPreview);
        PBPatrol->setObjectName(QStringLiteral("PBPatrol"));
        PBPatrol->setGeometry(QRect(530, 410, 40, 40));
        PBRecognize = new QPushButton(CameraPreview);
        PBRecognize->setObjectName(QStringLiteral("PBRecognize"));
        PBRecognize->setGeometry(QRect(580, 410, 40, 40));
        PBEdit = new QPushButton(CameraPreview);
        PBEdit->setObjectName(QStringLiteral("PBEdit"));
        PBEdit->setGeometry(QRect(630, 410, 40, 40));
        PBSnapshot = new QPushButton(CameraPreview);
        PBSnapshot->setObjectName(QStringLiteral("PBSnapshot"));
        PBSnapshot->setGeometry(QRect(680, 410, 40, 40));
        LPreviewScreen = new QLabel(CameraPreview);
        LPreviewScreen->setObjectName(QStringLiteral("LPreviewScreen"));
        LPreviewScreen->setGeometry(QRect(80, 20, 640, 360));
        LPreviewScreen->setFrameShape(QFrame::Box);
        LPreviewScreen->setAlignment(Qt::AlignCenter);
        LDetectedPeople = new QLabel(CameraPreview);
        LDetectedPeople->setObjectName(QStringLiteral("LDetectedPeople"));
        LDetectedPeople->setGeometry(QRect(120, 450, 191, 16));
        PBHome = new QPushButton(CameraPreview);
        PBHome->setObjectName(QStringLiteral("PBHome"));
        PBHome->setGeometry(QRect(650, 310, 40, 40));
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
        PBUp->setGeometry(QRect(650, 280, 40, 30));
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
        PBRight->setGeometry(QRect(690, 310, 30, 40));
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
        PBDown->setGeometry(QRect(650, 350, 40, 30));
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
        PBLeft->setGeometry(QRect(620, 310, 30, 40));
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
        PBSavePreset->setGeometry(QRect(480, 410, 41, 41));
        CBPresets = new QComboBox(CameraPreview);
        CBPresets->setObjectName(QStringLiteral("CBPresets"));
        CBPresets->setGeometry(QRect(330, 420, 131, 21));
        PBBack = new QPushButton(CameraPreview);
        PBBack->setObjectName(QStringLiteral("PBBack"));
        PBBack->setGeometry(QRect(30, 440, 61, 23));
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
        PBCameraOnOff->setGeometry(QRect(120, 420, 31, 23));

        retranslateUi(CameraPreview);

        QMetaObject::connectSlotsByName(CameraPreview);
    } // setupUi

    void retranslateUi(QDialog *CameraPreview)
    {
        CameraPreview->setWindowTitle(QApplication::translate("CameraPreview", "LeonCam", Q_NULLPTR));
        LCameraDetails->setText(QApplication::translate("CameraPreview", "Camera details", Q_NULLPTR));
        PBPatrol->setText(QApplication::translate("CameraPreview", "Patrol", Q_NULLPTR));
        PBRecognize->setText(QApplication::translate("CameraPreview", "Recognize", Q_NULLPTR));
        PBEdit->setText(QApplication::translate("CameraPreview", "Edit", Q_NULLPTR));
        PBSnapshot->setText(QApplication::translate("CameraPreview", "Snapshot", Q_NULLPTR));
        LPreviewScreen->setText(QApplication::translate("CameraPreview", "Preview", Q_NULLPTR));
        LDetectedPeople->setText(QApplication::translate("CameraPreview", "Number of detected people: 0", Q_NULLPTR));
        PBHome->setText(QString());
        PBUp->setText(QString());
        PBRight->setText(QString());
        PBDown->setText(QString());
        PBLeft->setText(QString());
        PBSavePreset->setText(QApplication::translate("CameraPreview", "Save", Q_NULLPTR));
        PBBack->setText(QApplication::translate("CameraPreview", "Back", Q_NULLPTR));
        PBCameraOnOff->setText(QApplication::translate("CameraPreview", "OnOff", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CameraPreview: public Ui_CameraPreview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAPREVIEW_H
