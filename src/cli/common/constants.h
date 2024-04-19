#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <mutex>

namespace s21::multithread {
inline int progress1 = 0;
inline int progress2 = 0;
inline std::mutex mtx_1;
inline std::mutex mtx_2;
inline std::atomic<bool> stop_thread(false);
inline std::atomic<bool> calculate(false);
}// namespace s21::multithread

#endif//CONSTANTS_H
