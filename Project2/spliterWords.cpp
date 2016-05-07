#include "spliterWords.h"


SpliterWords::SpliterWords(void)
{
}

SpliterWords::SpliterWords(std::string segment)
{
	this->segment = segment;
}

bool SpliterWords::spliterSegment(std::string str,std::string ret,std::vector<std::string> &spliterWords)
{
	int pos = str.find(ret);
	std::string tmp;
	while(pos!=-1)
	{
		spliterWords.push_back(str.substr(0,pos));
		str = str.substr(pos+1,str.length()-pos-1);

		pos = str.find(ret);
	}

	return true;
}

bool SpliterWords::removeStopWords()
{
	if(!NLPIR_Init())
	{
		std::cerr<<"nplir init failed"<<std::endl;
		return false;
	}
	const char *nlpirFiner = NLPIR_FinerSegment(segment.c_str());
	std::cout<<"finer words:"<<nlpirFiner<<std::endl;

	std::ifstream stopWordsFile("stopwords.txt");

	std::vector<std::string> stopWords;

	while (!stopWordsFile.eof())
	{
		char tmp[100];
		stopWordsFile>>tmp;
		std::string tmpstr(tmp);
		stopWords.push_back(tmpstr);
	}

	std::string finerWords(nlpirFiner);

	std::vector<std::string> spliterWords;
	spliterSegment(finerWords,"#",spliterWords);

	for(auto str:spliterWords)
		std::cout<<str.c_str()<<std::endl;

	for(std::vector<std::string>::iterator searchit = spliterWords.begin();searchit!=spliterWords.end();)
	{
		bool isDelete = false;
		for (auto stopit = stopWords.begin(); stopit!=stopWords.end(); stopit++)
		{
			if(strcmp(searchit->c_str(),stopit->c_str())==0)
			{
				searchit = spliterWords.erase(searchit);
				isDelete = true;
				break;
			}
		}
		if(!isDelete)
			++searchit;
	}

}

SpliterWords::~SpliterWords(void)
{
}
