#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

/*
 * Słownik to plik tekstowy zawierający słowa odzielone białymi znakami
 * Szyfrogram to plik zawiarający zaszyfrowaną wiadomość
 * Odpowiedzią jest klucz którym należy "powtórnie zaszyfrować"
 * szyfrogram, aby uzyskać odszyfrowany tekst. (Bijekcja na skończonych
 * zbiorach jest trywialnie odwracalna)
 */

int main(int argc, char **argv) {
    if(argc!=3)
    {
        std::cerr<<argv[0]<<" [słownik] [szyfrogram]\n";
        return 1;
    }
    std::ifstream dictionaryStream(argv[1]);
    std::ifstream messageStream(argv[2]);

    long dictionaryCounter[256]= {0};
    long messageCounter[256]= {0};

    for(;;)
    {
        std::string word;
        dictionaryStream>>word;
        if(dictionaryStream.eof())
            break;
for(const char c : word)
            ++dictionaryCounter[c];
    }

    std::vector<std::pair<long,char>> dictionary;
    for(std::size_t i=0; i<256; ++i)
    {
        if(dictionaryCounter[i]==0)
            continue;
        dictionary.push_back( {dictionaryCounter[i],i});
    }
    std::sort(dictionary.begin(),dictionary.end());
    for(std::size_t i=0; i<dictionary.size()-1; ++i)
        if(dictionary[i].first==dictionary[i+1].first)
        {
            std::cerr<<"Słownik jest niejednoznaczny!\n";
            return 2;
        }

    for(;;)
    {
        std::string word;
        messageStream>>word;
        if(messageStream.eof())
            break;
for(const char c : word)
            ++messageCounter[c];
    }

    std::vector<std::pair<long,char>> message;
    for(std::size_t i=0; i<256; ++i)
    {
        if(messageCounter[i]==0)
            continue;
        message.push_back( {messageCounter[i],i});
    }
    std::sort(message.begin(),message.end());
    for(std::size_t i=0; i<message.size()-1; ++i)
        if(message[i].first==message[i+1].first)
        {
            std::cerr<<"Wiadomość jest niejednoznaczna!\n";
            return 3;
        }

    if(message.size()!=dictionary.size())
    {
        std::cerr<<"Alfabet wiadomości nie jest zgodny z alfabetem słownika!\n";
        return 4;
    }

    // Słownik i wiadomość jest jednoznaczna - tworzę bijekcję odwracającą

    char map[256];
    for(std::size_t i=0;i<256;++i)
    {
        map[i]=i;
    }
    for(std::size_t i=0;i<message.size();++i)
    {
        map[message[i].second]=dictionary[i].second;
    }
    for(char c='a';c<='z';++c)
    {
        std::cout<<map[c];
    }

    return 0;
}
