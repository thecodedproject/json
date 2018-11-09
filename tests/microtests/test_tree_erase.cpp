#include <gmock/gmock.h>

#include <json/tree.hpp>

using namespace CodedProject;
using namespace ::testing;

class TestTreeErase : public ::testing::Test
{
};

TEST_F(TestTreeErase, eraseFieldThatExistsReturns1)
{
    auto t = Json::Tree();
    t["first"] = 10;
    t["second"] = false;
    t["third"] = std::string("hello");

    ASSERT_TRUE(t.isDocument());
    ASSERT_EQ(3, t.size());

    EXPECT_EQ(1, t.erase("second"));
}

TEST_F(TestTreeErase,
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

TEST_F(TestTreeErase,
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

TEST_F(TestTreeErase, eraseFieldThatDoesNotExistFromDocumentReturnsZero)
{
    auto t = Json::Tree();
    t["first"] = 10;
    t["second"] = false;
    t["third"] = std::string("hello");

    EXPECT_EQ(0, t.erase("some_field"));
}

TEST_F(TestTreeErase, eraseFieldThatDoesNotExistFromDocumentDoesNotChangeSizeOfDocument)
{
    auto t = Json::Tree();
    t["first"] = 10;
    t["second"] = false;
    t["third"] = std::string("hello");

    ASSERT_EQ(3, t.size());

    t.erase("some_field");

    EXPECT_EQ(3, t.size());
}

TEST_F(TestTreeErase,
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

TEST_F(TestTreeErase,
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

TEST_F(TestTreeErase, tryToEraseFieldFromValueTreeThrowsErrorWithHelpfulMessage)
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

TEST_F(TestTreeErase, tryToEraseFieldFromArrayTreeThrowsErrorWithHelpfulMessage)
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

TEST_F(TestTreeErase, eraseElementFromDocumentTreeWithIteratorReducesSizeByOne)
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

TEST_F(TestTreeErase, eraseElementFromDocumentTreeWithIteratorAndIterateOverRemainingValuesGivesCorrectValues)
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

TEST_F(TestTreeErase,
    eraseElementFromDocumentTreeWithIteratorAndGetRemainingValuesByFieldGivesCorrectValues)
{
    auto t = Json::Tree();
    t["a"] = 10;
    t["b"] = 12.3f;
    t["c"] = true;

    ASSERT_EQ(3, t.size());

    auto element_to_erase = std::begin(t);
    t.erase(element_to_erase);

    EXPECT_FLOAT_EQ(12.3f, t["b"].get<float>());
    EXPECT_TRUE(t["c"].get<bool>());
}
