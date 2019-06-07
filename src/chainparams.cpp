// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2019 The TWINS developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0,     uint256("0000071cf2d95aec5ba4818418756c93cb12cd627191710e8969f2f35c3530de")) // genesis
    (2000,  uint256("70362c3e307213d37dcc57d89f64d9bdeb7779e368f1c34c9b24af0dce72a6ae"))
    (50000, uint256("f5c1fe5c20a9f1fd981f5292d49293e59dd6fba685021994891f02667dce086b"))
    (80000, uint256("917998d20d8447861ef56dfc401bfa026ed5230953e20c046db2634f2b7e96df")) // split(s) caused by
    (81000, uint256("90555f5617101e868f41faf66c976b63c7a86b6c521c6f7e40f4aed8dd88be55")) // FakePoS attack are
    (82000, uint256("71ab39d5584b00e3b82e4e5bf35eb686278bbee50c02c6006f02d971ec52e57f")) // somewhere between
    (83000, uint256("0c05d80f0773e8d1a306ddcaa0c3d28c460e18e327a5b4f9369e0920bb91cf09")) // blocks 80,000 and 84,000
    (84123, uint256("1db6bab4574c294c9b5378e23997bc8a383f4ae25934041fb380634c1678d2c1")) //
    (85000, uint256("4b74d103475d7d606de8534a87bb3449fdf11e92e9dd6baa5fb7f1fe12656e9b"))
    (87000, uint256("6514126e1b1439b9b8a16657caff1f9bb7742d355e2e825a9a46e48aa99ee91e"))
    (89000, uint256("4ea0c0c13808fc908de9d24b318bba3330eb4626d7188ee089b42264db90fb17"))
    (93000, uint256("9068c3e6fb672ff33b91c35ae3fa466f4f5b57da53d332bdfb339ca5bf2219a2"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1557154659, // * UNIX timestamp of last checkpoint block
    233420,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    0           // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1740710,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x2f;
        pchMessageStart[1] = 0x1c;
        pchMessageStart[2] = 0xd3;
        pchMessageStart[3] = 0x0a;
        vAlertPubKey = ParseHex("047e0ecd1d96c6c02e18f702d4b19006ead8639f26dc0a606a673a68cd0731e0d5e754a374ed7fdf0029331c8842c9720a1ed2a3f557e4c6a69b8421a3a2c50cf1");
        nDefaultPort = 37817;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // TWINS starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 0;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60;
        nTargetSpacing = 2 * 60;  // TWINS: 2 minute
        nMaturity = 60;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 10000000000 * COIN;
        nMasternodeCollateral = 1000000 * COIN;//collateral
        /** Height or Time Based Activations **/
        nLastPOWBlock = 400;
        nModifierUpdateBlock = 200;
        nZerocoinStartHeight = 15000000;
        nZerocoinStartTime = 4070908800;
        nBlockEnforceSerialRange = 895400; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 891730; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 902850; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 268200*COIN; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 104153160; //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT
        nEnforceNewSporkKey = 1547424000; //!> Sporks signed after (GMT): Monday, January 14, 2019 00:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1547510400; //!> Fully reject old spork key after (GMT): Tuesday, Janurary 15, 2019 00:00:00 AM GMT

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "BBC 2018/12/31 Global markets in worst year since 2008";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c2851936b2196beb85e7eca91697884918bc6deacd4ca49b52418d376a092913bde42bc868178c0ed436c184259edd0bf2a3ff32388facd6d6332e8de31c9121") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1546790318;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 348223;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000071cf2d95aec5ba4818418756c93cb12cd627191710e8969f2f35c3530de"));
        assert(genesis.hashMerkleRoot == uint256("0x4271a3d993d6157f960de646ce8dfad07989dfd0703064f8056d1a7287283d06"));

        vSeeds.push_back(CDNSSeedData("18.228.216.158", "18.228.216.158")); //Brazil
        vSeeds.push_back(CDNSSeedData("13.210.111.12", "13.210.111.12"));   //Australia
        vSeeds.push_back(CDNSSeedData("46.19.210.197", "46.19.210.197"));   //Germany
        vSeeds.push_back(CDNSSeedData("46.19.214.68", "46.19.214.68"));     //Singapore
        vSeeds.push_back(CDNSSeedData("142.93.145.197", "142.93.145.197")); //Toronto
        vSeeds.push_back(CDNSSeedData("159.65.84.118", "159.65.84.118"));   //London
        vSeeds.push_back(CDNSSeedData("167.99.223.138", "167.99.223.138")); //Amsterdam
        vSeeds.push_back(CDNSSeedData("68.183.161.44", "68.183.161.44"));   //San Fransisco
        vSeeds.push_back(CDNSSeedData("46.19.212.68", "46.19.212.68"));     //LA
        vSeeds.push_back(CDNSSeedData("46.19.213.68", "46.19.213.68"));     //Miami
        vSeeds.push_back(CDNSSeedData("46.19.209.68", "46.19.209.68"));     //New York

        devAddress = "WmXhHCV6PjXjxJdSXPeC8e4PrY8qTQMBFg";

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 73);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 83);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 66);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0xCA).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "0496c1186ed9170fe353a6287c6f2b1ec768dcfc0fe71943067a0c21349dcf22af77a37f3202d540e85092ad4179f9b44806269450cd0982071ea7a9375ac7d949";
        strSporkKeyOld = "04d8ef5cc6ef836335a868be72cf1fa97bb2628a36febc54c004809259b64f2cc8b0dacfd72ca69b3a692c719672ca4f2cbbd7cdd140ad3e1544479ea378a21cc2";
        strObfuscationPoolDummyAddress = "AMwZqSp6C5fWeXKf7ahGjo2WVers4nAUps";
        nStartMasternodePayments = 1537122249;

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a ztwins to be stakable

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xe5;
        pchMessageStart[1] = 0xba;
        pchMessageStart[2] = 0xc5;
        pchMessageStart[3] = 0xb6;
        vAlertPubKey = ParseHex("04a8fadbd1ab6a725f8a61e92a930e2b2be0c348f8272a6755b279ffb219945ac71c7197cd205a2de8c0ad9b24807f74084a83801a8602d44d31c64b92c82c623a");
        nDefaultPort = 37847;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60;
        nTargetSpacing = 2 * 60;  // TWINS: 2 minute
        nLastPOWBlock = 400;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 10000000000 * COIN;
        nZerocoinStartHeight = 200;
        nZerocoinStartTime = 1537223238;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 9902850; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 15444020; //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1547424000; //!> Sporks signed after (GMT): Monday, January 14, 2019 00:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1547510400; //!> Fully reject old spork key after (GMT): Tuesday, Janurary 15, 2019 00:00:00 AM GMT

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1559924843;
        genesis.nNonce = 36377;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000c538590ec8fc7c6725262788f25cb5cd4aa3120f1fcb4fe5f135f6a0eeb"));

        vFixedSeeds.clear();
        vSeeds.clear();

        vSeeds.push_back(CDNSSeedData("18.228.216.158", "18.228.216.158")); //Brazil
        vSeeds.push_back(CDNSSeedData("13.210.111.12", "13.210.111.12"));   //Australia
        vSeeds.push_back(CDNSSeedData("46.19.210.197", "46.19.210.197"));   //Germany
        vSeeds.push_back(CDNSSeedData("46.19.214.68", "46.19.214.68"));     //Singapore
        vSeeds.push_back(CDNSSeedData("142.93.145.197", "142.93.145.197")); //Toronto
        vSeeds.push_back(CDNSSeedData("159.65.84.118", "159.65.84.118"));   //London
        vSeeds.push_back(CDNSSeedData("167.99.223.138", "167.99.223.138")); //Amsterdam
        vSeeds.push_back(CDNSSeedData("68.183.161.44", "68.183.161.44"));   //San Fransisco
        vSeeds.push_back(CDNSSeedData("46.19.212.68", "46.19.212.68"));     //LA
        vSeeds.push_back(CDNSSeedData("46.19.213.68", "46.19.213.68"));     //Miami
        vSeeds.push_back(CDNSSeedData("46.19.209.68", "46.19.209.68"));     //New York

        devAddress = "XiAHWrbngwovQPdtWzuehx4BL4dvCFKSW3";

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 76);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 137);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 237);
        // Testnet twins BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet twins BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet twins BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04c9ac467e88caca60e5048efa9d254098422a877f1ffcbb506c4e2b3786b8ae16ae45b586e4106661e4f157da64eeb1486b19940a25511ebcbd07bc8c2f85fdca";
        strSporkKeyOld = "04c9ac467e88caca60e5048efa9d254098422a877f1ffcbb506c4e2b3786b8ae16ae45b586e4106661e4f157da64eeb1486b19940a25511ebcbd07bc8c2f85fdca";
        strObfuscationPoolDummyAddress = "xznpVZnXKi7XDgUd3NXdqVhUftyHKi1L1K";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // TWINS: 1 day
        nTargetSpacing = 2 * 60;        // TWINS: 2 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1537120201;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12345;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 5467;
       /// assert(hashGenesisBlock == uint256("0x35495958253258ba1a6967ba6b846a297774efc4a010da004b044b0de6b3788e"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
