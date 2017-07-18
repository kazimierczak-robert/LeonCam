/********************************************************************************
** Form generated from reading UI file 'NewProfile.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPROFILE_H
#define UI_NEWPROFILE_H

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

class Ui_NewProfile
{
public:
    QLabel *Lloading;
    QLabel *label;
    QLineEdit *LUsername;
    QLineEdit *LPassword;
    QLineEdit *LConfPass;
    QLineEdit *LSecQuest;
    QLineEdit *LAnswer;
    QLabel *LTipUsername;
    QLabel *LTipPassword;
    QPushButton *PBBack;
    QPushButton *PBCreate;

    void setupUi(QDialog *NewProfile)
    {
        if (NewProfile->objectName().isEmpty())
            NewProfile->setObjectName(QStringLiteral("NewProfile"));
        NewProfile->setWindowModality(Qt::WindowModal);
        NewProfile->resize(800, 500);
        NewProfile->setStyleSheet(QLatin1String("#NewProfile{\n"
"	background-image: url(:/Resources/Images/backgroundv2.png);}"));
        Lloading = new QLabel(NewProfile);
        Lloading->setObjectName(QStringLiteral("Lloading"));
        Lloading->setGeometry(QRect(370, 80, 61, 61));
        label = new QLabel(NewProfile);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(250, 280, 301, 51));
        label->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59)"));
        LUsername = new QLineEdit(NewProfile);
        LUsername->setObjectName(QStringLiteral("LUsername"));
        LUsername->setGeometry(QRect(290, 160, 261, 30));
        LPassword = new QLineEdit(NewProfile);
        LPassword->setObjectName(QStringLiteral("LPassword"));
        LPassword->setGeometry(QRect(290, 200, 261, 30));
        LPassword->setEchoMode(QLineEdit::Password);
        LConfPass = new QLineEdit(NewProfile);
        LConfPass->setObjectName(QStringLiteral("LConfPass"));
        LConfPass->setGeometry(QRect(290, 240, 261, 30));
        LConfPass->setEchoMode(QLineEdit::Password);
        LSecQuest = new QLineEdit(NewProfile);
        LSecQuest->setObjectName(QStringLiteral("LSecQuest"));
        LSecQuest->setGeometry(QRect(250, 340, 301, 30));
        LAnswer = new QLineEdit(NewProfile);
        LAnswer->setObjectName(QStringLiteral("LAnswer"));
        LAnswer->setGeometry(QRect(250, 380, 301, 30));
        LTipUsername = new QLabel(NewProfile);
        LTipUsername->setObjectName(QStringLiteral("LTipUsername"));
        LTipUsername->setGeometry(QRect(250, 160, 31, 31));
        LTipUsername->setStyleSheet(QStringLiteral("background-image: url(:/Resources/Images/bulb.png);"));
        LTipPassword = new QLabel(NewProfile);
        LTipPassword->setObjectName(QStringLiteral("LTipPassword"));
        LTipPassword->setGeometry(QRect(250, 200, 31, 31));
        LTipPassword->setStyleSheet(QStringLiteral("background-image: url(:/Resources/Images/bulb.png);"));
        PBBack = new QPushButton(NewProfile);
        PBBack->setObjectName(QStringLiteral("PBBack"));
        PBBack->setGeometry(QRect(250, 420, 61, 23));
        PBBack->setStyleSheet(QLatin1String("color:rgb(255, 255, 255);\n"
"background-color: rgb(255, 77, 61);"));
        PBCreate = new QPushButton(NewProfile);
        PBCreate->setObjectName(QStringLiteral("PBCreate"));
        PBCreate->setGeometry(QRect(490, 420, 61, 23));
        PBCreate->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59);\n"
"data-balloon=\"Whats up!\"; data-balloon-pos=\"right\";\n"
"\n"
""));

        retranslateUi(NewProfile);

        QMetaObject::connectSlotsByName(NewProfile);
    } // setupUi

    void retranslateUi(QDialog *NewProfile)
    {
        NewProfile->setWindowTitle(QApplication::translate("NewProfile", "LeonCam", Q_NULLPTR));
        Lloading->setText(QString());
        label->setText(QApplication::translate("NewProfile", "<html><head/><body><p align=\"center\">For your protection please, type the <span style=\" font-weight:600; color:#bdf0ff;\">Security Question</span></p><p align=\"center\">and answer.This will help in future verification</p></body></html>", Q_NULLPTR));
        LUsername->setPlaceholderText(QApplication::translate("NewProfile", "Username", Q_NULLPTR));
        LPassword->setPlaceholderText(QApplication::translate("NewProfile", "Password", Q_NULLPTR));
        LConfPass->setPlaceholderText(QApplication::translate("NewProfile", "Confirm your password", Q_NULLPTR));
        LSecQuest->setPlaceholderText(QApplication::translate("NewProfile", "Security Question", Q_NULLPTR));
        LAnswer->setPlaceholderText(QApplication::translate("NewProfile", "Answer", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        LTipUsername->setToolTip(QApplication::translate("NewProfile", "<html><head/><body>\n"
"<span style=\"font-weight:600;\">Requirements:</span>\n"
"<ul style=\"margin-top:0px;\">\n"
"<li style=\"margin-left:-30px;\">minimum 8 characters</li>\n"
"</ul>\n"
"</body>\n"
"</html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        LTipUsername->setText(QString());
#ifndef QT_NO_TOOLTIP
        LTipPassword->setToolTip(QApplication::translate("NewProfile", "<html><head/><body>\n"
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
        LTipPassword->setText(QString());
        PBBack->setText(QApplication::translate("NewProfile", "Back", Q_NULLPTR));
        PBCreate->setText(QApplication::translate("NewProfile", "Create", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NewProfile: public Ui_NewProfile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPROFILE_H
