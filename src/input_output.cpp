#include "input_output.h"

#include <boost/format.hpp>
#include <sstream>
using std::stringstream;

#include <string>
using std::string;

#include <iomanip>
using std::endl;
using std::getline;
using std::hex;

#include <assert.h>

void readSecret(istream &fin, int256_t &secret) {
    string buf;
    stringstream ss;

    getline(fin, buf);
    ss << hex << buf;
    ss >> secret;
}

void readSplitParams(istream &fin, int16_t &splitNumber, int16_t &countPartsForRecover) {
    fin >> splitNumber >> countPartsForRecover;

    assert(splitNumber >= countPartsForRecover);
    assert(countPartsForRecover >= MIN_PARTS_FOR_RECOVER);
    assert(splitNumber <= MAX_SPLIT_NUMBER);
}

void readSecretParts(istream &fin, vector<share_t> &shares) {
    string buf(" ");
    int256_t temp;

    while (getline(fin, buf) && buf.length()) {
        stringstream ss;
        int16_t partNumber;

        ss << hex << buf.substr(buf.find(':') + 2);
        ss >> temp;

        partNumber = atoi(buf.substr(buf.find(' ') + 1).c_str());

        shares.push_back({ partNumber, temp });
    }
}

void printSplittedSecret(ostream &fout, const vector<share_t> &shares) {
    for (size_t i = 0; i < shares.size(); i++) {
        fout << "part " << shares[i].first << ": ";
        fout << int256ToHexString((uint256_t)shares[i].second) << endl;
    }
}

void printRecoveredSecret(ostream &fout, const int256_t &secret) {
    fout << "Recovered secret: " << endl;
    fout << int256ToHexString((uint256_t)secret) << endl;
}

string int256ToHexString(const uint256_t &number) {
    string hexString = (boost::format("%x") % number).str();
    return "0x" + hexString;
}
