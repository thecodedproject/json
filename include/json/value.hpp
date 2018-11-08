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

    template <typename T>
    Value(T value);

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
