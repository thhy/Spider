#pragma once
#include <iostream>
#include <vector>
#include "include\NLPIR.h"
#include <fstream>

#pragma comment(lib,"NLPIR.lib")
class SpliterWords
{
public:
	SpliterWords(void);
	SpliterWords(std::string segment);
	bool spliterSegment(std::string str,std::string ret,std::vector<std::string> &spliterWords);
	bool removeStopWords();


	~SpliterWords(void);

private:
	
	std::string segment;

	std::vector<std::string> spliterWords;
	std::vector<std::string> result;

};

