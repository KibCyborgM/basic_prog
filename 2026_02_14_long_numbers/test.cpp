#include "long_number.hpp"
using namespace tar;

int main() {
    LongNumber a("123456789");
    LongNumber b("12345");
    
    LongNumber q = a / b;  // 10000
    LongNumber r = a % b;  // 6789
    
    std::cout << a << " / " << b << " = " << q << std::endl;
    std::cout << a << " % " << b << " = " << r << std::endl;
    
    return 0;
}