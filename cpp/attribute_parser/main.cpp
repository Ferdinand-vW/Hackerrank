#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Attribute {
    std::string name;
    std::string value;
};

struct HMRL {
    std::string name;
    std::vector<Attribute> attributes;
    std::vector<HMRL> content;
};

struct Query {
    std::vector<std::string> tags;
    std::string attribute;
};

std::string parseOpenTagName(std::string s);
std::string parseCloseTagName(std::string s);
Attribute parseAttribute(std::string s);
HMRL parseHMRL(std::string s);
Query parseQuery(std::string s);
void runQuery(HMRL h,Query q);
std::string popQueryTag(Query &q);
HMRL findHMRL(std::vector<HMRL> doc, std::string tag);



int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n, q;
    std::cin >> n >> q;


    auto doc = parseHMRL("");

    for (int i=0; i<q;i++) {
        std::string line = "";
        std::getline(std::cin,line);
        auto query = parseQuery(line);
        popQueryTag(query);
        runQuery(doc,query);
    }

    return 0;
}

HMRL parseHMRL (std::string line) {
    //parse open tag
    auto openTag = parseOpenTagName(line);
    line = line.substr(line.find(openTag) + 1); // continue from after open tag

    std::vector<Attribute> attributes;
    while (line != ">") { //continue until closing bracket
        line = line.substr(1); //drop the space
        
        int eqPos = line.find('=');
        auto name = line.substr(0,eqPos);
        line = line.substr(eqPos+3); //skip over =,space and "

        int quotePos = line.find('"');
        auto val = line.substr(0,quotePos);
        line = line.substr(quotePos + 1); //skip over "

        attributes.push_back(Attribute {name,val});
    } 
    
    std::string nextLine;
    std::getline(std::cin,nextLine);
    std::vector<HMRL> content;
    // keep parsing new HMRL elements until closing tag was found
    while(openTag != parseCloseTagName(nextLine)) {
        content.push_back(parseHMRL(nextLine));
    }

    return HMRL {openTag,attributes,content};
}

std::string parseOpenTagName(std::string s) {
    auto until = s.find(' '); 
    if (until == std::string::npos) { //No attributes, then closing tag
        until = s.find('>');
    }
    return s.substr(1,until); // read until first space
}

std::string parseCloseTagName(std::string s) {
    return s.substr(2,s.find('>'));
}

HMRL findHMRL(std::vector<HMRL> doc, std::string tag) {
    auto it = find_if(doc.begin()
                   ,doc.end()
                   ,[&tag](const HMRL &subdoc) 
                            { return subdoc.name == tag;}
                   );
    return *it;
}

Query parseQuery(std::string line) {
    std::vector<std::string> tags;

    while (line.substr(0) != "~") {
        auto until = line.find(".");
        std::string name;
        if (until == std::string::npos) { 
            until = line.find("~");
            name = line.substr(0,until);
        } else {
            name = line.substr(0,until);
            line = line.substr(1); // drop .
        }
        tags.push_back(name);
    }

    auto attribute = line.substr(1);

    return Query {tags, attribute};


}

std::string popQueryTag(Query &q) {
    auto tag = q.tags.front();
    q.tags.erase(q.tags.begin());
    return tag;
}


void runQuery(HMRL doc, Query q) {
    
    while (q.tags.size() != 0) {
        std::string tag = popQueryTag(q);

        doc = *find_if(doc.content.begin()
                     ,doc.content.end()
                     ,[&tag](HMRL h) { return h.name == tag;});
    }
    

    auto qAttr = q.attribute;
    auto attr = find_if(doc.attributes.begin()
                        ,doc.attributes.end()
                        ,[&qAttr](Attribute a){ return a.name == qAttr;});

    std::cout << (*attr).value;
    return;


}