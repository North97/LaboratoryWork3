#include "lexicalanalyzer.h"

LexicalAnalyzer::LexicalAnalyzer()
{

}

int LexicalAnalyzer::toSymbolClass(char &value)
{
    if(value == '\n' || value == ' ' || value == '\t')
    {
        return 0;
    }
    else if(isdigit(value))
    {
        return 1;
    }
    else if(isalpha(value))
    {
        return 2;
    }
    else if(value == '=')
    {
        return 3;
    }
    else if(value == ';')
    {
        return 4;
    }
    else if(value == '+' || value == '-')
    {
        return 5;
    }
    else if(value == '*' || value == '\\')
    {
        return 6;
    }
    else
    {
        return 7;
    }
}

void LexicalAnalyzer::run(std::ifstream &in)
{
    std::string temp;
    std::ostringstream buffer;
    buffer << in.rdbuf();
    std::string code = buffer.str();
    buffer.str("");

    std::cout << "Source code:\n\n";
    std::cout << code;
    std::cout << "-------------------------------------------------------------------------\n";

    int beforeState;
    int currentState = stateMachine[toSymbolClass(code[0])][0];

    for(int i = 0; i < (int)code.length(); ++i)
    {
        beforeState = currentState;
        currentState = stateMachine[toSymbolClass(code[i])][currentState];

        if(separators.find(code[i]) != separators.end())
        {
            temp = buffer.str();
            buffer.str("");

            if(temp != std::string())
            {
                resultLexeme.push_back(temp + '\t' + lexemeInfo(beforeState, temp));
            }
            if(insignSeparators.find(code[i]) == insignSeparators.end())
            {
                temp = code[i];
                resultLexeme.push_back(temp + '\t' + lexemeInfo(currentState, temp));
            }
        }
        else
        {
            buffer << code[i];
        }
    }
}

void LexicalAnalyzer::print()
{
    for(int i = 0; i < (int)resultLexeme.size(); ++i)
    {
        std::cout << resultLexeme[i] << "\n";
    }
}

std::string LexicalAnalyzer::lexemeInfo(int &value, std::string &lex)
{
    switch (value) {
    case 0:
        return "Separator";
    case 1:
        if(keywords.find(lex) != keywords.end())
            return "Keyword";
        else
            return "Identifire";
    case 2:
        return "Constant";
    case 3:
        return "Assignment operator";
    case 4:
        return "Separator";
    case 5:
        return "Mathematical operation LP";
    case 6:
        return "Mathematical operation HP";
    default:
        return "Undefined lexeme";
    }
}
