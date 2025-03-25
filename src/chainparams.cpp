// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2022-2024 The Dogecoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1386325540, nBits=0x1e0ffff0, nNonce=99943, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "05/12/2024 - This is Flopcoin.";
    const CScript genesisOutputScript = CScript() << ParseHex("04a5c56a22caf4b1c8917f8a261a83efe5885526d05ad0cb7e9fc7d000d04085e225e578d8f899d3d9811f39f2e7c2c7322c8a070fd757e0c935dd6c35fc8c66cc") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
private:
    Consensus::Params digishieldConsensus;
    Consensus::Params auxpowConsensus;
public:
    CMainParams() {
        strNetworkID = "main";
	strDevFeeAddress = "FLDe9sDaU63Y6GALoSAJfTJ8NtkR9goLok";
	nDevFeePercentage = 10;
        consensus.nSubsidyHalvingInterval = 100000;
        consensus.nMajorityEnforceBlockUpgrade = 1500;
        consensus.nMajorityRejectBlockOutdated = 1900;
        consensus.nMajorityWindow = 2000;
	consensus.V3ForkHeight = 111000;
	consensus.AUXPOWHeight = 110000;
	consensus.V2_0ForkHeight = 120000;
	consensus.nDevFeeEndHeight = 600000;
        consensus.BIP34Height = 100;
        consensus.BIP34Hash = uint256S("0x67cf3c48ee2ff1db2598e59b8841c85c3e080758bd5a105158bccf4d268c0ab5");
        consensus.BIP65Height = consensus.V3ForkHeight;
        consensus.BIP66Height = 101;
        consensus.powLimit = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~uint256(0) >> 20;
        consensus.nPowTargetTimespan = 1 * 60 * 60;
        consensus.nPowTargetSpacing = 60;
        consensus.fDigishieldDifficultyCalculation = false;
        consensus.nCoinbaseMaturity = 30;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowAllowDigishieldMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 9576;
        consensus.nMinerConfirmationWindow = 10080;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999;

        // Deployment of BIP68, BIP112, and BIP113.
        // XXX: BIP heights and hashes all need to be updated to Flopcoin values
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1462060800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1493596800;

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1479168000;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 0;

        // Disable all unused version bits (3 to 28) for security
        for (int i = 3; i < (int)Consensus::MAX_VERSION_BITS_DEPLOYMENTS; i++) {
            consensus.vDeployments[i].bit = -1;
            consensus.vDeployments[i].nStartTime = -1;
            consensus.vDeployments[i].nTimeout = -1;
        }

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000002cc6be9a704f58da");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0cc5f930f568b8771242f9c733a52a83ca30319ad955fa555a8c0bd96185033d");

        // AuxPoW parameters
        consensus.nAuxpowChainId = 0x00A3; // 163 !
        consensus.fStrictChainId = true;
        consensus.fAllowLegacyBlocks = true;
        consensus.nHeightEffective = 0;

        // Blocks 145 - 109,999 are Digishield without AuxPoW
        digishieldConsensus = consensus;
        digishieldConsensus.nHeightEffective = 145;
        digishieldConsensus.fSimplifiedRewards = true;
        digishieldConsensus.fDigishieldDifficultyCalculation = true;
        digishieldConsensus.nPowTargetTimespan = 60; // post-digishield: 1 minute
        digishieldConsensus.nCoinbaseMaturity = 240;

        // Blocks 110000+ are AuxPoW
        auxpowConsensus = digishieldConsensus;
        auxpowConsensus.nHeightEffective = consensus.AUXPOWHeight;
        auxpowConsensus.fAllowLegacyBlocks = false;

        // Assemble the binary search tree of consensus parameters
        pConsensusRoot = &digishieldConsensus;
        digishieldConsensus.pLeft = &consensus;
        digishieldConsensus.pRight = &auxpowConsensus;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
/**     // Old pchMessageStart
        pchMessageStart[0] = 0xc0;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xc0;
**/
        // New pchMessageStart
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;


	LogPrintf("INFO: Using new messageStart for protocol v2.0.0.0 fork at block %d\n", consensus.V2_0ForkHeight);

        nDefaultPort = 32552;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1733419383, 39688, 0x1e0ffff0, 1, 88 * COIN);

        consensus.hashGenesisBlock = genesis.GetHash();
        digishieldConsensus.hashGenesisBlock = consensus.hashGenesisBlock;
        auxpowConsensus.hashGenesisBlock = consensus.hashGenesisBlock;
        assert(consensus.hashGenesisBlock == uint256S("0x1f1037762db00882d3353b8d9dcfd52fc93cbc2d694c62f1ecd6a209cf9d30d0"));
        assert(genesis.hashMerkleRoot == uint256S("0xd646459741e2708a78a3c00f7d42790509ef11c8448930b478bbcf6b6ee25961"));

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.push_back(CDNSSeedData("node.flopcoin.net", "seed.flopcoin.net", true));
        vSeeds.push_back(CDNSSeedData("node2.flopcoin.net", "seed2.flopcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,35);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,22);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,158);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0xfa)(0xca)(0xfd).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0xfa)(0xc3)(0x98).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (      0, uint256S("0x1f1037762db00882d3353b8d9dcfd52fc93cbc2d694c62f1ecd6a209cf9d30d0"))
            (      1, uint256S("0x303ba2e2c5489ec1bb2eced89b05d850fbd937d038b38cd05dda05c389a23b9f"))
            (      28838, uint256S("0x674e86088d3990535d366b6ca4a5ffc92759900d44001da99832c63a5f379e36"))
            (      109504, uint256S("0x3ca447af0d850da01c8de0d9460fd4bb77a612fc670ec6a5ba7c9ddb3ae85491"))
            (      111006, uint256S("0x0cc5f930f568b8771242f9c733a52a83ca30319ad955fa555a8c0bd96185033d"))
        };

        chainTxData = ChainTxData{
            // Data as of block 3ca447af0d850da01c8de0d9460fd4bb77a612fc670ec6a5ba7c9ddb3ae85491 (height 109504).
            // Tx estimate based on average of year 2018 (~27k transactions per day)
            1742625155, // * UNIX timestamp of last checkpoint block
            136669,   // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            1.000      // * estimated number of transactions per second after checkpoint
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
private:
    Consensus::Params digishieldConsensus;
    Consensus::Params auxpowConsensus;
    Consensus::Params minDifficultyConsensus;
public:
    CTestNetParams() {
        strNetworkID = "test";
        // Blocks 0 + are pre-Digishield
        consensus.nHeightEffective = 0;
	strDevFeeAddress = "PtTNHA68jc539AuWgqYsSGrzVyYpbu9frp";
	nDevFeePercentage = 10;
        consensus.nSubsidyHalvingInterval = 100000;
        consensus.nMajorityEnforceBlockUpgrade = 501;
        consensus.nMajorityRejectBlockOutdated = 750;
        consensus.nMajorityWindow = 1000;
	consensus.V3ForkHeight = 0;
	consensus.AUXPOWHeight = 0;
	consensus.V2_0ForkHeight = 0;
	consensus.nDevFeeEndHeight = 600000;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0xf4a99d0171235dab2cc2efb14055b86f96c9eda1653ff0a3b2153146391fe300");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.powLimit = uint256S("0x000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~uint256(0) >> 20;
        consensus.nPowTargetTimespan = 24 * 60 * 60;
        consensus.nPowTargetSpacing = 30;
        consensus.fDigishieldDifficultyCalculation = false;
        consensus.nCoinbaseMaturity = 30;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowAllowDigishieldMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 180;
        consensus.nMinerConfirmationWindow = 240;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = -1;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = -1;

        // Deployment of BIP68, BIP112, and BIP113.
        // XXX: BIP heights and hashes all need to be updated to Flopcoin values
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = -1;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = -1;

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = -1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = -1;

        // Disable all unused version bits (3 to 28) for security
        for (int i = 3; i < (int)Consensus::MAX_VERSION_BITS_DEPLOYMENTS; i++) {
            consensus.vDeployments[i].bit = -1;
            consensus.vDeployments[i].nStartTime = -1;
            consensus.vDeployments[i].nTimeout = -1;
        }

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000100010");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0xf4a99d0171235dab2cc2efb14055b86f96c9eda1653ff0a3b2153146391fe300");

        // AuxPoW parameters
        consensus.nAuxpowChainId = 0x0f44;
        consensus.fStrictChainId = false;
        consensus.fAllowLegacyBlocks = true;
        consensus.nHeightEffective = 0;

        // Blocks 0 + digishielconsensus phase
        digishieldConsensus = consensus;
        digishieldConsensus.nHeightEffective = 0;
        digishieldConsensus.nPowTargetTimespan = 60;
        digishieldConsensus.fDigishieldDifficultyCalculation = true;
        digishieldConsensus.fSimplifiedRewards = true;
        digishieldConsensus.fPowAllowMinDifficultyBlocks = false;
        digishieldConsensus.nCoinbaseMaturity = 30;

        // Blocks 0 + are Digishield with minimum difficulty on all blocks
        minDifficultyConsensus = digishieldConsensus;
        minDifficultyConsensus.nHeightEffective = 0;
        minDifficultyConsensus.fPowAllowDigishieldMinDifficultyBlocks = true;
        minDifficultyConsensus.fPowAllowMinDifficultyBlocks = true;

        // Enable AuxPoW at 0
        auxpowConsensus = minDifficultyConsensus;
        auxpowConsensus.nHeightEffective = consensus.AUXPOWHeight;
        auxpowConsensus.fPowAllowDigishieldMinDifficultyBlocks = true;
        auxpowConsensus.fAllowLegacyBlocks = false;

        // Assemble the binary search tree of parameters
        pConsensusRoot = &digishieldConsensus;
        digishieldConsensus.pLeft = &consensus;
        digishieldConsensus.pRight = &minDifficultyConsensus;
        minDifficultyConsensus.pRight = &auxpowConsensus;

        pchMessageStart[0] = 0xd5;
        pchMessageStart[1] = 0xa9;
        pchMessageStart[2] = 0xf0;
        pchMessageStart[3] = 0xb2;
        nDefaultPort = 44556;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1733419386, 308587, 0x1e0ffff0, 1, 88 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        digishieldConsensus.hashGenesisBlock = consensus.hashGenesisBlock;
        minDifficultyConsensus.hashGenesisBlock = consensus.hashGenesisBlock;
        auxpowConsensus.hashGenesisBlock = consensus.hashGenesisBlock;
        assert(consensus.hashGenesisBlock == uint256S("0xf4a99d0171235dab2cc2efb14055b86f96c9eda1653ff0a3b2153146391fe300"));
        assert(genesis.hashMerkleRoot == uint256S("0xd646459741e2708a78a3c00f7d42790509ef11c8448930b478bbcf6b6ee25961"));

        //vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("cc", "seeds.altcoinspool.cc"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,56);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,76);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,184);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xcf).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        //vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0xf4a99d0171235dab2cc2efb14055b86f96c9eda1653ff0a3b2153146391fe300")) 
        };

        chainTxData = ChainTxData{
            // Data as of block f4a99d0171235dab2cc2efb14055b86f96c9eda1653ff0a3b2153146391fe300(height 0)
            1733419386, // * UNIX timestamp of last checkpoint block
            0,    // * total number of transactions between genesis and last checkpoint
            0.000 // * estimated number of transactions per day after checkpoint
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
private:
    Consensus::Params digishieldConsensus;
    Consensus::Params auxpowConsensus;
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 0; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 0; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 0; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.powLimit = uint256S("0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~uint256(0) >> 1;
        consensus.nPowTargetTimespan = 1 * 60 * 60; // pre-digishield: 4 hours
        consensus.nPowTargetSpacing = 1; // regtest: 1 second blocks
        consensus.fDigishieldDifficultyCalculation = false;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 540; // 75% for testchains
        consensus.nMinerConfirmationWindow = 720; // Faster than normal for regtest (2,520 instead of 10,080)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        // AuxPow parameters
        consensus.nAuxpowChainId = 0x0062; // 98 - Josh Wise!
        consensus.fStrictChainId = true;
        consensus.fAllowLegacyBlocks = true;

        // Flopcoin parameters
        consensus.fSimplifiedRewards = true;
        consensus.nCoinbaseMaturity = 6; // For easier testability in RPC tests

        digishieldConsensus = consensus;
        digishieldConsensus.nHeightEffective = 10;
        digishieldConsensus.nPowTargetTimespan = 1; // regtest: also retarget every second in digishield mode, for conformity
        digishieldConsensus.fDigishieldDifficultyCalculation = true;

        auxpowConsensus = digishieldConsensus;
        auxpowConsensus.fAllowLegacyBlocks = false;
        auxpowConsensus.nHeightEffective = 20;

        // Assemble the binary search tree of parameters
        digishieldConsensus.pLeft = &consensus;
        digishieldConsensus.pRight = &auxpowConsensus;
        pConsensusRoot = &digishieldConsensus;

        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nDefaultPort = 18444;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1733419469, 3, 0x207fffff, 1, 88 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        digishieldConsensus.hashGenesisBlock = consensus.hashGenesisBlock;
        auxpowConsensus.hashGenesisBlock = consensus.hashGenesisBlock;
        assert(consensus.hashGenesisBlock == uint256S("0xe0950eaa6e8ee8c50f8291b47d83aa59763936adc96ec60bdfb72d513bd4f1d4"));
        assert(genesis.hashMerkleRoot == uint256S("0xd646459741e2708a78a3c00f7d42790509ef11c8448930b478bbcf6b6ee25961"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0xe0950eaa6e8ee8c50f8291b47d83aa59763936adc96ec60bdfb72d513bd4f1d4"))
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
    }

    void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

const Consensus::Params *Consensus::Params::GetConsensus(uint32_t nTargetHeight) const {
    if (nTargetHeight < this -> nHeightEffective && this -> pLeft != NULL) {
        return this -> pLeft -> GetConsensus(nTargetHeight);
    } else if (nTargetHeight > this -> nHeightEffective && this -> pRight != NULL) {
        const Consensus::Params *pCandidate = this -> pRight -> GetConsensus(nTargetHeight);
        if (pCandidate->nHeightEffective <= nTargetHeight) {
            return pCandidate;
        }
    }

    // No better match below the target height
    return this;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}
