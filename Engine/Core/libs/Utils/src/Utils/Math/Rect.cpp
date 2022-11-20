//
// Created by Monika on 18.11.2022.
//

#include <Utils/Math/Rect.h>

namespace SR_MATH_NS::StaticTest {
    SR_MAYBE_UNUSED static constexpr bool VerifyRectTest1() {
        IRect rect(5, -5, 10, -10);

        const int32_t right = rect.Right() + 5;
        const int32_t top = rect.Top() + 5;

        rect.SetRight(right);
        rect.SetTop(top);

        rect.SetLeft(5);
        rect.SetBottom(5);

        return rect.Right() == right && rect.Top() == top;
    }

    SR_MAYBE_UNUSED static constexpr bool VerifyRectTest2() {
        IRect rect(5, -5, 10, -10);

        const int32_t right = rect.Right() + 5;
        const int32_t top = rect.Top() + 5;

        rect.SetRight(right);
        rect.SetTop(top);

        rect.SetLeft(-5);
        rect.SetBottom(-5);

        return rect.Right() == right && rect.Top() == top;
    }

    SR_MAYBE_UNUSED static constexpr bool VerifyRectTest3() {
        IRect rect(5, -5, 10, -10);

        const int32_t left = rect.Left();
        const int32_t bottom = rect.Bottom();

        rect.SetRight(5);
        rect.SetTop(5);

        return rect.Left() == left && rect.Bottom() == bottom;
    }

    SR_MAYBE_UNUSED static constexpr bool VerifyRectTest4() {
        IRect rect(5, -5, 10, -10);

        const int32_t left = rect.Left();
        const int32_t bottom = rect.Bottom();

        rect.SetRight(-5);
        rect.SetTop(-5);

        return rect.Left() == left && rect.Bottom() == bottom;
    }

    SR_STATIC_ASSERT2(VerifyRectTest1(), "Failed verify rect!");
    SR_STATIC_ASSERT2(VerifyRectTest2(), "Failed verify rect!");
    SR_STATIC_ASSERT2(VerifyRectTest3(), "Failed verify rect!");
    SR_STATIC_ASSERT2(VerifyRectTest4(), "Failed verify rect!");
}