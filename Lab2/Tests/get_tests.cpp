#include "pch.h"
#include "gtest/gtest.h"
#include "JSON.h"

TEST(getInt, Equals) {
    JSON json;
    int value = 2;
    std::string key = "1";
    json.add(key, value);

    int expected = value;
    auto actual = json.getVal<int>(key);

    EXPECT_EQ(expected, actual);
}

TEST(getJSON, Equals) {
    JSON json;
    JSON value = JSON({ 1, 3 });;
    std::string key = "1";
    json.add(key, value);

    JSON expected = value;
    auto actual = json.getVal<JSON>(key);

    EXPECT_EQ(expected, actual);
}

TEST(getArray, Equals) {
    Array array = { 1, 3 };
    JSON json = JSON(array);

    Array expected = array;
    auto actual = json.asArray();
    EXPECT_EQ(expected, actual);
}

TEST(getNonExists, Equals) {
    JSON json;
    std::string key = "1";
    auto expected = std::nullopt;
    auto actual = json.getVal<int>(key);
    EXPECT_EQ(expected, actual);
}