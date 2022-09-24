#include<iostream>
#include<random>

using State = int;


class AbstractState {
    public:
        virtual bool contains(State s) const{
            return 0;
        }

         float test(unsigned test_count, unsigned seed, int E_min, int E_max) const {
            std :: default_random_engine reng(seed);
            std :: uniform_int_distribution<int> dstr (E_min, E_max);

            unsigned good = 0;
            for (unsigned cnt = 0; cnt != test_count; ++cnt)
                if (contains(dstr(reng))) ++good;

            return static_cast<float>(good) / static_cast<float>(test_count);
        }
};

class DiscreteState : public AbstractState {

    private:
        State const s0;

    public:
        DiscreteState(State s0) : s0(s0) {}
        bool contains(State s) const {
            return s == s0;
        }
};

class SegmentState : public AbstractState {

    private:
        State const begin_s0, end_s0;

    public:
        SegmentState(State begin_s0, State end_s0) : begin_s0(begin_s0), end_s0(end_s0) {}
        bool contains(State s) const {
            return begin_s0 <= s && end_s0 >=s;
        }
};

class ProbabilityTest {

    private:
        State const E_min, E_max;

    public:

        ProbabilityTest(State E_min, State E_max) : E_min(E_min), E_max(E_max) {}

        float test(DiscreteState system, unsigned test_count, unsigned seed) const {
            return system.test(test_count, seed, E_min, E_max);
        }

        float test(SegmentState system, unsigned test_count, unsigned seed) const {
            return system.test(test_count, seed, E_min, E_max);
        }

};

class Sus : public AbstractState {
    public:




}


int main(){

   DiscreteState d(0);
   SegmentState s (0, 100);
   ProbabilityTest pt(-1000, 1000);

   std :: cout << pt.test(d, 2000, 5) << '\n';
   std :: cout << pt.test(s, 2000, 5) << '\n';

return 0;
}
