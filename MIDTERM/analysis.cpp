// analysis.cpp

#include "analysis.h"
#include "grade.h"
#include "util.h"
#include "Student_info.h"
#include <algorithm>

double median(const std::vector<double>& vec) {
    if (vec.empty())
        throw std::domain_error("median of an empty vector");

    std::vector<double> sorted_vec(vec);
    std::sort(sorted_vec.begin(), sorted_vec.end());

    std::vector<double>::size_type mid = sorted_vec.size() / 2;

    if (sorted_vec.size() % 2 == 0)
        return (sorted_vec[mid - 1] + sorted_vec[mid]) / 2;
    else
        return sorted_vec[mid];
}

double grade(double midterm, double final, const std::vector<double>& hw) {
    if (hw.empty())
        throw std::domain_error("student has done no homework");

    return 0.2 * midterm + 0.4 * final + 0.4 * median(hw);
}

double optimistic_median(const Student_info& s) {
    std::vector<double> nonzero;
    std::remove_copy(s.homework.begin(), s.homework.end(), std::back_inserter(nonzero), 0);

    if (nonzero.empty())
        return grade(s.midterm, s.final, 0);
    else
        return grade(s.midterm, s.final, median(nonzero));
}

double median_analysis(const std::vector<Student_info>& students) {
    std::vector<double> grades;
    std::transform(students.begin(), students.end(),
        std::back_inserter(grades), optimistic_median);
    return median(grades);
}

double average(const std::vector<double>& v) {
    if (v.empty())
        throw std::domain_error("average of an empty vector");

    return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double average_grade(const Student_info& s) {
    return grade(s.midterm, s.final, average(s.homework));
}

double average_analysis(const std::vector<Student_info>& students) {
    std::vector<double> grades;
    std::transform(students.begin(), students.end(),
        std::back_inserter(grades), average_grade);
    return median(grades);
}

void write_analysis(std::ostream& out, const std::string& name,
    double analysis(const std::vector<Student_info>&),
    const std::vector<Student_info>& did,
    const std::vector<Student_info>& didnt) {
    out << name << ": median(did) = " << analysis(did)
        << ", median(didnt) = " << analysis(didnt) << std::endl;
}