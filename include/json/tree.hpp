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

#include <map>
#include <stdexcept>
#include <vector>

#include <json/value.hpp>

namespace CodedProject
{
namespace Json
{

class Tree
{
public:
    class IncorrectCallForType : public std::runtime_error
    {
    public:
        IncorrectCallForType(
            std::string const& function_description,
            std::string const& tree_type)
        : std::runtime_error(
            "Trying to call " + function_description +
            " on Json::Tree of type " + tree_type + ".")
        {
        }
    };

    enum class Type
    {
        Array,
        Document,
        Value,
        Uninitialised
    };

    typedef std::pair<std::string, Tree> value_type;
    typedef std::vector<value_type> value_storage_type;
    typedef value_storage_type::iterator iterator;
    typedef value_storage_type::const_iterator const_iterator;
    typedef value_storage_type::size_type size_type;

    Tree();

    Tree(Type type);

    template <typename T>
    Tree(T const& value);

    bool operator== (Tree const& rhs) const;
    bool operator!= (Tree const& rhs) const;

    bool compareOrderIndependent(Tree const& rhs) const;

    bool isArray() const;
    bool isDocument() const;
    bool isValue() const;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const noexcept;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const noexcept;

    size_t size() const;

    void erase(iterator position);

    // ----- Array functions -------
    Tree & operator[] (size_t index);

    Tree & at(size_t index);

    Tree const& at(size_t index) const;

    void pushBack(Tree subtree);

    // ----- Document functions -------

    Tree & operator[] (std::string const& field);
    // std::map doesn't have a const version of operator[].
    // Not sure why, but it makes me think that this function
    // shouldnt be defined. Certinaly it's stops things
    // compiling as it is - leaving it not defined for now
    // JDC 20181105
    //Value const& operator[] (std::string const& field) const;

    Tree & at(std::string const& field);

    Tree const& at(std::string const& field) const;

    int count(std::string const& field_name) const;

    size_type erase(std::string const& field);

    // ----- Value functions -------
    Value const& getValue() const;

    template <typename T>
    T get() const;

private:

    std::string typeAsString() const;

    bool isNotDocument() const;

    void throwIncorrectCallIfNotArray(
        std::string function_signature) const;

    void throwIncorrectCallIfNotDocument(
        std::string function_signature) const;

    void throwIncorrectCallIfPredicate(
        std::string function_signature,
        Type function_allowed_type,
        std::function<bool()> pred) const;

    Type type_ = Type::Uninitialised;
    value_storage_type values_ = {};
    std::map<std::string, size_t> field_indexes_ = {};
    Value value_ = {};
};

template <typename T>
Tree::Tree(T const& value)
: type_(Type::Value),
  value_(value)
{
}

template <typename T>
T Tree::get() const
{
    return value_.get<T>();
}

std::string toDebugString(Tree::Type type);

}
}
