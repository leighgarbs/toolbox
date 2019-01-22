#if !defined DATA_PACKET_HPP
#define DATA_PACKET_HPP

#include <stdexcept>
#include <cstdint>
#include <vector>

#include "DataField.hpp"

#include "misc.hpp"

class DataPacket : public DataField
{
public:

    // Initializes byte alignment
    explicit DataPacket(unsigned int bit_alignment = 8);

    // Does nothing
    virtual ~DataPacket();

    // Reads the data field from the "buffer" memory location without
    // considering byte ordering.
    virtual unsigned int readRaw(const std::uint8_t* buffer,
                                 unsigned int        bit_offset = 0);

    // Reads this data packet from the "buffer" memory location.  Each field
    // will be byteswapped if its source byte order does not match the byte
    // ordering of the host.
    virtual unsigned int readRaw(const std::uint8_t* buffer,
                                 misc::ByteOrder     source_byte_order,
                                 unsigned int        bit_offset = 0);

    // Writes the data field to the "buffer" memory location without considering
    // byte ordering.
    virtual unsigned int writeRaw(std::uint8_t* buffer,
                                  unsigned int  bit_offset = 0) const;

    // Writes this data packet to the "buffer" memory location.  Each field will
    // be byteswapped if its source byte order does not match the byte ordering
    // of the host.
    virtual unsigned int writeRaw(std::uint8_t*   buffer,
                                  misc::ByteOrder destination_byte_order,
                                  unsigned int    bit_offset = 0) const;

    // Returns the size of this field in bytes.  This will equal the number of
    // bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getLengthBits() const;

    // Byte alignment access
    unsigned int getBitAlignment() const;

    // Byte alignment mutator
    void setBitAlignment(unsigned int bit_alignment);

protected:

    // Adds the field to the end of the packet.  The field is not maintained
    // internally, only its order relative to other fields in this packet is.
    void addDataField(DataField* data_field);

private:

    // Derived classes should use this to add all their data fields
    virtual void addDataFields() = 0;

    // Computes amount of padding needed after a field given the current byte
    // alignment setting
    unsigned int computePaddingBits(unsigned int offset_bits,
                                    unsigned int field_length_bits) const;

    // All contained data fields ordered first to last
    std::vector<DataField*> data_fields;

    unsigned int bit_alignment;

    // A meaningful deep copy can't be done here so disallow that and operator=
    DataPacket(const DataPacket&);
    DataPacket& operator=(const DataPacket&);
};

inline unsigned int DataPacket::getBitAlignment() const
{
    return bit_alignment;
}

inline void DataPacket::setBitAlignment(unsigned int bit_alignment)
{
    if (bit_alignment == 0)
    {
        throw std::invalid_argument(
            "Nonsensical byte alignment value of 0 specified (must be 1 or "
            "greater)");
    }

    this->bit_alignment = bit_alignment;
}

inline void DataPacket::addDataField(DataField* data_field)
{
    data_fields.push_back(data_field);
}

#endif
