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

#include <cublas_v2.h>
#include <cudnn.h>
#include <functional>
#include <string>
#include <unordered_map>

#include "ngraph/runtime/nvidiagpu/nvidiagpu_cuda_context_manager.hpp"
#include "ngraph/runtime/nvidiagpu/nvidiagpu_cuda_function_pool.hpp"

namespace ngraph
{
    namespace runtime
    {
        namespace nvidiagpu
        {
            class StopWatchPool;

            using primitive = std::function<void(void**, void**)>;
            using memory_primitive = std::function<void*(void)>;

            extern "C" {
            struct RuntimeContext
            {
                cudnnHandle_t* cudnn_handle;
                cublasHandle_t* cublas_handle;
                nvidiagpu::primitive* const* nvidiagpu_primitives;
                const nvidiagpu::memory_primitive* nvidiagpu_memory_primitives;
                CudaFunctionPool* compiled_kernel_pool;
                StopWatchPool* stopwatch_pool = nullptr;
                // Note that in it's current state, calling methods of CudaFunctionPool
                // or other native compiled C++ functions in ngraph from the JIT code is
                // unsafe and will fail if the GLIBCXX versions are diffent for the
                // native compiler and clang. If all of the emitted CUDA ops are refactored
                // to use the PrimitiveEmitter, the above pointer can be removed. It is left now
                // for backward compatability.
            };

            void start_stopwatch(RuntimeContext* ctx, size_t idx);
            void stop_stopwatch(RuntimeContext* ctx, size_t idx);
            size_t count_stopwatch(RuntimeContext* ctx, size_t idx);
            size_t us_stopwatch(RuntimeContext* ctx, size_t idx);
            }
        }
    }
}
