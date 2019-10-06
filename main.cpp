#include <cstdio>
#include "parser.hpp"

using namespace std;

int main()
{
    if(parse("test.txt")) printf("Ok\n");
    else printf("Not Ok\n");
    return 0;
}
