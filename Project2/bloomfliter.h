#ifndef BLOOMFLITER_H
#define BLOOMFLITER_H

#include <bitset>
#include "simplehash.h"
class BloomFliter
{
public:
    BloomFliter();
    bool contain(std::string url);
    void add(std::string url);

private:
	
	const static int DEFAULT_SIZE = 2<<10;
	std::bitset<DEFAULT_SIZE> bits;
    SimpleHash *fun;
	static int seed[6];
};

#endif // BLOOMFLITER_H
