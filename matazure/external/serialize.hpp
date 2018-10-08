#pragma once

#if __has_include(<cereal/cereal.hpp>)

#include <cereal/cereal.hpp>
#include <matazure/point.hpp>

namespace cereal {
	//! Saving for matazure::point primitive types
	//! using binary serialization, if supported
	template <class Archive, class T, matazure::int_t N> inline
		typename std::enable_if<traits::is_output_serializable<BinaryData<T>, Archive>::value
		&& std::is_arithmetic<T>::value, void>::type
		CEREAL_SAVE_FUNCTION_NAME(Archive & ar, matazure::point<T, N> const & point) {
		ar(binary_data(point.data(), sizeof(point)));
	}

	//! Loading for matazure::point primitive types
	//! using binary serialization, if supported
	template <class Archive, class T, matazure::int_t N> inline
		typename std::enable_if<traits::is_input_serializable<BinaryData<T>, Archive>::value
		&& std::is_arithmetic<T>::value, void>::type
		CEREAL_LOAD_FUNCTION_NAME(Archive & ar, matazure::point<T, N> & point) {
		ar(binary_data(point.data(), sizeof(point)));
	}

	//! Saving for matazure::point all other types
	template <class Archive, class T, matazure::int_t N> inline
		typename std::enable_if<!traits::is_output_serializable<BinaryData<T>, Archive>::value
		|| !std::is_arithmetic<T>::value, void>::type
		CEREAL_SAVE_FUNCTION_NAME(Archive & ar, matazure::point<T, N> const & point) {
		matazure::for_each(point, [&ar](auto &e) {
			ar(e);
		});
	}

	//! Loading for matazure::point all other types
	template <class Archive, class T, matazure::int_t N> inline
		typename std::enable_if<!traits::is_input_serializable<BinaryData<T>, Archive>::value
		|| !std::is_arithmetic<T>::value, void>::type
		CEREAL_LOAD_FUNCTION_NAME(Archive & ar, matazure::point<T, N> & point) {
		matazure::for_each(point, [&ar](auto &e) {
			ar(e);
		});
	}
} // namespace cereal

#endif
