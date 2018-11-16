#pragma once

#include <string>
#include <stdexcept>

namespace CodedProject
{
namespace Json
{

class Value;

std::string toString(Value const& v);

class Value
{
friend std::string toString(Value const&);
public:
    enum class Type
    {
        String,
        Integer,
        Float,
        Bool,
        Null
    };

    class IncorrectTypeConversion : public std::runtime_error
    {
    public:
        IncorrectTypeConversion(Value const& v, std::string const& type_string)
        : std::runtime_error(
            "Trying to get " + v.objectAsPrintableString() + " as " + type_string)
        {
        }
    };

    Value();

    template <typename T>
    Value(T value);

    bool operator== (Value const& rhs) const;
    bool operator!= (Value const& rhs) const;

    Type type() const;

    template <typename T> T get() const;

private:

    std::string objectAsPrintableString() const;

    Type type_ = Type::Null;
    std::string string_value_ = {};
    int integer_value_ = {};
    float float_value_ = {};
    bool bool_value_ = {};
};

}
}
