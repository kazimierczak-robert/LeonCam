/********************************************************************************
** Form generated from reading UI file 'ForgottenPassword.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORGOTTENPASSWORD_H
#define UI_FORGOTTENPASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ForgottenPassword
{
public:
    QLabel *LHelp;
    QPushButton *PBBack;
    QLabel *Lloading;
    QLabel *LSecurityQuestion;
    QLineEdit *LESecurityQuestion;
    QLineEdit *LEAnswer;
    QPushButton *PBVerify;

    void setupUi(QDialog *ForgottenPassword)
    {
        if (ForgottenPassword->objectName().isEmpty())
            ForgottenPassword->setObjectName(QStringLiteral("ForgottenPassword"));
        ForgottenPassword->setWindowModality(Qt::WindowModal);
        ForgottenPassword->resize(800, 600);
        ForgottenPassword->setMinimumSize(QSize(800, 600));
        ForgottenPassword->setMaximumSize(QSize(800, 600));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/Images/logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ForgottenPassword->setWindowIcon(icon);
        ForgottenPassword->setStyleSheet(QLatin1String("#ForgottenPassword\n"
"{\n"
"	background-image:url(:/Resources/Images/background.png);\n"
"	background-color: rgb(174, 213, 255);\n"
"}\n"
"\n"
"\n"
"\n"
""));
        ForgottenPassword->setModal(true);
        LHelp = new QLabel(ForgottenPassword);
        LHelp->setObjectName(QStringLiteral("LHelp"));
        LHelp->setGeometry(QRect(250, 210, 301, 61));
        LHelp->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"/*background-color:rgb(36, 118, 59)*/\n"
"background-color: rgb(46, 147, 222);\n"
""));
        LHelp->setLineWidth(1);
        LHelp->setTextFormat(Qt::AutoText);
        LHelp->setScaledContents(false);
        PBBack = new QPushButton(ForgottenPassword);
        PBBack->setObjectName(QStringLiteral("PBBack"));
        PBBack->setGeometry(QRect(250, 510, 61, 25));
        PBBack->setStyleSheet(QLatin1String("#PBBack{\n"
"color:rgb(255, 255, 255);\n"
"background-color: rgb(255, 77, 61);}\n"
"#PBBack:hover{\n"
"background-color: rgb(255, 87, 58);\n"
"}\n"
"/*border: none;\n"
"margin: 0px;\n"
"padding: 0px;\n"
"background-color:none*/"));
        Lloading = new QLabel(ForgottenPassword);
        Lloading->setObjectName(QStringLiteral("Lloading"));
        Lloading->setGeometry(QRect(370, 80, 61, 61));
        Lloading->setStyleSheet(QStringLiteral("background-color:none"));
        LSecurityQuestion = new QLabel(ForgottenPassword);
        LSecurityQuestion->setObjectName(QStringLiteral("LSecurityQuestion"));
        LSecurityQuestion->setGeometry(QRect(250, 280, 161, 16));
        LSecurityQuestion->setStyleSheet(QLatin1String("background-color: none;\n"
"color: rgb(255, 255, 255)"));
        LESecurityQuestion = new QLineEdit(ForgottenPassword);
        LESecurityQuestion->setObjectName(QStringLiteral("LESecurityQuestion"));
        LESecurityQuestion->setEnabled(false);
        LESecurityQuestion->setGeometry(QRect(250, 300, 301, 25));
        LESecurityQuestion->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        LEAnswer = new QLineEdit(ForgottenPassword);
        LEAnswer->setObjectName(QStringLiteral("LEAnswer"));
        LEAnswer->setGeometry(QRect(250, 330, 301, 25));
        LEAnswer->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        PBVerify = new QPushButton(ForgottenPassword);
        PBVerify->setObjectName(QStringLiteral("PBVerify"));
        PBVerify->setGeometry(QRect(250, 380, 301, 30));
        PBVerify->setStyleSheet(QLatin1String("#PBVerify{\n"
"background-color: rgb(0, 69, 104);\n"
"color: rgb(255, 255, 255);}\n"
"#PBVerify:hover\n"
"{\n"
"background-color: rgb(0, 77, 116);\n"
"}"));
        QWidget::setTabOrder(LESecurityQuestion, LEAnswer);
        QWidget::setTabOrder(LEAnswer, PBVerify);
        QWidget::setTabOrder(PBVerify, PBBack);

        retranslateUi(ForgottenPassword);

        PBVerify->setDefault(true);


        QMetaObject::connectSlotsByName(ForgottenPassword);
    } // setupUi

    void retranslateUi(QDialog *ForgottenPassword)
    {
        ForgottenPassword->setWindowTitle(QApplication::translate("ForgottenPassword", "LeonCam", Q_NULLPTR));
        LHelp->setText(QApplication::translate("ForgottenPassword", "<html><head/><body><p align=\"center\">To recover your password, answer the <span style=\" font-weight:600; color:#bdf0ff;\">Security Question </span></p><p align=\"center\">and confirm by clicking the <span style=\" font-weight:600; color:#bdf0ff;\">Verify</span> button</p></body></html>", Q_NULLPTR));
        PBBack->setText(QApplication::translate("ForgottenPassword", "Back", Q_NULLPTR));
        Lloading->setText(QString());
        LSecurityQuestion->setText(QApplication::translate("ForgottenPassword", "Security Question", Q_NULLPTR));
        LEAnswer->setPlaceholderText(QApplication::translate("ForgottenPassword", "Answer", Q_NULLPTR));
        PBVerify->setText(QApplication::translate("ForgottenPassword", "Verify", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ForgottenPassword: public Ui_ForgottenPassword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORGOTTENPASSWORD_H
