#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Subject {
    string subjectName;
    int grade;
};
struct Student {
    string name;
    string studentID;
    Subject subjects[3];
    double gpa;
};
void inputStudents(Student students[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "\n--- " << i + 1 << "-студенттің мәліметтерін енгізу ---" << endl;
        cout << "Аты-жөні: ";
        getline(cin, students[i].name);
        cout << "Билет нөмірі (ID): ";
        getline(cin, students[i].studentID);
        for (int j = 0; j < 3; j++) {
            cout << "  " << j + 1 << "-пән атауы: ";
            getline(cin, students[i].subjects[j].subjectName);
            while (true) {
                cout << "  " << j + 1 << "-пән бағасы (0-100): ";
                if (cin >> students[i].subjects[j].grade && 
                    students[i].subjects[j].grade >= 0 && 
                    students[i].subjects[j].grade <= 100) {
                    cin.ignore();
                    break;
                } else {
                    cout << "  [Қате]: Баға 0 мен 100 аралығындағы бүтін сан болуы керек! Қайта енгізіңіз.\n";
                    cin.clear();
                    while (cin.get() != '\n');
                }
            }
        }
    }
}
void calculateGPA(Student students[], int n) {
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < 3; j++) {
            sum += students[i].subjects[j].grade;
        }
        students[i].gpa = (double)sum / 3.0;
    }
}
void findAndPrintTopStudents(const Student students[], int n) {
    double maxGpa = students[0].gpa;
    for (int i = 1; i < n; i++) {
        if (students[i].gpa > maxGpa) {
            maxGpa = students[i].gpa;
        }
    }
    cout << "\n======================== ҮЗДІК СТУДЕНТ(ТЕР) ========================" << endl;
    cout << "Ең жоғары балл (Max GPA): " << fixed << setprecision(2) << maxGpa << endl;
    cout << "-------------------------------------------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        if (students[i].gpa == maxGpa) {
            cout << "Аты-жөні: " << students[i].name 
                 << " | Билеті: " << students[i].studentID 
                 << " | GPA: " << fixed << setprecision(2) << students[i].gpa << endl;
        }
    }
    cout << "===================================================================" << endl;
}
void printAllStudents(const Student students[], int n) {
    cout << "\n======================== СЕССИЯ ҚОРЫТЫНДЫСЫ ========================" << endl;
    cout << left 
         << setw(4)  << "No" 
         << setw(20) << "Aty" 
         << setw(12) << "ID" 
         << setw(8)  << "Pan 1" 
         << setw(8)  << "Pan 2" 
         << setw(8)  << "Pan 3" 
         << setw(8)  << "GPA" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        cout << left 
             << setw(4)  << i + 1
             << setw(20) << students[i].name
             << setw(12) << students[i].studentID
             << setw(8)  << students[i].subjects[0].grade
             << setw(8)  << students[i].subjects[1].grade
             << setw(8)  << students[i].subjects[2].grade
             << fixed << setprecision(2) << setw(8) << students[i].gpa 
             << endl;
    }
    cout << "===================================================================" << endl;
}
int main() {
    int n;
    cout << "Студенттер санын енгізіңіз: ";
    if (!(cin >> n) || n <= 0) {
        cout << "[Қате]: Студенттер саны нөлден үлкен бүтін сан болуы керек!" << endl;
        return 0;
    }
    cin.ignore();
    Student *students = new Student[n];
    inputStudents(students, n);
    calculateGPA(students, n);
    printAllStudents(students, n);
    findAndPrintTopStudents(students, n);
    delete[] students;
    return 0;
}