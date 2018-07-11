// TCP packet header

#if !defined(TCP_HEADER_H)
#define TCP_HEADER_H

struct tcp_header
{
    // Source port
    char source_port[2];

    // Destination port
    char destination_port[2];

    // Sequence number
    char sequence_num[4];

    // Acknowledgement number (if ACK set)
    char ack_num[4];

    // Bits 0-3: data offset; bits 4-6: reserved
    // bit 7:  NS
    // bit 8:  CWR
    // bit 9:  ECE
    // bit 10: URG
    // bit 11: ACK
    // bit 12: PSH
    // bit 13: RST
    // bit 14: SYN
    // bit 15: FIN
    char fields[2];

    // Window size
    char window_size[2];

    // Packet checksum
    char cksum[2];

    // Urgent pointer (if URG set)
    char urgent[2];
};

#endif
