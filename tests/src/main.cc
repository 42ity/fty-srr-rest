
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include <filesystem>
#include "fty_srr_helpers.h"

//  -------------------------------------------------------------------------
//  All private classes tests.
//

typedef struct {
    const char *testname;           // test name, can be called from command line this way
    void (*test) (bool);            // function to run the test (or NULL for private tests)
} test_item_t;

static test_item_t
all_tests [] = {
    {NULL, NULL}          //  Sentinel
};

//  -------------------------------------------------------------------------
//  Run all tests.
//

static void
test_runall (bool verbose)
{
    printf ("Running fty-srr-rest selftests...\n");
    test_item_t *item;
    for (item = all_tests; item->testname; item++) {
        if (item->test)
            item->test (verbose);
    }
    printf ("Tests passed OK\n");
}

TEST_CASE("All the stuff of before")
{
    std::cout << "Current path is " << std::filesystem::current_path() << std::endl;
    test_runall(true);
}
