#if !defined SIGNAL_MANAGER_IMPL_HPP
#define SIGNAL_MANAGER_IMPL_HPP

class SignalManagerImpl
{
public:

    // Argument parsing and program initialization happens here
    SignalManagerImpl();

    // Nothing to do on shutdown here
    virtual ~SignalManagerImpl();

    // C function "cfun" is assigned to handle signals of type sig
    virtual bool registerSignalHandler(int sig, void cfun(int)) = 0;

    // External sources can use this interface to signal this program; signals
    // are not handled immediately, they are placed on a list and handled within
    // the processDeliveredSignals member function
    virtual void signal(int sig) = 0;

    // Returns true if sig has been delivered
    virtual bool isSignalDelivered(int sig) = 0;
};

#endif
