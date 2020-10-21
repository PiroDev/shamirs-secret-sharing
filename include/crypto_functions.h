#pragma once

#include <vector>
using std::vector;

#include "crypto_types.h"

vector<share_t> splitSecret(const int256_t &secret, int16_t splitNumber, int16_t countPartsForRecover);

int256_t recoverSecret(const vector<share_t> &parts);

int256_t getIntegerRand(int64_t randMin, int64_t randMax);

int256_t getPolynomValue(const int32_t &x, const vector<int256_t> &coefs, const int256_t &lastCoef);
