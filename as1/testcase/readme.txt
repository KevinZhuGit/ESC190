10% Hidden Test Cases: Test Flow
---------------------------------------------------------------

Note: Test descriptions prefaced with a "!!"
were tested using two test settings:

    (a) using **only code you submitted**
    (b) if (a) failed the test case, we re-tested your code
        by overwriting some functions with **our** (i.e. the
        correct) implementation.


0.8 load_menu(...)
    Load menu tested on additional menu files 
        - menu2_0.txt
        - menu3_0.txt
        - menu4_0.txt
        - menu5_0.txt
    
    Memory:         0.05 marks x 4 tests = 0.2
    Functionality:    0.15 marks x 4 tests = 0.6
    
    
0.4 build_order(...) 
    Build order tested on additional menu files indicated above
    Memory:           0.025 marks x 4 tests = 0.1
    Functionality:    0.075 marks x 4 tests = 0.3

    
0.1 get_order_subtotal(...) 
    get_order_total(...)
    get_item_cost(...)
    !! Menu reading functions for a single order using menu1.txt
    
    Functionality:    0.1 marks x 1 test = 0.1
    
    Functions replaced as per test setting (b):
        -load_menu(...)
        -clear_menu(...)
        -build_order(...)
        -clear_order(...)
        
        
8.7 enqueue(...) 
    dequeue(...)
    !! Testing the queue for sequences of enqueue/dequeue operations
    
    Memory:            0.27 marks x 10 tests = 2.7 
    Functionality:     0.6 marks x 10 tests = 6
    
    Functions replaced as per test setting (b):
        - load_menu(...)
        - clear_menu(...)
        - build_order(...)
        - clear_order(...)
        - initialize_restaurant(...)
        
    10 tests breakdown:
    
    Tests 0 and 1 have one order. Tests 2-9 have 5 orders.
    Enqueue is represented as ENQ, dequeue is represented as DQ,
    and close restaurant is represented as CR.
    
        Test 0) ENQ CR
        Test 1) ENQ DQ CR
        Test 2) ENQ ENQ ENQ ENQ ENQ CR
        Test 3) ENQ DQ ENQ DQ ENQ DQ ENQ DQ ENQ DQ CR
        Test 4) ENQ DQ ENQ ENQ DQ ENQ ENQ DQ DQ DQ CR
        Test 5) ENQ ENQ ENQ ENQ ENQ DQ DQ DQ DQ DQ CR
        Test 6) ENQ DQ ENQ ENQ DQ ENQ ENQ DQ CR
        Test 7) ENQ ENQ ENQ ENQ DQ ENQ DQ CR
        Test 8) ENQ DQ ENQ DQ ENQ DQ ENQ ENQ CR
        Test 9) ENQ DQ ENQ DQ ENQ DQ ENQ ENQ DQ CR
    
    Valgrind was assessed by success after CR, so this Valgrind
    test covers the functionality test for close_restaurant(...).
    Note that Valgrind tests were only run on test setting (a).

    Test "exact" vs test "partial"
        Anyone who passed the test "exact" test cases would
        also pass the corresponding test "partial" test cases.

        Non-Valgrind test partial test cases check for similarity
        between your output and the expected output. If the 
        similarity exceeds a threshold (which varies depending
        on the complexity of the test case), you pass the partial 
        test case. As the name suggests, the "exact" test case
        checks that you got the exact correct output with your code.

        Valgrind partial test cases offer part marks for memory 
        management if you managed to get the functionality partial
        test to pass.