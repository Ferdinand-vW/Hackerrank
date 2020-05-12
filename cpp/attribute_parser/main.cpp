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
bool isOpenTag (std::string);
bool isCloseTag(std::string s);
Attribute parseAttribute(std::string s);
HMRL parseHMRLOpen(std::string s);
Query parseQuery(std::string s);
void runQuery(HMRL h,Query q);
std::string popQueryTag(Query &q);
HMRL findHMRL(std::vector<HMRL> doc, std::string tag);



int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n, q;
    std::cin >> n >> q;

    std::string line = "";
    std::getline(std::cin,line);
    // auto doc = parseHMRL(line);
    auto root = HMRL { "root" , {}, {} };
    auto tagStack = std::vector<HMRL>{root};
    auto current = root;

    for (int i=0;i<n;i++) {
        std::getline(std::cin,line);
        if(isOpenTag(line)) {
            auto subdoc = parseHMRLOpen(line);
            current.content.push_back(subdoc);
            current = subdoc;
            tagStack.push_back(current);
        } else {
            tagStack.pop_back();
            current = tagStack.back();

        }
        

    }

    for (int i=0; i<q;i++) {
        std::getline(std::cin,line);
        auto query = parseQuery(line);
        runQuery(root,query);
    }

    return 0;
}

HMRL parseHMRLOpen (std::string line) {
    //parse open tag
    auto openTag = parseOpenTagName(line);
    line = line.substr(line.find(openTag) + openTag.size()); // continue from after open tag

    std::vector<Attribute> attributes;
    while (line != ">") { //continue until closing bracket
        line = line.substr(1); //drop the space
        
        int eqPos = line.find('=');
        auto name = line.substr(0,eqPos - 1);
        line = line.substr(eqPos+3); //skip over =,space and "

        int quotePos = line.find('"');
        auto val = line.substr(0,quotePos);
        line = line.substr(quotePos + 1); //skip over "

        attributes.push_back(Attribute {name,val});
    } 
    
    // std::string nextLine;
    // std::getline(std::cin,nextLine);
    // std::vector<HMRL> content;
    // // keep parsing new HMRL elements until closing tag was found
    // while(!isCloseTag(nextLine,openTag)) {
    //     content.push_back(parseHMRL(nextLine));
    //     std::getline(std::cin,nextLine);
    // }
    return HMRL {openTag,attributes,{}};
}

std::string parseOpenTagName(std::string s) {
    auto until = s.find(' '); 
    if (until == std::string::npos) { //No attributes, then closing tag
        until = s.find('>');
    }
    return s.substr(1,until - 1); // read until first space
}

bool isOpenTag (std::string s) {
    return s.find("</") == std::string::npos;
}

bool isCloseTag(std::string s) {
    return s.find("</") != std::string::npos;
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

    while (line.substr(0,1) != "~") {
        auto until = line.find(".");
        std::string name;
        if (until == std::string::npos) { 
            until = line.find("~");
            name = line.substr(0,until);
            line = line.substr(until);
        } else {
            name = line.substr(0,until);
            line = line.substr(until + 1); // drop .
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

        auto docIte = find_if(doc.content.begin()
                           ,doc.content.end()
                           ,[&tag](HMRL h) { return h.name == tag;});
        
        if (docIte == doc.content.end()) {
            std::cout << "Not Found!\n";
            return;
        } else {
            doc = *docIte;
        }
    }


    auto qAttr = q.attribute;
    auto attr = find_if(doc.attributes.begin()
                        ,doc.attributes.end()
                        ,[&qAttr](Attribute a){ return a.name == qAttr;});

    if (attr == doc.attributes.end()) { std::cout << "Not Found!\n"; }
    else                              { std::cout << (*attr).value << "\n"; }
    
    return;


}