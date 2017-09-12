//
//  dump.cpp
//  JSON dump with cajun
//
//  Created by Kylin on 2017/9/11.
//  Copyright © 2017年 Kylin. All rights reserved.
//

#include <iostream>
#include <string>
#include "json/elements.h"
#include "json/reader.h"
#include "json/writer.h"

std::string get_padding(int length)
{
    std::stringstream stream;
    while(length--)
    {
        stream.write(" ", 1);
    }
    return stream.str();
}

void dump_element(const char* name, const json::UnknownElement& element, int indent)
{
    std::cout << get_padding(indent * 4);
    if(name != nullptr)
    {
        std::cout << name << ": ";
    }
    if(element.IsArray())
    {
        std::cout << "array [" << std::endl;
        
        const json::Array& array = element;
        json::Array::const_iterator iter(array.Begin()), end(array.End());
        while(iter != end)
        {
            dump_element(nullptr, *iter, indent + 1);
            iter++;
        }
        
        std::cout << get_padding(indent * 4) << "]" << std::endl;
    }
    else if(element.IsObject())
    {
        std::cout << "object {" << std::endl;
        
        const json::Object& object = element;
        json::Object::const_iterator iter(object.Begin()), end(object.End());
        while(iter != end)
        {
            dump_element(iter->name.c_str(), iter->element, indent + 1);
            iter++;
        }
        
        std::cout << get_padding(indent * 4) << "}" << std::endl;
    }
    else if(element.IsNull())
    {
        std::cout << "null" << std::endl;
    }
    else if(element.IsString())
    {
        const json::String& string = element;
        std::cout << "string \"" << string.Value() << "\"" << std::endl;
    }
    else if(element.IsNumber())
    {
        const json::Number& number = element;
        std::cout << "number (" << number.Value() << ")" << std::endl;
    }
    else if(element.IsBoolean())
    {
        const json::Boolean& boolean = element;
        std::cout << "boolean (" << (boolean.Value() ? "true" : "false") << ")" << std::endl;
    }
}

void dump_json(const char* name, const json::UnknownElement& element, int indent)
{
    std::cout << get_padding(indent * 4);
    if(name != nullptr)
    {
        std::cout << "\"" << name << "\": ";
    }
    if(element.IsArray())
    {
        std::cout << "[";
        
        const json::Array& array = element;
        if(!array.Empty())
        {
            std::cout << std::endl;
        }
        json::Array::const_iterator iter(array.Begin()), begin(array.Begin()), end(array.End());
        while(iter != end)
        {
            if(iter != begin)
            {
                std::cout << "," << std::endl;
            }
            dump_json(nullptr, *iter, indent + 1);
            iter++;
        }
        
        std::cout << std::endl << get_padding(indent * 4) << "]";
    }
    else if(element.IsObject())
    {
        std::cout << "{";
        
        const json::Object& object = element;
        if(!object.Empty())
        {
            std::cout << std::endl;
        }
        json::Object::const_iterator iter(object.Begin()), begin(object.Begin()), end(object.End());
        while(iter != end)
        {
            if(iter != begin)
            {
                std::cout << "," << std::endl;
            }
            dump_json(iter->name.c_str(), iter->element, indent + 1);
            iter++;
        }
        
        std::cout << std::endl << get_padding(indent * 4) << "}";
    }
    else if(element.IsNull())
    {
        std::cout << "null";
    }
    else if(element.IsString())
    {
        const json::String& string = element;
        std::cout << "\"" << string.Value() << "\"";
    }
    else if(element.IsNumber())
    {
        const json::Number& number = element;
        std::cout << number.Value();
    }
    else if(element.IsBoolean())
    {
        const json::Boolean& boolean = element;
        std::cout << (boolean.Value() ? "true" : "false");
    }
    if(indent == 0)
    {
        std::cout << std::endl;
    }
}

int main(int argc, const char * argv[]) {
    
    auto s = R"({"a":[1,2,3],"o":{"i":9,"u":"\u610f\u5916\u7a0b\u5ea6,\u8bc4\u5206,\u5176\u5b83\u529f\u80fd"},"e":null,"s":"text","n":3.141592653,"b":true})";

    std::stringstream stream;
    stream.write(s, strlen(s));

    json::UnknownElement u;
    
    try
    {
        json::Reader::Read(u, stream);
        dump_element(nullptr, u, 0);
        dump_json(nullptr, u, 0);
    }
    catch (json::Exception e)
    {
        std::cout << e.what() << std::endl;
    }
        
    return 0;
}
