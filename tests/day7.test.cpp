#include <gtest/gtest.h>

#include "day07/day07.hpp"

TEST(CardSortTest, Default)
{
    auto oneOfAKind = Hand({1, 2, 3, 4, 5});
    auto twoOfAKind = Hand({2, 2, 3, 4, 5});
    auto twoPair = Hand({2, 2, 3, 3, 5});
    auto threeOfAKind = Hand({2, 2, 2, 3, 5});
    auto fullHouse = Hand({2, 2, 2, 3, 3});
    auto fourOfAKind = Hand({2, 2, 2, 2, 3});
    auto fiveOfAKind = Hand({2, 2, 2, 2, 2});

    EXPECT_LT(oneOfAKind, twoOfAKind);
    EXPECT_LT(twoOfAKind, twoPair);
    EXPECT_LT(twoPair, threeOfAKind);
    EXPECT_LT(threeOfAKind, fullHouse);
    EXPECT_LT(fullHouse, fourOfAKind);
    EXPECT_LT(fourOfAKind, fiveOfAKind);
}