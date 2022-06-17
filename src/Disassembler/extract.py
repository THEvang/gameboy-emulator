import sys
import json

if len(sys.argv) < 2:
    print("usage: ", sys.argv[0], "json")
    exit(0)

with open(sys.argv[1], 'r') as f:
    data = json.load(f)

    fs = ";"
    for code in data["unprefixed"]:
        op = data["unprefixed"][code]
        print(code, end=fs)
        print(op["mnemonic"], end=fs)
        for operand in op["operands"]: 
            print(operand["name"], end =",")
        print(end=fs)
        print(op["bytes"], end=fs)
        print()

