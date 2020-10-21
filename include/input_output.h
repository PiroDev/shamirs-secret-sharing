#pragma once

#include <fstream>
using std::istream;
using std::ostream;

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "crypto_types.h"

#define MIN_PARTS_FOR_RECOVER 2

#define MAX_SPLIT_NUMBER 100

void readSecret(istream &fin, int256_t &secret);

void readSplitParams(istream &fin, int16_t &splitNumber, int16_t &countPartsForRecover);

void readSecretParts(istream &fin, vector<share_t> &shares);

void printSplittedSecret(ostream &fout, const vector<share_t> &splittedSecret);

void printRecoveredSecret(ostream &fout, const int256_t &secret);

string int256ToHexString(const uint256_t &number);
