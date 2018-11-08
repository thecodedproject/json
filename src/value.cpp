#include <json/value.hpp>

namespace CodedProject
{
namespace Json
{

Value::Value() = default;

template <>
Value::Value(std::string s)
: type_(Type::String),
  string_value_(s)
{
}

template <>
Value::Value(char const * s)
: type_(Type::String),
  string_value_(s)
{
}

template <>
Value::Value(int i)
: type_(Type::Integer),
  integer_value_(i)
{
}

template <>
Value::Value(float f)
: type_(Type::Float),
  float_value_(f)
{
}

template <>
Value::Value(bool b)
: type_(Type::Bool),
  bool_value_(b)
{
}

bool Value::operator== (Value const& rhs) const
{
    return string_value_ == rhs.string_value_ &&
        float_value_ == rhs.float_value_ &&
        integer_value_ == rhs.integer_value_ &&
        bool_value_ == rhs.bool_value_;
}

bool Value::operator!= (Value const& rhs) const
{
    return !operator==(rhs);
}

Value::Type Value::type() const
{
    return type_;
}

std::string Value::asString() const
{
    if(type_ == Type::String)
    {
        return string_value_;
    }
    else
    {
        throw IncorrectTypeConversion(*this, "asString");
    }
}

int Value::asInteger() const
{
    if(type_ == Type::Integer)
    {
        return integer_value_;
    }
    else
    {
        throw IncorrectTypeConversion(*this, "asInteger");
    }
}

float Value::asFloat() const
{
    if(type_ == Type::Float)
    {
        return float_value_;
    }
    else
    {
        throw IncorrectTypeConversion(*this, "asFloat");
    }
}

bool Value::asBool() const
{
    if(type_ == Type::Bool)
    {
        return bool_value_;
    }
    else
    {
        throw IncorrectTypeConversion(*this, "asBool");
    }
}

std::string Value::objectAsPrintableString() const
{
    switch(type_)
    {
        case Type::Integer:
            return "Value(" + std::to_string(integer_value_) + ", Integer)";
        case Type::Bool:
            if(bool_value_)
                return "Value(true, Bool)";
            else
                return "Value(false, Bool)";
        case Type::String:
            return "Value(" + string_value_ + ", String)";
        case Type::Float:
            return "Value(" + std::to_string(float_value_) + ", Float)";
    }
}

}
}
