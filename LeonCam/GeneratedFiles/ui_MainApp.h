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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
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
    QTableWidget *TWGreenReport;
    QPushButton *PBRedAlert;
    QLabel *LChooseAlertDelSet;
    QTableWidget *TWRedReport;
    QComboBox *CBSettings;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *VLLayout;
    QPushButton *PBGreenAlert;
    QWidget *TSettings;
    QGroupBox *GBChangePassword;
    QLineEdit *LEChangePasswordOldPassword;
    QLineEdit *LEChangePasswordPassword;
    QLineEdit *LEChangePasswordConfPass;
    QLabel *LTipPass;
    QPushButton *PBChangePassword;
    QGroupBox *GBChangeLogin;
    QLineEdit *LEChangeLoginPassword;
    QLineEdit *LEChangeLoginUsername;
    QPushButton *PBChangeLogin;
    QLabel *LTipLogin;
    QGroupBox *GBChangeSecQuestion;
    QLineEdit *LEChangeSecQuestionSecQuest;
    QLineEdit *LEChangeSecQuestionNewAnswer;
    QPushButton *PBChangeSecQuestion;
    QLineEdit *LEChangeSecQuestionPassword;
    QGroupBox *GBDeleteProfile;
    QLineEdit *LEDeleteProfilePassword;
    QPushButton *PBDeleteProfile;
    QLineEdit *LEDeleteLoginUsername;
    QLabel *LSettingsHelp;
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
        TWCameraPages->setGeometry(QRect(10, 60, 720, 440));
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
        LESearchFB->setGeometry(QRect(35, 70, 676, 23));
        LESearchFB->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"padding-left: 22px;\n"
"border-radius: 11px;"));
        LSearch_2 = new QLabel(TFacesBase);
        LSearch_2->setObjectName(QStringLiteral("LSearch_2"));
        LSearch_2->setGeometry(QRect(30, 70, 23, 23));
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
"background-color:rgb(36, 118, 59);\n"
"}\n"
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
        TWGreenReport = new QTableWidget(TReports);
        if (TWGreenReport->columnCount() < 9)
            TWGreenReport->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        TWGreenReport->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        TWGreenReport->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        TWGreenReport->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        TWGreenReport->setHorizontalHeaderItem(3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        TWGreenReport->setHorizontalHeaderItem(4, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        TWGreenReport->setHorizontalHeaderItem(5, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        TWGreenReport->setHorizontalHeaderItem(6, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        TWGreenReport->setHorizontalHeaderItem(7, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        TWGreenReport->setHorizontalHeaderItem(8, __qtablewidgetitem15);
        TWGreenReport->setObjectName(QStringLiteral("TWGreenReport"));
        TWGreenReport->setGeometry(QRect(8, 70, 641, 209));
        TWGreenReport->setFocusPolicy(Qt::NoFocus);
        TWGreenReport->setAcceptDrops(false);
        TWGreenReport->setAutoFillBackground(false);
        TWGreenReport->setStyleSheet(QLatin1String("QTableWidget\n"
"{\n"
"	color: rgb(255, 255, 255);\n"
"    alternate-background-color: /*rgb(28, 93, 45);*/rgb(53, 89, 127);\n"
"}\n"
"QHeaderView::section\n"
"{\n"
"	/*background-color: rgb(28, 93, 45);*/	\n"
"	background-color:rgb(36, 118, 59);\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        TWGreenReport->setFrameShape(QFrame::Box);
        TWGreenReport->setFrameShadow(QFrame::Sunken);
        TWGreenReport->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        TWGreenReport->setAlternatingRowColors(true);
        TWGreenReport->setSelectionMode(QAbstractItemView::NoSelection);
        TWGreenReport->setShowGrid(false);
        TWGreenReport->setGridStyle(Qt::NoPen);
        TWGreenReport->setSortingEnabled(true);
        TWGreenReport->setWordWrap(false);
        TWGreenReport->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        TWGreenReport->verticalHeader()->setVisible(false);
        TWGreenReport->verticalHeader()->setHighlightSections(false);
        PBRedAlert = new QPushButton(TReports);
        PBRedAlert->setObjectName(QStringLiteral("PBRedAlert"));
        PBRedAlert->setGeometry(QRect(10, 30, 311, 31));
        PBRedAlert->setStyleSheet(QLatin1String("#PBRedAlert{\n"
"color:rgb(255, 255, 255);\n"
"background-color: rgb(255, 77, 61);}\n"
"#PBRedAlert:hover{\n"
"background-color: rgb(255, 87, 58);\n"
"}\n"
"/*border: none;\n"
"margin: 0px;\n"
"padding: 0px;\n"
"background-color:none*/"));
        LChooseAlertDelSet = new QLabel(TReports);
        LChooseAlertDelSet->setObjectName(QStringLiteral("LChooseAlertDelSet"));
        LChooseAlertDelSet->setGeometry(QRect(650, 30, 81, 31));
        LChooseAlertDelSet->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59);"));
        TWRedReport = new QTableWidget(TReports);
        if (TWRedReport->columnCount() < 7)
            TWRedReport->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        TWRedReport->setHorizontalHeaderItem(0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        TWRedReport->setHorizontalHeaderItem(1, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        TWRedReport->setHorizontalHeaderItem(2, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        TWRedReport->setHorizontalHeaderItem(3, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        TWRedReport->setHorizontalHeaderItem(4, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        TWRedReport->setHorizontalHeaderItem(5, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        TWRedReport->setHorizontalHeaderItem(6, __qtablewidgetitem22);
        TWRedReport->setObjectName(QStringLiteral("TWRedReport"));
        TWRedReport->setGeometry(QRect(8, 70, 641, 209));
        TWRedReport->setFocusPolicy(Qt::NoFocus);
        TWRedReport->setAcceptDrops(false);
        TWRedReport->setAutoFillBackground(false);
        TWRedReport->setStyleSheet(QLatin1String("QTableWidget\n"
"{\n"
"	color: rgb(255, 255, 255);\n"
"    alternate-background-color:  /*rgb(255, 99, 85);*/rgb(53, 89, 127);\n"
"\n"
"}\n"
"QHeaderView::section\n"
"{\n"
"	background-color: rgb(255, 77, 61);\n"
"	color: rgb(255, 255, 255);\n"
"\n"
"}"));
        TWRedReport->setFrameShape(QFrame::Box);
        TWRedReport->setFrameShadow(QFrame::Sunken);
        TWRedReport->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        TWRedReport->setAlternatingRowColors(true);
        TWRedReport->setSelectionMode(QAbstractItemView::NoSelection);
        TWRedReport->setShowGrid(false);
        TWRedReport->setGridStyle(Qt::NoPen);
        TWRedReport->setSortingEnabled(true);
        TWRedReport->setWordWrap(false);
        TWRedReport->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        TWRedReport->verticalHeader()->setVisible(false);
        TWRedReport->verticalHeader()->setHighlightSections(false);
        CBSettings = new QComboBox(TReports);
        CBSettings->setObjectName(QStringLiteral("CBSettings"));
        CBSettings->setGeometry(QRect(650, 70, 81, 22));
        CBSettings->setStyleSheet(QStringLiteral("background-color: none;"));
        verticalLayoutWidget = new QWidget(TReports);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 290, 711, 211));
        VLLayout = new QVBoxLayout(verticalLayoutWidget);
        VLLayout->setSpacing(6);
        VLLayout->setContentsMargins(11, 11, 11, 11);
        VLLayout->setObjectName(QStringLiteral("VLLayout"));
        VLLayout->setContentsMargins(0, 0, 0, 0);
        PBGreenAlert = new QPushButton(TReports);
        PBGreenAlert->setObjectName(QStringLiteral("PBGreenAlert"));
        PBGreenAlert->setGeometry(QRect(330, 30, 311, 31));
        PBGreenAlert->setStyleSheet(QLatin1String("#PBGreenAlert{\n"
"color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59)}\n"
"#PBGreenAlert:hover\n"
"{\n"
"background-color: rgb(39, 129, 63);\n"
"}\n"
"/*border: none;\n"
"margin: 0px;\n"
"padding: 0px;*/"));
        PBGreenAlert->setAutoDefault(true);
        PBGreenAlert->setFlat(false);
        TWMenu->addTab(TReports, QString());
        TSettings = new QWidget();
        TSettings->setObjectName(QStringLiteral("TSettings"));
        TSettings->setStyleSheet(QStringLiteral("background-color: transparent;"));
        GBChangePassword = new QGroupBox(TSettings);
        GBChangePassword->setObjectName(QStringLiteral("GBChangePassword"));
        GBChangePassword->setGeometry(QRect(70, 230, 291, 151));
        GBChangePassword->setStyleSheet(QStringLiteral("#GBChangePassword{color: rgb(255, 255, 255);}"));
        LEChangePasswordOldPassword = new QLineEdit(GBChangePassword);
        LEChangePasswordOldPassword->setObjectName(QStringLiteral("LEChangePasswordOldPassword"));
        LEChangePasswordOldPassword->setGeometry(QRect(10, 20, 231, 25));
        LEChangePasswordOldPassword->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
""));
        LEChangePasswordOldPassword->setMaxLength(127);
        LEChangePasswordOldPassword->setEchoMode(QLineEdit::Password);
        LEChangePasswordPassword = new QLineEdit(GBChangePassword);
        LEChangePasswordPassword->setObjectName(QStringLiteral("LEChangePasswordPassword"));
        LEChangePasswordPassword->setGeometry(QRect(10, 50, 231, 25));
        LEChangePasswordPassword->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
""));
        LEChangePasswordPassword->setMaxLength(127);
        LEChangePasswordPassword->setEchoMode(QLineEdit::Password);
        LEChangePasswordConfPass = new QLineEdit(GBChangePassword);
        LEChangePasswordConfPass->setObjectName(QStringLiteral("LEChangePasswordConfPass"));
        LEChangePasswordConfPass->setGeometry(QRect(10, 80, 231, 25));
        LEChangePasswordConfPass->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
""));
        LEChangePasswordConfPass->setMaxLength(127);
        LEChangePasswordConfPass->setEchoMode(QLineEdit::Password);
        LTipPass = new QLabel(GBChangePassword);
        LTipPass->setObjectName(QStringLiteral("LTipPass"));
        LTipPass->setGeometry(QRect(250, 50, 31, 31));
        LTipPass->setStyleSheet(QLatin1String("#LTipPass{background-image: url(:/Resources/Images/bulb.png);}\n"
"#LTipPass:hover{background-image: url(:/Resources/Images/bulbHover.png);}"));
        PBChangePassword = new QPushButton(GBChangePassword);
        PBChangePassword->setObjectName(QStringLiteral("PBChangePassword"));
        PBChangePassword->setGeometry(QRect(90, 115, 100, 23));
        PBChangePassword->setStyleSheet(QLatin1String("#PBChangePassword{\n"
"color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59)}\n"
"#PBChangePassword:hover\n"
"{\n"
"background-color: rgb(39, 129, 63);\n"
"}"));
        PBChangePassword->setAutoDefault(true);
        GBChangeLogin = new QGroupBox(TSettings);
        GBChangeLogin->setObjectName(QStringLiteral("GBChangeLogin"));
        GBChangeLogin->setGeometry(QRect(70, 100, 291, 121));
        GBChangeLogin->setStyleSheet(QStringLiteral("#GBChangeLogin{color: rgb(255, 255, 255);}"));
        LEChangeLoginPassword = new QLineEdit(GBChangeLogin);
        LEChangeLoginPassword->setObjectName(QStringLiteral("LEChangeLoginPassword"));
        LEChangeLoginPassword->setGeometry(QRect(10, 50, 231, 25));
        LEChangeLoginPassword->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
""));
        LEChangeLoginPassword->setMaxLength(127);
        LEChangeLoginPassword->setEchoMode(QLineEdit::Password);
        LEChangeLoginUsername = new QLineEdit(GBChangeLogin);
        LEChangeLoginUsername->setObjectName(QStringLiteral("LEChangeLoginUsername"));
        LEChangeLoginUsername->setGeometry(QRect(10, 20, 231, 25));
        LEChangeLoginUsername->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
""));
        LEChangeLoginUsername->setMaxLength(50);
        PBChangeLogin = new QPushButton(GBChangeLogin);
        PBChangeLogin->setObjectName(QStringLiteral("PBChangeLogin"));
        PBChangeLogin->setGeometry(QRect(90, 85, 100, 23));
        PBChangeLogin->setStyleSheet(QLatin1String("#PBChangeLogin{\n"
"color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59)}\n"
"#PBChangeLogin:hover\n"
"{\n"
"background-color: rgb(39, 129, 63);\n"
"}"));
        PBChangeLogin->setAutoDefault(true);
        LTipLogin = new QLabel(GBChangeLogin);
        LTipLogin->setObjectName(QStringLiteral("LTipLogin"));
        LTipLogin->setGeometry(QRect(250, 20, 31, 31));
        LTipLogin->setStyleSheet(QLatin1String("#LTipLogin{background-image: url(:/Resources/Images/bulb.png);}\n"
"#LTipLogin:hover{background-image: url(:/Resources/Images/bulbHover.png);}"));
        GBChangeSecQuestion = new QGroupBox(TSettings);
        GBChangeSecQuestion->setObjectName(QStringLiteral("GBChangeSecQuestion"));
        GBChangeSecQuestion->setGeometry(QRect(380, 230, 291, 151));
        GBChangeSecQuestion->setStyleSheet(QStringLiteral("#GBChangeSecQuestion{color: rgb(255, 255, 255);}"));
        LEChangeSecQuestionSecQuest = new QLineEdit(GBChangeSecQuestion);
        LEChangeSecQuestionSecQuest->setObjectName(QStringLiteral("LEChangeSecQuestionSecQuest"));
        LEChangeSecQuestionSecQuest->setGeometry(QRect(10, 50, 271, 25));
        LEChangeSecQuestionSecQuest->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
""));
        LEChangeSecQuestionNewAnswer = new QLineEdit(GBChangeSecQuestion);
        LEChangeSecQuestionNewAnswer->setObjectName(QStringLiteral("LEChangeSecQuestionNewAnswer"));
        LEChangeSecQuestionNewAnswer->setGeometry(QRect(10, 80, 271, 25));
        LEChangeSecQuestionNewAnswer->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
""));
        PBChangeSecQuestion = new QPushButton(GBChangeSecQuestion);
        PBChangeSecQuestion->setObjectName(QStringLiteral("PBChangeSecQuestion"));
        PBChangeSecQuestion->setGeometry(QRect(70, 115, 141, 23));
        PBChangeSecQuestion->setStyleSheet(QLatin1String("#PBChangeSecQuestion{\n"
"color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59)}\n"
"#PBChangeSecQuestion:hover\n"
"{\n"
"background-color: rgb(39, 129, 63);\n"
"}"));
        PBChangeSecQuestion->setAutoDefault(true);
        LEChangeSecQuestionPassword = new QLineEdit(GBChangeSecQuestion);
        LEChangeSecQuestionPassword->setObjectName(QStringLiteral("LEChangeSecQuestionPassword"));
        LEChangeSecQuestionPassword->setGeometry(QRect(10, 20, 271, 25));
        LEChangeSecQuestionPassword->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
""));
        LEChangeSecQuestionPassword->setMaxLength(127);
        LEChangeSecQuestionPassword->setEchoMode(QLineEdit::Password);
        GBDeleteProfile = new QGroupBox(TSettings);
        GBDeleteProfile->setObjectName(QStringLiteral("GBDeleteProfile"));
        GBDeleteProfile->setGeometry(QRect(380, 100, 291, 121));
        GBDeleteProfile->setStyleSheet(QStringLiteral("#GBDeleteProfile{color: rgb(255, 255, 255);}"));
        LEDeleteProfilePassword = new QLineEdit(GBDeleteProfile);
        LEDeleteProfilePassword->setObjectName(QStringLiteral("LEDeleteProfilePassword"));
        LEDeleteProfilePassword->setGeometry(QRect(10, 50, 271, 25));
        LEDeleteProfilePassword->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
""));
        LEDeleteProfilePassword->setMaxLength(127);
        LEDeleteProfilePassword->setEchoMode(QLineEdit::Password);
        PBDeleteProfile = new QPushButton(GBDeleteProfile);
        PBDeleteProfile->setObjectName(QStringLiteral("PBDeleteProfile"));
        PBDeleteProfile->setGeometry(QRect(90, 85, 100, 23));
        PBDeleteProfile->setStyleSheet(QLatin1String("#PBDeleteProfile{\n"
"color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59)}\n"
"#PBDeleteProfile:hover\n"
"{\n"
"background-color: rgb(39, 129, 63);\n"
"}"));
        PBDeleteProfile->setAutoDefault(true);
        LEDeleteLoginUsername = new QLineEdit(GBDeleteProfile);
        LEDeleteLoginUsername->setObjectName(QStringLiteral("LEDeleteLoginUsername"));
        LEDeleteLoginUsername->setGeometry(QRect(10, 20, 271, 25));
        LEDeleteLoginUsername->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
""));
        LEDeleteLoginUsername->setMaxLength(50);
        LSettingsHelp = new QLabel(TSettings);
        LSettingsHelp->setObjectName(QStringLiteral("LSettingsHelp"));
        LSettingsHelp->setGeometry(QRect(30, 30, 680, 41));
        LSettingsHelp->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(46, 147, 222);"));
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
        QWidget::setTabOrder(LESearchFB, LEUsername);
        QWidget::setTabOrder(LEUsername, LESurname);
        QWidget::setTabOrder(LESurname, PBAddPerson);
        QWidget::setTabOrder(PBAddPerson, PBRedAlert);
        QWidget::setTabOrder(PBRedAlert, PBGreenAlert);
        QWidget::setTabOrder(PBGreenAlert, CBSettings);
        QWidget::setTabOrder(CBSettings, LEChangeLoginUsername);
        QWidget::setTabOrder(LEChangeLoginUsername, LEChangeLoginPassword);
        QWidget::setTabOrder(LEChangeLoginPassword, PBChangeLogin);
        QWidget::setTabOrder(PBChangeLogin, LEChangePasswordOldPassword);
        QWidget::setTabOrder(LEChangePasswordOldPassword, LEChangePasswordPassword);
        QWidget::setTabOrder(LEChangePasswordPassword, LEChangePasswordConfPass);
        QWidget::setTabOrder(LEChangePasswordConfPass, PBChangePassword);
        QWidget::setTabOrder(PBChangePassword, LEDeleteLoginUsername);
        QWidget::setTabOrder(LEDeleteLoginUsername, LEDeleteProfilePassword);
        QWidget::setTabOrder(LEDeleteProfilePassword, PBDeleteProfile);
        QWidget::setTabOrder(PBDeleteProfile, LEChangeSecQuestionPassword);
        QWidget::setTabOrder(LEChangeSecQuestionPassword, LEChangeSecQuestionSecQuest);
        QWidget::setTabOrder(LEChangeSecQuestionSecQuest, LEChangeSecQuestionNewAnswer);
        QWidget::setTabOrder(LEChangeSecQuestionNewAnswer, PBChangeSecQuestion);
        QWidget::setTabOrder(PBChangeSecQuestion, PBLogout);

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
        LEnabledNumber->setText(QApplication::translate("MainApp", "Number of enabled cameras: 0/", Q_NULLPTR));
        TWMenu->setTabText(TWMenu->indexOf(TCameras), QApplication::translate("MainApp", "CAMERAS", Q_NULLPTR));
        LHelp->setText(QApplication::translate("MainApp", "<html><head/><body><p align=\"center\">You can sort by clicking on the table header</p></body></html>", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = TWFacesBase->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainApp", "ID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = TWFacesBase->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainApp", "Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = TWFacesBase->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainApp", "Surname", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = TWFacesBase->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainApp", "Go to", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = TWFacesBase->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainApp", "Take a photo", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = TWFacesBase->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainApp", "Edit", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = TWFacesBase->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainApp", "Delete", Q_NULLPTR));
        LESearchFB->setPlaceholderText(QApplication::translate("MainApp", "Search person by Surname", Q_NULLPTR));
        LSearch_2->setText(QString());
        LEUsername->setPlaceholderText(QApplication::translate("MainApp", "Name", Q_NULLPTR));
        LESurname->setPlaceholderText(QApplication::translate("MainApp", "Surname", Q_NULLPTR));
        PBAddPerson->setText(QApplication::translate("MainApp", "Add person", Q_NULLPTR));
        TWMenu->setTabText(TWMenu->indexOf(TFacesBase), QApplication::translate("MainApp", "FACES BASE", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = TWGreenReport->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QApplication::translate("MainApp", "ID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = TWGreenReport->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QApplication::translate("MainApp", "Camera ID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = TWGreenReport->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QApplication::translate("MainApp", "FaceID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = TWGreenReport->horizontalHeaderItem(3);
        ___qtablewidgetitem10->setText(QApplication::translate("MainApp", "Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = TWGreenReport->horizontalHeaderItem(4);
        ___qtablewidgetitem11->setText(QApplication::translate("MainApp", "Surname", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = TWGreenReport->horizontalHeaderItem(5);
        ___qtablewidgetitem12->setText(QApplication::translate("MainApp", "Start date", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = TWGreenReport->horizontalHeaderItem(6);
        ___qtablewidgetitem13->setText(QApplication::translate("MainApp", "Stop date", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem14 = TWGreenReport->horizontalHeaderItem(7);
        ___qtablewidgetitem14->setText(QApplication::translate("MainApp", "Go to", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem15 = TWGreenReport->horizontalHeaderItem(8);
        ___qtablewidgetitem15->setText(QApplication::translate("MainApp", "Delete alert", Q_NULLPTR));
        PBRedAlert->setText(QApplication::translate("MainApp", "Manage and view Red Alerts", Q_NULLPTR));
        LChooseAlertDelSet->setText(QApplication::translate("MainApp", "<html><head/><body><p align=\"center\">Choose alert <br/>delete settings</p></body></html>", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem16 = TWRedReport->horizontalHeaderItem(0);
        ___qtablewidgetitem16->setText(QApplication::translate("MainApp", "ID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem17 = TWRedReport->horizontalHeaderItem(1);
        ___qtablewidgetitem17->setText(QApplication::translate("MainApp", "Camera ID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem18 = TWRedReport->horizontalHeaderItem(2);
        ___qtablewidgetitem18->setText(QApplication::translate("MainApp", "Start date", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem19 = TWRedReport->horizontalHeaderItem(3);
        ___qtablewidgetitem19->setText(QApplication::translate("MainApp", "Stop date", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem20 = TWRedReport->horizontalHeaderItem(4);
        ___qtablewidgetitem20->setText(QApplication::translate("MainApp", "Go to", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem21 = TWRedReport->horizontalHeaderItem(5);
        ___qtablewidgetitem21->setText(QApplication::translate("MainApp", "Open movie", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem22 = TWRedReport->horizontalHeaderItem(6);
        ___qtablewidgetitem22->setText(QApplication::translate("MainApp", "Delete alert and movie", Q_NULLPTR));
        PBGreenAlert->setText(QApplication::translate("MainApp", "Manage and view Green Alerts", Q_NULLPTR));
        TWMenu->setTabText(TWMenu->indexOf(TReports), QApplication::translate("MainApp", "   REPORTS", Q_NULLPTR));
        GBChangePassword->setTitle(QApplication::translate("MainApp", "Change profile password", Q_NULLPTR));
        LEChangePasswordOldPassword->setText(QString());
        LEChangePasswordOldPassword->setPlaceholderText(QApplication::translate("MainApp", "Old password", Q_NULLPTR));
        LEChangePasswordPassword->setText(QString());
        LEChangePasswordPassword->setPlaceholderText(QApplication::translate("MainApp", "New password", Q_NULLPTR));
        LEChangePasswordConfPass->setPlaceholderText(QApplication::translate("MainApp", "Confirm new password", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        LTipPass->setToolTip(QApplication::translate("MainApp", "<html><head/><body>\n"
"<span style=\"font-weight:600;\">Requirements:</span>\n"
"<ul style=\"margin-top:0px;\">\n"
"<li style=\"margin-left:-30px;\">minimum 8 characters</li>\n"
"<li style=\"margin-left:-30px;\">minimum 1 digit</li>\n"
"<li style=\"margin-left:-30px;\">minimum 1 capital letter</li>\n"
"<li style=\"margin-left:-30px;\">minimum lowercase</li>\n"
"</ul>\n"
"</body>\n"
"</html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        LTipPass->setText(QString());
        PBChangePassword->setText(QApplication::translate("MainApp", "Change password", Q_NULLPTR));
        GBChangeLogin->setTitle(QApplication::translate("MainApp", "Change profile login", Q_NULLPTR));
        LEChangeLoginPassword->setText(QString());
        LEChangeLoginPassword->setPlaceholderText(QApplication::translate("MainApp", "Password", Q_NULLPTR));
        LEChangeLoginUsername->setText(QString());
        LEChangeLoginUsername->setPlaceholderText(QApplication::translate("MainApp", "New username", Q_NULLPTR));
        PBChangeLogin->setText(QApplication::translate("MainApp", "Change login", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        LTipLogin->setToolTip(QApplication::translate("MainApp", "<html><head/><body><p><span style=\" font-weight:600;\">Username</span> has <span style=\" font-weight:600;\">50</span> letters up limit</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        LTipLogin->setText(QString());
        GBChangeSecQuestion->setTitle(QApplication::translate("MainApp", "Change profile security question", Q_NULLPTR));
        LEChangeSecQuestionSecQuest->setText(QString());
        LEChangeSecQuestionSecQuest->setPlaceholderText(QApplication::translate("MainApp", "Security Question", Q_NULLPTR));
        LEChangeSecQuestionNewAnswer->setText(QString());
        LEChangeSecQuestionNewAnswer->setPlaceholderText(QApplication::translate("MainApp", "Answer", Q_NULLPTR));
        PBChangeSecQuestion->setText(QApplication::translate("MainApp", "Change security question", Q_NULLPTR));
        LEChangeSecQuestionPassword->setText(QString());
        LEChangeSecQuestionPassword->setPlaceholderText(QApplication::translate("MainApp", "Password", Q_NULLPTR));
        GBDeleteProfile->setTitle(QApplication::translate("MainApp", "Delete profile", Q_NULLPTR));
        LEDeleteProfilePassword->setText(QString());
        LEDeleteProfilePassword->setPlaceholderText(QApplication::translate("MainApp", "Password", Q_NULLPTR));
        PBDeleteProfile->setText(QApplication::translate("MainApp", "Delete profile", Q_NULLPTR));
        LEDeleteLoginUsername->setText(QString());
        LEDeleteLoginUsername->setPlaceholderText(QApplication::translate("MainApp", "Username", Q_NULLPTR));
        LSettingsHelp->setText(QApplication::translate("MainApp", "<html><head/><body><p align=\"center\">Here you can change settings of your profile<br/>If you complete it successfully, you'll be logged out</p></body></html>", Q_NULLPTR));
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
