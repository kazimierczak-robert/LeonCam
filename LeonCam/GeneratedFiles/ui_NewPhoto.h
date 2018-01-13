/********************************************************************************
** Form generated from reading UI file 'NewPhoto.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPHOTO_H
#define UI_NEWPHOTO_H

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

class Ui_NewPhoto
{
public:
    QPushButton *PBDown;
    QPushButton *PBRight;
    QPushButton *PBLeft;
    QPushButton *PBUp;
    QPushButton *PBSnapshot;
    QPushButton *PBBack;
    QComboBox *CBPresets;
    QLabel *LHelp;
    QPushButton *PBFolder;
    QPushButton *PBHome;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *LView;
    QPushButton *PWarning;

    void setupUi(QDialog *NewPhoto)
    {
        if (NewPhoto->objectName().isEmpty())
            NewPhoto->setObjectName(QStringLiteral("NewPhoto"));
        NewPhoto->resize(800, 600);
        NewPhoto->setMinimumSize(QSize(800, 600));
        NewPhoto->setMaximumSize(QSize(800, 600));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/Images/logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        NewPhoto->setWindowIcon(icon);
        NewPhoto->setStyleSheet(QLatin1String("#NewPhoto\n"
"{\n"
"	background-image: url(:/Resources/Images/backgroundMain.png);\n"
"}"));
        PBDown = new QPushButton(NewPhoto);
        PBDown->setObjectName(QStringLiteral("PBDown"));
        PBDown->setGeometry(QRect(715, 550, 30, 23));
        PBDown->setStyleSheet(QLatin1String("#PBDown {\n"
"background-image: url(:/Resources/Images/down.png);\n"
"border: none;\n"
"margin: 0px;\n"
"padding: 0px;}\n"
"#PBDown:hover{\n"
"background-image: url(:/Resources/Images/downHover.png);}"));
        PBDown->setFlat(true);
        PBRight = new QPushButton(NewPhoto);
        PBRight->setObjectName(QStringLiteral("PBRight"));
        PBRight->setGeometry(QRect(750, 515, 23, 30));
        PBRight->setStyleSheet(QLatin1String("#PBRight {\n"
"background-image: url(:/Resources/Images/right.png);\n"
"border: none;\n"
"margin: 0px;\n"
"padding: 0px;}\n"
"#PBRight:hover{\n"
"background-image: url(:/Resources/Images/rightHover.png);}"));
        PBRight->setFlat(true);
        PBLeft = new QPushButton(NewPhoto);
        PBLeft->setObjectName(QStringLiteral("PBLeft"));
        PBLeft->setGeometry(QRect(687, 515, 23, 30));
        PBLeft->setStyleSheet(QLatin1String("#PBLeft {\n"
"background-image: url(:/Resources/Images/left.png);\n"
"border: none;\n"
"margin: 0px;\n"
"padding: 0px;}\n"
"#PBLeft:hover{\n"
"background-image: url(:/Resources/Images/leftHover.png);}"));
        PBLeft->setFlat(true);
        PBUp = new QPushButton(NewPhoto);
        PBUp->setObjectName(QStringLiteral("PBUp"));
        PBUp->setGeometry(QRect(715, 487, 30, 23));
        PBUp->setStyleSheet(QLatin1String("#PBUp {\n"
"background-image: url(:/Resources/Images/up.png);\n"
"border: none;\n"
"margin: 0px;\n"
"padding: 0px;}\n"
"#PBUp:hover{\n"
"background-image: url(:/Resources/Images/upHover.png);}"));
        PBUp->setFlat(true);
        PBSnapshot = new QPushButton(NewPhoto);
        PBSnapshot->setObjectName(QStringLiteral("PBSnapshot"));
        PBSnapshot->setEnabled(false);
        PBSnapshot->setGeometry(QRect(360, 60, 40, 40));
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
        PBBack = new QPushButton(NewPhoto);
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
        CBPresets = new QComboBox(NewPhoto);
        CBPresets->setObjectName(QStringLiteral("CBPresets"));
        CBPresets->setGeometry(QRect(20, 70, 331, 21));
        LHelp = new QLabel(NewPhoto);
        LHelp->setObjectName(QStringLiteral("LHelp"));
        LHelp->setGeometry(QRect(20, 20, 761, 31));
        LHelp->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(46, 147, 222);"));
        PBFolder = new QPushButton(NewPhoto);
        PBFolder->setObjectName(QStringLiteral("PBFolder"));
        PBFolder->setGeometry(QRect(410, 60, 40, 40));
        PBFolder->setStyleSheet(QLatin1String("#PBFolder\n"
"{\n"
"background-image: url(:/Resources/Images/folder.png);\n"
"border: none;\n"
"margin: 0px;\n"
"padding: 0px;}\n"
"#PBFolder:hover{background-image: url(:/Resources/Images/folderHover.png);}\n"
""));
        PBFolder->setAutoDefault(true);
        PBFolder->setFlat(true);
        PBHome = new QPushButton(NewPhoto);
        PBHome->setObjectName(QStringLiteral("PBHome"));
        PBHome->setGeometry(QRect(710, 510, 40, 40));
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
        verticalLayoutWidget = new QWidget(NewPhoto);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(80, 110, 641, 361));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        LView = new QLabel(NewPhoto);
        LView->setObjectName(QStringLiteral("LView"));
        LView->setGeometry(QRect(80, 110, 640, 360));
        LView->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 54, 80);"));
        PWarning = new QPushButton(NewPhoto);
        PWarning->setObjectName(QStringLiteral("PWarning"));
        PWarning->setGeometry(QRect(265, 515, 271, 31));
        PWarning->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(255, 77, 61);"));
        LView->raise();
        PBDown->raise();
        PBRight->raise();
        PBLeft->raise();
        PBUp->raise();
        PBSnapshot->raise();
        PBBack->raise();
        CBPresets->raise();
        LHelp->raise();
        PBFolder->raise();
        PBHome->raise();
        verticalLayoutWidget->raise();
        PWarning->raise();

        retranslateUi(NewPhoto);

        QMetaObject::connectSlotsByName(NewPhoto);
    } // setupUi

    void retranslateUi(QDialog *NewPhoto)
    {
        NewPhoto->setWindowTitle(QApplication::translate("NewPhoto", "LeonCam", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        PBDown->setToolTip(QApplication::translate("NewPhoto", "Move the camera down", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBDown->setText(QString());
#ifndef QT_NO_TOOLTIP
        PBRight->setToolTip(QApplication::translate("NewPhoto", "Move the camera right", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBRight->setText(QString());
#ifndef QT_NO_TOOLTIP
        PBLeft->setToolTip(QApplication::translate("NewPhoto", "Move the camera left", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBLeft->setText(QString());
#ifndef QT_NO_TOOLTIP
        PBUp->setToolTip(QApplication::translate("NewPhoto", "Move the camera up", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBUp->setText(QString());
#ifndef QT_NO_TOOLTIP
        PBSnapshot->setToolTip(QApplication::translate("NewPhoto", "Take a photo", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBSnapshot->setText(QString());
        PBBack->setText(QApplication::translate("NewPhoto", "Back", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        CBPresets->setToolTip(QApplication::translate("NewPhoto", "Available cameras", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        LHelp->setText(QApplication::translate("NewPhoto", "<html><head/><body><p align=\"center\">If the face is detected, the <span style=\" font-weight:600;\">photo button</span> is enabled</p></body></html>", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        PBFolder->setToolTip(QApplication::translate("NewPhoto", "<html><head/><body><p>Go to the folder</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBFolder->setText(QString());
#ifndef QT_NO_TOOLTIP
        PBHome->setToolTip(QApplication::translate("NewPhoto", "Go to home position", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBHome->setText(QString());
        LView->setText(QApplication::translate("NewPhoto", "<html><head/><body><p align=\"center\"><br/></p></body></html>", Q_NULLPTR));
        PWarning->setText(QApplication::translate("NewPhoto", "No faces has been detected", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NewPhoto: public Ui_NewPhoto {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPHOTO_H
