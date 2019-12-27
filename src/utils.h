#ifndef UTILS_H
#define UTILS_H

#define UTILS_DEBUG_LINE UTILS_DEBUG_LINE_(__LINE__)
#define UTILS_DEBUG_LINE_(line) UTILS_DEBUG_LINE__(line)
#define UTILS_DEBUG_LINE__(line) __FILE__":"#line

#endif // UTILS_H
