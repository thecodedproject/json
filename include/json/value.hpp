#pragma once

#include <string>
#include <stdexcept>

namespace CodedProject
{
namespace Json
{

class Value
{
public:
    enum class Type
    {
        String,
        Integer,
        Float,
        Bool
    };

    class IncorrectTypeConversion : public std::runtime_error
    {
    public:
        IncorrectTypeConversion(Value const& v, std::string const& function)
        : std::runtime_error(
            "Trying to get" + v.objectAsPrintableString() + " " + function)
        {
        }
    };

    Value();

    // These would be better servered by a template constructor
    // which used enable_if and type traits to turn on certain
    // constructors based upon the type being passed in JDC 20181105
    Value(std::string const& s);
    Value(char * s);
    Value(int i);
    Value(float f);
    Value(bool b);

    bool operator== (Value const& rhs) const;
    bool operator!= (Value const& rhs) const;

    Type type() const;

    std::string asString() const;
    int asInteger() const;
    float asFloat() const;
    bool asBool() const;

private:

    std::string objectAsPrintableString() const;

    Type type_ = {};
    std::string string_value_ = {};
    int integer_value_ = {};
    float float_value_ = {};
    bool bool_value_ = {};
};

}
}
