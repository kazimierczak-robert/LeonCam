/********************************************************************************
** Form generated from reading UI file 'LogIn.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogInClass
{
public:
    QWidget *centralWidget;
    QLabel *Lloading;
    QPushButton *PBNewProfile;
    QLineEdit *LEUsername;
    QLineEdit *LEPassword;
    QPushButton *PBLogIn;
    QPushButton *PBForgotPassword;

    void setupUi(QMainWindow *LogInClass)
    {
        if (LogInClass->objectName().isEmpty())
            LogInClass->setObjectName(QStringLiteral("LogInClass"));
        LogInClass->resize(800, 600);
        LogInClass->setMinimumSize(QSize(800, 600));
        LogInClass->setMaximumSize(QSize(800, 600));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/Images/logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        LogInClass->setWindowIcon(icon);
        LogInClass->setLayoutDirection(Qt::LeftToRight);
        LogInClass->setStyleSheet(QLatin1String("#centralWidget\n"
"{\n"
"	/*background-color: rgb(174, 213, 255);*/\n"
"	background-image: url(:/Resources/Images/background.png);\n"
"}\n"
"\n"
"\n"
"\n"
""));
        centralWidget = new QWidget(LogInClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Lloading = new QLabel(centralWidget);
        Lloading->setObjectName(QStringLiteral("Lloading"));
        Lloading->setGeometry(QRect(370, 80, 61, 61));
        PBNewProfile = new QPushButton(centralWidget);
        PBNewProfile->setObjectName(QStringLiteral("PBNewProfile"));
        PBNewProfile->setGeometry(QRect(480, 510, 71, 25));
        PBNewProfile->setStyleSheet(QLatin1String("#PBNewProfile{\n"
"color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59)}\n"
"#PBNewProfile:hover\n"
"{\n"
"background-color: rgb(39, 129, 63);\n"
"}\n"
"/*border: none;\n"
"margin: 0px;\n"
"padding: 0px;*/"));
        PBNewProfile->setAutoDefault(true);
        PBNewProfile->setFlat(false);
        LEUsername = new QLineEdit(centralWidget);
        LEUsername->setObjectName(QStringLiteral("LEUsername"));
        LEUsername->setGeometry(QRect(250, 220, 301, 25));
        LEUsername->setStyleSheet(QStringLiteral(""));
        LEPassword = new QLineEdit(centralWidget);
        LEPassword->setObjectName(QStringLiteral("LEPassword"));
        LEPassword->setGeometry(QRect(250, 250, 301, 25));
        LEPassword->setEchoMode(QLineEdit::Password);
        PBLogIn = new QPushButton(centralWidget);
        PBLogIn->setObjectName(QStringLiteral("PBLogIn"));
        PBLogIn->setGeometry(QRect(250, 300, 301, 30));
        PBLogIn->setStyleSheet(QLatin1String("#PBLogIn{\n"
"background-color: rgb(0, 69, 104);\n"
"color: rgb(255, 255, 255);}\n"
"#PBLogIn:hover\n"
"{\n"
"background-color: rgb(0, 77, 116);\n"
"}"));
        PBLogIn->setAutoDefault(true);
        PBLogIn->setFlat(false);
        PBForgotPassword = new QPushButton(centralWidget);
        PBForgotPassword->setObjectName(QStringLiteral("PBForgotPassword"));
        PBForgotPassword->setGeometry(QRect(250, 340, 101, 16));
        PBForgotPassword->setStyleSheet(QLatin1String("#PBForgotPassword{\n"
"color: rgb(255, 90, 75);\n"
"border: none;\n"
"margin: 0px;\n"
"padding: 0px;}\n"
"#PBForgotPassword:hover\n"
"{\n"
"color: rgb(255, 122, 82);\n"
"}"));
        PBForgotPassword->setAutoDefault(true);
        PBForgotPassword->setFlat(true);
        LogInClass->setCentralWidget(centralWidget);
        QWidget::setTabOrder(LEUsername, LEPassword);
        QWidget::setTabOrder(LEPassword, PBLogIn);
        QWidget::setTabOrder(PBLogIn, PBForgotPassword);
        QWidget::setTabOrder(PBForgotPassword, PBNewProfile);

        retranslateUi(LogInClass);

        PBLogIn->setDefault(true);


        QMetaObject::connectSlotsByName(LogInClass);
    } // setupUi

    void retranslateUi(QMainWindow *LogInClass)
    {
        LogInClass->setWindowTitle(QApplication::translate("LogInClass", "LeonCam", Q_NULLPTR));
        Lloading->setText(QString());
        PBNewProfile->setText(QApplication::translate("LogInClass", "New profile", Q_NULLPTR));
        LEUsername->setPlaceholderText(QApplication::translate("LogInClass", "Username", Q_NULLPTR));
        LEPassword->setPlaceholderText(QApplication::translate("LogInClass", "Password", Q_NULLPTR));
        PBLogIn->setText(QApplication::translate("LogInClass", "Log In", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        PBForgotPassword->setToolTip(QApplication::translate("LogInClass", "To recover your password, firstly, fill your <b>Username</b>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        PBForgotPassword->setText(QApplication::translate("LogInClass", "Forgot password?", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LogInClass: public Ui_LogInClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
