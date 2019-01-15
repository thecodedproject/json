/* Copyright (c) 2018, Coded Project
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * * Neither the name of the Coded Project nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
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
