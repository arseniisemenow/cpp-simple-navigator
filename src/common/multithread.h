#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <mutex>

namespace s21::multithread {
inline int progress_1 = 0;
inline int progress_2 = 0;
inline std::mutex mutex_1{};
inline std::mutex mutex_2{};
inline std::atomic<bool> stop_thread_1(false);
inline std::atomic<bool> stop_thread_2(false);
inline std::atomic<bool> calculate_thread_1(false);
inline std::atomic<bool> calculate_thread_2(false);
}// namespace s21::multithread

#endif//CONSTANTS_H
