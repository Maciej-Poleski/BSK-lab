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
        std::cerr<<"Podaj klucz [0;256)\n";
        return 1;
    }
    auto key=std::stoul(argv[1]);
    if(key<0 || key>=256)
    {
        std::cerr<<"Klucz musi być z przedziału [0;256)\n";
        return 2;
    }
    for(auto c=std::cin.get();c!=std::char_traits<char>::eof();c=std::cin.get())
    {
        std::cout<<static_cast<char>((std::char_traits<char>::to_char_type(c)+key)%256);
    }
    return 0;
}
