#include <json/value.hpp>

#include <json/conversion_helpers/to_json_text.hpp>

namespace CodedProject
{
namespace Json
{

std::string toString(Value const& v)
{
    return v.objectAsPrintableString();
}

std::string toString(Value::Type type)
{
    switch(type)
    {
        case Value::Type::String:
            return "String";
        case Value::Type::Integer:
            return "Integer";
        case Value::Type::Bool:
            return "Bool";
        case Value::Type::Float:
            return "Float";
        case Value::Type::Null:
            return "Null";
    }
}

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

template <>
std::string Value::get() const
{
    if(type_ == Type::String)
    {
        return string_value_;
    }
    else
    {
        throw IncorrectTypeConversion(*this, "std::string");
    }
}

template <>
int Value::get() const
{
    if(type_ == Type::Integer)
    {
        return integer_value_;
    }
    else
    {
        throw IncorrectTypeConversion(*this, "int");
    }
}

template <>
float Value::get() const
{
    if(type_ == Type::Float)
    {
        return float_value_;
    }
    else
    {
        throw IncorrectTypeConversion(*this, "float");
    }
}

template <>
bool Value::get() const
{
    if(type_ == Type::Bool)
    {
        return bool_value_;
    }
    else
    {
        throw IncorrectTypeConversion(*this, "bool");
    }
}

std::string Value::objectAsPrintableString() const
{
    return "Value(" +
        ConversionHelpers::toJsonText(*this) + "," +
        toString(type()) + ")";
}

}
}
