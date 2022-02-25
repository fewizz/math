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

		constexpr auto operator + (Type v) {
			vector cpy{ *this };
			for(auto& v0 : cpy.m_storage) v0 += v;
			return cpy;
		}

	};

}