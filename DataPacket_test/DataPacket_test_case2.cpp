#include <cstring>
#include <iostream>

#include "DataPacket_test_case2.hpp"

#include "DataPacket.hpp"
#include "DataPacket_test1.hpp"
#include "DataPacket_test2.hpp"
#include "Test.hpp"
#include "TestMacros.hpp"

TEST_CONSTRUCTOR_DESTRUCTOR(DataPacket_test_case2);

//==============================================================================
Test::Result DataPacket_test_case2::run()
{
    // Initialize with some dummy data; will check for proper byteswappng later
    DataPacket_test2 dptest2(1.0f, 2.0f, 'A');
    DataPacket_test1 dptest1(3, 4.0, dptest2);

    // dptest2 data is copied to here; dptest2 is not referenced again
    DataPacket_test2* dptest2p = dptest1.getNestedPacket();

    dptest1.setByteAlignment(3);
    dptest2p->setByteAlignment(3);

    // Write out dptest1 with a 3-byte alignment and make sure it looks
    // alright.  Write is done in host byte order.
    unsigned char* raw_dptest1 = new unsigned char[dptest1.getLengthBytes()];
    dptest1.writeRaw(raw_dptest1);

    unsigned int offset = 0;

    // Grab sdf_int; it should be at the very beginning of the raw packet
    int dptest1_int;
    int dptest1_int_updated;
    pullUpdatePush(raw_dptest1, dptest1_int, dptest1_int_updated, offset);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab sdf_double; it should be right after sdf_int, which means an offset
    // of sizeof(int)
    double dptest1_double;
    double dptest1_double_updated;
    pullUpdatePush(raw_dptest1, dptest1_double, dptest1_double_updated, offset);

    // Should be 1 byte of padding here
    offset += 1;

    // Grab sdf_float1 from the nested packet; it should be right after all the
    // fields in the top-level packet, since we're still aligned on 4 bytes
    float dptest2_float1;
    float dptest2_float1_updated;
    pullUpdatePush(raw_dptest1, dptest2_float1, dptest2_float1_updated, offset);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab the character out of the nested packet and push an updated and
    // byteswapped copy of it into its place.  readRaw() will read this out
    // later, hopefully correctly.
    float dptest2_float2;
    float dptest2_float2_updated;
    pullUpdatePush(raw_dptest1, dptest2_float2, dptest2_float2_updated, offset);

    // Should be 2 bytes of padding here
    offset += 2;

    // Grab the character out of the nested packet and push an updated and
    // byteswapped copy of it into its place.  readRaw() will read this out
    // later, hopefully correctly.
    char dptest2_char;
    char dptest2_char_updated;
    pullUpdatePush(raw_dptest1, dptest2_char, dptest2_char_updated, offset);

    // All the values we copied out of the raw packet have to match the values
    // we originally set them to
    MUST_BE_TRUE(dptest1_int    == dptest1.getSdfInt());
    MUST_BE_TRUE(dptest1_double == dptest1.getSdfDouble());
    MUST_BE_TRUE(dptest2_float1 == dptest2p->getSdfFloat1());
    MUST_BE_TRUE(dptest2_float2 == dptest2p->getSdfFloat2());
    MUST_BE_TRUE(dptest2_char   == dptest2p->getSdfChar());

    // Read the updated raw data and compare against the updated values
    dptest1.readRaw(raw_dptest1);

    // All the values we wrote into the raw packet have to match the values we
    // retrieved after reading the raw packet
    MUST_BE_TRUE(dptest1_int_updated    == dptest1.getSdfInt());
    MUST_BE_TRUE(dptest1_double_updated == dptest1.getSdfDouble());
    MUST_BE_TRUE(dptest2_float1_updated == dptest2p->getSdfFloat1());
    MUST_BE_TRUE(dptest2_float2_updated == dptest2p->getSdfFloat2());
    MUST_BE_TRUE(dptest2_char_updated   == dptest2p->getSdfChar());

    delete [] raw_dptest1;

    return Test::PASSED;
}

//==============================================================================
// Does a couple things for hard-to-understand reasons.
//
// First we pull what we pull a T out of the memory starting at raw_dptest +
// offset (this function is used multiple times in succession and, as can be
// seen on the last line, offset is bumped each time, meaning a new section of
// memory is read each time).  This value is then left alone to be
// returned in the "dptest_var" argument.
//
// Second, we save a copy of an incremented "dptest_var" into
// "dptest_var_updated", meaning the memory location is now incremented but
// otherwise unchanged.  Later, readRaw() will read this, and we can test for
// presence of the incremented value.
//
// Lastly, offset is bumped past the memory location we read with it to prepare
// for its next usage.
//==============================================================================
template <class T>
void DataPacket_test_case2::pullUpdatePush(unsigned char* raw_dptest,
                                           T&             dptest_var,
                                           T&             dptest_var_updated,
                                           unsigned int&  offset)
{
    // Pull a field from the raw packet and swap to make it legible
    memcpy(&dptest_var, raw_dptest + offset, sizeof(T));

    // Increment the retrieved field but store it in a different place
    dptest_var_updated = dptest_var + 1;

    memcpy(raw_dptest + offset,
           reinterpret_cast<unsigned char*>(&dptest_var_updated),
           sizeof(T));

    // Bump this for successive calls
    offset += sizeof(T);
}