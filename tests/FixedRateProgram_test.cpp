#include <cerrno>
#include <stdexcept>
#include <system_error>

#include "FixedRateProgram_test.hpp"

#include "FixedRateProgram_test_tc1.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(FixedRateProgram_test);

//==============================================================================
FixedRateProgram_test::FixedRateProgram_test() :
    period(1.0)
{
}

//==============================================================================
FixedRateProgram_test::~FixedRateProgram_test()
{
}

//==============================================================================
Test::Result FixedRateProgram_test::run()
{
    // Normally it would not be possible for a program to receive no arguments
    FixedRateProgram_test_tc1 test_frp(0, 0, period);
    test_frp.run();

    throw std::system_error(ENOENT, std::system_category());

    return Test::PASSED;
}
