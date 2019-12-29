//
// Copyright (c) 2019 Julian Hinxlage. All rights reserved.
//

#include "util/log.h"

int main(int argc, char *argv[]){
    util::logSetFile("log.txt");
    util::logSetLevel(util::ERROR);
    util::logSetFileLevel(util::DEBUG);

    util::logDebug   ("util test\nutil test");
    util::logInfo    ("util test\nutil test");
    util::logWarning ("util test\nutil test");
    util::logError   ("util test\nutil test");
    util::logCritical("util test\nutil test");
    return 0;
}
