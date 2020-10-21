#include <string.h>

#include <iostream>

#include "crypto_functions.h"
#include "input_output.h"

using std::cin;
using std::cout;

int main(int argc, char **argv) {
    if (argc != 2)
        return 1;

    int256_t secret = 0x0;
    vector<share_t> shares;

    if (!strcmp(argv[1], "split")) {
        int16_t splitNumber, countPartsForRecover;
        readSecret(cin, secret);
        readSplitParams(cin, splitNumber, countPartsForRecover);

        shares = splitSecret(secret, splitNumber, countPartsForRecover);
        printSplittedSecret(cout, shares);
    } else if (!strcmp(argv[1], "recover")) {
        readSecretParts(cin, shares);

        secret = recoverSecret(shares);
        printRecoveredSecret(cout, secret);
    } else {
        return 2;
    }

    return 0;
}
