#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#define MAX_STUDENTS 100
#define MAX_LENGTH 100

struct Student {
    char firstName[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    char facultyNumber[MAX_LENGTH];
    char email[MAX_LENGTH];
    char faculty[MAX_LENGTH];
}; 

void print_student(const Student & student) {
    std::cout << "First Name: " << student.firstName << "\n"
            << "Last Name: " << student.lastName << "\n"
            << "Faculty Number: " << student.facultyNumber << "\n"
            << "Email: " << student.email << "\n"
            << "Faculty: " << student.faculty << "\n";
}


int load_students(const char* filename, Student students[]) {
    std::ifstream file(filename);
    int studentCount = 0;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 0;
    }

    char line[MAX_LENGTH * 5]; // Буфер за един ред
    while (std::getline(file, line) && studentCount < MAX_STUDENTS) {
        std::stringstream ss(line);
        ss.getline(students[studentCount].firstName, MAX_LENGTH, ',');
        ss.getline(students[studentCount].lastName, MAX_LENGTH, ',');
        ss.getline(students[studentCount].facultyNumber, MAX_LENGTH, ',');
        ss.getline(students[studentCount].email, MAX_LENGTH, ',');
        ss.getline(students[studentCount].faculty, MAX_LENGTH);

        studentCount++;
    }

    file.close();
    return studentCount;
}

void print_student_by_faculty_number(const Student students[], int studentCount, const char* facultyNumber) {
    for (int i = 0; i < studentCount; ++i) {
        if (std::strcmp(students[i].facultyNumber, facultyNumber) == 0) {
            print_student(students[i]);
            return;
        }
    }
    std::cout << "Student with faculty number " << facultyNumber << " not found.\n";
}

void update_student_email(Student students[], int studentCount, const char* facultyNumber, const char* faculty, const char* newEmail) {
    for (int i = 0; i < studentCount; ++i) {
        if (std::strcmp(students[i].facultyNumber, facultyNumber) == 0 && std::strcmp(students[i].faculty, faculty) == 0) {
            std::strcpy(students[i].email, newEmail);
            std::cout << "Email updated for student " << students[i].firstName << " " << students[i].lastName << "\n";
            return;
        }
    }
    std::cout << "Student with faculty number " << facultyNumber << " and faculty " << faculty << " not found.\n";
}

void save_students_to_file(const Student students[], int studentCount, const char* filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < studentCount; ++i) {
        file << students[i].firstName << ","
             << students[i].lastName << ","
             << students[i].facultyNumber << ","
             << students[i].email << ","
             << students[i].faculty << "\n";
    }

    file.close();
}

int main() {
    char filename[MAX_LENGTH];
    std::cout << "Enter the filename with student data: ";
    std::cin >> filename;

    Student students[MAX_STUDENTS];
    int studentCount = load_students(filename, students);

    if (studentCount == 0) {
        std::cout << "No students found or error loading file.\n";
        return 1;
    }

    char facultyNumber[MAX_LENGTH];
    std::cout << "Enter faculty number to search for: ";
    std::cin >> facultyNumber;
    print_student_by_faculty_number(students, studentCount, facultyNumber);

    char faculty[MAX_LENGTH];
    char newEmail[MAX_LENGTH];
    std::cout << "Enter faculty number to update email: ";
    std::cin >> facultyNumber;
    std::cin.ignore();
    std::cout << "Enter faculty name (specialty): ";
    std::cin.getline(faculty, MAX_LENGTH);
    std::cout << "Enter new email: ";
    std::cin >> newEmail;
    update_student_email(students, studentCount, facultyNumber, faculty, newEmail);

    save_students_to_file(students, studentCount, filename);

    return 0;
}
