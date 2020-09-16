#include <catch/catch.hpp>
#include <vili/parser/parser.hpp>

#include <vld8/templates.hpp>
#include <vld8/validator.hpp>

TEST_CASE("Animation validator")
{
    SECTION("Integer array")
    {
        vili::node validator
            = vili::parser::from_file("animation_validator.vili", vld8::vld8_templates());
        printf("");
    }
}