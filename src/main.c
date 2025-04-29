#include "io.h"
#include <stdio.h>
#include <stdlib.h>

/*
possible syntax:
------------------

proto logger
    proc __cpy(...)

    end

    proc log(msg: str)

    end
end

proc fizz()

end


set num = 5;
set log = cpy(logger);
out(num);


*/

int main() {
    char* hi = malloc(0);
    size_t size = rline(hi, stdin);
    printf("%s\n", hi); 
    free(hi);
}