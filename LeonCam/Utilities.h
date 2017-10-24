#pragma once
#include <QMessageBox>
#include <qicon.h>
#include <qdesktopwidget.h>
#include "qdatetime.h"
#include "openssl-win64\include\openssl\sha.h"
#include <iomanip>
#include <sstream>
#include <QDesktopServices>
#include <QVariant>
#include <QDir>
#include <QUrl>

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>



#define iconPath ":/Resources/Images/logo.ico"
typedef unsigned char BYTE;// 8-bit byte

class Utilities
{
public:
	Utilities();
	~Utilities();
	static void MBAlarm(QString alarm, bool errorOrSuccess);
	static QString GetCurrentDateTime();

	static bool SaveToBinFile(std::string fileName, BYTE *data);
	static BYTE *ReadFromBinFile(std::string fileName);
	static int BinFileElementsNo(std::string fileName);
	static bool MBQuestion(QString nameAndSurname);
	static std::string sha256HEX(const std::string str);
	static std::string sha256(const std::string str);
	static void OpenFileExplorer(int ID);
	static void CreateFolderIfNotExists(QString path);
	static void RemoveFolderRecursively(QString path);

	static int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
		unsigned char *iv, unsigned char *plaintext);
	static int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
		unsigned char *iv, unsigned char *ciphertext);
	static std::string  GetEncrypted(std::string yourHashKey, std::string msg);
	static std::string  GetDecrypted(std::string yourHashKey, std::string encMsg);
};

