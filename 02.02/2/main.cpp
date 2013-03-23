#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <vector>
#include <sstream>
#include <map>

/*
 * Słownik to plik tekstowy zawierający słowa odzielone białymi znakami
 * Szyfrogram to plik zawiarający zaszyfrowaną wiadomość
 * Odpowiedzią jest zestaw kluczy którymi należy "powtórnie zaszyfrować"
 * szyfrogram, aby uzyskać odszyfrowany tekst.
 */

int main(int argc, char **argv) {
    if(argc!=3)
    {
        std::cerr<<argv[0]<<" [słownik] [szyfrogram]\n";
        return 1;
    }
    std::ifstream dictionaryStream(argv[1]);
    std::ifstream messageStream(argv[2]);
    
    std::unordered_set<std::string> dictionary;
    for(;;)
    {
        std::string word;
        dictionaryStream>>word;
        if(dictionaryStream.eof())
            break;
        dictionary.insert(word);
    }
    dictionaryStream.close();
    std::vector<unsigned char> message;
    for(;!messageStream.eof();)
    {
        char buf[1024];
        messageStream.read(buf,1024);
        message.insert(message.end(),buf,buf+messageStream.gcount());
    }
    
    long rank[256];
    
    for(int key=0;key<256;++key)
    {
        std::string decrypted(message.size(),'\0');
        for(std::size_t i=0;i<message.size();++i)
            decrypted[i]=static_cast<char>(message[i]+key)%256;
        std::istringstream stream(decrypted);
        rank[key]=0;
        for(;;)
        {
            std::string word;
            stream>>word;
            if(stream.eof())
                break;
            if(dictionary.find(word)!=dictionary.end())
                rank[key]+=word.length();
        }
    }
    
    std::multimap<long,int,std::greater<long>> sortedRank;
    for(int key=0;key<256;++key)
    {
        sortedRank.insert(std::make_pair(rank[key],key));
    }
    for(auto p : sortedRank)
    {
        if(p.first==0)
            break;
        std::cout<<"Klucz: "<<p.second<<", ranga: "<<p.first<<'\n';
    }
    
    return 0;
}
