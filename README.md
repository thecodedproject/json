
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

## Improvements over Boost ptree (for the desired purpose of representing JSON, which is not what Boost ptree is meant for!):

* Preserves type information of the stored values.

* Gives explicit methods to tell if any given node in the tree is an array, document or value.

* Does not allow duplicate fields to be inserted into a document

## Grammers:

```
json_expression: document | array | VALUE | STRING_VALUE

document: LEFT_DOCUMENT_BRACE STRING_VALUE COLON json_expression (COMMA STRING_VALUE json_expression)* RIGHT_DOCUMENT_BRACE

array: LEFT_ARRAY_BRACE json_expression (COMMA expression_list)* RIGHT_ARRAY_BRACE
```


## Future improvements


### Allow adding trees with builder; i.e. pushBack(Tree), append("...", Tree), concat(Tree)...

### Better way to consturct null tree/value (connected with the potentially dodgey template, catch-all constuctor)

### Muddy `toString` statements

There are alot of toString overloads in the `CodedProject::Json` namespace - I feel like they should all do the same thing probably: convert the object to Json (if applicable).
However some, namely `toString(Value)` converts to a printable string showing the type, not to JSON.
Potentially rethink this design?

### Order independent comparison (of documents) and sort functions (for documents only)

This has been put into a new function called `compareOrderIndependent` (rather than muddying up the `operator==`).
However I'm not sure if that function name captures that the order independent-ness is only for documents and not arrays.

The reasoning for putting this in its own function rather than making it part of `operator==` is as follows;

A document currently stores the ordering of the fields inserted into it - when iterating through a document you visit fields in the order they were inserted; therefore it seems wierd to have the `operator==` return true for two documents which have different observable behaviours (i.e. same fields + values but in different order).
To resolve this there are two options; either remove the ordering of documents completely, or have `operator==` consider document order and create a new function for order indepenent comparison of documents.
The second option was favoured as to not remove the ordering functionality of documents which may be useful in some situations.

### Handle escpaed double quotes within strings

### Extra helper methods on Builder

```
Builder.append({"a", 1}, {"b", 2}, ...)

Builder.pushBack(1, 2, ...)


Builder.append("a", Container<T>)
```


### Builder interface

Not sure of the interface for openeing/closing subtrees in the builder.
Currently use the methods openSubtree and closeSubtree; however these don't make explicitly clear what you are adding to... Not sure if that is a problem?

### Possible issue

Does

```
template <typename T>
Tree(T const& value);
```
define the copy constructor for Tree??


Also the error messages created from this `catch all` constructor are very nasty - it's always link time errors!

### Issue with const-ness of field values in tree

Currently field values in a tree and not const; therefore when iterating over a tree they could be changed. I'm not sure if this is desired behvaiour?

If it is, it defaintely won't work properly - the field values may be changed, but the indexs which they associate to will not be updated so future field-name look up with fail for the new values (and be incorrect for the old values).

If it not, then the field values need to be made const - however this is slightly complicated as `std::pair<std::string const, Tree>` has an implicitly deleted copy constructor, and the copy constructor is needed by some methods on `std;:vector`.
I see two options here; either

* make a new key-value-pair type where the key value is always const but is also copyable (will probably require some nasty `const_cast`, and update `Tree::values_` to use that new type instead of `std::pair`
* _Or_ make a custom iterator for tree which always returns a const reference to the field.

### Idea for Basic Build structure (to remove duplicate code)

**Note** Does not work as the `closeDocument` and `closeArray` functions on a builder need to return the same type, and if there are different builder types for document and arrays the close methods have no knowledge of what type they should be returning.

```
class BasicBuilderBase
{
 ... commong stuffs ...
};

class Document : BasicBuilderBase {...};

class Array : BasicBuilderBase {...};
```

### Idea for inheritance hirearchy

I don' really like this design as TreeBase will still need to have all of the methods for accessing either a document, array or value so that when iterating over a Tree you can access the contents regarless of underlying type - to me this represents just writing extra code for the sake of a small sytactic improvment.
```
class TreeBase
{
    ... all public methods from Tree ...
protected:
    (all private functions from current Tree class as protected members)
};

class Document : public TreeBase
{
public:
    ... all document functions from Tree ...
};

class Array : public TreeBase
{
public:
    ... all array functions from Tree ...
};

class Value : puble TreeBase
{
    ... all value functions from tree ...
};
```


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



