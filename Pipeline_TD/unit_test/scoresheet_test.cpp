
#include "doctest.h"
#include "../include/scoresheet.hpp"
#include <sstream>

DOCTEST_TEST_CASE("scoresheet")
{

    ScoreSheet<int> scoreSheet;

    SUBCASE("Test addScore")
    {
        std::istringstream iss("Amy English 95 y Computer 85 n\n");
        std::cin.rdbuf(iss.rdbuf());
        scoreSheet.addScore();
        std::ostringstream oss;
        scoreSheet.printScoreSheet(oss);
        CHECK_EQ(oss.str(), "Computer:\n1 Amy 85\nEnglish:\n1 Amy 95\n");
    }

    SUBCASE("Test loadScoreFromFile")
    {
        std::ofstream ofs("score.txt");
        ofs << "Name Chinese Math\nAlice 80 90\nBob 90 90\n";
        ofs.close();
        std::istringstream iss("score.txt");
        std::cin.rdbuf(iss.rdbuf());
        scoreSheet.loadScoreFromFile();
        std::ostringstream oss;
        scoreSheet.printScoreSheet(oss);
        CHECK_EQ(oss.str(), "Math:\n1 Alice 90\n2 Bob 90\nChinese:\n1 Alice 80\n2 Bob 90\n");
    }

    SUBCASE("Test changeScore")
    {
        std::istringstream iss("Amy English 95 y Computer 85 n\n");
        std::cin.rdbuf(iss.rdbuf());
        scoreSheet.addScore();

        iss = std::istringstream("Amy English 100 n\n");
        std::cin.rdbuf(iss.rdbuf());
        scoreSheet.changeScore();
        std::ostringstream oss;
        scoreSheet.printScoreSheet(oss);
        CHECK_EQ(oss.str(), "Computer:\n1 Amy 85\nEnglish:\n1 Amy 100\n");
    }
}