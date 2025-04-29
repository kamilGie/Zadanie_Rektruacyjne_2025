#include <gtest/gtest.h>

#include "src/Application.h"

TEST(ApplicationEmptyTest, ReturnsEmptyWhenNoAsksAdded) {
    triangle t1{{{{200, 150}, {100, 350}, {300, 350}}}};
    triangle t2{{{{500, 250}, {400, 450}, {600, 450}}}};
    ASSERT_FALSE(isColliding(t1, t2));
}

TEST(ApplicationCollisionTest, ReturnsTrueWhenTrianglesCollide) {
    triangle t1{{{{200, 150}, {100, 350}, {300, 350}}}};
    triangle t2{{{{250, 250}, {150, 450}, {350, 450}}}};
    ASSERT_TRUE(isColliding(t1, t2));
}

TEST(ApplicationContainmentTest, ReturnsTrueWhenOneTriangleIsContainedInAnother) {
    triangle t1{{{{200, 150}, {100, 350}, {300, 350}}}};
    triangle t2{{{{250, 200}, {200, 350}, {300, 350}}}};
    ASSERT_TRUE(isColliding(t1, t2));
}

TEST(ApplicationTouchingTest, ReturnsTrueWhenTrianglesTouchAtOnePoint) {
    triangle t1{{{{200, 150}, {100, 350}, {300, 350}}}};
    triangle t2{{{{300, 350}, {200, 450}, {400, 450}}}};
    ASSERT_TRUE(isColliding(t1, t2));
}

TEST(ApplicationOverlapTest, ReturnsTrueWhenTrianglesHaveSameCoordinates) {
    triangle t1{{{{200, 150}, {100, 350}, {300, 350}}}};
    triangle t2{{{{200, 150}, {100, 350}, {300, 350}}}};
    ASSERT_TRUE(isColliding(t1, t2));
}

TEST(ApplicationVerticalTest, ReturnsTrueWhenTrianglesAreVerticallyAligned) {
    triangle t1{{{{200, 150}, {100, 350}, {300, 350}}}};
    triangle t2{{{{300, 250}, {200, 450}, {400, 450}}}};
    ASSERT_TRUE(isColliding(t1, t2));
}

TEST(ApplicationPartialOverlapTest, ReturnsTrueWhenTrianglePartiallyOverlapsAnother) {
    triangle t1{{{{200, 150}, {100, 350}, {300, 350}}}};
    triangle t2{{{{230, 200}, {150, 350}, {250, 350}}}};
    ASSERT_TRUE(isColliding(t1, t2));
}

TEST(ApplicationAdjacentTest, ReturnsFalseWhenTrianglesAreAdjacent) {
    triangle t1{{{{200, 150}, {100, 350}, {300, 350}}}};
    triangle t2{{{{400, 150}, {301, 351}, {500, 350}}}};
    ASSERT_FALSE(isColliding(t1, t2));
}
