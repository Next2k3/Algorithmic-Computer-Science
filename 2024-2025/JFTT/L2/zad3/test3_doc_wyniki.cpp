
/**
 * header-name
 */
//! Handling of `//`, `/*`, `*/` is implementation and platform dependent
//! #include <never/*comment*/>
//! #include "never/*comment*/"
#include <not//comment>
#include "not//comment"



//! Comments within `<>` get removed outside #include, but paths with a space are handled
//! platform specific (Windows includes properly, MacOS doesn't)
#include <iostream>


 int q;


/// TEST MACRO
#define TEST 1
/*! Important function */
int f(){return 42;}

/**
 * Documentation
 */
int main(void) {
        std::cout << TEST << "\n";

    printf("/* foo bar");
    
        std::cout << "/* is great */"
        << " and so is //"\
    "\n";

        std::cout << ":o"
        "a\n";

        std::cout << f()  << "\n";
}

