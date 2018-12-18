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
#include <json/tree.hpp>

#include <algorithm>

#include <iostream>

namespace CodedProject
{
namespace Json
{

Tree::Tree() = default;

Tree::Tree(Type type)
: type_(type)
{

}

bool Tree::operator== (Tree const& rhs) const
{
    if(type_ != rhs.type_)
        return false;

    if(isDocument() || isArray())
    {
        return values_ == rhs.values_;
    }

    return value_ == rhs.value_;
}

bool Tree::operator!= (Tree const& rhs) const
{
    return !operator==(rhs);
}

bool Tree::compareOrderIndependent(Tree const& rhs) const
{
    if(!isDocument() || !rhs.isDocument())
    {
        return operator==(rhs);
    }

    for(auto const& field_index : field_indexes_)
    {
        auto field = field_index.first;
        auto i = field_index.second;

        if(!rhs.count(field))
        {
            return false;
        }

        auto rhs_i = rhs.field_indexes_.at(field);
        if(!values_[i].second.compareOrderIndependent(
            rhs.values_[rhs_i].second))
        {
            return false;
        }
    }

    return true;
}

bool Tree::isArray() const
{
    return type_==Type::Array;
}

bool Tree::isDocument() const
{
    return type_==Type::Document;
}

bool Tree::isValue() const
{
    return type_==Type::Value;
}

Tree::iterator Tree::begin()
{
    return std::begin(values_);
}

Tree::const_iterator Tree::begin() const
{
    return std::begin(values_);
}

Tree::const_iterator Tree::cbegin() const noexcept
{
    return std::cbegin(values_);
}

Tree::iterator Tree::end()
{
    return std::end(values_);
}

Tree::const_iterator Tree::end() const
{
    return std::end(values_);
}

Tree::const_iterator Tree::cend() const noexcept
{
    return std::cend(values_);
}

size_t Tree::size() const
{
    return values_.size();
}

void Tree::erase(iterator position)
{
    auto field_to_remove = position->first;
    erase(field_to_remove);
}

Tree & Tree::operator[] (size_t index)
{
    throwIncorrectCallIfNotArray("operator[] (size_t)");
    return values_[index].second;
}

Tree & Tree::at(size_t index)
{
    throwIncorrectCallIfNotArray("at(size_t)");

    if(!(index<size()))
    {
        throw std::out_of_range(
            "CodedProject::Json::Tree::at(size_t): "
            "index " +
            std::to_string(index) +
            " out of range in array of size " +
            std::to_string(size()));
    }

    return operator[](index);
}

Tree const& Tree::at(size_t index) const
{
    return const_cast<Tree*>(this)->at(index);
}

void Tree::pushBack(Tree subtree)
{
    throwIncorrectCallIfPredicate(
        "pushBack(Tree)",
        Type::Array,
        [this](){
            return this->isDocument() || this->isValue();
        });
    type_ = Type::Array;
    values_.push_back({"",subtree});
}

Tree & Tree::operator[] (std::string const& field)
{
    throwIncorrectCallIfNotDocument("operator[] (std::string)");

    type_ = Type::Document;
    if(!count(field))
    {
        field_indexes_[field] = values_.size();
        values_.push_back({field, {}});
    }
    auto field_index = field_indexes_[field];
    return values_[field_index].second;
}

Tree & Tree::at(std::string const& field)
{
    if(!count(field))
    {
        throw std::out_of_range(
            "CodedProject::Json::Tree::at(std::string): "
            "key '" + field + "' not found"
        );
    }
    return operator[](field);
}

Tree const& Tree::at(std::string const& field) const
{
    return const_cast<Tree*>(this)->at(field);
}

int Tree::count(std::string const& field_name) const
{
    throwIncorrectCallIfNotDocument("count()");
    return field_indexes_.count(field_name);
}

Tree::size_type Tree::erase(std::string const& field_name)
{
    throwIncorrectCallIfNotDocument("erase(std::string)");

    if(!count(field_name))
        return 0;

    auto index_to_remove = field_indexes_[field_name];

    auto element_to_erase = std::begin(values_);
    std::advance(element_to_erase, index_to_remove);

    values_.erase(element_to_erase);

    for(auto & kv : field_indexes_)
    {
        if(kv.second>index_to_remove)
            --kv.second;
    }

    field_indexes_.erase(field_name);

    return 1;
}

Value const& Tree::getValue() const
{
    if(isValue())
        return value_;
    else
        throw IncorrectCallForType(
            "value function `getValue()`",
            typeAsString());

}

std::string Tree::typeAsString() const
{
    return toString(type_);
}

bool Tree::isNotDocument() const
{
    return isValue() || isArray();
}

void Tree::throwIncorrectCallIfNotArray(std::string function_signature) const
{
    throwIncorrectCallIfPredicate(
        function_signature,
        Type::Array,
        [this](){
            return !this->isArray();
        });
}

void Tree::throwIncorrectCallIfNotDocument(std::string function_signature) const
{
    throwIncorrectCallIfPredicate(
        function_signature,
        Type::Document,
        [this](){
            return this->isNotDocument();
        });
}

void Tree::throwIncorrectCallIfPredicate(
    std::string function_signature,
    Type function_allowed_type,
    std::function<bool()> pred) const
{
    if(pred())
    {
        throw IncorrectCallForType(
            toString(function_allowed_type) +
                "function `" + function_signature + "`",
            typeAsString());
    }
}

std::string toString(Tree::Type type)
{
    switch(type)
    {
        case Tree::Type::Array:
            return "array";
        case Tree::Type::Document:
            return "document";
        case Tree::Type::Value:
            return "value";
        case Tree::Type::Uninitialised:
            return "uninitialised";
    }
}

}
}
