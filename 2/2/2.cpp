
#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <limits> 

using namespace std;


struct Component {
    string designation;
    char type;  
    double nominal;
    int quantity;
};

const string DATA_FILE = "components.txt";

vector<Component> loadData() {
    vector<Component> components;
    ifstream inputFile(DATA_FILE);
    if (inputFile.is_open()) {
        Component component;
        while (getline(inputFile, component.designation, ',')) {
            inputFile >> component.type;
            inputFile.ignore(numeric_limits<streamsize>::max(), ','); 
            inputFile >> component.nominal;
            inputFile.ignore(numeric_limits<streamsize>::max(), ','); 
            inputFile >> component.quantity;
            inputFile.ignore(numeric_limits<streamsize>::max(), '\n'); 
            components.push_back(component);
        }
        inputFile.close();
    }
    else {
        cout << "Файл " << DATA_FILE << " не найден. Будет создан новый файл." << endl;
    }
    return components;
}

void saveData(const vector<Component>& components) {
    ofstream outputFile(DATA_FILE);
    if (outputFile.is_open()) {
        for (const auto& component : components) {
            outputFile << component.designation << ","
                << component.type << ","
                << component.nominal << ","
                << component.quantity << endl;
        }
        outputFile.close();
    }
    else {
        cerr << "Ошибка открытия файла " << DATA_FILE << " для записи." << endl;
    }
}

void displayTable(const vector<Component>& components) {
    cout << "\nВедомость комплектующих:\n" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "| Обозначение | Тип | Номинал | Количество |" << endl;
    cout << "--------------------------------------------------------" << endl;
    for (const auto& component : components) {
        cout << "| " << component.designation << " | "
            << component.type << " | "
            << component.nominal << " | "
            << component.quantity << " |" << endl;
    }
    cout << "--------------------------------------------------------" << endl;
}

vector<Component> addEntry(vector<Component> components) {
    Component newComponent;

    cout << "Введите обозначение: ";
    cin >> newComponent.designation;

    cout << "Введите тип (R/C): ";
    cin >> newComponent.type;
    newComponent.type = toupper(newComponent.type); 

    if (newComponent.type != 'R' && newComponent.type != 'C') {
        cout << "Ошибка: Тип должен быть 'R' или 'C'." << endl;
        return components;
    }

    cout << "Введите номинал: ";
    cin >> newComponent.nominal;

    if (cin.fail()) {
        cout << "Ошибка: Некорректный ввод номинала.  Введите число." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        return components;
    }

    cout << "Введите количество: ";
    cin >> newComponent.quantity;

    if (cin.fail()) {
        cout << "Ошибка: Некорректный ввод количества.  Введите целое число." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        return components;
    }


    components.push_back(newComponent);
    return components;
}


vector<Component> editEntry(vector<Component> components) {
    displayTable(components);

    int index;
    cout << "Введите номер строки для редактирования (начиная с 0): ";
    cin >> index;

    if (cin.fail()) {
        cout << "Ошибка: Введите целое число." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return components;
    }

    if (index < 0 || index >= components.size()) {
        cout << "Ошибка: Некорректный номер строки." << endl;
        return components;
    }

    cout << "Редактирование строки " << index << endl;


    string input;
    Component& component = components[index];

    cout << "Введите обозначение (оставьте пустым, чтобы оставить '" << component.designation << "'): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, input);
    if (!input.empty()) {
        component.designation = input;
    }

    cout << "Введите тип (R/C, оставьте пустым, чтобы оставить '" << component.type << "'): ";
    getline(cin, input);
    if (!input.empty()) {
        if (input.length() != 1 || (toupper(input[0]) != 'R' && toupper(input[0]) != 'C')) {
            cout << "Ошибка: Тип должен быть 'R' или 'C'. Изменения не сохранены." << endl;
            return components;
        }
        component.type = toupper(input[0]);
    }

    cout << "Введите номинал (оставьте пустым, чтобы оставить '" << component.nominal << "'): ";
    getline(cin, input);
    if (!input.empty()) {
        try {
            component.nominal = stod(input); 
        }
        catch (const invalid_argument& e) {
            cout << "Ошибка: Номинал должен быть числом. Изменения не сохранены." << endl;
            return components;
        }
    }

    cout << "Введите количество (оставьте пустым, чтобы оставить '" << component.quantity << "'): ";
    getline(cin, input);
    if (!input.empty()) {
        try {
            component.quantity = stoi(input);  
        }
        catch (const invalid_argument& e) {
            cout << "Ошибка: Количество должно быть целым числом. Изменения не сохранены." << endl;
            return components;
        }
    }

    return components;
}

vector<Component> deleteEntry(vector<Component> components) {
    displayTable(components);

    int index;
    cout << "Введите номер строки для удаления (начиная с 0): ";
    cin >> index;

    if (cin.fail()) {
        cout << "Ошибка: Введите целое число." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return components;
    }

    if (index < 0 || index >= components.size()) {
        cout << "Ошибка: Некорректный номер строки." << endl;
        return components;
    }

    components.erase(components.begin() + index);
    return components;
}

int main() {
    vector<Component> components = loadData();

    while (true) {
        cout << "\nМеню:" << endl;
        cout << "1. Показать таблицу" << endl;
        cout << "2. Добавить запись" << endl;
        cout << "3. Редактировать запись" << endl;
        cout << "4. Удалить запись" << endl;
        cout << "5. Выход" << endl;

        int choice;
        cout << "Выберите действие: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Ошибка: Некорректный ввод. Введите число от 1 до 5." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            displayTable(components);
            break;
        case 2:
            components = addEntry(components);
            saveData(components);
            break;
        case 3:
            components = editEntry(components);
            saveData(components);
            break;
        case 4:
            components = deleteEntry(components);
            saveData(components);
            break;
        case 5:
            cout << "Выход из программы." << endl;
            return 0;
        default:
            cout << "Некорректный ввод. Пожалуйста, выберите из предложенных вариантов." << endl;
        }
    }

    return 0;
}
