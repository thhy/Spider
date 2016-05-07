#include "downloadurl.h"

DownloadUrl::DownloadUrl()
{
	//伪造为火狐浏览器
	MyUrl tmp("http://vdisk.weibo.com/s/arya70XpqzOlK",1);
	this->url = tmp;
	useAgent = "Mozilla/4.0 (Windows NT 6.2; WOW64; rv:21.0) Gecko/20100101 Firefox/21.0";
}

DownloadUrl::DownloadUrl(MyUrl url)
{
	this->url = url;
	useAgent = "Mozilla/5.0 (compatible; Baiduspider/2.0; +http://www.baidu.com/search/spider.html)";
	//useAgent = "Mozilla/5.0 (Windows; U; Windows NT 5.1; sv-SE; rv:1.7.5) Gecko/20041108 Firefox/1.0";
}

DownloadUrl::DownloadUrl(MyUrl url,std::string filename)
{
	this->url = url;
	this->filename = filename;
}
DownloadUrl &DownloadUrl::operator=(const MyUrl &myurl)
{
	this->url = myurl;
	return *this;
}

//将传输过来的html文件存储到string中
size_t DownloadUrl::writeFun(void *ptr, size_t size, size_t nmemb, void *stream)
{
	std::string *userdata = (std::string *)stream;
	if(ptr!=NULL)
	{
		userdata->append((char *)ptr);
	}
	return size*nmemb;
}

void DownloadUrl::init()
{

	

	//mutex = new QMutex();
	this->m_curl = curl_easy_init();
	if(m_curl)
	{
		//curl_slist_append(m_curl,"use-agent:Mozilla/5.0 (Windows NT 6.1; WOW64; rv:17.0) Gecko/20100101 Firefox/17.0 IceDragon/18.0.1.0");
		curl_easy_setopt(m_curl,CURLOPT_USERAGENT,useAgent.c_str());
		curl_easy_setopt(m_curl,CURLOPT_WRITEFUNCTION,this->writeFun);
		curl_easy_setopt(m_curl,CURLOPT_WRITEDATA,&this->htmldata);
		curl_easy_setopt(m_curl,CURLOPT_TIMEOUT,5000);
		//curl_easy_setopt(m_curl,CURLOPT_HEADERDATA,this->header);

	}

}

void DownloadUrl::run()
{
	if(!m_curl)
	{
		std::cerr<<"please initialize"<<std::endl;
	}
	curl_easy_setopt(m_curl,CURLOPT_URL,url.getUrl().c_str());//设置下载url
	//visitedQueue.insert(url.getUrl());//将访问过的url加入到访问队列
	CURLcode res = curl_easy_perform(m_curl);
	if(res==CURLE_OK)
	{

	}

	std::ofstream out(filename.c_str());
	out<<this->htmldata.c_str();
	out.close();
#ifdef _DEBUG
	//std::cout<<this->htmldata<<std::endl;
#endif
	//htmldata.clear();
}


//void DownloadUrl::Stop()
//{
//
//
//}

std::string DownloadUrl::htmlData()
{
	return this->htmldata;
}

DownloadUrl::~DownloadUrl()
{
	curl_easy_cleanup(m_curl);
//	curl_global_cleanup();
}