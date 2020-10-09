#include <catch/catch.hpp>
#include <vili/parser/parser.hpp>

#include <vld8/templates.hpp>
#include <vld8/validator.hpp>

vili::parser::state animation_templates()
{
    vili::parser::state state;
    vili::node play_group
        = vili::object { { "command", "play_group" }, { "group", "" }, { "repeat", 1 } };
    state.push_template("play_group", play_group);
    vili::node wait = vili::object { { "command", "wait_command" }, { "time", 1.0 } };
    state.push_template("wait_command", wait);
    vili::node set_animation
        = vili::object { { "command", "set_animation" }, { "animation", "" } };
    state.push_template("set_animation", set_animation);

    // AnimationPlayMode enum
    state.push_template("OneTime", "OneTime");
    state.push_template("Loop", "Loop");
    state.push_template("Force", "Force");
    return state;
}

TEST_CASE("Animation validator")
{
    SECTION("Valid animation file")
    {
        vili::node validator = vili::parser::from_file(
            "animation_validator.vili", vili::validator::templates());
        vili::node animation
            = vili::parser::from_file("animation_file.vili", animation_templates());
        REQUIRE_NOTHROW(vili::validator::validate_tree(validator, animation));
        printf("");
    }
}