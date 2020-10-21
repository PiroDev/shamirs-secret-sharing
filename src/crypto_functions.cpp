#include <limits.h>

#include <random>
#include <string>
using std::string;

#include "crypto_functions.h"

/* Prime number used in Secp256k1 */
#define GROUP_FIELD_SIZE "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F"

#define RANDOM_ITERS 4

int256_t getIntegerRand(int64_t randMin = 1, int64_t randMax = INT64_MAX) {
    std::random_device seed;
    static std::default_random_engine generator{ seed() };
    static std::uniform_int_distribution<int64_t> distribution(randMin, randMax);

    int256_t result = 1;
    for (int i = 0; i < RANDOM_ITERS; i++) {
        result *= distribution(generator);
    }

    return result;
}

vector<share_t> splitSecret(const int256_t &secret, int16_t splitNumber, int16_t countPartsForRecover) {
    vector<share_t> shares;
    vector<int256_t> coefs;

    /* generate random coefficients for polynom */
    for (int16_t i = 0; i < countPartsForRecover - 1; i++) {
        coefs.push_back(getIntegerRand());
    }

    /* generate secret parts */
    for (int16_t x = 1; x <= splitNumber; x++) {
        shares.push_back({ x, getPolynomValue(x, coefs, secret) });
    }

    return shares;
}

int256_t recoverSecret(const vector<share_t> &shares) {
    int256_t groupFieldSize(GROUP_FIELD_SIZE);

    /* Lagrange polynomials interpolation */
    auto interpolation = [shares](int16_t x, int256_t y) -> float328_t {
        float328_t upper = 1.;
        float328_t lower = 1.;
        for (size_t j = 0; j < shares.size(); j++) {
            if (x != shares[j].first) {
                upper *= shares[j].first;
                lower *= (shares[j].first - x);
            }
        }
        return (y.convert_to<float328_t>() * upper) / lower;
    };

    float328_t secret = 0.;

    for (size_t i = 0; i < shares.size(); i++) {
        secret += interpolation(shares[i].first, shares[i].second);
    }

    return ((int256_t)secret) % groupFieldSize;
}

int256_t getPolynomValue(const int32_t &x, const vector<int256_t> &coefs, const int256_t &lastCoef) {
    int256_t groupFieldSize(GROUP_FIELD_SIZE);
    int256_t polynomValue = 0;

    for (size_t i = 0; i < coefs.size(); i++) {
        polynomValue += (int256_t)(coefs[i] * (int256_t)std::pow(x, i + 1));
    }
    polynomValue += lastCoef;

    return polynomValue % groupFieldSize;
}
