#include "student.h"

Student::Student(std::string name, std::string sid, double cppScore, double javaScore) 
{
    this->name = name;
    this->sid = sid;
    this->cppScore = cppScore;
    this->javaScore = javaScore;
}

Student::~Student()
{

}

double Student::score() const
{
    return this->cppScore + this->javaScore;
}

std::string Student::getName()
{
    return this->name;
}
std::string Student::getSid()
{
    return this->sid;
}

bool Student::operator>(const Student &s) const
{
    return this->score() > s.score();
}

bool Student::operator<(const Student &s) const
{
    return this->score() < s.score();
}

bool Student::operator==(const Student &s) const
{
    return this->score() == s.score();
}

bool Student::operator>=(const Student &s) const
{
    return this->score() >= s.score();
}

bool Student::operator<=(const Student &s) const
{
    return this->score() <= s.score();
}