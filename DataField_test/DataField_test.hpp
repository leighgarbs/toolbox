#if !defined DATA_FIELD_TEST
#define DATA_FIELD_TEST

#include <cstdint>

#include "Test.hpp"
#include "TestMacros.hpp"

TEST_CASES_BEGIN(DataField_test)

    // Tests the writeRaw const member function
    TEST_CASES_BEGIN(WriteRawConst)

        TEST(Byte1)
        TEST(Byte2)
        TEST(Byte4)

        template <class T> static Test::Result writeRawSlidingWindow();

    TEST_CASES_END(WriteRawConst)

    // Tests the readRaw member function
    TEST_CASES_BEGIN(ReadRaw)

        TEST(Byte1)
        TEST(Byte2)
        TEST(Byte4)

        template <class T> static Test::Result readRawSlidingWindow();

    TEST_CASES_END(ReadRaw)

    // Tests the readRaw member function that takes a const buffer
    TEST_CASES_BEGIN(ReadRawConstBuffer)

        TEST(Byte1)
        TEST(Byte2)
        TEST(Byte4)

        template <class T> static Test::Result readRawSlidingWindow();

    TEST_CASES_END(ReadRawConstBuffer)

    // Tests the normalizeMemoryLocation member function
    TEST_CASES_BEGIN(NormalizeMemoryLocation)

        TEST(Buffer0Bits0)
        TEST(Buffer0Bits8)
        TEST(Buffer1Bits16)
        TEST(Buffer2Bits404)

    TEST_CASES_END(NormalizeMemoryLocation)

    TEST_CASES_BEGIN(NormalizeMemoryLocationConst)

        TEST(Buffer0Bits0)
        TEST(Buffer0Bits8)
        TEST(Buffer1Bits16)
        TEST(Buffer2Bits404)

    TEST_CASES_END(NormalizeMemoryLocationConst)

    static Test::Result NML_BufferBits(std::uint8_t* buffer_before,
                                       unsigned long bits_before,
                                       std::uint8_t* buffer_after,
                                       unsigned long bits_after);

    static Test::Result NML_BufferBitsConst(std::uint8_t* buffer_before,
                                            unsigned long bits_before,
                                            std::uint8_t* buffer_after,
                                            unsigned long bits_after);

TEST_CASES_END(DataField_test)

#endif
