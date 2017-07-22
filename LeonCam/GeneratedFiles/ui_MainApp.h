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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainApp
{
public:
    QWidget *centralWidget;
    QTabWidget *TWMenu;
    QWidget *TCameras;
    QPushButton *PBNewCamera;
    QTextEdit *TESearch;
    QTableWidget *TLWCameras;
    QLabel *LTotalNumber;
    QLabel *LEnabledNumber;
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
"	color: rgb(144, 174, 255);\n"
"}\n"
""));
        TWMenu->setUsesScrollButtons(false);
        TCameras = new QWidget();
        TCameras->setObjectName(QStringLiteral("TCameras"));
        TCameras->setStyleSheet(QStringLiteral("background-color: transparent"));
        PBNewCamera = new QPushButton(TCameras);
        PBNewCamera->setObjectName(QStringLiteral("PBNewCamera"));
        PBNewCamera->setGeometry(QRect(610, 390, 111, 23));
        PBNewCamera->setStyleSheet(QLatin1String("#PBNewCamera{\n"
"color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59)}\n"
"#PBNewCamera:hover\n"
"{\n"
"background-color: rgb(39, 129, 63);\n"
"}"));
        TESearch = new QTextEdit(TCameras);
        TESearch->setObjectName(QStringLiteral("TESearch"));
        TESearch->setGeometry(QRect(20, 20, 701, 23));
        TESearch->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        TLWCameras = new QTableWidget(TCameras);
        if (TLWCameras->columnCount() < 8)
            TLWCameras->setColumnCount(8);
        TLWCameras->setObjectName(QStringLiteral("TLWCameras"));
        TLWCameras->setGeometry(QRect(20, 50, 700, 321));
        TLWCameras->setStyleSheet(QStringLiteral("selection-background-color: transparent;"));
        TLWCameras->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        TLWCameras->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TLWCameras->setEditTriggers(QAbstractItemView::DoubleClicked);
        TLWCameras->setProperty("showDropIndicator", QVariant(false));
        TLWCameras->setDragDropOverwriteMode(false);
        TLWCameras->setSelectionMode(QAbstractItemView::SingleSelection);
        TLWCameras->setSelectionBehavior(QAbstractItemView::SelectRows);
        TLWCameras->setGridStyle(Qt::DashLine);
        TLWCameras->setWordWrap(false);
        TLWCameras->setCornerButtonEnabled(false);
        TLWCameras->setColumnCount(8);
        TLWCameras->horizontalHeader()->setVisible(false);
        TLWCameras->horizontalHeader()->setDefaultSectionSize(85);
        TLWCameras->verticalHeader()->setVisible(false);
        TLWCameras->verticalHeader()->setDefaultSectionSize(50);
        LTotalNumber = new QLabel(TCameras);
        LTotalNumber->setObjectName(QStringLiteral("LTotalNumber"));
        LTotalNumber->setGeometry(QRect(20, 388, 201, 23));
        LTotalNumber->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: transparent;\n"
"font-weight:600;"));
        LTotalNumber->setIndent(0);
        LEnabledNumber = new QLabel(TCameras);
        LEnabledNumber->setObjectName(QStringLiteral("LEnabledNumber"));
        LEnabledNumber->setGeometry(QRect(290, 388, 221, 23));
        LEnabledNumber->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: transparent;\n"
"font-weight:600;"));
        LEnabledNumber->setIndent(0);
        TWMenu->addTab(TCameras, QString());
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
        PBNewCamera->setText(QApplication::translate("MainApp", "Add New Camera", Q_NULLPTR));
        TESearch->setPlaceholderText(QApplication::translate("MainApp", "Search camera", Q_NULLPTR));
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
