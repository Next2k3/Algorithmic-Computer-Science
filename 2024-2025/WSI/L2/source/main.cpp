#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <ctime>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <string>

using namespace std;
using namespace std::chrono;

int BOARD_SIZE = 3; 
int TOTAL_TILES;
string HEURISTIC_NAME;

struct PuzzleState {
    vector<int> board;
    int g, h;
    string path;

    bool operator>(const PuzzleState& other) const {
        return g + h > other.g + other.h;
    }
};

bool is_goal(const vector<int>& board) {
    for (int i = 0; i < TOTAL_TILES - 1; ++i)
        if (board[i] != i + 1) return false;
    return board[TOTAL_TILES - 1] == 0;
}

int manhattan(const vector<int>& board) {
    int dist = 0;
    for (int i = 0; i < TOTAL_TILES; ++i) {
        if (board[i] == 0) continue;
        int target = board[i] - 1;
        dist += abs(i / BOARD_SIZE - target / BOARD_SIZE) + abs(i % BOARD_SIZE - target % BOARD_SIZE);
    }
    return dist;
}

int misplaced(const vector<int>& board) {
    int count = 0;
    for (int i = 0; i < TOTAL_TILES; ++i)
        if (board[i] != 0 && board[i] != i + 1)
            ++count;
    return count;
}

int weighted_manhattan(const vector<int>& board) {
    int dist = 0;
    double weight = 1.5;
    
    for (int i = 0; i < TOTAL_TILES; ++i) {
        if (board[i] == 0) continue;
        int target = board[i] - 1;
        int manhattan_dist = abs(i / BOARD_SIZE - target / BOARD_SIZE) + abs(i % BOARD_SIZE - target % BOARD_SIZE);
        
        if (manhattan_dist > 0) {
            dist += manhattan_dist + static_cast<int>(weight * log2(manhattan_dist + 1));
        }
    }
    return dist;
}

bool is_solvable(const vector<int>& board) {
    int inv = 0;
    for (int i = 0; i < TOTAL_TILES; ++i) {
        if (board[i] == 0) continue;
        for (int j = i + 1; j < TOTAL_TILES; ++j)
            if (board[j] != 0 && board[i] > board[j])
                ++inv;
    }
    
    return inv % 2 == 0;
}

string serialize(const vector<int>& b) {
    string s;
    for (int n : b) s += to_string(n) + ",";
    return s;
}

void solve(const vector<int>& start_board, int heuristic_type) {
    auto start_time = high_resolution_clock::now();
    
    auto cmp = [](const PuzzleState& a, const PuzzleState& b) { return a > b; };
    priority_queue<PuzzleState, vector<PuzzleState>, decltype(cmp)> pq(cmp);
    unordered_set<string> visited;

    if (heuristic_type == 0) {
        HEURISTIC_NAME = "Manhattan";
    } else if (heuristic_type == 1) {
        HEURISTIC_NAME = "Misplaced";
    } else {
        HEURISTIC_NAME = "WeightedManhattan";
    }
    
    int h0;
    if (heuristic_type == 0) {
        h0 = manhattan(start_board);
    } else if (heuristic_type == 1) {
        h0 = misplaced(start_board);
    } else {
        h0 = weighted_manhattan(start_board);
    }
        
    pq.push({start_board, 0, h0, ""});

    while (!pq.empty()) {
        PuzzleState current = pq.top();
        pq.pop();
        string key = serialize(current.board);
        if (visited.count(key)) continue;
        visited.insert(key);

        if (is_goal(current.board)) {
            auto end_time = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end_time - start_time).count() / 1000000.0;
            
            cout << BOARD_SIZE << "x" << BOARD_SIZE << " " 
                 << HEURISTIC_NAME << " " 
                 << current.g << " " 
                 << visited.size() << " " 
                 << fixed << setprecision(3) << duration << endl;
             cout << "Ruchy: " << current.path << endl;
            return;
        }

        int zero_pos = find(current.board.begin(), current.board.end(), 0) - current.board.begin();
        int x = zero_pos / BOARD_SIZE, y = zero_pos % BOARD_SIZE;
        const int dx[] = {-1, 1, 0, 0};
        const int dy[] = {0, 0, -1, 1};
        const char dir[] = {'U', 'D', 'L', 'R'};

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || ny < 0 || nx >= BOARD_SIZE || ny >= BOARD_SIZE) continue;
            int npos = nx * BOARD_SIZE + ny;
            vector<int> new_board = current.board;
            swap(new_board[zero_pos], new_board[npos]);

            int h;
            if (heuristic_type == 0) 
                h = manhattan(new_board);
            else if (heuristic_type == 1) 
                h = misplaced(new_board);
            else 
                h = weighted_manhattan(new_board);
                
            pq.push({new_board, current.g + 1, h, current.path + dir[i]});
        }
    }

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end_time - start_time).count() / 1000000.0;
    
    cout << BOARD_SIZE << "x" << BOARD_SIZE << " " 
         << HEURISTIC_NAME << " " 
         << "BrakRozwiazania " 
         << visited.size() << " " 
         << fixed << setprecision(3) << duration << endl;
}

vector<int> generate_random_board() {
    vector<int> board(TOTAL_TILES);
    
    // Wypełniamy planszę liczbami od 1 do TOTAL_TILES-1
    iota(board.begin(), board.end() - 1, 1);
    
    // Ustawiamy zero jako ostatni element (prawy dolny róg)
    board[TOTAL_TILES - 1] = 0;

    random_device rd;
    mt19937 g(rd());

    do {
        // Tasujemy wszystkie elementy oprócz ostatniego (zero pozostaje w prawym dolnym rogu)
        shuffle(board.begin(), board.end() - 1, g);
    } while (!is_solvable(board));
    
    return board;
}

vector<int> generate_board_k_steps_from_goal(int k) {
    vector<int> board(TOTAL_TILES);
    iota(board.begin(), board.end() - 1, 1);
    board[TOTAL_TILES - 1] = 0; 

    int zero_pos = TOTAL_TILES - 1;
    int x = zero_pos / BOARD_SIZE, y = zero_pos % BOARD_SIZE;
    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};
    const char dir[] = {'U', 'D', 'L', 'R'};

    unordered_set<string> visited;
    visited.insert(serialize(board));  

    random_device rd;
    mt19937 g(rd());
    char last_move = '\0';

    for (int step = 0; step < k; ++step) {
        vector<pair<int, int>> moves;

        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && ny >= 0 && nx < BOARD_SIZE && ny < BOARD_SIZE) {
                int npos = nx * BOARD_SIZE + ny;

                // sprawdź, czy nie cofamy poprzedniego ruchu
                if ((last_move == 'U' && dir[d] == 'D') ||
                    (last_move == 'D' && dir[d] == 'U') ||
                    (last_move == 'L' && dir[d] == 'R') ||
                    (last_move == 'R' && dir[d] == 'L')) {
                    continue;
                }

                vector<int> temp_board = board;
                swap(temp_board[zero_pos], temp_board[npos]);

                if (visited.count(serialize(temp_board)) == 0) {
                    moves.emplace_back(d, npos);
                }
            }
        }

        if (moves.empty()) break;  // nie ma nowych ruchów

        shuffle(moves.begin(), moves.end(), g);
        int d = moves[0].first;
        int npos = moves[0].second;

        swap(board[zero_pos], board[npos]);
        zero_pos = npos;
        x = zero_pos / BOARD_SIZE;
        y = zero_pos % BOARD_SIZE;
        visited.insert(serialize(board));
        last_move = dir[d];
    }

    return board;
}



void print_board(const vector<int>& board) {
    cout << "Stan początkowy:" << endl;
    for (int i = 0; i < TOTAL_TILES; ++i) {
        if (board[i] == 0) cout << "   ";
        else cout << board[i] << (board[i] < 10 ? "  " : " ");
        if ((i + 1) % BOARD_SIZE == 0) cout << endl;
    }
    cout << endl;
}

int main() {

    cout << "Podaj rozmiar planszy (np. 3 dla 3x3, 4 dla 4x4): ";
    cin >> BOARD_SIZE;
    TOTAL_TILES = BOARD_SIZE * BOARD_SIZE;

    cout << "Wybierz tryb generowania planszy:\n";
    cout << "[1] Losowa poprawna plansza\n";
    cout << "[2] Plansza oddalona o k kroków od rozwiązania\n";
    cout << "[3] Własna plansza\n";
    int mode;
    cin >> mode;

    vector<int> board;
    if (mode == 1) {
        board = generate_random_board();
    } else if (mode == 2) {
        int k;
        cout << "Podaj liczbę kroków od rozwiązania: ";
        cin >> k;
        board = generate_board_k_steps_from_goal(k);
    } else {
      for (int i=0; i<TOTAL_TILES ;i++) {
        int tile;
        cin >> tile;
        board.push_back(tile);
      }
      if(is_solvable(board)) {
        cout << "Nie do rozwiązania" << endl;
      } 
    }

    print_board(board);

    cout << "[1] Manhattan Distance\n[2] Misplaced Tiles\n[3] Weighted Manhattan\nWybierz heurystykę: ";
    int h_choice;
    cin >> h_choice;
    int h_type;
    
    if (h_choice == 1) h_type = 0;
    else if (h_choice == 2) h_type = 1;
    else h_type = 2;

    solve(board, h_type);
    return 0;
}
