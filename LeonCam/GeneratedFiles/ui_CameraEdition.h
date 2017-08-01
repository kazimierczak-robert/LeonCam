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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CameraEdition
{
public:
    QLineEdit *LEDescripton;
    QLineEdit *LEModel;
    QLineEdit *LEIPv4Address;
    QLabel *LTip;
    QLabel *LHelp;
    QPushButton *PBBack;
    QPushButton *PBEdit;
    QLabel *Lloading;

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
        LEDescripton->setGeometry(QRect(250, 265, 231, 21));
        LEModel = new QLineEdit(CameraEdition);
        LEModel->setObjectName(QStringLiteral("LEModel"));
        LEModel->setGeometry(QRect(250, 245, 231, 21));
        LEIPv4Address = new QLineEdit(CameraEdition);
        LEIPv4Address->setObjectName(QStringLiteral("LEIPv4Address"));
        LEIPv4Address->setGeometry(QRect(250, 285, 231, 21));
        LTip = new QLabel(CameraEdition);
        LTip->setObjectName(QStringLiteral("LTip"));
        LTip->setGeometry(QRect(510, 260, 31, 31));
        LTip->setStyleSheet(QLatin1String("#LTip{background-image: url(:/Resources/Images/bulb.png);}\n"
"#LTip:hover{background-image: url(:/Resources/Images/bulbHover.png);}"));
        LHelp = new QLabel(CameraEdition);
        LHelp->setObjectName(QStringLiteral("LHelp"));
        LHelp->setGeometry(QRect(250, 200, 301, 31));
        LHelp->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color:rgb(36, 118, 59)"));
        PBBack = new QPushButton(CameraEdition);
        PBBack->setObjectName(QStringLiteral("PBBack"));
        PBBack->setGeometry(QRect(250, 510, 61, 23));
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
        PBEdit->setGeometry(QRect(480, 510, 61, 23));
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

        retranslateUi(CameraEdition);

        QMetaObject::connectSlotsByName(CameraEdition);
    } // setupUi

    void retranslateUi(QDialog *CameraEdition)
    {
        CameraEdition->setWindowTitle(QApplication::translate("CameraEdition", "LeonCam", Q_NULLPTR));
        LEDescripton->setText(QString());
        LEDescripton->setPlaceholderText(QApplication::translate("CameraEdition", "Description", Q_NULLPTR));
        LEModel->setText(QString());
        LEModel->setPlaceholderText(QApplication::translate("CameraEdition", "Model", Q_NULLPTR));
        LEIPv4Address->setText(QString());
        LEIPv4Address->setPlaceholderText(QApplication::translate("CameraEdition", "IPv4 address", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        LTip->setToolTip(QApplication::translate("CameraEdition", "<html><head/><body><p><span style=\" font-weight:600;\">Model</span> and <span style=\" font-weight:600;\">Description</span> have <span style=\" font-weight:600;\">X</span> letters limits.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        LTip->setText(QString());
        LHelp->setText(QApplication::translate("CameraEdition", "<html><head/><body><p align=\"center\">Edit selected fields</p></body></html>", Q_NULLPTR));
        PBBack->setText(QApplication::translate("CameraEdition", "Back", Q_NULLPTR));
        PBEdit->setText(QApplication::translate("CameraEdition", "Edit", Q_NULLPTR));
        Lloading->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CameraEdition: public Ui_CameraEdition {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAEDITION_H
