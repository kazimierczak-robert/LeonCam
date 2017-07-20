/********************************************************************************
** Form generated from reading UI file 'ForgotPassword.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORGOTPASSWORD_H
#define UI_FORGOTPASSWORD_H

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

class Ui_ForgotPassword
{
public:
    QLabel *label;
    QPushButton *PBBack;
    QLabel *Lloading;
    QLabel *label_2;
    QLineEdit *LSecurityQuestion;
    QLineEdit *LAnswer;
    QPushButton *PBVerify;

    void setupUi(QDialog *ForgotPassword)
    {
        if (ForgotPassword->objectName().isEmpty())
            ForgotPassword->setObjectName(QStringLiteral("ForgotPassword"));
        ForgotPassword->setWindowModality(Qt::WindowModal);
        ForgotPassword->resize(800, 500);
        ForgotPassword->setStyleSheet(QLatin1String("#ForgotPassword\n"
"{\n"
"	background-image:url(:/Resources/Images/backgroundv2.png);\n"
"	background-color: rgb(174, 213, 255);\n"
"}\n"
"\n"
"\n"
"\n"
""));
        ForgotPassword->setModal(true);
        label = new QLabel(ForgotPassword);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(250, 180, 301, 61));
        label->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59)\n"
""));
        label->setLineWidth(1);
        label->setTextFormat(Qt::AutoText);
        label->setScaledContents(false);
        PBBack = new QPushButton(ForgotPassword);
        PBBack->setObjectName(QStringLiteral("PBBack"));
        PBBack->setGeometry(QRect(250, 420, 61, 23));
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
        Lloading = new QLabel(ForgotPassword);
        Lloading->setObjectName(QStringLiteral("Lloading"));
        Lloading->setGeometry(QRect(370, 80, 61, 61));
        Lloading->setStyleSheet(QStringLiteral("background-color:none"));
        label_2 = new QLabel(ForgotPassword);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(250, 250, 161, 16));
        label_2->setStyleSheet(QLatin1String("background-color: none;\n"
"color: rgb(255, 255, 255)"));
        LSecurityQuestion = new QLineEdit(ForgotPassword);
        LSecurityQuestion->setObjectName(QStringLiteral("LSecurityQuestion"));
        LSecurityQuestion->setEnabled(false);
        LSecurityQuestion->setGeometry(QRect(250, 270, 301, 30));
        LSecurityQuestion->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        LAnswer = new QLineEdit(ForgotPassword);
        LAnswer->setObjectName(QStringLiteral("LAnswer"));
        LAnswer->setGeometry(QRect(250, 310, 301, 30));
        LAnswer->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        PBVerify = new QPushButton(ForgotPassword);
        PBVerify->setObjectName(QStringLiteral("PBVerify"));
        PBVerify->setGeometry(QRect(250, 360, 301, 30));
        PBVerify->setStyleSheet(QLatin1String("#PBVerify{\n"
"background-color: rgb(0, 69, 104);\n"
"color: rgb(255, 255, 255);}\n"
"#PBVerify:hover\n"
"{\n"
"background-color: rgb(0, 77, 116);\n"
"}"));

        retranslateUi(ForgotPassword);

        QMetaObject::connectSlotsByName(ForgotPassword);
    } // setupUi

    void retranslateUi(QDialog *ForgotPassword)
    {
        ForgotPassword->setWindowTitle(QApplication::translate("ForgotPassword", "LeoCam", Q_NULLPTR));
        label->setText(QApplication::translate("ForgotPassword", "<html><head/><body><p align=\"center\">To recover your password, answer the <span style=\" font-weight:600; color:#bdf0ff;\">Security Question </span></p><p align=\"center\">and confirm by clicking the <span style=\" font-weight:600; color:#bdf0ff;\">Verify</span> button</p></body></html>", Q_NULLPTR));
        PBBack->setText(QApplication::translate("ForgotPassword", "Back", Q_NULLPTR));
        Lloading->setText(QString());
        label_2->setText(QApplication::translate("ForgotPassword", "Security Question", Q_NULLPTR));
        LAnswer->setPlaceholderText(QApplication::translate("ForgotPassword", "Answer", Q_NULLPTR));
        PBVerify->setText(QApplication::translate("ForgotPassword", "Verify", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ForgotPassword: public Ui_ForgotPassword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORGOTPASSWORD_H
