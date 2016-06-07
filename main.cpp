#include "lexicalanalyzer.h"

int main()
{
    LexicalAnalyzer analyzer;
    std::ifstream in("program2.lng", std::ios::in);
    analyzer.run(in);
    analyzer.print();
    in.close();
    return 0;
}
