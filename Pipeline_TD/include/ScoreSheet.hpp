#pragma once

#include "subject.hpp"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>

template <typename Grade>
class ScoreSheet
{
private:
    using Name = std::string;
    std::unordered_map<Name, Subject<Name, Grade>> subjects;

public:
    ScoreSheet() = default;
    ScoreSheet(const ScoreSheet &other) = default;
    ScoreSheet(ScoreSheet &&other) = default;
    ScoreSheet &operator=(const ScoreSheet &other) = default;
    ScoreSheet &operator=(ScoreSheet &&other) = default;
    ~ScoreSheet() = default;

    bool run();
    void addScore();
    void loadScoreFromFile();
    void checkScore();
    void checkScore_1(const Name &subject) const;
    void checkScore_2();
    void checkScore_3() const;
    void changeScore();
    std::unordered_map<Name, std::set<Name>> getAbsentStudents() const;

    // for test
    void printScoreSheet(std::ostream &os = std::cout) const;
};

template <typename Grade>
bool ScoreSheet<Grade>::run()
{
    while (true)
    {
        std::cout << "请选择操作：" << std::endl;
        std::cout << "1. 录入成绩" << std::endl;
        std::cout << "2. 从文件中导入成绩" << std::endl;
        std::cout << "3. 查询成绩" << std::endl;
        std::cout << "4. 修改成绩" << std::endl;
        std::cout << "5. 拓展功能" << std::endl;
        std::cout << "6. 退出" << std::endl;

        int choice;
        std::cin >> choice;
        while (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "输入错误! 请重新输入：";
            std::cin >> choice;
        }

        switch (choice)
        {
        case 1:
            this->addScore();
            break;
        case 2:
            this->loadScoreFromFile();
            break;
        case 3:
            this->checkScore();
            break;
        case 4:
            this->changeScore();
            break;
        case 5:
            // enter the extended function
            return true;
        case 6:
            this->printScoreSheet();
            return false;
        default:
            std::cout << "输入错误！" << std::endl;
            break;
        }
    }
}

template <typename Grade>
void ScoreSheet<Grade>::addScore()
{
    std::cout << "请输入学生姓名：";
    std::string name;
    std::cin >> name;

    while (true)
    {
        std::cout << "请输入学科名称：";
        std::string subject;
        std::cin >> subject;

        std::cout << "请输入学生成绩(用-1表示缺省)："; // the default value is handled in Subject::addStudent
        Grade grade;
        std::cin >> grade;
        // while (std::cin.fail())
        // {
        //     std::cin.clear();
        //     std::cin.ignore();
        //     std::cout << "输入错误! 请重新输入：";
        //     std::cin >> grade;
        // }

        // check if the student already exists
        if (this->subjects.find(subject) != this->subjects.end() &&
            this->subjects[subject].hasStudent(name))
        {
            std::cout << "该学生已经存在！" << std::endl;
            break;
        }

        // if the subject does not exist, create a new one
        if (this->subjects.find(subject) == this->subjects.end())
            this->subjects.emplace(subject, Subject<Name, Grade>(subject));
        this->subjects[subject].addStudent(name, grade);

        std::cout << "是否继续输入？(y/n)";
        std::string choice;
        std::cin >> choice;
        if (choice == "n")
            break;
    }
}

template <typename Grade>
void ScoreSheet<Grade>::loadScoreFromFile()
{
    std::cout << "请输入文件名：";
    std::string filename;
    std::cin >> filename;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "文件打开失败！" << std::endl;
        return;
    }

    std::string line;

    // enter the first line: name subject1 subject2 ...
    std::vector<std::string> subjects;
    std::getline(file, line);
    std::stringstream ss(line);
    std::string name;
    std::string subject;
    ss >> name;
    while (ss >> subject)
        subjects.push_back(subject);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        Grade grade;
        ss >> name;
        for (const auto &subject : subjects)
        {
            std::string str;
            ss >> str;
            try // if the grade is not a number, set it to -1 (default value)
            {
                grade = std::stod(str);
            }
            catch (...)
            {
                grade = -1;
            }        

            // check if the student already exists
            if (this->subjects.find(subject) != this->subjects.end() &&
                this->subjects[subject].hasStudent(name))
            {
                std::cout << "该学生已经存在！" << std::endl;
                break;
            }

            // if the subject does not exist, create a new one
            if (this->subjects.find(subject) == this->subjects.end())
                this->subjects.emplace(subject, Subject<Name, Grade>(subject));
            this->subjects[subject].addStudent(name, grade);
        }
    }
}

template <typename Grade>
void ScoreSheet<Grade>::checkScore()
{
    std::cout << "请选择查询操作" << std::endl;
    std::cout << "a. 查询科目最高/最低分" << std::endl;
    std::cout << "b. 以各科成绩对同学姓名排序" << std::endl;
    std::cout << "c. 查询各科目平均分" << std::endl;

    std::string choice;
    std::cin >> choice;

    if (choice == "a")
    {
        std::cout << "请输入科目名称：";
        std::string subject;
        std::cin >> subject;
        this->checkScore_1(subject);
    }
    else if (choice == "b")
    {
        this->checkScore_2();
    }
    else if (choice == "c")
    {
        this->checkScore_3();
    }
    else
    {
        std::cout << "输入错误！" << std::endl;
    }
    std::cout << std::endl;
}

template <typename Grade>
void ScoreSheet<Grade>::checkScore_1(const std::string &subject) const
{
    if (this->subjects.find(subject) == this->subjects.end())
    {
        std::cout << subject << "不存在！" << std::endl;
        return;
    }
    this->subjects.at(subject).printMaxMinGrade();
}

template <typename Grade>
void ScoreSheet<Grade>::checkScore_2()
{
    for (auto &subject : this->subjects)
    {
        subject.second.sortStudents();
    }
}

template <typename Grade>
void ScoreSheet<Grade>::checkScore_3() const
{
    for (const auto &subject : this->subjects)
    {
        subject.second.printAverageGrade();
    }
}

template <typename Grade>
void ScoreSheet<Grade>::changeScore()
{
    std::cout << "请输入学生姓名：";
    std::string name;
    std::cin >> name;

    std::cout << "请输入学科名称：";
    std::string subject;
    std::cin >> subject;

    std::cout << "请输入学生成绩：";
    Grade grade;
    std::cin >> grade;
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "输入错误! 请重新输入：";
        std::cin >> grade;
    }

    if (this->subjects.find(subject) == this->subjects.end())
    {
        std::cout << "科目不存在！" << std::endl;
        return;
    }
    this->subjects[subject].changeStudentGrade(name, grade);
}

template <typename Grade>
std::unordered_map<typename ScoreSheet<Grade>::Name, std::set<typename ScoreSheet<Grade>::Name>> ScoreSheet<Grade>::getAbsentStudents() const
{
    std::unordered_map<Name, std::set<Name>> absentStudents;
    for (const auto &subject : this->subjects)
    {
        absentStudents[subject.first] = subject.second.getAbsentStudents();
    }
    return absentStudents;
}

template <typename Grade>
void ScoreSheet<Grade>::printScoreSheet(std::ostream &os) const
{
    for (const auto &subject : this->subjects)
    {
        os << subject.first << ":" << std::endl;
        subject.second.printStudents(os);
    }
}