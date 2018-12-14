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
#include <json/builder.hpp>

namespace CodedProject
{
namespace Json
{

Builder::Builder() = default;

Builder::Builder(
    Builder * parent_builder,
    std::string const& parent_field_name)
: parent_builder_{parent_builder},
  parent_field_name_{parent_field_name}
{
}

Builder& Builder::openSubtree()
{
    return setupChildBuilder();
}

Builder& Builder::openSubtree(std::string const& field)
{
    return setupChildBuilder(field);
}

Builder& Builder::closeSubtree()
{
    if(parent_field_name_.empty())
    {
        parent_builder_->pushBack(
            getTree());
    }
    else
    {
        parent_builder_->append(parent_field_name_, getTree());
    }
    return *parent_builder_;
}

Tree Builder::getTree()
{
    return tree_;
}

Builder& Builder::setupChildBuilder(std::string const& field)
{
    child_builder_ = std::unique_ptr<Builder>(
        new Builder(this, field));
    return *child_builder_;
}

}
}
