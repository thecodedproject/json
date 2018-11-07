
```
ElementType
{

private:

    std::string s;
    float f;
    int i;
    bool b;

    DataType type_;

};


ContainerType
{
public:

    begin...
    end...
    etc...


    isArray();

    isValue();

    ContainerTypeIterator insert(
        std::pair<std::string, ContainerType> ... );

private:


    std::map<std::string, ContainerType> internals...;

};


Builder?
{

    Builder& addField();



    ContainerType get();

};
```

## Improvements over Boost ptree (for the desired purpose of representing JSON):

* Preserves type information of the stored values.

* Gives explicit methods to tell if any given node in the tree is an array, document or value.

* Does not allow duplicate fields to be inserted into a document (although I think that this may be valid JSON)


### Idea for templated Value:

```
template <typename T>
class Value
{
    enum class Type
    {
        String,
        Integer,
        Float,
        Bool
    };

    Value(T t);

    Type type() const;

    T get() const;

private:

    T value_;
};

template <typename T>
struct TypeTrait;

template <>
struct TypeTrait<int>
{
    static Value::Type type = Value::Type::Integer;
};

template <>
struct TypeTrait<float>
{
    static Value::Type type = Value::Type::Float;
};

template <>
struct TypeTrait<std::string>
{
    static Value::Type type = Value::Type::String;
};

template <>
struct TypeTrait<bool>
{
    static Value::Type type = Value::Type::Bool;
};

template <typename T>
Value::Type Value<T>::type() const
{
    return TypeTrait<T>::type;
}

```





