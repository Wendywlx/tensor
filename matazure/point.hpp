﻿#pragma once

#include <matazure/type_traits.hpp>

namespace matazure {

/**
* @brief a point class, like as std::array.
*
* uses point<int_t, rank> to represent an array index, a tensor shape, stride etc.
* we clould look point as fixed length vector or array
*
* @tparam _ValueType the point element value type, must be pod
* @tparam _Rank the rank of point, it equals to point length/size
*/
template <typename _ValueType, int_t _Rank>
class point {
public:
	/// point length
	static const int_t				rank = _Rank;
	typedef _ValueType				value_type;
	typedef value_type &			reference;
	typedef const value_type &		const_reference;
	typedef linear_index			index_type;
	typedef local_tag				memory_type;

	/**
	* @brief accesses element by index
	* @param i element index
	* @return element const referece
	*/
	MATAZURE_GENERAL constexpr const_reference operator[](int_t i) const {
		return elements_[i];
	}

	/**
	* @brief accesses element by index
	* @param i element index
	* @return element referece
	*/
	MATAZURE_GENERAL reference operator[](int_t i) {
		return elements_[i];
	}

	/// return the length of point
	MATAZURE_GENERAL constexpr int_t size() const {
		return rank;
	}

	/// return a zero point
	MATAZURE_GENERAL static constexpr point zeros() {
		return { 0 };
	}

	/// return a point whose elements are v
	MATAZURE_GENERAL static point all(value_type v) {
		point re{};
		for (int_t i = 0;i < re.size(); ++i) {
			re[i] = v;
		}
		return re;
	}

	MATAZURE_GENERAL constexpr value_type * data() {
		return elements_;
	}

	MATAZURE_GENERAL constexpr const value_type * data() const {
		return elements_;
	}

public:
	value_type elements_[rank];
};

static_assert(std::is_pod<point<byte, 1>>::value, "point should be pod");

//binary opertor
#define MATAZURE_POINT_BINARY_OPERATOR(op) \
template <typename _T, int_t _Rank> \
inline MATAZURE_GENERAL auto operator op(const point<_T, _Rank> &lhs, const point<_T, _Rank> &rhs)->point<decltype(lhs[0] op rhs[0]), _Rank> { \
	point<decltype(lhs[0] op rhs[0]), _Rank> re; \
	for (int_t i = 0; i < _Rank; ++i) { \
		re[i] = lhs[i] op rhs[i]; \
	} \
	return re; \
} \
\
template <typename _T, int_t _Rank>  \
inline MATAZURE_GENERAL auto operator op(const point<_T, _Rank> &container, typename point<_T, _Rank>::value_type value)->point<decltype(container[0] op value), _Rank> { \
	point<decltype(container[0] op value), _Rank> re; \
	for (int_t i = 0; i < _Rank; ++i) { \
		re[i] = container[i] op value; \
	} \
\
return re; \
}\
\
template <typename _T, int_t _Rank>  \
inline MATAZURE_GENERAL auto operator op(typename point<_T, _Rank>::value_type value, const point<_T, _Rank> &container)->point<decltype(value op container[0]), _Rank> { \
	point<decltype(value op container[0]), _Rank> re; \
	for (int_t i = 0; i < _Rank; ++i) { \
		re[i] = container[i] op value; \
	} \
\
return re; \
}

// assignment operators
#define MATAZURE_POINT_ASSIGNMENT_OPERATOR(op) \
template <typename _T, int_t _Rank> \
inline MATAZURE_GENERAL auto operator op(point<_T, _Rank> &lhs, const point<_T, _Rank> &rhs)->point<_T, _Rank> { \
	for (int_t i = 0; i < _Rank; ++i) { \
		lhs[i] op rhs[i]; \
	} \
	return lhs; \
}\
\
template <typename _T, int_t _Rank>  \
inline MATAZURE_GENERAL auto operator op(point<_T, _Rank> &container, _T value)->point<_T, _Rank> { \
	for (int_t i = 0; i < _Rank; ++i) { \
		container[i] op value; \
	} \
\
return container; \
}

//Arithmetic
MATAZURE_POINT_BINARY_OPERATOR(+)
MATAZURE_POINT_BINARY_OPERATOR(-)
MATAZURE_POINT_BINARY_OPERATOR(*)
MATAZURE_POINT_BINARY_OPERATOR(/)
MATAZURE_POINT_BINARY_OPERATOR(%)
MATAZURE_POINT_ASSIGNMENT_OPERATOR(+=)
MATAZURE_POINT_ASSIGNMENT_OPERATOR(-=)
MATAZURE_POINT_ASSIGNMENT_OPERATOR(*=)
MATAZURE_POINT_ASSIGNMENT_OPERATOR(/=)
MATAZURE_POINT_ASSIGNMENT_OPERATOR(%=)
//Bit
MATAZURE_POINT_BINARY_OPERATOR(<<)
MATAZURE_POINT_BINARY_OPERATOR(>>)
MATAZURE_POINT_BINARY_OPERATOR(|)
MATAZURE_POINT_BINARY_OPERATOR(&)
MATAZURE_POINT_BINARY_OPERATOR(^)
MATAZURE_POINT_ASSIGNMENT_OPERATOR(<<=)
MATAZURE_POINT_ASSIGNMENT_OPERATOR(>>=)
MATAZURE_POINT_ASSIGNMENT_OPERATOR(|=)
MATAZURE_POINT_ASSIGNMENT_OPERATOR(&=)
MATAZURE_POINT_ASSIGNMENT_OPERATOR(^=)
//Logic
MATAZURE_POINT_BINARY_OPERATOR(||)
MATAZURE_POINT_BINARY_OPERATOR(&&)
//Compapre
MATAZURE_POINT_BINARY_OPERATOR(>)
MATAZURE_POINT_BINARY_OPERATOR(<)
MATAZURE_POINT_BINARY_OPERATOR(>=)
MATAZURE_POINT_BINARY_OPERATOR(<=)
MATAZURE_POINT_BINARY_OPERATOR(==)
MATAZURE_POINT_BINARY_OPERATOR(!=)

template <typename _T, int_t _Rank>
MATAZURE_GENERAL point<_T, _Rank> operator+(const point<_T, _Rank> &p) {
	return p;
}

template <typename _T, int_t _Rank>
MATAZURE_GENERAL point<_T, _Rank> operator-(const point<_T, _Rank> &p) {
	point<_T, _Rank> temp;
	for (int_t i = 0; i < _Rank; ++i) {
		temp[i] = -p[i];
	}

	return temp;
}

template <typename _T, int_t _Rank>
MATAZURE_GENERAL point<_T, _Rank>& operator++(point<_T, _Rank> &p) {
	for (int_t i = 0; i < _Rank; ++i) {
		++p[i];
	}

	return p;
}

template <typename _T, int_t _Rank>
MATAZURE_GENERAL point<_T, _Rank>& operator--(point<_T, _Rank> &p) {
	for (int_t i = 0; i < _Rank; ++i) {
		--p[i];
	}

	return p;
}

template <typename _ValueTypeDst, typename _ValueTypeSrc, int_t _Rank>
MATAZURE_GENERAL point<_ValueTypeDst, _Rank> point_cast(const point<_ValueTypeSrc, _Rank> &p) {
	point<_ValueTypeDst, _Rank> re;
	for (int_t i = 0; i < _Rank; ++i) {
		re[i] = static_cast<_ValueTypeDst>(p[i]);
	}

	return re;
}

/// get point element like as std::get
template<int_t _Idx, class _Ty, int_t _Rank>
MATAZURE_GENERAL constexpr _Ty& get(point<_Ty, _Rank>& pt) {
	// return element at _Idx in point pt
	static_assert(_Idx < _Rank, "point index out of bounds");
	return (pt.elements_[_Idx]);
}

template<int_t _Idx, class _Ty, int_t _Rank>
MATAZURE_GENERAL constexpr const _Ty& get(const point<_Ty, _Rank>& pt){
	// return element at _Idx in point pt
	static_assert(_Idx < _Rank, "point index out of bounds");
	return (pt.elements_[_Idx]);
}

template<int_t _Idx, class _Ty, int_t _Rank>
MATAZURE_GENERAL constexpr _Ty&& get(point<_Ty, _Rank>&& pt) {
	// return element at _Idx in point pt
	static_assert(_Idx < _Rank, "point index out of bounds");
	return (move(pt.elements_[_Idx]));
}

template <int_t _Rank> using pointb = point<byte, _Rank>;
template <int_t _Rank> using points = point<short, _Rank>;
template <int_t _Rank> using pointi = point<int_t, _Rank>;
template <int_t _Rank> using pointf = point<float, _Rank>;
template <int_t _Rank> using pointd = point<float, _Rank>;

/// if two points are equal elementwise, return true, others false.
template <typename _Ty, int_t _Rank>
inline MATAZURE_GENERAL bool equal(const point<_Ty, _Rank> &lhs, const point<_Ty, _Rank> &rhs) {
	for (int_t i = 0; i < lhs.size(); ++i) {
		if ((lhs[i] != rhs[i])) return false;
	}
	return true;
}

/// special zero for point
template <typename _T, int_t _Rank>
struct zero<point<_T, _Rank>>{
	MATAZURE_GENERAL static constexpr point<_T, _Rank> value(){
		return {0};
	};
};

/// return cumulative prod of point elements
template <int_t _Rank>
inline MATAZURE_GENERAL pointi<_Rank> cumulative_prod(pointi<_Rank> ex) {
	pointi<_Rank>  stride;
	stride[0] = ex[0];
	for (int_t i = 1; i < _Rank; ++i) {
		stride[i] = ex[i] * stride[i - 1];
	}
	return stride;
}

/**
* @brief detect whether a point is inside_range of a rect (left close, right open)
* @param idx point position
* @param left_top the lef top index of the rect
* @param right_bottom the right bottom index of the rect
* @return returns true if the point is inside_range of the rect
*/
template <typename _ValueType, int_t _Rank>
inline MATAZURE_GENERAL bool inside_range(point<_ValueType, _Rank> idx, point<_ValueType, _Rank> left_top, point<_ValueType, _Rank> right_bottom) {
	for (int_t i = 0; i < _Rank; ++i) {
		if ((idx[i] < left_top[i] || idx[i] >= right_bottom[i]))
			return false;
	}

	return true;
}

inline MATAZURE_GENERAL bool inside_range(pointi<1> idx, pointi<1> left_top, pointi<1> right_bottom) {
	if ((idx[0] >= left_top[0] && idx[0] < right_bottom[0])){
		return true;
	} else {
		return false;
	}
}

inline MATAZURE_GENERAL bool inside_range(pointi<2> idx, pointi<2> left_top, pointi<2> right_bottom) {
	if (idx[0] >= left_top[0] && idx[0] < right_bottom[0] &&
		idx[1] >= left_top[1] && idx[1] < right_bottom[1])
		return true;
	else
		return false;
}

inline MATAZURE_GENERAL bool inside_range(pointi<3> idx, pointi<3> left_top, pointi<3> right_bottom) {
	if (idx[0] >= left_top[0] && idx[0] < right_bottom[0] &&
		idx[1] >= left_top[1] && idx[1] < right_bottom[1] &&
		idx[2] >= left_top[2] && idx[2] < right_bottom[2])
		return true;
	else
		return false;
}

inline MATAZURE_GENERAL bool inside_range(pointi<4> idx, pointi<4> left_top, pointi<4> right_bottom) {
	if (idx[0] >= left_top[0] && idx[0] < right_bottom[0] &&
		idx[1] >= left_top[1] && idx[1] < right_bottom[1] &&
		idx[2] >= left_top[2] && idx[2] < right_bottom[2] &&
		idx[3] >= left_top[3] && idx[3] < right_bottom[3]){
		return true;
	} else{
		return false;
	}
}

/**
* @brief detect whether a point is outside_range of a rect (left close, right open)
* @param idx point position
* @param left_top the lef top index of the rect
* @param right_bottom the right bottom index of the rect
* @return true if the point is outside_range of the rect
*/
template <typename _ValueType, int_t _Rank>
inline MATAZURE_GENERAL bool outside_range(point<_ValueType, _Rank> idx, point<_ValueType, _Rank> left_top, point<_ValueType, _Rank> right_bottom) {
	for (int_t i = 0; i < _Rank; ++i) {
		if ((idx[i] < left_top[i] || idx[i] >= right_bottom[i]))
			return true;
	}

	return false;
}

inline MATAZURE_GENERAL bool outside_range(pointi<1> idx, pointi<1> left_top, pointi<1> right_bottom) {
	if ((idx[0] >= left_top[0] && idx[0] < right_bottom[0])){
		return true;
	} else {
		return false;
	}
}

inline MATAZURE_GENERAL bool outside_range(pointi<2> idx, pointi<2> left_top, pointi<2> right_bottom) {
	if (idx[0] >= left_top[0] && idx[0] < right_bottom[0] &&
		idx[1] >= left_top[1] && idx[1] < right_bottom[1])
		return true;
	else
		return false;
}

inline MATAZURE_GENERAL bool outside_range(pointi<3> idx, pointi<3> left_top, pointi<3> right_bottom) {
	if (idx[0] >= left_top[0] && idx[0] < right_bottom[0] &&
		idx[1] >= left_top[1] && idx[1] < right_bottom[1] &&
		idx[2] >= left_top[2] && idx[2] < right_bottom[2])
		return true;
	else
		return false;
}

inline MATAZURE_GENERAL bool outside_range(pointi<4> idx, pointi<4> left_top, pointi<4> right_bottom) {
	if (idx[0] >= left_top[0] && idx[0] < right_bottom[0] &&
		idx[1] >= left_top[1] && idx[1] < right_bottom[1] &&
		idx[2] >= left_top[2] && idx[2] < right_bottom[2] &&
		idx[3] >= left_top[3] && idx[3] < right_bottom[3]){
		return true;
	} else{
		return false;
	}
}

//pointi<3>
template <int_t _SliceDimIdx>
inline pointi<2> slice_point(pointi<3> pt);

template < >
inline pointi<2> slice_point<0>(pointi<3> pt) {
	return pointi<2>{get<1>(pt), get<2>(pt)};
}

template < >
inline pointi<2> slice_point<1>(pointi<3> pt) {
	return pointi<2>{get<0>(pt), get<2>(pt)};
}

template < >
inline pointi<2> slice_point<2>(pointi<3> pt) {
	return pointi<2>{get<0>(pt), get<1>(pt)};
}

template <int_t _CatDimIdx>
inline pointi<3> cat_point(pointi<2> pt, int_t cat_i);

template <>
inline pointi<3> cat_point<0>(pointi<2> pt, int_t cat_i) {
	return pointi<3>{cat_i, get<0>(pt), get<1>(pt)};
}

template <>
inline pointi<3> cat_point<1>(pointi<2> pt, int_t cat_i) {
	return pointi<3>{get<0>(pt), cat_i, get<1>(pt)};
}

template <>
inline pointi<3> cat_point<2>(pointi<2> pt, int_t cat_i) {
	return pointi<3>{get<0>(pt), get<1>(pt), cat_i};
}

/**
* @brief a wrapper for tuple to cast with point each other
*
* tuple<byte, byte, byte> and point<int, 3> can represent a rgb pixel, but they could not cast each other
* point_viewer make it work
*
* @tparam _Typle  the tuple type, such as tuple<int, int, int>
* @tparap the size of tuple elements
*/
template <typename _Tuple, int_t rank = tuple_size<_Tuple>::value>
class point_viewer;

/// special point_viewer for tuple<_T, 3>
template <typename _Tuple>
class point_viewer<_Tuple, 3> : public _Tuple{
public:
	static_assert(tuple_size<_Tuple>::value == 3, "");
	const static int_t rank = 3;
	typedef decay_t<typename tuple_element<0, _Tuple>::type> value_type;
	typedef point<value_type, rank> point_type;

	point_viewer(const _Tuple &tp): _Tuple(tp){}

	point_viewer &operator=(const point_type &tp) {
		get<0>(*static_cast<_Tuple *>(this)) = tp[0];
		get<1>(*static_cast<_Tuple *>(this)) = tp[1];
		get<2>(*static_cast<_Tuple *>(this)) = tp[2];

		return *this;
	}

	operator point_type() const {
		point_type re;
		re[0] = get<0>(*static_cast<_Tuple *>(this));
		re[1] = get<1>(*static_cast<_Tuple *>(this));
		re[2] = get<2>(*static_cast<_Tuple *>(this));
	}
};

}
