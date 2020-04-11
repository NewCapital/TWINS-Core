// Copyright (c) 2018 The PIVX developers
// Copyright (c) 2018-2019 The TWINS developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.



#ifndef TWINS_INVALID_SERIALS_JSON_H
#define TWINS_INVALID_SERIALS_JSON_H

#include <string>

std::string LoadInvalidSerials()
{
    std::string str = "[\n"
            // "  {\n"
            // "    \"s\": \"c9c868bb56eacfc4f3d829528a0ae812dff26619cd38e6c9a0eea1eacddc84\"\n"
            // "  },\n"
            // "  {\n"
            // "    \"s\": \"198b62253217000fbab79bfe4bc4189c17c083ccab115866f16bf803946627107\"\n"
            // "  }\n"
            "]";
    return str;
}

#endif //TWINS_INVALID_SERIALS_JSON_H
