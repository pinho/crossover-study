#include <fstream>
#include <sstream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <ccr/config/configuration.h>

void create_testfile1() {
    std::ofstream out("_config.yml");
    out << "id: CONFIG01\n";
    out << "crossover: uniform\n";
    out << "population: 100\n";
    out << "generations: 500\n";
    out << "crossover_rate: 0.8\n";
    out << "mutation_rate: 0.03\n";
    out.close();
}


TEST_SUITE("Config Module") {

    TEST_CASE("Configuration file with single values") {
        create_testfile1();
        Configuration conf("_config.yml");

        SUBCASE("Read: ID") {
            CHECK_EQ( conf.ID(), "CONFIG01" );
        }

        SUBCASE("Read: Crossover name") {
            CHECK_EQ( conf.crossover_name(), "uniform" );
        }

        SUBCASE("Read: Crossover rate") {
            CHECK_EQ( conf.crossover_rate(), 0.8 );
        }

        SUBCASE("Read: Mutation name") {
            CHECK_EQ( conf.mutation_rate(), 0.03 );
        }

        SUBCASE("Read: Length of Population") {
            CHECK_EQ( conf.popsize(), 100 );
        }

        SUBCASE("Read: Number of generations") {
            CHECK_EQ( conf.number_generations(), 500 );
        }
    }

}