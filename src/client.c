#include <curses.h>
#include <signal.h>
#include "client.h"
#include "log.h"

// Global variables
int command_mode = 0;
int input_height = 1;
size_t position = 0;
static char command_buffer[1024];
WINDOW *main_window;
WINDOW *input_window;

// Function prototypes
WINDOW *create_window(int height, int width, int starty, int startx);
void handle_input();
void init_curses();
void refresh_view();
void resize_view();

/** Bootstrapping of the client functionality */
int ant_client_start(void) {
   int ch;

   // Initialise the curses environment
   init_curses();

   // Endlessly process user input and bail out when escape is pressed.
   // Pressing escape while in command mode will exit command mode, not the
   // program.
   while ((ch = getch()) != 27 || command_mode == 1) {
      handle_input(ch);
   }

   endwin();
   return 0;
}

/** Creates a new window given its dimensions and coordinates */
WINDOW *create_window(int height, int width, int starty, int startx) {
   return newwin(height, width, starty, startx);
}

/** Initialises the screen and sets sane curses behaviour/defaults */
void init_curses() {
   int main_height;

   initscr();
   cbreak();
   noecho();
   keypad(stdscr, TRUE);

   // Create the main and input windows
   main_height = LINES - input_height;
   main_window = create_window(main_height, COLS, 0, 0);
   input_window = create_window(input_height, COLS, main_height, 0);

   // Set up the window colours if supported
   if (has_colors()) {
      start_color();
      use_default_colors();
      init_pair(1, COLOR_BLACK, COLOR_WHITE);
      init_pair(2, COLOR_WHITE, COLOR_BLACK);
      wbkgd(main_window, COLOR_PAIR(1));
      wbkgd(input_window, COLOR_PAIR(2));
   }

   // Ensure the curses changes are realised
   refresh_view();
}

/** Refreshes the windows in order from bottom to top */
void refresh_view() {
   refresh();
   wrefresh(main_window);
   wrefresh(input_window);
}

/** Resizes the windows according to the size of the terminal */
void resize_view() {
   int height, width;

   // Get the new dimensions of the screen
   getmaxyx(stdscr, height, width);

   // Resize the main window
   wresize(main_window, height - input_height, width);
   mvwin(main_window, 0, 0);

   // Resize the input window
   wresize(input_window, input_height, width);
   mvwin(input_window, height - input_height, 0);

   // Refresh the entire view
   refresh_view();
}

/* Processes user input */
void handle_input(int ch) {
   // Check if the character entered is a backspace
   if (ch == erasechar()) {
      ch = KEY_BACKSPACE;
   }

   switch(ch) {
      case ERR:
         // -1 is sent when there is no input, e.g. when the terminal
         // is being resized. Nothing to do.
         break;

      case 27:
         // Escape pressed so exit command mode
         if (command_mode) {
            command_mode = 0;
            wclear(input_window);
            wrefresh(input_window);
         }
         break;

      case KEY_RESIZE:
         // The terminal is being resized
         resize_view();
         break;

      case ':':
         wechochar(input_window, ch);

         // Switch to command mode
         if (!command_mode) {
            command_mode = 1;
         } else {
            command_buffer[position++] = (char)ch;
         }
         break;

      case KEY_BACKSPACE:
         if (position > 0) {
            // Move the cursor back one character
            wmove(input_window, 0, position);

            // Remove the character from the buffer
            command_buffer[--position] = 0;

            // Delete the character from the window under the cursor
            // and refresh the window
            wdelch(input_window);
            wrefresh(input_window);
         }
         break;

      case KEY_ENTER:
      case '\n':
         // Terminate the command string and reset the command variables
         command_buffer[position++] = 0;
         position = 0;
         command_mode = 0;

         // Reset the input window
         wclear(input_window);
         wrefresh(input_window);
         ant_log("Entered command: %s", command_buffer);
         break;

      default:
         // Echo the character if command mode is active
         if (command_mode == 1) {
            command_buffer[position++] = (char)ch;
            wechochar(input_window, ch);
         }
         break;
   }
}
