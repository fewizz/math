#pragma once

#include <core/integer.hpp>

namespace math {

	template<typename Type, nuint Size>
	struct vector {
		Type m_storage[Size];

		constexpr auto& operator [] (nuint index) {
			return m_storage[index];
		}

		constexpr auto& operator [] (nuint index) const {
			return m_storage[index];
		}

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
			for(auto& v0 : m_storage) v0 *= v;
			return *this;
		}

	};

}