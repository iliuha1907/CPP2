#include "pch.h"
#include <JSONException.h>
#include "gtest/gtest.h"
#include "JSON.h"

TEST(editInt, NotEquals) {
    std::string key = "1";
    JSON json1;
    json1.add(key, 2);
    JSON json2 = json1;
    json2.edit(key, 102);

    EXPECT_NE(json1, json2);
}

TEST(editJSON, NotEquals) {
    std::string key = "1";
    JSON json1;
    json1.add(key, JSON({ 1, 2 }));
    JSON json2 = json1;
    json2.edit(key, JSON({ 2 }));

    EXPECT_NE(json1, json2);
}

TEST(editArray, NotEquals) {
    JSON json1 = JSON({ 1, 2 });
    JSON json2 = json1;
    json2.edit(0, 1.53);

    EXPECT_NE(json1, json2);
}

TEST(editKeyValueToArray, Equals) {
    std::string expected = "Failed to edit KeyValue in Array";
    JSON json = JSON({ 1, 2 });
    try {
        json.edit("123", "1");
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(editArrayValueToArray, Equals) {
    std::string expected = "Failed to edit value in KeyValue";
    JSON json = JSON();
    try {
        json.edit(1, "1");
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(editArrayWithInvalidInxed, Equals) {
    std::string expected = "Invalid index";
    JSON json = JSON({ 1, 2 });
    try {
        json.edit(4, "1");
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(editNonExistingValue, Equals) {
    std::string expected = "No value for key";
    JSON json = JSON();
    try {
        json.edit("1", "1");
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(removeWithKey, Equals) {
    std::string key = "1";
    JSON json = { {key, 2} };
    json.remove(key);

    bool expected = true;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(removeFromEmptyWithIndex, Equals) {
    std::string expected = "Invalid index";
    JSON json = JSON({ 1 });
    try {
        json.remove(1);
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(removeFromEmptyWithKey, Equals) {
    std::string expected = "No value for key";
    JSON json;
    try {
        json.remove("1");
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(removeInArrayWithKey, Equals) {
    std::string expected = "Failed to remove KeyValue in Array";
    JSON json = JSON({ 1, 2 });
    try {
        json.remove("1");
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(removeInKeyValueWithIndex, Equals) {
    std::string expected = "Failed to remove value in KeyValue";
    JSON json;
    try {
        json.remove(1);
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(removeWithIndex, Equals) {
    JSON json = { 2 };
    json.remove(0);

    bool expected = true;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}