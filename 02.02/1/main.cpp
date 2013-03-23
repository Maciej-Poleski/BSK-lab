#include <iostream>
#include <fstream>
#include <iterator>

/*
 * Tekst do zaszyfrowania czytany ze standardowego wejścia
 * Zaszyfrowany wypisywany na standardowe wyjście
 * Klucz podany w argumencie
 */

int main(int argc, char **argv) {
    if(argc!=2)
    {
        std::cerr<<"Podaj klucz\n";
        return 1;
    }
    std::ifstream key(argv[1]);
    int l;
    key>>l;
    int permutation[l];
    for(int i=0;i<l;++i)
        key>>permutation[i];
    for(;!std::cin.eof();)
    {
        char buff[l];
        for(int i=0;i<l;++i)
            buff[i]='\0';
        std::cin.read(buff,l);
        char result[l];
        for(int i=0;i<l;++i)
            result[permutation[i]]=buff[i];
        std::cout.write(result,l);
    }
    return 0;
}
