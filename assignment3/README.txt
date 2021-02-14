During our development we experienced power outage so we could not complete it before Saturday night.


bucket.txt contains the structure of the Linear Hash table i.e. metadata and where each block
exists (the "pointer") in EmployeeIndex.
EmployeeIndex contains all blocks.

Guide to bucket.txt
The first 4 lines are all metadata
1-Empty overflow blocks
2-Number of records
3-Number of buckets
4-Number of blocks

The structure of the block is
1-Offset (We used seekg so its 4096*offset to get the right block)
2-Number of overflowblocks
X-offset for the overflow blocks

E.X. this is the starting linear hash with i=1 so there is only bucket '0' and bucket '1'

0 (Empty overflow blocks)
0 (Number of records)
2 (Number of buckets)
2 (Number of blocks)
0 (Location of bucket '0')
0 (No overflow)
1 (Location of bucket '1')
0 (No overflow)

Execution (runs on c++11)
g++ -std=c++11 finaldraft.cpp
a.out C
or
a.out L (id) 
**check notes on id

**Notes** 
Bit flipping is not required for this because the bucket will always grow the same way
e.g. [0,1] will always become [00,01,10,11] and we track the bucket keys such that they contain
both levels h0 and h1. So, based on N (number of bukets/ size of the index) we know what the h1 is
so we can match with the key id. And because we track both h0 and h1, we will cover every possible 
hash value

When we remove an overflow during redistribution, the actual block in EmployeeIndex is not removed. Instead, the offset value is removed from bucket.txt so that you will never read that
block again. All the records are distributed normally.

ID values cannot be bigger than what can be represtend by a long variable

If you want to rebuild a new linear hash table you must reset the bucket.txt back to its starting form i.e.
0
0
2
2
0
0
1
0


