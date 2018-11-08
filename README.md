
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

**Note** that this wont work because it will mean that the type contained within the Value would need to be named within any containers which hold multiple values, i.e. within the contianer inside the Tree class.
This goes against the purpose of the value type which is abstract away the actual underlying type at compile time, having it only visible at runtime.

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

The ValueTypeTraits could contain a return type for each, such that specialisations of different similar types could return the same things, e.g. flaot and double always returning double maybe??

```
template <>
struct TypeTrait<float>
{
    static Value::Type type = Value::Type::Double;
    typedef double return_type;
};

template <>
struct TypeTrait<double>
{
    static Value::Type type = Value::Type::Double;
    typedef double return_type;
};

```

or std;:string and char * always returning std::string:

```
template <>
struct TypeTrait<std::string>
{
    static Value::Type type = Value::Type::String;
    typedef std::string return_type;
};

template <>
struct TypeTrait<char*>
{
    static Value::Type type = Value::Type::String;
    typedef std::string return_type;
};
```



