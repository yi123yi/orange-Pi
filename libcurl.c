#include <stdio.h>
#include <curl/curl.h>

/*

http 获取信息

调用curl_global_init()初始化libcurl
调用curl_easy_init()函数得到 easy interface型指针
调用curl_easy_setopt()设置传输选项
根据curl_easy_setopt()设置的传输选项，实现回调函数以完成用户特定任务
调用curl_easy_perform()函数完成传输任务
调用curl_easy_cleanup()释放内存

*/


 
int getUrl(char *filename)
{
    CURL *curl;
    CURLcode res;
    FILE *fp;
    if ((fp = fopen(filename, "w")) == NULL)  // 返回结果用文件存储
        return false;
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: Agent-007");
    curl = curl_easy_init();    // 初始化
    if (curl)
    {
        //curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");// 代理
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);// 改协议头
        curl_easy_setopt(curl, CURLOPT_URL,"http://www.baidu.com");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); //将返回的http头输出到fp指向的文件
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, fp); //将返回的html主体数据输出到fp指向的文件
        res = curl_easy_perform(curl);   // 执行
        if (res != 0) {

            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
        fclose(fp);
        return true;
    }
}
int postUrl(char *filename)
{
    CURL *curl;
    CURLcode res;
    FILE *fp;
    if ((fp = fopen(filename, "w")) == NULL)
        return false;
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "/tmp/cookie.txt"); // 指定cookie文件
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "&logintype=uid&u=xieyan&psw=xxx86");    // 指定post内容
        //curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");
        curl_easy_setopt(curl, CURLOPT_URL, " http://mail.sina.com.cn/cgi-bin/login.cgi ");   // 指 定url
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    fclose(fp);
    return true;
}
int main(void)
{
    getUrl("/tmp/get.html");
    postUrl("/tmp/post.html");
}


/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>

// 回调函数，用于处理HTTP响应数据
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;
    char **response_buffer = (char **)userp;

    // 分配足够的内存来存储响应数据
    *response_buffer = (char *)realloc(*response_buffer, total_size + 1);

    if (*response_buffer) {
        // 将响应数据拷贝到response_buffer中
        memcpy(*response_buffer, contents, total_size);
        (*response_buffer)[total_size] = '\0';
    }

    return total_size;
}

int main() {
    CURL *curl;
    CURLcode res;
    char *response_buffer = NULL;

    // 初始化libcurl
    curl = curl_easy_init();
    if (curl) {
        // 设置Flask应用程序的URL
        const char *url = "http://localhost:8080/tracking_data";

        // 构建JSON数据
        const char *json_data = "{\"z\": 45.0}";  // 这是一个示例JSON数据

        // 设置HTTP POST请求
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);

        // 设置回调函数来处理响应数据
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_buffer);

        // 执行HTTP POST请求
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // 成功接收到响应数据，现在可以解析JSON响应
            struct json_object *root = json_tokener_parse(response_buffer);
            if (root) {
                // 提取JSON响应中的数据
                struct json_object *status_obj;
                if (json_object_object_get_ex(root, "status", &status_obj)) {
                    const char *status = json_object_get_string(status_obj);
                    printf("Received status: %s\n", status);
                } else {
                    printf("JSON response does not contain 'status' key\n");
                }

                // 释放JSON对象
                json_object_put(root);
            } else {
                printf("Failed to parse JSON response\n");
            }
        }

        // 释放libcurl资源
        curl_easy_cleanup(curl);
        if (response_buffer) {
            free(response_buffer);
        }
    }

    return 0;
}
*/