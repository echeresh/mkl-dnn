/*******************************************************************************
* Copyright 2016-2019 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef CPU_JIT_UNI_LRN_HPP
#define CPU_JIT_UNI_LRN_HPP

#include "c_types_map.hpp"
#include "type_helpers.hpp"
#include "utils.hpp"

#include "cpu_isa_traits.hpp"
#include "cpu_lrn_pd.hpp"

namespace dnnl {
namespace impl {
namespace cpu {

template <cpu_isa_t isa>
struct jit_uni_lrn_fwd_kernel_f32;
template <cpu_isa_t isa>
struct jit_uni_lrn_bwd_kernel_f32;

template <cpu_isa_t isa>
struct jit_uni_lrn_fwd_t : public primitive_impl_t {
    struct pd_t : public cpu_lrn_fwd_pd_t {
        using cpu_lrn_fwd_pd_t::cpu_lrn_fwd_pd_t;

        DECLARE_COMMON_PD_T(
                JIT_IMPL_NAME_HELPER("jit:", isa, ""), jit_uni_lrn_fwd_t);

        status_t init();

        format_tag_t dat_tag_;
    };

    jit_uni_lrn_fwd_t(const pd_t *apd);
    ~jit_uni_lrn_fwd_t();

    typedef typename prec_traits<data_type::f32>::type data_t;

    virtual status_t execute(const exec_ctx_t &ctx) const override {
        execute_forward(ctx);
        return status::success;
    }

private:
    void execute_forward(const exec_ctx_t &ctx) const;
    const pd_t *pd() const { return (const pd_t *)primitive_impl_t::pd(); }

    jit_uni_lrn_fwd_kernel_f32<isa> *ker_, *ker_first_, *ker_last_;
};

template <cpu_isa_t isa>
struct jit_uni_lrn_bwd_t : public primitive_impl_t {
    struct pd_t : public cpu_lrn_bwd_pd_t {
        using cpu_lrn_bwd_pd_t::cpu_lrn_bwd_pd_t;

        DECLARE_COMMON_PD_T(
                JIT_IMPL_NAME_HELPER("jit:", isa, ""), jit_uni_lrn_bwd_t);

        status_t init();

        format_tag_t dat_tag_;
    };

    jit_uni_lrn_bwd_t(const pd_t *apd);
    ~jit_uni_lrn_bwd_t();

    typedef typename prec_traits<data_type::f32>::type data_t;

    virtual status_t execute(const exec_ctx_t &ctx) const override {
        execute_backward(ctx);
        return status::success;
    }

private:
    void execute_backward(const exec_ctx_t &ctx) const;
    const pd_t *pd() const { return (const pd_t *)primitive_impl_t::pd(); }

    jit_uni_lrn_bwd_kernel_f32<isa> *ker_, *ker_first_, *ker_last_;
};

} // namespace cpu
} // namespace impl
} // namespace dnnl

#endif

// vim: et ts=4 sw=4 cindent cino+=l0,\:4,N-s
