#include<iostream>
#include<set>
#include<random>
#include<fstream>

using State = int;
const State MaxState = 1000;

class GeneralState {

    public:
        std::set <State> state;

    public:

        bool contains(const State &s) const{
            return state.count(s) > 0;
        }

        GeneralState(std::set  <State> state) : state(state) {}

        GeneralState(){
            state.clear();
        }

        GeneralState (const int N, int min, int max, int seed){
        /*
        Generates different(!) random numbers
        If N is bigger than amount of all possible numbers will die
        in infinite loop
        */
        std::set<State> Res;
        Res.clear();

        std :: default_random_engine reng(seed);
        std :: uniform_int_distribution<int> dstr (min, max);

        int different_states = 0;

        while(different_states != N){
            int current_random = dstr(reng);
            if (Res.count(current_random) == 0){
                Res.emplace(current_random);
                different_states++;
            }
        }

        state = Res;
    }

        GeneralState operator+ (const GeneralState &rha) const {
            GeneralState Sum = *this;
            for (std::set<State>::iterator i = rha.state.begin(); i !=  rha.state.end(); ++i){
                Sum.state.emplace(*i);
            }
            return Sum;
        }

        GeneralState operator* (const GeneralState &rha) const {
            GeneralState Res;
            for (std::set<State>::iterator i = rha.state.begin(); i !=  rha.state.end(); ++i){
                for (std::set<State>::iterator j = state.begin(); j !=  state.end(); ++j){
                    if (*i == *j){
                        Res.state.emplace(*i);
                    }
                }
            }
            return Res;
        }

        GeneralState operator! () const {
            GeneralState Res;

            for (State i = - MaxState; i <= MaxState; i++){
                if (this->state.count(i) == 0){
                    Res.state.emplace(i);
                }
            }

            return Res;
        }

        void write_in_file(std :: ofstream &fout){
            fout.open("Random_State.txt");
            for (std::set<State>::iterator i = state.begin(); i !=  state.end(); ++i){
                fout << *i << '\n';
            };
            fout.close();
        }

        GeneralState& fetch_from_file(std :: ifstream &fin){

            fin.open("Random_State.txt");

            if (fin.is_open()){
                std :: cout << "Reading";
            }
            else{
                std :: cout << "Cannot Read";
            }

            State current_state;
            while(fin >> current_state ){
                state.emplace(current_state);
            }
            fin.close();

            return *this;
        }

};







class DiscreteState : public GeneralState {
    public:

        DiscreteState(State s0){
            state.clear();
            state.emplace(s0);
        }
        DiscreteState() : DiscreteState(0) {}

};

class SegmentState : public GeneralState {

    public:
        SegmentState(State begin_s0, State end_s0) {
            state.clear();
            for(int i = begin_s0; i < end_s0 + 1; i++){
                state.emplace(i);
            }
        }
        SegmentState() : SegmentState(0, 0) {};
};


class ProbabilityTest {

    private:
        State const E_min, E_max;

    public:

        ProbabilityTest(State E_min, State E_max) : E_min(E_min), E_max(E_max) {}

        float test(GeneralState system, const unsigned test_count, const unsigned seed) {
            std :: default_random_engine reng(seed);
            std :: uniform_int_distribution<int> dstr (E_min, E_max);

            unsigned good = 0;
            for (unsigned cnt = 0; cnt != test_count; ++cnt){
                if (system.contains(dstr(reng))){
                    ++good;
                 }
            }

            return static_cast<float>(good) / static_cast<float>(test_count);
        }

        float different_seed_test(const GeneralState &system, const unsigned test_count, const int seed_seed){
            int N = 3;
            int bound = 100;
            std :: default_random_engine reng(seed_seed);
            std :: uniform_int_distribution<int> dstr (-bound, bound);
            float sum = 0;

            for (int i = 0; i < N; i++){
                sum += test(system, test_count, dstr(reng))/ N;
            }

            return sum;
        }
};



int main(){

int seed_for_State = 126;
int seed_for_Test = 0;

GeneralState Kolya(100, -1000, 1000, seed_for_State);
SegmentState s (0, 99);
ProbabilityTest pt(-1000, 1000);

GeneralState Evgen;


std::ofstream fout;


fout.open("results.txt");

fout << "State seed" << ';' <<  seed_for_State << ';'
                            << "Test seed" << ';' << seed_for_Test << '\n';

fout << "Test_Count" <<';' << "Random100" <<';' << "Consecutive 0-99" << '\n';

bool done = false;

int test_amount = 1;

while(!done){

    fout << test_amount << ';' << pt.different_seed_test(Kolya, test_amount, seed_for_Test) << ';'
                                << pt.different_seed_test(s, test_amount, seed_for_Test) << '\n';
    test_amount  += 10;

    if (test_amount > 40000){
        done = true;
    }
}

fout.close();

return 0;
}
