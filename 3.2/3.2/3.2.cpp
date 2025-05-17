#include <iostream>
#include <cstdlib> 
#include <ctime>   

class Time {
private:
    int hours;
    int minutes;
    int seconds;

public:
 
    Time(int hours = 0, int minutes = 0, int seconds = 0) : hours(hours), minutes(minutes), seconds(seconds) {
        normalize(); 
    }


    void normalize() {
        minutes += seconds / 60;
        seconds %= 60;
        hours += minutes / 60;
        minutes %= 60;
        hours %= 24; 
    }

    int operator/(int divisor) const {
        if (divisor == 0) {
            std::cerr << "Ошибка: Деление на ноль!" << std::endl;
            return 0; 
        }
        return (hours * 3600 + minutes * 60 + seconds) / (divisor * 3600); 
    }

   
    Time& operator++() { 
        seconds++;
        normalize();
        return *this;
    }

    Time operator++(int) { 
        Time temp = *this;
        ++(*this);  
        return temp;
    }

    Time& operator--() { 
        seconds--;
        if (seconds < 0) {
            seconds += 60;
            minutes--;
            if (minutes < 0) {
                minutes += 60;
                hours--;
                if (hours < 0) {
                    hours = 23;\
                }
            }
        }
        normalize();
        return *this;
    }

    Time operator--(int) {
        Time temp = *this;
        --(*this); 
        return temp;
    }

 
    void addRandomTime() {
       
        static bool seeded = false;
        if (!seeded) {
            srand(time(0));
            seeded = true;
        }

        int randomHours = rand() % 24;      
        int randomMinutes = rand() % 60;    
        int randomSeconds = rand() % 60;    

        hours += randomHours;
        minutes += randomMinutes;
        seconds += randomSeconds;
        normalize();
    }

    void displayTime() const {
        std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
    }
};

int main() {
    Time t1(10, 30, 45);
    std::cout << "Время t1: ";
    t1.displayTime();

    
    int hoursInTwo = t1 / 2; 
    std::cout << "Целых часов (t1 / 2): " << hoursInTwo << std::endl;

    std::cout << "Префиксный инкремент (++t1): ";
    (++t1).displayTime();

    std::cout << "Постфиксный инкремент (t1++): ";
    (t1++).displayTime();
    std::cout << "Время t1 после постфиксного инкремента: ";
    t1.displayTime();


    std::cout << "Префиксный декремент (--t1): ";
    (--t1).displayTime();

    std::cout << "Постфиксный декремент (t1--): ";
    (t1--).displayTime();
    std::cout << "Время t1 после постфиксного декремента: ";
    t1.displayTime();

    std::cout << "Прибавление случайного времени: ";
    t1.addRandomTime();
    t1.displayTime();

    return 0;
}