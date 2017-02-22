#include "Parser.h"

#include "../machine/Machine.h"

#include <climits>

Parser::Parser(Machine& machine)
        : machine(machine) {
}

enum STR2INT_ERROR { SUCCESS, OVERFLOW, UNDERFLOW, INCONVERTIBLE };

STR2INT_ERROR str2int(int& i, char const* s, int base = 0) {
    char* end;
    long l;
    errno = 0;
    l = strtol(s, &end, base);
    if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) {
        return OVERFLOW;
    }
    if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) {
        return UNDERFLOW;
    }
    if (*s == '\0' || *end != '\0') {
        return INCONVERTIBLE;
    }
    i = l;
    return SUCCESS;
}

bool contains(const char c, const char* s) {
    for (const char* t = s; *t; t++) {
        if (c == *t) {
            return true;
        }
    }
    return false;
}

const char* next(const char* input, bool b, const char* s) {
    for (; *input; input++) {
        char c = *input;
        if (contains(c, s) != b) return input;
    }
    return input;
}

std::vector<std::string> splitInverse(const char* input, const char* s) {
    std::vector<std::string> r;
    bool t = !contains(*input, s);
    for (;;) {
        const char* start = input;
        const char* end = next(input, !t, s);
        if (start == end) break;
        if (!t) r.emplace_back(start, end - start);
        t = !t;
        input = end;
    }
    return r;
}
std::vector<std::string> split(const char* input, const char* s) {
    std::vector<std::string> r;
    bool t = contains(*input, s);
    for (;;) {
        const char* start = input;
        const char* end = next(input, t, s);
        if (start == end) break;
        if (!t) r.emplace_back(start, end - start);
        t = !t;
        input = end;
    }
    return r;
}

struct Entry {
    char c;
    Data d;
};
Entry readData(const char* c) {
    char t = 'i';
    if (*c == 'r') {
        t = 'r';
        c++;
    }
    int v;
    Data dd;
    dd.i = 0;
    STR2INT_ERROR error = str2int(v, c);
    if (error == SUCCESS) {
        dd.i = v;
        return {t, dd};
    }
    return {'?', dd};
}

Instruction Parser::parseInstruction(const char* input) {
    std::vector<std::string> parts = splitInverse(input, "-_abcdefghijklmnopqrstuvwxyz0123456789");
    unsigned int size = parts.size();
    if (size == 0) return Instruction(-1);

    //read data
    Entry d[3];
    int tIndex = 0;
    int sIndex = 1;
    switch (size) {
        case 4:
            d[tIndex++] = readData(parts[sIndex++].c_str());
        case 3:
            d[tIndex++] = readData(parts[sIndex++].c_str());
        case 2:
            d[tIndex++] = readData(parts[sIndex].c_str());
            break;
        case 1:
            break;
        default:
            std::cout << "malformed instruction: " << input << std::endl;
    }
    //add postfix
    std::string op = parts[0];
    op += '_';
    for (int i = 0; i < tIndex; i++) {
        op += d[i].c;
    }
    switch (size) {
        case 1:
            return machine.instruction(op.c_str());
        case 2:
            return machine.instruction(op.c_str(), d[0].d.i);
        case 3:
            return machine.instruction(op.c_str(), d[0].d.i, d[1].d.i);
        case 4:
            return machine.instruction(op.c_str(), d[0].d.i, d[1].d.i, d[2].d.i);
        default:
            return Instruction(-1);
    }
}

Program Parser::parseProgram(const char* input) {
    std::vector<Instruction> v;
    std::vector<std::string> lines = split(input, ";\n");
    for (auto& i : lines) {
        v.push_back(parseInstruction(i.c_str()));
    }
    return Program{v};
}
