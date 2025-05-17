#include <iostream>
#include <string>
#include <algorithm>

class ШЕСТНАДЦАТЕРИЧНАЯ_СТРОКА {
private:
    std::string строка;

    bool isValidHexChar(char c) const {
        return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
    }

    int hexCharToInt(char c) const {
        if (c >= '0' && c <= '9') {
            return c - '0';
        }
        else if (c >= 'A' && c <= 'F') {
            return c - 'A' + 10;
        }
        else if (c >= 'a' && c <= 'f') {
            return c - 'a' + 10;
        }
    }

    
    char intToHexChar(int i) const {
        if (i >= 0 && i <= 9) {
            return i + '0';
        }
        else if (i >= 10 && i <= 15) {
            return i - 10 + 'A';
        }
        return '0'; 
    }

public:
   ШЕСТНАДЦАТЕРИЧНАЯ_СТРОКА(const std::string& str = "") {
        строка = ""; 
        for (char c : str) {
            if (isValidHexChar(c)) {
                строка += toupper(c);  
            }
            else {
                строка = "";  
                break;
            }
        }
    }

    ШЕСТНАДЦАТЕРИЧНАЯ_СТРОКА operator|(const ШЕСТНАДЦАТЕРИЧНАЯ_СТРОКА& other) const {
        std::string result = "";
        size_t maxLength = std::max(строка.length(), other.строка.length());

        std::string str1 = строка;
        std::string str2 = other.строка;
        while (str1.length() < maxLength) {
            str1 = "0" + str1;
        }
        while (str2.length() < maxLength) {
            str2 = "0" + str2;
        }

        for (size_t i = 0; i < maxLength; ++i) {
            int digit1 = hexCharToInt(str1[i]);
            int digit2 = hexCharToInt(str2[i]);
            result += intToHexChar(digit1 | digit2);
        }

        return ШЕСТНАДЦАТЕРИЧНАЯ_СТРОКА(result);
    }

    std::string getСтрока() const {
        return строка;
    }

    
    bool isEmpty() const {
        return строка.empty();
    }
};

int main() {
    ШЕСТНАДЦАТЕРИЧНАЯ_СТРОКА hex1("1A");
    ШЕСТНАДЦАТЕРИЧНАЯ_СТРОКА hex2("3C");
    ШЕСТНАДЦАТЕРИЧНАЯ_СТРОКА hex3("G2");
    ШЕСТНАДЦАТЕРИЧНАЯ_СТРОКА hex4("1A");
    ШЕСТНАДЦАТЕРИЧНАЯ_СТРОКА hex5("F");

    std::cout << "hex1: " << hex1.getСтрока() << std::endl;
    std::cout << "hex2: " << hex2.getСтрока() << std::endl;
    std::cout << "hex3: " << hex3.getСтрока() << std::endl;

    ШЕСТНАДЦАТЕРИЧНАЯ_СТРОКА result = hex1 | hex2;
    std::cout << "hex1 | hex2: " << result.getСтрока() << std::endl;

    ШЕСТНАДЦАТЕРИЧНАЯ_СТРОКА result2 = hex4 | hex5;
    std::cout << "hex4 | hex5: " << result2.getСтрока() << std::endl;
    return 0;
}