#include <catch/catch.hpp>

#include <vld8/exceptions.hpp>
#include <vld8/validator.hpp>

#include "vili/parser/parser.hpp"

TEST_CASE("String type check")
{
    vili::node string_validator = vili::object { { "type", "string" } };
    SECTION("Test integer type")
    {
        vili::node forty_two = 42;
        REQUIRE_THROWS_AS(
            vili::validator::validate_string("", string_validator, forty_two),
            vili::validator::exceptions::value_type_mismatch);
    }
    SECTION("Test string type")
    {
        vili::node are_you_okay = "Are you okay ?";
        REQUIRE_NOTHROW(
            vili::validator::validate_string("", string_validator, are_you_okay));
    }
    SECTION("Test boolean type")
    {
        vili::node bool_true = true;
        REQUIRE_THROWS_AS(
            vili::validator::validate_string("", string_validator, bool_true),
            vili::validator::exceptions::value_type_mismatch);
    }
    SECTION("Test number type")
    {
        vili::node khinchin = 2.685452;
        REQUIRE_THROWS_AS(
            vili::validator::validate_string("", string_validator, khinchin),
            vili::validator::exceptions::value_type_mismatch);
    }
    SECTION("Test array type")
    {
        vili::node table_of_5 = vili::array { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 };
        REQUIRE_THROWS_AS(
            vili::validator::validate_string("", string_validator, table_of_5),
            vili::validator::exceptions::value_type_mismatch);
    }
    SECTION("Test object type")
    {
        vili::node my_weapons
            = vili::object { { "Sword", 1.93 }, { "Bow", 38.32 }, { "Spear", 5.15 } };
        REQUIRE_THROWS_AS(
            vili::validator::validate_string("", string_validator, my_weapons),
            vili::validator::exceptions::value_type_mismatch);
    }
}

TEST_CASE("String validator type check")
{
    vili::node project_name = "vili";
    SECTION("Test boolean validator")
    {
        vili::node integer_validator = vili::object { { "type", "integer" } };
        REQUIRE_THROWS_AS(
            vili::validator::validate_string("", integer_validator, project_name),
            vili::validator::exceptions::validator_type_mismatch);
    }
    SECTION("Test string validator")
    {
        vili::node string_validator = vili::object { { "type", "string" } };
        REQUIRE_NOTHROW(
            vili::validator::validate_string("", string_validator, project_name));
    }
    SECTION("Test boolean validator")
    {
        vili::node boolean_validator = vili::object { { "type", "boolean" } };
        REQUIRE_THROWS_AS(
            vili::validator::validate_string("", boolean_validator, project_name),
            vili::validator::exceptions::validator_type_mismatch);
    }
    SECTION("Test number validator")
    {
        vili::node number_validator = vili::object { { "type", "number" } };
        REQUIRE_THROWS_AS(
            vili::validator::validate_string("", number_validator, project_name),
            vili::validator::exceptions::validator_type_mismatch);
    }
    SECTION("Test array validator")
    {
        vili::node array_validator = vili::object { { "type", "array" } };
        REQUIRE_THROWS_AS(
            vili::validator::validate_string("", array_validator, project_name),
            vili::validator::exceptions::validator_type_mismatch);
    }
    SECTION("Test object validator")
    {
        vili::node object_validator = vili::object { { "type", "object" } };
        REQUIRE_THROWS_AS(
            vili::validator::validate_string("", object_validator, project_name),
            vili::validator::exceptions::validator_type_mismatch);
    }
}

TEST_CASE("String min_length / max_length")
{
    SECTION("String min length")
    {
        vili::node non_empty_string
            = vili::object { { "type", "string" }, { "min_length", 1 } };
        vili::node long_string_only
            = vili::object { { "type", "string" }, { "min_length", 60 } };

        vili::node name = "Bob";
        REQUIRE_NOTHROW(vili::validator::validate_string("", non_empty_string, name));
        REQUIRE_THROWS_AS(vili::validator::validate_string("", long_string_only, name),
            vili::validator::exceptions::constraint_validation_failure);

        vili::node project_description
            = "Vili is a cool data language focusing on lisibility and simplicity";
        REQUIRE_NOTHROW(
            vili::validator::validate_string("", non_empty_string, project_description));
        REQUIRE_NOTHROW(
            vili::validator::validate_string("", long_string_only, project_description));

        vili::node empty_string = "";
        REQUIRE_THROWS_AS(
            vili::validator::validate_string("", non_empty_string, empty_string),
            vili::validator::exceptions::constraint_validation_failure);
        REQUIRE_THROWS_AS(
            vili::validator::validate_string("", long_string_only, empty_string),
            vili::validator::exceptions::constraint_validation_failure);
    }
    SECTION("String max length")
    {
        vili::node empty_string_validator
            = vili::object { { "type", "string" }, { "max_length", 0 } };
        vili::node bad_password_validator
            = vili::object { { "type", "string" }, { "max_length", 25 } };

        vili::node name = "Bob";
        REQUIRE_THROWS_AS(
            vili::validator::validate_string("", empty_string_validator, name),
            vili::validator::exceptions::constraint_validation_failure);
        REQUIRE_NOTHROW(
            vili::validator::validate_string("", bad_password_validator, name));

        vili::node project_description
            = "Vili is a cool data language focusing on lisibility and simplicity";
        REQUIRE_THROWS_AS(vili::validator::validate_string(
                              "", empty_string_validator, project_description),
            vili::validator::exceptions::constraint_validation_failure);
        REQUIRE_THROWS_AS(vili::validator::validate_string(
                              "", bad_password_validator, project_description),
            vili::validator::exceptions::constraint_validation_failure);

        vili::node empty_string = "";
        REQUIRE_NOTHROW(
            vili::validator::validate_string("", empty_string_validator, empty_string));
        REQUIRE_NOTHROW(
            vili::validator::validate_string("", bad_password_validator, empty_string));
    }
}

TEST_CASE("String pattern constraint")
{
    SECTION("Integer pattern")
    {
        vili::node integer_pattern
            = vili::object { { "type", "string" }, { "pattern", "integer" } };

        vili::node zero = "0";
        REQUIRE_NOTHROW(vili::validator::validate_string("", integer_pattern, zero));

        vili::node twenty_two = "22";
        REQUIRE_NOTHROW(
            vili::validator::validate_string("", integer_pattern, twenty_two));

        vili::node minus_12345 = "-12345";
        REQUIRE_NOTHROW(
            vili::validator::validate_string("", integer_pattern, minus_12345));

        vili::node pi = "3.14";
        REQUIRE_THROWS_AS(vili::validator::validate_string("", integer_pattern, pi),
            vili::validator::exceptions::constraint_validation_failure);

        vili::node real_integer = 25;
        REQUIRE_THROWS_AS(
            vili::validator::validate_string("", integer_pattern, real_integer),
            vili::validator::exceptions::value_type_mismatch);
    }
    SECTION("Number pattern")
    {
        vili::node number_pattern
            = vili::object { { "type", "string" }, { "pattern", "number" } };
    }
}