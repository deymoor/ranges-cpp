#include "libs/ranges.h"
#include <gtest/gtest.h>
#include <vector>
#include <map>

using namespace ranges;

TEST(RangesTestSuite, TrasformTest1) {
    std::vector<int> test = {1 ,2, 3, 4, 5, 6};
    std::vector<int> ans = {1, 4, 9, 16, 25, 36};
    int j = 0;
    for (auto i : test | transform([](int i) {return i * i;})) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, TrasformTest2) {
    std::vector<int> test = {1 ,2, 3, 4};
    std::vector<int> ans = {2, 3, 4, 5};
    int j = 0;
    for (auto i : transform_view(test, [](int i) {return i + 1;})) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, FilterTest1) {
    std::vector<int> test = {1 ,2, 3, 4, 5, 6};
    std::vector<int> ans = {2, 4, 6};
    int j = 0;
    for (auto i : test | filter([](int i) {return i % 2 == 0;})) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, FilterTest2) {
    std::vector<int> test = {1 ,2, 3, 4};
    std::vector<int> ans = {3};
    int j = 0;
    for (auto i : filter_view(test, [](int i) {return i == 3;})) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, TakeTest1) {
    std::vector<int> test = {1 ,2, 3, 4, 5, 6};
    std::vector<int> ans = {1, 2, 3, 4};
    int j = 0;
    for (auto i : test | take(4)) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, TakeTest2) {
    std::vector<int> test = {1 ,2, 3, 4};
    std::vector<int> ans = {1, 2};
    int j = 0;
    for (auto i : take_view(test, 2)) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, TakeTest3) {
    std::vector<int> test = {1 ,2, 3, 4};
    std::vector<int> ans;
    for (auto i : take_view(test, 0)) {
        ans.push_back(i);
    }
    ASSERT_EQ(true, ans.empty());
}

TEST(RangesTestSuite, TakeTest4) {
    std::vector<int> test = {1 ,2, 3, 4};
    std::vector<int> ans = {1, 2, 3, 4};
    int j = 0;
    for (auto i : take_view(test, 6)) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, DropTest1) {
    std::vector<int> test = {1 ,2, 3, 4, 5, 6};
    std::vector<int> ans = {3, 4, 5, 6};
    int j = 0;
    for (auto i : test | drop(2)) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, DropTest2) {
    std::vector<int> test = {1 ,2, 3, 4};
    std::vector<int> ans = {4};
    int j = 0;
    for (auto i : drop_view(test, 3)) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, DropTest3) {
    std::vector<int> test = {1 ,2, 3, 4};
    std::vector<int> ans;
    for (auto i : drop_view(test, 5)) {
        ans.push_back(i);
    }
    ASSERT_EQ(true, ans.empty());
}

TEST(RangesTestSuite, DropTest4) {
    std::vector<int> test = {1 ,2, 3, 4};
    std::vector<int> ans = {1, 2, 3, 4};
    int j = 0;
    for (auto i : take_view(test, 0)) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, ReverseTest1) {
    std::vector<int> test = {1 ,2, 3, 4, 5, 6};
    std::vector<int> ans = {6, 5, 4, 3, 2, 1};
    int j = 0;
    for (auto i : test | reverse()) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, ReverseTest2) {
    std::vector<int> test = {1 ,2, 3, 4};
    std::vector<int> ans = {4, 3, 2, 1};
    int j = 0;
    for (auto i : reverse_view(test)) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, KeysTest1) {
    std::map<float, std::string> test = {{2.5, "abc"}, {4.0, "qwe"}, {10.0, "test"}};
    std::vector<float> ans = {2.5, 4.0, 10.0};
    int j = 0;
    for (auto i : test | keys()) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, KeysTest2) {
    std::map<float, std::string> test = {{2.5, "abc"}, {4.0, "qwe"}, {10.0, "test"}};
    std::vector<float> ans = {2.5, 4.0, 10.0};
    int j = 0;
    for (auto i : keys_view(test)) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, ValuesTest1) {
    std::map<float, std::string> test = {{2.5, "abc"}, {4.0, "qwe"}, {10.0, "test"}};
    std::vector<std::string> ans = {"abc", "qwe", "test"};
    int j = 0;
    for (auto i : test | values()) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, ValuesTest2) {
    std::map<float, std::string> test = {{2.5, "abc"}, {4.0, "qwe"}, {10.0, "test"}};
    std::vector<std::string> ans = {"abc", "qwe", "test"};
    int j = 0;
    for (auto i : values_view(test)) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, CombinatedTest1) {
    std::vector<int> test = {1 ,2, 3, 4};
    std::vector<int> ans = {16, 9, 4, 1};
    int j = 0;
    for (auto i : transform_view(test, [](int i){return i * i;}) | reverse()) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, CombinatedTest2) {
    std::vector<int> test = {1 ,2, 3, 4};
    std::vector<int> ans = {16, 9};
    int j = 0;
    for (auto i : transform_view(test, [](int i){return i * i;}) |
            reverse() | take(2)) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, CombinatedTest3) {
    std::vector<int> test = {1 ,2, 3, 4};
    std::vector<int> ans = {9, 4, 1};
    int j = 0;
    for (auto i : transform_view(test, [](int i){return i * i;}) |
            reverse() | drop(1)) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, CombinatedTest4) {
    std::vector<int> test = {1 ,2, 3, 4};
    std::vector<int> ans = {16, 4};
    auto pow = [](int i){return i * i;};
    auto even = [](int i){return i % 2 == 0;};
    int j = 0;
    for (auto i : transform_view(test, pow) |
            filter(even) | reverse()) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, CombinatedTest5) {
    std::vector<int> test = {1 ,2, 3, 4};
    std::vector<int> ans = {16};
    auto pow = [](int i){return i * i;};
    auto even = [](int i){return i % 2 == 0;};
    int j = 0;
    for (auto i : transform_view(test, pow) |
            filter(even) | reverse() | take(1)) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, CombinatedTest6) {
    std::vector<int> test = {1 ,2, 3, 4};
    std::vector<int> ans = {9, 16};
    auto pow = [](int i){return i * i;};
    int j = 0;
    for (auto i : drop_view(test, 2) | transform(pow)) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, CombinatedTest7) {
    std::vector<int> test = {1 ,2, 3, 4};
    std::vector<int> ans = {1, 2, 3, 4};
    int j = 0;
    for (auto i : reverse_view(test) | reverse()) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, CombinatedTest8) {
    std::vector<int> test = {1 ,2, 3, 4};
    std::vector<int> ans = {1, 16, 81, 256};
    auto pow = [](int i){return i * i;};
    int j = 0;
    for (auto i : transform_view(test, pow) | transform(pow)) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, CombinatedTest9) {
    std::map<int, std::string> test = {{2, "abc"}, {5, "qwe"}, {10, "test"}};
    std::vector<int> ans = {2, 10};
    auto even = [](int i){return i % 2 == 0;};
    int j = 0;
    for (auto i : keys_view(test) | filter(even)) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}

TEST(RangesTestSuite, CombinatedTest10) {
    std::map<std::string, int> test = {{"abc", 2}, {"qwe", 5}, {"test", 10}};
    std::vector<int> ans = {25};
    auto pow = [](int i){return i * i;};
    int j = 0;
    for (auto i : values_view(test) | take(1) |
            drop(1) | transform(pow)) {
        ASSERT_EQ(i, ans[j]);
        ++j;
    }
}