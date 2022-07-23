#include "a1.h"

/**
    Add your functions to this file.
    Make sure to review a1.h.
    Do NOT include a main() function in this file
    when you submit.
*/

char *convert_string(char *str)
{
    int size = strlen(str);

    char *temp = (char *)malloc(sizeof(char) * (size + 1));

    for (int i = 0; i < (size); i++)
    {
        temp[i] = str[i];
    }

    *(temp + size) = '\0';

    return temp;
}

Restaurant *initialize_restaurant(char *name)
{
    Restaurant *ptr = (Restaurant *)malloc(sizeof(Restaurant));
    ptr->name = convert_string(name);
    ptr->num_completed_orders = 0;
    ptr->num_pending_orders = 0;
    ptr->menu = load_menu("menu.txt");
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    ptr->pending_orders = queue;
    ptr->pending_orders->head = NULL;
    ptr->pending_orders->tail = NULL;

    return ptr;
}

Menu *load_menu(char *fname)
{
    // reading file

    FILE *fp = fopen("menu.txt", "r");
    char *line = NULL;
    size_t line_len = 0;

    Menu *menu = (Menu *)malloc(sizeof(Menu));

    // count number of items in menu
    menu->num_items = 0;
    while (getline(&line, &line_len, fp) != -1)
    {
        menu->num_items++;
    }

    // allocate memory for item_name and item_codes
    menu->item_codes = (char **)malloc(sizeof(char *) * menu->num_items);
    menu->item_names = (char **)malloc(sizeof(char *) * menu->num_items);
    menu->item_cost_per_unit = (double *)malloc(sizeof(double) * menu->num_items);

    // we need to allocate memory for each char*
    free(line);
    fclose(fp); // closes file

    char *aline = NULL;
    line_len = 0;
    FILE *fptr = fopen("menu.txt", "r");
    int counter2 = 0;
    while (getline(&aline, &line_len, fptr) != -1)
    {
        // we need to allocate memory for each string
        int counter = 0;
        char *code = (char *)malloc(sizeof(char) * ITEM_CODE_LENGTH);
        char *name = (char *)malloc(sizeof(char) * MAX_ITEM_NAME_LENGTH);

        counter = 0;
        int code_ind = 0;
        int name_ind = 0;
        int cost_int = 0;
        // loop through each character until we hit ","
        while (aline[counter] != MENU_DELIM[0])
        {
            code[code_ind] = aline[counter];
            code_ind++;
            counter++;
        }
        counter++;
        // loop through each character until we hit ","
        while (aline[counter] != MENU_DELIM[0])
        {
            name[name_ind] = aline[counter];
            name_ind++;
            counter++;
        }
        counter += 2; // double skip because we need to account for "$"
        int price_count = 0;
        char store[10];
        while (aline[counter] != '\0')
        { // create string by appending characters to store
            store[price_count] = aline[counter];
            price_count++;
            counter++;
        }
        double double_eq = atof(store); // convert the string to a double

        code[ITEM_CODE_LENGTH - 1] = '\0';
        name[code_ind] = '\0';

        menu->item_codes[counter2] = code;
        menu->item_names[counter2] = name;
        menu->item_cost_per_unit[counter2] = double_eq;
        counter2++;
    }
    free(aline);
    fclose(fptr);
    return menu;
}

// Order* build_order(char* items, char* quantities) {
//     //allocate memory for order
//     Order* order = (Order*)malloc(sizeof(Order));
//     //find number of items in input
//     int count_comma = 1;
//     //count max number of char in quantities
//     int i = 0;
//     while (quantities[i] != "\0") {
//         if (quantities[i] == MENU_DELIM[0]) {
//             count_comma++;
//         }
//         i++;
//     }
//     order->num_items = count_comma;
//     order->item_codes = (char**)malloc(sizeof(char*) * order->num_items);
//     order->item_quantities = (char**)malloc(sizeof(char*) * order->item_quantities);
//
//     //allocate memory for code
//     int counter = 0;
//     int ind = 0;
//     int num_char = 0;
//     while (items[counter] != '\0'){
//         //checks if the counter is at an even number
//         char* code  = (char*)malloc(sizeof(char) * (ITEM_CODE_LENGTH-1)); //alloc memory for code
//         code[ind] = items[counter];
//         code[ind+1] = items[counter+1];
//         order->item_codes[num_char] = code ;
//         num_char++;
//         ind = 0;
//         counter+=2; //skips over by 2 so we can alloc memory again for string
//     }
//     counter = 0;
//
//     int* item_quantities = (int*)malloc(sizeof(int) * MAX_ITEM_QUANTITY_DIGITS);
//     char* portion = strtok(quantities, MENU_DELIM[0]); //strtok takes in a string and delim and returns
//     //a token which is a pointer to string
//     while(portion != NULL) { // this allows us to loop through all tokens (lowkey dont understand how it works lol)
//             item_quantities[counter] = atoi(portion);
//             counter++;
//             portion = strtok(NULL, MENU_DELIM[0]);
//         }
//         order->item_quantities = item_quantities;
//     }
//
///*
//	Managing our order queue
//*/
// void enqueue_order(Order* order, Restaurant* restaurant) {
//    QueueNode* queueNode = (QueueNode*)malloc(sizeof(QueueNode)); //alloc memory
//    queueNode->order = order;
//    queueNode->next = NULL; // since we are enqueing at the back, next will be set to NULL
//    Queue* queue = (Queue*)malloc(sizeof(Queue)); // alloc memory for queue
//    if (queue->head == NULL){ //if our queue is empty
//        queue->head = queueNode;
//        queue->tail = queueNode;
//    }
//    else {
//        queue->tail = queueNode;
//    }
//    restaurant->pending_orders = queue;
//    restaurant->num_pending_orders++; //adjusting number of pending orders
//}
//
// Order* dequeue_order(Restaurant* restaurant) {
//    if (restaurant->pending_orders->head == NULL) {
//        printf("Queue is empty");
//    }
//    else if (restaurant->pending_orders->head = restaurant->pending_orders->tail) {
//        restaurant->pending_orders->head = NULL;
//        restaurant->pending_orders->tail = NULL;
//    }
//    else {
//        QueueNode* q = restaurant->pending_orders->head;
//        restaurant->pending_orders->head = q->next;
//        free(q);
//    }
//}
///*
//	Getting information about our orders and order status
//*/
// double get_item_cost(char* item_code, Menu* menu) {
//    int counter = 0;
//    while (menu->item_codes[counter] != '\0') {
//        if (menu->item_codes[counter] == item_code) {
//            break;
//        }
//        else {
//            counter++;
//        }
//    }
//    return menu->item_cost_per_unit[counter];
//
//}
//
// double get_order_subtotal(Order* order, Menu* menu) {
//    double* array_of_ind = (double*)malloc(sizeof(double) * order->num_items); //allocate memory for an array to store
//    //the prices of items before accounting for number of items
//    for(int counter = 0; counter < order->num_items; counter++) { //loop through order codes
//        for (int counter2 = 0; counter < menu->num_items; counter2++) { //loop through menu items
//            if (order->item_codes[counter] == menu->item_codes[counter2]) { //find when order code matches menu code
//                array_of_ind[counter] = menu->item_cost_per_unit[counter2]; //add the price associated with code to
//                //array_of_ind
//            }
//        }
//    }
//    double subtotal = 0; //initialize subtotal
//    for (int i = 0; i < order->num_items; i++) {
//        array_of_ind[i] = array_of_ind[i] * order->item_quantities[i]; //this will account for item quantities
//        subtotal += array_of_ind[i]; //adds each element to subtotal
//    }
//    return subtotal;
//}
//
// double get_order_total(Order* order, Menu* menu) {
//    double subtotal = get_order_subtotal(order, menu); //find subtotal
//    double order_total = subtotal + (subtotal * TAX_RATE); //applying tax rate
//    return order_total;
//}
// int get_num_completed_orders(Restaurant* restaurant);
// int get_num_pending_orders(Restaurant* restaurant);
//
///*
//	Closing down and deallocating memory
//*/
// void clear_order(Order** order);
// void clear_menu(Menu** menu);
// void close_restaurant(Restaurant** restaurant);
//
///*
//	These functions are implemented for you in
//	restaurant.c
//*/
// void print_menu(Menu* menu);
// void print_order(Order* order);
// void print_receipt(Order* order, Menu* menu);
//
///* ------- End of header file -------*/
//
// void print_menu(Menu* menu){
//	fprintf(stdout, "--- Menu ---\n");
//	for (int i = 0; i < menu->num_items; i++){
//		fprintf(stdout, "(%s) %s: %.2f\n",
//			menu->item_codes[i],
//			menu->item_names[i],
//			menu->item_cost_per_unit[i]
//		);
//	}
//}
//
// void print_order(Order* order){
//	for (int i = 0; i < order->num_items; i++){
//		fprintf(
//			stdout,
//			"%d x (%s)\n",
//			order->item_quantities[i],
//			order->item_codes[i]
//		);
//	}
//}

// void print_receipt(Order* order, Menu* menu){
//	for (int i = 0; i < order->num_items; i++){
//		double item_cost = get_item_cost(order->item_codes[i], menu);
//		fprintf(
//			stdout,
//			"%d x (%s)\n @$%.2f ea \t %.2f\n",
//			order->item_quantities[i],
//			order->item_codes[i],
//			item_cost,
//			item_cost * order->item_quantities[i]
//		);
//	}
//	double order_subtotal = get_order_subtotal(order, menu);
//	double order_total = get_order_total(order, menu);
//
//	fprintf(stdout, "Subtotal: \t %.2f\n", order_subtotal);
//	fprintf(stdout, "               -------\n");
//	fprintf(stdout, "Tax %.2f%%: \t$%.2f\n", TAX_RATE, order_total);
//	fprintf(stdout, "              ========\n");
//  }