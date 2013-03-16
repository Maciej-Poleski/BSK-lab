/*
 * Nie próbowałem kompilować tego innym kompilatorem niż Clang 3.2
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

class Rotor
{
public:
    template<typename URNG>
    Rotor(URNG&& generator)
    {
        for(std::size_t i=0;i<256;++i)
            _mapping[i]=i;
        std::shuffle(_mapping,_mapping+256,generator);
    }
    
    const unsigned char translate(const unsigned char ch) const
    {
        return _mapping[(ch+_rotation)%256];
    }
    
    /**
     * @return Czy obecny obrót kończy obrót o 360 stopni
     */
    bool rotate()
    {
        ++_rotation;
        if(_rotation==256)
        {
            _rotation=0;
            return true;
        }
        return false;
    }

private:
    // Bęben ma 256 pozycji - koduje ciąg bajtów
    unsigned char _mapping[256];
    std::size_t _rotation=0;
};

/**
 * Nie wykorzystuje bębna obracającego
 */
class Enigma
{
public:
    Enigma()
    {
        // Aby wygenerować zawartość bębnów wykorzystam deterministyczny PRNG
        // można w tym miejscu dopisać kod który tworzyłby bębny o określonej
        // strukturze zamiast automatycznego generowania.
        std::mt19937 engine(404);
        for(std::remove_const<decltype(_numberOfRotors)>::type i=0; i<_numberOfRotors; ++i)
        {
            _rotors.push_back(Rotor(engine));
        }
    }

    /**
     * Szyfruje podaną wiadomość
     *
     * @return Zaszyfrowana wiadomość (niekoniecznie tekst)
     */
    std::string encrypt(const std::string &string)
    {
        std::string result;
        for(auto ch : string)
        {
            // Najpierw koduje znak, potem obraca bębny
            result+=encodeCharacter(ch);
            adjustState();
        }
        return result;
    }

private:
    const unsigned char encodeCharacter(const unsigned char ch) const
    {
        auto result=ch;
        for(const Rotor r : _rotors)
            result=r.translate(result);
        return result;
    }

    void adjustState()
    {
        for(auto i=_rotors.rbegin(),e=_rotors.rend(); i!=e; ++i)
        {
            if(!i->rotate())
                break;
        }
    }

private:
    // Arbitralnie wybrana ilość bębnów
    static constexpr std::size_t _numberOfRotors=5;
    std::vector<Rotor> _rotors;
};

int main(int argc, char **argv) {
    Enigma enigma;
    std::cout << enigma.encrypt("Hello, World!") << std::endl;
    return 0;
}
