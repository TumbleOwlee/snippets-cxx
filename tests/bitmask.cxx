#include "bitmask.hxx"
#include <cassert>

int main(int, char **) {
    snippets::bitmask<8> bitmask;
    // Set bit 1 to on
    bitmask.set<1>();
    // Set bits 1, 2, 3 to on
    bitmask.set<1, 2, 3>();
    // Set bit 1 to off
    bitmask.unset<1>();
    // Set bits 1, 2, 3 to off
    bitmask.unset<1, 2, 3>();
    // Check if bit 1 is set to on
    bitmask.is_set<1>();
    // Check if bits 1, 2, 3 are set to on
    bitmask.is_set<1, 2, 3>();
    // Check if any of bits 1, 2, 3 is set to on
    bitmask.is_any<1, 2, 3>();
    // Check if bits 1, 2, 3 are set to off
    bitmask.is_none<1, 2, 3>();
    return 0;
}