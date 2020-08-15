#include <string>

#include "ConfigurationParameter_test.hpp"

#include "ConfigurationNoopParameter.hpp"
#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_PROGRAM_MAIN(Configuration::Parameter_test);

//=============================================================================================
void Configuration::Parameter_test::addTestCases()
{
    ADD_TEST_CASE(SetValue);

    // Relational operators
    ADD_TEST_CASE(OperatorLessThan);
    ADD_TEST_CASE(OperatorGreaterThan);
    ADD_TEST_CASE(OperatorLessThanOrEqualTo);
    ADD_TEST_CASE(OperatorGreaterThanOrEqualTo);
    ADD_TEST_CASE(OperatorEquality);
    ADD_TEST_CASE(OperatorNotEqual);
}

//=============================================================================================
void Configuration::Parameter_test::SetValue::addTestCases()
{
    ADD_TEST_CASE(Bool);
    ADD_TEST_CASE(String);
    ADD_TEST_CASE(Char);
    ADD_TEST_CASE(Double);
    ADD_TEST_CASE(Float);
    ADD_TEST_CASE(Int);
    ADD_TEST_CASE(Long);
    ADD_TEST_CASE(LongDouble);
    ADD_TEST_CASE(LongLong);
    ADD_TEST_CASE(Short);
    ADD_TEST_CASE(UnsignedChar);
    ADD_TEST_CASE(UnsignedInt);
    ADD_TEST_CASE(UnsignedLong);
    ADD_TEST_CASE(UnsignedLongLong);
    ADD_TEST_CASE(UnsignedShort);
}

//=============================================================================================
void Configuration::Parameter_test::OperatorLessThan::addTestCases()
{
    ADD_TEST_CASE(Bool);
    ADD_TEST_CASE(StringConstCharP);
    ADD_TEST_CASE(String);
    ADD_TEST_CASE(Char);
    ADD_TEST_CASE(Double);
    ADD_TEST_CASE(Float);
    ADD_TEST_CASE(Int);
    ADD_TEST_CASE(Long);
    ADD_TEST_CASE(LongDouble);
    ADD_TEST_CASE(LongLong);
    ADD_TEST_CASE(Short);
    ADD_TEST_CASE(UnsignedChar);
    ADD_TEST_CASE(UnsignedInt);
    ADD_TEST_CASE(UnsignedLong);
    ADD_TEST_CASE(UnsignedLongLong);
    ADD_TEST_CASE(UnsignedShort);
}

//=============================================================================================
void Configuration::Parameter_test::OperatorGreaterThan::addTestCases()
{
    ADD_TEST_CASE(Bool);
    ADD_TEST_CASE(StringConstCharP);
    ADD_TEST_CASE(String);
    ADD_TEST_CASE(Char);
    ADD_TEST_CASE(Double);
    ADD_TEST_CASE(Float);
    ADD_TEST_CASE(Int);
    ADD_TEST_CASE(Long);
    ADD_TEST_CASE(LongDouble);
    ADD_TEST_CASE(LongLong);
    ADD_TEST_CASE(Short);
    ADD_TEST_CASE(UnsignedChar);
    ADD_TEST_CASE(UnsignedInt);
    ADD_TEST_CASE(UnsignedLong);
    ADD_TEST_CASE(UnsignedLongLong);
    ADD_TEST_CASE(UnsignedShort);
}

//=============================================================================================
void Configuration::Parameter_test::OperatorLessThanOrEqualTo::addTestCases()
{
    ADD_TEST_CASE(StringConstCharP);
    ADD_TEST_CASE(String);
    ADD_TEST_CASE(Char);
    ADD_TEST_CASE(Double);
    ADD_TEST_CASE(Float);
    ADD_TEST_CASE(Int);
    ADD_TEST_CASE(Long);
    ADD_TEST_CASE(LongDouble);
    ADD_TEST_CASE(LongLong);
    ADD_TEST_CASE(Short);
    ADD_TEST_CASE(UnsignedChar);
    ADD_TEST_CASE(UnsignedInt);
    ADD_TEST_CASE(UnsignedLong);
    ADD_TEST_CASE(UnsignedLongLong);
    ADD_TEST_CASE(UnsignedShort);
}

//=============================================================================================
void Configuration::Parameter_test::OperatorGreaterThanOrEqualTo::addTestCases()
{
    ADD_TEST_CASE(StringConstCharP);
    ADD_TEST_CASE(String);
    ADD_TEST_CASE(Char);
    ADD_TEST_CASE(Double);
    ADD_TEST_CASE(Float);
    ADD_TEST_CASE(Int);
    ADD_TEST_CASE(Long);
    ADD_TEST_CASE(LongDouble);
    ADD_TEST_CASE(LongLong);
    ADD_TEST_CASE(Short);
    ADD_TEST_CASE(UnsignedChar);
    ADD_TEST_CASE(UnsignedInt);
    ADD_TEST_CASE(UnsignedLong);
    ADD_TEST_CASE(UnsignedLongLong);
    ADD_TEST_CASE(UnsignedShort);
}

//=============================================================================================
void Configuration::Parameter_test::OperatorEquality::addTestCases()
{
    ADD_TEST_CASE(Bool);
    ADD_TEST_CASE(StringConstCharP);
    ADD_TEST_CASE(String);
    ADD_TEST_CASE(Char);
    ADD_TEST_CASE(Double);
    ADD_TEST_CASE(Float);
    ADD_TEST_CASE(Int);
    ADD_TEST_CASE(Long);
    ADD_TEST_CASE(LongDouble);
    ADD_TEST_CASE(LongLong);
    ADD_TEST_CASE(Short);
    ADD_TEST_CASE(UnsignedChar);
    ADD_TEST_CASE(UnsignedInt);
    ADD_TEST_CASE(UnsignedLong);
    ADD_TEST_CASE(UnsignedLongLong);
    ADD_TEST_CASE(UnsignedShort);
}

//=============================================================================================
void Configuration::Parameter_test::OperatorNotEqual::addTestCases()
{
    ADD_TEST_CASE(Bool);
    ADD_TEST_CASE(StringConstCharP);
    ADD_TEST_CASE(String);
    ADD_TEST_CASE(Char);
    ADD_TEST_CASE(Double);
    ADD_TEST_CASE(Float);
    ADD_TEST_CASE(Int);
    ADD_TEST_CASE(Long);
    ADD_TEST_CASE(LongDouble);
    ADD_TEST_CASE(LongLong);
    ADD_TEST_CASE(Short);
    ADD_TEST_CASE(UnsignedChar);
    ADD_TEST_CASE(UnsignedInt);
    ADD_TEST_CASE(UnsignedLong);
    ADD_TEST_CASE(UnsignedLongLong);
    ADD_TEST_CASE(UnsignedShort);
}

//=============================================================================================
template <class T> Test::Result Configuration::Parameter_test::SetValue::test(
    const T& initial_value,
    const T& set_value)
{
    NoopParameter<T> configuration_value(initial_value);

    // Arguments are not set by default, even when given a default value.
    MUST_BE_TRUE(!configuration_value.isSet());

    configuration_value.setValue(set_value);

    // Now we should be set.
    MUST_BE_TRUE(configuration_value.isSet());

    // Get the value after the update and compare to what we expected.
    T retrieved_value;
    configuration_value.getValue(retrieved_value);
    MUST_BE_TRUE(set_value == retrieved_value);

    return Test::PASSED;
}

//=============================================================================================
template <class T>
Test::Result Configuration::Parameter_test::OperatorLessThan::test(const T& smaller,
                                                                   const T& bigger)
{
    NoopParameter<T> arg_smaller(smaller);
    NoopParameter<T> arg_bigger(bigger);

    // NoopParameter<T> vs. NoopParameter<T>
    MUST_BE_TRUE(arg_smaller < arg_bigger);
    MUST_BE_TRUE(!(arg_bigger < arg_smaller));
    MUST_BE_TRUE(!(arg_smaller < arg_smaller));

    // NoopParameter<T> vs. const T
    MUST_BE_TRUE(arg_smaller < bigger);
    MUST_BE_TRUE(!(bigger < arg_smaller));
    MUST_BE_TRUE(!(arg_smaller < arg_smaller));

    // const T vs. NoopParameter<T>
    MUST_BE_TRUE(smaller < arg_bigger);
    MUST_BE_TRUE(!(arg_bigger < smaller));
    MUST_BE_TRUE(!(smaller < smaller));

    return Test::PASSED;
}

//=============================================================================================
template <class T>
Test::Result Configuration::Parameter_test::OperatorGreaterThan::test(const T& smaller,
                                                                      const T& bigger)
{
    NoopParameter<T> arg_smaller(smaller);
    NoopParameter<T> arg_bigger(bigger);

    // NoopParameter<T> vs. NoopParameter<T>
    MUST_BE_TRUE(arg_bigger > arg_smaller);
    MUST_BE_TRUE(!(arg_smaller > arg_bigger));
    MUST_BE_TRUE(!(arg_smaller > arg_smaller));

    // NoopParameter<T> vs. const T
    MUST_BE_TRUE(bigger > arg_smaller);
    MUST_BE_TRUE(!(arg_smaller > bigger));
    MUST_BE_TRUE(!(arg_smaller > arg_smaller));

    // const T vs. NoopParameter<T>
    MUST_BE_TRUE(arg_bigger > smaller);
    MUST_BE_TRUE(!(smaller > arg_bigger));
    MUST_BE_TRUE(!(smaller > smaller));

    return Test::PASSED;
}

//=============================================================================================
template <class T>
Test::Result Configuration::Parameter_test::OperatorLessThanOrEqualTo::test(const T& smaller,
                                                                            const T& bigger)
{
    NoopParameter<T> arg_smaller(smaller);
    NoopParameter<T> arg_bigger(bigger);

    // NoopParameter<T> vs. NoopParameter<T>
    MUST_BE_TRUE(arg_smaller <= arg_bigger);
    MUST_BE_TRUE(!(arg_bigger <= arg_smaller));
    MUST_BE_TRUE(arg_smaller <= arg_smaller);

    // NoopParameter<T> vs. const T
    MUST_BE_TRUE(arg_smaller <= bigger);
    MUST_BE_TRUE(!(bigger <= arg_smaller));
    MUST_BE_TRUE(arg_smaller <= arg_smaller);

    // const T vs. NoopParameter<T>
    MUST_BE_TRUE(smaller <= arg_bigger);
    MUST_BE_TRUE(!(arg_bigger <= smaller));
    MUST_BE_TRUE(smaller <= smaller);

    return Test::PASSED;
}

//=============================================================================================
template <class T> Test::Result
Configuration::Parameter_test::OperatorGreaterThanOrEqualTo::test(const T& smaller,
                                                                  const T& bigger)
{
    NoopParameter<T> arg_smaller(smaller);
    NoopParameter<T> arg_bigger(bigger);

    // NoopParameter<T> vs. NoopParameter<T>
    MUST_BE_TRUE(arg_bigger >= arg_smaller);
    MUST_BE_TRUE(!(arg_smaller >= arg_bigger));
    MUST_BE_TRUE(arg_smaller >= arg_smaller);

    // NoopParameter<T> vs. const T
    MUST_BE_TRUE(bigger >= arg_smaller);
    MUST_BE_TRUE(!(arg_smaller >= bigger));
    MUST_BE_TRUE(arg_smaller >= arg_smaller);

    // const T vs. NoopParameter<T>
    MUST_BE_TRUE(arg_bigger >= smaller);
    MUST_BE_TRUE(!(smaller >= arg_bigger));
    MUST_BE_TRUE(smaller >= smaller);

    return Test::PASSED;
}

//=============================================================================================
template <class T> Test::Result Configuration::Parameter_test::OperatorEquality::test(
    const T& smaller, const T& bigger)
{
    NoopParameter<T> arg_smaller(smaller);
    NoopParameter<T> arg_bigger(bigger);

    // NoopParameter<T> vs. NoopParameter<T>
    MUST_BE_TRUE(arg_smaller == arg_smaller);
    MUST_BE_TRUE(!(arg_smaller == arg_bigger));

    // NoopParameter<T> vs. const T
    MUST_BE_TRUE(arg_smaller == arg_smaller);
    MUST_BE_TRUE(!(arg_smaller == bigger));

    // const T vs. NoopParameter<T>
    MUST_BE_TRUE(smaller == smaller);
    MUST_BE_TRUE(!(smaller == arg_bigger));

    return Test::PASSED;
}

//=============================================================================================
template <class T> Test::Result Configuration::Parameter_test::OperatorNotEqual::test(
    const T& smaller, const T& bigger)
{
    NoopParameter<T> arg_smaller(smaller);
    NoopParameter<T> arg_bigger(bigger);

    // NoopParameter<T> vs. NoopParameter<T>
    MUST_BE_TRUE(arg_smaller != arg_bigger);
    MUST_BE_TRUE(!(arg_smaller != arg_smaller));

    // NoopParameter<T> vs. const T
    MUST_BE_TRUE(arg_smaller != bigger);
    MUST_BE_TRUE(!(arg_smaller != arg_smaller));

    // const T vs. NoopParameter<T>
    MUST_BE_TRUE(smaller != arg_bigger);
    MUST_BE_TRUE(!(smaller != smaller));

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::Bool::body()
{
    return test<bool>(false, true);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::String::body()
{
    return test<std::string>("", "1234");
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::Char::body()
{
    return test<char>(0, '1');
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::Double::body()
{
    return test<double>(0, 111.0);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::Float::body()
{
    return test<float>(0, 111.0f);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::Int::body()
{
    return test<int>(0, 111);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::Long::body()
{
    return test<long>(0, 111L);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::LongDouble::body()
{
    return test<long double>(0, 111.0L);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::LongLong::body()
{
    return test<long long>(0, 111LL);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::Short::body()
{
    return test<short>(0, static_cast<short>(111));
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::UnsignedChar::body()
{
    return test<unsigned char>(0, static_cast<unsigned char>('1'));
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::UnsignedInt::body()
{
    return test<unsigned int>(0, 111U);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::UnsignedLong::body()
{
    return test<unsigned long>(0, 111);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 111ULL);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::SetValue::UnsignedShort::body()
{
    return test<unsigned short>(0, static_cast<unsigned short>(111));
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThan::Bool::body()
{
    return test<bool>(false, true);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThan::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    NoopParameter<std::string> smaller_arg(smaller);
    NoopParameter<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(smaller < bigger_arg);
    MUST_BE_TRUE(smaller_arg < bigger);
    MUST_BE_TRUE(!(smaller_arg < smaller));

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThan::String::body()
{
    return test<std::string>("abcd", "efgh");
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThan::Char::body()
{
    return test<char>('a', 'b');
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThan::Double::body()
{
    return test<double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThan::Float::body()
{
    return test<float>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThan::Int::body()
{
    return test<int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThan::Long::body()
{
    return test<long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThan::LongDouble::body()
{
    return test<long double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThan::LongLong::body()
{
    return test<long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThan::Short::body()
{
    return test<short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThan::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThan::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThan::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThan::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThan::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThan::Bool::body()
{
    return test<bool>(false, true);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThan::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    NoopParameter<std::string> smaller_arg(smaller);
    NoopParameter<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(bigger_arg > smaller);
    MUST_BE_TRUE(bigger > smaller_arg);
    MUST_BE_TRUE(!(bigger > bigger_arg));

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThan::String::body()
{
    return test<std::string>("abcd", "efgh");
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThan::Char::body()
{
    return test<char>('a', 'b');
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThan::Double::body()
{
    return test<double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThan::Float::body()
{
    return test<float>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThan::Int::body()
{
    return test<int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThan::Long::body()
{
    return test<long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThan::LongDouble::body()
{
    return test<long double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThan::LongLong::body()
{
    return test<long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThan::Short::body()
{
    return test<short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThan::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThan::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThan::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThan::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThan::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThanOrEqualTo::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    NoopParameter<std::string> smaller_arg(smaller);
    NoopParameter<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(smaller <= bigger_arg);
    MUST_BE_TRUE(smaller_arg <= bigger);
    MUST_BE_TRUE(smaller_arg <= smaller);

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThanOrEqualTo::String::body()
{
    return test<std::string>("abcd", "efgh");
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThanOrEqualTo::Char::body()
{
    return test<char>('a', 'b');
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThanOrEqualTo::Double::body()
{
    return test<double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThanOrEqualTo::Float::body()
{
    return test<float>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThanOrEqualTo::Int::body()
{
    return test<int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThanOrEqualTo::Long::body()
{
    return test<long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThanOrEqualTo::LongDouble::body()
{
    return test<long double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThanOrEqualTo::LongLong::body()
{
    return test<long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThanOrEqualTo::Short::body()
{
    return test<short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThanOrEqualTo::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThanOrEqualTo::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThanOrEqualTo::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThanOrEqualTo::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorLessThanOrEqualTo::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
}

//=============================================================================================
Test::Result
Configuration::Parameter_test::OperatorGreaterThanOrEqualTo::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    NoopParameter<std::string> smaller_arg(smaller);
    NoopParameter<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(bigger >= smaller_arg);
    MUST_BE_TRUE(bigger_arg  >= smaller);
    MUST_BE_TRUE(smaller_arg >= smaller);

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThanOrEqualTo::String::body()
{
    return test<std::string>("abcd", "efgh");
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThanOrEqualTo::Char::body()
{
    return test<char>('a', 'b');
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThanOrEqualTo::Double::body()
{
    return test<double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThanOrEqualTo::Float::body()
{
    return test<float>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThanOrEqualTo::Int::body()
{
    return test<int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThanOrEqualTo::Long::body()
{
    return test<long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThanOrEqualTo::LongDouble::body()
{
    return test<long double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThanOrEqualTo::LongLong::body()
{
    return test<long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThanOrEqualTo::Short::body()
{
    return test<short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThanOrEqualTo::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThanOrEqualTo::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThanOrEqualTo::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

//=============================================================================================
Test::Result
Configuration::Parameter_test::OperatorGreaterThanOrEqualTo::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorGreaterThanOrEqualTo::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorEquality::Bool::body()
{
    return test<bool>(false, true);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorEquality::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    NoopParameter<std::string> smaller_arg(smaller);
    NoopParameter<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(bigger == bigger_arg);
    MUST_BE_TRUE(bigger_arg == bigger);

    MUST_BE_TRUE(!(bigger == smaller_arg));
    MUST_BE_TRUE(!(bigger_arg == smaller));

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorEquality::String::body()
{
    return test<std::string>("abcd", "efgh");
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorEquality::Char::body()
{
    return test<char>('a', 'b');
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorEquality::Double::body()
{
    return test<double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorEquality::Float::body()
{
    return test<float>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorEquality::Int::body()
{
    return test<int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorEquality::Long::body()
{
    return test<long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorEquality::LongDouble::body()
{
    return test<long double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorEquality::LongLong::body()
{
    return test<long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorEquality::Short::body()
{
    return test<short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorEquality::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorEquality::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorEquality::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorEquality::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorEquality::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorNotEqual::Bool::body()
{
    return test<bool>(false, true);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorNotEqual::StringConstCharP::body()
{
    const char* smaller = "abcd";
    const char* bigger  = "efgh";

    NoopParameter<std::string> smaller_arg(smaller);
    NoopParameter<std::string> bigger_arg(bigger);

    MUST_BE_TRUE(bigger != smaller_arg);
    MUST_BE_TRUE(bigger_arg != smaller);

    MUST_BE_TRUE(!(bigger != bigger_arg));
    MUST_BE_TRUE(!(bigger_arg != bigger));

    return Test::PASSED;
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorNotEqual::String::body()
{
    return test<std::string>("abcd", "efgh");
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorNotEqual::Char::body()
{
    return test<char>('a', 'b');
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorNotEqual::Double::body()
{
    return test<double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorNotEqual::Float::body()
{
    return test<float>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorNotEqual::Int::body()
{
    return test<int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorNotEqual::Long::body()
{
    return test<long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorNotEqual::LongDouble::body()
{
    return test<long double>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorNotEqual::LongLong::body()
{
    return test<long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorNotEqual::Short::body()
{
    return test<short>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorNotEqual::UnsignedChar::body()
{
    return test<unsigned char>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorNotEqual::UnsignedInt::body()
{
    return test<unsigned int>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorNotEqual::UnsignedLong::body()
{
    return test<unsigned long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorNotEqual::UnsignedLongLong::body()
{
    return test<unsigned long long>(0, 1);
}

//=============================================================================================
Test::Result Configuration::Parameter_test::OperatorNotEqual::UnsignedShort::body()
{
    return test<unsigned short>(0, 1);
}