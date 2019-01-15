#include <gmock/gmock.h>

#include <type_traits>

class TestIfConstExprTemplateCtor : public ::testing::Test
{
};

template<class T> struct DependentFalse : std::false_type {};

class A
{
public:
    template <typename T>
    A(T t);

    std::string type;
};

template <typename T>
A::A(T t)
{
    if constexpr(std::is_same<T, std::string>::value)
    {
        type = "string";
    }
    else if constexpr(std::is_same<T, int>::value)
    {
        type = "int";
    }
    else
    {
        static_assert(DependentFalse<T>::value, "Wrong type");
    }
}

TEST_F(TestIfConstExprTemplateCtor, string)
{
    A a(std::string("hello"));
    EXPECT_EQ("string", a.type);
}

TEST_F(TestIfConstExprTemplateCtor, integer)
{
    A a(123);
    EXPECT_EQ("int", a.type);
}
