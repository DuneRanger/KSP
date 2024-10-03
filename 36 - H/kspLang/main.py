code = ""

def push(x):
    global code
    if x >= 0:
        if x >= 1155:
            push(1)
            code += """praise qeq qeq qeq pop
cs cs ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ pop2 cs cs funkcia ++ ++ u """
            code += "++ " * (x-1155)
        elif x >= 1078:
            push(1)
            code += """praise qeq qeq qeq pop
cs cs ++ ++ ++ ++ ++ ++ ++ ++ ++ pop2 cs cs funkcia ++ ++ u """
            code += "++ " * (x-1078)
        elif x >= 924:
            push(1)
            code += """praise qeq qeq qeq pop
cs cs ++ ++ ++ ++ ++ ++ ++ pop2 cs cs funkcia ++ ++ u """
            code += "++ " * (x-924)
        elif x >= 866:
            push(1)
            code += """praise qeq qeq pop cs cs funkcia u
cs cs funkcia ++ ++ ++ ++ cs cs funkcia ++ ++ u
cs cs pop2 cs funkcia u
cs cs pop2 cs funkcia u """
            code += "++ " * (x-866)
        elif x >= 821:
            push(1)
            code += """praise qeq cs cs funkcia u
cs cs funkcia ++ ++ cs u
cs cs pop2 cs funkcia u
cs cs pop2 cs funkcia u
cs cs funkcia u
cs cs pop2 cs funkcia u
pop2
cs cs pop2 cs funkcia u\n"""
            code += "++ " * (x-821)
        elif x >= 225:
            push(1)
            code += "praise qeq qeq qeq pop2 "
            code += "++ " * (x-225)
        elif x >= 63:
            push(1)
            code += "praise qeq qeq pop2 funkcia funkcia ++ % "
            code += "++ " * (x-63)
        else:
            code += "cs cs lensum cs funkcia"
            for i in range(x):
                code += " ++"
            code += "\n"
    else:
        if (x == -1):
            push(1)
            code += "cs cs cs % qeq\n"
        elif (x > -10):
            push(abs(x))
            code += "cs cs % ++ cs cs % qeq\n"
        else:
            push(-1)
            code += "cs"
            for i in range(abs(x)-1):
                code += " ++"
            code += "\n"
            push(2)
            code += "u\n"
        

def gap():
    global code
    code += "\n\n"

def negate():
    # 10
    global code
    code += "cs cs lensum cs funkcia ++ cs cs % qeq\n"

def minusMinus():
    global code
    push(-1)
    push(0)
    code += "u\n"

def dup_64b():
    global code
    # 56
    code += """cs cs lensum cs funkcia cs
++ ++ ++
m cs cs ++ gcd ++ max cs cs % qeq
cs cs cs ++ ++ qeq pop2
cs j ++ cs praise qeq qeq pop2 funkcia funkcia ++ % bitshift
cs cs gcd cs ++ lroll
cs u
cs cs pop2 cs lensum m pop2 pop2\n"""

def dup_32b():
    global code
    # 32
    code += """cs cs lensum ++ cs lensum ++ cs ^^
cs cs lensum m
cs cs lensum cs lensum ++ % 
cs u cs bitshift ++ bitshift 
cs cs lensum m
pop2 pop2\n"""

def dup_32b_pos():
    global code
    dup_32b()

# this works for numbers less than 3
def dup_32b_neg():
    global code
    # 19
    code += "cs cs lensum ++ cs lensum ++ cs ^^\n"
    negate()
    code += "cs cs lensum m pop2 pop2\n"

def swapTopTwo():
    global code
    # 9
    push(1)
    code += "cs ++ lroll\n"

def lrollX(x, y = 1):
    global code
    if (y < 0 and x > -y and y > -10):
        push(y)
        code += "cs " + "++ " * (x+y) + "lroll\n"
    elif (x > y and y < 10):
        push(y)
        code += "cs " + "++ " * (x-y) + "lroll\n"
    elif(x > 5 and x < 10):
        push(x)
        code += "cs " + "++ " * (y-x)
        swapTopTwo()
        code += "lroll\n"
    else:
        push(y)
        push(x)
        code += "lroll\n"


def notZero():
    # 56
    global code
    push(5)
    code += "u\n"
    code += "cs pop2 "
    minusMinus()

def sequence():
    global code
    push(0)
    code += "cs pop pop\n"
    dup_32b()
    minusMinus()
    code += "cs "
    push(6)
    swapTopTwo()
    notZero()
    code += "BRZ pop pop\n"

def OldsortTopTwo():
    global code
    # 202 (effective 200 (because of rel jump in dup64b))
    dup_64b()
    lrollX(3, 2)
    dup_64b()
    lrollX(4)
    negate()
    swapTopTwo()
    negate()
    code += "max\n"
    lrollX(3)
    code += "max\n"
    swapTopTwo()
    negate()
    swapTopTwo()

def sortTopTwo():
    global code
    # 487
    dup_64b()
    lrollX(3, 2)
    dup_64b()
    lrollX(4)
    push(5)
    code += "u\n"
    swapTopTwo()
    push(5)
    code += "u\n"
    negate()
    code += "cs cs funkcia " # quick zero
    code += "u\n"

    # logic for skipping ahead
    code += "cs "
    push(5)
    code += "u\n"
    push(230)
    # code += "cs praise qeq qeq qeq pop2 ++ ++ ++\n" # quick 228
    push(2)
    code += "u\n"
    code += "j\n"

    gap()
    # Solves signum(x) == signum(y)
    code += "pop pop\n"
    dup_64b()
    lrollX(3, 2)
    dup_64b()
    lrollX(4)
    code += "max\n"
    swapTopTwo()
    dup_64b()
    lrollX(3)
    push(1)
    code += "u\n"
    push(5)
    code += "u\n"
    gap()

    # End of jump
    code += "cs pop\n"

    # actually swaps x and y based on (-1,-2,0 == 0 - no swap) (1,2 == 1 - swap)
    minusMinus()
    code += "cs cs funkcia ++ ++ ++ ++ ++\n" # quick five
    code += "u ++\n"
    code += "cs cs funkcia ++ ++ ++ ++ ++ u\n"

    code += "cs cs funkcia ++ ++ lroll\n"

def newSort():
    global code
    # iterator 1 = stack size left to sort
    # iterator 2 = iterator for current bubble sort run

    # additional logic, for if the stack only has 1 member
    push(0)
    code += "cs cs pop pop "
    code += "j pop "

    # prepare iterator 1 and iterator 2
    minusMinus()

    # additional logic, for if the stack only has 1 member
    code += "cs "
    push(1155)
    swapTopTwo()
    code += "brz pop pop\n"
    gap()

    dup_32b_pos()
    # preparation for iterator 2 & 1
    code += "cs cs pop pop "
    # move number pair to sort to the top
    lrollX(4, 2)
    gap()

    sortTopTwo()
    gap()

    # get iterator 1 to the top to move unsorted stack by one
    lrollX(4, 3)
    dup_32b_pos()
    lrollX(5)
    code += "++ ++ ++ "
    push(1)
    swapTopTwo()
    code += "lroll\n"
    gap()

    # get iterators back to the top, to decrement iterator 2
    lrollX(3, 1)
    minusMinus()
    gap()

    # logic for iterator 2
    dup_32b_pos()
    notZero()
    push(105)
    swapTopTwo()
    code += "brz pop pop\n"
    gap()

    # At this point, the lowest number should be at the top (under both iterators)
    # prepare and recreate iterators
    code += "pop "
    minusMinus()
    dup_32b_pos()
    gap()

    # move lowest number to the bottom of the stack
    dup_32b_pos()
    lrollX(4, 2)
    code += "++ ++ ++ ++\n"
    push(1)
    swapTopTwo()
    code += "lroll\n"
    gap()

    # iterator 1 logic (iterator 2 is currently on the top)
    swapTopTwo()
    dup_32b_pos()
    lrollX(3)
    notZero()
    push(105)
    swapTopTwo()
    code += "brz pop pop\n"
    code += "pop pop\n"

    code += "cs pop " * 25
    code += "cs ++ cs cs cs pop pop pop pop"


newSort()



print(code)
print(len(code.split()))

import subprocess
subprocess.run("clip", text=True, input=code)