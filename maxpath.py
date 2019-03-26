import sys
from dataclasses import dataclass

with open(sys.argv[1]) as f:
    pyramid = f.readlines();

@dataclass
class Node:
    value: int;
    isPrime : bool;
    

