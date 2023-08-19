#include <iostream>
#include <random>
#include <iomanip>

int generateRandomNumber(int min_value, int max_value) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min_value, max_value);
    return dis(gen);
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
    char exit;
    char repeat;
    char conductor;

    do {
        std::cout << "Введите минимальное значение диапазона: ";
        while (!(std::cin >> min_range)) {
            std::cout << "Ошибка! Введите корректное значение: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        //std::cin >> min_range;
        std::cout << "Введите максимальное значение диапазона: ";
        while (!(std::cin >> max_range) || max_range <= min_range) {
            std::cout << "Ошибка! Введите корректное значение, больше " << min_range << ": ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        //std::cin >> max_range;
        std::cout << "Введите количество наборов чисел: ";
        std::cin >> num_count;

        std::cout << "однофазный проводник (y/n)? ";
        std::cin >> conductor;


        std::random_device rd;
        std::mt19937 gen(rd());
        
        do {
            if (conductor == 'y' || conductor == 'Y') {
                for (int i = 0; i < num_count; ++i) {
                    NumberSet set = generateNumberSet(min_range, max_range);

                    for (int k = 0; k < 2; ++k) {
                        if (k == 0) {
                            std::cout
                                << " " << std::fixed << std::setprecision(2) << set.a << " - " << " - "
                                << set.A << " - " << " - \n";
                        }
                        else if (k == 1) {
                            std::cout
                                << " " << " - " << std::fixed << std::setprecision(2) << set.b << " - "
                                << " - " << set.B << " - \n";
                        }
                        else if (k == 2) {
                            std::cout
                                << " " << " - " << " - " << std::fixed << std::setprecision(2) << set.c
                                << " - " << " - " << set.C << "\n";
                        }
                    }
                }
            }
            else {
                for (int i = 0; i < num_count; ++i) {
                    NumberSet set = generateNumberSet(min_range, max_range);

                    std::cout
                        << " " << std::fixed << std::setprecision(2) << set.a << " " << std::fixed << std::setprecision(2) << set.b << " " << std::fixed << std::setprecision(2) << set.c
                        << " " << set.A << " " << set.B << " " << set.C << "\n";
                }
 
               /* for (int k = 0; k < 2; ++k) {
                    if (k == 0) {
                        std::cout
                            << " " << std::fixed << std::setprecision(2) << set.a << " - " << " - "
                            << set.A << " - " << " - \n";
                    }else if (k == 1){
                        std::cout
                            << " " << " - " << std::fixed << std::setprecision(2) << set.b << " - "
                            << " - " << set.B << " - \n";
                    }
                    else if (k == 2) {
                        std::cout
                            << " " << " - " << " - " << std::fixed << std::setprecision(2) << set.c
                            << " - " << " - " << set.C << "\n";
                    }
                }*/

                //int A = generateRandomNumber(min_range, max_range);
                //int B = std::min(A + generateRandomNumber(1, 3), max_range); // Ограничение диапазона
                //int C = std::min(B + generateRandomNumber(1, 3), max_range); // Ограничение диапазона

                //double a = 230.0 / A;
                //double b = 230.0 / B;
                //double c = 230.0 / C;

               /* if (conductor == 'y' || conductor == 'Y') {
                    
                }else{
                    std::cout
                        << " " << std::fixed << std::setprecision(2) << set.a << " " << std::fixed << std::setprecision(2) << set.b << " " << std::fixed << std::setprecision(2) << set.c
                        << " " << set.A << " " << set.B << " " << set.C << "\n";
                }*/
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Хотите сгенерировать еще с заданными параметрами (y/n)? ";
            std::cin >> repeat;
        } while (repeat == 'y' || repeat == 'Y');
        std::cout << "начать сначала (y/n)? ";
        std::cin >> exit;
    } while (exit == 'y' || exit == 'Y');
    std::cout << "Программа завершена." << std::endl;
    return 0;
}
