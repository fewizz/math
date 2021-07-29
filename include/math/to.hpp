#pragma once

#include "vec.hpp"

namespace uni {

namespace internal {
	template<typename To, typename... Args>
	To to(auto from, Args... args) {
		if constexpr( sizeof...(Args) == uni::size<To>) {
			return { args... };
		}
		else {
			return to<To>(from, args..., get<sizeof...(Args)>(from));
		}
	}
}

template<uni::any_vec To>
To to(uni::vec<uni::size<To>, uni::get_type_decayed<To, 0>> auto from) {
	return internal::to<To>(from);
}

}