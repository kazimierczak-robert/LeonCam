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
    QTabWidget *TWCameraPages;
    QLabel *LTotalNumber;
    QLabel *LEnabledNumber;
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
        TWMenu->setGeometry(QRect(30, 20, 740, 561));
        TWMenu->setStyleSheet(QLatin1String("QTabWidget::pane {\n"
"color: rgb(213, 235, 255);\n"
"border: 0px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"background-color: transparent;\n"
"color: rgb(133, 196, 255);\n"
"height: 32px;\n"
"font: 18pt \"Nirmala UI\";\n"
"width: 185px;\n"
"}\n"
"\n"
"QTabBar::tab:hover{\n"
"color: rgb(160, 209, 255);\n"
"\n"
"}\n"
"\n"
"QTabBar::tab:selected{\n"
"margin-top: 1px;\n"
"color:rgb(219, 235, 255)\n"
"}\n"
""));
        TWMenu->setUsesScrollButtons(false);
        TCameras = new QWidget();
        TCameras->setObjectName(QStringLiteral("TCameras"));
        TCameras->setStyleSheet(QStringLiteral("background-color: transparent"));
        PBAddCamera = new QPushButton(TCameras);
        PBAddCamera->setObjectName(QStringLiteral("PBAddCamera"));
        PBAddCamera->setGeometry(QRect(610, 30, 100, 23));
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
        LESearch->setGeometry(QRect(35, 30, 560, 23));
        LESearch->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"padding-left: 22px;\n"
"border-radius: 11px;"));
        TWCameraPages = new QTabWidget(TCameras);
        TWCameraPages->setObjectName(QStringLiteral("TWCameraPages"));
        TWCameraPages->setGeometry(QRect(10, 59, 720, 440));
        TWCameraPages->setStyleSheet(QLatin1String("QTabWidget::pane {\n"
"color: rgb(213, 235, 255);\n"
"border: 0px;\n"
"}\n"
"\n"
"QTabWidget::tab-bar {\n"
"left: 342px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"background-color: transparent;\n"
"color: rgb(133, 196, 255);\n"
"height: 18px;\n"
"width: 36px;\n"
"}\n"
"\n"
"QTabBar::tab:hover{\n"
"color: rgb(160, 209, 255);\n"
"}\n"
"\n"
"QTabBar::tab:selected{\n"
"margin-top: -1px;\n"
"color:rgb(219, 235, 255);\n"
"}"));
        TWCameraPages->setTabPosition(QTabWidget::South);
        TWCameraPages->setTabShape(QTabWidget::Rounded);
        TWCameraPages->setUsesScrollButtons(false);
        LTotalNumber = new QLabel(TCameras);
        LTotalNumber->setObjectName(QStringLiteral("LTotalNumber"));
        LTotalNumber->setGeometry(QRect(30, 500, 200, 13));
        LTotalNumber->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: transparent;\n"
"font-weight:600;"));
        LEnabledNumber = new QLabel(TCameras);
        LEnabledNumber->setObjectName(QStringLiteral("LEnabledNumber"));
        LEnabledNumber->setGeometry(QRect(30, 515, 200, 13));
        LEnabledNumber->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: transparent;\n"
"font-weight:600;"));
        TWMenu->addTab(TCameras, QString());
        PBAddCamera->raise();
        LESearch->raise();
        LSearch->raise();
        TWCameraPages->raise();
        LTotalNumber->raise();
        LEnabledNumber->raise();
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
        TWCameraPages->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainApp);
    } // setupUi

    void retranslateUi(QMainWindow *MainApp)
    {
        MainApp->setWindowTitle(QApplication::translate("MainApp", "LeonCam", Q_NULLPTR));
        PBAddCamera->setText(QApplication::translate("MainApp", "Add Camera", Q_NULLPTR));
        LSearch->setText(QString());
        LESearch->setPlaceholderText(QApplication::translate("MainApp", "Search camera", Q_NULLPTR));
        LTotalNumber->setText(QApplication::translate("MainApp", "Total number of cameras: 0", Q_NULLPTR));
        LEnabledNumber->setText(QApplication::translate("MainApp", "Number of enabled cameras: 0", Q_NULLPTR));
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
