#include "paserurl.h"

PaserUrl::PaserUrl()
{

}

PaserUrl::PaserUrl(std::string filename)
{
	this->filename = filename;
	init();
}

PaserUrl::PaserUrl(std::string filename,MyUrl url)
{
	this->filename = filename;
	this->currentUrl = url;
}

PaserUrl &PaserUrl::operator=(const PaserUrl& paser)
{
	this->filename = paser.filename;
	this->currentUrl = paser.currentUrl;
	return *this;
}

void PaserUrl::init()
{
	this->urlMatch = std::regex("((http|ftp|https)://)(([a-zA-Z0-9\._-]+\.[a-zA-Z]{2,6})|([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}))(:[0-9]{1,4})*(/[a-zA-Z0-9\&%_\./-~-]*)?");
	std::ifstream htmlFile(filename.c_str());
	while(htmlFile.eof())
	{
		std::string tmp;
		htmlFile>>tmp;
		html.append(tmp);
		htmlFile.close();
	}
}

std::string UTF8_To_string(const std::string & str) 
{ 
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0); 

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	memset(pwBuf, 0, nwLen * 2 + 2); 

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen); 

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL); 

	char * pBuf = new char[nLen + 1]; 
	memset(pBuf, 0, nLen + 1); 

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL); 

	std::string retStr = pBuf; 

	delete []pBuf; 
	delete []pwBuf; 

	pBuf = NULL; 
	pwBuf = NULL; 

	return retStr; 
} 

std::string string_To_UTF8(const std::string & str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete []pwBuf;
	delete []pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

void PaserUrl::getUrl(std::priority_queue<MyUrl> &downloadQueue)
{
	////匹配url的正则表达式
	//static bool first = true;
	//std::string pattern;
	//if (first)
	//{
	//	first = true;
	//	pattern = "((http|ftp|https)://)(([a-zA-Z0-9\._-]+\.[a-zA-Z]{2,6})|([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}))(:[0-9]{1,4})*(/[a-zA-Z0-9\&%_\./-~-]*)?";
	//}
	//else{
	//	pattern = "src=\"(([a-zA-Z0-9\._-]+\.[a-zA-Z]{2,6})|([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}))(:[0-9]{1,4})*(/[a-zA-Z0-9\&%_\./-~-]*)?";
	//}
	//std::regex r(pattern);

	int srcPos[DEFSIZE];
	int hrefPos[DEFSIZE];

	memset(srcPos,0,DEFSIZE);
	memset(hrefPos,0,DEFSIZE);

	findAll(html.c_str(),html.length(),"src=",srcPos);
	findAll(html.c_str(),html.length(),"href=",hrefPos);

	auto srcBegin = html.c_str();
	int endSrc;
	std::string urlBuf;
	std::vector<std::string> urls;
	for(int i = 0;srcPos[i]!=0;++i)
	{
		if(srcPos[i]+4<html.length()){
			endSrc = find_first(srcBegin+srcPos[i]+5,"\"");
			if(endSrc!=0)
			{
				std::string tmp = html.substr(srcPos[i]+5,endSrc);
				if(tmp.at(0) =='\.')
					tmp = getRelUrl(this->currentUrl.getUrl(),tmp.substr(1,tmp.length()-1));
				if(std::regex_match(tmp,urlMatch)&&!fliter.contain(tmp.c_str()))
				{
					MyUrl newUrl(tmp,1);
					downloadQueue.push(newUrl);
#ifdef _DEBUG
					std::cout<<newUrl.getUrl()<<std::endl;
#endif
				}
			}
		}
	}

	for(int i = 0;hrefPos[i]!=0;++i)
	{
		if(hrefPos[i]+6<html.length()){
			endSrc = find_first(srcBegin+hrefPos[i]+7,"\"");
			if(endSrc!=0)
			{
				std::string tmp = html.substr(hrefPos[i]+6,endSrc);
				if(tmp.at(0) =='\.')
					tmp = getRelUrl(this->currentUrl.getUrl(),tmp.substr(1,tmp.length()-1));
				if(std::regex_match(tmp,urlMatch)&&!fliter.contain(tmp.c_str()))
				{
					MyUrl newUrl(tmp,1);
					downloadQueue.push(newUrl);
#ifdef _DEBUG
					std::cout<<newUrl.getUrl()<<std::endl;
#endif
				}
			}
		}
	}
}

void PaserUrl::paserTitleAndContent()
{
	try{
	if(!HPR_Init("","LingjoinHtmlParse*~!@#$%&*(^^^)*&%$#@!~*"))
	{
		std::cout<<"HPR_Init failed";
		exit(1);
	}
	HPR_ParseFile(filename.c_str());
	this->title = UTF8_To_string( HPR_GetTitle());
	this->content =UTF8_To_string( HPR_GetContent());
	//HPR_Exit();
	}
	catch(std::exception e)
	{
		std::cerr<<e.what();
		return ;
	}
}

std::string PaserUrl::getTitle()
{
	return this->title;
}

std::string PaserUrl::getContent()
{
	return this->content;
}

void PaserUrl::paserKeyWords()
{
	int metapos = 0;

	int metaLength = 0;
	std::string metaStr;
	metapos = html.find("meta name=\"keywords\"");
	if(metapos==-1)
		this->KeyWords = "";
	for(int i = 0;i<html.length();++i)
	{

		if(html.at(metapos+i)=='>')
		{
			metaLength=i;
			break;
		}
	}

	if(metapos!=-1&&metaLength!=0)
	{
		metaStr = html.substr(metapos+4,metaLength-2);

		std::ofstream out("out.txt",std::ios::app);

		out<<metaStr.c_str();

		out.close();

	}

	std::string metaKeywods;

	if(metaStr.find("name=\"keywords\"")!=-1)
	{
		int keywordspos = metaStr.find("content=");
		metaKeywods = metaStr.substr(keywordspos+8,metaStr.length()-keywordspos+1);
		std::cout<<UTF8_To_string(metaKeywods);
		this->KeyWords = metaKeywods;
	}
			this->KeyWords = "";
}

std::string PaserUrl::getKeyWords()
{
	return this->KeyWords;
}

int PaserUrl::find_first(const char *ch,const char *match)
{
	int pos;
	bool isMatch = true;
	for(int i = 0;ch[i]!='\0';++i)
	{
		for(int j = 0;match[j]!='\0';)
		{
			const char tmp= ch[i+j];
			if(tmp==match[j])
			{
				++j;
				isMatch = true;
			}
			else
			{
				isMatch = false;
				break;
			}
		}
		if(isMatch)
			return i;
	}
	return 0;
}

void PaserUrl::findAll(const char *ch,int length,const char *match,int *result)
{
	int pos = 0;
	bool isMatch = true;
	for(int i = 0;i<length;++i)
	{
		for(int j = 0;match[j]!='\0';)
		{
			const char tmp= ch[i+j];
			if(tmp==match[j])
			{
				++j;
				isMatch = true;
			}
			else
			{
				isMatch = false;
				break;
			}
		}
		if(isMatch)
			result[pos++] =  i;
	}
}

std::string PaserUrl::getRelUrl(std::string index,std::string relUrl)
{
	return index+relUrl;
}

void PaserUrl::parser(std::string htmldata,std::priority_queue<MyUrl> &downloadQueue)
{
	if(htmldata.empty())
		return ;
	this->html = htmldata;
	this->getUrl(downloadQueue);
	this->paserTitleAndContent();
//	this->paserKeyWords();
}


PaserUrl::~PaserUrl()
{
	
}