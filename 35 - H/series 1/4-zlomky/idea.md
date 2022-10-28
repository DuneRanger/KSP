# Concept
For even Y's I need p/Y where p is a prime number and Y <= N
For odd Y's I need X/Y where X < Y and Y <= N

Prime number generation: O(N)
Generate all even numbers: O(N \* P)

P = N/ln(N)

P nezapočítá {2}, ale počítá {1}

Generate 1 odd number: N/2 \+ (N/2 \- D) = O(N-D)
                Even versions + odd versions (where D is every odd divisor of N)

Generating all divisors of N: O(N^(1/3))

Generate all odd numbers: N/2 \* (N/2 \+ (N/2 \- D)) = O(N \* (N-D))

==> Compare N/ln(N) and N-D
The larger of the which is now M
===> O(N \* M)

N-D grows faster than N/ln(N)
(Because D barely grows at all and N is linear)