#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <vector>
#include <map>
using namespace std;


// json序列化示例1
string func1(){
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello, what are you doing now?";

    string sendBuf = js.dump();
    return sendBuf;
}

string func2(){
    json js;

    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);

    js["list"] = vec;

    map<int, string> m;
    m.insert({1, "黄"});
    m.insert({2, "华"});
    m.insert({3, "泰"});

    js["path"] = m;

    string sendBuf = js.dump();
    return sendBuf;
}

int main(){
    string recBuf = func1();

    // 反序列化，字符串转为容器
    json jsBuf = json::parse(recBuf);
    cout << jsBuf["msg_type"] << endl;
    cout << jsBuf["from"] << endl;
    cout << jsBuf["to"] << endl;
    cout << jsBuf["msg"] << endl;

    return 0;
}