/********************************************************************************
** Form generated from reading UI file 'MainApp.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINAPP_H
#define UI_MAINAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainApp
{
public:
    QWidget *centralWidget;
    QTabWidget *TWMenu;
    QWidget *TCameras;
    QPushButton *PBAddCamera;
    QLabel *LSearch;
    QLineEdit *LESearch;
    QWidget *gridLayoutWidget;
    QGridLayout *GLCameras;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *HLCameraPages;
    QWidget *TFacesBase;
    QWidget *TReports;
    QWidget *TSettings;

    void setupUi(QMainWindow *MainApp)
    {
        if (MainApp->objectName().isEmpty())
            MainApp->setObjectName(QStringLiteral("MainApp"));
        MainApp->resize(800, 600);
        MainApp->setMinimumSize(QSize(800, 600));
        MainApp->setMaximumSize(QSize(800, 600));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/Images/logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainApp->setWindowIcon(icon);
        MainApp->setStyleSheet(QLatin1String("#centralWidget\n"
"{\n"
"	background-image: url(:/Resources/Images/backgroundMain.png);\n"
"}\n"
"\n"
"\n"
"\n"
""));
        centralWidget = new QWidget(MainApp);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        TWMenu = new QTabWidget(centralWidget);
        TWMenu->setObjectName(QStringLiteral("TWMenu"));
        TWMenu->setGeometry(QRect(30, 20, 740, 551));
        TWMenu->setStyleSheet(QLatin1String("QTabWidget::pane {\n"
"color: rgb(213, 235, 255);\n"
"border: 0px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"background-color: transparent;\n"
"/*color: rgb(0, 69, 104);*/\n"
"/*color: rgb(116, 145, 206);*/\n"
"color: rgb(133, 196, 255);\n"
"height: 32px;\n"
"font: 18pt \"Nirmala UI\";\n"
"width: 185px;\n"
"}\n"
"\n"
"QTabBar::tab:hover{\n"
"/*color: rgb(185, 185, 185);*/\n"
"/*	color: rgb(134, 164, 245);*/\n"
"color: rgb(160, 209, 255);\n"
"\n"
"}\n"
"\n"
"QTabBar::tab:selected{\n"
"margin-top: 1px;\n"
"/*color: rgb(205, 220, 255);*/\n"
"/*color: rgb(160, 209, 255);*/\n"
"color:rgb(219, 235, 255)\n"
"}\n"
""));
        TWMenu->setUsesScrollButtons(false);
        TCameras = new QWidget();
        TCameras->setObjectName(QStringLiteral("TCameras"));
        TCameras->setStyleSheet(QStringLiteral("background-color: transparent"));
        PBAddCamera = new QPushButton(TCameras);
        PBAddCamera->setObjectName(QStringLiteral("PBAddCamera"));
        PBAddCamera->setGeometry(QRect(610, 30, 101, 23));
        PBAddCamera->setStyleSheet(QLatin1String("#PBAddCamera{\n"
"color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59)}\n"
"#PBAddCamera:hover\n"
"{\n"
"background-color: rgb(39, 129, 63);\n"
"}"));
        LSearch = new QLabel(TCameras);
        LSearch->setObjectName(QStringLiteral("LSearch"));
        LSearch->setGeometry(QRect(30, 30, 23, 23));
        LSearch->setStyleSheet(QStringLiteral("background-image: url(:/Resources/Images/search.png); border: none; margin: 0px; padding: 0px;"));
        LESearch = new QLineEdit(TCameras);
        LESearch->setObjectName(QStringLiteral("LESearch"));
        LESearch->setGeometry(QRect(35, 30, 561, 23));
        LESearch->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"padding-left: 22px;\n"
"border-radius: 11px;"));
        gridLayoutWidget = new QWidget(TCameras);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 60, 701, 421));
        GLCameras = new QGridLayout(gridLayoutWidget);
        GLCameras->setSpacing(6);
        GLCameras->setContentsMargins(11, 11, 11, 11);
        GLCameras->setObjectName(QStringLiteral("GLCameras"));
        GLCameras->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget = new QWidget(TCameras);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 490, 701, 25));
        HLCameraPages = new QHBoxLayout(horizontalLayoutWidget);
        HLCameraPages->setSpacing(6);
        HLCameraPages->setContentsMargins(11, 11, 11, 11);
        HLCameraPages->setObjectName(QStringLiteral("HLCameraPages"));
        HLCameraPages->setContentsMargins(0, 0, 0, 0);
        TWMenu->addTab(TCameras, QString());
        PBAddCamera->raise();
        LESearch->raise();
        LSearch->raise();
        gridLayoutWidget->raise();
        horizontalLayoutWidget->raise();
        TFacesBase = new QWidget();
        TFacesBase->setObjectName(QStringLiteral("TFacesBase"));
        TFacesBase->setStyleSheet(QStringLiteral("background-color: transparent;"));
        TWMenu->addTab(TFacesBase, QString());
        TReports = new QWidget();
        TReports->setObjectName(QStringLiteral("TReports"));
        TReports->setStyleSheet(QStringLiteral("background-color: transparent;"));
        TWMenu->addTab(TReports, QString());
        TSettings = new QWidget();
        TSettings->setObjectName(QStringLiteral("TSettings"));
        TSettings->setStyleSheet(QStringLiteral("background-color: transparent;"));
        TWMenu->addTab(TSettings, QString());
        MainApp->setCentralWidget(centralWidget);

        retranslateUi(MainApp);

        TWMenu->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainApp);
    } // setupUi

    void retranslateUi(QMainWindow *MainApp)
    {
        MainApp->setWindowTitle(QApplication::translate("MainApp", "LeonCam", Q_NULLPTR));
        PBAddCamera->setText(QApplication::translate("MainApp", "Add Camera", Q_NULLPTR));
        LSearch->setText(QString());
        LESearch->setPlaceholderText(QApplication::translate("MainApp", "Search camera", Q_NULLPTR));
        TWMenu->setTabText(TWMenu->indexOf(TCameras), QApplication::translate("MainApp", "CAMERAS", Q_NULLPTR));
        TWMenu->setTabText(TWMenu->indexOf(TFacesBase), QApplication::translate("MainApp", "FACES BASE", Q_NULLPTR));
        TWMenu->setTabText(TWMenu->indexOf(TReports), QApplication::translate("MainApp", "   REPORTS", Q_NULLPTR));
        TWMenu->setTabText(TWMenu->indexOf(TSettings), QApplication::translate("MainApp", "SETTINGS", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainApp: public Ui_MainApp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINAPP_H
