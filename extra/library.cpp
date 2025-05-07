#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Book {
    string title;
    string author;
    string field;
    string project_type;
    string difficulty;
};

vector<Book> library = {
    {"AI for Beginners", "John Smith", "AI", "theoretical", "beginner"},
    {"Hands-on Machine Learning", "Aurélien Géron", "AI", "practical", "intermediate"},
    {"Deep Learning Research", "Ian Goodfellow", "AI", "research", "advanced"},
    {"Data Structures in C++", "S. Sahni", "Programming", "theoretical", "beginner"},
    {"Competitive Programming 3", "Halim", "Programming", "practical", "advanced"},
    {"Database System Concepts", "Silberschatz", "Database", "theoretical", "intermediate"},
    {"SQL Practice Projects", "Jane Doe", "Database", "practical", "beginner"},
    {"Advanced Database Systems", "Ramakrishnan", "Database", "research", "advanced"},
    {"Network Security Basics", "Mark Daniels", "Networking", "theoretical", "beginner"},
    {"Practical Ethical Hacking", "Kevin Mitnick", "Networking", "practical", "intermediate"},
    {"Cybersecurity Research Trends", "Alex Lin", "Networking", "research", "advanced"}
};

void recommend_books(const string &field, const string &project_type, const string &difficulty) {
    vector<Book> recommendations;

    for (const auto &book : library) {
        if ((field == "any" || book.field == field) &&
            (project_type == "any" || book.project_type == project_type) &&
            (difficulty == "any" || book.difficulty == difficulty)) {
            recommendations.push_back(book);
        }
    }

    if (recommendations.empty()) {
        cout << "No suitable books found for the given preferences.\n";
    } else {
        cout << "\nRecommended Books:\n";
        for (const auto &book : recommendations) {
            cout << "- " << book.title << " by " << book.author
                 << " [" << book.field << ", " << book.project_type << ", " << book.difficulty << "]\n";
        }
    }
}

int main() {
    string field, project_type, difficulty;

    cout << "=== Library Expert System: Book Recommendation ===\n";
    cout << "Fields available: AI, Programming, Database, Networking\n";
    cout << "Enter your field of study (or type 'any'): ";
    cin >> field;

    cout << "Project type (theoretical / practical / research / any): ";
    cin >> project_type;

    cout << "Difficulty level (beginner / intermediate / advanced / any): ";
    cin >> difficulty;

    // Convert to lowercase to avoid mismatch
    transform(field.begin(), field.end(), field.begin(), ::tolower);
    transform(project_type.begin(), project_type.end(), project_type.begin(), ::tolower);
    transform(difficulty.begin(), difficulty.end(), difficulty.begin(), ::tolower);

    // Capitalize first letter for consistent comparison
    if (field != "any") field[0] = toupper(field[0]);

    recommend_books(field, project_type, difficulty);

    return 0;
}
