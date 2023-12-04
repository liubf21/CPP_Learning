#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/subject.hpp"
#include <string>
// #include <sstream>

DOCTEST_TEST_CASE("subject")
{
    Subject<std::string, int> sm("Math");
    sm.addStudent("Tom", 90);
    sm.addStudent("Jerry", 80);
    sm.addStudent("Alice", 85);
    sm.addStudent("Bob", 75);
    sm.addStudent("David", 95);
    sm.addStudent("Frank", 85);

    SUBCASE("Test hasStudent") {
        CHECK(sm.hasStudent("Tom"));
        CHECK_FALSE(sm.hasStudent("Peter"));
    }

    SUBCASE("Test changeStudentGrade") {
        CHECK_EQ(sm.getStudents()[1].first, 80);
        sm.changeStudentGrade("Jerry", 85);
        CHECK_EQ(sm.getStudents()[1].first, 85);
    }

    SUBCASE("Test sortStudents") {
        sm.sortStudents();
        CHECK_EQ(sm.getStudents()[0].second, "David");
        CHECK_EQ(sm.getStudents()[5].second, "Bob");
    }

    SUBCASE("Test printMaxMinGrade") {
        std::ostringstream oss;
        sm.printMaxMinGrade(oss);
        CHECK_EQ(oss.str(), "Math的最高分：95，最低分：75\n");
    }

    SUBCASE("Test printAverageGrade") {
        std::ostringstream oss;
        sm.printAverageGrade(oss);
        CHECK_EQ(oss.str(), "Math的平均分：85\n");
    }

    SUBCASE("Test getAbsentStudents") {
        sm.changeStudentGrade("Bob", -1);
        sm.changeStudentGrade("David", -1);
        auto absent_students = sm.getAbsentStudents();
        CHECK(absent_students.find("Bob") != absent_students.end());
        CHECK(absent_students.find("David") != absent_students.end());
        CHECK(absent_students.size() == 2);
    }

}