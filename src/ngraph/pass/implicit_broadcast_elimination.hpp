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

#pragma once

#include "ngraph/op/util/broadcasting.hpp"
#include "ngraph/pass/pass.hpp"

namespace ngraph
{
    namespace pass
    {
        template <typename T>
        NodeVector static explicit_broadcast(std::shared_ptr<T>& node)
        {
            if (node->get_autob().type == op::AutoBroadcastType::NONE)
            {
                return node->get_arguments();
            }
            else if (node->get_autob().type == op::AutoBroadcastType::NUMPY)
            {
                return op::numpy_style_broadcast(node->get_arguments());
            }
            else
            {
                throw ngraph_error("Unsupported implicit broadcast type");
            }
        }

        class ImplicitBroadcastElimination : public NodePass
        {
        public:
            bool run_on_node(std::shared_ptr<ngraph::Node> node) override;
        };
    }
}
