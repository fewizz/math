#pragma once

#include <array.hpp>
#include <integer.hpp>
#include <number.hpp>

namespace math {

	template<typename Type, nuint Size>
	struct vector : array<Type, Size> {

		using array<Type, Size>::array;

		constexpr bool
		operator == (const vector& other) const {
			for(nuint i = 0; i < Size; ++i) {
				if((*this)[i] != other[i]) return false;
			}
			return true;
		}

		constexpr bool
		operator == (const Type& value) const {
			for(nuint i = 0; i < Size; ++i) {
				if((*this)[i] != value) return false;
			}
			return true;
		}

		constexpr auto operator + (Type v) const {
			vector cpy { *this };
			for(auto& v0 : cpy) v0 += v;
			return cpy;
		}

		constexpr auto operator + (vector v) const {
			vector cpy { *this };
			for(nuint i = 0; i < Size; ++i) {
				cpy[i] += v[i];
			}
			return cpy;
		}

		constexpr auto operator - (Type v) const {
			vector cpy { *this };
			for(auto& v0 : cpy) v0 -= v;
			return cpy;
		}

		constexpr auto operator - (vector v) const {
			vector cpy { *this };
			for(nuint i = 0; i < Size; ++i) {
				cpy[i] -= v[i];
			}
			return cpy;
		}

		constexpr auto operator * (Type v) const {
			vector cpy { *this };
			for(auto& v0 : cpy) v0 *= v;
			return cpy;
		}

		constexpr auto operator * (vector v) const {
			vector cpy { *this };
			for(nuint i = 0; i < Size; ++i) {
				cpy[i] *= v[i];
			}
			return cpy;
		}

		constexpr vector operator / (Type v) const {
			vector cpy { *this };
			for(auto& v0 : cpy) v0 /= v;
			return cpy;
		}

		constexpr vector& operator *= (Type v) {
			for(auto& v0 : *this) v0 *= v;
			return *this;
		}

		constexpr vector clamp(vector min, vector max) {
			vector result { *this };
			for(nuint i = 0; i < Size; ++i) {
				result[i] = number { result[i] }.clamp(min[i], max[i]);
			}
			return result;
		}

		template<typename To>
		constexpr vector<To, Size> cast() {
			vector<To, Size> result;
			for(nuint i = 0; i < Size; ++i) {
				result = (To) (*this)[i];
			}
			return result;
		}

	};

	template<typename... Types>
	requires(sizeof...(Types) == 1 || types_are_same<Types...>)
	vector(Types&&...)
		-> vector<
			remove_reference<first_type<Types...>>,
			sizeof...(Types)
		>;

} // math

#include <std/tuple_size.hpp>

template<typename Type, nuint Size>
struct std::tuple_size<math::vector<Type, Size>> {
	static constexpr nuint value = Size;
};

#include <std/tuple_element.hpp>

template<nuint Index, typename Type, nuint Size>
struct std::tuple_element<Index, math::vector<Type, Size>> {
	using type = Type;
};