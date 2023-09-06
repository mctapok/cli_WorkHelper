#include <iostream>
#include <random>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
//update encoding utf-8

int generateRandomNumber(int min_value, int max_value) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min_value, max_value);
	return dis(gen);
}
void programMenu() {
	std::cout << "1 прочитать данные из файла ?\n";
	std::cout << "2 заполнить данные вручную ?\n";
	std::cout << "q выход\n";
}


int regexVerify(std::string input) {
	if (std::regex_match(input, std::regex("\\d+\\.\\d+ \\d+\\.\\d+ \\d+\\.\\d+ \\d+ \\d+ \\d+\\n"))) {
		return 1;
	}
	else if (std::regex_match(input, std::regex("\\d+\\.\\d+ - - \\d+ - -\\n"))) {
		return 2;
	}
	else if (std::regex_match(input, std::regex("- \\d+\\.\\d+ - - \\d+ -\\n"))) {
		return 3;
	}
	else if (std::regex_match(input, std::regex("- - \\d+\\.\\d+ - - \\d+\\n"))) {
		return 4;
	}
	else {
		std::cout << "некорректный вид строки" << std::endl;
	}
}

//set structure
struct NumberSet
{
	double a, b, c;
	int A, B, C;
};

NumberSet generateNumberSet(int min_range, int max_range) {
	NumberSet set;

	set.A = generateRandomNumber(min_range, max_range);
	set.B = std::min(set.A + generateRandomNumber(1, 3), max_range);
	set.C = std::min(set.B + generateRandomNumber(1, 3), max_range);

	set.a = 230.0 / set.A;
	set.b = 230.0 / set.B;
	set.c = 230.0 / set.C;

	return set;
}


int main() {
	setlocale(LC_ALL, "Russian");
	int min_range, max_range;
	int num_count;
	char repeat;
	char conductor;
	char optionMenu;
	std::string filePath;


	do {
		system("cls");
		programMenu();
		std::cin >> optionMenu;

		if (optionMenu == '1') {
			std::ifstream myFile;
			while (optionMenu != 'n') {
				std::cout << "введите путь к файлу: ";
				std::cin >> filePath;
				myFile.open(filePath);
				if (!myFile.is_open()) {
					std::cerr << "Не удалось открыть файл " << filePath << std::endl;
					std::cout << "хотите попробовать снова ? (y/n) ";
					std::cin >> optionMenu;
				}
				else break;		
			}

			std::string line;

			int automaticCurrent;//ток выключателя в файле
			int polusCount; //число полюсов
			int triggerCurrent;//ток кз

			std::string lastString = "0.0 0.0 0.0 0 0 0\n"; //строка выведеная в консоль
			int typeOfString;

			while (std::getline(myFile, line)) {
				std::istringstream iss(line);
				std::string firstPart, secondPart, thirdPart;

				// Извлекаем части из строки
				if (std::getline(iss, firstPart, '-') &&
					std::getline(iss, secondPart, ' ') &&
					std::getline(iss, thirdPart)) {
					try {
						automaticCurrent = std::stoi(secondPart);
						polusCount = std::stoi(thirdPart);
					}
					catch (const std::invalid_argument& e) {
						std::cerr << "Ошибка: Некорректный формат чисел" << std::endl;
					}
				}
				else {
					std::cerr << "Ошибка: Не удалось извлечь части из строки" << std::endl;
				}
				/*
					triggerCurrent это значение тока, для генерации разных чисел требуется диапазон значений

					для задачи диапазона будем использовать формулу
					min_range = triggerCurrent - (triggerCurrent * 0.3),
					max_range = triggerCurrent + (triggerCurrent * 0.3)
				*/

				triggerCurrent = automaticCurrent * generateRandomNumber(3, 6); //вычислили ток кз

				//установили диапазон
				min_range = triggerCurrent - (triggerCurrent * 0.3);
				max_range = triggerCurrent + (triggerCurrent * 0.3);

				//создали набор
				NumberSet set = generateNumberSet(min_range, max_range);
				std::stringstream capturedStream;//поток вывода в консоль

				if (polusCount == 3) {
					std::cout
						<< std::fixed << std::setprecision(2) << set.a << " " << std::fixed << std::setprecision(2) << set.b << " " << std::fixed << std::setprecision(2) << set.c
						<< " " << set.A << " " << set.B << " " << set.C << "\n";
					capturedStream << std::fixed << std::setprecision(2) << set.a << " " << std::fixed << std::setprecision(2) << set.b << " " << std::fixed << std::setprecision(2) << set.c
						<< " " << set.A << " " << set.B << " " << set.C << "\n";

					lastString = capturedStream.str();

				}

				if (polusCount == 1) {
					typeOfString = regexVerify(lastString);
					if (typeOfString == 1 || typeOfString == 4) {
						std::cout
							<< std::fixed << std::setprecision(2) << set.a << " " << "-" << " " << "-" << " " << set.A << " " << "-" << " " << "-\n";

						capturedStream << std::fixed << std::setprecision(2) << set.a << " " << "-" << " " << "-"
							<< " " << set.A << " " << "-" << " " << "-\n";
						lastString = capturedStream.str();

					}
					else if (typeOfString == 2) {

						std::cout
							<< "-" << " " << std::fixed << std::setprecision(2) << set.b << " " << "-"
							<< " " << "-" << " " << set.B << " " << "-\n";
						capturedStream << "-" << " " << std::fixed << std::setprecision(2) << set.b << " " << "-"
							<< " " << "-" << " " << set.B << " " << "-\n";
						lastString = capturedStream.str();

					}
					else if (typeOfString == 3) {
						std::cout
							<< "-" << " " << "-" << " " << std::fixed << std::setprecision(2) << set.c
							<< " " << "-" << " " << "-" << " " << set.C << "\n";
						capturedStream << "-" << " " << "-" << " " << std::fixed << std::setprecision(2) << set.c
							<< " " << "-" << " " << "-" << " " << set.C << "\n";
						lastString = capturedStream.str();
					}
					else {
						std::cout << "Строка не соответствует ни одному виду." << std::endl;
					}
				}
			}
			myFile.close();
			std::cout << "Чтобы начать сначала нажмите любую клавишу\nдля выхода нажмите 'q' ";
			std::cin >> optionMenu;
		}
		else if (optionMenu == '2') {
			std::cout << "Введите минимальное значение диапазона: ";
			while (!(std::cin >> min_range)) {
				std::cout << "Ошибка! Введите корректное значение: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			std::cout << "Введите максимальное значение диапазона: ";
			while (!(std::cin >> max_range) || max_range <= min_range) {
				std::cout << "Ошибка! Введите корректное значение, больше " << min_range << ": ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			std::cout << "Введите количество наборов чисел: ";
			while (!(std::cin >> num_count)) {
				std::cout << "Ошибка! Введите корректное значение: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			std::cout << "однофазный проводник (y/n)? ";
			while (!(std::cin >> conductor)) {
				std::cout << "Ошибка! Введите корректное значение: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			std::random_device rd;
			std::mt19937 gen(rd());

			do {
				if (conductor == 'y' || conductor == 'Y') {
					for (int i = 0; i < num_count; ++i) {
						NumberSet set = generateNumberSet(min_range, max_range);
						for (int k = 0; k <= 2; ++k) {
							if (k == 0) {
								std::cout
									<< std::fixed << std::setprecision(2) << set.a << " - " << " - "
									<< set.A << " - " << " - \n";
							}
							else if (k == 1) {
								std::cout
									<< " - " << std::fixed << std::setprecision(2) << set.b << " - "
									<< " - " << set.B << " - \n";
							}
							else if (k == 2) {
								std::cout
									<< " - " << " - " << std::fixed << std::setprecision(2) << set.c
									<< " - " << " - " << set.C << "\n";
							}
						}
					}
				}
				else {
					for (int i = 0; i < num_count; ++i) {
						NumberSet set = generateNumberSet(min_range, max_range);

						std::cout
							<< std::fixed << std::setprecision(2) << set.a << " " << std::fixed << std::setprecision(2) << set.b << " " << std::fixed << std::setprecision(2) << set.c
							<< set.A << " " << set.B << " " << set.C << "\n";
					}
				}
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Хотите сгенерировать еще с заданными параметрами (y/n)? ";
				std::cin >> repeat;
			} while (repeat == 'y' || repeat == 'Y');
		}
		else break;
	} while (optionMenu != 'Q' && optionMenu != 'q');
	std::cout << "Программа завершена." << std::endl;
	return 0;
}