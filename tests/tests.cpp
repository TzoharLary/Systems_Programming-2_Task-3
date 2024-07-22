#include <gtest/gtest.h>
#include "player.hpp"
#include "board.hpp"
#include "catan.hpp"

// בדיקות יחידה לדוגמה

TEST(PlayerTest, Initialization) {
    Player p("TestPlayer");
    ASSERT_EQ(p.getName(), "TestPlayer");
}

TEST(BoardTest, Setup) {
    Board b;
    b.setup();
    // Add assertions to verify the setup
}

TEST(CatanTest, StartingPlayer) {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3);
    catan.ChooseStartingPlayer();
    // Add assertions to verify the chosen starting player
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
