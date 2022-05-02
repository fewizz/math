#pragma once

#include <core/array.hpp>
#include <core/integer.hpp>

namespace math {

	template<typename Type, nuint Size>
	struct vector : array<Type, Size> {

		constexpr bool
		operator == (const vector& other) const {
			for(nuint i = 0; i < Size; ++i) {
				if((*this)[i] != other[i]) return false;
			}
			return true;
		}

		constexpr auto operator + (Type v) const {
			vector cpy{ *this };
			for(auto& v0 : cpy.m_storage) v0 += v;
			return cpy;
		}

		constexpr auto operator * (Type v) const {
			vector cpy{ *this };
			for(auto& v0 : cpy.m_storage) v0 *= v;
			return cpy;
		}

		constexpr vector& operator *= (Type v) {
			for(auto& v0 : *this) v0 *= v;
			return *this;
		}

	};

} // math

#include <core/std/tuple_size.hpp>

template<typename Type, nuint Size>
struct std::tuple_size<math::vector<Type, Size>> {
	static constexpr nuint value = Size;
};

#include <core/std/tuple_element.hpp>

template<nuint Index, typename Type, nuint Size>
struct std::tuple_element<Index, math::vector<Type, Size>> {
	using type = Type;
};