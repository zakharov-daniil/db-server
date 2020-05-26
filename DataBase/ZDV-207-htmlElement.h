//
//  htmlElement.h
//  DataBase
//
//  Created by Daniil Zakharov on 23.05.2020.
//  Copyright © 2020 Daniil Zakharov. All rights reserved.
//

#ifndef htmlElement_h
#define htmlElement_h
#include <vector>
#include <string>
#include <map>

struct htmlElem{
    std::vector<htmlElem> children;
    std::string textContent;
    std::map<std::string, std::string> style;
    std::string render() const{
        std::string res = "<div style=\"";
        for(auto key_v:style){
            res += key_v.first + ":" + key_v.second + ";";
        }
        res+="\">";
        res += textContent;
        for(const auto &c:children){
            res += c.render();
        }
        return res+"</div>";
    }
    
    htmlElem(){}
    
};

#endif /* htmlElement_h */
