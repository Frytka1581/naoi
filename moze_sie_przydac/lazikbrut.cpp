// lazikbrut.cpp
// Bruteforce blokami: sekwencje postaci D^{a1} P^{a2} D^{a3} ...
// Usage: ./lazikbrut n m maxlen

#include <bits/stdc++.h>
using namespace std;

int n, m;

// apply single move (wraps around)
inline void apply_move(int &x, int &y, char c){
    if(c == 'D') x = (x + 1) % n;
    else if(c == 'P') y = (y + 1) % m;
}

// simulate sequence S, return true if visits all n*m cells
bool sim_visits_all(const string &S){
    int k = (int)S.size();
    // Handle trivial invalid
    if(k == 0) return false;

    // visited cells
    vector<char> visited_cell((size_t)n * m, 0);
    int visited_count = 0;

    // seen states (x,y,idx)
    // size = n * m * k
    size_t states_sz = (size_t)n * (size_t)m * (size_t)k;
    if(states_sz > 200'000'000) {
        // safety: very large memory would be needed; bail out for this S
        // (shouldn't happen for reasonable n,m,k)
        return false;
    }
    vector<char> seen_state(states_sz, 0);
    auto state_index = [&](int xx, int yy, int ii)->size_t{
        return ((size_t)ii * (size_t)(n*m)) + (size_t)(xx * m + yy);
    };

    int x = 0, y = 0, idx = 0;
    seen_state[state_index(x,y,idx)] = 1;
    if(!visited_cell[x*m + y]){ visited_cell[x*m + y] = 1; ++visited_count; }
    if(visited_count == n * m) return true;

    while(true){
        apply_move(x, y, S[idx]);
        idx = (idx + 1) % k;

        if(!visited_cell[x*m + y]){
            visited_cell[x*m + y] = 1;
            ++visited_count;
            if(visited_count == n * m) return true;
        }

        size_t si = state_index(x,y,idx);
        if(seen_state[si]) break; // cycle -> won't get new cells
        seen_state[si] = 1;
    }
    return false;
}

// backtracking to generate compositions of totalLen into partsCount positive integers
// parts vector collects the run lengths. For each composition we build S for both starts.
bool generate_compositions_and_test(int totalLen, int partsCount, int startChar /*0->D,1->P*/,
                                    vector<int> &parts, int pos /*current part index*/, int rem){
    if(pos == partsCount){
        if(rem != 0) return false;
        // build string S from parts alternating starting char
        string S;
        S.reserve(totalLen);
        int cur = startChar;
        for(int i = 0; i < partsCount; ++i){
            int cnt = parts[i];
            char ch = (cur == 0 ? 'D' : 'P');
            for(int t = 0; t < cnt; ++t) S.push_back(ch);
            cur ^= 1;
        }
        // simulate
        if(sim_visits_all(S)){
            cout << "ZNALEZIONO S (len=" << totalLen << "): " << S << "\n";
            return true;
        }
        return false;
    }

    // minimal sum remaining for remaining parts: 1 each
    int min_need = partsCount - pos - 1;
    // try assign current part from 1 .. rem - min_need
    for(int take = 1; take <= rem - min_need; ++take){
        parts[pos] = take;
        if(generate_compositions_and_test(totalLen, partsCount, startChar, parts, pos+1, rem - take))
            return true;
    }
    return false;
}

int main(int argc, char** argv){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if(argc < 4){
        cerr << "Użycie: " << argv[0] << " n m maxlen\n";
        return 1;
    }

    n = atoi(argv[1]);
    m = atoi(argv[2]);
    int maxlen = atoi(argv[3]);

    if(n <= 0 || m <= 0 || maxlen <= 0){
        cerr << "Niepoprawne parametry.\n";
        return 1;
    }

    // safety: avoid astronomicznie dużych totalLen
    if(maxlen > 60){
        cerr << "maxlen > 60 może być zbyt duże — skróć maxlen.\n";
        // but proceed if user insists
    }

    for(int totalLen = 1; totalLen <= maxlen; ++totalLen){
        // liczba kompozycji 2^(totalLen-1) — ostrzeżenie dla dużych totalLen
        if(totalLen >= 40){
            cerr << "Uwaga: totalLen=" << totalLen << " => dużo kompozycji; może działać długo.\n";
        }
        cerr << "Sprawdzam totalLen=" << totalLen << " ...\n";

        // partsCount = liczba bloków (1..totalLen)
        for(int partsCount = 1; partsCount <= totalLen; ++partsCount){
            // partsCount bloków
            vector<int> parts(partsCount, 0);
            // both starting chars: 0 -> 'D', 1 -> 'P'
            for(int start = 0; start <= 1; ++start){
                bool found = generate_compositions_and_test(totalLen, partsCount, start, parts, 0, totalLen);
                if(found) return 0;
            }
        }
    }

    cout << "NIE znaleziono żadnej sekwencji do długości " << maxlen << "\n";
    return 0;
}
