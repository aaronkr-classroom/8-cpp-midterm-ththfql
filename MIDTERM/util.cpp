// util.cpp
// util.cpp

#include <algorithm>
#include <fstream> 
#include <iomanip>
#include <iostream>
#include <numeric> 

#include "analysis.h"
#include "Student_info.h"
#include "util.h"

using namespace std;

double average(const vector<double>& v) {
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

bool did_all_hw(const Student_info& s) {
    return ((find(s.homework.begin(), s.homework.end(), 0)) == s.homework.end());
}

int printGreeting() {
    cout << "Welcome to Student Gradebook!" << endl;
    cout << "==============================" << endl << endl;

    cout << "Which file would you like to load?" << endl;
    cout << "1. Original grades.txt (20 students)" << endl;
    cout << "2. All homework grades_did.txt (24 students)" << endl;
    cout << "3. No homework grades_didnt.txt (18 students)" << endl;
    cout << "0. Quit" << endl;
    cout << "Selection: ";

    int choice;
    while (cin >> choice) {
        if (choice != 0 && choice != 1 && choice != 2 && choice != 3) {
            cout << "Invalid selection. Choose 1, 2, 3, or 0 to quit: ";
        }
        else {
            return choice;
        }
    }

    cout << endl;
}

void printMenu() {
    cout << "------------------------------" << endl
        << "1. Check homework" << endl
        << "2. Analyze Grades" << endl
        << "3. Show Final Scores" << endl
        << "4. Return to File Selection" << endl
        << "0. Quit" << endl
        << "------------------------------" << endl
        << "Choice: ";
}

void loadGrades(ifstream& student_file,
    vector<Student_info>& students,
    vector<Student_info>& did,
    vector<Student_info>& didnt,
    string::size_type& maxlen
) {
    Student_info record;

    while (read(student_file, record)) {
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);

        if (did_all_hw(record)) {
            did.push_back(record);
        }
        else {
            didnt.push_back(record);
        }
    }

    cout << "Read " << students.size() << " records." << endl << endl;
}

void fileSelect(int fileChoice,
    vector<Student_info>& students,
    vector<Student_info>& did,
    vector<Student_info>& didnt,
    string::size_type& maxlen
) {
    students.clear();
    did.clear();
    didnt.clear();

    if (fileChoice == 1) {
        ifstream student_file("grades.txt");
        loadGrades(student_file, students, did, didnt, maxlen);
    }
    else if (fileChoice == 2) {
        ifstream student_file("grades_did.txt");
        loadGrades(student_file, students, did, didnt, maxlen);
    }
    else if (fileChoice == 3) {
        ifstream student_file("grades_didnt.txt");
        loadGrades(student_file, students, did, didnt, maxlen);
    }
    else
        cout << "Invalid file choice.";
}

int checkHw(vector<Student_info>& did, vector<Student_info>& didnt) {
    cout << endl;

    if (did.empty()) {
        cout << "No student did all the homework!" << endl;
        return 1;
    }
    if (didnt.empty()) {
        cout << "Every student did all the homework!" << endl;
        return 1;
    }
    cout << did.size() << " students did all the homework." << endl;
    cout << didnt.size() << " students didn't do all the homework." << endl;

    cout << endl;
}

void write_analysis(ostream& out, const string& name,
    double analysis(const vector<Student_info>&),
    const vector<Student_info>& students,
    string vec) {

    out << name << ": median(" << vec << ") = " << analysis(students) << endl;

}

double optimistic_median_analysis(const vector<Student_info>& students) {
    vector<double> grades;

    for (const auto& student : students) {
        double grade = optimistic_median(student);
        grades.push_back(grade);
    }

    return median(grades);
}

void analyzeGrades(vector<Student_info>& did, vector<Student_info>& didnt) {
    cout << endl;

    if (did.empty()) {
        write_analysis(cout, "average", average_analysis, didnt, "didnt");
        write_analysis(cout, "median", median_analysis, didnt, "didnt");
        write_analysis(cout, "median of homework turned in",
            optimistic_median_analysis, didnt, "didnt");
        cout << endl;
        return;
    }

    if (didnt.empty()) {
        write_analysis(cout, "average", average_analysis, did, "did");
        write_analysis(cout, "median", median_analysis, did, "did");
        write_analysis(cout, "median of homework turned in",
            optimistic_median_analysis, did, "did");
        cout << endl;
        return;
    }

    write_analysis(cout, "average", average_analysis, did, didnt);
    write_analysis(cout, "median", median_analysis, did, didnt);
    write_analysis(cout, "median of homework turned in",
        optimistic_median_analysis, did, didnt);

    cout << endl;
}

void showScores(vector<Student_info>& students, string::size_type& maxlen) {
    cout << endl;

    sort(students.begin(), students.end(), compare);

    for (vector<Student_info>::size_type i = 0; i != students.size(); ++i) {
        cout << students[i].name
            << string(maxlen + 1 - students[i].name.size(), ' ');

        try {
            double final_grade = grade(students[i]);
            streamsize prec = cout.precision();
            cout << "Final grade: " << setprecision(3)
                << final_grade << setprecision(prec) << endl;
        }
        catch (domain_error e) {
            cout << e.what();
        }
    }

    cout << endl;
}