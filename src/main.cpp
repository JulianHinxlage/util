//
// Copyright (c) 2019 Julian Hinxlage. All rights reserved.
//

#include "util/log.h"
#include "util/Clock.h"

int main(int argc, char *argv[]){
    util::Clock clock;
    util::logSetFile("log.txt");
    util::logSetLevel(util::ERROR);
    util::logSetFileLevel(util::DEBUG);

    util::logDebug   ("util test\nutil test");
    util::logInfo    ("util test\nutil test");
    util::logWarning ("util test\nutil test");
    util::logError   ("util test\nutil test");
    util::logCritical("util test\nutil test");

    clock.sleep(0.1);
    util::logError("time: ", clock.elapsed());
    return 0;
}
