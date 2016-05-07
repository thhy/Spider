#include "simplehash.h"

SimpleHash::SimpleHash()
{

}

SimpleHash::SimpleHash(int cap, int seed)
{
    this->cap = cap;
    this->seed = seed;
}

int SimpleHash::hash(std::string value)
{
    int result = 0;
    int len = value.length();
    for(int i = 0;i<len;++i)
    {
        result = result * seed + value.at(i);
    }
    return (cap - 1) & result;
}

SimpleHash &SimpleHash::operator=(const SimpleHash *hash)
{
	this->cap = hash->cap;
	this->seed = hash->seed;
	return *this;
}
