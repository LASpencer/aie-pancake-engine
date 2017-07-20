#include "stdafx_test.h"
#include "catch.hpp"
#include "Component.h"
#include "SceneObject.h"
#include "Sprite.h"
#include "Entity.h"

static const float default_tolerance = 0.00001f;

bool compare(float a, float b, float tolerance = default_tolerance) {
	if (abs(a - b) > tolerance) {
		return false;
	}
	return true;
}

bool compare(glm::mat3 a, glm::mat3 b, float tolerance = default_tolerance) {
	// compare each element in a and b
	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			if (!compare(a[i][j], b[i][j], tolerance)) {
				return false;
			}
		}
	}
	return true;
}


TEST_CASE("Scene Object", "[scene object][component][glm]") {
	SceneObjectPtr obj = SceneObjectPtr(new SceneObject());
	REQUIRE(compare(obj->getLocalTransform(), glm::mat3(1)));
	REQUIRE(compare(obj->getGlobalTransform(), glm::mat3(1)));
	SECTION("Set and Apply transforms") {
		glm::mat3 matA = { 5,0,0,0,3,0,0,0,1 };
		glm::mat3 matB = { 1,0,0,0,1,0,6,2,1 };
		SECTION("Set transform") {
			obj->setLocalTransform(matA);
			REQUIRE(compare(obj->getLocalTransform(), matA));
			REQUIRE(compare(obj->getGlobalTransform(), matA));
		}
		SECTION("Apply transform") {
			obj->applyTransform(matA);
			REQUIRE(compare(obj->getLocalTransform(), matA));
			REQUIRE(compare(obj->getGlobalTransform(), matA));
			SECTION("Post apply") {
				glm::mat3 result = { 5,0,0,0,3,0,30,6,1 };
				obj->applyTransform(matB);
				REQUIRE(compare(obj->getLocalTransform(), result));
				REQUIRE(compare(obj->getGlobalTransform(), result));
			}
			SECTION("Pre apply") {
				glm::mat3 result = { 5,0,0,0,3,0,6,2,1 };
				obj->applyTransform(matB, false);
				REQUIRE(compare(obj->getLocalTransform(), result));
				REQUIRE(compare(obj->getGlobalTransform(), result));
			}
		}
	}
}