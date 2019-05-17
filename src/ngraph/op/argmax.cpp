//*****************************************************************************
// Copyright 2017-2019 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//*****************************************************************************

#include "ngraph/op/argmax.hpp"

using namespace std;
using namespace ngraph;

BasicNodeType<op::ArgMax> op::ArgMax::node_type("ArgMax");

op::ArgMax::ArgMax()
{
}

op::ArgMax::ArgMax(const std::shared_ptr<Node>& arg,
                   size_t axis,
                   const element::Type& index_element_type)
    : op::util::IndexReduction(arg, axis, index_element_type)
{
    constructor_validate_and_infer_types();
}

shared_ptr<Node> op::ArgMax::copy_with_new_args(const NodeVector& new_args) const
{
    check_new_args_count(this, new_args);
    check_new_args_count(this, new_args);
    return make_shared<ArgMax>(new_args.at(0), m_axis, this->get_element_type());
}
