import datetime
def getMinuteInRomanNumerals(romanInt = None):
    if romanInt == None:
        romanInt = int(str(datetime.datetime.now().time())[3:5])

    roman = ""
    if (romanInt >= 50):
        romanInt -= 50
        roman += "L."
    while (romanInt >= 10):
        romanInt -= 10
        roman += "X."
    if (romanInt >= 5):
        romanInt -= 5
        roman += "V."
    while (romanInt >= 1):
        romanInt -= 1
        roman += "I."
    roman += "a" * (len(roman)//2)
    return roman

def requiredAtomicNumber(inp, goal = 780):
    ans = ""
    # if "I" in inp:
    #     goal -= 53
    # if "V" in inp:
    #     goal -= 23
    # goal -= 19 + 36 #Krakov if only capital
    # goal -= 19 + 8 + 23 + 88 #Krakov if only lowercase
    for x in inp: # for roman numerals
        if x == "I": goal -= 53
        if x == "V": goal -= 23
    elements = ["Og", "Ts", "Rg", "Sg", "Rf", "Es", "At", "As", "Ge", "Ga", "Ar", "P", "N", "B", "Be", "H"]
    # nums = [(118 + 8), 117, 111, (106 + 16), (104 + 9), 99, 85, 33, 32, 31, 18, 15, 7, 5, 4, 1]
    nums = [(118 + 8), 117, 111, (106 + 16), (104), 99, 85, 33, 32, 31, 18, 15, 7, 5, 4, 1]

    ans += "H.a." * (goal)

    return ans