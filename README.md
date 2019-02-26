
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

# General design decisions

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


## Design decision around support for narrowing types

The value class may be setup to support all basic types, however JSON will preserver none of this type information.
It is unclear what should happen in the coversion to/from JSON and whether the narrower types should be allowed.
E.g. Integers should _probably_ be stored as `int64_t` (or maybe even `long long`?) (when converted from JSON into `Value`s) in order to avoid narrowing, however does that mean that int32 shouldnt be supported by `Value`? Doing so might make the interface nasty  if `int64_t` has to be used both to set and get values from `Value` and `Tree`.
The same can be said for floating point numbers as well; _probably should_ use `double` not `float`.
(It's unclear what should happen for strings... should they be `std::string` of `char const *`? This is seperate from the narrowing question.)

The best solution seems to be to allow all types with `Value`, then accept the loss of type info when converting to JSON - when converting back from JSON have integeres, real numbers, amd strings convert to some predefined types (e.g. `int_64_t`, `double` and `std::string`) always.


*New thoughts 20190124:*
A potential better solution is to have predefined types for json strings, integers, floating points and bools and only allow `Value` to store one of those particular types.
I.e. the whole JSON lib. will only work with those types and store everyhting in the widest possible representation (which also has the nice property that converting to JSON and back will give JSON trees which compare equal - which semantically they should).
One thing that should happen in this case, however, is to get `Value` to do the conversion from all relevant types to the appropriate long types.
This should be relatively stright forward:

* For strings this is only `std::string` and `char const *` (and maybe `std::string_view`?)
* For integers `std::is_integral` can be used
* For floating points `std::is_float` can be used
* For bools this should be trivial as (I think!) this should only be `bool`)

Not sure what to do about unsigned integers in the above schema... maybe they should be forbidden at compile time? (Seems like the safest thing...)

## toString methods

Only 1 single `toString` method exists in the `Json` namespace (and it's sub-namespaces) - this converts a tree object to a json string.
All other methods used for debugging are named `toDebugString`.


# Future improvements


### Allow adding trees with builder; i.e. pushBack(Tree), append("...", Tree), concat(Tree)...

### Better way to consturct null tree/value (connected with the potentially dodgey template, catch-all constuctor)

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



