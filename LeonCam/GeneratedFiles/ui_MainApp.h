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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainApp
{
public:
    QWidget *centralWidget;
    QTabWidget *TWMenu;
    QWidget *TCameras;
    QPushButton *PBAddCamera;
    QTableWidget *TLWCameras;
    QLabel *LTotalNumber;
    QLabel *LEnabledNumber;
    QLabel *LHelpCameras;
    QLabel *LSearch;
    QLineEdit *LESearch;
    QWidget *TFacesBase;
    QWidget *TReports;
    QWidget *TSettings;

    void setupUi(QMainWindow *MainApp)
    {
        if (MainApp->objectName().isEmpty())
            MainApp->setObjectName(QStringLiteral("MainApp"));
        MainApp->resize(800, 500);
        MainApp->setMinimumSize(QSize(800, 500));
        MainApp->setMaximumSize(QSize(800, 500));
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
        TWMenu->setGeometry(QRect(30, 20, 740, 461));
        TWMenu->setStyleSheet(QLatin1String("QTabWidget::pane {\n"
"border: 0px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"background-color: transparent;\n"
"/*color: rgb(0, 69, 104);*/\n"
"color: rgb(116, 145, 206);\n"
"height: 32px;\n"
"font: 18pt \"Nirmala UI\";\n"
"width: 185px;\n"
"}\n"
"\n"
"QTabBar::tab:hover{\n"
"/*color: rgb(185, 185, 185);*/\n"
"	color: rgb(134, 164, 245);\n"
"}\n"
"\n"
"QTabBar::tab:selected{\n"
"margin-top: 1px;\n"
"	color: rgb(205, 220, 255);\n"
"}\n"
""));
        TWMenu->setUsesScrollButtons(false);
        TCameras = new QWidget();
        TCameras->setObjectName(QStringLiteral("TCameras"));
        TCameras->setStyleSheet(QStringLiteral("background-color: transparent"));
        PBAddCamera = new QPushButton(TCameras);
        PBAddCamera->setObjectName(QStringLiteral("PBAddCamera"));
        PBAddCamera->setGeometry(QRect(610, 390, 111, 23));
        PBAddCamera->setStyleSheet(QLatin1String("#PBAddCamera{\n"
"color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59)}\n"
"#PBAddCamera:hover\n"
"{\n"
"background-color: rgb(39, 129, 63);\n"
"}"));
        TLWCameras = new QTableWidget(TCameras);
        if (TLWCameras->columnCount() < 9)
            TLWCameras->setColumnCount(9);
        TLWCameras->setObjectName(QStringLiteral("TLWCameras"));
        TLWCameras->setGeometry(QRect(20, 100, 700, 281));
        TLWCameras->setStyleSheet(QLatin1String("QTableWidget { selection-background-color: transparent;\n"
"gridline-color: rgb(116, 145, 206);\n"
"}\n"
"\n"
"QTableWidget::item { padding: 0px }"));
        TLWCameras->setFrameShape(QFrame::StyledPanel);
        TLWCameras->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        TLWCameras->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TLWCameras->setEditTriggers(QAbstractItemView::DoubleClicked);
        TLWCameras->setProperty("showDropIndicator", QVariant(false));
        TLWCameras->setDragDropOverwriteMode(false);
        TLWCameras->setSelectionMode(QAbstractItemView::SingleSelection);
        TLWCameras->setSelectionBehavior(QAbstractItemView::SelectRows);
        TLWCameras->setWordWrap(false);
        TLWCameras->setCornerButtonEnabled(false);
        TLWCameras->setColumnCount(9);
        TLWCameras->horizontalHeader()->setVisible(false);
        TLWCameras->horizontalHeader()->setDefaultSectionSize(85);
        TLWCameras->verticalHeader()->setVisible(false);
        TLWCameras->verticalHeader()->setDefaultSectionSize(40);
        LTotalNumber = new QLabel(TCameras);
        LTotalNumber->setObjectName(QStringLiteral("LTotalNumber"));
        LTotalNumber->setGeometry(QRect(20, 390, 201, 23));
        LTotalNumber->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: transparent;\n"
"font-weight:600;"));
        LTotalNumber->setIndent(0);
        LEnabledNumber = new QLabel(TCameras);
        LEnabledNumber->setObjectName(QStringLiteral("LEnabledNumber"));
        LEnabledNumber->setGeometry(QRect(290, 390, 221, 23));
        LEnabledNumber->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: transparent;\n"
"font-weight:600;"));
        LEnabledNumber->setIndent(0);
        LHelpCameras = new QLabel(TCameras);
        LHelpCameras->setObjectName(QStringLiteral("LHelpCameras"));
        LHelpCameras->setGeometry(QRect(20, 30, 701, 31));
        LHelpCameras->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59)"));
        LSearch = new QLabel(TCameras);
        LSearch->setObjectName(QStringLiteral("LSearch"));
        LSearch->setGeometry(QRect(20, 70, 23, 23));
        LSearch->setStyleSheet(QStringLiteral("background-image: url(:/Resources/Images/search.png); border: none; margin: 0px; padding: 0px;"));
        LESearch = new QLineEdit(TCameras);
        LESearch->setObjectName(QStringLiteral("LESearch"));
        LESearch->setGeometry(QRect(25, 70, 695, 23));
        LESearch->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"padding-left: 22px;\n"
"border-radius: 11px;"));
        TWMenu->addTab(TCameras, QString());
        PBAddCamera->raise();
        TLWCameras->raise();
        LTotalNumber->raise();
        LEnabledNumber->raise();
        LHelpCameras->raise();
        LESearch->raise();
        LSearch->raise();
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
        LTotalNumber->setText(QApplication::translate("MainApp", "Total number of cameras: 0", Q_NULLPTR));
        LEnabledNumber->setText(QApplication::translate("MainApp", "Number of enabled cameras: 0", Q_NULLPTR));
        LHelpCameras->setText(QApplication::translate("MainApp", "<html><head/><body><p align=\"center\">Here you can manage cameras assigned to your profile</p></body></html>", Q_NULLPTR));
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
