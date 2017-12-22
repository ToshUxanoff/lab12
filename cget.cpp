#include <iostream>
#include <functional>
#include <future>
#include <thread>
#include <curl/curl.h>

void GetResponse(std::future<char*> &Future)
{
    CURL *curl;
    CURLcode res;
    char *url = Future.get();
    curl = curl_easy_init();
    if (curl) {
      curl_easy_setopt(curl, CURLOPT_URL, url);
      curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
    }
    res = curl_easy_perform(curl);
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    std::cout << "Response answer: " << http_code << '\n';
}

int main(int argc, char *argv[])
{
    char *url = argv[1];
    std::promise<char*> Promise;
    std::future<char*> Future = Promise.get_future();
    std::thread Thread (GetResponse, std::ref(Future));
    Promise.set_value(url);
    Thread.join();
    return 0;
}
