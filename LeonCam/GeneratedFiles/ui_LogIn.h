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
#include <QtWidgets/QCheckBox>
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
    QLineEdit *LUsername;
    QLineEdit *LPassword;
    QCheckBox *CBRememberMe;
    QPushButton *PBLogIn;
    QPushButton *PBForgotPassword;

    void setupUi(QMainWindow *LogInClass)
    {
        if (LogInClass->objectName().isEmpty())
            LogInClass->setObjectName(QStringLiteral("LogInClass"));
        LogInClass->resize(800, 500);
        LogInClass->setMaximumSize(QSize(800, 500));
        LogInClass->setLayoutDirection(Qt::LeftToRight);
        LogInClass->setStyleSheet(QLatin1String("#centralWidget\n"
"{\n"
"	/*background-color: rgb(174, 213, 255);*/\n"
"	background-image: url(:/Resources/Images/backgroundv2.png);\n"
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
        PBNewProfile->setGeometry(QRect(480, 420, 71, 23));
        PBNewProfile->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59)\n"
"/*border: none;\n"
"margin: 0px;\n"
"padding: 0px;*/"));
        PBNewProfile->setFlat(false);
        LUsername = new QLineEdit(centralWidget);
        LUsername->setObjectName(QStringLiteral("LUsername"));
        LUsername->setGeometry(QRect(250, 180, 301, 30));
        LUsername->setStyleSheet(QStringLiteral(""));
        LPassword = new QLineEdit(centralWidget);
        LPassword->setObjectName(QStringLiteral("LPassword"));
        LPassword->setGeometry(QRect(250, 220, 301, 30));
        LPassword->setEchoMode(QLineEdit::Password);
        CBRememberMe = new QCheckBox(centralWidget);
        CBRememberMe->setObjectName(QStringLiteral("CBRememberMe"));
        CBRememberMe->setGeometry(QRect(250, 260, 261, 21));
        CBRememberMe->setStyleSheet(QStringLiteral("color: rgb(35, 167, 255)"));
        PBLogIn = new QPushButton(centralWidget);
        PBLogIn->setObjectName(QStringLiteral("PBLogIn"));
        PBLogIn->setGeometry(QRect(250, 290, 301, 30));
        PBLogIn->setStyleSheet(QLatin1String("background-color: rgb(0, 69, 104);\n"
"color: rgb(255, 255, 255);"));
        PBLogIn->setFlat(false);
        PBForgotPassword = new QPushButton(centralWidget);
        PBForgotPassword->setObjectName(QStringLiteral("PBForgotPassword"));
        PBForgotPassword->setGeometry(QRect(250, 330, 101, 16));
        PBForgotPassword->setStyleSheet(QLatin1String("color: rgb(255, 90, 75);\n"
"border: none;\n"
"margin: 0px;\n"
"padding: 0px;"));
        PBForgotPassword->setFlat(true);
        LogInClass->setCentralWidget(centralWidget);

        retranslateUi(LogInClass);

        QMetaObject::connectSlotsByName(LogInClass);
    } // setupUi

    void retranslateUi(QMainWindow *LogInClass)
    {
        LogInClass->setWindowTitle(QApplication::translate("LogInClass", "LeonCam", Q_NULLPTR));
        Lloading->setText(QString());
        PBNewProfile->setText(QApplication::translate("LogInClass", "New profile", Q_NULLPTR));
        LUsername->setPlaceholderText(QApplication::translate("LogInClass", "Username", Q_NULLPTR));
        LPassword->setPlaceholderText(QApplication::translate("LogInClass", "Password", Q_NULLPTR));
        CBRememberMe->setText(QApplication::translate("LogInClass", "Remember me", Q_NULLPTR));
        PBLogIn->setText(QApplication::translate("LogInClass", "Log In", Q_NULLPTR));
        PBForgotPassword->setText(QApplication::translate("LogInClass", "Forgot password?", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LogInClass: public Ui_LogInClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
