#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>

#include "DataField.hpp"
#include "SimpleDataField.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"
#include "misc.hpp"

TRIVIAL_TEST(DataField_test);

//==============================================================================
template <class T> bool writeRawTest()
{
    // With this test we're going to write a simple integer data field set to 0
    // into a buffer of 1s that is double the integer's size at successively
    // greater offsets.  As we go along the first half of the buffer will lose
    // 0s and the second half will gain 0s.  We can predict exactly what both
    // halves should be equal to as integers, so we check this with each offset
    // write.

    // Will go false if the test fails
    bool passed = true;

    const unsigned int workarea_size = sizeof(T) * 2;
    T workarea[2];

    for (unsigned int i = 0; i <= sizeof(T) * BITS_PER_BYTE; ++i)
    {
        // Set the entire work area to all ones
        memset(workarea, 0xff, workarea_size);

        // We'll shift this 0 across the whole work area one bit at a time,
        // checking the value of both halves against math
        SimpleDataField<T> test_sdf(0);

        T something = std::pow(2, i) - 1;

        // Work area halves should equal these two values after the write
        T correct_firsthalf = something;
        T correct_secondhalf = std::numeric_limits<T>::max() - something;

        // Actually do the write
        test_sdf.DataField::writeRaw(
            reinterpret_cast<std::uint8_t*>(workarea), i);

        // Now check both halves
        std::cout << "Offset " << i << " " << workarea[0] << " ";
        if (workarea[0] != correct_firsthalf)
        {
            std::cout << "(WRONG should be " << correct_firsthalf << ") ";
            passed = false;
        }

        std::cout << workarea[1] << " ";
        if (workarea[1] != correct_secondhalf)
        {
            std::cout << "(WRONG should be " << correct_secondhalf << ") ";
            passed = false;
        }

        std::cout << "\n";

        if (!passed)
        {
            break;
        }
    }

    return passed;
}

//==============================================================================
Test::Result DataField_test::body()
{
    MUST_BE_TRUE(writeRawTest<std::uint8_t>());
    MUST_BE_TRUE(writeRawTest<std::uint16_t>());
    MUST_BE_TRUE(writeRawTest<std::uint32_t>());

    return Test::PASSED;
}
