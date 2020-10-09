#include <catch/catch.hpp>

#include <vld8/exceptions.hpp>
#include <vld8/validator.hpp>

TEST_CASE("Integer type check")
{
    vili::node integer_validator = vili::object { { "type", "integer" } };
    SECTION("Test integer type")
    {
        vili::node zero = 0;
        REQUIRE_NOTHROW(vili::validator::validate_integer("", integer_validator, zero));
    }
    SECTION("Test string type")
    {
        vili::node hello_world = "Hello, world!";
        REQUIRE_THROWS_AS(
            vili::validator::validate_integer("", integer_validator, hello_world),
            vili::validator::exceptions::value_type_mismatch);
    }
    SECTION("Test boolean type")
    {
        vili::node bool_true = true;
        REQUIRE_THROWS_AS(
            vili::validator::validate_integer("", integer_validator, bool_true),
            vili::validator::exceptions::value_type_mismatch);
    }
    SECTION("Test number type")
    {
        vili::node pi = 3.14;
        REQUIRE_THROWS_AS(vili::validator::validate_integer("", integer_validator, pi),
            vili::validator::exceptions::value_type_mismatch);
    }
    SECTION("Test array type")
    {
        vili::node table_of_6 = vili::array { 6, 12, 18, 24, 30, 36, 42, 48, 54, 60 };
        REQUIRE_THROWS_AS(
            vili::validator::validate_integer("", integer_validator, table_of_6),
            vili::validator::exceptions::value_type_mismatch);
    }
    SECTION("Test object type")
    {
        vili::node my_family
            = vili::object { { "Bob", 10 }, { "Jack", 20 }, { "Molly", 30 } };
        REQUIRE_THROWS_AS(
            vili::validator::validate_integer("", integer_validator, my_family),
            vili::validator::exceptions::value_type_mismatch);
    }
}

TEST_CASE("Integer validator type check")
{
    vili::node zero = 10;
    SECTION("Test integer validator")
    {
        vili::node integer_validator = vili::object { { "type", "integer" } };
        REQUIRE_NOTHROW(vili::validator::validate_integer("", integer_validator, zero));
    }
    SECTION("Test string validator")
    {
        vili::node string_validator = vili::object { { "type", "string" } };
        REQUIRE_THROWS_AS(vili::validator::validate_integer("", string_validator, zero),
            vili::validator::exceptions::validator_type_mismatch);
    }
    SECTION("Test boolean validator")
    {
        vili::node boolean_validator = vili::object { { "type", "boolean" } };
        REQUIRE_THROWS_AS(vili::validator::validate_integer("", boolean_validator, zero),
            vili::validator::exceptions::validator_type_mismatch);
    }
    SECTION("Test number validator")
    {
        vili::node number_validator = vili::object { { "type", "number" } };
        REQUIRE_THROWS_AS(vili::validator::validate_integer("", number_validator, zero),
            vili::validator::exceptions::validator_type_mismatch);
    }
    SECTION("Test array validator")
    {
        vili::node array_validator = vili::object { { "type", "array" } };
        REQUIRE_THROWS_AS(vili::validator::validate_integer("", array_validator, zero),
            vili::validator::exceptions::validator_type_mismatch);
    }
    SECTION("Test object validator")
    {
        vili::node object_validator = vili::object { { "type", "object" } };
        REQUIRE_THROWS_AS(vili::validator::validate_integer("", object_validator, zero),
            vili::validator::exceptions::validator_type_mismatch);
    }
}

TEST_CASE("multiple_of validator")
{
    SECTION("Multiple of 10")
    {
        vili::node multiple_of_10_validator
            = vili::object { { "type", "integer" }, { "multiple_of", 10 } };

        vili::node zero = 0;
        REQUIRE_NOTHROW(
            vili::validator::validate_integer("", multiple_of_10_validator, zero));

        vili::node ten = 10;
        REQUIRE_NOTHROW(
            vili::validator::validate_integer("", multiple_of_10_validator, ten));

        vili::node fifty = 50;
        REQUIRE_NOTHROW(
            vili::validator::validate_integer("", multiple_of_10_validator, fifty));

        vili::node one_hundred = 100;
        REQUIRE_NOTHROW(
            vili::validator::validate_integer("", multiple_of_10_validator, one_hundred));

        vili::node secret = 101100001000100;
        REQUIRE_NOTHROW(
            vili::validator::validate_integer("", multiple_of_10_validator, secret));

        vili::node minus_one_thousand = -1000;
        REQUIRE_NOTHROW(vili::validator::validate_integer(
            "", multiple_of_10_validator, minus_one_thousand));

        vili::node five = 5;
        REQUIRE_THROWS_AS(
            vili::validator::validate_integer("", multiple_of_10_validator, five),
            vili::validator::exceptions::constraint_validation_failure);

        vili::node eleven = 11;
        REQUIRE_THROWS_AS(
            vili::validator::validate_integer("", multiple_of_10_validator, eleven),
            vili::validator::exceptions::constraint_validation_failure);
    }
}

TEST_CASE("min / max validator")
{
    SECTION("Positive number")
    {
        vili::node positive_number_validator
            = vili::object { { "type", "integer" }, { "min", 0 } };

        vili::node twenty_two = 22;
        REQUIRE_NOTHROW(
            vili::validator::validate_integer("", positive_number_validator, twenty_two));

        vili::node minus_one = -1;
        REQUIRE_THROWS_AS(
            vili::validator::validate_integer("", positive_number_validator, minus_one),
            vili::validator::exceptions::constraint_validation_failure);

        vili::node zero = 0;
        REQUIRE_NOTHROW(
            vili::validator::validate_integer("", positive_number_validator, zero));
    }
    SECTION("Negative number")
    {
        vili::node negative_number_validator
            = vili::object { { "type", "integer" }, { "max", 0 } };

        vili::node minus_one_hundred = -100;
        REQUIRE_NOTHROW(vili::validator::validate_integer(
            "", negative_number_validator, minus_one_hundred));

        vili::node one_hundred = 100;
        REQUIRE_THROWS_AS(
            vili::validator::validate_integer("", negative_number_validator, one_hundred),
            vili::validator::exceptions::constraint_validation_failure);

        vili::node one_thousand = 1000;
        REQUIRE_THROWS_AS(vili::validator::validate_integer(
                              "", negative_number_validator, one_thousand),
            vili::validator::exceptions::constraint_validation_failure);

        vili::node zero = 0;
        REQUIRE_NOTHROW(
            vili::validator::validate_integer("", negative_number_validator, zero));
    }
    SECTION("Number in range")
    {
        vili::node between_minus_100_and_100_validator
            = vili::object { { "type", "integer" }, { "min", -100 }, { "max", 100 } };

        vili::node minus_one_hundred = -100;
        REQUIRE_NOTHROW(vili::validator::validate_integer(
            "", between_minus_100_and_100_validator, minus_one_hundred));

        vili::node one_thousand = 1000;
        REQUIRE_THROWS_AS(vili::validator::validate_integer(
                              "", between_minus_100_and_100_validator, one_thousand),
            vili::validator::exceptions::constraint_validation_failure);

        vili::node on_negative_edge = -101;
        REQUIRE_THROWS_AS(vili::validator::validate_integer(
                              "", between_minus_100_and_100_validator, on_negative_edge),
            vili::validator::exceptions::constraint_validation_failure);

        vili::node on_positive_edge = 101;
        REQUIRE_THROWS_AS(vili::validator::validate_integer(
                              "", between_minus_100_and_100_validator, on_positive_edge),
            vili::validator::exceptions::constraint_validation_failure);

        vili::node zero = 0;
        REQUIRE_NOTHROW(vili::validator::validate_integer(
            "", between_minus_100_and_100_validator, zero));
    }
    SECTION("Non-zero Positive number")
    {
        vili::node positive_number_validator
            = vili::object { { "type", "integer" }, { "exclusive_min", 0 } };

        vili::node twenty_two = 22;
        REQUIRE_NOTHROW(
            vili::validator::validate_integer("", positive_number_validator, twenty_two));

        vili::node minus_one = -1;
        REQUIRE_THROWS_AS(
            vili::validator::validate_integer("", positive_number_validator, minus_one),
            vili::validator::exceptions::constraint_validation_failure);

        vili::node zero = 0;
        REQUIRE_THROWS_AS(
            vili::validator::validate_integer("", positive_number_validator, zero),
            vili::validator::exceptions::constraint_validation_failure);
    }
    SECTION("Non-zero Negative number")
    {
        vili::node negative_number_validator
            = vili::object { { "type", "integer" }, { "exclusive_max", 0 } };

        vili::node minus_one_hundred = -100;
        REQUIRE_NOTHROW(vili::validator::validate_integer(
            "", negative_number_validator, minus_one_hundred));

        vili::node one_hundred = 100;
        REQUIRE_THROWS_AS(
            vili::validator::validate_integer("", negative_number_validator, one_hundred),
            vili::validator::exceptions::constraint_validation_failure);

        vili::node one_thousand = 1000;
        REQUIRE_THROWS_AS(vili::validator::validate_integer(
                              "", negative_number_validator, one_thousand),
            vili::validator::exceptions::constraint_validation_failure);

        vili::node zero = 0;
        REQUIRE_THROWS_AS(
            vili::validator::validate_integer("", negative_number_validator, zero),
            vili::validator::exceptions::constraint_validation_failure);
    }
}