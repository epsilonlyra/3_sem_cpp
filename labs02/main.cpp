#include<iostream>
#include<set>
#include<random>

using State = int;
const State MaxState = 1000;

class GeneralState {

    protected:
        std::set <State> state;


    public:

        bool contains(const State &s) const{
            return state.count(s) > 0;
        }

        GeneralState(std::set  <State> state) : state(state) {}

        GeneralState(){
            state.clear();
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
            for(int i = begin_s0; i < end_s0+ 1; i++){
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
};

GeneralState RandomGeneralState(const int N, int min, int max, int seed){
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

    return GeneralState(Res);
}


int main(){




DiscreteState d(0);
SegmentState s (0, 100);
GeneralState Kolya = RandomGeneralState(10, -1000, 1000, 1);



ProbabilityTest pt(-1000, 1000);

std :: cout << pt.test(d, 2000, 5) << '\n';
std :: cout << pt.test(s, 20000000, 5) << '\n';
std :: cout << pt.test(Kolya, 20000000, 5) << '\n';

/*
std::set<State> Elena {1,4, 5};
std::set<State> Anoshin {1,4, 5};
std::set<State> Amogus {1,4, 5};

GeneralState ElenaT(Elena);
GeneralState AnoshinA(Anoshin);
GeneralState AmogusS(Amogus);

AmogusS = A;

    for (std::set<State>::iterator i = AmogusS.state.begin(); i !=  AmogusS.state.end(); ++i){
                std :: cout << *i << '\n';
        }
*/
return 0;
}
