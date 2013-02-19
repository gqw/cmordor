#include <unistd.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>


#include "daemon.h"

using namespace std;

int run_main(int argc, char **argv) {
    while (true) {
        std::cout << "sleep 10" << std::endl;
        sleep(10);
    }
    return 0;
}

int main(int argc, char **argv) {
    int ret = CMordor::run(argc, argv, run_main, false);
    return ret;
}
