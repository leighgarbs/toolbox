#include <stdexcept>
#include <unordered_set>

#if defined DEBUG
#include <iostream>
#endif

#include "SignalManager.hpp"

#include "SignalManagerFactory.hpp"
#include "SignalManagerImpl.hpp"

//==============================================================================
SignalManager::SignalManager() :
    signal_manager_impl(0)
{
    signal_manager_impl = SignalManagerFactory::createSignalManager();

    if (!signal_manager_impl)
    {
        throw std::runtime_error(
            "Platform-specific signal manager could not be created");
    }
}

//==============================================================================
SignalManager::~SignalManager()
{
    delete signal_manager_impl;
}

//==============================================================================
// C function "cfun" is assigned to handle signals of type sig
//==============================================================================
bool SignalManager::registerSignalHandler(int sig, void cfun(int))
{
    if (signal_manager_impl)
    {
        return signal_manager_impl->registerSignalHandler(sig, cfun);
    }

#if defined DEBUG
    std::cerr << "Signal handling not available on this platform, ignoring\n";
#endif

    return false;
}

//==============================================================================
// External sources can use this interface to signal this program; signals are
// not handled immediately, they are placed on a list and handled within the
// processDeliveredSignals member function
//==============================================================================
void SignalManager::signal(int sig)
{
    if (signal_manager_impl)
    {
        signal_manager_impl->signal(sig);
    }
#if defined DEBUG
    else
    {
        std::cerr <<
            "Signal handling not available on this platform, ignoring\n";
    }
#endif
}

//==============================================================================
// Returns true if sig has been delivered
//==============================================================================
bool SignalManager::isSignalDelivered(int sig)
{
    if (signal_manager_impl)
    {
        return signal_manager_impl->isSignalDelivered(sig);
    }

#if defined DEBUG
    std::cerr << "Signal handling not available on this platform, ignoring\n";
#endif

    return false;
}

//==============================================================================
// Fills in a user-provided set with the list of signals we know about
//==============================================================================
void
SignalManager::getSupportedSignals(std::unordered_set<int>& supported_signals)
{
    signal_manager_impl->getSupportedSignals(supported_signals);
}
