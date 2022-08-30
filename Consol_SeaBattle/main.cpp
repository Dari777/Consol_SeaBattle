#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>
#include <tchar.h>
#include <vector>
using namespace std;

const int N = 10; // ��������� �������� ����
const int numShips = 9; // ����� ������ shipsUser, shipsBot
int shipsID = 1; // �����, ��� ������ ������������� �������, �������� ��������� �������
int ships[N] = { 0 }; // �����, ���� ������� ���������� �� ������� ������� �� ������� ������������ �����

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //���������� ��������� ����

												  // ����̲�Ͳ ����ֲ� ��� ��������� ���
// ����, ���� ������ �������
enum Color {
	Black, 
	Blue, 
	Green, 
	Cyan, 
	Red, 
	Magenta, 
	Brown, 
	LightGray, 
	DarkGray, 
	LightBlue, 
	LightGreen, 
	LightCyan, 
	LightRed,
	LightMagenta, 
	Yellow, 
	White,
};

// �������, ��� �������� �������� ���� ������ �� ����
void setColor(Color text, Color background) {
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

// �������, ��� ���������� ������ � ����� ���������� X �� Y 
void setCursor(int X, int Y) {
	COORD setCoordinates = { X, Y };
	SetConsoleCursorPosition(hStdOut, setCoordinates);
}

//�������, ��� �������� ����� ��� �� ������ �� �� ����� 
void firstScreen() { 
	wchar_t const* myTitle{ L"��� '�������� ���'" }; // ������������ ����� ��� � ����� ������
	::SetConsoleTitleW(myTitle);
	setColor(LightBlue, Black);
	cout << "²����� � �в '�������� ���'!!! �� ��, �������� ���...";
	Sleep(2000);
}

// �������, ��� �������� ��� �������: ����� �� ������� ���. 
// ϳ��� ������ ������ ����� ����� ������� ����������� ��� ����� ���̲����� �����˲�.
void secondScreen() {
	int i;
	int key = 0, key1 = 0;
	do {
		system("cls");
		cout << "1 - �������" << endl;
		cout << "2 - �����" << endl;
		cin >> key1;
		if (key1 == 1) {
			system("cls");
			cout << "��������� �� � ��� ��� ���� ��������, � ��� ������ �� ���� ��������� ���������� �� ������� �� ���� ���������. ���� � ��������� � ���� ���� � �������� (���������� ������), �� �������� ��� ���� ������� �����, � ���, ��� ������, ������� ����� ������� �� ���� ���. ���� ������ � ������ �������� �� ������ ������������." << endl;
			_getch();
		}
		if (key1 == 2) {
			break;
		}
	} while (key1 != 1 || key1 != 2);//����������� �� ��������� ����
	system("cls");
}

													// �����Ͳ ����ֲ� ���
													// 
// ������� ���������� ��������� �������
void automaticPlacementOfShips(int map[N][N], int NumberOfShipDecks, int shipID) {
	bool correctSetting; // ������ �����, ��� ������� �������� 0 ��� 1 � ��������� �� ��������� ��������� �������
	int x, y; // �������� ���������� ����, �� ����� ���������� ���� �������
	int tempX, tempY; // ���� ��������, ��� �������� �������� �������� x �� y, ��� ��������� ���������� �� ���������� �����������
	int direction = 0; // �����, ��� ������� �������� ������� (�� �������� �� 0 �� 3)
	int countShip = 0; // �����, ��� �������� ������� ������ ������������ �������
	while (countShip < 1) {
		do {
			x = rand() % N; // ��������� ��������� ���������� ��������� (�� 0 �� 9)
			y = rand() % N;

			tempX = x; // ���� ��������, ��� �������� �������� �������� x �� y, ��� ��������� ���������� �� ���������� �����������
			tempY = y;

			direction = rand() % 4; // ��������� ��������� �������� ��������� ������� �� 0 �� 3 (4 ��������: ����� ����, ����, ������)

			correctSetting = 1;

			for (int i = 0; i < NumberOfShipDecks; i++) { // ����, �  ����� ������������ ��������� ������������ ������� � ������� ����� �������� ����
				
				if (x < 0 || y < 0 || x >= N || y >= N) { // ��������, �� ���������� ����������� � ����� �������� ����
					correctSetting = 0;
					break;
				}
				if (map[x][y] >= 1 || // ��������, �� ���� ������� ������� �������� ���� �� �� ����� ���� �������
					map[x][y + 1] >= 1 ||
					map[x][y - 1] >= 1 ||
					map[x + 1][y] >= 1 ||
					map[x + 1][y + 1] >= 1 ||
					map[x + 1][y - 1] >= 1 ||
					map[x - 1][y] >= 1 ||
					map[x - 1][y + 1] >= 1 ||
					map[x - 1][y - 1] >= 1)
				{
					correctSetting = 0;
					break;
				}
				switch (direction) { // ����� ���������� ������� � ��������� �� ����������� �� ����� ������������ 
				case 0:
					x++;
					break;
				case 1:
					y++;
					break;
				case 2:
					x--;
					break;
				case 3:
					y--;
					break;
				}
			}
		} while (correctSetting != 1);
		
		if (correctSetting == 1) { //���� �������� �������, �� ���������� ������������ ������� �� ����� ������� � �����
			x = tempX; // ��������� ��������� �������� ������ x �� y � ������ tempX �� tempY
			y = tempY;
			for (int i = 0; i < NumberOfShipDecks; ++i) {
				map[x][y] = shipID; // ������ � ����� �������������� �������
				switch (direction) {
				case 0: // ���� �������
					x++;
					break;
				case 1: // ������ ���� 
					y++;
					break;
				case 2: // ������ �����
					x--;
					break;
				case 3: // ����� �����
					y--;
					break;
				}
			}
			countShip++;
		}
	}
}

// �������, ��� ������� ������ ����
void creatMap(int map[N][N], int maskUser[N][N], bool useMask) {
	int i, j;
	cout << " ";

	for (i = 0; i < N; i++) { // ����, ���� ������ ��������� ���������
		cout << i;
	}
	cout << endl;

	for (i = 0; i < N; i++) { // ����, ���� ������ ��������� �����
		cout << i; 
		for (j = 0; j < N; j++) {
			if (maskUser[j][i] == 1 || useMask == 0) {
				if (map[j][i] == 0) { // ���� ���� �����, ���������� "-"
					cout << "-";
				} else if (map[j][i] == -1) { // ���� �������� "-1" (������ Shot - map[x][y] = -1;) - � ��� ��� �������� �� �� ����� ���� ��������, ���������� "�"
					cout << "X";
				} else if (map[j][i] == -2) { // �������, �� ���� �������, ��� �� �� ����������� ������, ���������� "*"
					cout << "*";
				} else {
					cout << map[j][i];
				}
			} else {
				cout << " ";
			}
		}
		cout << endl;
	}
}

// �������, ��� ������� �������� �� �������� ��� ��� ����� ��������� �������
void showShip(int x, int y, int direction, int NumberOfShipDecks) { 
	int i;
	for (i = 0; i < NumberOfShipDecks; i++) {
		setCursor(x+1, y+3); // ������� ������������ ������� � ����� ���������
		cout << "#";
		switch (direction) {
		case 0:
			x++;
			break;
		case 1:
			y++;
			break;
		case 2:
			x--;
			break;
		case 3:
			y--;
			break;
		}
	}
}

// �������, ��� �������� �� ����������� �������� � ����� �������� ���� ��� ����� ��������� �������
bool shipOnTheMap(int x, int y, int direction, int NumberOfShipDecks) { 
	bool onMap = 1;
	for (int i = 0; i < NumberOfShipDecks; i++) { // ����, ���� ��������, �� ��������� �������� � ��������� ��������� ������������ � ����� ����
		if (x < 0 || y < 0 || x >= N || y >= N) { // �������� - �� �������� ������ ������� �� ��� ����
			onMap = 0;
			break;
		}
		switch (direction) { // ������� ���������� x �� y � ��������� �� �������� ������� 
		case 0:
			x++;
			break;
		case 1:
			y++;
			break;
		case 2:
			x--;
			break;
		case 3:
			y--;
			break;
		}
	}
	return onMap;
}

// ������� ����� ��������� �������
void manualPlacementOfShips(int map[N][N], int NumberOfShipDecks, int numShip) {
	bool correctSetting; // ������ ��������, ��� ������� �������� 0 ��� 1 � ��������� �� ��������� ��������� �������
	int x = 0, y = 0; // �������� ���������� ����, �� ����� ���������� ���� �������
	int tempX, tempY, tempDirection; // ���� ��������, ��� �������� �������� �������� x �� y, ��� ��������� ���������� �� ���������� �����������
	int direction = 0; // �����, ��� ������� �������� ������� (�� �������� �� 0 �� 3)
	int countShip = 0; // �����, ��� �������� ������� ������ ������������ �������
	int maskUser[N][N] = { 0 };

	while (countShip < numShip) {
		system("cls");
		setColor(LightBlue, Black);
		cout << " <--- ���� ���� ---> " << endl;
		cout << endl;
		setColor(LightGray, Black);
		creatMap(map, maskUser, 0); // ���� �������� ���� ����������� �� �����
		showShip(x, y, direction, NumberOfShipDecks);
		tempX = x; // ������� ��� ����������� ��������� ���������� ��������� �������
		tempY = y;
		tempDirection = direction;

		int getch = _getch();
		switch (getch) { // ���������� ���� ��� ��������� ��������� �����. ³��������� ���� ����������� �� ����������
		case 100: // ������ D - ������
			x++;
			break;
		case 115: // ������ S - ����
			y++;
			break;
		case 97: // ������ A - ����
			x--;
			break;
		case 119: // ������ W - �����
			y--;
			break;
		case 114: // ������ R - �������
			direction = !direction;
			break;
		case 13: // ������ R - ������������ �������
			correctSetting = 1;
			for (int i = 0; i < NumberOfShipDecks; i++) { // ����, ���� �������� �� ���� ������� ������� �������� ���� �� ���� �������
				if (map[x][y] >= 1) {
					correctSetting = 0;
					break;
				}
				if (y < N - 1) { // �� ���� ����� � ����� ����, ���� ���� �� �������� �� 1
					if (map[x][y + 1] >= 1) {
						correctSetting = 0;
						break;
					}
				}
				if (y > 0) {
					if (map[x][y - 1] >= 1) {
						correctSetting = 0;
						break;
					}
				}
				if (x < N - 1) {
					if (map[x + 1][y] >= 1) {
						correctSetting = 0;
						break;
					}
				}
				if (x < N - 1 && y < N - 1) {
					if (map[x + 1][y + 1]) {
						correctSetting = 0;
						break;
					}
				}
				if (x < N - 1 && y > 0) {
					if (map[x + 1][y - 1]) {
						correctSetting = 0;
						break;
					}
				}
				if (x > 0) {
					if (map[x - 1][y] >= 1) {
						correctSetting = 0;
						break;
					}
				}
				if (x > 0 && y < N - 1) {
					if (map[x - 1][y + 1] >= 1) {
						correctSetting = 0;
						break;
					}
				}
				if (x > 0 && y > 0) {
					if (map[x - 1][y - 1] >= 1) {
						correctSetting = 0;
						break;
					}
				}
				switch (direction) {
				case 0:
					x++;
					break;
				case 1:
					y++;
					break;
				case 2:
					x--;
					break;
				case 3:
					y--;
					break;
				}
			}
			if (correctSetting == 1) { // ��������, ���� ����� ��������� �������� ��������, �������
				x = tempX;
				y = tempY;
				for (int i = 0; i < NumberOfShipDecks; i++) {
					map[x][y] = shipsID;
					switch (direction) {
					case 0:
						x++;
						break;
					case 1:
						y++;
						break;
					case 2:
						x--;
						break;
					case 3:
						y--;
						break;
					}
				}
				ships[shipsID] = NumberOfShipDecks;
				shipsID++;
				countShip++;
			}
			break;
		}
		if (!shipOnTheMap(x, y, direction, NumberOfShipDecks)) { // ��������, ���� �������� �������� �� ��� �������� ����, ���������� ���������� ������ �� ���������� �������
					x = tempX; // ���� �������� false, ������ ����� ������ �� ������, ���� �������� �� �� ��������
					y = tempY;
					direction = tempDirection;
		}
		system("cls");
	}
}

// �������, ��� ������� ������
int shot(int map[N][N], int x, int y, int ships[numShips + 1], int maskUser[N][N]) {
	int result = 0; // �����, ��� ������� ��������� �������
	if (map[x][y] == -1 || map[x][y] == -2) { // �������, �� ��� ��� ��� ������
		result = 3; // ��� ���� ����������� ��������� ��������� ���������
	} else if (map[x][y] >= 1) { // ���� �������� ����������� � ��������
		ships[map[x][y]]--; // �������� ������� ����� �������
		if (ships[map[x][y]] <= 0) { // ���� ������� �����  <= 0 - �������� ��������
			result = 2;
		} else { // � ������ ������� ���������
			result = 1;
		}
		map[x][y] = -1; // ������ �������, �� ���� ���� ��������
	} else {
		map[x][y] = -2; // �������, �� ���� ������� ������
	}
	maskUser[x][y] = 1;
	return result;
}

// ������� ������� ���
int _tmain(int argc, _TCHAR* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	
	int i;
	int key = 0, key1 = 0;
	int map[N][N] = { 0 }; // �������� ����� 10*10 - ����� �������� ���� �����������
	int mapBot[N][N] = { 0 }; // �������� ����� 10*10 - ����� �������� ���� ����
	int maskUser[N][N] = { 0 }; // �������� ����� �������� ���� �����������, ���� �������, �� ������� ������ map ������ ���������, � �� �
	int maskBot[N][N] = { 0 }; // �������� ����� �������� ���� ����, ���� �������, �� ������� ������ map ������ ���������, � �� �
	int shipsUser[numShips + 1] = { 0, 4, 3, 3, 2, 2, 2, 1, 1, 1 }; // ������ ��� �����������
	int shipsBot[numShips + 1] = { 0, 4, 3, 3, 2, 2, 2, 1, 1, 1 }; // ������ ��� ����
	
	int x = 0, y = 0; // ���������� �������, �� ����� ������ ����������
	int xBot = 0, yBot = 0; // ���������� �������, �� ����� ������ ���
	int firstBotX = 0, firstBotY = 0; // ���������� ��� ���������� ����������� ������� ����
	int direction = 0; // �������� ������� ����

	vector <int> dirs; // ������ ������ ��������
	dirs.push_back(3);
	dirs.push_back(2);
	dirs.push_back(1);
	dirs.push_back(0);

	bool move = 1; // ����� ����������� ����, ��� ������� ��������� ���� ����������� �� ����
	bool winUser = 0; // ����, �� ���������, ��� ������ ���������� �� ���
	bool winBot = 0;
	bool mode = 0; // ���� ������
	bool changeDirection; // ������ ����� ��� ���� �������� "���������" ������� ����

	firstScreen();
	secondScreen();

	cout << "����в�� ���Ѳ� ���̲����� �����˲�: " << endl;
	cout << "1 - ������������" << endl;
	cout << "2 - ������" << endl;
	cin >> key;
	system("cls");
	switch (key) {
	case 1:
		for (i = 1; i <= numShips; i++) {
			automaticPlacementOfShips(map, shipsUser[i], i);
		}
		for (i = 1; i <= numShips; i++) {
			automaticPlacementOfShips(mapBot, shipsBot[i], i);
		}
		break;
	case 2:
		manualPlacementOfShips(map, 4, 1);
		manualPlacementOfShips(map, 3, 2);
		manualPlacementOfShips(map, 2, 3);
		manualPlacementOfShips(map, 1, 3);
		for (i = 1; i <= numShips; i++) {
			automaticPlacementOfShips(mapBot, shipsBot[i], i);
		}
		break;
	default:
		cout << "������� �������!" << endl;
		break;
	}

	while (winUser == false && winBot == false) {
		int resultShot = 0;
		do {
			system("cls");
			setColor(LightBlue, Black);
			cout << " <--- ���� ���� ---> " << endl;
			cout << endl;
			setColor(LightGray, Black);
			creatMap(map, maskUser, 0); // ���� �������� ���� ����������� �� �����
			setColor(Red, Black);
			cout << endl;
			cout << " <--- ���� ���� ---> " << endl;
			cout << endl;
			setColor(LightGray, Black);
			creatMap(mapBot, maskBot, 1); // ���� �������� ���� ���� �� �����

			if (move == 0) { // ������ �����������
				do {
					cout << "������ ���������� (�������� �� 0 �� 10) = ";
					cin >> x;
					cout << "������ ���������� (����� �� 0 �� 10) = ";
					cin >> y;
				} while (x < 0 || x > 9 || y < 0 || y > 9);
				resultShot = shot(mapBot, x, y, shipsBot, maskBot);

				if (resultShot == 1) {
					setColor(LightRed, Black);
					cout << "�������� � ����. �� ���������..." << endl;
					setColor(White, Black);
				} else if (resultShot == 2) {
					bool died = 1;
					for (i = 1; i <= numShips; i++) {
						if (shipsBot[i] != 0) {
							died = 0;
							break;
						}
					}
					if (died == 1) {
						winUser = 1;
						break;
					}
					setColor(Red, Black);
					cout << "³����, �������� �������!!!" << endl;
					setColor(White, Black);
				} else {
					cout << "�����������..." << endl;
				}
			}

			if (move == 1) { // ������ ����
				if (mode == 0) { // 1-�� ����� (���������� ������)
					do {
						cout << "ճ� ����'����� (�������� �� 0 �� 10) = ";
						Sleep(500);
						xBot = rand() % N;
						cout << xBot << endl;
						cout << "ճ� ����'����� (����� �� 0 �� 10) = ";
						Sleep(500);
						yBot = rand() % N;
						cout << yBot << endl;
						resultShot = shot(map, xBot, yBot, shipsUser, maskUser);
					} while (resultShot == 3);
					
					if (resultShot == 1) {
						mode = 1;
						firstBotX = xBot;
						firstBotY = yBot;
						if (!dirs.empty()) { // �������� �� ������� �������
							direction = dirs[dirs.size() - 1];
							dirs.pop_back();
						}
						setColor(LightRed, Black);
						cout << "��� �������� � ����" << endl;
						setColor(White, Black);
					} else if (resultShot == 2) {
						bool died = 1;
						for (i = 1; i <= numShips; i++) {
							if (shipsUser[i] != 0) {
								died = 0;
								break;
							}
						}
						if (died == 1) {
							winBot = 1;
							break;
						}
						setColor(Red, Black);
						cout << "���, ������ ��� �������� !!!" << endl;
						setColor(White, Black);
					} else {
						cout << "��� �����������, �������) " << endl;
					}
				} else if (mode == 1) { // 2-�� ����� (��������� "��������� �������" ����, ���� �������� ����� �������� � ������ ���� ������)
					changeDirection = 0;
					if (direction == 0) { // �������� ����
						if (xBot > 0) { // �������� �� ��� �������� ����
							xBot--;
						} else {
							changeDirection = 1;
						}
					} else if (direction == 1) { // �������� ������
						if (xBot < N - 1) { // �������� �� ��� �������� ����
							xBot++;
						} else {
							changeDirection = 1;
						}
					} else if (direction == 2) { // �������� �����
						if (yBot > 0) { // �������� �� ��� �������� ����
							yBot--;
						} else {
							changeDirection = 1;
						}
					} else if (direction == 3) { // �������� ����
						if (yBot < N - 1) { // �������� �� ��� �������� ����
							yBot++;
						} else {
							changeDirection = 1;
						}
					}
					if (changeDirection == 1) {
						if (!dirs.empty()) { // �������� �� ������� �������
							direction = dirs[dirs.size() - 1]; // ���������� �� ���������� �������� �������
							dirs.pop_back(); // ���������
						}
						xBot = firstBotX; // ���������� ���������� ���������
						yBot = firstBotY;
						continue;
					}
					
					resultShot = shot(map, xBot, yBot, shipsUser, maskUser);

					if (resultShot == 1) {
						setColor(LightRed, Black);
						cout << "��� �������� � ����" << endl;
						setColor(White, Black);
					} else if (resultShot == 2) {
						mode = 0;
						dirs.clear(); // ������� ��������� ����� �������
						dirs.push_back(3); // ���������� ����� �������� �������
						dirs.push_back(2);
						dirs.push_back(1);
						dirs.push_back(0);
						bool died = 1;
						for (i = 1; i <= numShips; i++) {
							if (shipsUser[i] != 0) {
								died = 0;
								break;
							}
						}
						if (died == 1) {
							winBot = 1;
							break;
						}
						setColor(Red, Black);
						cout << "���, ������ ��� �������� !!!" << endl;
						setColor(White, Black);
					} else {
							if (!dirs.empty()) { // �������� �� ������� �������
								direction = dirs[dirs.size() - 1]; // ���������� �� ���������� �������� �������
								dirs.pop_back(); // ���������
							}
							xBot = firstBotX;
							yBot = firstBotY;
							cout << "��� �����������, �������) " << endl;
					}
				}
			}
			Sleep(1000);
		} while (resultShot != 0);
		move = !move;
	}
	if (winUser == true) {
		setColor(LightMagenta, Black);
		cout << "³����, �� ��������� � ��� ��!!!" << endl;
	} else if (winBot == true) {
		setColor(LightGreen, Black);
		cout << "�� ����, ��� ������ � ��� ��..." << endl;
	}
	_getch();
	system("pause");
	return 0;
}