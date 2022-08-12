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
    (93000, uint256("9068c3e6fb672ff33b91c35ae3fa466f4f5b57da53d332bdfb339ca5bf2219a2"))
    (100000, uint256("db0569db100c482e19789c6459ccfe906415fe5bbfc2d5bacfc93a4c03938c36"))
    (106344, uint256("1570eb5464f9d586ee0de79524b3c360b54e53610ebe5cf3964cf58637db366e")) // split
    (110000, uint256("b94b2bfe0cf63604784d28dce62f78c29c492d2fb276ce1b78661d82985e7365"))
    (113000, uint256("06dec9e49608a776876766b1a9edc690c1d5e5f53e0e59b1f85829cb8331827f"))
    (113500, uint256("d053ed7eb99b639c4b45817b4c7a00699e1dc8e5043f474ab8b351da1bd3ee52"))
    (113715, uint256("0b6252798e7628257417e927dc3f1e9cad56fe2042700d2a8803923659953d8e"))
    (113719, uint256("81923b7058cf8b3eb3e2e69f89bc23f290ab386cc8149c7e4b2adcff12e826df")) // Last block before split
    (113720, uint256("d31998ff85218e6cac477cd7d7c7bfa91009a58d4371ab1bed148d4cbf72158f")) // !! mainnet
    (113871, uint256("44fc9bc5c0b1a35aa2f1dc3c7ee1722722873e2dfb0c013ecbea66caa4ec86a5")) // before split
    (113872, uint256("13bb2e1c7c95dd40c631d0fb314b6b4b27b583bffa1e5c5e4535ae34ee02fb68")) // !! mainnet
    (114000, uint256("42d1dea87efa95cac8d1ede5d2ed37f6f99929edd9b17e946dbd9e2e520528a8"))
    (114500, uint256("5bd14bcb6b82cc1b0f073f902db59ecafa5d9d364cb6a91bd78b7377b7a61921"))
    (115200, uint256("9b23c51a7d288f0c2aa82601cfbd3499c23d0696194a75afa8b2ef4aca909eaa"))
    (116000, uint256("42d9dd5852a3cf0d9a799e4eb1ab8b54609aef25a1c649562d7453dae48b77b8"))
    (117000, uint256("6e6983dccf2a30662c5ae82370c6911580dd79ce40a1ddf56cb732d36f7d9687"))
    (117250, uint256("98a0eefbfe111c51784944b2c650b2cc5ba749b21cba837d9734a1a45a4c36f2"))
    (200000, uint256("c0a39556e6d7f0c80c7efc479640151c0db31f38afcf91dd72f6a2b9897c76d2"))
    (230000, uint256("eee7bfa3489249b8547cb539468cb7df139606f88d303afa2b175e317e8c865e"))
    (250000, uint256("c3ed34dde5ebd0a679667ab37891a5079207847ba55ee6ba40872e693a2c0b67"))
    (280000, uint256("85ac815a816a8c98cbdd9c10c26edd71c4edd7eb87cdc473e650e12981307ffe"))
    (300000, uint256("9e1eb7bfc58e66ad4ff62ca20b6c0aa838c2a6151100c574548317affb214212"))
    (314883, uint256("07ed00a702b3e78a6a1664befb950ecb08e112ad1f4af65f3d6b08d593b84929"))
    (316999, uint256("867f64f36a34f99881b19e9e4802149b3f37978085245fb37be6fd1a0583f459"))
    (317000, uint256("1657f2baa2b635805daccb32adbe7b5da847b2e96f7a7da8b213cccc6c90f262")) // Min staking enforcement, New protocol enforcement (70922)
    (317001, uint256("ed7a7c72e9c31ef0e9e08da12a0ac57ccd87ff0ddf0e6694e4ce1edd9761b23b"))
    (317005, uint256("44405d602b2dca51798def580721c768280cb57f729bf74c02d586caa0b22812"))
    (317167, uint256("a5e4d2c9ebb2411119970a6e185e6e0d7f8b14e2d769cefc4c7c442b36cc7e39"))
    (317168, uint256("6b3ed5c27f90e5d463a7991c95933f7918e9fc1c3cc070333280e1dc4d211497")) // known split
    (320500, uint256("013b9e3d4cd2511507ba73c93a71cb53095a78e81c9256deb14d94f9706efa7c"))
    (321000, uint256("f952755ad4ced9dcd70ab83686548d53ca690cd5bad6e60e43e76231f2ff1992"))
    (322000, uint256("850c8f67919f8dc23679e0b5ef1e2599034b729efc6f44387462efb3e1f95e70"))
    (323000, uint256("622192c9e38d1cfcfe76fe9659bc89d430d17b04c031e119b4698fdf31c6435f"))
    (323987, uint256("4a2d43e8b9a22cd6789d26aecf103d70035d6d038a669336125d802aa9b19c78")) // 70923 enforcement
    (323989, uint256("410704a99d95725af169c8805607bb09881c7c840105b7430a1e007ff38943c5"))
    (324000, uint256("6b7e2a40ed3fc09c93fbd4e3073de6c2ddbe0b048499686e537257515e0bc165"))
    (325000, uint256("93cd883cf9858fb944459a1aa3a30d3487372b21666d72bb2ebd4d0b1a39e580"))
    (322999, uint256("d22553c89e2bcf2880da68f06ac677a535388583ead3b3a14671f19be43f6e77"))
    (332120, uint256("27045d11d68c210997565a8a7b1ff8783af10c864f00e773f6355a860a349d0d"))
    (333499, uint256("be482c0c599bacba2b3673482c56a5a7804924883d2c8269f2a7e4d1a8bd2e28"))
    (333500, uint256("fa4657c82b54cb75510d3b0f14e4a5131f6ca972a5522806ba78cedc3e4fa02b")) // Min stake fix
    (333510, uint256("206a4fd16dcf58c549f13faebf7dba877041b9edb379f3386561bf9df7901cff"))
    (340000, uint256("28a4de165cf11170b035515972e232c711981434f50b62400b36d58e4929a95c"))
    (350000, uint256("e5954e2a84643ffc67f0ec6d98a768918844be9a58558c01df14eb482cdc6b70"))
    (360000, uint256("89475bd848b0086430bc6532ba4b695abea900ab84b10c1260b5f236bd635e79"))
    (375600, uint256("f71da43f75eedda8c86003d891a254254c484f8044a79089df101be0aa0a52c8"))
    (382000, uint256("045aec823149c164bad0341de41f98e844f228ede271cf9c671b190805487de4")) // 70924 enforcement
    (382050, uint256("6f510b37501369a22d9a1f9e3f3ceec4a476e731b15215b678a9cf908b71ced6"))
    (382150, uint256("bf2d5cdc298a332f2ee1ec7caf45ec10f5a6c08b52946cc076ae7edd89133351"))
    (394756, uint256("8aa66d6721481b39813df844677c6142e39a6e068584b5503a9d48621ad0c9e4"))
    (420000, uint256("ade10823f13d1f5f6b9f3a4722b8956878d17d257482768680b0bf4bc0493201"))
    (441201, uint256("593456c5007465e968b7487fd55b2e36dbfb18dda45109551c5d4a83067e0a5e")) // split
    (441397, uint256("777d3d58642fae753b67d503362195607006a1c017e89b082a27123d080b784d"))
    (442325, uint256("1d16bad5a8da7dc3c0bc2f417ec35d2c7ff558a7ee95bf0f731e308324b4dfa4"))
    (500000, uint256("9f5aaff290c48d5a8cd53e3b7cb7eea911a5f10831b0a946348a1db1a645a2ec"))
    (550000, uint256("c6f21271fbdaec10dfee16d9cf4c4d073d78b1282d1aa4414001a4ec5fc05008"))
    (650000, uint256("8942cf0b3850d448289ebe663e074c122bf0d36361bf6dd374aeeffa2b9c340b"))
    (682400, uint256("89708f4d054771b2079854b415fb8d336d9f16c9b5cd1342d3b233229a35c97c")) // preparing update for 70926
    (907970, uint256("3d9698bc000068035cebe5ed382ae5bb660b8debe271dffed70f914de22bc9aa"))
    (907995, uint256("a626b8fe541f3a07ba0f59836cc631dd81db07296a158287635e67fd2ba5225a")) // Network recovery & fork. 08.2022 (start)
    (907996, uint256("4faaf1b056965328980ae1b6caeca7428698f916110e473e39c161543d32a767"))
    (907997, uint256("a99b449ac84f53f3a9c7aba594654b2a7f803f94b25b0f835337e160e8e93f3a"))
    (907998, uint256("1b629d939db0c4f71e42d206b59ea0f2c0f1019c8b5f46b66241e9ea25e8854a"))
    (907999, uint256("3714adc51af727462177131098c5ed6f46489350eeab716c8f96b744afdc88d0"))
    (908000, uint256("f9f9d700a25f1b8a98ed53829278180a75da9781bde525a0cc90a1ef9b2fa8fc"))
    (908001, uint256("58dfee65f4fe0d7d97e5618c10c5cb68ee50e9a210189ab8e1aa0dae659087a8"))
    (908002, uint256("a43c4301f66e211818915d2692a6455addbc19e299590cd13d78c061764094e0"))
    (908003, uint256("6a13fffd1d02ad616682ed92ec72076bdfab0453fc9aa6624a846640daa539d3"))
    (908004, uint256("cacf903e1d9c05a182d7dd480ffb9349e9d9de1242f5740c453194aec19f5b88"))
    (908005, uint256("033d4929561bf239b1d8c32a702690f1fae903ef4031ae6f320159ba8b52b5fe"))
    (908006, uint256("1e8900e8a6872310af5d7171a2252a390846c4bc5e73c8ad35f7e2ff35f460f9"))
    (908007, uint256("7933e12ba1321b30385f37254fa40d62cf064fd60766c65cfc97179770125720"))
    (908614, uint256("e94ff6dd468d909e14d447762bb52051e41ea0bf91b10d48869fd093cdb540df")) // Network recovery & fork. 08.2022 (end)
    (909389, uint256("bd5a38aa452c21e6c6039cd464fe60366bbed8964735088391ee0c6cca68bd02"))
    // (, uint256(""))
    ;
//
// Blacklist
//
static Checkpoints::MapCheckpoints BadBlocks =
    boost::assign::map_list_of
    (907998, uint256("91ee7fb080b75f37cd96223134d52cccb9fdc19f2698c65a4343356a1421e0b0"))
    (907999, uint256("75759383da8f63daa3980f5b1767287a204124c317083780d457ebd6d15d4639")) // 29.7 - 908000
    (908000, uint256("3a1daa15d6ab64d79d4f71e40dfde714fd5f0d181b12a4123d9e555b216fe358"))
    ;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    &BadBlocks,
    1660309215, // * UNIX timestamp of last checkpoint block
    2239385,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    0           // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static Checkpoints::MapCheckpoints BadBlocksTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    &BadBlocksTestnet,
    1740710,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static Checkpoints::MapCheckpoints BadBlocksRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    &BadBlocksRegtest,
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

        nTier1mCollateral =     1000000 * COIN;
        nTier1mProbability =                 1;
        nTier5mCollateral =     5000000 * COIN;
        nTier5mProbability =                 5;
        // nTier10mCollateral =   10000000 * COIN;
        // nTier10mProbability =               10;
        nTier20mCollateral =   20000000 * COIN;
        nTier20mProbability =               20;
        nTier100mCollateral = 100000000 * COIN;
        nTier100mProbability =             100;
        nStakeMinInput = 12000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 400;
        nModifierUpdateBlock = 200;
        nZerocoinStartHeight = 15000000;
        nZerocoinStartTime = 4070908800;
        nBlockEnforceSerialRange = 895400; //Enforce serial range starting this block
        // nBlockRecalculateAccumulators = 908000; //Trigger a recalculation of accumulators
        nBlockRecalculateAccumulators = 6569605; //Trigger a recalculation of accumulators
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

        vSeeds.push_back(CDNSSeedData("45.77.64.171", "45.77.64.171"));   //Germany
        vSeeds.push_back(CDNSSeedData("67.219.107.45", "67.219.107.45")); //Australia
        vSeeds.push_back(CDNSSeedData("104.238.185.162", "104.238.185.162")); //UK
        vSeeds.push_back(CDNSSeedData("208.85.21.121", "208.85.21.121")); //Spain
        vSeeds.push_back(CDNSSeedData("45.77.118.66", "45.77.118.66")); //FL
        vSeeds.push_back(CDNSSeedData("65.20.69.84", "65.20.69.84"));   //IN
        vSeeds.push_back(CDNSSeedData("140.82.15.118", "140.82.15.118")); //NJ
        vSeeds.push_back(CDNSSeedData("158.247.239.189", "158.247.239.189"));   //SK
        vSeeds.push_back(CDNSSeedData("216.128.182.65", "216.128.182.65"));   //CA
        vSeeds.push_back(CDNSSeedData("149.28.149.146", "149.28.149.146"));   //Singapore
        vSeeds.push_back(CDNSSeedData("45.32.36.145", "45.32.36.145"));   //Japan

        devAddress = "WmXhHCV6PjXjxJdSXPeC8e4PrY8qTQMBFg";

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 73);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 83);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 66);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0xCA).convert_to_container<std::vector<unsigned char> >();
        nExtCoinType = 970;

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

        nTier1mCollateral =     1000000 * COIN;
        nTier1mProbability =                 1;
        nTier5mCollateral =     5000000 * COIN;
        nTier5mProbability =                 5;
        // nTier10mCollateral =   10000000 * COIN;
        // nTier10mProbability =               10;
        nTier20mCollateral =   20000000 * COIN;
        nTier20mProbability =               20;
        nTier100mCollateral = 100000000 * COIN;
        nTier100mProbability =             100;
        nStakeMinInput = 12000 * COIN;

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

        // vSeeds.push_back(CDNSSeedData("18.228.216.158", "18.228.216.158")); //Brazil
        // vSeeds.push_back(CDNSSeedData("13.210.111.12", "13.210.111.12"));   //Australia
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
        nExtCoinType = 1;

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04dc3b42d79cdbd29a4694040a060ef5e5b2f50a8d52a28d133c506352e2bc43328ab94f4dc508c9c0a61bb381c98b6e0b7319bf87b4f76a52af55058ecaefe968";
        strSporkKeyOld = "048c5897893ef51a021ef4aa4f095790942ec289d01da5c1f1488d0eccdb08762c3a815a91871526ed2861a1551881f7fc91d8ebc8d84f0f849689ca5211807852";
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
