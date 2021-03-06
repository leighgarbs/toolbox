#include <iostream>
#include <stdexcept>
#include <string>

#include "Test.hpp"

//==============================================================================
Test::Test(const std::string& name)
{
    setName(name);
}

//==============================================================================
Test::~Test()
{
}

//==============================================================================
Test::Result Test::run()
{
    // Print test case name
    std::cout << "Running " << name << "\n";

    // Run the body of the test
    Test::Result result = body();

    // Print out the result
    std::cout << name << " ";

    if (result == Test::FAILED)
    {
        std::cout << "failed";
    }
    else if (result == Test::PASSED)
    {
        std::cout << "passed";
    }
    else if (result == Test::SKIPPED)
    {
        // Must have been skipped, there are no other cases
        std::cout << "skipped";
    }
    else
    {
        throw std::runtime_error("Test returned unknown result");
    }

    std::cout << "\n";

    return result;
}
