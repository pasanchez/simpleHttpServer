#include <stdio.h>
#include "Server.h"

int main() {

    printf("Starting server.\n");
    Server server(8000);
    printf("Listening....\n");
    server.listen();
    return 0;
}