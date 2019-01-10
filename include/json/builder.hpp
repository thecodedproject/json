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

#include <memory>

#include <json/tree.hpp>

namespace CodedProject
{
namespace Json
{

class Builder
{
public:
    Builder();

    template <typename T>
    Builder& append(
        std::string const& field,
        T const& value);

    template <typename... Args>
    Builder& pushBack(
        Args&&... values);

    Builder& openSubtree();
    Builder& openSubtree(std::string const& field);
    Builder& closeSubtree();

/*  I dont think it makes sense to present this interface
    as well as the openSubtree/closeSubtree JDC 20181113

    Builder& openArray();
    Builder& openArray(std::string const& field);
    Builder& closeArray();

    Builder& openDocument();
    Builder& openDocument(std::string const& field);
    Builder& closeDocument();
*/

    Tree getTree();

private:
    Builder(
        Builder * parent_builder,
        std::string const& parent_field_name);

    Builder& setupChildBuilder(std::string const& field="");

    Tree tree_ = {};
    std::unique_ptr<Builder> child_builder_ = {};
    Builder * parent_builder_ = nullptr;
    std::string parent_field_name_ = {};
};

template <typename T>
Builder& Builder::append(
    std::string const& field,
    T const& value)
{
    tree_[field] = value;
    return *this;
}

template <typename... Args>
Builder& Builder::pushBack(Args&&... values)
{
    (tree_.pushBack(values), ...);
    return *this;
}

}
}
