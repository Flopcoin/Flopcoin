// Copyright (c) 2009-2010 Florins Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "amount.h"

#include "tinyformat.h"

const std::string CURRENCY_UNIT = "FLOP";

CFeeRate::CFeeRate(const CAmount& nFeePaid, size_t nBytes_)
{
    assert(nBytes_ <= uint64_t(std::numeric_limits<int64_t>::max()));
    int64_t nSize = int64_t(nBytes_);

    if (nSize > 0)
        nFlorinssPerK = nFeePaid * 1000 / nSize;
    else
        nFlorinssPerK = 0;
}

CAmount CFeeRate::GetFee(size_t nBytes_) const
{
    assert(nBytes_ <= uint64_t(std::numeric_limits<int64_t>::max()));
    int64_t nSize = int64_t(nBytes_);

    // Flopcoin: Round up to the nearest 1000 bytes so we get round tx fees
    if (nSize % 1000 > 0) {
        nSize = nSize + 1000 - (nSize % 1000);
    }

    CAmount nFee = nFlorinssPerK * nSize / 1000;

    if (nFee == 0 && nSize != 0) {
        if (nFlorinssPerK > 0)
            nFee = CAmount(1);
        if (nFlorinssPerK < 0)
            nFee = CAmount(-1);
    }

    return nFee;
}

std::string CFeeRate::ToString() const
{
    return strprintf("%d.%08d %s/kB", nFlorinssPerK / COIN, nFlorinssPerK % COIN, CURRENCY_UNIT);
}