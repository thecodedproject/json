#include <gmock/gmock.h>

#include <json/tree.hpp>

using namespace CodedProject;
using namespace ::testing;

class TestTreeDocumentUsage : public ::testing::Test
{
};

TEST_F(TestTreeDocumentUsage, defaultConstructAndAssignValueToFieldMakesIsDocumentReturnTrue)
{
    auto t = Json::Tree();
    t["some_field_name"] = "some_value";
    EXPECT_TRUE(t.isDocument());
}

TEST_F(TestTreeDocumentUsage, assignStringToFieldOperatorAndGetSameFieldValueAsStringGivesSameValue)
{
    auto s = std::string("hello");
    auto field_name = "some_string_field";
    auto t = Json::Tree();

    t[field_name] = s;

    EXPECT_EQ(s, t[field_name].get<std::string>());
}

TEST_F(TestTreeDocumentUsage, assignIntToFieldOperatorAndGetSameFieldValueAsIntGivesSameValue)
{
    auto i = 10;
    auto field_name = "some_integer_field";
    auto t = Json::Tree();

    t[field_name] = i;

    EXPECT_EQ(i, t[field_name].get<int>());
}

TEST_F(TestTreeDocumentUsage, assignFloatToFieldOperatorAndGetSameFieldValueAsFloatGivesSameValue)
{
    auto f = 10.5f;
    auto field_name = "some_float_field";
    auto t = Json::Tree();

    t[field_name] = f;

    EXPECT_FLOAT_EQ(f, t[field_name].get<float>());
}

TEST_F(TestTreeDocumentUsage, assignBoolToFieldOperatorAndGetSameFieldValueAsBoolGivesSameValue)
{
    auto b = true;
    auto field_name = "some_bool_field";
    auto t = Json::Tree();

    t[field_name] = b;

    EXPECT_EQ(b, t[field_name].get<bool>());
}

TEST_F(TestTreeDocumentUsage, assignDifferentValuesToDifferentFieldsAndAccessThemGivesCorrectValues)
{
    auto t = Json::Tree();

    t["some_int_field"] = 14;
    t["some_string_field"] = std::string("hello world");
    t["some_bool_field"] = true;
    t["some_float_field"] = 13.5f;

    EXPECT_EQ(14, t["some_int_field"].get<int>());
    EXPECT_EQ("hello world", t["some_string_field"].get<std::string>());
    EXPECT_FLOAT_EQ(13.5f, t["some_float_field"].get<float>());
    EXPECT_EQ(true, t["some_bool_field"].get<bool>());
}

TEST_F(TestTreeDocumentUsage, getCountOfFieldNameWhichHasBeenAddedReturnsOne)
{
    auto t = Json::Tree();
    t["some_field"] = 12.0f;
    EXPECT_EQ(1, t.count("some_field"));
}

TEST_F(TestTreeDocumentUsage, getCountOfFieldNameWhichDoesNotExistFromDocumentReturnsZero)
{
    auto t = Json::Tree();
    t["some_field"] = 12.0f;
    EXPECT_EQ(0, t.count("some_other_field"));
}

TEST_F(TestTreeDocumentUsage, getCountFromDefaultConstructedTreeReturnsZero)
{
    auto t = Json::Tree();
    EXPECT_EQ(0, t.count("some_field"));
}

TEST_F(TestTreeDocumentUsage, getCountFromValueTreeThrowsErrorWithHelpfulMessage)
{
    auto t = Json::Tree(12);
    ASSERT_TRUE(t.isValue());
    EXPECT_THROW({
        try
        {
            t.count("some_field");
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("document"));
            EXPECT_THAT(err_msg, HasSubstr("count()"));
            EXPECT_THAT(err_msg, HasSubstr("value"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}

TEST_F(TestTreeDocumentUsage, getCountFromArrayTreeThrowsErrorWithHelpfulMessage)
{
    auto t = Json::Tree();
    t.pushBack(12);
    ASSERT_TRUE(t.isArray());
    EXPECT_THROW({
        try
        {
            t.count("some_field");
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("document"));
            EXPECT_THAT(err_msg, HasSubstr("count()"));
            EXPECT_THAT(err_msg, HasSubstr("array"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}

TEST_F(TestTreeDocumentUsage, assignSubtreeDocumentWithValuesToFieldAllowsAccessOfAllSubtreeValues)
{
    auto subtree = Json::Tree();
    subtree["some_int_field"] = 14;
    subtree["some_string_field"] = std::string("hello world");
    subtree["some_bool_field"] = true;
    subtree["some_float_field"] = 13.5f;

    auto t = Json::Tree();
    t["some_subtree_field"] = subtree;
    t["some_string_field"] = std::string("hello world");
    t["some_bool_field"] = true;
    t["some_float_field"] = 13.5f;

    EXPECT_EQ(
        14,
        t["some_subtree_field"]["some_int_field"].get<int>());
    EXPECT_EQ(
        "hello world",
        t["some_subtree_field"]["some_string_field"].get<std::string>());
    EXPECT_FLOAT_EQ(
        13.5f,
        t["some_subtree_field"]["some_float_field"].get<float>());
    EXPECT_EQ(
        true,
        t["some_subtree_field"]["some_bool_field"].get<bool>());
}

TEST_F(TestTreeDocumentUsage, defaultConstructAndAssignValueToFieldMakesIsArrayAndIsValueReturnFalse)
{
    auto t = Json::Tree();
    t["some_field_name"] = 13.5f;
    EXPECT_FALSE(t.isArray());
    EXPECT_FALSE(t.isValue());
}

TEST_F(TestTreeDocumentUsage, assignMultipleValuesToDifferentFieldsAndGetSize)
{
    auto t = Json::Tree();
    t["some_int_field"] = 14;
    t["some_string_field"] = std::string("hello world");
    t["some_bool_field"] = true;
    t["some_float_field"] = 13.5f;
    t["some_other_value"] = Json::Tree();
    EXPECT_EQ(5, t.size());
}

TEST_F(TestTreeDocumentUsage, constructFromValueAndTryToGetFieldValueThrowsErrorWithHelpfulMessage)
{
    auto t = Json::Tree(23.1f);
    EXPECT_THROW({
        try
        {
            t["some_field"] = 10;
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("document"));
            EXPECT_THAT(err_msg, HasSubstr("operator[] (std::string)"));
            EXPECT_THAT(err_msg, HasSubstr("value"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}

TEST_F(TestTreeDocumentUsage, constructArrayAndTryToGetFieldValueThrowsErrorWithHelpfulMessage)
{
    auto t = Json::Tree();
    t.pushBack(10);
    ASSERT_TRUE(t.isArray());
    EXPECT_THROW({
        try
        {
            t["some_field"] = 10;
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("document"));
            EXPECT_THAT(err_msg, HasSubstr("operator[] (std::string)"));
            EXPECT_THAT(err_msg, HasSubstr("array"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}

TEST_F(TestTreeDocumentUsage, createDocumentAndAccessValueWithAtAccessor)
{
    auto t = Json::Tree();
    t["some_field"] = std::string("some_value");
    EXPECT_EQ("some_value", t.at("some_field").get<std::string>());
}

TEST_F(TestTreeDocumentUsage, createDocumentAndAccessManyValuesWithAtAccessor)
{
    auto t = Json::Tree();
    t["a"] = std::string("some_value");
    t["b"] = 23;
    t["c"] = false;
    t["d"] = 34.5f;

    EXPECT_EQ("some_value", t.at("a").get<std::string>());
    EXPECT_EQ(23, t.at("b").get<int>());
    EXPECT_FALSE(t.at("c").get<bool>());
    EXPECT_FLOAT_EQ(34.5f, t.at("d").get<float>());
}

TEST_F(TestTreeDocumentUsage, createConstDocumentAndAccessValueWithAtAccessor)
{
    auto t = Json::Tree();
    t["some_field"] = std::string("some_value");
    auto const& t_const = t;
    EXPECT_EQ("some_value", t_const.at("some_field").get<std::string>());
}

TEST_F(TestTreeDocumentUsage, accessFieldWhichDoesNotExistWithAtTHrowsOutOfRange)
{
    auto t = Json::Tree();
    t["a"] = true;
    t["b"] = 123;
    EXPECT_THROW({
        try
        {
            auto a = t.at("hello");
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("at(std::string)"));
            EXPECT_THAT(err_msg, HasSubstr("'hello'"));
            throw;
        }
    }, std::out_of_range);
}

TEST_F(TestTreeDocumentUsage, accessFieldOnConstTreeWhichDoesNotExistWithAtTHrowsOutOfRange)
{
    auto t = Json::Tree();
    t["a"] = true;
    t["b"] = 123;
    auto const& t_const = t;
    EXPECT_THROW({
        try
        {
            auto a = t_const.at("hello");
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("at(std::string)"));
            EXPECT_THAT(err_msg, HasSubstr("'hello'"));
            throw;
        }
    }, std::out_of_range);
}
