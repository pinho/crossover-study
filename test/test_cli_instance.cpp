#include "doctest.h"
#include <cli/options.h>
#include <cli/parse.h>

TEST_SUITE("cl_arguments struct") {

    cl_arguments cli_default;
    cl_arguments cli1 = cl_arguments{(char *)"test.txt", 100, 100, 0, 0.5, 0.05};

    TEST_CASE("ID of default params") {
        CHECK_EQ( identify(cli_default), "UNIFORMP100G50CR080MR005" );
    }

    TEST_CASE("ID of custom params") {
        CHECK_EQ( identify(cli1), "UNIFORMP100G100CR050MR005" );
    }

    TEST_CASE("ID of params with 16 points") {
        cli1.crossover_id = 16;
        CHECK_EQ( identify(cli1), "16POINTSP100G100CR050MR005" );
    }


    TEST_CASE("ID of params with 32 points") {
        cli1.crossover_id = 32;
        CHECK_EQ( identify(cli1), "32POINTSP100G100CR050MR005" );
    }

}