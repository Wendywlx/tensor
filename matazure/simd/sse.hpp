#pragma once

#include <matazure/config.hpp>
#include <matazure/meta.hpp>

#include <emmintrin.h>

namespace matazure { inline namespace simd {

	template <typename _ValueType, int_t Rank>
	class sse_vector;

	template <>
	class sse_vector<float, 4> {
	public:
		/// point length
		static const int_t				rank = 4;
		typedef float					value_type;
		typedef value_type &			reference;
		typedef linear_index			index_type;
		typedef local_tag				memory_type;

	#ifdef __GNUC__

		/**
		* @brief accesses element by index
		* @param i element index
		* @return element const referece
		*/
		MATAZURE_GENERAL const float & operator[](int_t i) const {
			return elements_[i];
		}

		/**
		* @brief accesses element by index
		* @param i element index
		* @return element referece
		*/
		MATAZURE_GENERAL float operator[](int_t i) {
			return elements_[i];
		}

	#endif

		/// return the length of point
		MATAZURE_GENERAL constexpr int_t size() const {
			return rank;
		}

		MATAZURE_GENERAL  const value_type * data() const {
			return reinterpret_cast<const value_type *>(&elements_);
		}

		MATAZURE_GENERAL  value_type * data() {
			return reinterpret_cast<value_type *>(&elements_);
		}

	public:

		__m128 elements_;
	};

	#define MATAZURE_NEON_FLOAT_BINARY_OPERATOR(tag, op) \
	inline sse_vector<float, 4> operator op(const sse_vector<float, 4> &lhs, const sse_vector<float, 4> &rhs){ \
		return sse_vector<float, 4>{  _mm_##tag##_ps(lhs.elements_, rhs.elements_) }; \
	}

	#define MATAZURE_NEON_FLOAT_ASSIGNMENT_OPERATOR(tag, op) \
	inline sse_vector<float, 4> operator op (sse_vector<float, 4> &lhs, const sse_vector<float, 4> &rhs){ \
		lhs = sse_vector<float, 4> {  _mm_##tag##_ps(lhs.elements_, rhs.elements_) }; \
		return lhs; \
	}

	MATAZURE_NEON_FLOAT_BINARY_OPERATOR(add, +)
	MATAZURE_NEON_FLOAT_BINARY_OPERATOR(sub, -)
	MATAZURE_NEON_FLOAT_BINARY_OPERATOR(mul, *)
	MATAZURE_NEON_FLOAT_BINARY_OPERATOR(div, /)

	MATAZURE_NEON_FLOAT_BINARY_OPERATOR(cmpgt, >)
	MATAZURE_NEON_FLOAT_BINARY_OPERATOR(cmplt, <)
	MATAZURE_NEON_FLOAT_BINARY_OPERATOR(cmpge, >=)
	MATAZURE_NEON_FLOAT_BINARY_OPERATOR(cmple, <=)
	MATAZURE_NEON_FLOAT_BINARY_OPERATOR(cmpeq, ==)
	MATAZURE_NEON_FLOAT_BINARY_OPERATOR(cmpneq, !=)

} }

namespace matazure {

	using namespace simd;

	template <>
	struct zero<simd::sse_vector<float, 4>> {
		static simd::sse_vector<float, 4> value() {
			return simd::sse_vector<float, 4>{ _mm_setzero_ps() };
		}
	};

}

