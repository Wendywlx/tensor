#pragma once

#include <arm_neon.h>
#include <matazure/config.hpp>
#include <matazure/meta.hpp>

namespace matazure { namespace simd {

	template <typename _ValueType, int_t Rank>
	class neon_vector;

	template <>
	class neon_vector<float, 4> {
	public:
		using value_type = float;
		const static int_t rank = 4;

		float32x4_t e_;
	};


#define MATAZURE_NEON_FLOAT_BINARY_OPERATOR(tag, op) \
inline neon_vector<float, 4> operator op(const neon_vector<float, 4> &lhs, const neon_vector<float, 4> &rhs){ \
	return neon_vector<float, 4>{ v##tag##q_f32(lhs.e_, rhs.e_) }; \
}

#define MATAZURE_NEON_FLOAT_ASSIGNMENT_OPERATOR(tag, op) \
inline neon_vector<float, 4> operator op (neon_vector<float, 4> &lhs, const neon_vector<float, 4> &rhs){ \
	lhs = neon_vector<float, 4> { v##tag##q_f32(lhs.e_, rhs.e_) }; \
	return lhs; \
}


MATAZURE_NEON_FLOAT_BINARY_OPERATOR(add, +)
MATAZURE_NEON_FLOAT_BINARY_OPERATOR(sub, -)
MATAZURE_NEON_FLOAT_BINARY_OPERATOR(mul, *)
//MATAZURE_NEON_FLOAT_BINARY_OPERATOR(div, /)

//MATAZURE_NEON_FLOAT_BINARY_OPERATOR(cmpgt, >)
//MATAZURE_NEON_FLOAT_BINARY_OPERATOR(cmplt, <)
//MATAZURE_NEON_FLOAT_BINARY_OPERATOR(cmpge, >=)
//MATAZURE_NEON_FLOAT_BINARY_OPERATOR(cmple, <=)
//MATAZURE_NEON_FLOAT_BINARY_OPERATOR(cmpeq, ==)
//MATAZURE_NEON_FLOAT_BINARY_OPERATOR(cmpneq, !=)

MATAZURE_NEON_FLOAT_ASSIGNMENT_OPERATOR(add, +=)
MATAZURE_NEON_FLOAT_ASSIGNMENT_OPERATOR(sub, -=)
MATAZURE_NEON_FLOAT_ASSIGNMENT_OPERATOR(mul, *=)
//MATAZURE_NEON_FLOAT_ASSIGNMENT_OPERATOR(div, /=)

} }

namespace matazure {

	using namespace simd;

	template <>
	struct zero<simd::neon_vector<float, 4>> {
		static simd::neon_vector<float, 4> value() {
			return simd::neon_vector<float, 4>{ vdupq_n_f32(0) };
		}
	};

}

