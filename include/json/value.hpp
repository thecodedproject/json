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
#pragma once

#include <string>
#include <stdexcept>
#include <type_traits>
#include <variant>

#include <json/type_defs.hpp>

namespace CodedProject
{
namespace Json
{

template<class T> struct DependentFalse : std::false_type {};

class Value;

std::string toDebugString(Value const& v);

class Value
{
friend std::string toDebugString(Value const&);
public:
    enum class Type
    {
        String,
        Integer,
        FloatingPoint,
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

    template <typename T>
    constexpr Type getType() const;

    std::string objectAsPrintableString() const;

    Type type_ = Type::Null;
    std::variant<String, Integer, FloatingPoint, Bool> value_;
};

std::string toDebugString(Value::Type type);

template <typename T>
constexpr Value::Type Value::getType() const
{
    if constexpr (std::is_same<T, String>::value)
    {
        return Type::String;
    }
    else if constexpr (std::is_same<T, Bool>::value)
    {
        return Type::Bool;
    }
    else if constexpr (std::is_same<T, Integer>::value)
    {
        return Type::Integer;
    }
    else if constexpr (std::is_same<T, FloatingPoint>::value)
    {
        return Type::FloatingPoint;
    }
    else
    {
        static_assert(
            DependentFalse<T>::value,
            "Value::getType(): Not a Json type");
    }
}

template <typename T>
Value::Value(T value)
{
    if constexpr (
        std::is_same<T, std::string>::value ||
        std::is_same<T, const char *>::value)
    {
        value_ = static_cast<String>(value);
        type_ = Type::String;
    }
    else if constexpr (std::is_same<T, Bool>::value)
    {
        value_ = value;
        type_ = Type::Bool;
    }
    else if constexpr (std::is_integral<T>::value)
    {
        value_ = static_cast<Integer>(value);
        type_ = Type::Integer;
    }
    else if constexpr (std::is_floating_point<T>::value)
    {
        value_ = static_cast<FloatingPoint>(value);
        type_ = Type::FloatingPoint;
    }
    else
    {
        static_assert(DependentFalse<T>::value, "Unsupported type");
    }
}

template <typename T>
T Value::get() const
{
    auto requested_type = getType<T>();
    if(type_ == requested_type)
    {
        return std::get<T>(value_);
    }
    else
    {
        throw IncorrectTypeConversion(*this, toDebugString(requested_type));
    }
}

}
}
