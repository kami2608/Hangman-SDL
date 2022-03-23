#include <bits/stdc++.h>
#include <SDL2/SDL.h>
using namespace std;

//********* Main Code **************
string chooseSecretWord();
char guessLetter();
bool update(char a);
void displayGameResult();

//*********************************
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int max_bad_guess_count = 10;
const string animals[] = {
    "cat", "frog", "chicken", "turtle", "crab", "rabbit", "shark", 
    "cow", "dog", "horse", "bull", "pig", "rhino", "sheep", "snake", "panda"
};
const string food[] = {
    "noodles", "apple", "sandwich", "peas", "mangoes",
    "candy", "pizza", "fish", "rice", "bread", "donuts"
};
const string jobs[] = {
    "nurse", "doctor", "artist", "singer", "dancer",
    "pilot", "driver", "student", "teacher", "farmer"
};
const string number[] = {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
    "eleven", "twelve", "thirteen", "fourteen", "fifteen", "fifty"
};
const int animalsCount = sizeof(animals) / sizeof(string);
const int foodCount = sizeof(food) / sizeof(string);
const int jobsCount = sizeof(jobs) / sizeof(string);
const int numberCount = sizeof(number) / sizeof(string);

int secretWordLenght;
string secretWord;
string guessWord;

SDL_Window *window;
SDL_Renderer *ren;
SDL_Texture *num[10], *letter[26], *bg, *line, *lose, *win, *select_content;
SDL_Texture *job, *numbers, *food1, *animal, *guess, *correct;

bool init();
SDL_Texture *loadTexture(string path);
void renderTexture(SDL_Texture *tex, int x, int y, int w, int h);
void renderTexture(SDL_Texture *tex, int x, int y);
void WaitUntilKeyPressed();
void close();

void loadMedia();
void showGame();
void renderStart();
void renderNum(int index);
void renderLetter(char a, int x, int y);
void renderLine();
void renderContent(SDL_Texture *tex);
void renderCorrect();
void renderGuess();
void renderResult(SDL_Texture *tex);

//************%% Main %%****************

int main(int argv, char* argc[]) {
    loadMedia();
    int badGuessCount = 0;
    secretWord = chooseSecretWord();
    secretWordLenght = secretWord.size();
    showGame();
    renderLine();
    guessWord = string(secretWord.size(),'-');
    do {
        char c = guessLetter();
        if(!update(c)) {
            badGuessCount++;
            renderNum(badGuessCount);
        }
    } while(badGuessCount < max_bad_guess_count && secretWord != guessWord);
    displayGameResult();
    WaitUntilKeyPressed();
    close();
    return 0;
}

//************************************
string chooseSecretWord() {
    srand(time(NULL));
    renderStart();
    SDL_Delay(500);
    SDL_Event e;
    int randomIndex;
    bool quit = false;
    while(!quit) {
        SDL_Delay(10);
        if(SDL_WaitEvent(&e) == 0) continue;
        if((e.type == SDL_QUIT) || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
            close();
            exit(1);
        }
        if(e.type == SDL_MOUSEBUTTONDOWN) {
            int x,y;
            x = e.button.x;
            y = e.button.y;
            if(e.button.button == SDL_BUTTON_LEFT || e.button.button == SDL_BUTTON_RIGHT || e.button.button == SDL_BUTTON_MIDDLE) {
                if(x >= 100 && x<= 339 && y>= 258 && y<= 354) {
                    // jobs
                    randomIndex = rand() % jobsCount;
                    renderContent(job);
                    SDL_Delay(1300);
                    return jobs[randomIndex];
                }
                else if(x >= 100 && x<= 339 && y>= 437 && y<= 535) {
                    // food
                    randomIndex = rand() % foodCount;
                    renderContent(food1);
                    SDL_Delay(1300);
                    return food[randomIndex];
                }
                else if(x >= 446 && x<= 686 && y>= 258 && y<= 354) {
                    // animals
                    randomIndex = rand() % animalsCount;
                    renderContent(animal);
                    SDL_Delay(1300);
                    return animals[randomIndex];
                }
                else if(x >= 446 && x<= 686 && y>= 436 && y<= 535) {
                    // numbers
                    randomIndex = rand() % numberCount;
                    renderContent(numbers); 
                    SDL_Delay(1300);
                    return number[randomIndex];
                    }
            }
            quit = true; 
        }
    }

    // int k;
    // bool quit = false;
    // while(!quit) {
    //     while(SDL_PollEvent(&e) != 0)
    //         if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) 
    //             quit = true;
    //         else if(e.type == SDL_KEYDOWN) {
    //             switch (e.key.keysym.sym)
    //             {
    //             case SDLK_UP:
    //                 randomIndex = rand() % jobsCount;
    //                 renderContent(job);
    //                 k = 1;
    //                 break;
    //             case SDLK_DOWN:
    //                 randomIndex = rand() % animalsCount;
    //                 renderContent(animal);
    //                 k = 2;
    //                 break;
    //             case SDLK_LEFT:
    //                 randomIndex = rand() % foodCount;
    //                 renderContent(food1);
    //                 k = 3;
    //                 break;
    //             case SDLK_RIGHT:
    //                 randomIndex = rand() % numberCount;
    //                 renderContent(numbers);
    //                 k = 4;
    //                 break;
    //             default:
    //                 break;
    //             }
    //         }
    // }
    // SDL_Delay(1300);
    // if(k == 1) return jobs[randomIndex];
    // if(k == 2) return animals[randomIndex];
    // if(k == 3) return food[randomIndex];
    // if(k == 4) return number[randomIndex];
}

char guessLetter() {
    char c;
    SDL_Delay(100);
    renderGuess();
    SDL_Event e;
    bool quit = false;
    while(!quit) {
        SDL_Delay(10);
        if(SDL_WaitEvent(&e) == 0) continue;
        if((e.type == SDL_QUIT) || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
            close();
            exit(1);
        }
        if(e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym)
            {
            case SDLK_a:
                c = 'a';
                quit = true;
                break;
            case SDLK_b:
                c = 'b';
                quit = true;
                break;
            case SDLK_c:
                c = 'c';
                quit = true;
                break;
            case SDLK_d:
                c = 'd';
                quit = true;
                break;
            case SDLK_e:
                c = 'e';
                quit = true;
                break;
            case SDLK_f:
                c = 'f';
                quit = true;
                break;
            case SDLK_g:
                c = 'g';
                quit = true;
                break;
            case SDLK_h:
                c = 'h';
                quit = true;
                break;
            case SDLK_i:
                c = 'i';
                quit = true;
                break;
            case SDLK_j:
                c = 'j';
                quit = true;
                break;
            case SDLK_k:
                c = 'k';
                quit = true;
                break;
            case SDLK_l:
                c = 'l';
                quit = true;
                break;
            case SDLK_m:
                c = 'm';
                quit = true;
                break;
            case SDLK_n:
                c = 'n';
                quit = true;
                break;
            case SDLK_o:
                c = 'o';
                quit = true;
                break;
            case SDLK_p:
                c = 'p';
                quit = true;
                break;
            case SDLK_q:
                c = 'q';
                quit = true;
                break;
            case SDLK_r:
                c = 'r';
                quit = true;
                break;
            case SDLK_s:
                c = 's';
                quit = true;
                break;
            case SDLK_t:
                c = 't';
                quit = true;
                break;
            case SDLK_u:
                c = 'u';
                quit = true;
                break;
            case SDLK_v:
                c = 'v';
                quit = true;
                break;
            case SDLK_w:
                c = 'w';
                quit = true;
                break;
            case SDLK_z:
                c = 'z';
                quit = true;
                break;
            case SDLK_y:
                c = 'y';
                quit = true;
                break;
            case SDLK_x:
                c = 'x';
                quit = true;
                break;
            default:
                break;
            }
        }
    }
    SDL_Delay(1000);
    return c;
}

bool update(char a) {
    bool ok=false;
    for(int i=0 ; i<secretWordLenght ; i++) 
        if(secretWord[i] == a && guessWord[i] == '-') {
            guessWord[i] = a;
            ok = true;
        }
    if(ok) {
        int x = 440-44*secretWordLenght;
        for(int i=0 ; i<guessWord.size() ; i++) 
            if(guessWord[i] != '-') renderLetter(guessWord[i], x/2+44*i+320, 223);
    }
    return ok;
}

void displayGameResult() {
     if(secretWord == guessWord) renderResult(win);
    else {
        renderResult(lose);
        SDL_Delay(500);
        renderCorrect();
    }
}

//*********************************
void loadMedia() {
    if(!init()) cout<<"Fail init"<<endl;
    else {
        bg = loadTexture("images/bg.bmp");
        select_content = loadTexture("images/select_content.bmp");
        lose = loadTexture("images/lose.bmp");
        win = loadTexture("images/win.bmp");
        line = loadTexture("images/line.bmp");
        animal = loadTexture("images/animals.bmp");
        job = loadTexture("images/job.bmp");
        numbers = loadTexture("images/number.bmp");
        food1 = loadTexture("images/food.bmp");
        guess = loadTexture("images/guess.bmp");
        correct = loadTexture("images/correct.bmp");
        bool check = true;
        for(int i=1 ; i<=10; i++) {
            num[i] = loadTexture("images/" + to_string(i) + ".bmp");
            if(num[i] == NULL) {
                check = false;
                break;
            }
        }
        for(char i='a' ; i<='z'; i++) {
            string s = "images/";
            s += i;
            s += ".bmp";
            letter[i] = loadTexture(s.c_str());
            if(letter[i] == NULL) {
                check = false;
                break;
            }
        }
        if(!check || bg == NULL || select_content == NULL || lose == NULL || win == NULL || guess == NULL ||
         line == NULL || animal == NULL || job == NULL || numbers == NULL || food1 == NULL || correct == NULL) {
            cout<<"coudn't load image"<<endl;
            close();
        }
    }
}

void showGame() {
    SDL_RenderClear(ren);
    renderTexture(bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent(ren);
}

void renderStart() {
    SDL_RenderClear(ren);
    renderTexture(select_content, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent(ren);
}

void renderNum(int index) {
    renderTexture(num[index], 18, 200);
    SDL_RenderPresent(ren);
}

void renderLetter(char a, int x, int y) {
    renderTexture(letter[a], x, y);
    SDL_RenderPresent(ren);
}

void renderLine() {
    int x = 440-44*secretWordLenght;
    for(int i=x/2 ; i< 44*secretWordLenght + x/2 ; i+=44) {
        renderTexture(line, i+320, 270);
    }
    SDL_RenderPresent(ren);
}

void renderContent(SDL_Texture *tex) {
    renderTexture(tex, 247, 200);
    SDL_RenderPresent(ren);
}

void renderCorrect() {
    renderTexture(correct, 292, 55);
    SDL_Delay(100);
    int x = 440-44*secretWordLenght;
    int j=0;
    for(int i=x/2 ; i<= 44*secretWordLenght + x/2 ; i+=44) {
        renderLetter(secretWord[j], i+320, 223);
        j++;
    }
    SDL_RenderPresent(ren);
}

void renderResult(SDL_Texture *tex) {
    renderTexture(tex, 390, 366);
    SDL_RenderPresent(ren);
}

void renderGuess() {
    renderTexture(guess, 292, 55);
    SDL_RenderPresent(ren);
}

//************ SDL Function **************
bool init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout<<"SDL could not be initialized"<<endl;
        return false;
    }
    else {
        window = SDL_CreateWindow("Hangman SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL) {
            cout<<"Window could not be created"<<endl;
            return false;
        }
        else {
            ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        }
    }
    return true;
}

SDL_Texture *loadTexture(string path) {
    SDL_Texture *tex = NULL;
    SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == NULL) cout<<"Unable to load image surface"<<endl;
    else {
        tex = SDL_CreateTextureFromSurface(ren, loadedSurface);
        SDL_FreeSurface(loadedSurface);
    }
    return tex;
}

void renderTexture(SDL_Texture *tex, int x, int y) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, tex, NULL, &dst);
}

void renderTexture(SDL_Texture *tex, int x, int y, int w, int h) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(ren, tex, NULL, &dst);
}

void WaitUntilKeyPressed() {
    SDL_Event e;
    while(true) {
        if(SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_QUIT)) {
            return ;
            SDL_Delay(100);
        }
    }
}

void close() {
    SDL_DestroyTexture(bg);
    bg = NULL;
    for(int i=1 ; i<=10 ; i++) {
        SDL_DestroyTexture(num[i]);
        num[i] = NULL;
    }
    for(int i=97; i<=122 ; i++) {
        SDL_DestroyTexture(letter[i]);
        letter[i] = NULL;
    }
    SDL_DestroyTexture(lose);
    lose = NULL;
    SDL_DestroyTexture(win);
    win = NULL;
    SDL_DestroyTexture(select_content);
    select_content = NULL;
    SDL_DestroyTexture(line);
    line = NULL;
    SDL_DestroyTexture(animal);
    animal = NULL;
    SDL_DestroyTexture(job);
    job = NULL;
    SDL_DestroyTexture(numbers);
    numbers = NULL;
    SDL_DestroyTexture(food1);
    food1 = NULL;
    SDL_DestroyTexture(guess);
    guess = NULL;
    SDL_DestroyTexture(correct);
    correct = NULL;
    SDL_DestroyRenderer(ren);
    ren = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}
