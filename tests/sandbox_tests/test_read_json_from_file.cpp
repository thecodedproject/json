#include <gmock/gmock.h>

#include <fstream>
#include <json/conversion.hpp>

class TestReadJsonFromFile : public ::testing::Test
{
};

TEST_F(TestReadJsonFromFile, readFromFileAndConvertBackToString)
{
    auto f = std::ifstream("temp.json");
    auto stream = std::stringstream();
    stream << f.rdbuf();
    auto json_string = stream.str();

    auto tree = CodedProject::Json::fromString(json_string);

    auto s = CodedProject::Json::toString(tree, true);


}
