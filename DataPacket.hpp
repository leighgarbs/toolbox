#if !defined DATA_PACKET_HPP
#define DATA_PACKET_HPP

#include <cstdint>
#include <cstdlib>
#include <list>
#include <stdexcept>

#include "DataField.hpp"

#include "misc.hpp"

// Represents a data field that contains other data fields.  Supports byte-wise
// or bit-wise alignment of contained fields in memory.
class DataPacket : public DataField
{
public:

    // Initializes alignment; defaults align contained data fields on 1 byte
    DataPacket(unsigned int    alignment = 1,
               misc::DataUnits alignment_units = misc::BYTES);

    // Does nothing
    virtual ~DataPacket();

    // Reads all contained data packets in the order they were added from the
    // "buffer" memory location.  Each field is byteswapped if
    // "source_byte_order" doesn't match host byte ordering.
    virtual unsigned long readRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder source_byte_order);

    // Const-compatible version of the above member function
    virtual unsigned long readRaw(const std::uint8_t* buffer,
                                  misc::ByteOrder     source_byte_order);

    // Writes all contained data packets in the order they were added to the
    // "buffer" memory location.  Each field is byteswapped if
    // "destination_byte_order" doesn't match host byte ordering.
    virtual unsigned long writeRaw(
        std::uint8_t*   buffer,
        misc::ByteOrder destination_byte_order) const;

    // Returns the size of this field in bits.  This will equal the number of
    // bits written by writeRaw() and read by readRaw().
    virtual unsigned long getLengthBits() const;

    // Alignment access
    unsigned int
    getAlignment(misc::DataUnits alignment_units = misc::BYTES) const;

    // Alignment mutator
    void setAlignment(unsigned int    alignment,
                      misc::DataUnits alignment_units = misc::BYTES);

protected:

    // Adds a data field to the end of this packet.  Contained data fields are
    // read and written in added order.  Data packets do not take ownership of
    // added data fields.  Data packets do not delete added data fields.
    void addDataField(DataField* data_field);

private:

    // All contained data fields ordered first to last
    std::list<DataField*> data_fields;

    unsigned int alignment_bits;

    // A meaningful deep copy can't be done here so disallow that and operator=
    DataPacket(const DataPacket&);
    DataPacket& operator=(const DataPacket&);
};

//==============================================================================
inline
unsigned int DataPacket::getAlignment(misc::DataUnits alignment_units) const
{
    if (alignment_units == misc::BITS)
    {
        // This is easy since we store alignment in bits already
        return alignment_bits;
    }
    else if (alignment_units == misc::BYTES)
    {
        // Convert bits to bytes.  If it's not an even conversion then return
        // the smallest number of bytes that can store all the bits.
        std::ldiv_t div_result = std::ldiv(alignment_units, BITS_PER_BYTE);
        if (div_result.rem > 0)
        {
            div_result.quot += 1;
        }
        return static_cast<unsigned int>(div_result.quot);
    }
    else
    {
        throw std::invalid_argument("Unsupported units type");
    }
}

//==============================================================================
inline void DataPacket::setAlignment(unsigned int    alignment,
                                     misc::DataUnits alignment_units)
{
    if (alignment == 0)
    {
        throw std::invalid_argument("Alignment must be greater than 0");
    }

    if (alignment_units == misc::BITS)
    {
        alignment_bits = alignment;
    }
    else if (alignment_units == misc::BYTES)
    {
        // Convert to bits
        alignment_bits = alignment * BITS_PER_BYTE;
    }
    else
    {
        throw std::invalid_argument("Unsupported units type");
    }
}

//==============================================================================
inline void DataPacket::addDataField(DataField* data_field)
{
    data_fields.push_back(data_field);
}

#endif
