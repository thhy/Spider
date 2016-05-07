#ifndef DOWNLOADURL_H
#define DOWNLOADURL_H

#include <iostream>
#include <unordered_set>
#include "curl/curl.h"
//#include <QThread>
#include "myurl.h"
//#include <QMutex>
//#include "paserurl.h"
#include <queue>
#include <fstream>

#pragma comment(lib,"libcurl.lib")

class DownloadUrl
{
public:
    DownloadUrl();
	DownloadUrl(MyUrl url);
	DownloadUrl(MyUrl url,std::string filename);
	DownloadUrl & operator = (const MyUrl &url);
    void init();
	void run();
    static size_t writeFun(void *ptr, size_t size, size_t nmemb, void *stream);
    void stop();
	bool isComplete();
	std::string htmlData();
	~DownloadUrl();
    
private:
    
//    std::unordered_set<std::string>::iterator it;
    std::string htmldata;
	MyUrl url;
    CURL* m_curl;
    //QMutex *mutex;
   // PaserUrl *paser;
//    struct curl_slist *header;
    std::string useAgent;//伪造火狐浏览器usr-agent
	std::string filename;
};

#endif // DOWNLOADURL_H
