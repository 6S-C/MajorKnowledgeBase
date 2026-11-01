#pragma once
#include <string>
#include <utility>

// Replace non-overlapping occurrences in the original S, from left to right.
// Do not rescan text inserted from V. T and V may alias S.
inline bool Replace(std::string& S, const std::string& T, const std::string& V) {
    if (T.empty()) return false;
    std::string result;
    std::size_t i = 0;
    while (i < S.size()) {
        if (T.size() <= S.size() - i && S.compare(i, T.size(), T) == 0) {
            result.append(V);
            i += T.size();
        } else {
            result.push_back(S[i]);
            ++i;
        }
    }
    S.swap(result);
    return true;
}

inline void reverseRange(std::string& S, std::size_t left, std::size_t right) {
    if (left >= right) return;
    std::swap(S[left], S[right]);
    reverseRange(S, left + 1, right - 1);
}

inline void reverseRecursive(std::string& S) {
    if (!S.empty()) reverseRange(S, 0, S.size() - 1);
}

inline void reverseIterative(std::string& S) {
    std::size_t left = 0, end = S.size();
    while (left < end) {
        --end;
        if (left >= end) break;
        std::swap(S[left], S[end]);
        ++left;
    }
}
