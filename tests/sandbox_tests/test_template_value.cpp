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
