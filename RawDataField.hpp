#if !defined RAW_DATA_FIELD_HPP
#define RAW_DATA_FIELD_HPP

#include <bitset>
#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <string>

#include "DataField.hpp"

#include "misc.hpp"

class RawDataField : public DataField
{
public:

    // Possible settings for data indexing.  "MS_ZERO" stands for "Most
    // Significant Zero" and means the most significant data unit is assigned
    // index 0.  "LS_ZERO" stands for "Least Significant Zero" and means the
    // least significant data unit is assigned index 0.  The rest of the indices
    // are assigned in order of increasing or decreasing significance as
    // expected.
    enum DataIndexingMode
    {
        MS_ZERO,
        LS_ZERO
    };

    // Dynamically allocates and maintains data field of size "length".  Units
    // of length are specified in "length_units".  Storage is dynamically
    // allocated.
    // cppcheck-suppress noExplicitConstructor
    RawDataField(unsigned long    length,
                 misc::DataUnits  length_units,
                 DataIndexingMode bit_indexing_mode = LS_ZERO);

    // Behavior depends on the value of "memory_internal".  If "memory_internal"
    // is true, the data at "buffer" of will be copied into dynamically
    // allocated memory internal to this class.  If "memory_internal" is false,
    // the data at "buffer" will be used by this class in-place and no dynamic
    // memory allocation will occur.
    RawDataField(std::uint8_t*    buffer,
                 unsigned long    length,
                 misc::DataUnits  length_units,
                 bool             memory_internal = true,
                 DataIndexingMode bit_indexing_mode = LS_ZERO);

    // Copy constructor; dynamically allocates and maintains a bit field that is
    // "length_bytes" in size, and then copies the given bit field into this
    // newly-allocated memory.
    RawDataField(const RawDataField& raw_data_field);

    // Will free the memory at "raw_data" if it is owned by this class
    virtual ~RawDataField();

    // Reads from the "buffer" memory location plus an offset of "bit_offset"
    // bits.  No byteswapping is performed even when "source_byte_order" doesn't
    // match host byte ordering, since this is just raw data.
    virtual unsigned long readRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder source_byte_order,
                                  unsigned long   offset_bits = 0);

    // Writes to the "buffer" memory location plus an offset of "bit_offset"
    // bits.  No byteswapping is performed even when "source_byte_order" doesn't
    // match host byte ordering, since this is just raw data.
    virtual unsigned long writeRaw(std::uint8_t*   buffer,
                                   misc::ByteOrder destination_byte_order,
                                   unsigned long   offset_bits = 0) const;

    // Octet access or mutation, indexed by (obviously) octet
    std::uint8_t getByte(unsigned int index) const;
    void setByte(unsigned int index, std::uint8_t value);

    // Bit access or mutation, indexed by bit
    bool getBit(unsigned long index) const;
    void setBit(unsigned long index, bool value);

    // Copies a range of bits into the given typed numeric variable.  Useful for
    // pulling things like integers and floating-point numbers out of bitfields.
    // Bit numbering follows the convention used by getBit().  Operation starts
    // by copying the least significant bit in the specified range into the
    // least significant bit in "type_var", and proceeds to successively more
    // significant bits until "count" bits are copied.
    template <class T> void getBitsAsNumericType(
        T&           type_var,
        unsigned int start_bit = 0,
        unsigned int count     = sizeof(T) * BITS_PER_BYTE) const;

    // Copies a range of bits from the given typed numeric variable.  Useful for
    // pushing things like integers and floating-point numbers into bitfields.
    // Bit numbering follows the convention used by getBit().  Operation starts
    // by copying the least significant bit in the typed numeric variable into
    // the least significant bit in the specified range, and proceeds to
    // successively more significant bits until "count" bits are copied.
    template <class T> void setBitsAsNumericType(
        T            type_var,
        unsigned int start_bit = 0,
        unsigned int count     = sizeof(T) * BITS_PER_BYTE);

    // Bits shift toward the most significant bit, if this bitfield were
    // interpreted as one big integer
    void shiftLeft(unsigned int shift_bits);

    // Bits shift toward the least significant bit, if this bitfield were
    // interpreted as one big integer
    void shiftRight(unsigned int shift_bits);

    // Returns the size of this field in bits.  This will equal the number of
    // bits written by writeRaw() and read by readRaw().
    virtual unsigned long getLengthBits() const;

    // Simple accessor for memory_internal
    bool getMemoryInternal() const;

    // Indexing mode access
    DataIndexingMode getBitIndexingMode() const;

    // Indexing mode mutator
    void setBitIndexingMode(DataIndexingMode bit_indexing_mode);

    RawDataField& operator=(const RawDataField& raw_data_field);

    // Uses leftShift()
    RawDataField& operator<<=(unsigned int shift_bits);

    // Uses rightShift()
    RawDataField& operator>>=(unsigned int shift_bits);

protected:

    // Tosses a std::out_of_range exception if index >= size
    static void throwIfIndexOutOfRange(unsigned long index, unsigned long size);

private:

    // Only for use as a delegating constructor.  Sets length_bits and indexing
    // mode.
    RawDataField(unsigned long    length,
                 misc::DataUnits  length_units,
                 bool             memory_internal,
                 DataIndexingMode bit_indexing_mode);

    // Reference to the raw data represented by this class
    std::uint8_t* raw_data;

    // Field is this many bits in length
    unsigned long length_bits;

    // Does this class own the memory at "raw_data"?
    bool memory_internal;

    // How are we indexing into the raw data
    DataIndexingMode bit_indexing_mode;
};

//==============================================================================
inline unsigned long RawDataField::getLengthBits() const
{
    return length_bits;
}

//==============================================================================
inline bool RawDataField::getMemoryInternal() const
{
    return memory_internal;
}

//==============================================================================
inline RawDataField::DataIndexingMode RawDataField::getBitIndexingMode() const
{
    return bit_indexing_mode;
}

//==============================================================================
inline void RawDataField::setBitIndexingMode(
    RawDataField::DataIndexingMode bit_indexing_mode)
{
    this->bit_indexing_mode = bit_indexing_mode;
}

//==============================================================================
inline void RawDataField::throwIfIndexOutOfRange(unsigned long index,
                                                 unsigned long size)
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
}

bool operator==(const RawDataField& lhs, const RawDataField& rhs);
bool operator!=(const RawDataField& lhs, const RawDataField& rhs);

RawDataField operator>>(const RawDataField& lhs, unsigned int rhs);
RawDataField operator<<(const RawDataField& lhs, unsigned int rhs);

#endif