# Shamir's secret sharing

The program divides a secret string in hex format up to 256 bit long (for example, ECDSA secp256k1 private key) into N parts according to Shamir scheme and recovers it when any T parts are provided.

## Installation

Download c++ boost library:

For Ubuntu:

`$ sudo apt install libboost-all-dev`

Build project in project directory:

`$ make`

## Usage

The program has two modes:

- Mode split: ` $ ./bin/trinket.exe split`

- Mode recover: `$ ./bin/trinket.exe recover`

### Mode split
Input data (stdin):
```
1 line - secret key
2 line - two numbers: N, T

Where 2 < T <= N < 100. N - split number, T - minimum parts required for recover secret.
```

Output data (stdout):
```
N lines,
Each line contains secret part (as a string)
```

Example input:
```
0xc2cdf0a8b0a83b35ace53f097b5e6e6a0a1f2d40535eff1cf434f52a43d59d8f
5 3
```

Example output:
```
part 1: 0xc36ddc11cfc30d54f7eb2db0854ca2b01949f6fc9a9a00d90b2f7d38a2c8283b
part 2: 0xc4cd4ef9916768181ab64eb430a5df529f5186e849c5f3ee20b72da115e967ff
part 3: 0xc6ec495ff5954b7f1546a2147d6a24519c35dd0360e2d85c34cc06639d395cdb
part 4: 0xc9cacb44fc4cb789e79c27d16b9971ad0ff6f94ddff0ae23476e078038b806cf
part 5: 0xcd68d4a8a58dac3891b6dfeafb33c764fa94dbc7c6ef7543589d30f6e86565db
```

### Mode recover

Input data (stdin):
```
T or more lines with parts of secret (each line has a part of secret in the same format as the program output in split mode)

End of input is empty line
```

Output data (stdout):
```
Secret string in the same form as before division
```

Example input:
```
part 3: 0xc6ec495ff5954b7f1546a2147d6a24519c35dd0360e2d85c34cc06639d395cdb
part 5: 0xcd68d4a8a58dac3891b6dfeafb33c764fa94dbc7c6ef7543589d30f6e86565db
part 1: 0xc36ddc11cfc30d54f7eb2db0854ca2b01949f6fc9a9a00d90b2f7d38a2c8283b

```

Example output:
```
Recovered secret: 
0xc2cdf0a8b0a83b35ace53f097b5e6e6a0a1f2d40535eff1cf434f52a43d59d8f
```
