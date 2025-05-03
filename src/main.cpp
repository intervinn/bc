
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

#include "token.hpp"
#include <iostream>

int main() {
    auto toks = bc::parse("1()[]");
    for (auto tok : toks) {
        std::cout << std::to_string(tok.kind) << std::endl;
    }
}