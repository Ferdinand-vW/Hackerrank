#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class Spell { 
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Fireball : public Spell { 
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell { 
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell { 
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
}; 
string SpellJournal::journal = "";

int LCSubSeq(std::string spell, std::string journal) {
  int m = spell.length();
  int n = journal.length();

  int mem[m+1][n+1];
  int res = 0;

  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      if (i == 0 || j == 0) {
        mem[i][j] = 0;
      }
      else if (spell[i - 1] == journal[j - 1]) {
        mem[i][j] = 1 + mem[i-1][j-1]; 
      }
      else {
        mem[i][j] = std::max(mem[i][j-1],mem[i-1][j]);
      }

      if (mem[i][j] > res) { res = mem[i][j]; }
    }
  }

  return res;
}

void counterspell(Spell *spell) {

  /* Enter your code here */
  if(Fireball* b = dynamic_cast<Fireball*>(spell)) {
    b->revealFirepower();
  }
  else if (Waterbolt* b = dynamic_cast<Waterbolt*>(spell)) {
    b->revealWaterpower();
  }
  else if (Frostbite* b = dynamic_cast<Frostbite*>(spell)) {
    b->revealFrostpower();
  }
  else if (Thunderstorm* b = dynamic_cast<Thunderstorm*>(spell)) {
    b->revealThunderpower();
  }
  else {
    std::string spellName = spell->revealScrollName();
    std::string spellJournal = SpellJournal::journal;
    int n = LCSubSeq(spellName,spellJournal);
    std::cout << n << endl;
  }

}

class Wizard {
    public:
        Spell *cast() {
            Spell *spell;
            string s; cin >> s;
            int power; cin >> power;
            if(s == "fire") {
                spell = new Fireball(power);
            }
            else if(s == "frost") {
                spell = new Frostbite(power);
            }
            else if(s == "water") {
                spell = new Waterbolt(power);
            }
            else if(s == "thunder") {
                spell = new Thunderstorm(power);
            } 
            else {
                spell = new Spell(s);
                cin >> SpellJournal::journal;
            }
            return spell;
        }
};

int main() {
    int T;
    cin >> T;
    Wizard Arawn;
    while(T--) {
        Spell *spell = Arawn.cast();
        counterspell(spell);
        delete spell;
    }
    return 0;
}