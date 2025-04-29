document.addEventListener('DOMContentLoaded', function() {
    if (document.getElementById('game-container')) {
        const words = [
            'komputer', 'programowanie', 'javascript', 'internet', 'keyboard', 
            'monitor', 'telefon', 'aplikacja', 'samochód', 'książka', 
            'klawiatura', 'algorytm', 'problem', 'słownik', 'tablica',
            'łańcuch', 'zmienne', 'funkcja', 'warunek', 'obiekt',
            'metoda', 'klasa', 'dziedziczenie', 'interfejs', 'implementacja',
            'architektura', 'projekt', 'dokumentacja', 'analiza', 'testowanie',
            'zadanie', 'rozwiązanie', 'struktura', 'zmienna', 'rekurencja'
        ];

        const alphabet = 'aąbcćdeęfghijklłmnńoópqrsśtuvwxyzźż'.split('');

        let selectedWord = '';
        let guessedLetters = [];
        let wrongAttempts = 0;
        let gameOver = false;

        const MAX_ATTEMPTS = 9;

        const STORAGE_KEY = {
            WORD: 'hangman_word',
            GUESSED: 'hangman_guessed',
            WRONG_ATTEMPTS: 'hangman_wrong_attempts',
            GAME_OVER: 'hangman_game_over'
        };

        function saveGameState() {
            localStorage.setItem(STORAGE_KEY.WORD, selectedWord);
            localStorage.setItem(STORAGE_KEY.GUESSED, JSON.stringify(guessedLetters));
            localStorage.setItem(STORAGE_KEY.WRONG_ATTEMPTS, wrongAttempts);
            localStorage.setItem(STORAGE_KEY.GAME_OVER, gameOver);
        }

        function loadGameState() {
            const savedWord = localStorage.getItem(STORAGE_KEY.WORD);
            
            if (savedWord) {
                selectedWord = savedWord;
                guessedLetters = JSON.parse(localStorage.getItem(STORAGE_KEY.GUESSED) || '[]');
                wrongAttempts = parseInt(localStorage.getItem(STORAGE_KEY.WRONG_ATTEMPTS) || '0');
                gameOver = localStorage.getItem(STORAGE_KEY.GAME_OVER) === 'true';
                return true;
            }
            
            return false;
        }

        function clearGameState() {
            localStorage.removeItem(STORAGE_KEY.WORD);
            localStorage.removeItem(STORAGE_KEY.GUESSED);
            localStorage.removeItem(STORAGE_KEY.WRONG_ATTEMPTS);
            localStorage.removeItem(STORAGE_KEY.GAME_OVER);
        }

        function initGame(loadSaved = true) {
            let hasRestoredGame = false;
            
            if (loadSaved && loadGameState()) {
                hasRestoredGame = true;
                console.log("Wczytano zapisany stan gry.");
            } else {
                selectedWord = words[Math.floor(Math.random() * words.length)];
                guessedLetters = [];
                wrongAttempts = 0;
                gameOver = false;
            }
            
            document.getElementById('winMessage').style.display = 'none';
            document.getElementById('loseMessage').style.display = 'none';
            
            const wordDisplay = document.getElementById('wordDisplay');
            wordDisplay.innerHTML = '';
            
            for (let i = 0; i < selectedWord.length; i++) {
                const letterSpace = document.createElement('div');
                letterSpace.className = 'letter-space';
                wordDisplay.appendChild(letterSpace);
            }
            
            const keyboard = document.getElementById('keyboard');
            keyboard.innerHTML = '';
            
            alphabet.forEach(letter => {
                const letterKey = document.createElement('div');
                letterKey.className = 'letter-key';
                letterKey.textContent = letter;
                
                if (guessedLetters.includes(letter)) {
                    letterKey.classList.add('used');
                }
                
                letterKey.addEventListener('click', () => handleLetterClick(letter, letterKey));
                keyboard.appendChild(letterKey);
            });
            
            const canvas = document.getElementById('hangman');
            const ctx = canvas.getContext('2d');
            ctx.clearRect(0, 0, canvas.width, canvas.height);
            
            drawBase();
            
            if (hasRestoredGame) {
                guessedLetters.forEach(letter => {
                    updateWordDisplay(letter);
                });
                
                for (let i = 1; i <= wrongAttempts; i++) {
                    drawHangman(i);
                }
                
                if (gameOver) {
                    const isWin = wrongAttempts < MAX_ATTEMPTS;
                    showEndGameMessage(isWin);
                }
            }
            
            saveGameState();
        }

        function showEndGameMessage(isWin) {
            if (isWin) {
                document.getElementById('winMessage').style.display = 'block';
            } else {
                document.getElementById('correctWord').textContent = selectedWord;
                document.getElementById('loseMessage').style.display = 'block';
                
                const letterSpaces = document.querySelectorAll('.letter-space');
                for (let i = 0; i < selectedWord.length; i++) {
                    letterSpaces[i].textContent = selectedWord[i];
                }
            }
        }

        function handleLetterClick(letter, letterKey) {
            if (gameOver || letterKey.classList.contains('used')) {
                return;
            }
            
            letterKey.classList.add('used');
            guessedLetters.push(letter);
            
            if (selectedWord.includes(letter)) {
                updateWordDisplay(letter);
                
                checkWin();
            } else {
                wrongAttempts++;
                drawHangman(wrongAttempts);
                
                if (wrongAttempts >= MAX_ATTEMPTS) {
                    endGame(false);
                }
            }
            
            saveGameState();
        }

        function updateWordDisplay(letter) {
            const letterSpaces = document.querySelectorAll('.letter-space');
            
            for (let i = 0; i < selectedWord.length; i++) {
                if (selectedWord[i] === letter) {
                    letterSpaces[i].textContent = letter;
                }
            }
        }

        function checkWin() {
            for (let i = 0; i < selectedWord.length; i++) {
                const currentLetter = selectedWord[i];
                if (!guessedLetters.includes(currentLetter)) {
                    return; 
                }
            }
            
            endGame(true);
        }

        function endGame(isWin) {
            gameOver = true;
            showEndGameMessage(isWin);
            
            saveGameState();
        }

        function drawBase() {
            const canvas = document.getElementById('hangman');
            const ctx = canvas.getContext('2d');
            
            ctx.strokeStyle = '#333';
            ctx.lineWidth = 3;
            ctx.beginPath();
            ctx.moveTo(50, 250);
            ctx.lineTo(250, 250);
            ctx.stroke();
        }

        function drawHangman(step) {
            const canvas = document.getElementById('hangman');
            const ctx = canvas.getContext('2d');
            
            ctx.strokeStyle = '#333';
            ctx.lineWidth = 3;
            ctx.fillStyle = '#333';
            
            switch(step) {
                case 1:
                    // Pionowy słupek
                    ctx.beginPath();
                    ctx.moveTo(100, 250);
                    ctx.lineTo(100, 50);
                    ctx.stroke();
                    break;
                case 2:
                    // Poziomy słupek
                    ctx.beginPath();
                    ctx.moveTo(100, 50);
                    ctx.lineTo(200, 50);
                    ctx.stroke();
                    break;
                case 3:
                    // Lina
                    ctx.beginPath();
                    ctx.moveTo(200, 50);
                    ctx.lineTo(200, 80);
                    ctx.stroke();
                    break;
                case 4:
                    // Głowa
                    ctx.beginPath();
                    ctx.arc(200, 100, 20, 0, Math.PI * 2);
                    ctx.stroke();
                    break;
                case 5:
                    // Tułów
                    ctx.beginPath();
                    ctx.moveTo(200, 120);
                    ctx.lineTo(200, 180);
                    ctx.stroke();
                    break;
                case 6:
                    // Lewa ręka
                    ctx.beginPath();
                    ctx.moveTo(200, 130);
                    ctx.lineTo(170, 160);
                    ctx.stroke();
                    break;
                case 7:
                    // Prawa ręka
                    ctx.beginPath();
                    ctx.moveTo(200, 130);
                    ctx.lineTo(230, 160);
                    ctx.stroke();
                    break;
                case 8:
                    // Lewa noga
                    ctx.beginPath();
                    ctx.moveTo(200, 180);
                    ctx.lineTo(170, 220);
                    ctx.stroke();
                    break;
                case 9:
                    // Prawa noga
                    ctx.beginPath();
                    ctx.moveTo(200, 180);
                    ctx.lineTo(230, 220);
                    ctx.stroke();
                    
                    // Smutna twarz
                    ctx.beginPath();
                    ctx.arc(190, 95, 3, 0, Math.PI * 2);
                    ctx.fill();
                    
                    ctx.beginPath();
                    ctx.arc(210, 95, 3, 0, Math.PI * 2);
                    ctx.fill();
                    
                    ctx.beginPath();
                    ctx.moveTo(190, 110);
                    ctx.lineTo(210, 110);
                    ctx.stroke();
                    break;
            }
        }

        const newGameBtn = document.getElementById('newGameBtn');
        if (newGameBtn) {
            newGameBtn.addEventListener('click', () => {
                clearGameState();
                initGame(false);
            });
        }

        const cancelGameBtn = document.getElementById('cancelGameBtn');
        if (cancelGameBtn) {
            cancelGameBtn.addEventListener('click', () => {
                clearGameState();
                initGame(false);
            });
        }

        initGame(true);

        window.addEventListener('beforeunload', () => {
            if (!gameOver) {
                saveGameState();
            }
        });
    }
});
