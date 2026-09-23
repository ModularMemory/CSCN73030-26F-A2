#include "student_data.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <optional>
#include <vector>

using namespace std;

optional<STUDENT_DATA> readStudent(istream& stream) {
    string line;
    getline(stream, line);

    if (line.empty()) {
        return {};
    }

    istringstream lineStream(line);

    string firstName;
    string lastName;
    getline(lineStream, firstName, ',');
    getline(lineStream, lastName, ',');

    return STUDENT_DATA { .firstName = firstName, .lastName = lastName };
}

int main(int argc, char* argv[]) {
    const string filename = "StudentData.txt";

    ifstream fin;
    fin.open(filename);
    if (!fin.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return 1;
    }

    vector<STUDENT_DATA> students;
    while (true) {
        optional<STUDENT_DATA> student = readStudent(fin);
        if (student.has_value()) {
            students.push_back(student.value());
        }

        if (fin.eof()) {
            break;
        }
    }

#ifdef _DEBUG
    cout << "Parsed " << students.size() << " students" << endl;
    for (const auto& student : students) {
        cout << "Student: " << student.firstName << ", " << student.lastName << endl;
    }
#endif

    return 0;
}