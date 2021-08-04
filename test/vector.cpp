#include <vector>
#include <string>
#include <assert.h>
#include <iostream>

#include "math/vector.hpp"
#include "math/cartesian.hpp"
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

int main() {
	using namespace std;

	static_assert(math::vector<glm::vec2>);
	static_assert(!math::vector<int>);

	using cv = math::cartesian_vector_by<pair<int, int>>;
	static_assert(std::same_as<int, math::element_type<cv, 0>>);
	static_assert(math::vector<cv>);

	glm::vec2 v{1.0F, 12.0F};
	auto p = math::to<std::pair<float, float>>(v);
	static_assert(is_same_v<decltype(p), pair<float, float>>);
	assert(math::element<0>(v) == math::element<0>(p) && math::element<1>(v) == math::element<1>(p));

	math::cartesian_vector_by<std::pair<float, float>> one_pair{ 1.0F, 1.0F };

	auto result{ one_pair };
	math::for_each_element(result, [](auto& r) {
		r += 1.0F;
	});
	assert(result.x() == 2.0F && result.y() == 2.0F);

	auto sum{ one_pair + v };
	assert(sum.x() == 2.0F && sum.y() == 13.0F);

	math::cartesian_vector_by<std::pair<float, float>> rotated{-1.0F, 1.0F};
	assert(math::dot(one_pair, rotated) == 0.0F);

	assert(
		math::length(math::cross<glm::vec3>(
			math::cartesian_vector_by<std::tuple<float, float, float>>{ 1.0F, 0.0F, 0.0F },
			glm::vec3{ 0.0F, 0.0F, -1.0F }
		)) == 1.0F
	);
}