#include "chapter4_reference.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>

std::string expectedReplace(const std::string& s, const std::string& t,
                            const std::string& v) {
    if (t.empty()) return s;
    std::string out;
    std::size_t cursor = 0, found;
    while ((found = s.find(t, cursor)) != std::string::npos) {
        out += s.substr(cursor, found - cursor);
        out += v;
        cursor = found + t.size();
    }
    return out + s.substr(cursor);
}

int main() {
    std::mt19937 rng(20261101);
    auto randomString = [&](unsigned bound) {
        std::string s;
        unsigned n = rng() % bound;
        while (n--) s += "ab c"[rng() % 4];
        return s;
    };
    for (int i = 0; i < 5000; ++i) {
        const std::string source = randomString(65), t = randomString(10),
                          v = randomString(15);
        std::string s = source;
        bool ok = Replace(s, t, v);
        assert(ok == !t.empty());
        assert(s == expectedReplace(source, t, v));
        std::string a = source, b = source, expected = source;
        std::reverse(expected.begin(), expected.end());
        reverseRecursive(a); reverseIterative(b);
        assert(a == expected && b == expected);
    }
    std::string s = "I AM A STUDENT";
    assert(Replace(s, "STUDENT", "WORKER") && s == "I AM A WORKER");
    s = "aaaaa";
    assert(Replace(s, "aa", "b") && s == "bba");
    s = "abc";
    assert(Replace(s, s, "x") && s == "x");
    s = "aba";
    assert(Replace(s, "a", s) && s == "abababa");
    s = "abc";
    assert(!Replace(s, "", "x") && s == "abc");
    s = "aa";
    assert(Replace(s, "a", "aa") && s == "aaaa");
    s = "abab";
    assert(Replace(s, "ab", "") && s.empty());
    s = "abcsxw"; reverseRecursive(s); assert(s == "wxscba");
    s = std::string("a\0b", 3);
    assert(Replace(s, std::string("\0", 1), "X") && s == "aXb");
    std::cout << "PASS: 5000 randomized replacement/reversal cases and boundary/alias cases\n";
}
