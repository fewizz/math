#pragma once

#include <core/meta/type/is_base.hpp>

namespace math::geometry {

	struct vector_marker{};

	template<typename Type>
	concept vector = type::is_base<vector_marker>::for_type<Type>;

}