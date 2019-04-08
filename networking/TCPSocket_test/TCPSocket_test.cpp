#include <cstring>
#include <iostream>

#include "TCPSocket.hpp"

#include "Test.hpp"
#include "TestCases.hpp"
#include "TestMacros.hpp"

TEST_CASES_PROGRAM_BEGIN(TCPSocket_test)
TEST(SendReceive_TwoSockets)
TEST(SendReceive_TwoSockets_AcceptSpawn)
TEST_CASES_PROGRAM_END(TCPSocket_test)

//==============================================================================
void TCPSocket_test::addTestCases()
{
    addTestCase(new SendReceive_TwoSockets());
    addTestCase(new SendReceive_TwoSockets_AcceptSpawn());
}

//==============================================================================
Test::Result TCPSocket_test::SendReceive_TwoSockets::body()
{
    unsigned int port = 0;  // Use whatever port is available

    unsigned char send1[]      = {'o',  'n',  'e',  '\0'};
    unsigned char send1_recv[] = {'\0', '\0', '\0', '\0'};
    unsigned char send2[]      = {'t',  'w',  'o',  '\0'};
    unsigned char send2_recv[] = {'\0', '\0', '\0', '\0'};
    int send_size = 4;  // Must equal the length of all four arrays

    TCPSocket socket1;
    TCPSocket socket2;

    socket2.disableBlocking();

    MUST_BE_TRUE(socket2.bind(port));

    std::cout << "Using port " << port << "\n";

    MUST_BE_TRUE(socket2.listen());

    // As long as this goes out to localhost it should be almost instantaneous,
    // at least in human terms
    MUST_BE_TRUE(socket1.connect("localhost", port));

    // SEND SOMETHING ONE WAY

    MUST_BE_TRUE(socket2.accept());

    socket2.enableBlocking();

    MUST_BE_TRUE(socket1.write(send1, send_size) == send_size);
    MUST_BE_TRUE(socket2.read(send1_recv, send_size) == send_size);

    std::cout << "Sent " << send1 << " received " << send1_recv << "\n";
    MUST_BE_TRUE(memcmp(send1, send1_recv, send_size) == 0);

    // SEND SOMETHING BACK

    MUST_BE_TRUE(socket2.write(send2, send_size) == send_size);
    MUST_BE_TRUE(socket1.read(send2_recv, send_size) == send_size);

    std::cout << "Sent " << send2 << " received " << send2_recv << "\n";
    MUST_BE_TRUE(memcmp(send2, send2_recv, send_size) == 0);

    return Test::PASSED;
}

//==============================================================================
Test::Result TCPSocket_test::SendReceive_TwoSockets_AcceptSpawn::body()
{
    unsigned int port = 0;  // Use whatever port is available

    unsigned char send1[]      = {'a',  'b',  'c',  '\0'};
    unsigned char send1_recv[] = {'\0', '\0', '\0', '\0'};
    unsigned char send2[]      = {'d',  'e',  'f',  '\0'};
    unsigned char send2_recv[] = {'\0', '\0', '\0', '\0'};
    int send_size = 4;  // Must equal the length of all four arrays

    TCPSocket socket1;
    TCPSocket socket2;

    socket2.disableBlocking();

    MUST_BE_TRUE(socket2.bind(port));

    std::cout << "Using port " << port << "\n";

    MUST_BE_TRUE(socket2.listen());

    // As long as this goes out to localhost it should be almost instantaneous,
    // at least in human terms
    MUST_BE_TRUE(socket1.connect("localhost", port));

    // SEND SOMETHING ONE WAY

    TCPSocket* socket3 = socket2.accept(false);
    MUST_BE_TRUE(socket3 != 0);

    socket3->enableBlocking();

    MUST_BE_TRUE(socket1.write(send1, send_size) == send_size);
    MUST_BE_TRUE(socket3->read(send1_recv, send_size) == send_size);

    std::cout << "Sent " << send1 << " received " << send1_recv << "\n";
    MUST_BE_TRUE(memcmp(send1, send1_recv, send_size) == 0);

    // SEND SOMETHING BACK

    MUST_BE_TRUE(socket3->write(send2, send_size) == send_size);
    MUST_BE_TRUE(socket1.read(send2_recv, send_size) == send_size);

    std::cout << "Sent " << send2 << " received " << send2_recv << "\n";
    MUST_BE_TRUE(memcmp(send2, send2_recv, send_size) == 0);

    // Have to do this here to shut the socket down so we can open another one
    // below
    delete socket3;

    // Reset the receiving arrays
    memset(send1_recv, 0, 4);
    memset(send2_recv, 0, 4);

    TCPSocket socket4;

    // As long as this goes out to localhost it should be almost instantaneous,
    // at least in human terms
    MUST_BE_TRUE(socket4.connect("localhost", port))

    TCPSocket* socket5 = socket2.accept(false);
    MUST_BE_TRUE(socket5 != 0)

    socket5->enableBlocking();

    MUST_BE_TRUE(socket4.write(send1, send_size) == send_size);

    MUST_BE_TRUE(socket5->read(send1_recv, send_size) == send_size);

    std::cout << "Sent " << send1 << " received " << send1_recv << "\n";
    MUST_BE_TRUE(memcmp(send1, send1_recv, send_size) == 0);

    // SEND SOMETHING BACK

    MUST_BE_TRUE(socket5->write(send2, send_size) == send_size);
    MUST_BE_TRUE(socket4.read(send2_recv, send_size) == send_size);

    std::cout << "Sent " << send2 << " received " << send2_recv << "\n";
    MUST_BE_TRUE(memcmp(send2, send2_recv, send_size) == 0);

    delete socket5;

    return Test::PASSED;
}
