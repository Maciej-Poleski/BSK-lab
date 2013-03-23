#include <iostream>
#include <fstream>
#include <iterator>

/*
 * Tekst do zaszyfrowania czytany ze standardowego wejścia
 * Zaszyfrowany wypisywany na standardowe wyjście
 * Klucz podany w argumencie (ścieżka do pliku)
 * Na wyjście błędów jest wypisywana bijekcja
 */

int main(int argc, char **argv) {
    if(argc!=2)
    {
        std::cerr<<"Podaj klucz\n";
        return 1;
    }
    std::ifstream key(argv[1]);
    char map[256];
    for(std::size_t i=0;i<256;++i)
        map[i]=i;       // Identyczność dla pozostałych znaków
    for(char c='a';c<='z';++c)
    {
        char cc;
        key>>cc;
        std::clog<<c<<" -> "<<cc<<std::endl;
        map[c]=cc;
    }
    for(auto c=std::cin.get();c!=std::char_traits<char>::eof();c=std::cin.get())
    {
        std::cout<<map[std::char_traits<char>::to_char_type(c)];
    }
    return 0;
}
