#include <iostream>
#include <fstream>
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
    void get_output_address(std::ofstream& O_file);
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

void Address::get_output_address(std::ofstream& O_file) {
    O_file << this->city << ", " << this->street << ", " << this->house_number << ", " << this->apartament_number << "\n";
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

            Address *addr = new Address[width];
            // Взятие данных
            for (int i = 0; i < width; ++i)
                addr[i].set_input_address(i_file);
            // запись данных
            for (int i = width - 1; i >= 0; --i)
                addr[i].get_output_address(o_file);

            delete[] addr;
            o_file.close();
        } else {
            std::cout << "Не удалось найти или создать файл для вывода!" << std::endl;
            return 2;
        }
        i_file.close();
    } else {
        std::cout << "Не удалось найти файл ввода!" << std::endl;
        return 1;
    }

    return 0;
}