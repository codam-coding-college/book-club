#include "catch.hh"
#include "generator.hpp"
#include <random>
#include <iostream>

static void
clear_estimates_list(t_estimate *estimates[])
{
    if (estimates == NULL) {
        return ;
    }
    for (int idx = 0; estimates[idx] != NULL; idx++) {
        estimate_del(estimates[idx]);
    }
    free(estimates);
}

static void
clear_char_array(char **arr)
{
    if (arr == NULL)
        return ;
    for (int idx = 0; arr[idx]; idx++) {
        free(arr[idx]);
    }
    free(arr);
}

TEST_CASE("rejectNullInput", "[estimate_extremes][bad_inputs]") {
    CHECK(estimate_extremes(NULL) == NULL);
}

TEST_CASE("rejectEmptyList", "[estimate_extremes][bad_inputs]") {
    t_estimate  **empty_estimates_list;

    empty_estimates_list = (t_estimate **)malloc(sizeof(t_estimate *));
    REQUIRE(empty_estimates_list != NULL);
    empty_estimates_list[0] = NULL;

    CHECK(estimate_extremes(empty_estimates_list) == NULL);
    clear_estimates_list(empty_estimates_list);
}

TEST_CASE("rejectSingleEstimate", "[estimate_extremes][bad_inputs]") {
    t_estimate  **single_estimates_list;

    single_estimates_list = (t_estimate **)malloc(sizeof(t_estimate *) * 2);
    REQUIRE(single_estimates_list != NULL);
    single_estimates_list[0] = estimate_new("Richard", 5);
    REQUIRE(single_estimates_list[0] != NULL);
    single_estimates_list[1] = NULL;

    CHECK(estimate_extremes(single_estimates_list) == NULL);
    clear_estimates_list(single_estimates_list);
}

TEST_CASE("twoEstimates", "[estimate_extremes][boundary_inputs]") {
    t_estimate  **estimates_list;
    char        **developers;

    estimates_list = (t_estimate **)malloc(sizeof(t_estimate *) * 3);
    REQUIRE(estimates_list != NULL);
    estimates_list[0] = estimate_new("Richard", 5);
    REQUIRE(estimates_list[0] != NULL);
    estimates_list[1] = estimate_new("Dywel", 10);
    REQUIRE(estimates_list[1] != NULL);
    estimates_list[2] = NULL;

    CHECK((developers = estimate_extremes(estimates_list)) != NULL);
    CHECK(strcmp("Richard", developers[0]) == 0);
    CHECK(strcmp("Dywel", developers[1]) == 0);
    clear_estimates_list(estimates_list);
    clear_char_array(developers);
}

TEST_CASE("manyEstimates", "[estimate_extremes][boundary_inputs]") {
    t_estimate  **estimates_list;
    char        **developers;

    estimates_list = (t_estimate **)malloc(sizeof(t_estimate *) * 4);
    REQUIRE(estimates_list != NULL);
    estimates_list[0] = estimate_new("Richard", 5);
    REQUIRE(estimates_list[0] != NULL);
    estimates_list[1] = estimate_new("Dywel", 10);
    REQUIRE(estimates_list[1] != NULL);
    estimates_list[2] = estimate_new("Amber", 15);
    REQUIRE(estimates_list[2] != NULL);
    estimates_list[3] = NULL;

    CHECK((developers = estimate_extremes(estimates_list)) != NULL);
    CHECK(strcmp("Richard", developers[0]) == 0);
    CHECK(strcmp("Amber", developers[1]) == 0);
    clear_estimates_list(estimates_list);
    clear_char_array(developers);
}

TEST_CASE("developersWithSameEstimates", "[estimate_extremes][boundary_inputs]") {
    t_estimate  **estimates_list;
    char        **developers;

    estimates_list = (t_estimate **)malloc(sizeof(t_estimate *) * 6);
    REQUIRE(estimates_list != NULL);
    estimates_list[0] = estimate_new("Mauricio", 10);
    REQUIRE(estimates_list[0] != NULL);
    estimates_list[1] = estimate_new("Arie", 5);
    REQUIRE(estimates_list[1] != NULL);
    estimates_list[2] = estimate_new("Andy", 10);
    REQUIRE(estimates_list[2] != NULL);
    estimates_list[3] = estimate_new("Frank", 7);
    REQUIRE(estimates_list[3] != NULL);
    estimates_list[4] = estimate_new("Annibale", 5);
    REQUIRE(estimates_list[4] != NULL);
    estimates_list[5] = NULL;

    CHECK((developers = estimate_extremes(estimates_list)) != NULL);
    CHECK(strcmp("Arie", developers[0]) == 0);          // INTERESING -> This is actually wrong in the book
    CHECK(strcmp("Mauricio", developers[1]) == 0);
    clear_estimates_list(estimates_list);
    clear_char_array(developers);
}

TEST_CASE("allDevelopersWithTheSameEstimate", "[estimate_extremes][boundary_inputs]") {
    t_estimate  **estimates_list;
    char        **developers;

    estimates_list = (t_estimate **)malloc(sizeof(t_estimate *) * 6);
    REQUIRE(estimates_list != NULL);
    estimates_list[0] = estimate_new("Mauricio", 10);
    REQUIRE(estimates_list[0] != NULL);
    estimates_list[1] = estimate_new("Arie", 10);
    REQUIRE(estimates_list[1] != NULL);
    estimates_list[2] = estimate_new("Andy", 10);
    REQUIRE(estimates_list[2] != NULL);
    estimates_list[3] = estimate_new("Frank", 10);
    REQUIRE(estimates_list[3] != NULL);
    estimates_list[4] = estimate_new("Annibale", 10);
    REQUIRE(estimates_list[4] != NULL);
    estimates_list[5] = NULL;

    CHECK((developers = estimate_extremes(estimates_list)) != NULL);
    CHECK(developers[0] == NULL);
    clear_estimates_list(estimates_list);
    clear_char_array(developers);
}

TEST_CASE("inAnyOrder", "[estimate_extremes][property_tests]") {
    char    **developers;
    auto    estimates = GENERATE(take(100, random(2, 99)));

    REQUIRE(estimates != NULL);
    developers = estimate_extremes(estimates);
    REQUIRE(strcmp("MrLowEstimate", developers[0]) == 0);
    REQUIRE(strcmp("MsHighEstimate", developers[1]) == 0);
    clear_estimates_list(estimates);
    clear_char_array(developers);
}
