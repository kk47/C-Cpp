#include <json/json.h>
#include <iostream>
#include <vector>
#include <string>

void WriteJsonData(const char* filename)
{    
    // Json object <-> file
    Json::Reader reader;
    Json::Value root;
    ifstream is;
    is.open(filename, std::ios::binary);
    if (reader.parse(is, root, FALSE)) {
        Json::Value item;
        root["key"] = "value1"; 
        // add new item
        item["arraykey"] = 2; 
        root["array"].append(item)

        Json::FastWriter writer;
        string strWrite = writer.write(root);
        ofstream ofs;
        ofs.open(filename);
        ofs << strWrite;
        ofs.close();
    }
    is.close();  
}

int main()
{
    // json string to json object
    std::string str = "{\"key\":\"value1\",\"array\":[{\"arraykey\":1},{\"arraykey\":2}]}";
    Json::Reader reader;
    Json::Value root;
    if(reader.parse(str, root)) {
        if(!root["key"].isNull()) {
            std::cout << root["key"].asString() << std::endl;
        }
    }
    
    Json::Value arrObj = root["array"];
    for(int i = 0; i < arrObj.size(); i++) {
        int iarrValue = arrObj[i]["arraykey"].asInt();
        std::cout << iarrValue << std::endl;
    }
    
    // Json object to string
    Json::Value item; 
    for (int i=0; i<10; i++)
    { 
      item["arraykey"] = i; 
      arrObj.append(item);
    } 
    root["array"] = arrObj; 
    std::string out = root.toStyledString();
    std::cout << out << std::endl;    
    
    // clear object
    root["array"].resize(0);
    
    // delete json object
    root.removeMember("key");
    std::string out = root.toStyledString();
    std::cout << out << std::endl;    
    return 0;  
}
