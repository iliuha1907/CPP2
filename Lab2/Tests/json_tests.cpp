#include "pch.h"
#include "gtest/gtest.h"
#include "JSON.h"

TEST(isNotEmpty, Equals) {
    JSON json = { 1, 3 };
    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(isEmpty, Equals) {
    JSON json;
    bool expected = true;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(isJSON, Equals) {
    Array array = { 1, 2, 3 };
    JSON json = { {"32", 2}, { "2" , array} };

    bool expected = false;
    bool actual = json.isArray();
    EXPECT_EQ(expected, actual);
}

TEST(copyJSON, Equals) {
    JSON json1 = JSON();
    JSON json2 = json1;

    EXPECT_EQ(json1, json2);
}

TEST(forEachNonEmpty, Equals) {
    JSON json = { 1, 2, std::string("32") };
    std::stringstream ss;

    for (const auto& value : json) {
        ss << value << std::endl;
    }

    auto expected = false;
    auto actual = ss.str().empty();
    EXPECT_EQ(expected, actual);
}

TEST(forEachEmpty, Equals) {
    JSON json = {};
    std::stringstream ss;

    for (const auto& value : json) {
        ss << value << std::endl;
    }

    auto expected = true;
    auto actual = ss.str().empty();
    EXPECT_EQ(expected, actual);
}

TEST(findIteratorSuccess, Equals) {
    JSON json = { 1, 2, std::string("21") };

    auto expected = 2;
    auto actual = *std::find(json.begin(), json.end(), expected);
    EXPECT_EQ(expected, actual);
}