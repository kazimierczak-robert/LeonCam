#include "Utilities.h"



Utilities::Utilities()
{
}


Utilities::~Utilities()
{
}
bool Utilities::MBQuestion(QString message)
{
	//http://doc.qt.io/qt-4.8/qmessagebox.html
	QMessageBox msgBox;
	QPixmap pixmap(iconPath);
	QIcon ButtonIcon(pixmap);
	msgBox.setWindowIcon(ButtonIcon);
	msgBox.setText(message);
	//msgBox.setInformativeText(message);
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	msgBox.adjustSize();
	int result = msgBox.exec();
	if (result == QMessageBox::Yes)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Utilities::MBAlarm(QString alarm, bool errorOrSuccess)
{
	QMessageBox msgBox;
	QPixmap pixmap(iconPath);
	QIcon ButtonIcon(pixmap);
	msgBox.setWindowIcon(ButtonIcon);
	//msgBox.setStyleSheet("QPushButton{background-color: rgb(36, 118, 59);color: rgb(255, 255, 255); }QPushButton:hover{background-color: rgb(39, 129, 63);}");

	if (errorOrSuccess == true) 
	{
		msgBox.setText("<b>Success:</b> " + alarm);
	}
	else
	{
		msgBox.setText("<b>Error:</b> " + alarm);
	}
	msgBox.exec();
}
QString Utilities::GetCurrentDateTime()
{
	//get system current time
	QDateTime currentDateTime = QDateTime::currentDateTime();
	QString currentDateTimeS = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");
	return currentDateTimeS;
}


bool Utilities::SaveToBinFile(std::string fileName, BYTE *data)
{
	FILE *file = NULL;
	fopen_s(&file, fileName.c_str(), "wb");
	if (file != NULL)
	{
		fwrite(data, 1, 32, file);
	}
	else
	{
		printf("%s is corrupted!", fileName.c_str());
		fclose(file);
		return false;
	}

	fclose(file);
	return true;
}
BYTE * Utilities::ReadFromBinFile(std::string fileName)
{
	FILE *file = NULL;
	fopen_s(&file, fileName.c_str(), "rb");
	if (file != NULL)
	{
		long lSize;
		BYTE * data;
		size_t result;

		fseek(file, 0, SEEK_END);
		lSize = ftell(file);
		rewind(file);

		data = new BYTE[lSize];
		if (data != NULL)
		{
			result = fread(data, 1, lSize, file);

			if (result == lSize)
			{
				fclose(file);
				return data;
			}
			else
			{
				fclose(file);
				return NULL;
			}

		}
	}
	else
	{
		//std::cout << fileName << " is corrupted!" << std::endl;
		return NULL;
	}
}

int Utilities::BinFileElementsNo(std::string fileName)
{
	FILE *file = NULL;
	int lSize = 0;
	fopen_s(&file, fileName.c_str(), "rb");
	if (file != NULL)
	{

		BYTE * data;
		size_t result;

		fseek(file, 0, SEEK_END);
		lSize = ftell(file);

		fclose(file);
	}
	return lSize;
}
//https://stackoverflow.com/a/10632725
std::string Utilities::sha256HEX(const std::string str)
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	std::stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		ss << std::hex << std::uppercase<< std::setw(2) << std::setfill('0') << (int)hash[i];
	}
	return ss.str();
}
std::string Utilities::sha256(const std::string str)
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	std::stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		ss << hash[i];
	}
	return ss.str();
}
void Utilities::OpenFileExplorer(int ID)
{
	QString path = ".\\FaceBase\\" + QVariant(ID).toString();
	//https://stackoverflow.com/a/11517874
	QDir folder(path);
	if (!folder.exists())
	{
		folder.mkpath(".");
	}
	//https://stackoverflow.com/q/3490336
	QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}
void Utilities::CreateFolderIfNotExists(QString path)
{
	//Create Picture folder if doesn't exist
	//https://stackoverflow.com/a/11517874
	QDir folder(path);
	if (!folder.exists())
	{
		folder.mkpath(".");
	}
}
//https://stackoverflow.com/a/27758627
void Utilities::RemoveFolderRecursively(QString path)
{
	QDir dir(path);
	int result=dir.removeRecursively();
	if (result == true)
	{
		Utilities::MBAlarm("Folder " + path +" has been removed!", true);
	}
	else
	{
		Utilities::MBAlarm("Folder " + path + " hasn't been removed!", true);
	}
}
//https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
int Utilities::encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
	unsigned char *iv, unsigned char *ciphertext)
{
	EVP_CIPHER_CTX *ctx;

	int len;

	int ciphertext_len;

	/* Create and initialise the context */
	if (!(ctx = EVP_CIPHER_CTX_new()))
	{
		return -1;
	}

	/* Initialise the encryption operation. IMPORTANT - ensure you use a key
	* and IV size appropriate for your cipher
	* In this example we are using 256 bit AES (i.e. a 256 bit key). The
	* IV size for *most* modes is the same as the block size. For AES this
	* is 128 bits */
	if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
	{
		return -1;
	}

	/* Provide the message to be encrypted, and obtain the encrypted output.
	* EVP_EncryptUpdate can be called multiple times if necessary
	*/
	if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
	{
		return -1;
	}

	ciphertext_len = len;

	/* Finalise the encryption. Further ciphertext bytes may be written at
	* this stage.
	*/
	if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
	{
		return -1;
	}
	ciphertext_len += len;

	/* Clean up */
	EVP_CIPHER_CTX_free(ctx);

	return ciphertext_len;
}
//method doesn't return length because of changes in code, it rounds the value up to multiples of 8 
int Utilities::decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
	unsigned char *iv, unsigned char *plaintext)
{
	EVP_CIPHER_CTX *ctx;

	int len;

	int plaintext_len;

	/* Create and initialise the context */
	if (!(ctx = EVP_CIPHER_CTX_new()))
	{
		return -1; 
	}

	/* Initialise the decryption operation. IMPORTANT - ensure you use a key
	* and IV size appropriate for your cipher
	* In this example we are using 256 bit AES (i.e. a 256 bit key). The
	* IV size for *most* modes is the same as the block size. For AES this
	* is 128 bits */
	if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
	{
		return -1;
	}

	/* Provide the message to be decrypted, and obtain the plaintext output.
	* EVP_DecryptUpdate can be called multiple times if necessary
	*/
	if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
	{
		return -1;
	}
	plaintext_len = len;

	/* Finalise the decryption. Further plaintext bytes may be written at
	* this stage.
	*/
	EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
	/*if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
	{
		return -1;
	}*/
	plaintext_len += len;

	/* Clean up */
	EVP_CIPHER_CTX_free(ctx);

	return plaintext_len;
}
std::string Utilities::GetEncrypted(std::string yourHashKey, std::string msg)
{
	//Convert string to unsigned char *
	unsigned char *hashKey = new unsigned char[yourHashKey.length()+1];
	memcpy(hashKey, yourHashKey.c_str(), yourHashKey.length());
	hashKey[yourHashKey.length()] = '\0';

	unsigned char *mesg = new unsigned char[msg.length()+1];
	memcpy(mesg, msg.c_str(), msg.length());
	mesg[msg.length()] = '\0';

	/* A 128 bit IV */
	unsigned char *iv = new unsigned char[16];
	memcpy(iv, hashKey, 16);

	/* Buffer for ciphertext. Ensure the buffer is long enough for the
	* ciphertext which may be longer than the plaintext, dependant on the
	* algorithm and mode
	*/
	unsigned char ciphertext[128];
	int ciphertext_len;

	/* Initialise the library */
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	OPENSSL_config(NULL);

	/* Encrypt the plaintext */
	ciphertext_len = encrypt(mesg, strlen((char *)mesg) + 1, hashKey, iv,
		ciphertext);

	/* Clean up */
	EVP_cleanup();
	ERR_free_strings();
	delete iv;
	delete hashKey;
	delete mesg;

	if (ciphertext_len == -1)
	{
		Utilities::MBAlarm("Error, Encryption has failed", false);
		return "";
	}

	//Convert ciphertext to string
	//std::string ciphTmp(reinterpret_cast<char const*>(ciphertext));
	unsigned char ciphTmp[172];
	EVP_EncodeBlock((unsigned char *)ciphTmp, ciphertext, ciphertext_len);
	std::string ciphTmps(reinterpret_cast<char const*>(ciphTmp));
	return ciphTmps;
}
std::string Utilities::GetDecrypted(std::string yourHashKey, std::string encMsg)
{

	//Convert string to unsigned char *
	unsigned char *hashKey = new unsigned char[yourHashKey.length()+1];
	memcpy(hashKey, yourHashKey.c_str(), yourHashKey.length());
	hashKey[yourHashKey.length()] = '\0';

	unsigned char *encMesg64 = new unsigned char[encMsg.length()+1];
	memcpy(encMesg64, encMsg.c_str(), encMsg.length());
	encMesg64[encMsg.length()] = '\0';

	int encMsgLen = encMsg.length();
	unsigned char *encMesg=new unsigned char[encMsgLen];
	EVP_DecodeBlock(encMesg, encMesg64, strlen(reinterpret_cast<char const*>(encMesg64)));

	/* A 128 bit IV */
	unsigned char *iv = new unsigned char[16];
	memcpy(iv, hashKey, 16);

	/* Buffer for the decrypted text */
	unsigned char decryptedtext[129];
	int decryptedtext_len;
	/* Initialise the library */
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	OPENSSL_config(NULL);

	/* Decrypt the ciphertext */
	decryptedtext_len = Utilities::decrypt(encMesg, strlen((char *)encMesg), hashKey, iv, decryptedtext);

	/* Clean up */
	EVP_cleanup();
	ERR_free_strings();
	delete iv;
	delete hashKey;
	delete encMesg;

	if (decryptedtext_len == -1)
	{
		Utilities::MBAlarm("Error, Decryption has failed", false);
		return "";
	}

	/* Add a NULL terminator. We are expecting printable text */
	decryptedtext[decryptedtext_len] = '\0';

	//convert decryptedtext to string
	std::string decTmp(reinterpret_cast<char const*>(decryptedtext));
	return decTmp;
}