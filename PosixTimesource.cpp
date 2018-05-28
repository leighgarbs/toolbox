#include "PosixTimesource.hpp"

#include "PosixTimestamp.hpp"

//==============================================================================
//
//==============================================================================
PosixTimesource::PosixTimesource(clockid_t clk_id) :
    clk_id(clk_id)
{
}

//==============================================================================
//
//==============================================================================
PosixTimesource::~PosixTimesource()
{
}

//==============================================================================
//
//==============================================================================
int PosixTimesource::getCurrentTime(PosixTimestamp& ts) const
{
    timespec tp;
    int cg_ret = clock_gettime(clk_id, &tp);

    ts = tp;

    return cg_ret;
}
