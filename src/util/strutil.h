//
// Copyright (c) 2019 Julian Hinxlage. All rights reserved.
//

#ifndef UTIL_STRUTIL_H
#define UTIL_STRUTIL_H

#include "util/ArrayList.h"
#include <string>

namespace util{

    std::string readFile(const std::string &filename);

    ArrayList<std::string> split(const std::string &str, const std::string &delimiter = " ");

    ArrayList<std::string> split(const ArrayList<std::string> &list, const std::string &delimiter = " ");

    std::string replace(const std::string &str, const std::string &match, const std::string &replacement);

    std::string join(const ArrayList<std::string> &list, const std::string &delimiter = "");

    bool strContains(const std::string &str, const std::string &value);

    bool isNum(const std::string &str);

    int toNum(const std::string &str);

}

#endif //UTIL_STRUTIL_H
