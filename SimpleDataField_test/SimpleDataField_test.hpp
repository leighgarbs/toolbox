#if !defined SIMPLE_DATA_FIELD_TEST
#define SIMPLE_DATA_FIELD_TEST

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(SimpleDataField_test);

    TEST(Lengths)
    TEST(AssignmentGetValue)
    TEST(WriteRaw)
    TEST(ReadRaw)

TEST_CASES_END(SimpleDataField_test);

#endif