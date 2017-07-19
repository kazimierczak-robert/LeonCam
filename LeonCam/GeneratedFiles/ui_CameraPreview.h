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
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CameraPreview
{
public:
    QLabel *isAvailable;
    QLabel *cameraDetailsLabel;
    QPushButton *patrolButton;
    QPushButton *recognizeButton;
    QPushButton *editButton;
    QPushButton *snapshotButton;
    QLabel *previewScreen;
    QPushButton *backButton;
    QLabel *detectedPeopleLabel;
    QPushButton *homeButton;
    QPushButton *upButton;
    QPushButton *rightButton;
    QPushButton *downButton;
    QPushButton *leftButton;

    void setupUi(QDialog *CameraPreview)
    {
        if (CameraPreview->objectName().isEmpty())
            CameraPreview->setObjectName(QStringLiteral("CameraPreview"));
        CameraPreview->resize(800, 500);
        CameraPreview->setMinimumSize(QSize(800, 500));
        CameraPreview->setMaximumSize(QSize(800, 500));
        CameraPreview->setStyleSheet(QLatin1String("#CameraPreview\n"
"{\n"
"	background-image: url(:/Resources/Images/backgroundMain.png);\n"
"}"));
        isAvailable = new QLabel(CameraPreview);
        isAvailable->setObjectName(QStringLiteral("isAvailable"));
        isAvailable->setGeometry(QRect(80, 430, 10, 10));
        isAvailable->setStyleSheet(QStringLiteral("background-image: url(:/Resources/Images/unavailable.png);"));
        cameraDetailsLabel = new QLabel(CameraPreview);
        cameraDetailsLabel->setObjectName(QStringLiteral("cameraDetailsLabel"));
        cameraDetailsLabel->setGeometry(QRect(100, 427, 101, 16));
        patrolButton = new QPushButton(CameraPreview);
        patrolButton->setObjectName(QStringLiteral("patrolButton"));
        patrolButton->setGeometry(QRect(420, 420, 40, 40));
        recognizeButton = new QPushButton(CameraPreview);
        recognizeButton->setObjectName(QStringLiteral("recognizeButton"));
        recognizeButton->setGeometry(QRect(470, 420, 40, 40));
        editButton = new QPushButton(CameraPreview);
        editButton->setObjectName(QStringLiteral("editButton"));
        editButton->setGeometry(QRect(520, 420, 40, 40));
        snapshotButton = new QPushButton(CameraPreview);
        snapshotButton->setObjectName(QStringLiteral("snapshotButton"));
        snapshotButton->setGeometry(QRect(570, 420, 40, 40));
        previewScreen = new QLabel(CameraPreview);
        previewScreen->setObjectName(QStringLiteral("previewScreen"));
        previewScreen->setGeometry(QRect(80, 20, 640, 360));
        previewScreen->setFrameShape(QFrame::Box);
        previewScreen->setAlignment(Qt::AlignCenter);
        backButton = new QPushButton(CameraPreview);
        backButton->setObjectName(QStringLiteral("backButton"));
        backButton->setGeometry(QRect(0, 225, 40, 50));
        backButton->setStyleSheet(QLatin1String("#backButton{\n"
"	font: 30pt \"Kristen ITC\";\n"
"letter-spacing:12px;\n"
"background-color: transparent;\n"
"color: rgb(138, 138, 207);\n"
"}\n"
"\n"
"#backButton:hover{\n"
"color: rgb(233, 233, 233);\n"
"}"));
        detectedPeopleLabel = new QLabel(CameraPreview);
        detectedPeopleLabel->setObjectName(QStringLiteral("detectedPeopleLabel"));
        detectedPeopleLabel->setGeometry(QRect(80, 450, 191, 16));
        homeButton = new QPushButton(CameraPreview);
        homeButton->setObjectName(QStringLiteral("homeButton"));
        homeButton->setGeometry(QRect(660, 420, 40, 40));
        upButton = new QPushButton(CameraPreview);
        upButton->setObjectName(QStringLiteral("upButton"));
        upButton->setGeometry(QRect(660, 390, 40, 30));
        rightButton = new QPushButton(CameraPreview);
        rightButton->setObjectName(QStringLiteral("rightButton"));
        rightButton->setGeometry(QRect(700, 420, 30, 40));
        downButton = new QPushButton(CameraPreview);
        downButton->setObjectName(QStringLiteral("downButton"));
        downButton->setGeometry(QRect(660, 460, 40, 30));
        leftButton = new QPushButton(CameraPreview);
        leftButton->setObjectName(QStringLiteral("leftButton"));
        leftButton->setGeometry(QRect(630, 420, 30, 40));

        retranslateUi(CameraPreview);

        QMetaObject::connectSlotsByName(CameraPreview);
    } // setupUi

    void retranslateUi(QDialog *CameraPreview)
    {
        CameraPreview->setWindowTitle(QApplication::translate("CameraPreview", "LeonCam", Q_NULLPTR));
        isAvailable->setText(QString());
        cameraDetailsLabel->setText(QApplication::translate("CameraPreview", "Camera details", Q_NULLPTR));
        patrolButton->setText(QApplication::translate("CameraPreview", "Patrol", Q_NULLPTR));
        recognizeButton->setText(QApplication::translate("CameraPreview", "Recognize", Q_NULLPTR));
        editButton->setText(QApplication::translate("CameraPreview", "Edit", Q_NULLPTR));
        snapshotButton->setText(QApplication::translate("CameraPreview", "Snapshot", Q_NULLPTR));
        previewScreen->setText(QApplication::translate("CameraPreview", "Preview", Q_NULLPTR));
        backButton->setText(QApplication::translate("CameraPreview", "<<", Q_NULLPTR));
        detectedPeopleLabel->setText(QApplication::translate("CameraPreview", "Number of detected people: 0", Q_NULLPTR));
        homeButton->setText(QApplication::translate("CameraPreview", "Home", Q_NULLPTR));
        upButton->setText(QApplication::translate("CameraPreview", "Up", Q_NULLPTR));
        rightButton->setText(QApplication::translate("CameraPreview", "Right", Q_NULLPTR));
        downButton->setText(QApplication::translate("CameraPreview", "Down", Q_NULLPTR));
        leftButton->setText(QApplication::translate("CameraPreview", "Left", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CameraPreview: public Ui_CameraPreview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAPREVIEW_H
