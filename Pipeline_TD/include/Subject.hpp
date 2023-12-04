#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <utility>   // pair
#include <algorithm> // sort

template <typename Name, typename Grade>
class Subject
{
private:
    using Student = std::pair<Grade, Name>;

    Name subjectName;
    std::vector<Student> students;

    std::set<Name> existStudents;  // check if a student exists
    std::set<Name> absentStudents; // check if a student is absent

    // Max and min grade
    bool hasMaxMinGrade = false;
    Grade maxGrade;
    Grade minGrade;
    // store the sum of grades, if the sum overflows, set overMax to true
    bool overMax = false;
    Grade sumGrade = 0; // initial value is 0

    void updateMaxMinGrade(); // update maxGrade and minGrade

public:
    Subject() = default;
    Subject(const Subject &other) = default;
    Subject(Subject &&other) = default;
    Subject &operator=(const Subject &other) = default;
    Subject &operator=(Subject &&other) = default;
    ~Subject() = default;
    Subject(Name subjectName) : subjectName(subjectName){};

    bool hasStudent(Name name) const;
    void addStudent(Name name, Grade grade);
    void changeStudentGrade(Name name, Grade grade);
    void sortStudents();
    void printMaxMinGrade(std::ostream &os = std::cout) const;
    void printAverageGrade(std::ostream &os = std::cout) const;
    std::set<Name> getAbsentStudents() const;

    // for test
    std::vector<Student> getStudents() const;
    void printStudents(std::ostream &os = std::cout) const;
};

template <typename Name, typename Grade>
bool Subject<Name, Grade>::hasStudent(Name name) const
{
    return this->existStudents.find(name) != this->existStudents.end();
}

template <typename Name, typename Grade>
void Subject<Name, Grade>::addStudent(Name name, Grade grade)
{
    // if grade is -1, the student is absent
    if (grade == -1)
    {
        this->absentStudents.insert(name);
        return;
    }
    this->existStudents.insert(name);
    this->students.emplace_back(grade, name);

    // update maxGrade and minGrade
    if (!this->hasMaxMinGrade)
    {
        this->hasMaxMinGrade = true;
        this->maxGrade = grade;
        this->minGrade = grade;
    }
    else
    {
        if (grade > this->maxGrade)
            this->maxGrade = grade;
        if (grade < this->minGrade)
            this->minGrade = grade;
    }

    this->sumGrade += grade;
    if (this->sumGrade < grade) // overflow
        this->overMax = true;
}

template <typename Name, typename Grade>
void Subject<Name, Grade>::changeStudentGrade(Name name, Grade grade)
{
    // if the student is absent, add the student
    if (this->absentStudents.find(name) != this->absentStudents.end())
    {
        this->absentStudents.erase(name);
        this->addStudent(name, grade);
        return;
    }

    bool hasStudent = false;
    for (auto it = this->students.begin(); it != this->students.end(); ++it)
    {
        if (it->second == name)
        {
            hasStudent = true;
            Grade oldGrade = it->first;
            if (grade == -1)
            {
                this->students.erase(it);
                this->existStudents.erase(name);
                this->absentStudents.insert(name);
                if (oldGrade == this->maxGrade || oldGrade == this->minGrade)
                    this->updateMaxMinGrade();
                this->sumGrade -= oldGrade;
            }
            else
            {
                it->first = grade;
                if (grade > this->maxGrade)
                    this->maxGrade = grade;
                else if (grade < this->minGrade)
                    this->minGrade = grade;
                else if (oldGrade == this->maxGrade || oldGrade == this->minGrade)
                    this->updateMaxMinGrade();

                this->sumGrade += grade - oldGrade;
                if (this->sumGrade < grade - oldGrade) // overflow
                    this->overMax = true;
            }
        }
    }
    if (!hasStudent)
        std::cout << "没有学生" << name << std::endl;
}

template <typename Name, typename Grade>
void Subject<Name, Grade>::sortStudents()
{
    sort(this->students.begin(), this->students.end(), [](const Student &s1, const Student &s2)
         { return s1.first > s2.first; });

    std::cout << this->subjectName << "的成绩排序如下：" << std::endl;
    for (auto it = this->students.begin(); it != this->students.end(); ++it)
        std::cout << it - this->students.begin() + 1 << " " << it->second << " " << it->first << std::endl;
}

template <typename Name, typename Grade>
void Subject<Name, Grade>::updateMaxMinGrade()
{
    this->maxGrade = max_element(this->students.begin(), this->students.end(), [](const Student &s1, const Student &s2)
                                 { return s1.first < s2.first; })
                         ->first;
    this->minGrade = min_element(this->students.begin(), this->students.end(), [](const Student &s1, const Student &s2)
                                 { return s1.first < s2.first; })
                         ->first;
}

template <typename Name, typename Grade>
void Subject<Name, Grade>::printMaxMinGrade(std::ostream &os) const
{
    if (!this->hasMaxMinGrade)
        os << this->subjectName << "没有学生成绩" << std::endl;
    else
    {
        os << this->subjectName << "的最高分：" << this->maxGrade << "，最低分：" << this->minGrade << std::endl;
    }
}

template <typename Name, typename Grade>
void Subject<Name, Grade>::printAverageGrade(std::ostream &os) const
{
    if (this->students.empty())
        os << this->subjectName << "没有学生成绩" << std::endl;
    else if (!overMax)
    {
        os << this->subjectName << "的平均分："
           << static_cast<Grade>(this->sumGrade / this->students.size()) << std::endl;
    }
    else
    {
        size_t num = this->students.size();
        double average = static_cast<double>(this->students[0].first / num);
        for (auto it = this->students.begin() + 1; it != this->students.end(); ++it)
            average += static_cast<double>(it->first / num);
        os << this->subjectName << "的平均分：" << average << std::endl;
    }
}

template <typename Name, typename Grade>
std::set<Name> Subject<Name, Grade>::getAbsentStudents() const
{
    return this->absentStudents;
}

template <typename Name, typename Grade>
std::vector<typename Subject<Name, Grade>::Student> Subject<Name, Grade>::getStudents() const
{
    return this->students;
}

template <typename Name, typename Grade>
void Subject<Name, Grade>::printStudents(std::ostream &os) const
{
    for (auto it = this->students.begin(); it != this->students.end(); ++it)
        os << it - this->students.begin() + 1 << " " << it->second << " " << it->first << std::endl;
}
