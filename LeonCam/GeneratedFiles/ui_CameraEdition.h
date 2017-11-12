/********************************************************************************
** Form generated from reading UI file 'CameraEdition.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAEDITION_H
#define UI_CAMERAEDITION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CameraEdition
{
public:
    QLineEdit *LEDescripton;
    QLineEdit *LEIPv4Address;
    QLabel *LTip;
    QLabel *LHelp;
    QPushButton *PBBack;
    QPushButton *PBEdit;
    QLabel *Lloading;
    QLineEdit *LELogin;
    QGroupBox *GBChangePassword;
    QLineEdit *LEOldPassword;
    QLineEdit *LEPassword;
    QLineEdit *LEConfPass;

    void setupUi(QDialog *CameraEdition)
    {
        if (CameraEdition->objectName().isEmpty())
            CameraEdition->setObjectName(QStringLiteral("CameraEdition"));
        CameraEdition->setWindowModality(Qt::WindowModal);
        CameraEdition->resize(800, 600);
        CameraEdition->setStyleSheet(QStringLiteral("#CameraEdition{background-image: url(:/Resources/Images/background.png);}"));
        CameraEdition->setModal(true);
        LEDescripton = new QLineEdit(CameraEdition);
        LEDescripton->setObjectName(QStringLiteral("LEDescripton"));
        LEDescripton->setGeometry(QRect(250, 240, 251, 25));
        LEIPv4Address = new QLineEdit(CameraEdition);
        LEIPv4Address->setObjectName(QStringLiteral("LEIPv4Address"));
        LEIPv4Address->setGeometry(QRect(250, 270, 251, 25));
        LTip = new QLabel(CameraEdition);
        LTip->setObjectName(QStringLiteral("LTip"));
        LTip->setGeometry(QRect(510, 265, 31, 31));
        LTip->setStyleSheet(QLatin1String("#LTip{background-image: url(:/Resources/Images/bulb.png);}\n"
"#LTip:hover{background-image: url(:/Resources/Images/bulbHover.png);}"));
        LHelp = new QLabel(CameraEdition);
        LHelp->setObjectName(QStringLiteral("LHelp"));
        LHelp->setGeometry(QRect(250, 160, 301, 51));
        LHelp->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"/*background-color:rgb(36, 118, 59)*/\n"
"background-color: rgb(46, 147, 222);"));
        PBBack = new QPushButton(CameraEdition);
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
        PBEdit = new QPushButton(CameraEdition);
        PBEdit->setObjectName(QStringLiteral("PBEdit"));
        PBEdit->setGeometry(QRect(490, 510, 61, 25));
        PBEdit->setStyleSheet(QLatin1String("#PBEdit{\n"
"background-color: rgb(0, 69, 104);\n"
"color: rgb(255, 255, 255);}\n"
"#PBEdit:hover\n"
"{\n"
"background-color: rgb(0, 77, 116);\n"
"}\n"
"/*border: none;\n"
"margin: 0px;\n"
"padding: 0px;*/"));
        PBEdit->setFlat(false);
        Lloading = new QLabel(CameraEdition);
        Lloading->setObjectName(QStringLiteral("Lloading"));
        Lloading->setGeometry(QRect(370, 80, 61, 61));
        Lloading->setStyleSheet(QStringLiteral("background-color:none"));
        LELogin = new QLineEdit(CameraEdition);
        LELogin->setObjectName(QStringLiteral("LELogin"));
        LELogin->setGeometry(QRect(250, 300, 251, 25));
        GBChangePassword = new QGroupBox(CameraEdition);
        GBChangePassword->setObjectName(QStringLiteral("GBChangePassword"));
        GBChangePassword->setGeometry(QRect(250, 350, 251, 115));
        GBChangePassword->setStyleSheet(QStringLiteral("#GBChangePassword{color: rgb(255, 255, 255);}"));
        LEOldPassword = new QLineEdit(GBChangePassword);
        LEOldPassword->setObjectName(QStringLiteral("LEOldPassword"));
        LEOldPassword->setGeometry(QRect(10, 20, 231, 25));
        LEOldPassword->setMaxLength(127);
        LEOldPassword->setEchoMode(QLineEdit::Password);
        LEPassword = new QLineEdit(GBChangePassword);
        LEPassword->setObjectName(QStringLiteral("LEPassword"));
        LEPassword->setGeometry(QRect(10, 50, 231, 25));
        LEPassword->setMaxLength(127);
        LEPassword->setEchoMode(QLineEdit::Password);
        LEConfPass = new QLineEdit(GBChangePassword);
        LEConfPass->setObjectName(QStringLiteral("LEConfPass"));
        LEConfPass->setGeometry(QRect(10, 80, 231, 25));
        LEConfPass->setMaxLength(127);
        LEConfPass->setEchoMode(QLineEdit::Password);
        QWidget::setTabOrder(LEDescripton, LEIPv4Address);
        QWidget::setTabOrder(LEIPv4Address, LELogin);
        QWidget::setTabOrder(LELogin, LEOldPassword);
        QWidget::setTabOrder(LEOldPassword, LEPassword);
        QWidget::setTabOrder(LEPassword, LEConfPass);
        QWidget::setTabOrder(LEConfPass, PBEdit);
        QWidget::setTabOrder(PBEdit, PBBack);

        retranslateUi(CameraEdition);

        PBEdit->setDefault(true);


        QMetaObject::connectSlotsByName(CameraEdition);
    } // setupUi

    void retranslateUi(QDialog *CameraEdition)
    {
        CameraEdition->setWindowTitle(QApplication::translate("CameraEdition", "LeonCam", Q_NULLPTR));
        LEDescripton->setText(QString());
        LEDescripton->setPlaceholderText(QApplication::translate("CameraEdition", "Description", Q_NULLPTR));
        LEIPv4Address->setText(QString());
        LEIPv4Address->setPlaceholderText(QApplication::translate("CameraEdition", "IPv4 address : port number", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        LTip->setToolTip(QApplication::translate("CameraEdition", "<html><head/><body><p><span style=\" font-weight:600;\">Description</span> have <span style=\" font-weight:600;\">X</span> letters limits and must be unique.<br/>If <span style=\" font-weight:600;\">IP Address</span> is typed without port number, it takes <span style=\" font-weight:600;\">default</span> port (<span style=\" font-weight:600;\">80</span>)</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        LTip->setText(QString());
        LHelp->setText(QApplication::translate("CameraEdition", "<html><head/><body><p align=\"center\">Edit selected fields. If you do not want to change password, </p><p align=\"center\">skip <span style=\" font-weight:600; color:#bdf0ff;\">Change password</span> section!</p></body></html>", Q_NULLPTR));
        PBBack->setText(QApplication::translate("CameraEdition", "Back", Q_NULLPTR));
        PBEdit->setText(QApplication::translate("CameraEdition", "Edit", Q_NULLPTR));
        Lloading->setText(QString());
        LELogin->setText(QString());
        LELogin->setPlaceholderText(QApplication::translate("CameraEdition", "Login", Q_NULLPTR));
        GBChangePassword->setTitle(QApplication::translate("CameraEdition", "Change password", Q_NULLPTR));
        LEOldPassword->setText(QString());
        LEOldPassword->setPlaceholderText(QApplication::translate("CameraEdition", "Old password", Q_NULLPTR));
        LEPassword->setText(QString());
        LEPassword->setPlaceholderText(QApplication::translate("CameraEdition", "New password", Q_NULLPTR));
        LEConfPass->setPlaceholderText(QApplication::translate("CameraEdition", "Confirm new password", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CameraEdition: public Ui_CameraEdition {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAEDITION_H
