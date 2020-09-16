#include <vld8/validator.hpp>

namespace vld8
{
    vili::node validate_object(const vili::node& validator, const vili::node& input)
    {
        return vili::object {};
    }

    vili::node validate_tree(const vili::node& validator, const vili::node& input)
    {
        if (validator.is<vili::object>())
        {
            validate_object(validator, input);
        }

        return vili::object {};
    }
}
