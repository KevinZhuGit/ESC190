#include "a1.h"

Restaurant *initialize_restaurant(char *name)
{
    // intialize restaurant
    Restaurant *restaurant;
    restaurant = (Restaurant *)malloc(sizeof(Restaurant));

    // initialize name
    restaurant->name = name;

    // initialize menu
    restaurant->menu = load_menu(MENU_FNAME);

    // set orders to 0
    restaurant->num_completed_orders = 0;
    restaurant->num_pending_orders = 0;

    // initialize empty queue
    Queue *queue;
    queue = (Queue *)malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    restaurant->pending_orders = queue;

    return restaurant;
}

Menu *load_menu(char *fname)
{
    FILE *fp = fopen(fname, "a+");
    int linesize = ITEM_CODE_LENGTH + MAX_ITEM_NAME_LENGTH + 20;
    char str[linesize];

    // get # lines, counts for blank lines in the back
    int linecount = 1;
    char ch;
    char prev = '\n';

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n' && ch != prev)
        {
            linecount++;
        }

        prev = ch;
    }

    if (prev == '\n')
    {
        linecount--;
    }

    // initialize menu struct
    // initialize dynamic arrays of item_codes, item_names
    Menu *menu = (Menu *)malloc(sizeof(Menu));
    menu->num_items = linecount;
    menu->item_codes = (char **)malloc(sizeof(char *) * linecount);
    menu->item_names = (char **)malloc(sizeof(char *) * linecount);
    menu->item_cost_per_unit = (double *)malloc(sizeof(double) * linecount);

    // appends to dynamic arrays
    int index = 0;
    char delim = MENU_DELIM[0];
    rewind(fp);

    while ((fgets(str, linesize, fp) != NULL) && (index < linecount))
    {
        // break the string into pieces to be used, will have many extra things not necessary since size is extra

        char *temp_item_code = malloc(sizeof(char) * ITEM_CODE_LENGTH);
        char *temp_item_name = malloc(sizeof(char) * MAX_ITEM_NAME_LENGTH);
        char temp_price[10] = {0}; // why does this need to be reset
        int len = strlen(str);
        int delimcount = 0;
        int str_index = 0;

        for (int i = 0; i < len; i++)
        {
            if (str[i] == delim)
            {
                if (delimcount == 0)
                {
                    temp_item_code[str_index] = '\0';
                }
                else
                {
                    temp_item_name[str_index] = '\0';
                }

                delimcount++;
                str_index = 0;
            }
            else if (str[i] != ' ' && delimcount == 0)
            {
                temp_item_code[str_index] = str[i];
                str_index++;
            }
            else if (delimcount == 1)
            {
                temp_item_name[str_index] = str[i];
                str_index++;
            }
            else if (str[i] != '$' && str[i] != '\n' && str[i] != ' ' && delimcount == 2) // also != ' '
            {
                temp_price[str_index] = str[i];
                str_index++;
            }
        }

        // assign strings to array
        *(menu->item_codes + index) = temp_item_code;
        *(menu->item_names + index) = temp_item_name;

        // assign price
        double val = atof(temp_price);
        *(menu->item_cost_per_unit + index) = val;

        index++;
    }

    fclose(fp);

    return menu;
}

Order *build_order(char *items, char *quantities)
{
    int size = strlen(items) / (ITEM_CODE_LENGTH - 1);

    Order *order = (Order *)malloc(sizeof(Order));
    order->item_codes = (char **)malloc(sizeof(char *) * size);
    order->item_quantities = (int *)malloc(sizeof(int) * size);
    order->num_items = size;

    // add quantities to item code
    char delim = MENU_DELIM[0];
    int items_index = 0;      // tracks index of items
    int quantities_index = 0; // tracks index in quantities

    for (int i = 0; i < size; i++)
    {
        char *temp_codes = (char *)malloc(sizeof(char) * (ITEM_CODE_LENGTH));
        char temp_quantities[MAX_ITEM_QUANTITY_DIGITS + 1] = {0};

        for (int j = 0; j < (ITEM_CODE_LENGTH - 1); j++)
        {
            temp_codes[j] = items[items_index + j];
        }

        int arr_index = 0;

        while (quantities[quantities_index] != delim && quantities[quantities_index] != '\0') // neither can be false
        {
            temp_quantities[arr_index] = quantities[quantities_index];
            arr_index++;
            quantities_index++;
        }

        temp_codes[ITEM_CODE_LENGTH - 1] = '\0';
        items_index += (ITEM_CODE_LENGTH - 1);
        *(order->item_codes + i) = temp_codes;

        temp_quantities[arr_index] = '\0';
        double val = atof(temp_quantities);
        *(order->item_quantities + i) = val;
        quantities_index++;
    }

    return order;
}

void enqueue_order(Order *order, Restaurant *restaurant)
{
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    node->order = order;
    node->next = NULL;

    if (restaurant->pending_orders->head == NULL)
    {
        restaurant->pending_orders->head = node;
        restaurant->pending_orders->tail = node;
    }
    else
    {
        restaurant->pending_orders->tail->next = node;
        restaurant->pending_orders->tail = node;
    }

    restaurant->num_pending_orders++;
}

Order *dequeue_order(Restaurant *restaurant)
{
    // do book keeping on head and tail, and nexts where necessary
    // CASE ONLY ONE, HAVE TO CHANGE TAIL

    QueueNode *prev_head = restaurant->pending_orders->head;
    Order *order = restaurant->pending_orders->head->order;
    restaurant->pending_orders->head = restaurant->pending_orders->head->next;

    if (restaurant->pending_orders->head->next == NULL)
    {
        restaurant->pending_orders->tail = NULL;
    }

    // free Queue node
    free(prev_head);

    // update values
    restaurant->num_completed_orders++;
    restaurant->num_pending_orders--;

    return order;
}

double get_item_cost(char *item_code, Menu *menu)
{
    int i;

    for (i = 0; i < menu->num_items; i++)
    {

        if (strcmp(item_code, (menu->item_codes)[i]) == 0)
        {
            break;
        }
    }

    double price = (menu->item_cost_per_unit)[i];
    price = (int)(price * 100 + 0.5);
    return price / 100;
}

double get_order_subtotal(Order *order, Menu *menu)
{
    double total = 0;

    for (int i = 0; i < order->num_items; i++)
    {
        char order_code[MAX_ITEM_NAME_LENGTH];
        strcpy(order_code, (order->item_codes)[i]);
        double price = get_item_cost(order_code, menu);

        total += price * (order->item_quantities)[i];
    }

    return total;
}

double get_order_total(Order *order, Menu *menu)
{
    double price = get_order_subtotal(order, menu);
    double tax = TAX_RATE;

    return price * (1 + tax / 100);
}

int get_num_completed_orders(Restaurant *restaurant)
{
    return restaurant->num_completed_orders;
}

int get_num_pending_orders(Restaurant *restaurant)
{
    return restaurant->num_pending_orders;
}

void clear_order(Order **order)
{
    for (int i = 0; i < (*order)->num_items; i++)
    {
        free(((*order)->item_codes)[i]);
    }

    free((*order)->item_quantities);
    free((*order)->item_codes);
    free(*order);
    *order = NULL;
}

void clear_menu(Menu **menu)
{
    for (int i = 0; i < (*menu)->num_items; i++)
    {
        free(((*menu)->item_codes)[i]);
        free(((*menu)->item_names)[i]);
    }

    free((*menu)->item_codes);
    free((*menu)->item_names);
    free((*menu)->item_cost_per_unit);
    free(*menu);
    *menu = NULL;
}

void close_restaurant(Restaurant **restaurant)
{
    clear_menu(&((*restaurant)->menu));

    while ((*restaurant)->pending_orders->head != NULL)
    {
        Order *order = dequeue_order(*restaurant);
        clear_order(&order);
    }

    free((*restaurant)->pending_orders);
    free(*restaurant);
    *restaurant = NULL;
}

void print_menu(Menu *menu)
{
    fprintf(stdout, "--- Menu ---\n");
    for (int i = 0; i < menu->num_items; i++)
    {
        fprintf(stdout, "(%s) %s: %.2f\n",
                menu->item_codes[i],
                menu->item_names[i],
                menu->item_cost_per_unit[i]);
    }
}

void print_order(Order *order)
{
    for (int i = 0; i < order->num_items; i++)
    {
        fprintf(
            stdout,
            "%d x (%s)\n",
            order->item_quantities[i],
            order->item_codes[i]);
    }
}

void print_receipt(Order *order, Menu *menu)
{
    for (int i = 0; i < order->num_items; i++)
    {
        double item_cost = get_item_cost(order->item_codes[i], menu);
        fprintf(
            stdout,
            "%d x (%s)\n @$%.2f ea \t %.2f\n",
            order->item_quantities[i],
            order->item_codes[i],
            item_cost,
            item_cost * order->item_quantities[i]);
    }
    double order_subtotal = get_order_subtotal(order, menu);
    double order_total = get_order_total(order, menu);

    fprintf(stdout, "Subtotal: \t %.2f\n", order_subtotal);
    fprintf(stdout, "               -------\n");
    fprintf(stdout, "Tax %d%%: \t$%.2f\n", TAX_RATE, order_total);
    fprintf(stdout, "              ========\n");
}

int main()
{
    Menu *menu = load_menu(MENU_FNAME);

    printf("%d\n", menu->num_items);

    print_menu(menu);

    return 0;
}