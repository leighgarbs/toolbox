#include <cstring>
#include <new>

#include "NetworkAddress.hpp"

#include "DataField.hpp"
#include "misc.hpp"

//==============================================================================
// Dynamically allocates an address that is "length_bytes" in size
//==============================================================================
NetworkAddress::NetworkAddress(unsigned int length_bytes) :
    DataField(),
    length_bytes(length_bytes),
    network_address_raw_owned(true)
{
    network_address_raw = new unsigned char[length_bytes];
    memset(network_address_raw, 0, length_bytes);
}

//==============================================================================
// Uses the memory at "buffer" (of size "length_bytes") as the raw network
// address; does not dynamically allocate memory
//==============================================================================
NetworkAddress::NetworkAddress(unsigned char* buffer,
                               unsigned int   length_bytes) :
    DataField(),
    network_address_raw(buffer),
    length_bytes(length_bytes),
    network_address_raw_owned(false)
{
}

//==============================================================================
// Copy constructor; will dynamically allocate memory for the
// "network_address_raw" stored in the new NetworkAddress
//==============================================================================
NetworkAddress::NetworkAddress(const NetworkAddress& network_address) :
    DataField(),
    network_address_raw_owned(true)
{
    length_bytes = network_address.getLengthBytes();

    network_address_raw = new unsigned char[length_bytes];

    network_address.writeRaw(network_address_raw);
}

//==============================================================================
// Frees the memory at "network_address_raw" if owned by this class
//==============================================================================
NetworkAddress::~NetworkAddress()
{
    if (network_address_raw_owned)
    {
        delete[] network_address_raw;
    }
}

//==============================================================================
// Reads a raw network address from the "buffer" memory location.
//==============================================================================
unsigned int NetworkAddress::readRaw(const unsigned char* buffer)
{
    return DataField::readRaw(buffer);
}

//==============================================================================
// Reads a raw network address from the "buffer" memory location.
//==============================================================================
unsigned int NetworkAddress::readRaw(const unsigned char* buffer,
                                     misc::ByteOrder      source_byte_order)
{
    // Byteswapping doesn't seem to be a relevant operation on network addresses
    // in the general sense of the term
    memcpy(network_address_raw, buffer, length_bytes);
    return length_bytes;
}

//==============================================================================
// Writes a raw network address from the "buffer" memory location.
//==============================================================================
unsigned int NetworkAddress::writeRaw(unsigned char* buffer) const
{
    return DataField::writeRaw(buffer);
}

//==============================================================================
// Writes a raw network address from the "buffer" memory location.
//==============================================================================
unsigned int
NetworkAddress::writeRaw(unsigned char*  buffer,
                         misc::ByteOrder destination_byte_order) const
{
    // Byteswapping doesn't seem to be a relevant operation on network addresses
    // in the general sense of the term
    memcpy(buffer, network_address_raw, length_bytes);
    return length_bytes;
}

//==============================================================================
// Assigns a NetworkAddress to this NetworkAddress
//==============================================================================
NetworkAddress& NetworkAddress::operator=(const NetworkAddress& network_address)
{
    network_address.writeRaw(network_address_raw);
    return *this;
}

//==============================================================================
// Equality comparison, NetworkAddress == NetworkAddress
//==============================================================================
bool operator==(const NetworkAddress& network_address1,
                const NetworkAddress& network_address2)
{
    if (network_address1.getLengthBytes() != network_address2.getLengthBytes())
    {
        return false;
    }

    // We know both addresses have equal length at this point
    unsigned int length_bytes = network_address1.getLengthBytes();

    for (unsigned int i = 0; i < length_bytes; i++)
    {
        if (network_address1.getOctet(i) != network_address2.getOctet(i))
        {
            return false;
        }
    }

    return true;
}

//==============================================================================
// Inequality comparison, NetworkAddress != NetworkAddress
//==============================================================================
bool operator!=(const NetworkAddress& network_address1,
                const NetworkAddress& network_address2)
{
    return !(network_address1 == network_address2);
}
