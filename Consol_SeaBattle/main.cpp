#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>
#include <tchar.h>
#include <vector>
using namespace std;

const int N = 10; // розмірність ігрового поля
const int numShips = 9; // розмір масиву shipsUser, shipsBot
int shipsID = 1; // змінна, яка зберігає ідентифікатор корабля, наскрізна нумерація кораблів
int ships[N] = { 0 }; // масив, який створює відповідність між номером корабля та кількістю залишившихся життів

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //Дескриптер активного вікна

												  // ДОПОМІЖНІ ФУНКЦІЇ ДЛЯ ВИКОНАННЯ ГРИ
// Клас, який зберігає кольори
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

// Функція, яка дозволяє змінювати колір тексту та фону
void setColor(Color text, Color background) {
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

// Функція, яка встановляю курсор в задані координати X та Y 
void setCursor(int X, int Y) {
	COORD setCoordinates = { X, Y };
	SetConsoleCursorPosition(hStdOut, setCoordinates);
}

//Функція, яка відображає назву гри та виводе її на екран 
void firstScreen() { 
	wchar_t const* myTitle{ L"ГРА 'МОРСЬКИЙ БІЙ'" }; // встановлення назви гри в шапці консолі
	::SetConsoleTitleW(myTitle);
	setColor(LightBlue, Black);
	cout << "ВІТАЄМО В ГРІ 'МОРСЬКИЙ БІЙ'!!! Ну що, починаємо гру...";
	Sleep(2000);
}

// Функція, яка відображає два варіанти: ГРАТИ та ПРАВИЛА ГРИ. 
// Після вибору пункту ГРАТИ можна вибрати АВТОМАТИЧНЕ або РУЧНЕ РОЗМІЩЕННЯ КОРАБЛІВ.
void secondScreen() {
	int i;
	int key = 0, key1 = 0;
	do {
		system("cls");
		cout << "1 - ПРАВИЛА" << endl;
		cout << "2 - ГРАТИ" << endl;
		cin >> key1;
		if (key1 == 1) {
			system("cls");
			cout << "«Морський бій» — гра для двох учасників, у якій гравці по черзі називають координати на невідомій їм карті суперника. Якщо у суперника в тому місці є корабель (координати зайняті), то корабель або його частина «тоне», а той, хто влучив, здобуває право зробити ще один хід. Мета гравця — першим потопити всі кораблі супротивника." << endl;
			_getch();
		}
		if (key1 == 2) {
			break;
		}
	} while (key1 != 1 || key1 != 2);//повертається до Головного меню
	system("cls");
}

													// ОСНОВНІ ФУНКЦІЇ ГРИ
													// 
// Функція атоматичної установки корабля
void automaticPlacementOfShips(int map[N][N], int NumberOfShipDecks, int shipID) {
	bool correctSetting; // булева змінна, яка повертає значення 0 або 1 в залежності від можливості розміщення корабля
	int x, y; // початкові координати поля, від якого починається зріст корабля
	int tempX, tempY; // змінні необхідні, щоб записати початкові значення x та y, щоб розміщення відбувалось по початковим координатам
	int direction = 0; // змінна, яка визначає напрямок корабля (має значення від 0 до 3)
	int countShip = 0; // змінна, яка підраховує кількість успішно встановлених кораблів
	while (countShip < 1) {
		do {
			x = rand() % N; // випадкова генерація початкових координат (від 0 до 9)
			y = rand() % N;

			tempX = x; // змінні необхідні, щоб записати початкові значення x та y, щоб розміщення відбувалось по початковим координатам
			tempY = y;

			direction = rand() % 4; // випадкова генерація напрямку розміщення корабля від 0 до 3 (4 напрямки: вверх вниз, вліво, вправо)

			correctSetting = 1;

			for (int i = 0; i < NumberOfShipDecks; i++) { // цикл, в  якому перевіряється можливість встановлення корабля в заданих межах ігрового поля
				
				if (x < 0 || y < 0 || x >= N || y >= N) { // перевірка, що координати знаходяться в межах ігрового поля
					correctSetting = 0;
					break;
				}
				if (map[x][y] >= 1 || // перевірка, чи вільні клітинки навколо обраного поля та чи вільна сама клітинка
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
				switch (direction) { // змінює координати корабля в залежності від направлення та знову перевіряється 
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
		
		if (correctSetting == 1) { //якщо перевірка пройшла, то відбувається встановлення корабля та запис значень у масив
			x = tempX; // повертаємо початкове значення змінних x та y зі змінних tempX та tempY
			y = tempY;
			for (int i = 0; i < NumberOfShipDecks; ++i) {
				map[x][y] = shipID; // записа в масив ідентифікатору корабля
				switch (direction) {
				case 0: // зліва направо
					x++;
					break;
				case 1: // зверху вниз 
					y++;
					break;
				case 2: // зправа наліво
					x--;
					break;
				case 3: // знизу вверх
					y--;
					break;
				}
			}
			countShip++;
		}
	}
}

// Функція, яка створює ігрове поле
void creatMap(int map[N][N], int maskUser[N][N], bool useMask) {
	int i, j;
	cout << " ";

	for (i = 0; i < N; i++) { // цикл, який виводе нумерацію стовпчиків
		cout << i;
	}
	cout << endl;

	for (i = 0; i < N; i++) { // цикл, який виводе нумерацію рядків
		cout << i; 
		for (j = 0; j < N; j++) {
			if (maskUser[j][i] == 1 || useMask == 0) {
				if (map[j][i] == 0) { // якщо поле пусте, виводиться "-"
					cout << "-";
				} else if (map[j][i] == -1) { // якщо значення "-1" (фнкція Shot - map[x][y] = -1;) - в полі був корабель та по ньому було ввлучено, виводиться "Х"
					cout << "X";
				} else if (map[j][i] == -2) { // клітинка, де немає корабля, але по ній здійснювався постріл, виводиться "*"
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

// Функція, яка зображує корабель на ігровому полі при ручній установці корабля
void showShip(int x, int y, int direction, int NumberOfShipDecks) { 
	int i;
	for (i = 0; i < NumberOfShipDecks; i++) {
		setCursor(x+1, y+3); // функція встановлення курсору в задані кординати
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

// Функція, яка перевіряє чи знаходиться корабель в межах ігрового поля при ручній установці корабля
bool shipOnTheMap(int x, int y, int direction, int NumberOfShipDecks) { 
	bool onMap = 1;
	for (int i = 0; i < NumberOfShipDecks; i++) { // цикл, який перевіряє, чи поміщається корабель з випадково вибраними координатами в межах поля
		if (x < 0 || y < 0 || x >= N || y >= N) { // перевірка - не виходить палуба коробля за межі поля
			onMap = 0;
			break;
		}
		switch (direction) { // змінюємо координати x та y в залежності від напрямку корабля 
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

// Функція ручної установки корабля
void manualPlacementOfShips(int map[N][N], int NumberOfShipDecks, int numShip) {
	bool correctSetting; // булеве значення, яке повертає значення 0 або 1 в залежності від можливості розміщення корабля
	int x = 0, y = 0; // початкові координати поля, від якого починається зріст корабля
	int tempX, tempY, tempDirection; // змінні необхідні, щоб записати початкові значення x та y, щоб розміщення відбувалось по початковим координатам
	int direction = 0; // змінна, яка визначає напрямок корабля (має значення від 0 до 3)
	int countShip = 0; // змінна, яка підраховує кількість успішно встановлених кораблів
	int maskUser[N][N] = { 0 };

	while (countShip < numShip) {
		system("cls");
		setColor(LightBlue, Black);
		cout << " <--- ВАШЕ ПОЛЕ ---> " << endl;
		cout << endl;
		setColor(LightGray, Black);
		creatMap(map, maskUser, 0); // вивід ігрового поля Користувача на екран
		showShip(x, y, direction, NumberOfShipDecks);
		tempX = x; // перемінні для тимчасового зберігання початкових координат корабля
		tempY = y;
		tempDirection = direction;

		int getch = _getch();
		switch (getch) { // Оброблювач подій при натисканні відповідних клавіш. Відбувається зміна направлення та координатів
		case 100: // клавіша D - вправо
			x++;
			break;
		case 115: // клавіша S - вниз
			y++;
			break;
		case 97: // клавіша A - вліво
			x--;
			break;
		case 119: // клавіша W - вверх
			y--;
			break;
		case 114: // клавіша R - поворот
			direction = !direction;
			break;
		case 13: // клавіша R - встановлення корабля
			correctSetting = 1;
			for (int i = 0; i < NumberOfShipDecks; i++) { // цикл, який перевіряє чи вільні клітинки навколо обраного поля та сама клітинка
				if (map[x][y] >= 1) {
					correctSetting = 0;
					break;
				}
				if (y < N - 1) { // чи буде змінна в межах поля, після того як зміниться на 1
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
			if (correctSetting == 1) { // перевірка, якщо можна поставити коректно корабель, ставимо
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
		if (!shipOnTheMap(x, y, direction, NumberOfShipDecks)) { // Перевірка, якщо корабель виходить за межі ігрового поля, відбувається повернення змінних до початкових значень
					x = tempX; // якщо значення false, робимо відкат змінних на момент, коли значення ще не змінилися
					y = tempY;
					direction = tempDirection;
		}
		system("cls");
	}
}

// Функція, яка здійснює постріл
int shot(int map[N][N], int x, int y, int ships[numShips + 1], int maskUser[N][N]) {
	int result = 0; // змінна, яка визначає результат пострілу
	if (map[x][y] == -1 || map[x][y] == -2) { // клітинка, по якій Бот вже стріляв
		result = 3; // Для Бота запускається додаткова генерація координат
	} else if (map[x][y] >= 1) { // якщо відбулося потрапляння в корабель
		ships[map[x][y]]--; // зменшуємо кількість життів корабля
		if (ships[map[x][y]] <= 0) { // якщо кількість життів  <= 0 - корабель знищений
			result = 2;
		} else { // в іншому випадку поранений
			result = 1;
		}
		map[x][y] = -1; // палуби корабля, по яким було влучення
	} else {
		map[x][y] = -2; // клітинки, по яким відбувся промах
	}
	maskUser[x][y] = 1;
	return result;
}

// Основна функція гри
int _tmain(int argc, _TCHAR* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	
	int i;
	int key = 0, key1 = 0;
	int map[N][N] = { 0 }; // двомірний масив 10*10 - розмір ігрового поля Користувача
	int mapBot[N][N] = { 0 }; // двомірний масив 10*10 - розмір ігрового поля Бота
	int maskUser[N][N] = { 0 }; // двомірний масив ігрового поля Користувача, який визначає, які клітинки масиву map будуть відображені, а які ні
	int maskBot[N][N] = { 0 }; // двомірний масив ігрового поля Бота, який визначає, які клітинки масиву map будуть відображені, а які ні
	int shipsUser[numShips + 1] = { 0, 4, 3, 3, 2, 2, 2, 1, 1, 1 }; // кораблі для Користувача
	int shipsBot[numShips + 1] = { 0, 4, 3, 3, 2, 2, 2, 1, 1, 1 }; // кораблі для Бота
	
	int x = 0, y = 0; // координати клітинки, по якому стріляє Користувач
	int xBot = 0, yBot = 0; // координати клітинки, по якому стріляє Бот
	int firstBotX = 0, firstBotY = 0; // координати для збереження початкового пострілу Бота
	int direction = 0; // напрямок пострілу Бота

	vector <int> dirs; // процес вибору напрямку
	dirs.push_back(3);
	dirs.push_back(2);
	dirs.push_back(1);
	dirs.push_back(0);

	bool move = 1; // змінна булевського типу, яка визначає черговість ходу Користувача та Бота
	bool winUser = 0; // змінні, які вістежують, хто переміг Користувач чи Бот
	bool winBot = 0;
	bool mode = 0; // зміна режимів
	bool changeDirection; // булева змінна для зміни напрямку "розумного" пострілу Бота

	firstScreen();
	secondScreen();

	cout << "ВИБЕРІТЬ СПОСІБ РОЗМІЩЕННЯ КОРАБЛІВ: " << endl;
	cout << "1 - АВТОМАТИЧНИЙ" << endl;
	cout << "2 - РУЧНИЙ" << endl;
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
		cout << "Виникла помилка!" << endl;
		break;
	}

	while (winUser == false && winBot == false) {
		int resultShot = 0;
		do {
			system("cls");
			setColor(LightBlue, Black);
			cout << " <--- ВАШЕ ПОЛЕ ---> " << endl;
			cout << endl;
			setColor(LightGray, Black);
			creatMap(map, maskUser, 0); // вивід ігрового поля Користувача на екран
			setColor(Red, Black);
			cout << endl;
			cout << " <--- ПОЛЕ БОТА ---> " << endl;
			cout << endl;
			setColor(LightGray, Black);
			creatMap(mapBot, maskBot, 1); // вивід ігрового поля Бота на екран

			if (move == 0) { // Постріл Користувача
				do {
					cout << "Введіть координати (стовпець від 0 до 10) = ";
					cin >> x;
					cout << "Введіть координати (рядок від 0 до 10) = ";
					cin >> y;
				} while (x < 0 || x > 9 || y < 0 || y > 9);
				resultShot = shot(mapBot, x, y, shipsBot, maskBot);

				if (resultShot == 1) {
					setColor(LightRed, Black);
					cout << "Потрапив в ціль. Не зупиняйся..." << endl;
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
					cout << "Вітаємо, корабель знищено!!!" << endl;
					setColor(White, Black);
				} else {
					cout << "Промахнувся..." << endl;
				}
			}

			if (move == 1) { // Постріл Бота
				if (mode == 0) { // 1-ий режим (випадковий постріл)
					do {
						cout << "Хід комп'ютера (стовпець від 0 до 10) = ";
						Sleep(500);
						xBot = rand() % N;
						cout << xBot << endl;
						cout << "Хід комп'ютера (рядок від 0 до 10) = ";
						Sleep(500);
						yBot = rand() % N;
						cout << yBot << endl;
						resultShot = shot(map, xBot, yBot, shipsUser, maskUser);
					} while (resultShot == 3);
					
					if (resultShot == 1) {
						mode = 1;
						firstBotX = xBot;
						firstBotY = yBot;
						if (!dirs.empty()) { // перевірка на пустоту вектора
							direction = dirs[dirs.size() - 1];
							dirs.pop_back();
						}
						setColor(LightRed, Black);
						cout << "БОТ потрапив в ціль" << endl;
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
						cout << "БОТ, знищив твій корабель !!!" << endl;
						setColor(White, Black);
					} else {
						cout << "БОТ промахнувся, видахай) " << endl;
					}
				} else if (mode == 1) { // 2-ий режим (активація "розумного пострілу" Бота, коли відбулося перше влучання і шукаємо інші палуби)
					changeDirection = 0;
					if (direction == 0) { // напрямок вліво
						if (xBot > 0) { // перевірка на межі ігрового поля
							xBot--;
						} else {
							changeDirection = 1;
						}
					} else if (direction == 1) { // напрямок вправо
						if (xBot < N - 1) { // перевірка на межі ігрового поля
							xBot++;
						} else {
							changeDirection = 1;
						}
					} else if (direction == 2) { // напрямок вверх
						if (yBot > 0) { // перевірка на межі ігрового поля
							yBot--;
						} else {
							changeDirection = 1;
						}
					} else if (direction == 3) { // напрямок вниз
						if (yBot < N - 1) { // перевірка на межі ігрового поля
							yBot++;
						} else {
							changeDirection = 1;
						}
					}
					if (changeDirection == 1) {
						if (!dirs.empty()) { // перевірка на пустоту вектора
							direction = dirs[dirs.size() - 1]; // звертаємося до останнього елемента вектора
							dirs.pop_back(); // видаляємо
						}
						xBot = firstBotX; // відновлення початкових координат
						yBot = firstBotY;
						continue;
					}
					
					resultShot = shot(map, xBot, yBot, shipsUser, maskUser);

					if (resultShot == 1) {
						setColor(LightRed, Black);
						cout << "БОТ потрапив в ціль" << endl;
						setColor(White, Black);
					} else if (resultShot == 2) {
						mode = 0;
						dirs.clear(); // повністю видаляємо склад вектора
						dirs.push_back(3); // відновлюємо склад напрямків вектора
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
						cout << "БОТ, знищив твій корабель !!!" << endl;
						setColor(White, Black);
					} else {
							if (!dirs.empty()) { // перевірка на пустоту вектора
								direction = dirs[dirs.size() - 1]; // звертаємося до останнього елемента вектора
								dirs.pop_back(); // видаляємо
							}
							xBot = firstBotX;
							yBot = firstBotY;
							cout << "БОТ промахнувся, видахай) " << endl;
					}
				}
			}
			Sleep(1000);
		} while (resultShot != 0);
		move = !move;
	}
	if (winUser == true) {
		setColor(LightMagenta, Black);
		cout << "Вітаємо, Ви перемогли в цій грі!!!" << endl;
	} else if (winBot == true) {
		setColor(LightGreen, Black);
		cout << "На жаль, БОТ переміг в цій грі..." << endl;
	}
	_getch();
	system("pause");
	return 0;
}