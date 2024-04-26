#pragma once
// analysis.h

#ifndef GUARD_analysis_h
#define GUARD_analysis_h

#include <iostream>
#include <string>
#include <vector>
#include "Student_info.h"

double median(const std::vector<double>&);
double grade(double, double, const std::vector<double>&);
double optimistic_median(const Student_info&);
double median_analysis(const std::vector<Student_info>&);
double average(const std::vector<double>&);
double average_grade(const Student_info&);
double average_analysis(const std::vector<Student_info>&);

void write_analysis(std::ostream& out, const std::string& name,
    double analysis(const std::vector<Student_info>&),
    const std::vector<Student_info>& did,
    const std::vector<Student_info>& didnt);

#endif // GUARD_analysis_h