#include <curses.h>
#include <string>

//Prototypes
void updateGUI(int numMachines);
void init();
void shutdown();

int main() {
  init(); //Initialize everything

  //A couple positions we'll need
  int counterX;
  int counterY;

  //A couple variables we'll need
  int multiplier = 1;
  int counterValue = 0;

  //
  int numMachines = 0;

  std::string converter;

  //Main input detection loop
  while (true) {

    int counterX = COLS / 2;
    int counterY = LINES / 2;

    int ch = getch();
    clear();

    switch(ch) {
      case ' ':
        counterValue += multiplier;
        break;

      case KEY_DOWN:
        shutdown();
        return 0;
        break;

      case KEY_UP:
        if (counterValue >= 250) {
          counterValue -= 250;

          numMachines += 1;
          multiplier += 5;
        }
        break;
    }

    converter = std::to_string(counterValue);
    mvprintw(counterY, counterX, converter.c_str());

    updateGUI(numMachines);

  }

}

void shutdown() {
  system("setterm -cursor on");

  endwin();
}

void updateGUI(int numMachines) {
  std::string converter = std::to_string(numMachines);

  std::string superMachines = "SUPER MACHINES";
  std::string buyFor = "BUY FOR 250";

  mvprintw(1, COLS / 4, buyFor.c_str());
  mvprintw(2, COLS / 4, superMachines.c_str());
  mvprintw(3, COLS / 4, converter.c_str());
}

void init() {
  initscr(); //Init the curse lib
  raw(); //Disable line buffering

  keypad(stdscr, TRUE); //Get F1, F2 etc...
  noecho(); // Don't echo() while we do getch()

  system("setterm -cursor off"); //Gets rid of the white cursor
}
