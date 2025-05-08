#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <arpa/inet.h>
#include <limits.h>

#include "./board.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Wagi heurystyczne
#define WIN_SCORE 1000
#define LOSE_SCORE -1000
#define THREE_IN_ROW_SCORE 25
#define TWO_IN_ROW_SCORE 5
#define BLOCKING_SCORE 2

int minimax(int depth, int player, int alpha, int beta);
int evaluateBoard(int player);
int getBestMove(int player, int depth);
bool isGameOver(int *winner);
bool checkLine(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int player);
bool checkThreeLine(int x1, int y1, int x2, int y2, int x3, int y3, int player);
int countInLine(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int player);

int minimax(int depth, int player, int alpha, int beta) {
    int winner = 0;
    
    // Sprawdź czy gra się skończyła lub czy osiągnęliśmy maksymalną głębokość
    if (depth == 0 || isGameOver(&winner)) {
        return evaluateBoard(player);
    }
    
    int opponent = 3 - player;
    int bestScore, score;
    int bestMove = -1;
    
    if (player == 1) { // Gracz maksymalizujący
        bestScore = INT_MIN;
        
        // Sprawdź wszystkie możliwe ruchy
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (board[i][j] == 0) {

                    board[i][j] = player;
                    
                    // Wywołaj rekurencyjnie minimax
                    score = minimax(depth - 1, opponent, alpha, beta);
                    
                    board[i][j] = 0;
                    
                    // Aktualizuj najlepszy wynik
                    if (score > bestScore) {
                        bestScore = score;
                        bestMove = (i + 1) * 10 + (j + 1);
                    }
                    
                    // Przycinanie alfa-beta
                    alpha = MAX(alpha, bestScore);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
            
            // Sprawdzenie przycinania alfa-beta
            if (beta <= alpha) {
                break;
            }
        }
        
        return bestScore;
    } else { // Gracz minimalizujący
        bestScore = INT_MAX;
        
        // Sprawdź wszystkie możliwe ruchy
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (board[i][j] == 0) {

                    board[i][j] = player;
                    
                    // Wywołaj rekurencyjnie minimax
                    score = minimax(depth - 1, opponent, alpha, beta);
                    
                    board[i][j] = 0;
                    
                    // Aktualizuj najlepszy wynik
                    if (score < bestScore) {
                        bestScore = score;
                        bestMove = (i + 1) * 10 + (j + 1);
                    }
                    
                    // Przycinanie alfa-beta
                    beta = MIN(beta, bestScore);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
            
            // Sprawdzenie przycinania alfa-beta
            if (beta <= alpha) {
                break;
            }
        }
        
        return bestScore;
    }
}

int getBestMove(int player, int depth) {
    int bestScore = (player == 1) ? INT_MIN : INT_MAX;
    int bestMove = -1;
    int moveCount = 0;
    int possibleMoves[25];
    int opponent = 3 - player;
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == 0) {

                board[i][j] = player;
                
                // Jeśli ten ruch tworzy nieprzerwany ciąg trzech symboli bez tworzenia linii czterech,
                // to prowadzi do natychmiastowej przegranej - unikaj go
                bool creates_three = false;
                for (int row = 0; row < 5; row++) {
                    for (int col = 0; col <= 2; col++) {
                        if (checkThreeLine(row, col, row, col+1, row, col+2, player)) {
                            creates_three = true;
                        }
                    }
                }
                for (int col = 0; col < 5; col++) {
                    for (int row = 0; row <= 2; row++) {
                        if (checkThreeLine(row, col, row+1, col, row+2, col, player)) {
                            creates_three = true;
                        }
                    }
                }
                for (int row = 0; row <= 2; row++) {
                    for (int col = 0; col <= 2; col++) {
                        if (checkThreeLine(row, col, row+1, col+1, row+2, col+2, player)) {
                            creates_three = true;
                        }
                    }
                }
                for (int row = 0; row <= 2; row++) {
                    for (int col = 2; col < 5; col++) {
                        if (checkThreeLine(row, col, row+1, col-1, row+2, col-2, player)) {
                            creates_three = true;
                        }
                    }
                }
                
                // Sprawdź czy ten ruch tworzy wygraną (cztery w rzędzie)
                bool creates_win = false;

                for (int row = 0; row < 5; row++) {
                    for (int col = 0; col <= 1; col++) {
                        if (checkLine(row, col, row, col+1, row, col+2, row, col+3, player)) {
                            creates_win = true;
                        }
                    }
                }

                for (int col = 0; col < 5; col++) {
                    for (int row = 0; row <= 1; row++) {
                        if (checkLine(row, col, row+1, col, row+2, col, row+3, col, player)) {
                            creates_win = true;
                        }
                    }
                }

                for (int row = 0; row <= 1; row++) {
                    for (int col = 0; col <= 1; col++) {
                        if (checkLine(row, col, row+1, col+1, row+2, col+2, row+3, col+3, player)) {
                            creates_win = true;
                        }
                    }
                }

                for (int row = 3; row < 5; row++) {
                    for (int col = 0; col <= 1; col++) {
                        if (checkLine(row, col, row-1, col+1, row-2, col+2, row-3, col+3, player)) {
                            creates_win = true;
                        }
                    }
                }
                
                if (creates_three && !creates_win) {
                    // Pomiń ten ruch, ponieważ prowadziłby do natychmiastowej przegranej
                    board[i][j] = 0;
                    continue;
                }
                
                int score = minimax(depth - 1, opponent, INT_MIN, INT_MAX);
                
                board[i][j] = 0;
                
                // Aktualizuj najlepszy wynik i ruch
                if ((player == 1 && score > bestScore) || (player == 2 && score < bestScore)) {
                    bestScore = score;
                    bestMove = (i + 1) * 10 + (j + 1);
                    moveCount = 1;
                    possibleMoves[0] = bestMove;
                } else if (score == bestScore) {
                    // Jeśli mamy wiele ruchów z takim samym wynikiem, wybierzemy losowo jeden z nich
                    possibleMoves[moveCount] = (i + 1) * 10 + (j + 1);
                    moveCount++;
                }
            }
        }
    }
    
    // Jeśli mamy kilka najlepszych ruchów, wybierz jeden losowo
    if (moveCount > 1) {
        bestMove = possibleMoves[rand() % moveCount];
    }
    
    return bestMove;
}

/**
 * Sprawdź czy linia zawiera dokładnie trzy symbole danego gracza bez symboli przeciwnika
 */
bool checkThreeLine(int x1, int y1, int x2, int y2, int x3, int y3, int player) {
    return (board[x1][y1] == player && board[x2][y2] == player && board[x3][y3] == player);
}

/**
 * Sprawdź czy linia zawiera dokładnie cztery symbole danego gracza bez symboli przeciwnika
 */
bool checkLine(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int player) {
    return (board[x1][y1] == player && board[x2][y2] == player && 
            board[x3][y3] == player && board[x4][y4] == player);
}

/**
 * Policz liczbę symboli danego gracza w linii
 */
int countInLine(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int player) {
    int count = 0;
    int opponent = 3 - player;
    
    // Jeśli w linii jest symbol przeciwnika, zwróć 0
    if (board[x1][y1] == opponent || board[x2][y2] == opponent || 
        board[x3][y3] == opponent || board[x4][y4] == opponent) {
        return 0;
    }
    
    // Policz symbole gracza
    if (board[x1][y1] == player) count++;
    if (board[x2][y2] == player) count++;
    if (board[x3][y3] == player) count++;
    if (board[x4][y4] == player) count++;
    
    return count;
}

bool isGameOver(int *winner) {
    *winner = 0;
    
    // Sprawdź czy jest zwycięzca (cztery w rzędzie)
    for (int player = 1; player <= 2; player++) {

        for (int row = 0; row < 5; row++) {
            for (int col = 0; col <= 1; col++) {
                if (checkLine(row, col, row, col+1, row, col+2, row, col+3, player)) {
                    *winner = player;
                    return true;
                }
            }
        }
        
        for (int col = 0; col < 5; col++) {
            for (int row = 0; row <= 1; row++) {
                if (checkLine(row, col, row+1, col, row+2, col, row+3, col, player)) {
                    *winner = player;
                    return true;
                }
            }
        }
        
        for (int row = 0; row <= 1; row++) {
            for (int col = 0; col <= 1; col++) {
                if (checkLine(row, col, row+1, col+1, row+2, col+2, row+3, col+3, player)) {
                    *winner = player;
                    return true;
                }
            }
        }
        
        for (int row = 3; row < 5; row++) {
            for (int col = 0; col <= 1; col++) {
                if (checkLine(row, col, row-1, col+1, row-2, col+2, row-3, col+3, player)) {
                    *winner = player;
                    return true;
                }
            }
        }
        
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col <= 2; col++) {
                if (checkThreeLine(row, col, row, col+1, row, col+2, player)) {
                    *winner = 3 - player; 
                    return true;
                }
            }
        }
        for (int col = 0; col < 5; col++) {
            for (int row = 0; row <= 2; row++) {
                if (checkThreeLine(row, col, row+1, col, row+2, col, player)) {
                    *winner = 3 - player;
                    return true;
                }
            }
        }
        for (int row = 0; row <= 2; row++) {
            for (int col = 0; col <= 2; col++) {
                if (checkThreeLine(row, col, row+1, col+1, row+2, col+2, player)) {
                    *winner = 3 - player; 
                    return true;
                }
            }
        }
        for (int row = 0; row <= 2; row++) {
            for (int col = 2; col < 5; col++) {
                if (checkThreeLine(row, col, row+1, col-1, row+2, col-2, player)) {
                    *winner = 3 - player; 
                    return true;
                }
            }
        }
    }
    
    // Sprawdź czy plansza jest pełna (remis)
    bool isFull = true;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == 0) {
                isFull = false;
                break;
            }
        }
        if (!isFull) {
            break;
        }
    }
    
    return isFull;
}

/**
 * Ocena aktualnego stanu planszy dla danego gracza
 *
 * Wyjaśnienie funkcji heurystycznej:
 * 1. Jeśli gracz wygrał, zwraca wysoką wartość dodatnią (WIN_SCORE)
 * 2. Jeśli gracz przegrał, zwraca wysoką wartość ujemną (LOSE_SCORE)
 * 3. Oblicza wynik na podstawie potencjalnych pozycji wygrywających:
 *    a. Liczy liczbę symboli gracza w każdej potencjalnej linii wygrywającej (poziomej, pionowej, przekątnej)
 *    b. Przyznaje wyższe wyniki za więcej symboli w rzędzie (np. trzy w rzędzie jest lepsze niż dwa w rzędzie)
 *    c. Nakłada kary za pozycje, które mogą prowadzić do utworzenia trzech w rzędzie przez przeciwnika
 *    d. Przyznaje bonusowe punkty za blokowanie potencjalnych ruchów wygrywających przeciwnika
 */
int evaluateBoard(int player) {
    int opponent = 3 - player;
    int score = 0;
    int winner = 0;
    
    if (isGameOver(&winner)) {
        if (winner == player) {
            return WIN_SCORE;
        } else if (winner == opponent) {
            return LOSE_SCORE;
        } else {
            return 0; // Remis
        }
    }
    
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col <= 1; col++) {
            int playerCount = countInLine(row, col, row, col+1, row, col+2, row, col+3, player);
            int opponentCount = countInLine(row, col, row, col+1, row, col+2, row, col+3, opponent);
            
            if (playerCount == 3) {
                score += THREE_IN_ROW_SCORE;
            } else if (playerCount == 2) {
                score += TWO_IN_ROW_SCORE;
            }
            
            if (opponentCount == 3) {
                score -= THREE_IN_ROW_SCORE;
            } else if (opponentCount == 2) {
                score -= TWO_IN_ROW_SCORE;
            }
        }
    }
    
    for (int col = 0; col < 5; col++) {
        for (int row = 0; row <= 1; row++) {
            int playerCount = countInLine(row, col, row+1, col, row+2, col, row+3, col, player);
            int opponentCount = countInLine(row, col, row+1, col, row+2, col, row+3, col, opponent);
            
            if (playerCount == 3) {
                score += THREE_IN_ROW_SCORE;
            } else if (playerCount == 2) {
                score += TWO_IN_ROW_SCORE;
            }
            
            if (opponentCount == 3) {
                score -= THREE_IN_ROW_SCORE;
            } else if (opponentCount == 2) {
                score -= TWO_IN_ROW_SCORE;
            }
        }
    }
    
    for (int row = 0; row <= 1; row++) {
        for (int col = 0; col <= 1; col++) {
            int playerCount = countInLine(row, col, row+1, col+1, row+2, col+2, row+3, col+3, player);
            int opponentCount = countInLine(row, col, row+1, col+1, row+2, col+2, row+3, col+3, opponent);
            
            if (playerCount == 3) {
                score += THREE_IN_ROW_SCORE;
            } else if (playerCount == 2) {
                score += TWO_IN_ROW_SCORE;
            }
            
            if (opponentCount == 3) {
                score -= THREE_IN_ROW_SCORE;
            } else if (opponentCount == 2) {
                score -= TWO_IN_ROW_SCORE;
            }
        }
    }
    
    for (int row = 3; row < 5; row++) {
        for (int col = 0; col <= 1; col++) {
            int playerCount = countInLine(row, col, row-1, col+1, row-2, col+2, row-3, col+3, player);
            int opponentCount = countInLine(row, col, row-1, col+1, row-2, col+2, row-3, col+3, opponent);
            
            if (playerCount == 3) {
                score += THREE_IN_ROW_SCORE;
            } else if (playerCount == 2) {
                score += TWO_IN_ROW_SCORE;
            }
            
            if (opponentCount == 3) {
                score -= THREE_IN_ROW_SCORE;
            } else if (opponentCount == 2) {
                score -= TWO_IN_ROW_SCORE;
            }
        }
    }
    
    // Sprawdź blokujące symbole (symbole, które uniemożliwiają przeciwnikowi utworzenie linii)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == player) {
                if (j > 0 && j < 4 && board[i][j-1] == opponent && board[i][j+1] == opponent) {
                    score += BLOCKING_SCORE;
                }

                if (i > 0 && i < 4 && board[i-1][j] == opponent && board[i+1][j] == opponent) {
                    score += BLOCKING_SCORE;
                }

                if (i > 0 && i < 4 && j > 0 && j < 4 && 
                    board[i-1][j-1] == opponent && board[i+1][j+1] == opponent) {
                    score += BLOCKING_SCORE;
                }

                if (i > 0 && i < 4 && j > 0 && j < 4 && 
                    board[i+1][j-1] == opponent && board[i-1][j+1] == opponent) {
                    score += BLOCKING_SCORE;
                }
            }
        }
    }
    
    return score;
}

int main(int argc, char *argv[]) {
    int server_socket;
    struct sockaddr_in server_addr;
    char server_message[16], player_message[16];
    
    bool end_game;
    int player, msg, move;
    int search_depth;
    
    if (argc != 6) {
        printf("Nieprawidłowa liczba argumentów\n");
        printf("Użycie: %s <adres_ip_serwera> <port_serwera> <numer_gracza> <nazwa_gracza> <głębokość_przeszukiwania>\n", argv[0]);
        return -1;
    }
    
    srand(time(NULL));
    
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        printf("Nie można utworzyć socketu\n");
        return -1;
    }
    printf("Socket utworzony pomyślnie\n");
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    
    if (connect(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Nie można połączyć\n");
        return -1;
    }
    printf("Połączono z serwerem pomyślnie\n");
    
    memset(server_message, '\0', sizeof(server_message));
    if (recv(server_socket, server_message, sizeof(server_message), 0) < 0) {
        printf("Błąd podczas odbierania wiadomości serwera\n");
        return -1;
    }
    
    memset(player_message, '\0', sizeof(player_message));
    snprintf(player_message, sizeof(player_message), "%s %s", argv[3], argv[4]);
    if (send(server_socket, player_message, strlen(player_message), 0) < 0) {
        printf("Nie można wysłać wiadomości\n");
        return -1;
    }
    
    setBoard();
    end_game = false;
    sscanf(argv[3], "%d", &player);
    sscanf(argv[5], "%d", &search_depth);
    
    if (search_depth < 1) search_depth = 1;
    if (search_depth > 10) search_depth = 10;
    
    while (!end_game) {
        memset(server_message, '\0', sizeof(server_message));
        if (recv(server_socket, server_message, sizeof(server_message), 0) < 0) {
            printf("Błąd podczas odbierania wiadomości serwera\n");
            return -1;
        }
        sscanf(server_message, "%d", &msg);
        move = msg % 100;
        msg = msg / 100;
        if (move != 0) {
            setMove(move, 3 - player);
        }
        if ((msg == 0) || (msg == 6)) {
            move = getBestMove(player, search_depth);
            setMove(move, player);
            memset(player_message, '\0', sizeof(player_message));
            snprintf(player_message, sizeof(player_message), "%d", move);
            if (send(server_socket, player_message, strlen(player_message), 0) < 0) {
                printf("Nie można wysłać wiadomości\n");
                return -1;
            }
        } else {
            end_game = true;
            switch (msg) {
                case 1: printf("Wygrałeś.\n"); break;
                case 2: printf("Przegrałeś.\n"); break;
                case 3: printf("Remis.\n"); break;
                case 4: printf("Wygrałeś. Błąd przeciwnika.\n"); break;
                case 5: printf("Przegrałeś. Twój błąd.\n"); break;
            }
        }
    }
    
    close(server_socket);
    
    return 0;
}