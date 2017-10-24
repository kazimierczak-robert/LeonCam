/********************************************************************************
** Form generated from reading UI file 'UserCamera.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERCAMERA_H
#define UI_USERCAMERA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UserCamera
{
public:
    QLabel *Lloading;
    QLabel *LHelp;
    QComboBox *CBAvailableCameras;
    QLabel *LAvailableCameras;
    QLabel *LNewCamera;
    QLineEdit *LEIPv4Address;
    QLineEdit *LEDescripton;
    QPushButton *PBBack;
    QGroupBox *groupBox;
    QLineEdit *LELogin;
    QLineEdit *LEPassword;
    QPushButton *PBAdd;
    QLabel *LTip;
    QCheckBox *CBAssign;
    QLabel *LTipLoginPass;

    void setupUi(QDialog *UserCamera)
    {
        if (UserCamera->objectName().isEmpty())
            UserCamera->setObjectName(QStringLiteral("UserCamera"));
        UserCamera->setWindowModality(Qt::WindowModal);
        UserCamera->resize(800, 600);
        UserCamera->setMinimumSize(QSize(800, 600));
        UserCamera->setMaximumSize(QSize(800, 600));
        UserCamera->setStyleSheet(QLatin1String("#UserCamera\n"
"{\n"
"	background-image: url(:/Resources/Images/background.png);\n"
"}\n"
""));
        Lloading = new QLabel(UserCamera);
        Lloading->setObjectName(QStringLiteral("Lloading"));
        Lloading->setGeometry(QRect(370, 80, 61, 61));
        LHelp = new QLabel(UserCamera);
        LHelp->setObjectName(QStringLiteral("LHelp"));
        LHelp->setGeometry(QRect(250, 157, 301, 31));
        LHelp->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"/*background-color:rgb(36, 118, 59)*/\n"
"background-color: rgb(46, 147, 222);"));
        CBAvailableCameras = new QComboBox(UserCamera);
        CBAvailableCameras->setObjectName(QStringLiteral("CBAvailableCameras"));
        CBAvailableCameras->setGeometry(QRect(250, 217, 231, 25));
        LAvailableCameras = new QLabel(UserCamera);
        LAvailableCameras->setObjectName(QStringLiteral("LAvailableCameras"));
        LAvailableCameras->setGeometry(QRect(250, 197, 281, 16));
        LAvailableCameras->setStyleSheet(QLatin1String("background-color: none;\n"
"color: rgb(255, 255, 255)"));
        LNewCamera = new QLabel(UserCamera);
        LNewCamera->setObjectName(QStringLiteral("LNewCamera"));
        LNewCamera->setGeometry(QRect(250, 257, 261, 16));
        LNewCamera->setStyleSheet(QLatin1String("background-color: none;\n"
"color: rgb(255, 255, 255)"));
        LEIPv4Address = new QLineEdit(UserCamera);
        LEIPv4Address->setObjectName(QStringLiteral("LEIPv4Address"));
        LEIPv4Address->setGeometry(QRect(250, 307, 271, 25));
        LEIPv4Address->setMaxLength(24);
        LEDescripton = new QLineEdit(UserCamera);
        LEDescripton->setObjectName(QStringLiteral("LEDescripton"));
        LEDescripton->setGeometry(QRect(250, 277, 271, 25));
        LEDescripton->setMaxLength(24);
        PBBack = new QPushButton(UserCamera);
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
        groupBox = new QGroupBox(UserCamera);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(250, 357, 271, 75));
        LELogin = new QLineEdit(groupBox);
        LELogin->setObjectName(QStringLiteral("LELogin"));
        LELogin->setGeometry(QRect(10, 10, 251, 25));
        LELogin->setMaxLength(24);
        LEPassword = new QLineEdit(groupBox);
        LEPassword->setObjectName(QStringLiteral("LEPassword"));
        LEPassword->setGeometry(QRect(10, 40, 251, 25));
        LEPassword->setMaxLength(24);
        LEPassword->setEchoMode(QLineEdit::Password);
        PBAdd = new QPushButton(UserCamera);
        PBAdd->setObjectName(QStringLiteral("PBAdd"));
        PBAdd->setGeometry(QRect(490, 510, 61, 25));
        PBAdd->setStyleSheet(QLatin1String("#PBAdd{\n"
"color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59)}\n"
"#PBAdd:hover\n"
"{\n"
"background-color: rgb(39, 129, 63);\n"
"}\n"
"/*border: none;\n"
"margin: 0px;\n"
"padding: 0px;*/"));
        PBAdd->setFlat(false);
        LTip = new QLabel(UserCamera);
        LTip->setObjectName(QStringLiteral("LTip"));
        LTip->setGeometry(QRect(530, 290, 31, 31));
        LTip->setStyleSheet(QLatin1String("#LTip{background-image: url(:/Resources/Images/bulb.png);}\n"
"#LTip:hover{background-image: url(:/Resources/Images/bulbHover.png);}"));
        CBAssign = new QCheckBox(UserCamera);
        CBAssign->setObjectName(QStringLiteral("CBAssign"));
        CBAssign->setGeometry(QRect(490, 220, 61, 25));
        CBAssign->setStyleSheet(QLatin1String("#CBAssign{color: rgb(35, 167, 255);}\n"
"#CBAssign:hover\n"
"{\n"
"	color: rgb(89, 178, 255);\n"
"}"));
        LTipLoginPass = new QLabel(UserCamera);
        LTipLoginPass->setObjectName(QStringLiteral("LTipLoginPass"));
        LTipLoginPass->setGeometry(QRect(530, 380, 31, 31));
        LTipLoginPass->setStyleSheet(QLatin1String("#LTipLoginPass{background-image: url(:/Resources/Images/bulb.png);}\n"
"#LTipLoginPass:hover{background-image: url(:/Resources/Images/bulbHover.png);}"));
        QWidget::setTabOrder(CBAvailableCameras, CBAssign);
        QWidget::setTabOrder(CBAssign, LEDescripton);
        QWidget::setTabOrder(LEDescripton, LEIPv4Address);
        QWidget::setTabOrder(LEIPv4Address, LELogin);
        QWidget::setTabOrder(LELogin, LEPassword);
        QWidget::setTabOrder(LEPassword, PBAdd);
        QWidget::setTabOrder(PBAdd, PBBack);

        retranslateUi(UserCamera);

        PBAdd->setDefault(true);


        QMetaObject::connectSlotsByName(UserCamera);
    } // setupUi

    void retranslateUi(QDialog *UserCamera)
    {
        UserCamera->setWindowTitle(QApplication::translate("UserCamera", "LeonCam", Q_NULLPTR));
        Lloading->setText(QString());
        LHelp->setText(QApplication::translate("UserCamera", "<html><head/><body><p align=\"center\">Assign from available or define a new one</p></body></html>", Q_NULLPTR));
        LAvailableCameras->setText(QApplication::translate("UserCamera", "<html><head/><body><p>Cameras from Data Base <span style=\" font-weight:600; color:#fe7e5d;\">not assigned</span> to your account</p></body></html>", Q_NULLPTR));
        LNewCamera->setText(QApplication::translate("UserCamera", "<html><head/><body><p>Define <span style=\" font-weight:600; color:#fe7e5d;\">New Camera</span></p></body></html>", Q_NULLPTR));
        LEIPv4Address->setText(QString());
        LEIPv4Address->setPlaceholderText(QApplication::translate("UserCamera", "IPv4 address", Q_NULLPTR));
        LEDescripton->setText(QString());
        LEDescripton->setPlaceholderText(QApplication::translate("UserCamera", "Description", Q_NULLPTR));
        PBBack->setText(QApplication::translate("UserCamera", "Back", Q_NULLPTR));
        groupBox->setTitle(QString());
        LELogin->setText(QString());
        LELogin->setPlaceholderText(QApplication::translate("UserCamera", "Login", Q_NULLPTR));
        LEPassword->setText(QString());
        LEPassword->setPlaceholderText(QApplication::translate("UserCamera", "Password", Q_NULLPTR));
        PBAdd->setText(QApplication::translate("UserCamera", "Add", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        LTip->setToolTip(QApplication::translate("UserCamera", "<html><head/><body><p><span style=\" font-weight:600;\">Description</span> have <span style=\" font-weight:600;\">X</span> letters limits and must be unique</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        LTip->setText(QString());
        CBAssign->setText(QApplication::translate("UserCamera", "Assign", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        LTipLoginPass->setToolTip(QApplication::translate("UserCamera", "<html><head/><body><p><span style=\" font-weight:600;\">Login</span> and <span style=\" font-weight:600;\">Password</span> must be filled.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        LTipLoginPass->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UserCamera: public Ui_UserCamera {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERCAMERA_H
