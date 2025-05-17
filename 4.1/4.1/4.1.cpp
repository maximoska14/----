#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>  

class Авиабилет; 

class Flight {
public:
    static double calculateFlightTime(const Авиабилет& ticket);
};

class Авиабилет {
private:
    std::string пунктОтправления;
    std::string пунктНазначения;
    std::chrono::system_clock::time_point датаВылета;
    std::chrono::system_clock::time_point датаПрилета;

    
    std::chrono::system_clock::time_point stringToTimePoint(const std::string& dateTimeString) const {
        std::tm t = {};
        std::istringstream ss(dateTimeString);
        ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S");
        if (ss.fail()) {
            throw std::runtime_error{ "failed to parse time string" };
        }

        t.tm_isdst = -1; 

        std::time_t tp = mktime(&t);
        if (tp == -1) {
            throw std::runtime_error{ "failed to create time_t object" };
        }
        return std::chrono::system_clock::from_time_t(tp);
    }


public:
    Авиабилет(const std::string& пунктОтправления, const std::string& пунктНазначения,
        const std::string& датаВылетаStr, const std::string& датаПрилетаStr)
        : пунктОтправления(пунктОтправления), пунктНазначения(пунктНазначения) {

        try {
            датаВылета = stringToTimePoint(датаВылетаStr);
            датаПрилета = stringToTimePoint(датаПрилетаStr);
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Ошибка при создании авиабилета: " << e.what() << std::endl;
            // Можно установить какие-то значения по умолчанию или выбросить исключение
        }

    }

   
    std::chrono::system_clock::time_point getДатаВылета() const { return датаВылета; }
    std::chrono::system_clock::time_point getДатаПрилета() const { return датаПрилета; }


    friend class Flight;
};


double Flight::calculateFlightTime(const Авиабилет& ticket) {
    auto duration = ticket.getДатаПрилета() - ticket.getДатаВылета();
    auto hours = std::chrono::duration_cast<std::chrono::duration<double, std::chrono::hours::period>>(duration);
    return hours.count();
}



int main() {

    Авиабилет ticket("Москва", "Париж", "2023-12-03 10:00:00", "2023-12-03 13:00:00");

    double flightTime = Flight::calculateFlightTime(ticket);

    std::cout << "Время полета: " << flightTime << " часов" << std::endl;

    return 0;
}

