#include <catch/catch.hpp>

#include <vld8/exceptions.hpp>
#include <vld8/validator.hpp>

TEST_CASE("Boolean type check")
{
    vili::node boolean_validator = vili::object { { "type", "boolean" } };
    SECTION("Test integer type")
    {
        vili::node twenty_two = 22;
        REQUIRE_THROWS_AS(
            vili::validator::validate_boolean("", boolean_validator, twenty_two),
            vili::validator::exceptions::value_type_mismatch);
    }
    SECTION("Test string type")
    {
        vili::node how_are_you = "How is your day ?";
        REQUIRE_THROWS_AS(
            vili::validator::validate_boolean("", boolean_validator, how_are_you),
            vili::validator::exceptions::value_type_mismatch);
    }
    SECTION("Test boolean type")
    {
        vili::node bool_true = true;
        REQUIRE_NOTHROW(
            vili::validator::validate_boolean("", boolean_validator, bool_true));

        vili::node bool_false = false;
        REQUIRE_NOTHROW(
            vili::validator::validate_boolean("", boolean_validator, bool_false));
    }
    SECTION("Test number type")
    {
        vili::node golden_ratio = 1.6180;
        REQUIRE_THROWS_AS(
            vili::validator::validate_boolean("", boolean_validator, golden_ratio),
            vili::validator::exceptions::value_type_mismatch);
    }
    SECTION("Test array type")
    {
        vili::node table_of_7 = vili::array { 7, 14, 21, 28, 35, 42, 49, 56, 63, 70 };
        REQUIRE_THROWS_AS(
            vili::validator::validate_boolean("", boolean_validator, table_of_7),
            vili::validator::exceptions::value_type_mismatch);
    }
    SECTION("Test object type")
    {
        vili::node my_pets
            = vili::object { { "Turtle", true }, { "Puppy", false }, { "Cat", true } };
        REQUIRE_THROWS_AS(
            vili::validator::validate_boolean("", boolean_validator, my_pets),
            vili::validator::exceptions::value_type_mismatch);
    }
}

TEST_CASE("Boolean validator type check")
{
    vili::node is_vili_cool = true;
    SECTION("Test boolean validator")
    {
        vili::node integer_validator = vili::object { { "type", "integer" } };
        REQUIRE_THROWS_AS(
            vili::validator::validate_boolean("", integer_validator, is_vili_cool),
            vili::validator::exceptions::validator_type_mismatch);
    }
    SECTION("Test string validator")
    {
        vili::node string_validator = vili::object { { "type", "string" } };
        REQUIRE_THROWS_AS(
            vili::validator::validate_boolean("", string_validator, is_vili_cool),
            vili::validator::exceptions::validator_type_mismatch);
    }
    SECTION("Test boolean validator")
    {
        vili::node boolean_validator = vili::object { { "type", "boolean" } };
        REQUIRE_NOTHROW(
            vili::validator::validate_boolean("", boolean_validator, is_vili_cool));
    }
    SECTION("Test number validator")
    {
        vili::node number_validator = vili::object { { "type", "number" } };
        REQUIRE_THROWS_AS(
            vili::validator::validate_boolean("", number_validator, is_vili_cool),
            vili::validator::exceptions::validator_type_mismatch);
    }
    SECTION("Test array validator")
    {
        vili::node array_validator = vili::object { { "type", "array" } };
        REQUIRE_THROWS_AS(
            vili::validator::validate_boolean("", array_validator, is_vili_cool),
            vili::validator::exceptions::validator_type_mismatch);
    }
    SECTION("Test object validator")
    {
        vili::node object_validator = vili::object { { "type", "object" } };
        REQUIRE_THROWS_AS(
            vili::validator::validate_boolean("", object_validator, is_vili_cool),
            vili::validator::exceptions::validator_type_mismatch);
    }
}