#include "doctest.h"
#include <ga/crossover_fabric.h>

TEST_SUITE("Crossover Fabric") {

	TEST_CASE("Create Uniform Crossover") {
		auto x = CrossoverFabric::create_uniform();
		CHECK_EQ(x->className(), "eoUBitXover");
	}

	TEST_CASE("Create Uniform Crossover with crossID") {
		auto x = CrossoverFabric::create(0);
		CHECK_EQ(x->className(), "eoUBitXover");
	}

	TEST_CASE("Create One Point Crossover") {
		auto x = CrossoverFabric::create_cutpoints(1);
		CHECK_EQ(x->className(), "eo1PtBitXover");
	}

	TEST_CASE("Create One Point Crossover with crossID") {
		auto x = CrossoverFabric::create(1);
		CHECK_EQ(x->className(), "eo1PtBitXover");
	}

	TEST_CASE("Create N Points Crossover") {
		auto x = CrossoverFabric::create_cutpoints(3);
		CHECK_EQ(x->className(), "eoNPtsBitXover");
	}

	TEST_CASE("Create N Points Crossover with crossID") {
		auto x = CrossoverFabric::create(4);
		CHECK_EQ(x->className(), "eoNPtsBitXover");
	}

}
