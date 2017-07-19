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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainApp
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *camerasTab;
    QPushButton *newCameraButton;
    QTextBrowser *textBrowser;
    QTableWidget *camerasTable;
    QWidget *peopleBaseTab;
    QWidget *reportsTab;
    QWidget *settingsTab;
    QPushButton *logOutButton;

    void setupUi(QMainWindow *MainApp)
    {
        if (MainApp->objectName().isEmpty())
            MainApp->setObjectName(QStringLiteral("MainApp"));
        MainApp->resize(800, 500);
        MainApp->setMinimumSize(QSize(800, 500));
        MainApp->setMaximumSize(QSize(800, 500));
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
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(30, 20, 740, 461));
        tabWidget->setFocusPolicy(Qt::TabFocus);
        tabWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        tabWidget->setStyleSheet(QLatin1String("QTabWidget::pane {\n"
"border: 0px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"background-color: transparent;\n"
"color: rgb(138, 138, 207);\n"
"height: 32px;\n"
"font: 20pt \"Nirmala UI\";\n"
"width: 178px;\n"
"}\n"
"\n"
"QTabBar::tab:hover{\n"
"color: rgb(185, 185, 185);\n"
"}\n"
"\n"
"QTabBar::tab:selected{\n"
"margin-top: 1px;\n"
"color: rgb(233, 233, 233);\n"
"}\n"
""));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setUsesScrollButtons(false);
        camerasTab = new QWidget();
        camerasTab->setObjectName(QStringLiteral("camerasTab"));
        camerasTab->setStyleSheet(QStringLiteral("background-color: transparent"));
        newCameraButton = new QPushButton(camerasTab);
        newCameraButton->setObjectName(QStringLiteral("newCameraButton"));
        newCameraButton->setGeometry(QRect(602, 20, 120, 30));
        newCameraButton->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59)"));
        textBrowser = new QTextBrowser(camerasTab);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(20, 20, 560, 30));
        camerasTable = new QTableWidget(camerasTab);
        if (camerasTable->columnCount() < 8)
            camerasTable->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        camerasTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        camerasTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        camerasTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignTrailing|Qt::AlignVCenter);
        camerasTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignCenter);
        camerasTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setTextAlignment(Qt::AlignCenter);
        camerasTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setTextAlignment(Qt::AlignCenter);
        camerasTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setTextAlignment(Qt::AlignCenter);
        camerasTable->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        camerasTable->setObjectName(QStringLiteral("camerasTable"));
        camerasTable->setGeometry(QRect(20, 70, 700, 340));
        camerasTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        camerasTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        camerasTable->setEditTriggers(QAbstractItemView::DoubleClicked);
        camerasTable->setDragDropOverwriteMode(false);
        camerasTable->setSelectionMode(QAbstractItemView::SingleSelection);
        camerasTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        camerasTable->setShowGrid(true);
        camerasTable->setGridStyle(Qt::DashLine);
        camerasTable->setWordWrap(true);
        camerasTable->setCornerButtonEnabled(true);
        camerasTable->setRowCount(0);
        camerasTable->setColumnCount(8);
        camerasTable->horizontalHeader()->setVisible(false);
        camerasTable->horizontalHeader()->setCascadingSectionResizes(false);
        camerasTable->horizontalHeader()->setDefaultSectionSize(85);
        camerasTable->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        camerasTable->horizontalHeader()->setStretchLastSection(false);
        camerasTable->verticalHeader()->setVisible(false);
        camerasTable->verticalHeader()->setDefaultSectionSize(50);
        camerasTable->verticalHeader()->setStretchLastSection(false);
        tabWidget->addTab(camerasTab, QString());
        peopleBaseTab = new QWidget();
        peopleBaseTab->setObjectName(QStringLiteral("peopleBaseTab"));
        peopleBaseTab->setStyleSheet(QStringLiteral("background-color: transparent;"));
        tabWidget->addTab(peopleBaseTab, QString());
        reportsTab = new QWidget();
        reportsTab->setObjectName(QStringLiteral("reportsTab"));
        reportsTab->setStyleSheet(QStringLiteral("background-color: transparent;"));
        tabWidget->addTab(reportsTab, QString());
        settingsTab = new QWidget();
        settingsTab->setObjectName(QStringLiteral("settingsTab"));
        settingsTab->setStyleSheet(QStringLiteral("background-color: transparent;"));
        tabWidget->addTab(settingsTab, QString());
        logOutButton = new QPushButton(centralWidget);
        logOutButton->setObjectName(QStringLiteral("logOutButton"));
        logOutButton->setGeometry(QRect(740, 25, 30, 30));
        logOutButton->setStyleSheet(QLatin1String("color:rgb(255, 255, 255);\n"
"background-color: rgb(255, 77, 61);"));
        MainApp->setCentralWidget(centralWidget);

        retranslateUi(MainApp);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainApp);
    } // setupUi

    void retranslateUi(QMainWindow *MainApp)
    {
        MainApp->setWindowTitle(QApplication::translate("MainApp", "LeonCam", Q_NULLPTR));
        newCameraButton->setText(QApplication::translate("MainApp", "Add New Camera", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = camerasTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainApp", "isRunning", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = camerasTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainApp", "Preview", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = camerasTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainApp", "Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = camerasTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainApp", "Model", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = camerasTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainApp", "Patrol", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = camerasTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainApp", "Recognation", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = camerasTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainApp", "Edit", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = camerasTable->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("MainApp", "Remove", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(camerasTab), QApplication::translate("MainApp", "CAMERAS", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(peopleBaseTab), QApplication::translate("MainApp", "PEOPLE BASE", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(reportsTab), QApplication::translate("MainApp", "   REPORTS", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(settingsTab), QApplication::translate("MainApp", "SETTINGS", Q_NULLPTR));
        logOutButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainApp: public Ui_MainApp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINAPP_H
