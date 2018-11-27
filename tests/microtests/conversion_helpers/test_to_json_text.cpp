#include <gmock/gmock.h>

#include <json/conversion_helpers/to_json_text.hpp>

#include <json/value.hpp>

using namespace CodedProject::Json;
using namespace CodedProject::Json::ConversionHelpers;

class TestToJsonText : public ::testing::Test
{
};

TEST_F(TestToJsonText, DISABLED_stringValue)
{
    auto v = Value("some_value");
    EXPECT_EQ("\"some_value\"", toJsonText(v));
}
