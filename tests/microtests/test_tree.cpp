#include <gmock/gmock.h>

#include <json/tree.hpp>

using namespace CodedProject;
using namespace ::testing;

class TestTree : public ::testing::Test
{
};

TEST_F(TestTree, defaultConstructAndCallIsValueReturnsFalse)
{
    auto t = Json::Tree();
    EXPECT_FALSE(t.isValue());
}

TEST_F(TestTree, defaultConstructAndCallIsArrayReturnsFalse)
{
    auto t = Json::Tree();
    EXPECT_FALSE(t.isArray());
}

TEST_F(TestTree, defaultConstructAndCallIsDocumentReturnsFalse)
{
    auto t = Json::Tree();
    EXPECT_FALSE(t.isDocument());
}

TEST_F(TestTree, consturctFromValueAndCallIsValueReturnsTrue)
{
    auto t = Json::Tree(Json::Value(23.0f));
    EXPECT_TRUE(t.isValue());
}

TEST_F(TestTree, consturctFromStringAndGetValueAsString)
{
    auto t = Json::Tree(std::string("something"));
    EXPECT_EQ("something", t.get<std::string>());
}

TEST_F(TestTree, consturctFromFloatAndGetValueAsFloat)
{
    auto t = Json::Tree(10.5f);
    EXPECT_FLOAT_EQ(10.5f, t.get<float>());
}

TEST_F(TestTree, constructFromIntandGetAsInt)
{
    auto t = Json::Tree(12);
    EXPECT_EQ(12, t.get<int>());
}

TEST_F(TestTree, constructFromBoolAndGetBool)
{
    auto t = Json::Tree(true);
    EXPECT_TRUE(t.get<bool>());
}

TEST_F(TestTree, consturctFromValueAndCallIsArrayReturnsFalse)
{
    auto t = Json::Tree(Json::Value(23.0f));
    EXPECT_FALSE(t.isArray());
}

TEST_F(TestTree, consturctFromValueAndCallIsDocumentReturnsFalse)
{
    auto t = Json::Tree(Json::Value(23.0f));
    EXPECT_FALSE(t.isDocument());
}

TEST_F(TestTree, consturctFromValueAndGetValue)
{
    auto v = Json::Value(23.0f);
    auto t = Json::Tree(v);
    EXPECT_EQ(v, t.getValue());
}

TEST_F(TestTree, assignStringToFieldOperatorAndGetSameFieldValueAsStringGivesSameValue)
{
    auto s = std::string("hello");
    auto field_name = "some_string_field";
    auto t = Json::Tree();

    t[field_name] = s;

    EXPECT_EQ(s, t[field_name].get<std::string>());
}

TEST_F(TestTree, assignIntToFieldOperatorAndGetSameFieldValueAsIntGivesSameValue)
{
    auto i = 10;
    auto field_name = "some_integer_field";
    auto t = Json::Tree();

    t[field_name] = i;

    EXPECT_EQ(i, t[field_name].get<int>());
}

TEST_F(TestTree, assignFloatToFieldOperatorAndGetSameFieldValueAsFloatGivesSameValue)
{
    auto f = 10.5f;
    auto field_name = "some_float_field";
    auto t = Json::Tree();

    t[field_name] = f;

    EXPECT_FLOAT_EQ(f, t[field_name].get<float>());
}

TEST_F(TestTree, assignBoolToFieldOperatorAndGetSameFieldValueAsBoolGivesSameValue)
{
    auto b = true;
    auto field_name = "some_bool_field";
    auto t = Json::Tree();

    t[field_name] = b;

    EXPECT_EQ(b, t[field_name].get<bool>());
}

TEST_F(TestTree, assignDifferentValuesToDifferentFieldsAndAccessThemGivesCorrectValues)
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

TEST_F(TestTree, getCountOfFieldNameWhichHasBeenAddedReturnsOne)
{
    auto t = Json::Tree();
    t["some_field"] = 12.0f;
    EXPECT_EQ(1, t.count("some_field"));
}

TEST_F(TestTree, getCountOfFieldNameWhichDoesNotExistFromDocumentReturnsZero)
{
    auto t = Json::Tree();
    t["some_field"] = 12.0f;
    EXPECT_EQ(0, t.count("some_other_field"));
}

TEST_F(TestTree, getCountFromDefaultConstructedTreeReturnsZero)
{
    auto t = Json::Tree();
    EXPECT_EQ(0, t.count("some_field"));
}

TEST_F(TestTree, getCountFromValueTreeThrowsErrorWithHelpfulMessage)
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

TEST_F(TestTree, getCountFromArrayTreeThrowsErrorWithHelpfulMessage)
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

TEST_F(TestTree, assignSubtreeDocumentWithValuesToFieldAllowsAccessOfAllSubtreeValues)
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

TEST_F(TestTree, defaultConstructAndAssignValueToFieldMakesIsArrayAndIsValueReturnFalse)
{
    auto t = Json::Tree();
    t["some_field_name"] = 13.5f;
    EXPECT_FALSE(t.isArray());
    EXPECT_FALSE(t.isValue());
}

TEST_F(TestTree, defaultConstructAndAssignValueToFieldMakesIsDocumentReturnTrue)
{
    auto t = Json::Tree();
    t["some_field_name"] = "some_value";
    EXPECT_TRUE(t.isDocument());
}

TEST_F(TestTree, pushBackStringIntoArrayAndGetValueWithArrayIndexReturnsSameValue)
{
    auto t = Json::Tree();
    t.pushBack(std::string("some_value"));
    EXPECT_EQ("some_value", t[0].get<std::string>());
}

TEST_F(TestTree, defaultConstructAndPushBackElementMakesIsArrayReturnTrue)
{
    auto t = Json::Tree();
    t.pushBack(std::string("some_value"));
    EXPECT_TRUE(t.isArray());
}

TEST_F(TestTree, pushBackSeveralValuesIntoArrayAndGetWithArrayIndexReturnsSameValue)
{
    auto t = Json::Tree();
    t.pushBack(false);
    t.pushBack(std::string("some_value"));
    t.pushBack(43);
    t.pushBack(23.5f);
    EXPECT_EQ(false, t[0].get<bool>());
    EXPECT_EQ("some_value", t[1].get<std::string>());
    EXPECT_EQ(43, t[2].get<int>());
    EXPECT_FLOAT_EQ(23.5f, t[3].get<float>());
}

TEST_F(TestTree, tryToAccessArrayIndexOnEmptyTreeThrowsHelpfulError)
{
    auto t = Json::Tree();

    EXPECT_THROW({
        try
        {
            auto a = t[0];
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("array"));
            EXPECT_THAT(err_msg, HasSubstr("operator[] (size_t)"));
            EXPECT_THAT(err_msg, HasSubstr("uninitalised Tree"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}

TEST_F(TestTree, pushBackSeveralValuesIntoArrayAndGetSize)
{
    auto subtree_1 = Json::Tree();
    subtree_1["some_int_field"] = 14;
    subtree_1["some_string_field"] = std::string("hello world");
    auto subtree_2 = Json::Tree();
    subtree_2["some_bool_field"] = true;
    subtree_2["some_float_field"] = 13.5f;

    auto t = Json::Tree();
    t.pushBack(subtree_1);
    t.pushBack(43);
    t.pushBack(subtree_2);

    EXPECT_EQ(14, t[0]["some_int_field"].get<int>());
    EXPECT_EQ("hello world", t[0]["some_string_field"].get<std::string>());
    EXPECT_EQ(43, t[1].get<int>());
    EXPECT_FLOAT_EQ(13.5f, t[2]["some_float_field"].get<float>());
    EXPECT_EQ(true, t[2]["some_bool_field"].get<bool>());
}

TEST_F(TestTree, pushBackSeveralValuesIncludingSubtreesIntoArrayAndGetSize)
{
    auto t = Json::Tree();
    t.pushBack(false);
    t.pushBack(std::string("some_value"));
    t.pushBack(43);
    t.pushBack(23.5f);
    EXPECT_EQ(4, t.size());
}

TEST_F(TestTree, defaultConstructAndGetSizeReturnsZero)
{
    auto t = Json::Tree();
    EXPECT_EQ(0, t.size());
}

TEST_F(TestTree, assignMultipleValuesToDifferentFieldsAndGetSize)
{
    auto t = Json::Tree();
    t["some_int_field"] = 14;
    t["some_string_field"] = std::string("hello world");
    t["some_bool_field"] = true;
    t["some_float_field"] = 13.5f;
    t["some_other_value"] = Json::Tree();
    EXPECT_EQ(5, t.size());
}

TEST_F(TestTree, constructValueAndGetSizeReturnsZero)
{
    auto t = Json::Tree(12);
    EXPECT_EQ(0, t.size());
}

TEST_F(TestTree, constructFromValueAndTryToGetFieldValueThrowsErrorWithHelpfulMessage)
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

TEST_F(TestTree, constructArrayAndTryToGetFieldValueThrowsErrorWithHelpfulMessage)
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

TEST_F(TestTree, constructFromValueAndTryToGetArrayElementThrowsErrorWithHelpfulMessage)
{
    auto t = Json::Tree(23.1f);
    EXPECT_THROW({
        try
        {
            t[0] = 10;
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("array"));
            EXPECT_THAT(err_msg, HasSubstr("operator[] (size_t)"));
            EXPECT_THAT(err_msg, HasSubstr("value"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}

TEST_F(TestTree, constructDocumentAndTryToGetArrayElementThrowsErrorWithHelpfulMessage)
{
    auto t = Json::Tree();
    t["some_field"] = 10;
    ASSERT_TRUE(t.isDocument());
    EXPECT_THROW({
        try
        {
            t[0] = 10;
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("array"));
            EXPECT_THAT(err_msg, HasSubstr("operator[] (size_t)"));
            EXPECT_THAT(err_msg, HasSubstr("document"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}

TEST_F(TestTree, iterateOverDocumentOfValuesGetCorrectFieldsAndValuesAsPairs)
{
    auto t = Json::Tree();
    t["first_field"] = 10;
    t["second_field"] = true;
    t["thrid_field"] = std::string("hello");

    auto it = std::begin(t);

    EXPECT_EQ("first_field", it->first);
    EXPECT_EQ(10, it->second.get<int>());
    ++it;
    EXPECT_EQ("second_field", it->first);
    EXPECT_TRUE(it->second.get<bool>());
    ++it;
    EXPECT_EQ("thrid_field", it->first);
    EXPECT_EQ("hello", it->second.get<std::string>());
    ++it;
    EXPECT_TRUE(it == std::end(t));
}

TEST_F(TestTree, iterateOverConstDocumentOfValuesGetCorrectFieldsAndValuesAsPairs)
{
    auto t = Json::Tree();
    t["first_field"] = 10;
    t["second_field"] = true;
    t["thrid_field"] = std::string("hello");

    auto const t_const = t;

    auto it = std::begin(t_const);

    EXPECT_EQ("first_field", it->first);
    EXPECT_EQ(10, it->second.get<int>());
    ++it;
    EXPECT_EQ("second_field", it->first);
    EXPECT_TRUE(it->second.get<bool>());
    ++it;
    EXPECT_EQ("thrid_field", it->first);
    EXPECT_EQ("hello", it->second.get<std::string>());
    ++it;
    EXPECT_TRUE(it == std::end(t_const));
}

TEST_F(TestTree,
    iterateOverDocumentOfValuesWithConstIteratorsAndGetCorrectFieldsAndValuesAsPairs)
{
    auto t = Json::Tree();
    t["first_field"] = 10;
    t["second_field"] = true;
    t["thrid_field"] = std::string("hello");

    auto it = std::cbegin(t);

    EXPECT_EQ("first_field", it->first);
    EXPECT_EQ(10, it->second.get<int>());
    ++it;
    EXPECT_EQ("second_field", it->first);
    EXPECT_TRUE(it->second.get<bool>());
    ++it;
    EXPECT_EQ("thrid_field", it->first);
    EXPECT_EQ("hello", it->second.get<std::string>());
    ++it;
    EXPECT_TRUE(it == std::cend(t));
}

TEST_F(TestTree, iterateOverArrayGivesaCorrectValuesInOrderWithEmptyStringsForKeys)
{
    auto t = Json::Tree();
    t.pushBack(10);
    t.pushBack(false);
    t.pushBack(std::string("hello"));

    ASSERT_TRUE(t.isArray());
    ASSERT_EQ(3, t.size());

    auto it = std::begin(t);

    EXPECT_TRUE(it->first.empty());
    EXPECT_EQ(10, it->second.get<int>());
    ++it;
    EXPECT_TRUE(it->first.empty());
    EXPECT_FALSE(it->second.get<bool>());
    ++it;
    EXPECT_TRUE(it->first.empty());
    EXPECT_EQ("hello", it->second.get<std::string>());
    ++it;
    EXPECT_TRUE(it == std::end(t));
}

TEST_F(TestTree, iterateOverConstArrayGivesaCorrectValuesInOrderWithEmptyStringsForKeys)
{
    auto t = Json::Tree();
    t.pushBack(10);
    t.pushBack(false);
    t.pushBack(std::string("hello"));

    auto const t_const = t;

    ASSERT_TRUE(t_const.isArray());
    ASSERT_EQ(3, t_const.size());

    auto it = std::begin(t_const);

    EXPECT_TRUE(it->first.empty());
    EXPECT_EQ(10, it->second.get<int>());
    ++it;
    EXPECT_TRUE(it->first.empty());
    EXPECT_FALSE(it->second.get<bool>());
    ++it;
    EXPECT_TRUE(it->first.empty());
    EXPECT_EQ("hello", it->second.get<std::string>());
    ++it;
    EXPECT_TRUE(it == std::end(t_const));
}

TEST_F(TestTree,
    iterateOverArrayWithConstIteratorsGivesaCorrectValuesInOrderWithEmptyStringsForKeys)
{
    auto t = Json::Tree();
    t.pushBack(10);
    t.pushBack(false);
    t.pushBack(std::string("hello"));

    auto const t_const = t;

    ASSERT_TRUE(t_const.isArray());
    ASSERT_EQ(3, t_const.size());

    auto it = std::cbegin(t_const);

    EXPECT_TRUE(it->first.empty());
    EXPECT_EQ(10, it->second.get<int>());
    ++it;
    EXPECT_TRUE(it->first.empty());
    EXPECT_FALSE(it->second.get<bool>());
    ++it;
    EXPECT_TRUE(it->first.empty());
    EXPECT_EQ("hello", it->second.get<std::string>());
    ++it;
    EXPECT_TRUE(it == std::cend(t_const));
}

TEST_F(TestTree, callingBeginOnValueGivesEndIterator)
{
    auto t = Json::Tree("some_value");

    ASSERT_TRUE(t.isValue());

    auto it = std::begin(t);
    EXPECT_TRUE(it == std::end(t));
}

TEST_F(TestTree, eraseFieldThatExistsReturns1)
{
    auto t = Json::Tree();
    t["first"] = 10;
    t["second"] = false;
    t["third"] = std::string("hello");

    ASSERT_TRUE(t.isDocument());
    ASSERT_EQ(3, t.size());

    EXPECT_EQ(1, t.erase("second"));
}

TEST_F(TestTree,
    eraseFieldFromDocumentByFieldNameForFieldThatExistsAndIterateThroughGivesCorrectValues)
{
    auto t = Json::Tree();
    t["first"] = 10;
    t["second"] = false;
    t["third"] = std::string("hello");

    ASSERT_TRUE(t.isDocument());
    ASSERT_EQ(3, t.size());

    t.erase("second");

    ASSERT_EQ(2, t.size());
    auto it = std::begin(t);
    EXPECT_EQ("first", it->first);
    EXPECT_EQ(10, it->second.get<int>());
    ++it;
    EXPECT_EQ("third", it->first);
    EXPECT_EQ("hello", it->second.get<std::string>());
    ++it;
    EXPECT_TRUE(it == std::end(t));
}

TEST_F(TestTree,
    eraseFieldFromDocumentByFieldNameForFieldThatExistsAndGetExistingFieldsByNameGivesCorrectValues)
{
    auto t = Json::Tree();
    t["first"] = 10;
    t["second"] = false;
    t["third"] = std::string("hello");

    ASSERT_TRUE(t.isDocument());
    ASSERT_EQ(3, t.size());

    t.erase("second");

    ASSERT_EQ(2, t.size());
    EXPECT_EQ(10, t["first"].get<int>());
    EXPECT_EQ("hello", t["third"].get<std::string>());
}

TEST_F(TestTree, eraseFieldThatDoesNotExistFromDocumentReturnsZero)
{
    auto t = Json::Tree();
    t["first"] = 10;
    t["second"] = false;
    t["third"] = std::string("hello");

    EXPECT_EQ(0, t.erase("some_field"));
}

TEST_F(TestTree, eraseFieldThatDoesNotExistFromDocumentDoesNotChangeSizeOfDocument)
{
    auto t = Json::Tree();
    t["first"] = 10;
    t["second"] = false;
    t["third"] = std::string("hello");

    ASSERT_EQ(3, t.size());

    t.erase("some_field");

    EXPECT_EQ(3, t.size());
}

TEST_F(TestTree,
    eraseFieldThatDoesNotExistFromDocumentDoesNotChangeExistingValuesWhenAccessedByFieldName)
{
    auto t = Json::Tree();
    t["first"] = 10;
    t["second"] = false;
    t["third"] = std::string("hello");

    ASSERT_TRUE(t.isDocument());
    ASSERT_EQ(3, t.size());

    t.erase("some_field");

    EXPECT_EQ(10, t["first"].get<int>());
    EXPECT_FALSE(t["second"].get<bool>());
    EXPECT_EQ("hello", t["third"].get<std::string>());
}

TEST_F(TestTree,
    eraseFieldFromDocumentAndInsertTheSameFieldAndAccessAllFieldsByFieldNameGivesorrectValues)
{
    auto t = Json::Tree();
    t["first"] = 10;
    t["second"] = false;
    t["third"] = std::string("hello");

    ASSERT_TRUE(t.isDocument());
    ASSERT_EQ(3, t.size());

    t.erase("second");
    t["second"] = 23.5f;

    EXPECT_EQ(10, t["first"].get<int>());

    std::cout << static_cast<int>(t["third"].getValue().type()) << std::endl;

    EXPECT_EQ("hello", t["third"].get<std::string>());
    EXPECT_FLOAT_EQ(23.5f, t["second"].get<float>());
}

TEST_F(TestTree, tryToEraseFieldFromValueTreeThrowsErrorWithHelpfulMessage)
{
    auto t = Json::Tree(std::string("some_value"));
    ASSERT_TRUE(t.isValue());

    EXPECT_THROW({
        try
        {
            t.erase("some_field");
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("document"));
            EXPECT_THAT(err_msg, HasSubstr("erase(std::string)"));
            EXPECT_THAT(err_msg, HasSubstr("value"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}

TEST_F(TestTree, tryToEraseFieldFromArrayTreeThrowsErrorWithHelpfulMessage)
{
    auto t = Json::Tree();
    t.pushBack(1);
    ASSERT_TRUE(t.isArray());

    EXPECT_THROW({
        try
        {
            t.erase("some_field");
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("document"));
            EXPECT_THAT(err_msg, HasSubstr("erase(std::string)"));
            EXPECT_THAT(err_msg, HasSubstr("array"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}

TEST_F(TestTree, eraseElementFromDocumentTreeWithIteratorReducesSizeByOne)
{
    auto t = Json::Tree();
    t["a"] = 10;
    t["b"] = 12.3f;
    t["c"] = true;

    ASSERT_EQ(3, t.size());

    auto element_to_erase = std::begin(t);
    t.erase(element_to_erase);

    EXPECT_EQ(2, t.size());
}

TEST_F(TestTree, eraseElementFromDocumentTreeWithIteratorAndIterateOverRemainingValuesGivesCorrectValues)
{
    auto t = Json::Tree();
    t["a"] = 10;
    t["b"] = 12.3f;
    t["c"] = true;

    ASSERT_EQ(3, t.size());

    auto element_to_erase = std::begin(t);
    t.erase(element_to_erase);

    ASSERT_EQ(2, t.size());
    auto it = std::begin(t);
    EXPECT_EQ("b", it->first);
    EXPECT_FLOAT_EQ(12.3f, it->second.get<float>());
    ++it;
    EXPECT_EQ("c", it->first);
    EXPECT_TRUE(it->second.get<bool>());
    ++it;
    EXPECT_TRUE(it == std::end(t));
}
