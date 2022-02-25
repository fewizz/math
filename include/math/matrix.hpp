#pragma once

#include <core/array.hpp>
#include <core/integer.hpp>
#include <core/meta/values/first.hpp>
#include <core/meta/values/permutations.hpp>
#include <core/range/transform.hpp>
#include <core/meta/values/permutations_parity.hpp>

#include "vector.hpp"

namespace math {

	template<typename Type, nuint Height, nuint Width>
	struct matrix {
		static constexpr bool is_square = Width == Height;

		math::vector<Type, Width> m_storage[Height];

		constexpr auto& operator [] (nuint index) {
			return m_storage[index];
		}

		constexpr auto& operator [] (nuint index) const {
			return m_storage[index];
		}

		constexpr matrix operator + (Type v) {
			matrix cpy{ *this };
			for(auto& v0 : cpy.m_storage) v0 += v;
			return cpy;
		}

		template<nuint OtherWidth>
		matrix<Type, OtherWidth, Height>
		operator * (math::matrix<Type, OtherWidth, Width> other) const {
			matrix<Type, Height, OtherWidth> result{};

			for(nuint h = 0; h < Height; ++h) {
				for(nuint w = 0; w < OtherWidth; ++w) {
					for(nuint i = 0; i < Width; ++i) {
						result[h][w] += this->operator [](h)[i] * other[i][w];
					}
				}
			}

			return result;
		}

		constexpr matrix<Type, Height, Width> transposed() const {
			matrix<Type, Height, Width> result;

			for(nuint r = 0; r < Height; ++r) {
				for(nuint c = 0; c < Width; ++c) {
					result[r][c] = this-> operator [] (c)[r];
				}
			}

			return result;
		}

		constexpr Type determinant() const requires is_square {
			using permutations = typename
				indices::from<0>::to<Width>::template
				pass_for_type<values::permutations>;
			
			Type determinant{};

			[&]<
				typename... ValuesOfColumn,
				nuint... ValuesOfColumnIndices
			>(
				types::of<ValuesOfColumn...>,
				indices::of<ValuesOfColumnIndices...>
			) {

				([&]<
					nuint... ColumnIndices,
					nuint... RowIndices
				>(
					indices::of<ColumnIndices...>,
					indices::of<RowIndices...>
				) {
					
					Type sign(values::permutations_parity::for_indices<ColumnIndices...> % 2);
					sign = sign * Type(2) - Type(1);
					sign *= Type(-1);

					determinant += ((*this)[ColumnIndices][RowIndices] * ...) * sign;

				}(ValuesOfColumn{}, indices::from<0>::to<Width>{}) , ...);

			}(permutations{}, indices::from<0>::to<permutations::size>{});

			return determinant;
		}

		constexpr matrix<Type, Width - 1, Height - 1> minor() const {

		}

		matrix inversed() const requires is_square {

		}

	};

}