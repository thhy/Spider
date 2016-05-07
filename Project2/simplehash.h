#ifndef SIMPLEHASH_H
#define SIMPLEHASH_H

#include <iostream>
class SimpleHash
{
public:
    SimpleHash();
    SimpleHash(int cap,int seed);
    int hash(std::string value);
	SimpleHash &operator = (const SimpleHash *hash);
private:
    int cap;
    int seed;
};

#endif // SIMPLEHASH_H
