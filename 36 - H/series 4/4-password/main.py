from helper import *

number = input()
number = number.split()[-1][:-1]

with open("test.txt", 'a') as f:
    f.write("\n" + number + " ")

password = "aaaaAAAAA1._"
# password = "KrakovAAAAA1._"
password += getMinuteInRomanNumerals() + "_"
password += requiredAtomicNumber(password) + "_"

# password += "T"

print(password)



