//
// Copyright (c) 2019 Julian Hinxlage. All rights reserved.
//

#include "strutil.h"
#include <fstream>

namespace util{

    std::string readFile(const std::string &filename) {
        std::ifstream stream(filename);
        if(stream.is_open()){
            try{
                return std::string((std::istreambuf_iterator<char>(stream)), (std::istreambuf_iterator<char>()));
            }
            catch (...){
                return "";
            }
        }else{
            return "";
        }
    }

    ArrayList<std::string> split(const std::string &str, const std::string &delimiter, bool addEmptyParts) {
        ArrayList<std::string> res;
        if(delimiter.empty()){
            for(char c : str){
                res.add(std::string(1, c));
            }
        }else if(delimiter.size() == 1){
            std::string buffer;
            for(char c : str){
                if(c == delimiter[0]){
                    if(!buffer.empty() || addEmptyParts){
                        res.add(buffer);
                        buffer = "";
                    }
                }else{
                    buffer += c;
                }
            }
            if(!buffer.empty() || addEmptyParts){
                res.add(buffer);
            }
        }else{
            std::string buffer;
            int index = 0;
            for(char c : str){
                buffer += c;
                if(c == delimiter[index]){
                    index++;
                    if(index >= (int)delimiter.size()){
                        index = 0;
                        buffer = buffer.substr(0, buffer.size() - delimiter.size());
                        if(!buffer.empty() || addEmptyParts){
                            res.add(buffer);
                        }
                        buffer = "";
                    }
                }else{
                    index = 0;
                }
            }
            if(!buffer.empty() || addEmptyParts){
                res.add(buffer);
            }
        }
        return res;
    }

    ArrayList<std::string> split(const ArrayList<std::string> &list, const std::string &delimiter) {
        ArrayList<std::string> res;
        for(const std::string &str : list){
            res.add(split(str, delimiter));
        }
        return res;
    }

    std::string replace(const std::string &str, const std::string &match, const std::string &replacement) {
        std::string res;
        if((int)match.size() >= 1) {
            std::string buffer;
            int index = 0;
            for (char c : str) {
                buffer += c;
                if (c == match[index]) {
                    index++;
                    if (index >= (int)match.size()) {
                        index = 0;
                        buffer = buffer.substr(0, buffer.size() - match.size());
                        res += buffer;
                        res += replacement;
                        buffer = "";
                    }
                } else {
                    index = 0;
                }
            }
            if (!buffer.empty()) {
                res += buffer;
            }
        }
        return res;
    }

    std::string join(const ArrayList<std::string> &list, const std::string &delimiter) {
        std::string res;
        for(int i = 0; i < (int)list.size();i++){
            if(i != 0){
                res += delimiter;
            }
            res += list[i];
        }
        return res;
    }

    bool strContains(const std::string &str, const std::string &value) {
        if(value.empty()){
            return true;
        }else if(value.size() == 1){
            for(char c : str){
                if(c == value[0]){
                    return true;
                }
            }
            return false;
        }else{
            int index = 0;
            for(char c : str){
                if(c == value[index]){
                    index++;
                    if(index >= (int)value.size()){
                        return true;
                    }
                }else{
                    index = 0;
                }
            }
            return false;
        }
    }

    bool isNum(const std::string &str) {
        for(char c : str){
            if(!(c >= '0' && c <= '9')){
                return false;
            }
        }
        return true;
    }

    int toNum(const std::string &str) {
        int num = 0;
        for(char c : str){
            num *= 10;
            num += c - '0';
            if(!(c >= '0' && c <= '9')){
                return -1;
            }
        }
        return num;
    }

}
