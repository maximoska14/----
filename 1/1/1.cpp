#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    int age;
    double gpa;

public:
    // 1) Реализация методов Set...()
    void SetName(const std::string& newName) {
        name = newName;
    }

    void SetAge(int newAge) {
        if (newAge > 0) { 
            age = newAge;
        }
        else {
            std::cout << "Ошибка: Возраст должен быть положительным числом." << std::endl;
        }
    }

    void SetGPA(double newGPA) {
        if (newGPA >= 0.0 && newGPA <= 4.0) { 
            gpa = newGPA;
        }
        else {
            std::cout << "Ошибка: GPA должен быть в диапазоне от 0.0 до 4.0." << std::endl;
        }
    }

    // 2) Реализация методов Get...()
    std::string GetName() const {
        return name;
    }

    int GetAge() const {
        return age;
    }

    double GetGPA() const {
        return gpa;
    }

    // 3) Метод PrintInfo()
    void PrintInfo() const {
        std::cout << "Имя: " << name << std::endl;
        std::cout << "Возраст: " << age << std::endl;
        std::cout << "Средний балл: " << gpa << std::endl;
    }
};

int main() {
    Student student1;

 
    student1.SetName("Иван Иванов");
    student1.SetAge(20);
    student1.SetGPA(3.8);

    std::cout << "Информация о студенте:" << std::endl;
    student1.PrintInfo();

    std::cout << "\nИмя студента: " << student1.GetName() << std::endl;
    std::cout << "Возраст студента: " << student1.GetAge() << std::endl;
    std::cout << "GPA студента: " << student1.GetGPA() << std::endl;

    Student student2;
    student2.SetAge(-5); 
    student2.SetGPA(5.0); 

    return 0;
}