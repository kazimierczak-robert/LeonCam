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
    QLabel *LSearch;
    QLineEdit *LESearch;
    QTabWidget *TWCameraPages;
    QLabel *LTotalNumber;
    QLabel *LEnabledNumber;
    QWidget *TFacesBase;
    QLabel *LHelp;
    QTableWidget *TWFacesBase;
    QLineEdit *LESearchFB;
    QLabel *LSearch_2;
    QLineEdit *LEUsername;
    QLineEdit *LESurname;
    QPushButton *PBAddPerson;
    QWidget *TReports;
    QWidget *TSettings;
    QPushButton *PBLogout;

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
        TWMenu->setGeometry(QRect(30, 30, 740, 561));
        TWMenu->setStyleSheet(QLatin1String("QTabWidget::pane {\n"
"/*background-color: rgb(221, 221, 221);*/\n"
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
        PBAddCamera->setAutoDefault(true);
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
        LHelp = new QLabel(TFacesBase);
        LHelp->setObjectName(QStringLiteral("LHelp"));
        LHelp->setGeometry(QRect(30, 30, 680, 31));
        LHelp->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(46, 147, 222);"));
        TWFacesBase = new QTableWidget(TFacesBase);
        if (TWFacesBase->columnCount() < 7)
            TWFacesBase->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        TWFacesBase->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        TWFacesBase->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        TWFacesBase->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        TWFacesBase->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        TWFacesBase->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        TWFacesBase->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        TWFacesBase->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        TWFacesBase->setObjectName(QStringLiteral("TWFacesBase"));
        TWFacesBase->setGeometry(QRect(30, 100, 705, 357));
        TWFacesBase->setFocusPolicy(Qt::NoFocus);
        TWFacesBase->setAcceptDrops(false);
        TWFacesBase->setAutoFillBackground(false);
        TWFacesBase->setStyleSheet(QLatin1String("QTableWidget\n"
"{\n"
"	color: rgb(255, 255, 255);\n"
"    alternate-background-color: rgb(53, 89, 127);\n"
"}\n"
"QHeaderView::section\n"
"{\n"
"	background-color: rgb(53, 89, 127);\n"
"	color: rgb(203, 203, 203);\n"
"}"));
        TWFacesBase->setFrameShape(QFrame::Box);
        TWFacesBase->setFrameShadow(QFrame::Sunken);
        TWFacesBase->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        TWFacesBase->setAlternatingRowColors(true);
        TWFacesBase->setSelectionMode(QAbstractItemView::NoSelection);
        TWFacesBase->setShowGrid(false);
        TWFacesBase->setGridStyle(Qt::NoPen);
        TWFacesBase->setSortingEnabled(true);
        TWFacesBase->setWordWrap(false);
        TWFacesBase->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        TWFacesBase->verticalHeader()->setVisible(false);
        TWFacesBase->verticalHeader()->setHighlightSections(false);
        LESearchFB = new QLineEdit(TFacesBase);
        LESearchFB->setObjectName(QStringLiteral("LESearchFB"));
        LESearchFB->setGeometry(QRect(30, 70, 681, 23));
        LESearchFB->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"padding-left: 22px;\n"
"border-radius: 11px;"));
        LSearch_2 = new QLabel(TFacesBase);
        LSearch_2->setObjectName(QStringLiteral("LSearch_2"));
        LSearch_2->setGeometry(QRect(29, 70, 23, 23));
        LSearch_2->setStyleSheet(QStringLiteral("background-image: url(:/Resources/Images/search.png); border: none; margin: 0px; padding: 0px;"));
        LEUsername = new QLineEdit(TFacesBase);
        LEUsername->setObjectName(QStringLiteral("LEUsername"));
        LEUsername->setGeometry(QRect(30, 480, 200, 25));
        LEUsername->setStyleSheet(QStringLiteral("background-color: rgb(234, 234, 234);"));
        LESurname = new QLineEdit(TFacesBase);
        LESurname->setObjectName(QStringLiteral("LESurname"));
        LESurname->setGeometry(QRect(240, 480, 200, 25));
        LESurname->setStyleSheet(QStringLiteral("background-color: rgb(234, 234, 234);"));
        PBAddPerson = new QPushButton(TFacesBase);
        PBAddPerson->setObjectName(QStringLiteral("PBAddPerson"));
        PBAddPerson->setGeometry(QRect(450, 480, 81, 25));
        PBAddPerson->setStyleSheet(QLatin1String("#PBAddPerson{\n"
"color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59)}\n"
"#PBAddPerson:hover\n"
"{\n"
"background-color: rgb(39, 129, 63);\n"
"}\n"
"/*border: none;\n"
"margin: 0px;\n"
"padding: 0px;*/"));
        PBAddPerson->setAutoDefault(true);
        PBAddPerson->setFlat(false);
        TWMenu->addTab(TFacesBase, QString());
        TReports = new QWidget();
        TReports->setObjectName(QStringLiteral("TReports"));
        TReports->setStyleSheet(QStringLiteral("background-color: transparent;"));
        TWMenu->addTab(TReports, QString());
        TSettings = new QWidget();
        TSettings->setObjectName(QStringLiteral("TSettings"));
        TSettings->setStyleSheet(QStringLiteral("background-color: transparent;"));
        TWMenu->addTab(TSettings, QString());
        PBLogout = new QPushButton(centralWidget);
        PBLogout->setObjectName(QStringLiteral("PBLogout"));
        PBLogout->setGeometry(QRect(750, 550, 40, 40));
        PBLogout->setStyleSheet(QLatin1String("#PBLogout\n"
"{\n"
"background-image: url(:/Resources/Images/logout.png);\n"
"border: none;\n"
"margin: 0px;\n"
"padding: 0px;}\n"
"#PBLogout:hover{background-image: url(:/Resources/Images/logoutHover.png);}\n"
""));
        PBLogout->setAutoDefault(true);
        PBLogout->setFlat(true);
        MainApp->setCentralWidget(centralWidget);
        QWidget::setTabOrder(TWMenu, LESearch);
        QWidget::setTabOrder(LESearch, TWCameraPages);
        QWidget::setTabOrder(TWCameraPages, PBAddCamera);
        QWidget::setTabOrder(PBAddCamera, LESearchFB);
        QWidget::setTabOrder(LESearchFB, TWFacesBase);
        QWidget::setTabOrder(TWFacesBase, LEUsername);
        QWidget::setTabOrder(LEUsername, LESurname);
        QWidget::setTabOrder(LESurname, PBAddPerson);
        QWidget::setTabOrder(PBAddPerson, PBLogout);

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
        LHelp->setText(QApplication::translate("MainApp", "<html><head/><body><p align=\"center\">You can sort by clicking on the table header</p></body></html>", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = TWFacesBase->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainApp", "ID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = TWFacesBase->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainApp", "Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = TWFacesBase->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainApp", "Surname", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = TWFacesBase->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainApp", "Go to the folder", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = TWFacesBase->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainApp", "Take picture", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = TWFacesBase->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainApp", "Edit", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = TWFacesBase->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainApp", "Delete", Q_NULLPTR));
        LESearchFB->setPlaceholderText(QApplication::translate("MainApp", "  Search person by Surname", Q_NULLPTR));
        LSearch_2->setText(QString());
        LEUsername->setPlaceholderText(QApplication::translate("MainApp", "Name", Q_NULLPTR));
        LESurname->setPlaceholderText(QApplication::translate("MainApp", "Surname", Q_NULLPTR));
        PBAddPerson->setText(QApplication::translate("MainApp", "Add person", Q_NULLPTR));
        TWMenu->setTabText(TWMenu->indexOf(TFacesBase), QApplication::translate("MainApp", "FACES BASE", Q_NULLPTR));
        TWMenu->setTabText(TWMenu->indexOf(TReports), QApplication::translate("MainApp", "   REPORTS", Q_NULLPTR));
        TWMenu->setTabText(TWMenu->indexOf(TSettings), QApplication::translate("MainApp", "SETTINGS", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        PBLogout->setToolTip(QApplication::translate("MainApp", "<html><head/><body><p>Log out</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBLogout->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainApp: public Ui_MainApp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINAPP_H
