// Copyright (c) 2018 The PIVX developers
// Copyright (c) 2018-2019 The TWINS developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TWINS_INVALID_OUTPOINTS_JSON_H
#define TWINS_INVALID_OUTPOINTS_JSON_H
#include <string>

std::string LoadInvalidOutPoints()
{
    std::string str = "[\n"
            // "  {\n"
            // "    \"txid\": \"fff7164737e3437fd27b3787edeb2650eddd07966c492ffb7e0eb537c0a5b850\",\n"
            // "    \"n\": 0\n"
            // "  },\n"
            // "  {\n"
            // "    \"txid\": \"fff7164737e3437fd27b3787edeb2650eddd07966c492ffb7e0eb537c0a5b850\",\n"
            // "    \"n\": 1\n"
            // "  }\n"
            "]";
    return str;
}

#endif //TWINS_INVALID_OUTPOINTS_JSON_H
