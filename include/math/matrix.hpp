#pragma once

#include <array.hpp>
#include <integer.hpp>
#include <__values/permutations.hpp>
#include <__values/permutations_parity.hpp>

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

		constexpr bool
		operator == (const matrix& other) const {
			for (nuint r = 0; r < Height; ++r) {
				if ((*this)[r] != other[r]) return false;
			}

			return true;
		}

		constexpr matrix
		operator + (Type v) {
			matrix cpy{ *this };
			for (auto& v0 : cpy.m_storage) v0 += v;
			return cpy;
		}

		constexpr matrix
		operator * (Type s) const {
			matrix result{ *this };

			for (auto& r : result.m_storage) {
				r *= s;
			}

			return result;
		}

		template<nuint OtherHeight, nuint OtherWidth>
		requires(Width == OtherHeight)
		constexpr matrix<Type, Height, OtherWidth>
		operator * (math::matrix<Type, OtherHeight, OtherWidth> other) const {
			matrix<Type, Height, OtherWidth> result{};

			for (nuint h = 0; h < Height; ++h) {
				for (nuint w = 0; w < OtherWidth; ++w) {
					for (nuint i = 0; i < Width; ++i) {
						result[h][w] += (*this)[h][i] * other[i][w];
					}
				}
			}

			return result;
		}

		constexpr matrix<Type, Width, Height>
		transposed() const {
			matrix<Type, Width, Height> result;

			for (nuint r = 0; r < Height; ++r) {
				for (nuint c = 0; c < Width; ++c) {
					result[c][r] = (*this)[r][c];
				}
			}

			return result;
		}

		constexpr Type determinant() const requires is_square {
			using permutations = typename
				indices::from<0>::to<Width>::template
				pass_for_type<__values::permutations>;
			
			Type determinant{};

			[&]<typename... ValuesOfColumn, nuint... ValuesOfColumnIndices>
			(types<ValuesOfColumn...>, indices::of<ValuesOfColumnIndices...>) {
				([&]<nuint... ColumnIndices, nuint... RowIndices>
				(indices::of<ColumnIndices...>, indices::of<RowIndices...>) {
					Type sign(__values::permutations_parity::for_indices<ColumnIndices...> % 2);
					sign = sign * Type(2) - Type(1);
					sign *= Type(-1);

					determinant += ((*this)[RowIndices][ColumnIndices] * ...) * sign;
				}(ValuesOfColumn{}, indices::from<0>::to<Width>{}) , ...);
			}(permutations{}, indices::from<0>::to<permutations::size>{});

			return determinant;
		}

		// TODO simplify
		constexpr Type
		minor(nuint Row, nuint Column) const {
			matrix<Type, Height - 1, Width - 1> result;

			for (nuint r = 0, r1 = 0; r < Height;) {
				for (nuint c = 0, c1 = 0; c < Width;) {
					if (r != Row && c != Column) {
						result[r1][c1] = (*this)[r][c];
						++c1;
					}
					++c;
				}

				if (r != Row) ++r1;
				++r;
			}

			return result.determinant();
		}

		constexpr Type
		cofactor(nuint Row, nuint Column) const {
			return 
				minor(Row, Column) * -(Type((Row + Column) % 2) * Type(2) - Type(1))
			;
		}

		constexpr matrix
		cofactor() const {
			matrix result;

			for (nuint r = 0; r < Height; ++r) {
				for (nuint c = 0; c < Width; ++c) {
					result[r][c] = cofactor(r, c);
				}
			}

			return result;
		}

		constexpr matrix inversed() const requires is_square {
			return cofactor().transposed() * (Type(1) / determinant());
		}

	};

}