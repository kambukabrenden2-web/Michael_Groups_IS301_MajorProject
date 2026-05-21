
#include <stdio.h>
#include "auth.h"
#include "menu.h"

int main() {
    if (!login()) {
        printf("Exiting system.\n");
        return 1;
    }
    runMainMenu();
    return 0;
}
