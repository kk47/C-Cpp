#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>

struct mycomp {
    bool operator() (const std::string& k1, const std::string& k2) const {
        if (k1.size() < k2.size()) {
            return true;
        } else if (k1.size() == k2.size()) {
            if (k1.compare(k2) < 0) return true;
        } else {
            return false;
        }
    }
};

int main()
{
    std::map<std::string, std::string, mycomp> mymap;
    std::map<std::string, std::string, mycomp>::value_type e("kk-d01", "UP-d10");
    mymap.insert(e);
    std::map<std::string, std::string, mycomp>::value_type f("kk-d103", "UP-d104");
    mymap.insert(f);
    std::map<std::string, std::string, mycomp>::value_type g("kk-d104", "UP-d103");
    mymap.insert(g);
    std::map<std::string, std::string, mycomp>::value_type h("kk-d12", "UP-d01");
    mymap.insert(h);
    /*mymap["d10"] = "UP";
    mymap["d11"] = "DOWN";
    mymap["d101"] = "UP";
    mymap["d102"] = "DOWN";*/
    
    std::map<std::string, std::string, mycomp>::iterator it = mymap.begin();
    for(; it != mymap.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }
    it = mymap.find("kk-d12");
    if(it != mymap.end()) {
        it->second = "UP-d12";
    }
    it = mymap.begin();
    for(; it != mymap.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }
    return 0;
}
