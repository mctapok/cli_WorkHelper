#include <iostream>
#include <random>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

int generateRandomNumber(int min_value, int max_value) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min_value, max_value);
	return dis(gen);
}
void programMenu() {
	std::cout << "1 ��������� ������ �� ����� ?\n";
	std::cout << "2 ��������� ������ ������� ?\n";
	std::cout << "q �����\n";
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
		std::cout << "������������ ��� ������" << std::endl;
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

		/*while (!std::cin) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("cls");
			programMenu();
			std::cout << "Option: ";
			std::cout << "Please enter a number, not a letter, you fuckwit: " << std::endl;
			std::cin >> optionMenu;
		}*/
		if (optionMenu == '1') {
			/*std::cout << "������� ���� � �����: ";
			std::cin >> filePath;*/
			std::ifstream myFile;
			//myFile.open(filePath);

			/*myFile.open("someText.txt", std::ios::in)*/; //read file
			while (optionMenu != 'n') {
				std::cout << "������� ���� � �����: ";
				std::cin >> filePath;
				myFile.open(filePath);
				if (!myFile.is_open()) {
					std::cerr << "�� ������� ������� ���� " << filePath << std::endl;
					std::cout << "������ ����������� ����� ? (y/n) ";
					std::cin >> optionMenu;
				}
				else break;		
			}

			std::string line;

			int automaticCurrent;//��� ����������� � �����
			int polusCount; //����� �������
			int triggerCurrent;//��� ��

			std::string lastString = "0.0 0.0 0.0 0 0 0\n"; //������ ��������� � �������
			int typeOfString;

			while (std::getline(myFile, line)) {
				std::istringstream iss(line);
				std::string firstPart, secondPart, thirdPart;

				// ��������� ����� �� ������
				if (std::getline(iss, firstPart, '-') &&
					std::getline(iss, secondPart, ' ') &&
					std::getline(iss, thirdPart)) {
					try {
						automaticCurrent = std::stoi(secondPart);
						polusCount = std::stoi(thirdPart);
					}
					catch (const std::invalid_argument& e) {
						std::cerr << "������: ������������ ������ �����" << std::endl;
					}
				}
				else {
					std::cerr << "������: �� ������� ������� ����� �� ������" << std::endl;
				}
				/*
					triggerCurrent ��� �������� ����, ��� ��������� ������ ����� ��������� �������� ��������

					��� ������ ��������� ����� ������������ �������
					min_range = triggerCurrent - (triggerCurrent * 0.3),
					max_range = triggerCurrent + (triggerCurrent * 0.3)
				*/

				triggerCurrent = automaticCurrent * generateRandomNumber(3, 6); //��������� ��� ��

				//���������� ��������
				min_range = triggerCurrent - (triggerCurrent * 0.3);
				max_range = triggerCurrent + (triggerCurrent * 0.3);

				//������� �����
				NumberSet set = generateNumberSet(min_range, max_range);
				std::stringstream capturedStream;//����� ������ � �������

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
						std::cout << "������ �� ������������� �� ������ ����." << std::endl;
					}
				}
			}
			myFile.close();
			std::cout << "����� ������ ������� ������� ����� �������\n��� ������ ������� 'q' ";
			std::cin >> optionMenu;
		}
		else if (optionMenu == '2') {
			std::cout << "������� ����������� �������� ���������: ";
			while (!(std::cin >> min_range)) {
				std::cout << "������! ������� ���������� ��������: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			std::cout << "������� ������������ �������� ���������: ";
			while (!(std::cin >> max_range) || max_range <= min_range) {
				std::cout << "������! ������� ���������� ��������, ������ " << min_range << ": ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			std::cout << "������� ���������� ������� �����: ";
			std::cin >> num_count;

			std::cout << "���������� ��������� (y/n)? ";
			std::cin >> conductor;


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
				std::cout << "������ ������������� ��� � ��������� ����������� (y/n)? ";
				std::cin >> repeat;
			} while (repeat == 'y' || repeat == 'Y');
		}
		else break;
	} while (optionMenu != 'Q' && optionMenu != 'q');
	std::cout << "��������� ���������." << std::endl;
	return 0;
}


//
//std::cout << "��������� ������ �� ����� (y/n)?";
//std::cin >> option;
//if (option == 'y' || option == 'Y') {
//	do {
//		//������ ������ � ������
//		std::cout << "������� ���� � ����� ";
//
//		std::cin >> filePath;
//		std::ifstream myFile;
//		myFile.open(filePath);
//
//		/*myFile.open("someText.txt", std::ios::in)*/; //read file
//		if (!myFile.is_open()) {
//			std::cerr << "�� ������� ������� ���� " << filePath << std::endl;
//			return -1; //� ������ ������
//		}
//
//		std::string line;
//
//		int automaticCurrent;//��� ����������� � �����
//		int polusCount; //����� �������
//		int triggerCurrent;//��� ��
//
//		std::string lastString = "0.0 0.0 0.0 0 0 0\n"; //������ ��������� � �������
//		int typeOfString;
//
//		while (std::getline(myFile, line)) {
//			std::istringstream iss(line);
//			std::string firstPart, secondPart, thirdPart;
//
//			// ��������� ����� �� ������
//			if (std::getline(iss, firstPart, '-') &&
//				std::getline(iss, secondPart, ' ') &&
//				std::getline(iss, thirdPart)) {
//				try {
//					automaticCurrent = std::stoi(secondPart);
//					polusCount = std::stoi(thirdPart);
//				}
//				catch (const std::invalid_argument& e) {
//					std::cerr << "������: ������������ ������ �����" << std::endl;
//				}
//			}
//			else {
//				std::cerr << "������: �� ������� ������� ����� �� ������" << std::endl;
//			}
//			/*
//				triggerCurrent ��� �������� ����, ��� ��������� ������ ����� ��������� �������� ��������
//
//				��� ������ ��������� ����� ������������ �������
//				min_range = triggerCurrent - (triggerCurrent * 0.3),
//				max_range = triggerCurrent + (triggerCurrent * 0.3)
//			*/
//
//			triggerCurrent = automaticCurrent * generateRandomNumber(3, 6); //��������� ��� ��
//
//			//���������� ��������
//			min_range = triggerCurrent - (triggerCurrent * 0.3);
//			max_range = triggerCurrent + (triggerCurrent * 0.3);
//
//			//������� �����
//			NumberSet set = generateNumberSet(min_range, max_range);
//			std::stringstream capturedStream;//����� ������ � �������
//
//			if (polusCount == 3) {
//				std::cout
//					<< std::fixed << std::setprecision(2) << set.a << " " << std::fixed << std::setprecision(2) << set.b << " " << std::fixed << std::setprecision(2) << set.c
//					<< " " << set.A << " " << set.B << " " << set.C << "\n";
//				capturedStream << std::fixed << std::setprecision(2) << set.a << " " << std::fixed << std::setprecision(2) << set.b << " " << std::fixed << std::setprecision(2) << set.c
//					<< " " << set.A << " " << set.B << " " << set.C << "\n";
//
//				lastString = capturedStream.str();
//
//			}
//
//			if (polusCount == 1) {
//				typeOfString = regexVerify(lastString);
//				if (typeOfString == 1 || typeOfString == 4) {
//					std::cout
//						<< std::fixed << std::setprecision(2) << set.a << " " << "-" << " " << "-" << " " << set.A << " " << "-" << " " << "-\n";
//
//					capturedStream << std::fixed << std::setprecision(2) << set.a << " " << "-" << " " << "-"
//						<< " " << set.A << " " << "-" << " " << "-\n";
//					lastString = capturedStream.str();
//
//				}
//				else if (typeOfString == 2) {
//
//					std::cout
//						<< "-" << " " << std::fixed << std::setprecision(2) << set.b << " " << "-"
//						<< " " << "-" << " " << set.B << " " << "-\n";
//					capturedStream << "-" << " " << std::fixed << std::setprecision(2) << set.b << " " << "-"
//						<< " " << "-" << " " << set.B << " " << "-\n";
//					lastString = capturedStream.str();
//
//				}
//				else if (typeOfString == 3) {
//					std::cout
//						<< "-" << " " << "-" << " " << std::fixed << std::setprecision(2) << set.c
//						<< " " << "-" << " " << "-" << " " << set.C << "\n";
//					capturedStream << "-" << " " << "-" << " " << std::fixed << std::setprecision(2) << set.c
//						<< " " << "-" << " " << "-" << " " << set.C << "\n";
//					lastString = capturedStream.str();
//				}
//				else {
//					std::cout << "������ �� ������������� �� ������ ����." << std::endl;
//				}
//			}
//		}
//		myFile.close();
//		std::cout << "��������� (y / n) ? ";
//		std::cin >> repeat;
//	} while (repeat == 'y' || repeat == 'Y');
//}
//
//
//do {
//	std::cout << "��������� ������ �� ����� (y/n)?";
//	std::cin >> option;
//	if (option == 'y' || option == 'Y') {
//		//������ ������ � ������
//		std::cout << "������� ���� � ����� ";
//
//		std::cin >> filePath;
//		std::ifstream myFile;
//		myFile.open(filePath);
//
//		/*myFile.open("someText.txt", std::ios::in)*/; //read file
//		if (!myFile.is_open()) {
//			std::cerr << "�� ������� ������� ���� " << filePath << std::endl;
//			return -1; //� ������ ������
//		}
//
//		std::string line;
//
//		int automaticCurrent;//��� ����������� � �����
//		int polusCount; //����� �������
//		int triggerCurrent;//��� ��
//
//		std::string lastString = "0.0 0.0 0.0 0 0 0\n"; //������ ��������� � �������
//		int typeOfString;
//
//		while (std::getline(myFile, line)) {
//			std::istringstream iss(line);
//			std::string firstPart, secondPart, thirdPart;
//
//			// ��������� ����� �� ������
//			if (std::getline(iss, firstPart, '-') &&
//				std::getline(iss, secondPart, ' ') &&
//				std::getline(iss, thirdPart)) {
//				try {
//					automaticCurrent = std::stoi(secondPart);
//					polusCount = std::stoi(thirdPart);
//				}
//				catch (const std::invalid_argument& e) {
//					std::cerr << "������: ������������ ������ �����" << std::endl;
//				}
//			}
//			else {
//				std::cerr << "������: �� ������� ������� ����� �� ������" << std::endl;
//			}
//			/*
//				triggerCurrent ��� �������� ����, ��� ��������� ������ ����� ��������� �������� ��������
//
//				��� ������ ��������� ����� ������������ �������
//				min_range = triggerCurrent - (triggerCurrent * 0.3),
//				max_range = triggerCurrent + (triggerCurrent * 0.3)
//			*/
//
//			triggerCurrent = automaticCurrent * generateRandomNumber(3, 6); //��������� ��� ��
//
//			//���������� ��������
//			min_range = triggerCurrent - (triggerCurrent * 0.3);
//			max_range = triggerCurrent + (triggerCurrent * 0.3);
//
//			//������� �����
//			NumberSet set = generateNumberSet(min_range, max_range);
//			std::stringstream capturedStream;//����� ������ � �������
//
//			if (polusCount == 3) {
//				std::cout
//					<< std::fixed << std::setprecision(2) << set.a << " " << std::fixed << std::setprecision(2) << set.b << " " << std::fixed << std::setprecision(2) << set.c
//					<< " " << set.A << " " << set.B << " " << set.C << "\n";
//				capturedStream << std::fixed << std::setprecision(2) << set.a << " " << std::fixed << std::setprecision(2) << set.b << " " << std::fixed << std::setprecision(2) << set.c
//					<< " " << set.A << " " << set.B << " " << set.C << "\n";
//
//				lastString = capturedStream.str();
//
//			}
//
//			if (polusCount == 1) {
//				typeOfString = regexVerify(lastString);
//				if (typeOfString == 1 || typeOfString == 4) {
//					std::cout
//						<< std::fixed << std::setprecision(2) << set.a << " " << "-" << " " << "-" << " " << set.A << " " << "-" << " " << "-\n";
//
//					capturedStream << std::fixed << std::setprecision(2) << set.a << " " << "-" << " " << "-"
//						<< " " << set.A << " " << "-" << " " << "-\n";
//					lastString = capturedStream.str();
//
//				}
//				else if (typeOfString == 2) {
//
//					std::cout
//						<< "-" << " " << std::fixed << std::setprecision(2) << set.b << " " << "-"
//						<< " " << "-" << " " << set.B << " " << "-\n";
//					capturedStream << "-" << " " << std::fixed << std::setprecision(2) << set.b << " " << "-"
//						<< " " << "-" << " " << set.B << " " << "-\n";
//					lastString = capturedStream.str();
//
//				}
//				else if (typeOfString == 3) {
//					std::cout
//						<< "-" << " " << "-" << " " << std::fixed << std::setprecision(2) << set.c
//						<< " " << "-" << " " << "-" << " " << set.C << "\n";
//					capturedStream << "-" << " " << "-" << " " << std::fixed << std::setprecision(2) << set.c
//						<< " " << "-" << " " << "-" << " " << set.C << "\n";
//					lastString = capturedStream.str();
//				}
//				else {
//					std::cout << "������ �� ������������� �� ������ ����." << std::endl;
//				}
//			}
//		}
//		myFile.close();
//	}
//
//
//	std::cout << "������� ����������� �������� ���������: ";
//	while (!(std::cin >> min_range)) {
//		std::cout << "������! ������� ���������� ��������: ";
//		std::cin.clear();
//		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//	}
//	//std::cin >> min_range;
//	std::cout << "������� ������������ �������� ���������: ";
//	while (!(std::cin >> max_range) || max_range <= min_range) {
//		std::cout << "������! ������� ���������� ��������, ������ " << min_range << ": ";
//		std::cin.clear();
//		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//	}
//	//std::cin >> max_range;
//	std::cout << "������� ���������� ������� �����: ";
//	std::cin >> num_count;
//
//	std::cout << "���������� ��������� (y/n)? ";
//	std::cin >> conductor;
//
//
//	std::random_device rd;
//	std::mt19937 gen(rd());
//
//	do {
//		if (conductor == 'y' || conductor == 'Y') {
//			for (int i = 0; i < num_count; ++i) {
//
//				NumberSet set = generateNumberSet(min_range, max_range);
//
//				for (int k = 0; k < 2; ++k) {
//					if (k == 0) {
//						std::cout
//							<< std::fixed << std::setprecision(2) << set.a << " - " << " - "
//							<< set.A << " - " << " - \n";
//					}
//					else if (k == 1) {
//						std::cout
//							<< " - " << std::fixed << std::setprecision(2) << set.b << " - "
//							<< " - " << set.B << " - \n";
//					}
//					else if (k == 2) {
//						std::cout
//							<< " - " << " - " << std::fixed << std::setprecision(2) << set.c
//							<< " - " << " - " << set.C << "\n";
//					}
//				}
//			}
//		}
//		else {
//			for (int i = 0; i < num_count; ++i) {
//				NumberSet set = generateNumberSet(min_range, max_range);
//
//				std::cout
//					<< std::fixed << std::setprecision(2) << set.a << " " << std::fixed << std::setprecision(2) << set.b << " " << std::fixed << std::setprecision(2) << set.c
//					<< set.A << " " << set.B << " " << set.C << "\n";
//			}
//
//			/* for (int k = 0; k < 2; ++k) {
//				 if (k == 0) {
//					 std::cout
//						 << " " << std::fixed << std::setprecision(2) << set.a << " - " << " - "
//						 << set.A << " - " << " - \n";
//				 }else if (k == 1){
//					 std::cout
//						 << " " << " - " << std::fixed << std::setprecision(2) << set.b << " - "
//						 << " - " << set.B << " - \n";
//				 }
//				 else if (k == 2) {
//					 std::cout
//						 << " " << " - " << " - " << std::fixed << std::setprecision(2) << set.c
//						 << " - " << " - " << set.C << "\n";
//				 }
//			 }*/
//
//			 //int A = generateRandomNumber(min_range, max_range);
//			 //int B = std::min(A + generateRandomNumber(1, 3), max_range); // ����������� ���������
//			 //int C = std::min(B + generateRandomNumber(1, 3), max_range); // ����������� ���������
//
//			 //double a = 230.0 / A;
//			 //double b = 230.0 / B;
//			 //double c = 230.0 / C;
//
//			/* if (conductor == 'y' || conductor == 'Y') {
//
//			 }else{
//				 std::cout
//					 << " " << std::fixed << std::setprecision(2) << set.a << " " << std::fixed << std::setprecision(2) << set.b << " " << std::fixed << std::setprecision(2) << set.c
//					 << " " << set.A << " " << set.B << " " << set.C << "\n";
//			 }*/
//		}
//		std::cin.clear();
//		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//		std::cout << "������ ������������� ��� � ��������� ����������� (y/n)? ";
//		std::cin >> repeat;
//	} while (repeat == 'y' || repeat == 'Y');
//	std::cout << "������ ������� (y/n)? ";
//	std::cin >> exit;
//} while (exit == 'y' || exit == 'Y');
//std::cout << "��������� ���������." << std::endl;
//return 0;
//}
