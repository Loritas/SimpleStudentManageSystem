#ifndef __STUDENT_H__
#define __STUDENT_H__
#include <string>

class Student
{
private:
    std::string name;
    std::string sid;
    double cppScore;
    double javaScore;
public:
    Student(std::string, std::string, double, double);
    ~Student();

    double score() const;
    std::string getName();
    std::string getSid();

    bool operator>(const Student &) const;
    bool operator<(const Student &) const;
    bool operator==(const Student &) const;
    bool operator>=(const Student &) const;
    bool operator<=(const Student &) const;
};

#endif