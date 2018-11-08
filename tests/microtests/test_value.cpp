#include <gmock/gmock.h>

#include <json/value.hpp>

using namespace CodedProject;
using namespace ::testing;

class TestValue : public Test
{
};

TEST_F(TestValue, constructFromStringAndGetType)
{
    auto v = Json::Value(std::string("some_string"));
    EXPECT_EQ(Json::Value::Type::String, v.type());
}

TEST_F(TestValue, constructFromIntAndGetType)
{
    auto v = Json::Value(10);
    EXPECT_EQ(Json::Value::Type::Integer, v.type());
}

TEST_F(TestValue, constructFromFloatAndGetType)
{
    auto v = Json::Value(2.0f);
    EXPECT_EQ(Json::Value::Type::Float, v.type());
}

TEST_F(TestValue, constructFromBoolAndGetType)
{
    auto v = Json::Value(true);
    EXPECT_EQ(Json::Value::Type::Bool, v.type());
}

TEST_F(TestValue, constructFromStringAndGetValueAsString)
{
    auto value = std::string("some_value");
    auto v = Json::Value(value);
    EXPECT_EQ(value, v.get<std::string>());
}

TEST_F(TestValue, constructFromCharArrayAndGetValueAsString)
{
    auto value = "some_value_2";
    auto v = Json::Value(value);
    EXPECT_EQ(value, v.get<std::string>());
}

TEST_F(TestValue, constructFromIntAndGetValueAsStringThrowsWithHelpfulMessage)
{
    auto v = Json::Value(10);
    EXPECT_THROW({
        try
        {
            v.get<std::string>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("10"));
            EXPECT_THAT(err_msg, HasSubstr("Integer"));
            EXPECT_THAT(err_msg, HasSubstr("std::string"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromTrueBoolAndGetValueAsStringThrowsWithHelpfulMessage)
{
    auto v = Json::Value(true);
    EXPECT_THROW({
        try
        {
            v.get<std::string>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("true"));
            EXPECT_THAT(err_msg, HasSubstr("Bool"));
            EXPECT_THAT(err_msg, HasSubstr("std::string"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromFalseBoolAndGetValueAsStringThrowsWithHelpfulMessage)
{
    auto v = Json::Value(false);
    EXPECT_THROW({
        try
        {
            v.get<std::string>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("false"));
            EXPECT_THAT(err_msg, HasSubstr("Bool"));
            EXPECT_THAT(err_msg, HasSubstr("std::string"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromFloatAndGetValueAsStringThrowsWithHelpfulMessage)
{
    auto v = Json::Value(2.5f);
    EXPECT_THROW({
        try
        {
            v.get<std::string>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("2.50"));
            EXPECT_THAT(err_msg, HasSubstr("Float"));
            EXPECT_THAT(err_msg, HasSubstr("std::string"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromIntAndGetValueAsInteger)
{
    auto value = 23;
    auto v = Json::Value(value);
    EXPECT_EQ(value, v.get<int>());
}

TEST_F(TestValue, constructFromStringAndGetValueAsIntegerThrowsWithHelpfulMessage)
{
    auto v = Json::Value(std::string("hello"));
    EXPECT_THROW({
        try
        {
            v.get<int>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("hello"));
            EXPECT_THAT(err_msg, HasSubstr("String"));
            EXPECT_THAT(err_msg, HasSubstr("int"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromFloatAndGetValueAsIntegerThrowsWithHelpfulMessage)
{
    auto v = Json::Value(4.5f);
    EXPECT_THROW({
        try
        {
            v.get<int>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("4.50"));
            EXPECT_THAT(err_msg, HasSubstr("Float"));
            EXPECT_THAT(err_msg, HasSubstr("int"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromBoolAndGetValueAsIntegerThrowsWithHelpfulMessage)
{
    auto v = Json::Value(true);
    EXPECT_THROW({
        try
        {
            v.get<int>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("true"));
            EXPECT_THAT(err_msg, HasSubstr("Bool"));
            EXPECT_THAT(err_msg, HasSubstr("int"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromFloatAndGetValueAsFloat)
{
    auto value = 23.5f;
    auto v = Json::Value(value);
    EXPECT_EQ(value, v.get<float>());
}

TEST_F(TestValue, constructFromStringAndGetValueAsFloatThrowsWithHelpfulMessage)
{
    auto v = Json::Value(std::string("eggs"));
    EXPECT_THROW({
        try
        {
            v.get<float>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("eggs"));
            EXPECT_THAT(err_msg, HasSubstr("String"));
            EXPECT_THAT(err_msg, HasSubstr("float"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromIntAndGetValueAsFloatThrowsWithHelpfulMessage)
{
    auto v = Json::Value(13);
    EXPECT_THROW({
        try
        {
            v.get<float>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("13"));
            EXPECT_THAT(err_msg, HasSubstr("Integer"));
            EXPECT_THAT(err_msg, HasSubstr("float"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromBoolAndGetValueAsFloatThrowsWithHelpfulMessage)
{
    auto v = Json::Value(false);
    EXPECT_THROW({
        try
        {
            v.get<float>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("false"));
            EXPECT_THAT(err_msg, HasSubstr("Bool"));
            EXPECT_THAT(err_msg, HasSubstr("float"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromBoolAndGetValueAsBool)
{
    auto value = true;
    auto v = Json::Value(value);
    EXPECT_EQ(value, v.get<bool>());
}

TEST_F(TestValue, constructFromStringAndGetValueAsBoolThrowsWithHelpfulMessage)
{
    auto v = Json::Value(std::string("coke"));
    EXPECT_THROW({
        try
        {
            v.get<bool>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("coke"));
            EXPECT_THAT(err_msg, HasSubstr("String"));
            EXPECT_THAT(err_msg, HasSubstr("bool"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromFloatAndGetValueAsBoolThrowsWithHelpfulMessage)
{
    auto v = Json::Value(34.5f);
    EXPECT_THROW({
        try
        {
            v.get<bool>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("34.50"));
            EXPECT_THAT(err_msg, HasSubstr("Float"));
            EXPECT_THAT(err_msg, HasSubstr("bool"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromIntAndGetValueAsBoolThrowsWithHelpfulMessage)
{
    auto v = Json::Value(32);
    EXPECT_THROW({
        try
        {
            v.get<bool>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("32"));
            EXPECT_THAT(err_msg, HasSubstr("Integer"));
            EXPECT_THAT(err_msg, HasSubstr("bool"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromSameStrings)
{
    auto v1 = Json::Value(std::string("some_string"));
    auto v2 = Json::Value(std::string("some_string"));
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromDifferentStrings)
{
    auto v1 = Json::Value(std::string("some_string"));
    auto v2 = Json::Value(std::string("some_other_string"));
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromSameFloats)
{
    auto v1 = Json::Value(12.5f);
    auto v2 = Json::Value(12.5f);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromDifferentFloats)
{
    auto v1 = Json::Value(12.5f);
    auto v2 = Json::Value(10.0f);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromSameIntegers)
{
    auto v1 = Json::Value(12);
    auto v2 = Json::Value(12);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromDifferentIntegers)
{
    auto v1 = Json::Value(12);
    auto v2 = Json::Value(11);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromSameBools)
{
    auto v1 = Json::Value(true);
    auto v2 = Json::Value(true);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromDifferentBools)
{
    auto v1 = Json::Value(true);
    auto v2 = Json::Value(false);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromDifferentTypes)
{
    auto v1 = Json::Value(true);
    auto v2 = Json::Value(12);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}
