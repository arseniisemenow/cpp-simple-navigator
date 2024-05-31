#include "ChooseFilePath.h"
#include <unistd.h>
#include <ncurses.h>
#include <string>
#include <vector>
#include <algorithm>
#include <dirent.h>

std::vector<std::string> ListDirectories(const std::string &path) {
  std::vector<std::string> directories;
  DIR *dir;
  struct dirent *entry;

  // Open directory
  dir = opendir(path.c_str());
  if (dir != nullptr) {

    while ((entry = readdir(dir)) != nullptr) {
      if (entry->d_type == DT_DIR && std::string(entry->d_name) != "." && std::string(entry->d_name) != "..") {
        directories.push_back(entry->d_name);
      }
    }
    closedir(dir);
  }

  return directories;
}
void ChooseFilePath(std::string &selected_path) {
  int row, col;
  getmaxyx(stdscr, row, col);

  // Create a window for the file path selection UI
  WINDOW *win = newwin(row - 4, col - 4, 2, 2);
  box(win, 0, 0);
  mvwprintw(win, 0, 2, "Select a directory");
  wrefresh(win);

  // Display instructions
  mvprintw(row - 2, 0, "Use arrow keys to navigate, press Enter to select, and Esc to cancel.");

  // Display current dataset path
  mvprintw(row - 1, 0, "Current path: %s", selected_path.c_str());
  refresh();

  // Initial directory browsing
  std::string current_path = selected_path;
  std::vector<std::string> directories = ListDirectories(current_path);
  std::sort(directories.begin(), directories.end());

  // Main loop for file path selection
  int selected_index = 0;
  int ch;
  bool done = false;
  while (!done) {
    // Clear window and redraw
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, "Select a directory");
    for (size_t i = 0; i < directories.size(); ++i) {
      if (static_cast<int>(i) == selected_index) {
        wattron(win, A_REVERSE);
        mvwprintw(win, i + 1, 1, "%s", directories[i].c_str());
        wattroff(win, A_REVERSE);
      } else {
        mvwprintw(win, i + 1, 1, "%s", directories[i].c_str());
      }
    }
    wrefresh(win);

    ch = getch();
    switch (ch) {
      case KEY_UP:
        if (selected_index > 0)
          --selected_index;
        break;
      case KEY_DOWN:
        if (selected_index < static_cast<int>(directories.size()) - 1)
          ++selected_index;
        break;           case KEY_LEFT: // Navigate up
      {
        // Find the last occurrence of '/' in current_path
        size_t pos = current_path.find_last_of('/');
        if (pos != std::string::npos) {
          current_path = current_path.substr(0, pos);
          directories = ListDirectories(current_path);
          std::sort(directories.begin(), directories.end());
          selected_index = 0;
        }
      }
        break;
      case KEY_RIGHT: // Navigate down
        if (!directories.empty()) {
          std::string selected_dir = directories[selected_index];
          if (current_path.back() != '/')
            current_path += '/';
          current_path += selected_dir;
          directories = ListDirectories(current_path);
          std::sort(directories.begin(), directories.end());
          selected_index = 0;
        }
        break;
      case 10: // Enter key
        if (!directories.empty()) {
          std::string selected_dir = directories[selected_index];
          if (current_path.back() != '/')
            current_path += '/';
          selected_path = current_path + selected_dir;
          done = true;
        }
        break;
      case 27: // Escape key
        done = true;
        break;
    }

    // Update directories if needed
    if (ch == KEY_UP || ch == KEY_DOWN) {
      directories = ListDirectories(current_path);
      std::sort(directories.begin(), directories.end());
      selected_index = std::min(selected_index, static_cast<int>(directories.size()) - 1);
    }
  }

  // Cleanup
  delwin(win);
  endwin();
}

std::string GetCurrentWorkingDirectory() {
  char buffer[PATH_MAX]{};
  if (getcwd(buffer, sizeof(buffer)) != nullptr) {
    return std::string(buffer);
  } else {
    // Handle error
    return "";
  }
}