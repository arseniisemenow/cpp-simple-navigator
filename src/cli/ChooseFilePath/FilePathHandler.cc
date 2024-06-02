#include "FilePathHandler.h"

#include <__filesystem/recursive_directory_iterator.h>
#include <dirent.h>
#include <ncurses.h>
#include <unistd.h>

#include <algorithm>
#include <string>
#include <vector>

#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

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

  WINDOW *win = newwin(row - 4, col - 4, 2, 2);
  box(win, 0, 0);
  mvwprintw(win, 0, 2, "Select a directory");
  wrefresh(win);

  mvprintw(row - 2, 0, "Use arrow keys to navigate, press Enter to select, and Esc to cancel.");

  mvprintw(row - 1, 0, "Current path: %s", selected_path.c_str());
  refresh();

  std::string current_path = selected_path;
  std::vector<std::string> directories = ListDirectories(current_path);
  std::sort(directories.begin(), directories.end());

  int selected_index = 0;
  int ch;
  bool done = false;
  while (!done) {
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
        break;           case KEY_LEFT:
      {
        size_t pos = current_path.find_last_of('/');
        if (pos != std::string::npos) {
          current_path = current_path.substr(0, pos);
          directories = ListDirectories(current_path);
          std::sort(directories.begin(), directories.end());
          selected_index = 0;
        }
      }
        break;
      case KEY_RIGHT:
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
      case 10:
        if (!directories.empty()) {
          std::string selected_dir = directories[selected_index];
          if (current_path.back() != '/')
            current_path += '/';
          selected_path = current_path + selected_dir;
          done = true;
        }
        break;
      case 27:
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



void FindDatasetDirectoryRecursive(const fs::path& dir, int current_depth, int max_depth, std::string& dataset_directory, std::unordered_map<std::string, int>& txt_file_count) {
    if (current_depth > max_depth) return;

    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.is_directory()) {
            FindDatasetDirectoryRecursive(entry.path(), current_depth + 1, max_depth, dataset_directory, txt_file_count);
        } else if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            auto parent_path = entry.path().parent_path().string();
            txt_file_count[parent_path]++;

            if (entry.path().filename().string().find("graph") != std::string::npos) {
                dataset_directory = parent_path;
            }
        }
    }
}

std::string FindDatasetDirectory(const std::string& path, int max_depth) {
    std::unordered_map<std::string, int> txt_file_count;
    std::string dataset_directory;
    FindDatasetDirectoryRecursive(path, 0, max_depth, dataset_directory, txt_file_count);

    if (dataset_directory.empty()) {
        int max_txt_files = 0;
        for (const auto& [dir, count] : txt_file_count) {
            if (count > max_txt_files) {
                max_txt_files = count;
                dataset_directory = dir;
            }
        }
    }

    return dataset_directory;
}