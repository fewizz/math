#pragma once

#include <__type/is_base.hpp>

namespace math::geometry {

	struct vector_marker{};

	template<typename Type>
	concept vector = base_of<Type, vector_marker>;

}