#if !defined NETWORK_ADDRESS_HPP
#define NETWORK_ADDRESS_HPP

#include <stdexcept>
#include <string>

#include "DataField.hpp"
#include "MemoryMode.hpp"

#include "misc.hpp"

class NetworkAddress : public DataField
{
public:

    // Will dynamically allocate an address that is "length_bytes" in size.
    // Implies MemoryMode::INTERNAL.
    // cppcheck-suppress noExplicitConstructor
    NetworkAddress(unsigned int length_bytes);

    // Behavior depends on the value of "memory_mode".  If "memory_mode" is
    // MemoryMode::INTERNAL, the data at "buffer" of length "length_bytes" will
    // be copied into dynamically-allocated memory internal to this class.  If
    // "memory_mode" is MemoryMode::EXTERNAL, the data at "buffer" of length
    // "length_bytes" will be used by this class in-place and no dynamic memory
    // allocation will occur.
    NetworkAddress(unsigned char* buffer,
                   unsigned int   length_bytes,
                   MemoryMode     memory_mode);

    // Copy constructor; will dynamically allocate memory for the
    // "network_address_raw" stored in the new NetworkAddress
    NetworkAddress(const NetworkAddress& network_address);

    // Will free the memory at "raw_network_address" if it is owned by this
    // class
    virtual ~NetworkAddress();

    // Reads a raw network address from the "buffer" memory location without
    // considering byte ordering.  Byte ordering has seemingly no relevance to
    // network addresses (in the general sense of the term) anyway.
    virtual unsigned int readRaw(const unsigned char* buffer);

    // Reads a raw network address from the "buffer" memory location.  This
    // function is required by the framework to be implemented here, despite
    // being functionally identical to the single-argument version defined
    // above.  If byte ordering were relevant to network addresses (in the
    // general sense of the term) this function would be where that difference
    // would be handled.
    virtual unsigned int readRaw(const unsigned char* buffer,
                                 misc::ByteOrder      source_byte_order);

    // Writes a raw network address from the "buffer" memory location without
    // considering byte ordering.  Byte ordering has seemingly no relevance to
    // network addresses (in the general sense of the term) anyway.
    virtual unsigned int writeRaw(unsigned char* buffer) const;

    // Writes a raw network address from the "buffer" memory location.  This
    // function is required by the framework to be implemented here, despite being
    // functionally identical to the single-argument version defined above.  If
    // byte ordering were relevant to network addresses (in the general sense of
    // the term) this function would be where that difference would be handled.
    virtual unsigned int writeRaw(unsigned char*  buffer,
                                  misc::ByteOrder destination_byte_order) const;

    // Octet access
    unsigned char getOctet(unsigned int octet) const;

    // Octet mutation
    void setOctet(unsigned int octet, unsigned char value);

    // Returns the size of this data field in bytes.  This will equal the number
    // of bytes written by writeRaw() and read by readRaw().
    virtual unsigned int getLengthBytes() const;

    NetworkAddress& operator=(const NetworkAddress& network_address);

private:

    // Raw network address is stored at this location
    unsigned char* network_address_raw;

    // Raw network address is this many bytes in length
    unsigned int length_bytes;

    // Does this class own the memory at "network_address_raw"?
    MemoryMode memory_mode;
};

inline unsigned char NetworkAddress::getOctet(unsigned int octet) const
{
    if (octet >= length_bytes)
    {
        throw std::out_of_range("Out-of-range octet specified");
    }

    return network_address_raw[octet];
}

inline void NetworkAddress::setOctet(unsigned int octet, unsigned char value)
{
    if (octet >= length_bytes)
    {
        throw std::out_of_range("Out-of-range octet specified");
    }

    network_address_raw[octet] = value;
}

inline unsigned int NetworkAddress::getLengthBytes() const
{
    return length_bytes;
}

bool operator==(const NetworkAddress& network_address1,
                const NetworkAddress& network_address2);

bool operator!=(const NetworkAddress& network_address1,
                const NetworkAddress& network_address2);

#endif
