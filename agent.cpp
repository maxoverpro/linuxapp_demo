#include    <string>
#include    <iostream>
#include    <cstring>
#include    <curl/curl.h>

using namespace std;

size_t callBackFunk(char* ptr, size_t size, size_t nmemb, string* stream)
{
    int realsize = size * nmemb;
    stream->append(ptr, realsize);
    return realsize;
}

string url_post_proc (const char url[],const char post_data[])
{
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    string chunk;

    if (curl)
        {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(post_data));
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callBackFunk);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (string*)&chunk);
        curl_easy_setopt(curl, CURLOPT_PROXY, "");
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        }
		    if (res != CURLE_OK) {
        cout << "curl error" << endl;
        exit (1);
    }

    return chunk;
}

int main (int argc,char *argv[])
{

    char url_target[] = "http://192.168.56.1:8080/api/saveproc";
    char post_data[] = "title=linux&content=linux app";

    string str_out = url_post_proc (url_target,post_data);

    cout << str_out << "\n";


    return 0;
}



