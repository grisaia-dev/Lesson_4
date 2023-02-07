#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

class Address {
private:
    std::string city, street;
    int house_number, apartament_number;
public:
    // Конструктор
    Address() { city = street = ""; house_number = apartament_number = 0; } // Дефолтный конструктор
    Address(std::string city, std::string street, int house_number, int apartament_number);
    // Деструктор
    ~Address() {};

    // getter and setter
    void set_input_address(std::ifstream& I_file);
    std::string get_output_address();
    std::string get_city() { return this->city; }
};

Address::Address(std::string city, std::string street, int house_number, int apartament_number) {
    this->city = city;
    this->street = street;
    this->house_number = house_number;
    this->apartament_number = apartament_number;
}

void Address::set_input_address(std::ifstream& I_file) {
    I_file >> this->city;
    I_file >> this->street;
    I_file >> this->house_number;
    I_file >> this->apartament_number;
}

std::string Address::get_output_address() {
    return this->get_city() + ", " + this->street + ", " + std::to_string(this->house_number) + ", " + std::to_string(this->apartament_number) + "\n";
}

// Функция сортировки
void sort (Address* __addr, unsigned const int* size) {
    Address temp;
    for (int i = 0; i < *size - 1; ++i) {
        for (int j = i + 1; j < *size; ++j) {
            if (std::strcmp(__addr[i].get_city().c_str(), __addr[j].get_city().c_str()) > 0) {
                temp = __addr[i];
                __addr[i] = __addr[j];
                __addr[j] = temp;
            }
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::ifstream i_file("in.txt");
    if (i_file.is_open()) {
        std::cout << "Файл ввода открыт!" << std::endl;
        std::ofstream o_file("out.txt");

        if (o_file.is_open()) {
            std::cout << "Файл вывода открыт!" << std::endl;
            unsigned int width = 0;
            i_file >> width;
            o_file << width << "\n";

            Address* addr = new Address[width];
            // Взятие данных
            for (int i = 0; i < width; ++i)
                addr[i].set_input_address(i_file);

            // Соритировка
            sort(addr, &width);

            // запись данных
            for (int i = 0; i < width; ++i)
                o_file << addr[i].get_output_address();

            std::cout << "Запись прошла успешно!" << std::endl;

            delete[] addr;
            o_file.close();
            std::cout << "Файл вывода закрыт!" << std::endl;
        } else {
            std::cout << "Не удалось найти или создать файл для вывода!" << std::endl;
            i_file.close();
            std::cout << "Файл ввода закрыт!" << std::endl;
            return 2;
        }
        i_file.close();
        std::cout << "Файл ввода закрыт!" << std::endl;
    }
    else {
        std::cout << "Не удалось найти файл ввода!" << std::endl;
        return 1;
    }

    return 0;
}