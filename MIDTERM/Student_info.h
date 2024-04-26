#pragma once
// Student_info.h

#ifndef GUARD_Student_info
#define GUARD_Student_info

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student_info {
    std::string name;
    double midterm;
    double final;
    std::vector<double> homework;
};

// 변환 함수 추가
double grade(const Student_info&);
double optimistic_median(const Student_info&);
double average_grade(const Student_info&);



bool compare(const Student_info&, const Student_info&);
istream& read(istream&, Student_info&);
istream& read_hw(istream&, vector<double>&);

#endif