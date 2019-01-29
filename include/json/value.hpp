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

std::string toString(Value const& v);

class Value
{
friend std::string toString(Value const&);
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

    std::string objectAsPrintableString() const;

    Type type_ = Type::Null;
    std::variant<String, Integer, FloatingPoint, Bool> value_;
};

template <typename T>
Value::Value(T value)
{
    if constexpr (
        std::is_same<T, std::string>::value ||
        std::is_same<T, const char *>::value)
    {
        type_ = Type::String;
        value_ = static_cast<String>(value);
    }
    else if constexpr (std::is_same<T, bool>::value)
    {
        type_ = Type::Bool;
        value_ = value;
    }
    else if constexpr (std::is_integral<T>::value)
    {
        type_ = Type::Integer;
        value_ = static_cast<Integer>(value);
    }
    else if constexpr (std::is_floating_point<T>::value)
    {
        type_ = Type::FloatingPoint;
        value_ = static_cast<FloatingPoint>(value);
    }
    else
    {
        static_assert(DependentFalse<T>::value, "Unsupported type");
    }
}

std::string toString(Value::Type type);

}
}
