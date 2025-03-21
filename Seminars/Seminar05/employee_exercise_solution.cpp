#include <iostream>
#include <cstring>

struct EmployeeType {
    enum class Value { FULL_TIME, PART_TIME, FREELANCER };

    Value type;

    EmployeeType(Value t) : type(t) {}

    const char* to_string() const {
        switch (type) {
        case Value::FULL_TIME: return "Full-Time";
        case Value::PART_TIME: return "Part-Time";
        case Value::FREELANCER: return "Freelancer";
        default: return "Unknown";
        }
    }
};

class Employee {
private:
    char* name;
    int id;
    EmployeeType type;  // Using EmployeeType struct
    double salary;
    int hours_worked;  // For part-time employees
    int projects_completed;  // For freelancers

public:
    // Constructor
    Employee(const char* emp_name, int emp_id, EmployeeType emp_type, double emp_salary, int hours = 0, int projects = 0)
        : id(emp_id), type(emp_type), salary(emp_salary), hours_worked(hours), projects_completed(projects) {

        size_t emp_name_length = strlen(emp_name);
        name = new char[emp_name_length + 1];
        strcpy_s(name, emp_name_length + 1, emp_name);
    }

    // Destructor
    ~Employee() {
        std::cout << "Destroying Employee: " << name << std::endl;
        delete[] name;
    }

    // Copy Constructor (Deep Copy)
    Employee(const Employee& other)
        : id(other.id), type(other.type), salary(other.salary), hours_worked(other.hours_worked), projects_completed(other.projects_completed) {

        size_t other_name_size = strlen(other.name);
        name = new char[other_name_size + 1];
        strcpy_s(name, other_name_size + 1, other.name);

        std::cout << "Copy Constructor called for: " << name << std::endl;
    }

    // Copy Assignment Operator (Deep Copy)
    Employee& operator=(const Employee& other) {
        if (this != &other) { // Avoid self-assignment
            delete[] name;

            size_t other_name_size = strlen(other.name);
            name = new char[other_name_size + 1];
            strcpy_s(name, other_name_size + 1, other.name);

            id = other.id;
            type = other.type;
            salary = other.salary;
            hours_worked = other.hours_worked;
            projects_completed = other.projects_completed;

            std::cout << "Copy Assignment Operator called for: " << name << std::endl;
        }
        return *this;
    }

    // Salary Calculation (Encapsulation)
    double calculate_salary() const {
        switch (type.type) {
        case EmployeeType::Value::FULL_TIME:
            return salary * 0.8; // Deduct 20% tax
        case EmployeeType::Value::PART_TIME:
            return salary * hours_worked; // Hourly rate * hours worked
        case EmployeeType::Value::FREELANCER:
            return salary * projects_completed; // Payment per project
        default:
            return 0.0;
        }
    }

    void change_salary(double new_salary) {
        salary = new_salary;
    }

    void add_project_completed(int completed_projects) {
        projects_completed += completed_projects;
    }

    void add_hours_worked(int worked_hours) {
        hours_worked += worked_hours;
    }
    
    // Display Employee Information
    void display_info() const {
        std::cout << "Employee ID: " << id << ", Name: " << name
            << ", Type: " << type.to_string()
            << ", Calculated Salary: $" << calculate_salary() << std::endl;
    }
};

int main() {
    Employee emp1("Alice Johnson", 101, EmployeeType(EmployeeType::Value::FULL_TIME), 5000);
    Employee emp2("Bob Smith", 102, EmployeeType(EmployeeType::Value::PART_TIME), 20, 80);
    Employee emp3("Charlie Brown", 103, EmployeeType(EmployeeType::Value::FREELANCER), 500, 0, 3);

    emp1.display_info();
    emp2.display_info();
    emp3.display_info();

    Employee emp4 = emp1; // Copy Constructor
    emp4.display_info();

    emp2 = emp3; // Copy Assignment Operator
    emp2.display_info();

    return 0;
}
