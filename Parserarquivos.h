#ifndef PARSERARQUIVOS_H
#define PARSERARQUIVOS_H

#include <fstream>

using namespace std;

class ParserArquivos
{
public:
    ParserArquivos();
    void lerArquivo(string);
    void escreverEmArquivo();
};

#endif // PARSERARQUIVOS_H
