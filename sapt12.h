#pragma once
// jur ca e atat de tampit clion la indentare pe .h
// ca mai am putin si o scriu in notepad

// #define NDEBUG

#ifdef NDEBUG
    #define LINE ((void)0)
#else
    // ahfhahfahfaheafh nu cred ca era asta deja predefinit
    #define LINE printf("@%d\n", __LINE__)
#endif