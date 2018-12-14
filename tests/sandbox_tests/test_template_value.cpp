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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\"
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
#include <gmock/gmock.h>

class TestTemplateValue : public ::testing::Test
{
};

enum class Type
{
    String,
    Integer,
    Float,
    Bool
};

template <typename T>
struct TypeTrait;

template <>
struct TypeTrait<int>
{
    static Type const type = Type::Integer;
};

template <>
struct TypeTrait<float>
{
    static Type const type = Type::Float;
};

template <>
struct TypeTrait<std::string>
{
    static Type const type = Type::String;
};

template <>
struct TypeTrait<bool>
{
    static Type const type = Type::Bool;
};

template <typename T>
class Value
{
public:

    Value(T value);

    Type type() const;

    T get() const;

private:

    T value_;
};

template <typename T>
Value<T>::Value(T value)
: value_(value)
{
}

template <typename T>
Type Value<T>::type() const
{
    return TypeTrait<T>::type;
}

template <typename T>
T Value<T>::get() const
{
    return value_;
}

TEST_F(TestTemplateValue, some)
{

    auto v = Value<std::string>("10.0fdsa");
    std::cout << static_cast<int>(v.type()) << std::endl;

    auto f = v.get();

    std::cout << f << std::endl;
}
