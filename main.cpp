#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;

namespace fs = std::filesystem;

void updateCsvFile(int rowToUpdate) {
    string filename = "/Users/andyg/Facultate/Anul 2 Sem I/POO/FLOW/FlowCreate/FlowCreate/analytics.csv";
    ifstream fileIn(filename);
    vector < string > rows;
    string line, cell;

    if (!fileIn.is_open()) {
        cerr << "Failed to open file." << endl;
        updateCsvFile(14);
        return;
    }

    while (getline(fileIn, line)) {
        rows.push_back(line);
    }
    fileIn.close();

    if (rowToUpdate < 0 || rowToUpdate >= rows.size()) {
        cerr << "Analytics not updated." << endl;
        updateCsvFile(14);
        return;
    }

    stringstream ss(rows[rowToUpdate]);
    getline(ss, cell, ',');
    int value;
    ss >> value;
    rows[rowToUpdate] = cell + ", " + to_string(value + 1);

    ofstream fileOut(filename);
    for (const auto & row: rows) {
        fileOut << row << endl;
    }
}
void showAnalytics() {
    string filename = "/Users/andyg/Facultate/Anul 2 Sem I/POO/FLOW/FlowCreate/FlowCreate/analytics.csv";
    ifstream fileIn(filename);
    string line, cell;

    if (!fileIn.is_open()) {
        cerr << "Failed to open file." << endl;
        updateCsvFile(14);
        return;
    }
    cout << "\n--- App analytics ---\n\n";
    while (getline(fileIn, line)) {
        stringstream ss(line);
        bool firstCell = true;

        while (getline(ss, cell, ',')) {
            if (!firstCell) {
                cout << " : ";
            }
            cout << cell;
            firstCell = false;
        }

        cout << "." << endl;
    }
    cout << "\n";
    fileIn.close();
}

void afiseazaFlowuriExistente() {
    string path = "/Users/andyg/Facultate/Anul 2 Sem I/POO/FLOW/FlowCreate/FlowCreate/FlowuriExistente/";
    vector < string > fileNames;

    // se afiseaza fisierele din vector pentru a fi accesate
    int index = 1;
    for (const auto & entry: fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            fileNames.push_back(entry.path().filename());
            cout << index++ << ". " << entry.path().filename() << '\n';
        }
    }

    cout << "Choose the file number to open it: ";
    int choice;
    cin >> choice;
    if (choice > 0 && choice <= fileNames.size()) {
        string filePath = path + fileNames[choice - 1];
        ifstream file(filePath);
        string line;
        while (getline(file, line)) {
            cout << line << '\n';
        }
    } else {
        cout << "Invalid choice." << endl;
        updateCsvFile(14);
    }
}

void stergeFlow() {
    string path = "/Users/andyg/Facultate/Anul 2 Sem I/POO/FLOW/FlowCreate/FlowCreate/FlowuriExistente/";
    vector < string > fileNames;
    int index = 1;

    // se listeaza flowurile pentru a fi sterse
    for (const auto & entry: fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            fileNames.push_back(entry.path().filename());
            cout << index++ << ". " << entry.path().filename() << '\n';
        }
    }

    cout << "Choose the file number to delete it: ";
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits < streamsize > ::max(), '\n');

    if (choice > 0 && choice <= fileNames.size()) {
        string fullPath = path + fileNames[choice - 1];
        if (remove(fullPath.c_str()) == 0) {
            cout << "File deleted succesfully." << endl;
            updateCsvFile(2);
        } else {
            cout << "Error deleting the file." << endl;
            updateCsvFile(14);
        }
    } else {
        cout << "Invalid choice." << endl;
        updateCsvFile(14);
    }
}

// vectorul number input
vector < float > numberInputs;

class Flow {
    // vectorul flow ce contine datele despre fiecare step
    private: vector < string > stepData;

    public: void addStepData(const string & data) {
        stepData.push_back(data);
    }

    const vector < string > & getStepData() const {
        return stepData;
    }

};

Flow flow;

int transformOperationToNumber(char operation) {
    switch (operation) {
    case '+':
        return 1;
    case '-':
        return 2;
    case '*':
        return 3;
    case '/':
        return 4;
    case 'm':
        return 5;
    case 'M':
        return 6;
    default:
        return -1; // Invalid operation
    }
}

class Step {
    public: virtual void showStep() {
        cout << "This is showStep from parent class" << endl;
    }

    Step() {}
};

// 1. CLASA TITLU

class TitleStep: public Step {
    private: string title;
    string subTitle;

    public: void addTitle() {
        cout << "Enter the title: ";
        getline(cin, title);
    }

    void addSubTitle() {
        cout << "Enter the subtitle: ";
        getline(cin, subTitle);
        string data = "--- Title step ---\nTitle is :" + title + "\nSubitle is :" + subTitle + "\n";
        flow.addStepData(data);
        updateCsvFile(3);
    }

    void setTitle(const string & title) {
        this -> title = title;
    }

    void setSubTitle(const string & subTitle) {
        this -> subTitle = subTitle;
    }

    void showStep() override {
        cout << "Title is: " << title << endl;
        cout << "Subtitle is: " << subTitle << endl;
    }

};

//2. CLASA TEXT

class TextStep: public Step {
    private: string title;
    string copy;

    public: TextStep() {
        cout << "Enter the text title: ";
        getline(cin, title);

        cout << "Enter the copy: ";
        getline(cin, copy);
        string data = "--- Text step: ---\nTitle is: " + title + "\nCopy is: " + copy + "\n";
        flow.addStepData(data);
        updateCsvFile(4);
    }

    void showStep() override {
        cout << "Title is: " << title << endl;
        cout << "Copy is: " << copy << endl;
    }
};

//3. CLASA TEXT INPUT

class TextInput: public Step {
    private: string description;
    string textInput;

    public: TextInput() {
        cout << "Enter the description for the input: ";
        getline(cin, description);

        cout << "Enter the text input: ";
        getline(cin, textInput);
        string data = "--- Text Input step: ---\nDescription is: " + description + "\nText Input is: " + textInput + "\n";
        flow.addStepData(data);
        updateCsvFile(5);
    }

    void showStep() override {
        cout << "Description is: " << description << endl;
        cout << "Text input is: " << textInput << endl;
    }
};

//4. CLASA NUMBER INPUT

class NumberInput: public Step {
    private: string description;
    float number;

    public: NumberInput() {
        cout << "Enter the description: ";
        getline(cin, description);

        cout << "Enter the number: ";
        cin >> number;
        cin.ignore(numeric_limits < streamsize > ::max(), '\n'); // curata buffer
        string data = "--- Number Input Step --- \nDescription: " + description + ", Number input is: " + to_string(number) + "\n";
        flow.addStepData(data);
        updateCsvFile(6);
    }

    void showStep() override {
        cout << "Description is: " << description << endl;
        cout << "Number input is: " << number << endl;
    }
    void addNumberToVector() {
        numberInputs.push_back(number);
    };
};

// 5. CALCULUS STEP

class Calculus: public Step {
    public: void showStep() override {}

    void showMenu() {
        cout << "Choose an operation:\n";
        cout << "1. Addition (+)\n";
        cout << "2. Subtraction (-)\n";
        cout << "3. Multiplication (*)\n";
        cout << "4. Division (/)\n";
        cout << "5. Minimum (m)\n";
        cout << "6. Maximum (M)\n";
        cout << "Choose an operation (+, -, *, /, m, M): ";
    }
    // se iau numerele din vector si se face operatia ceruta
    void performOperation(int operation) {
        float result = 0;
        switch (operation) {
        case 1: // Addition
            for (float num: numberInputs) {
                result += num;
            }
            break;
        case 2: // Subtraction
            result = numberInputs.size() > 0 ? numberInputs[0] : 0;
            for (size_t i = 1; i < numberInputs.size(); ++i) {
                result -= numberInputs[i];
            }
            break;
        case 3: // Multiplication
            result = numberInputs.size() > 0 ? 1 : 0;
            for (float num: numberInputs) {
                result *= num;
            }
            break;
        case 4: // Division
            result = numberInputs.size() > 0 ? numberInputs[0] : 0;
            for (size_t i = 1; i < numberInputs.size(); ++i) {
                if (numberInputs[i] != 0) {
                    result /= numberInputs[i];
                } else {
                    cout << "Division by zero!" << endl;
                    updateCsvFile(14);
                    return;
                }
            }
            break;
        case 5: // Minimum
            if (!numberInputs.empty()) {
                result = * min_element(numberInputs.begin(), numberInputs.end());
            }
            break;
        case 6: // Maximum
            if (!numberInputs.empty()) {
                result = * max_element(numberInputs.begin(), numberInputs.end());
            }
        case -1:
            cout << "Invalid operation";
            updateCsvFile(14);
            return;

        }
        cout << "The result is: " << result << endl;
        string stepResult = "--- Calculus step---\nResult is: " + to_string(result) + "\n";
        flow.addStepData(stepResult);
        updateCsvFile(7);

    }

};

// 7. TEXT FILE INPUT STEP

class TextFileInputStep: public Step {
    private: string description;
    static vector < string > fileNames;

    public: TextFileInputStep() {
        cout << "Enter the description for the text file: ";
        getline(cin, description);

        string fileName;
        cout << "Enter the file name: ";
        getline(cin, fileName);

        checkFileExistence(fileName);
    }

    static
    const vector < string > & getFileNames() {
        return fileNames;
    }

    void checkFileExistence(const string & fileName) {
        ifstream file(fileName);
        if (!file) {
            cout << "File '" << fileName << "' not found." << endl;
            updateCsvFile(14);
        } else {
            cout << "File '" << fileName << "' is ready for use." << endl;
            fileNames.push_back(fileName); // daca exista fisierul se adauga in vector
            string stepData = "--- Text file input step ---\nTXT File name is: " + fileName + "\n";
            flow.addStepData(stepData);
            updateCsvFile(8);
        }
    }
};

vector < string > TextFileInputStep::fileNames; // initializare vector static text files

// 8. CSV FILE INPUT STEP

class CSVFileInputStep: public Step {
    private: string description;
    static vector < string > csvFileNames;

    public: CSVFileInputStep() {
        cout << "Enter the description for the CSV file: ";
        getline(cin, description);

        string fileName;
        cout << "Enter the CSV file name: ";
        getline(cin, fileName);

        if (checkFileExistence(fileName)) {
            csvFileNames.push_back(fileName);
        }
    }

    static
    const vector < string > & getCSVFileNames() {
        return csvFileNames;
    }

    private: bool checkFileExistence(const string & fileName) {
        ifstream file(fileName);
        if (!file) {
            cout << "CSV File '" << fileName << "' not found." << endl;
            updateCsvFile(14);
            return false;
        } else {
            cout << "CSV File '" << fileName << "' is ready for use." << endl;
            string stepData = "--- CSV file input step ---\nCSV File name is: " + fileName + "\n";
            flow.addStepData(stepData);
            updateCsvFile(9);
            return true;

        }
    }
};

vector < string > CSVFileInputStep::csvFileNames; // Initializarea vectorului static csv files

// 6. DISPAY TEXT

class DisplayStep: public Step {
    public: void showStep() override {
        cout << "Choose the type of document to display:\n";
        cout << "1. Text Document\n";
        cout << "2. CSV Document\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        // alegere intre csv si txt
        switch (choice) {
        case 1:
            displayTextFiles();
            break;
        case 2:
            displayCSVFiles();
            break;
        default:
            cout << "Invalid choice." << endl;
            updateCsvFile(14);
        }
    }

    private: void displayFileContent(const string & fileName) {
        ifstream file(fileName);
        if (file) {
            cout << "Contents of " << fileName << ":\n";
            string line;
            while (getline(file, line)) {
                cout << line << endl;
            }
        } else {
            cout << "Failed to open " << fileName << "." << endl;
            updateCsvFile(14);
        }
    }

    void displayTextFiles() {
        if (TextFileInputStep::getFileNames().empty()) {
            cout << "No files available to display." << endl;
            return;
        }

        // se afiseaza lista de fisiere
        int index = 1;
        for (const auto & fileName: TextFileInputStep::getFileNames()) {
            cout << index++ << ". " << fileName << endl;
        }

        cout << "Select a text file number to display: ";
        int choice;
        cin >> choice;

        if (choice > 0 && choice <= TextFileInputStep::getFileNames().size()) {
            displayFileContent(TextFileInputStep::getFileNames()[choice - 1]);
            string stepData = "--- Display step ---\nThe displayed text file is: " + TextFileInputStep::getFileNames()[choice - 1] + "\n";
            flow.addStepData(stepData);
            updateCsvFile(12);
        } else {
            cout << "Invalid selection." << endl;
            updateCsvFile(14);
        }
    }

    void displayCSVFiles() {
        if (CSVFileInputStep::getCSVFileNames().empty()) {
            cout << "No csv files available to display." << endl;
            return;
        }

        int index = 1;
        for (const auto & fileName: CSVFileInputStep::getCSVFileNames()) {
            cout << index++ << ". " << fileName << endl;
        }

        cout << "Select a csv file number to display: ";
        int choice;
        cin >> choice;

        if (choice > 0 && choice <= CSVFileInputStep::getCSVFileNames().size()) {
            displayFileContent(CSVFileInputStep::getCSVFileNames()[choice - 1]);
            string stepData = "--- Display step ---\nThe displayed CSV file is: " + TextFileInputStep::getFileNames()[choice - 1] + "\n";
            flow.addStepData(stepData);
            updateCsvFile(13);
        } else {
            cout << "Invalid selection." << endl;
        }
    }
};

// 9. CLASA UTPUT STEP

class OutputStep: public Step {
    public: void executeStep() {
        string fileName, description;
        string directory = "/Users/andyg/Facultate/Anul 2 Sem I/POO/FLOW/FlowCreate/FlowCreate/output/"; // CALEA MEA (TREBUIE SCHIMBATA)

        cout << "Enter the name for the output file: ";
        getline(cin, fileName);
        cout << "Enter a description for the file: ";
        getline(cin, description);

        string fullPath = directory + fileName;
        ofstream outputFile(fullPath);
        if (outputFile.is_open()) {
            outputFile << "Description: " << description << "\n\n";
            for (const auto & data: flow.getStepData()) {
                outputFile << data << "\n";
            }
            cout << "File '" << fullPath << "' has been created successfully." << endl;
            updateCsvFile(10);
        } else {
            cout << "Failed to create file: " << fullPath << endl;
            updateCsvFile(14);
        }
    }
};

void printMeniuFlow() {
    cout << "Choose a step:\n";
    cout << "1. Title step\n";
    cout << "2. Text step\n";
    cout << "3. Text input step\n";
    cout << "4. Number input step\n";
    cout << "5. Calculus step\n";
    cout << "6. Display step\n";
    cout << "7. Text file input step\n";
    cout << "8. CSV file input step\n";
    cout << "9. Output step\n";
    cout << "0. End\n";
    cout << "Input: ";
}

void afiseazaMeniuFlow() {
    int pas;

    while (true) {
        printMeniuFlow();
        cin >> pas;
        cin.ignore(numeric_limits < streamsize > ::max(), '\n');

        switch (pas) {
        case 1: {
            TitleStep titleStep;
            titleStep.addTitle();
            titleStep.addSubTitle();
            titleStep.showStep();
        }
        break;
        case 2: {
            TextStep textStep;
            textStep.showStep();
        }
        break;
        case 3: {
            TextInput textInputStep;
            textInputStep.showStep();
        }
        break;
        case 4: {
            NumberInput numberInputStep;
            numberInputStep.showStep();
            numberInputStep.addNumberToVector();
        }
        break;
        case 5: {
            Calculus calculusStep;
            calculusStep.showMenu();

            char operation;
            cin >> operation;
            cin.ignore(numeric_limits < streamsize > ::max(), '\n');

            int operationNumber = transformOperationToNumber(operation);
            calculusStep.performOperation(operationNumber);
        }
        break;
        case 6: {
            DisplayStep displayStep;
            displayStep.showStep();
        }
        break;
        case 7: {
            TextFileInputStep textFileInputStep;
        }
        break;
        case 8: {
            CSVFileInputStep csvFileInputStep;
        }
        break;
        case 9: {
            OutputStep outputStep;
            outputStep.executeStep();
        }
        break;
        case 0: {
            cout << "Do you want to save this flow? (yes/no): ";
            string raspuns;
            getline(cin, raspuns);
            if (raspuns == "yes") {
                cout << "Enter a name for this flow: ";
                string numeFisier;
                getline(cin, numeFisier);
                updateCsvFile(11);

                // se salveaza flowurile intr un folder
                ofstream outputFile("/Users/andyg/Facultate/Anul 2 Sem I/POO/FLOW/FlowCreate/FlowCreate/FlowuriExistente/" + numeFisier + ".txt");
                // DIN NOU CALEA MEA (TREBUIE SCHIMBATA)
                if (outputFile.is_open()) {
                    for (const auto & data: flow.getStepData()) {
                        outputFile << data << "\n";
                    }
                    // se adauga timestamp la finalul documentului
                    auto now = chrono::system_clock::now();
                    auto now_c = chrono::system_clock::to_time_t(now);
                    outputFile << "\nTimestamp: " << put_time(localtime( & now_c), "%Y-%m-%d %X") << endl;
                    cout << "Flow saved succesfully in file '" << numeFisier << ".txt'" << endl;

                } else {
                    cout << "Error creating the file." << endl;
                }

            }
            cout << "Closing flow..." << endl;
            return;
        }
        default:
            cout << "\nInvalid option. Please try again.\n";
            updateCsvFile(14);
        }
    }
}

void startApp() {
    int alegere;

    while (true) {
        cout << "--- Flow creator app ---\n\n";
        cout << "1. Create a new flow.\n";
        cout << "2. Existing flows.\n";
        cout << "3. Delete flows.\n";
        cout << "4. Show analytics.\n";
        cout << "5. Exit.\n";
        cout << "Choose an option: ";
        cin >> alegere;

        switch (alegere) {
        case 1:
            afiseazaMeniuFlow();
            break;
        case 2:
            afiseazaFlowuriExistente();
            break;
        case 3:
            stergeFlow();
            break;
        case 4:
            showAnalytics();
            break;
        case 5:
            cout << "Goodbye!\n";
            return;
        default:
            cout << "Invalid option. Try again.\n";
            updateCsvFile(14);
        }
    }
}

int main() {
    updateCsvFile(0);
    startApp();
    return 0;
}
