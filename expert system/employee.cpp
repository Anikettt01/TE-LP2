#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;

struct Employee {
    string id;
    string name;
    string department;
    string role;
    string doj;
    map<string, int> performance;
};

vector<Employee> employees;

map<string, double> performance_qualities = {
    {"Punctuality", 0.2},
    {"Communication", 0.15},
    {"Teamwork", 0.2},
    {"Problem Solving", 0.2},
    {"Initiative", 0.15},
    {"Technical Knowledge", 0.1}
};

string generate_emp_id() {
    return "E" + string(3 - to_string(employees.size() + 1).length(), '0') + to_string(employees.size() + 1);
}

void show_menu() {
    cout << "\n=== Employee Management Expert System ===\n";
    cout << "1. Add New Employee\n";
    cout << "2. View All Employees\n";
    cout << "3. Search Employee by ID\n";
    cout << "4. Update Employee Performance\n";
    cout << "5. View Performance Summary\n";
    cout << "6. HR Knowledge Base\n";
    cout << "7. Exit\n";
}

void add_employee() {
    cout << "\n--- Add New Employee ---\n";
    Employee emp;
    cout << "Enter full name: ";
    cin.ignore();
    getline(cin, emp.name);
    cout << "Enter department (e.g., IT, HR, Sales): ";
    getline(cin, emp.department);
    cout << "Enter job role: ";
    getline(cin, emp.role);
    cout << "Enter date of joining (DD/MM/YYYY): ";
    getline(cin, emp.doj);
    emp.id = generate_emp_id();

    for (auto &pq : performance_qualities) {
        emp.performance[pq.first] = -1; // placeholder for not yet rated
    }

    employees.push_back(emp);
    cout << "Employee added successfully. Employee ID: " << emp.id << "\n";
}

void view_all_employees() {
    cout << "\n--- All Employees ---\n";
    for (auto &e : employees) {
        cout << "\nID: " << e.id << "\n";
        cout << "Name: " << e.name << "\n";
        cout << "Department: " << e.department << "\n";
        cout << "Role: " << e.role << "\n";
        cout << "Date of Joining: " << e.doj << "\n";
        cout << "Performance:\n";
        for (auto &p : e.performance) {
            cout << "  " << p.first << ": ";
            if (p.second == -1) cout << "Not Rated\n";
            else cout << p.second << "\n";
        }
    }
}

void search_employee() {
    cout << "\n--- Search Employee by ID ---\n";
    string eid;
    cout << "Enter Employee ID: ";
    cin >> eid;
    for (auto &e : employees) {
        if (e.id == eid) {
            cout << "\nID: " << e.id << "\n";
            cout << "Name: " << e.name << "\n";
            cout << "Department: " << e.department << "\n";
            cout << "Role: " << e.role << "\n";
            cout << "Date of Joining: " << e.doj << "\n";
            cout << "Performance:\n";
            for (auto &p : e.performance) {
                cout << "  " << p.first << ": ";
                if (p.second == -1) cout << "Not Rated\n";
                else cout << p.second << "\n";
            }
            return;
        }
    }
    cout << "Employee not found.\n";
}

void update_performance() {
    cout << "\n--- Update Performance ---\n";
    string eid;
    cout << "Enter Employee ID: ";
    cin >> eid;
    for (auto &e : employees) {
        if (e.id == eid) {
            cout << "Enter performance ratings (1-10):\n";
            for (auto &pq : performance_qualities) {
                int score;
                cout << pq.first << ": ";
                cin >> score;
                e.performance[pq.first] = score;
            }
            cout << "Performance updated successfully.\n";
            return;
        }
    }
    cout << "Employee not found.\n";
}

double calculate_weighted_avg(map<string, int> &perf) {
    double total = 0, weight_sum = 0;
    for (auto &pq : performance_qualities) {
        if (perf[pq.first] != -1) {
            total += perf[pq.first] * pq.second;
            weight_sum += pq.second;
        }
    }
    return weight_sum == 0 ? 0 : total / weight_sum;
}

void view_performance_summary() {
    cout << "\n--- Employee Performance Summary ---\n";
    for (auto &e : employees) {
        bool complete = true;
        for (auto &p : e.performance) {
            if (p.second == -1) {
                complete = false;
                break;
            }
        }

        if (complete) {
            double avg = calculate_weighted_avg(e.performance);
            string grade;
            if (avg >= 9) grade = "Outstanding";
            else if (avg >= 7) grade = "Excellent";
            else if (avg >= 5) grade = "Satisfactory";
            else grade = "Needs Improvement";

            cout << "\n" << e.name << " (" << e.id << ") - Avg: " << fixed << setprecision(2) << avg << " | Grade: " << grade << "\n";
        } else {
            cout << "\n" << e.name << " (" << e.id << ") - Performance data incomplete\n";
        }
    }
}

void hr_knowledge_base() {
    cout << "\n--- HR Knowledge Base ---\n";
    cout << "Enter HR keyword (leave, bonus, late, policy): ";
    string query;
    cin >> query;

    if (query.find("leave") != string::npos)
        cout << "Suggestion: Employees can apply for up to 18 paid leaves per year via the HR portal.\n";
    else if (query.find("bonus") != string::npos)
        cout << "Suggestion: Bonuses are performance-based and disbursed in Q4 each year.\n";
    else if (query.find("late") != string::npos || query.find("attendance") != string::npos)
        cout << "Suggestion: More than 3 late logins in a month may affect performance review.\n";
    else if (query.find("policy") != string::npos)
        cout << "Suggestion: Refer to the company intranet > HR > Policy Documents.\n";
    else
        cout << "No suggestion found. Please contact HR.\n";
}

int main() {
    while (true) {
        show_menu();
        string choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1") add_employee();
        else if (choice == "2") view_all_employees();
        else if (choice == "3") search_employee();
        else if (choice == "4") update_performance();
        else if (choice == "5") view_performance_summary();
        else if (choice == "6") hr_knowledge_base();
        else if (choice == "7") {
            cout << "Exiting Employee Expert System...\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
