#if !defined CONFIGURATION_PARAMETER_TEST_HPP
#define CONFIGURATION_PARAMETER_TEST_HPP

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

#include "ConfigurationParameter.hpp"

namespace Configuration
{
    TEST_CASES_BEGIN(Parameter_test)

        TEST_CASES_BEGIN(SetValue)

            TEST(String)
            TEST(Char)
            TEST(Double)
            TEST(Float)
            TEST(Int)
            TEST(Long)
            TEST(LongDouble)
            TEST(LongLong)
            TEST(Short)
            TEST(UnsignedChar)
            TEST(UnsignedInt)
            TEST(UnsignedLong)
            TEST(UnsignedLongLong)
            TEST(UnsignedShort)

            template <class T>
            static Test::Result test(const T& initial_value, const T& set_value);

        TEST_CASES_END(SetValue)

        TEST_CASES_BEGIN(OperatorLessThan)

            TEST(StringConstCharP)
            TEST(String)
            TEST(Char)
            TEST(Double)
            TEST(Float)
            TEST(Int)
            TEST(Long)
            TEST(LongDouble)
            TEST(LongLong)
            TEST(Short)
            TEST(UnsignedChar)
            TEST(UnsignedInt)
            TEST(UnsignedLong)
            TEST(UnsignedLongLong)
            TEST(UnsignedShort)

            template <class T> static Test::Result test(const T& value1, const T& value2);

        TEST_CASES_END(OperatorLessThan)

        TEST_CASES_BEGIN(OperatorGreaterThan)

            TEST(StringConstCharP)
            TEST(String)
            TEST(Char)
            TEST(Double)
            TEST(Float)
            TEST(Int)
            TEST(Long)
            TEST(LongDouble)
            TEST(LongLong)
            TEST(Short)
            TEST(UnsignedChar)
            TEST(UnsignedInt)
            TEST(UnsignedLong)
            TEST(UnsignedLongLong)
            TEST(UnsignedShort)

            template <class T> static Test::Result test(const T& value1, const T& value2);

        TEST_CASES_END(OperatorGreaterThan)

        TEST_CASES_BEGIN(OperatorLessThanOrEqualTo)

            TEST(StringConstCharP)
            TEST(String)
            TEST(Char)
            TEST(Double)
            TEST(Float)
            TEST(Int)
            TEST(Long)
            TEST(LongDouble)
            TEST(LongLong)
            TEST(Short)
            TEST(UnsignedChar)
            TEST(UnsignedInt)
            TEST(UnsignedLong)
            TEST(UnsignedLongLong)
            TEST(UnsignedShort)

            template <class T> static Test::Result test(const T& value1, const T& value2);

        TEST_CASES_END(OperatorLessThanOrEqualTo)

        TEST_CASES_BEGIN(OperatorGreaterThanOrEqualTo)

            TEST(StringConstCharP)
            TEST(String)
            TEST(Char)
            TEST(Double)
            TEST(Float)
            TEST(Int)
            TEST(Long)
            TEST(LongDouble)
            TEST(LongLong)
            TEST(Short)
            TEST(UnsignedChar)
            TEST(UnsignedInt)
            TEST(UnsignedLong)
            TEST(UnsignedLongLong)
            TEST(UnsignedShort)

            template <class T> static Test::Result test(const T& value1, const T& value2);

        TEST_CASES_END(OperatorGreaterThanOrEqualTo)

        TEST_CASES_BEGIN(OperatorEquality)

            TEST(StringConstCharP)
            TEST(String)
            TEST(Char)
            TEST(Double)
            TEST(Float)
            TEST(Int)
            TEST(Long)
            TEST(LongDouble)
            TEST(LongLong)
            TEST(Short)
            TEST(UnsignedChar)
            TEST(UnsignedInt)
            TEST(UnsignedLong)
            TEST(UnsignedLongLong)
            TEST(UnsignedShort)

            template <class T> static Test::Result test(const T& value1, const T& value2);

        TEST_CASES_END(OperatorEquality)

        TEST_CASES_BEGIN(OperatorNotEqual)

            TEST(StringConstCharP)
            TEST(String)
            TEST(Char)
            TEST(Double)
            TEST(Float)
            TEST(Int)
            TEST(Long)
            TEST(LongDouble)
            TEST(LongLong)
            TEST(Short)
            TEST(UnsignedChar)
            TEST(UnsignedInt)
            TEST(UnsignedLong)
            TEST(UnsignedLongLong)
            TEST(UnsignedShort)

            template <class T> static Test::Result test(const T& value1, const T& value2);

        TEST_CASES_END(OperatorNotEqual)

    TEST_CASES_END(Parameter_test)
}

#endif
