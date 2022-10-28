Use uint64_t for possibilites

Base possibilities: 2^N where N is the amount of question marks

Limitations:
The base difference between up and down must be made up within the question marks
    => 2^(N-1) only searching for equality 
    For each difference (X) -> N-=X and 2^(N-1)*X
I cannot go under 0 height
    I will always start at height >= 0
    So something based on start height?