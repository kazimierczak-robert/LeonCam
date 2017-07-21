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
        TWMenu->setFocusPolicy(Qt::TabFocus);
        TWMenu->setContextMenuPolicy(Qt::DefaultContextMenu);
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
        TWMenu->setTabPosition(QTabWidget::North);
        TWMenu->setTabShape(QTabWidget::Rounded);
        TWMenu->setElideMode(Qt::ElideNone);
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
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        TLWCameras->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        TLWCameras->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        TLWCameras->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignTrailing|Qt::AlignVCenter);
        TLWCameras->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignCenter);
        TLWCameras->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setTextAlignment(Qt::AlignCenter);
        TLWCameras->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setTextAlignment(Qt::AlignCenter);
        TLWCameras->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setTextAlignment(Qt::AlignCenter);
        TLWCameras->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        TLWCameras->setObjectName(QStringLiteral("TLWCameras"));
        TLWCameras->setGeometry(QRect(20, 50, 700, 321));
        TLWCameras->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        TLWCameras->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TLWCameras->setEditTriggers(QAbstractItemView::DoubleClicked);
        TLWCameras->setDragDropOverwriteMode(false);
        TLWCameras->setSelectionMode(QAbstractItemView::SingleSelection);
        TLWCameras->setSelectionBehavior(QAbstractItemView::SelectRows);
        TLWCameras->setShowGrid(true);
        TLWCameras->setGridStyle(Qt::DashLine);
        TLWCameras->setWordWrap(true);
        TLWCameras->setCornerButtonEnabled(true);
        TLWCameras->setRowCount(0);
        TLWCameras->setColumnCount(8);
        TLWCameras->horizontalHeader()->setVisible(false);
        TLWCameras->horizontalHeader()->setCascadingSectionResizes(false);
        TLWCameras->horizontalHeader()->setDefaultSectionSize(85);
        TLWCameras->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        TLWCameras->horizontalHeader()->setStretchLastSection(false);
        TLWCameras->verticalHeader()->setVisible(false);
        TLWCameras->verticalHeader()->setDefaultSectionSize(50);
        TLWCameras->verticalHeader()->setStretchLastSection(false);
        LTotalNumber = new QLabel(TCameras);
        LTotalNumber->setObjectName(QStringLiteral("LTotalNumber"));
        LTotalNumber->setGeometry(QRect(20, 388, 201, 23));
        LTotalNumber->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: transparent;"));
        LTotalNumber->setFrameShape(QFrame::NoFrame);
        LTotalNumber->setIndent(8);
        LEnabledNumber = new QLabel(TCameras);
        LEnabledNumber->setObjectName(QStringLiteral("LEnabledNumber"));
        LEnabledNumber->setGeometry(QRect(290, 388, 221, 23));
        LEnabledNumber->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: transparent;"));
        LEnabledNumber->setFrameShape(QFrame::NoFrame);
        LEnabledNumber->setIndent(8);
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
        QTableWidgetItem *___qtablewidgetitem = TLWCameras->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainApp", "isRunning", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = TLWCameras->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainApp", "Preview", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = TLWCameras->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainApp", "Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = TLWCameras->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainApp", "Model", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = TLWCameras->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainApp", "Patrol", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = TLWCameras->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainApp", "Recognation", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = TLWCameras->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainApp", "Edit", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = TLWCameras->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("MainApp", "Remove", Q_NULLPTR));
        LTotalNumber->setText(QApplication::translate("MainApp", "<html><head/><body><p><span style=\" font-weight:600;\">Total number of cameras: 0</span></p></body></html>", Q_NULLPTR));
        LEnabledNumber->setText(QApplication::translate("MainApp", "<html><head/><body><p><span style=\" font-weight:600;\">Number of enabled cameras: 0 </span></p></body></html>", Q_NULLPTR));
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
