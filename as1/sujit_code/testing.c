#include "../../Downloads/assign1(2)/a1_starter_tests.h"
#include "a1.c"

TestResults* test_menu(){
    TestResults* test_results_all = malloc(sizeof(TestResults));
    test_results_all->mistakes = 0;
    test_results_all->correct = 0;

    Menu* menu = load_menu(MENU_FNAME);

    return test_results_all;
}

int main(){
    run_tests("MENU TESTER SMALL", &test_menu);
}