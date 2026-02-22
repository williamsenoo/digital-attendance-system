#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/* =====================================================
   STUDENT CLASS  (Week 1)
===================================================== */
class Student {
public:
    string name;
    string indexNumber;

    Student(string n, string i) {
        name = n;
        indexNumber = i;
    }

    void display() const {
        cout << "Name: " << name
             << " | Index: " << indexNumber << endl;
    }
};

vector<Student> students;

/* =====================================================
   ATTENDANCE SESSION CLASS (Week 2)
===================================================== */
class AttendanceSession {
public:
    string courseCode;
    string date;
    string startTime;
    int duration;

    AttendanceSession(string c, string d, string s, int dur) {
        courseCode = c;
        date = d;
        startTime = s;
        duration = dur;
    }

    void display() const {
        cout << "Course: " << courseCode
             << " | Date: " << date
             << " | Start: " << startTime
             << " | Duration: " << duration << " hour(s)" << endl;
    }
};

vector<AttendanceSession> sessions;

/* =====================================================
   ATTENDANCE RECORD CLASS (Week 3)
===================================================== */
class AttendanceRecord {
public:
    string studentIndex;
    string courseCode;
    string date;
    string status;

    AttendanceRecord(string s, string c, string d, string st) {
        studentIndex = s;
        courseCode = c;
        date = d;
        status = st;
    }
};

vector<AttendanceRecord> attendanceRecords;

/* =====================================================
   FILE LOADING FUNCTIONS (Week 4)
===================================================== */
void loadStudents() {
    ifstream file("students.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string name, index;
        getline(ss, name, ',');
        getline(ss, index);
        students.push_back(Student(name, index));
    }
    file.close();
}

void saveStudents() {
    ofstream file("students.txt");
    for (auto &s : students)
        file << s.name << "," << s.indexNumber << endl;
    file.close();
}

void saveAttendance() {
    ofstream file("attendance.txt");
    for (auto &r : attendanceRecords)
        file << r.studentIndex << ","
             << r.courseCode << ","
             << r.date << ","
             << r.status << endl;
    file.close();
}

/* =====================================================
   STUDENT FUNCTIONS (Week 1)
===================================================== */
void registerStudent() {
    string name, index;

    cin.ignore();
    cout << "Enter Student Name: ";
    getline(cin, name);

    cout << "Enter Index Number: ";
    getline(cin, index);

    students.push_back(Student(name, index));
    saveStudents();

    cout << "Student registered successfully!\n";
}

void viewStudents() {
    if (students.empty()) {
        cout << "No students registered.\n";
        return;
    }

    for (auto &s : students)
        s.display();
}

void searchStudent() {
    string index;
    cout << "Enter index number: ";
    cin >> index;

    for (auto &s : students) {
        if (s.indexNumber == index) {
            s.display();
            return;
        }
    }

    cout << "Student not found.\n";
}

/* =====================================================
   SESSION FUNCTIONS (Week 2)
===================================================== */
void createSession() {
    string course, date, time;
    int duration;

    cout << "Enter Course Code: ";
    cin >> course;

    cout << "Enter Date (YYYY-MM-DD): ";
    cin >> date;

    cout << "Enter Start Time: ";
    cin >> time;

    cout << "Enter Duration (hours): ";
    cin >> duration;

    sessions.push_back(AttendanceSession(course, date, time, duration));

    // Save session file
    ofstream file("session_" + course + "_" + date + ".txt");
    file << course << "," << date << "," << time << "," << duration << endl;
    file.close();

    cout << "Session created successfully!\n";
}

/* =====================================================
   ATTENDANCE FUNCTIONS (Week 3)
===================================================== */
void markAttendance() {
    if (students.empty() || sessions.empty()) {
        cout << "Students or sessions not available.\n";
        return;
    }

    AttendanceSession session = sessions.back();

    for (auto &s : students) {
        char response;
        cout << "Status for " << s.name
             << " (P=Present, A=Absent, L=Late): ";
        cin >> response;

        string status;
        if (response=='P'||response=='p') status="Present";
        else if (response=='L'||response=='l') status="Late";
        else status="Absent";

        attendanceRecords.push_back(
            AttendanceRecord(s.indexNumber,
                             session.courseCode,
                             session.date,
                             status)
        );
    }

    cout << "Attendance marked successfully!\n";
}

void attendanceSummary() {
    int present=0, absent=0, late=0;

    for (auto &r : attendanceRecords) {
        if (r.status=="Present") present++;
        else if (r.status=="Late") late++;
        else absent++;
    }

    cout << "\nAttendance Summary\n";
    cout << "Present: " << present << endl;
    cout << "Late: " << late << endl;
    cout << "Absent: " << absent << endl;
}

void viewSessionAttendance() {
    string course;
    cout << "Enter Course Code: ";
    cin >> course;

    for (auto &r : attendanceRecords) {
        if (r.courseCode == course) {
            cout << "Index: " << r.studentIndex
                 << " | Date: " << r.date
                 << " | Status: " << r.status << endl;
        }
    }
}

/* =====================================================
   MAIN MENU
===================================================== */
int main() {

    loadStudents();

    int choice;

    do {
        cout << "\n===== DIGITAL ATTENDANCE SYSTEM =====\n";
        cout << "1. Register Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Create Attendance Session\n";
        cout << "5. Mark Attendance\n";
        cout << "6. View Session Attendance\n";
        cout << "7. Attendance Summary\n";
        cout << "8. Save Attendance to File\n";
        cout << "9. Exit\n";
        cout << "Choice: ";

        cin >> choice;

        if(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"Invalid input!\n";
            continue;
        }

        switch (choice) {
            case 1: registerStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: createSession(); break;
            case 5: markAttendance(); break;
            case 6: viewSessionAttendance(); break;
            case 7: attendanceSummary(); break;
            case 8: saveAttendance(); break;
            case 9: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 9);

    return 0;
}