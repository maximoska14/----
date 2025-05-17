#include <iostream>
#include <string>

class Пользователь {
private:
    std::string имя;
    std::string логин;
    std::string email;
    int возраст;
    std::string роль; 

public:
    
    Пользователь(std::string имя, std::string логин) : имя(имя), логин(логин) {
        std::cout << "Конструктор 1: Имя и логин" << std::endl;
        email = "Не указан"; 
        возраст = 0;
        роль = "Обычный пользователь";
    }

  
    Пользователь(std::string имя, std::string логин, std::string email) : имя(имя), логин(логин), email(email) {
        std::cout << "Конструктор 2: Имя, логин и email" << std::endl;
        возраст = 0;
        роль = "Обычный пользователь";
    }

  
    Пользователь(std::string имя, std::string логин, std::string email, int возраст) : имя(имя), логин(логин), email(email), возраст(возраст) {
        std::cout << "Конструктор 3: Имя, логин, email и возраст" << std::endl;
        роль = "Обычный пользователь";
    }

   
    Пользователь(std::string имя, std::string логин, std::string email, int возраст, std::string роль) : имя(имя), логин(логин), email(email), возраст(возраст), роль(роль) {
        std::cout << "Конструктор 4: Имя, логин, email, возраст и роль" << std::endl;
    }


    void ВывестиИнформацию() const {
        std::cout << "Имя: " << имя << std::endl;
        std::cout << "Логин: " << логин << std::endl;
        std::cout << "Email: " << email << std::endl;
        std::cout << "Возраст: " << возраст << std::endl;
        std::cout << "Роль: " << роль << std::endl;
    }

  
    ~Пользователь() {
        std::cout << "Вызвался деструктор для пользователя: " << имя << std::endl;
    }
};

int main() {
    
    Пользователь user1("Иван Иванов", "ivan123");
    user1.ВывестиИнформацию();

    Пользователь user2("Петр Петров", "petr456", "petr@example.com");
    user2.ВывестиИнформацию();

    Пользователь user3("Анна Сидорова", "anna789", "anna@example.com", 25);
    user3.ВывестиИнформацию();

    Пользователь user4("Мария Кузнецова", "maria012", "maria@example.com", 30, "Администратор");
    user4.ВывестиИнформацию();

    return 0; 
}