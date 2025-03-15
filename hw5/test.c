#include "test.h"

Test createTest(Breed* types, End* ends, int* data, char* expected, int count) {
    Test test = malloc(sizeof(struct Test));
    test->count = count;
    test->expected = expected;
    test->steps = malloc(sizeof(struct TestStep) * count);

    for (int i = 0; i < count; i++) {
        TestStep step = malloc(sizeof(struct TestStep));
        step->type = types[i];
        step->end = ends[i];
        step->data = malloc(sizeof(int));
        *step->data = data[i];

        test->steps[i] = step;
    }

    return test;
}


//string representaion of int
char *printInt(Data d) {
    int value = *((int*) d);
    int len = snprintf(NULL, 0, "%d", value);
    char *str = malloc(len + 1);
    snprintf(str, len + 1, "%d", value);

    return str;
}


//head is equal to the expected head
bool headCheck(char actual, char expected)  {

    if (actual == expected) {
        printf("%s", "Head check passed\n");
        return true;
    }
    fprintf(stderr, "%s%c%s%c%s", "Actual head ", actual, "is not equal to expected", expected, "\n");
    return false;
}

//tail is equal to the expected tail
bool tailCheck(char actual, char expected)  {
    if (actual == expected) {
        printf("%s", "Tail check passed\n");
        return true;
    }
    fprintf(stderr, "%s%c%s%c", "Actual tail ", actual, "is not equal to expected\n", expected);
    return false;
}

//run test off structure
bool run(Test test) {
    Deq d = deq_new();

    for (int i = 0; i < test->count; i++) {
        TestStep step = test->steps[i];
        Data data = step->data;
        End end = step->end;
        Breed type = step->type;

        if (type == PUT) {
            if (end == Head) {
                deq_head_put(d, data);
            } else {
                deq_tail_put(d, data);
            }
        } else if (type == ITH) {
            if (end == Head) {
                deq_head_ith(d, 0);
            } else {
                deq_tail_ith(d, -1);
            }
        } else if (type == GET) {
            if (end == Head) {
                deq_head_get(d);
            } else {
                deq_tail_get(d);
            }
        } else if (type == REM) {
            if (end == Head) {
                deq_head_rem(d, d);
            } else {
                deq_tail_rem(d, d);
            }
        }
    }

    char *actual = toString(d);
    bool result = comp(actual, test->expected);

    free(actual);
    destroyDEQ(d);

    return result;
}

//compare expected and actual result
bool comp(char *actual, char *expected) {
    if (strcmp(actual, expected) == 0)  {
        printf("%s", "String comparison passed\n");
        return true;
    }
    fprintf(stderr, "%s%s%s%s%s", "String comparison failed\n Actual:", actual, "\nExpected:", expected, "\n");
    return false;
}

//return val of function ran
void printReturn(char *function, Data d) {
    if (d == NULL)  {
        printf("%s%s", function, " Return data was null\n");
    } else  {
        char *returnVal = printInt(d);
        printf("%s%s%s%s", function, " Return value was: ", returnVal, "\n");
        free(returnVal);
    }
}


///TESTS!!!!
//HEAD
//adding a value to the head of an empty list
bool Put_AddToHeadEmptyList() {
    printf("%s", "\nRunning function : Put_AddToHeadEmptyList\n");
    Breed types[] = {PUT};
    End ends[] = {Head};
    int data[] = {5};
    char *expected = "[5]";

    Test test = createTest(types, ends, data, expected, 1);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//putting two items at the head of the list
bool Put_AddToHead2Item()   {
    printf("%s", "\nRunning function : Put_AddToHead2Item\n");
    int stepCount = 2;
    int data[] = {5, 6};
    char *expected = "6 5";

    Breed types[] = {PUT, PUT};
    End end[] = {Head, Head};

    Test test = createTest(types, end, data, expected, stepCount);
    return run(test);
}

//getting ith from head for empty list
bool Ith_Head_EmptyList()   {
    printf("%s", "\nRunning function : th_Head_EmptyList\n");
    Breed types[] = {PUT, PUT};
    End ends[] = {Head, Head};
    int data[] = {5, 10};
    char *expected = "[10, 5]";

    Test test = createTest(types, ends, data, expected, 2);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//getting ith from the head with only one item
bool Ith_Head_1Item()  {
    printf("%s", "\nRunning function : Ith_Head_1Item\n");
    Breed types[] = {PUT, ITH};
    End ends[] = {Head, Head};
    int data[] = {5};
    char *expected = "[5]";

    Test test = createTest(types, ends, data, expected, 2);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//getting an item from head of an empty list
bool Get_Head_EmptyList()  {
    printf("%s", "\nRunning function : Get_Head_EmptyList\n");
    Breed types[] = {GET};
    End ends[] = {Head};
    int data[] = {};
    char *expected = "[]";

    Test test = createTest(types, ends, data, expected, 1);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//getting an item from the head of a list with one item
bool Get_Head_1Item()   {
    printf("%s", "\nRunning function : Get_Head_1Item\n");
    Breed types[] = {PUT, GET};
    End ends[] = {Head, Head};
    int data[] = {5};
    char *expected = "[]";

    Test test = createTest(types, ends, data, expected, 2);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//removing from head with an empty list
bool Rem_Head_EmptyList()  {
    printf("%s", "\nRunning function : Rem_Head_EmptyList\n");
    Breed types[] = {REM};
    End ends[] = {Head};
    int data[] = {};
    char *expected = "[]";

    Test test = createTest(types, ends, data, expected, 1);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}


//removing item with one item in the list
bool Rem_Head_Add1()  {
    printf("%s", "\nRunning function : Rem_Head_Add1\n");
    Breed types[] = {PUT, REM};
    End ends[] = {Head, Head};
    int data[] = {5};
    char *expected = "[]";

    Test test = createTest(types, ends, data, expected, 2);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//TAIL
//adding an item to the tail of an empty list
bool Put_AddToTailEmptyList()  {
    printf("%s", "\nRunning function : Put_AddToTailEmptyList\n");
     Breed types[] = {PUT};
    End ends[] = {Tail};
    int data[] = {5};
    char *expected = "[5]";

    Test test = createTest(types, ends, data, expected, 1);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//putting two items at the tail of the empty list
bool Put_Add2Tail()    {
    printf("%s", "\nRunning function : Put_Add2Tail\n");
    Breed types[] = {PUT, PUT};
    End ends[] = {Tail, Tail};
    int data[] = {5, 7};
    char *expected = "[5,7]";

    Test test = createTest(types, ends, data, expected, 2);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//getting ith from the tail with an empty list
bool Ith_Tail_EmptyList()  {
    printf("%s", "\nRunning function : Ith_Tail_EmptyList\n");
    Breed types[] = {ITH};
    End ends[] = {Tail};
    int data[] = {0};
    char *expected = "[]";

    Test test = createTest(types, ends, data, expected, 1);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//getting ith from the tail with only one item
bool Ith_Tail_1Item()  {
    printf("%s", "\nRunning function : Ith_Tail_1Item\n");
    Breed types[] = {PUT, ITH};
    End ends[] = {Tail, Tail};
    int data[] = {5, 0};
    char *expected = "[5]";

    Test test = createTest(types, ends, data, expected, 2);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//getting an item from the tail of an empty list
bool Get_Tail_EmptyList()  {
    printf("%s", "\nRunning function : Get_Tail_EmptyList\n");
    Breed types[] = {GET};
    End ends[] = {Tail};
    int data[] = {0};
    char *expected = "[]";

    Test test = createTest(types, ends, data, expected, 1);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//getting an item from the tail of a list with one item
bool Get_Tail_1Item()   {
    printf("%s", "\nRunning function : Get_Tail_1Item\n");
    Breed types[] = {PUT, GET};
    End ends[] = {Tail, Tail};
    int data[] = {5, 0};
    char *expected = "[]";

    Test test = createTest(types, ends, data, expected, 2);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//removing from tail with an empty list
bool Rem_Tail_EmptyList()   {
    printf("%s", "\nRunning function : Test_rem_Tail_EmptyList\n");
   Breed types[] = {REM};
    End ends[] = {Tail};
    int data[] = {0};
    char *expected = "[]";

    Test test = createTest(types, ends, data, expected, 1);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//removing item starting search at tail with one item in list
bool Rem_Tail_Add1()    {
    printf("%s", "\nRunning function : Rem_Tail_Add1\n");
    Breed types[] = {PUT, REM};
    End ends[] = {Tail, Tail};
    int data[] = {5, 0};
    char *expected = "[]";

    Test test = createTest(types, ends, data, expected, 2);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//HEAD + TAIL

//adding two items to the head and then 1 to the tail
bool Put_Add2Head1Tail()    {
    printf("%s", "\nRunning function : Put_Add2Head1Tail\n");
    Breed types[] = {PUT, PUT, PUT};
    End ends[] = {Head, Head, Tail};
    int data[] = {5, 6, 7};
    char *expected = "[6, 5, 7]";

    Test test = createTest(types, ends, data, expected, 3);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//adding two the head, getting from tail and then putting at tail
bool Get_Add2Head2TailGetTail() {
    printf("%s", "\nRunning function : Get_Add2Head2TailGetTail\n");
    Breed types[] = {PUT, PUT, PUT, PUT, GET};
    End ends[] = {Head, Head, Tail, Tail, Tail};
    int data[] = {5, 6, 7, 8, 0};
    char *expected = "[5, 6, 7, 8]";

    Test test = createTest(types, ends, data, expected, 5);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//adding two items to tail getting from the head and adding to the head
bool Get_Add2Tail2HeadGetHead()    {
    printf("%s", "\nRunning function : Get_Add2Tail2HeadGetHead\n");
    Breed types[] = {PUT, PUT, PUT, PUT, GET};
    End ends[] = {Tail, Tail, Head, Head, Head};
    int data[] = {5, 6, 7, 8, 0};
    char *expected = "[8, 7, 6, 5]";

    Test test = createTest(types, ends, data, expected, 5);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//removing an item from the middle of a list with 4 elements and ensures pointers to the new middle object are accurate
bool Rem_GetHeadTail()  {
    printf("%s", "\nRunning function : Rem_GetHeadTail\n");
    Breed types[] = {PUT, PUT, PUT, PUT, REM, REM};
    End ends[] = {Head, Head, Tail, Tail, Head, Tail};
    int data[] = {5, 6, 7, 8, 0, 0};
    char *expected = "[6, 7]";

    Test test = createTest(types, ends, data, expected, 6);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}

//removing an item from the middle of a list with 4 elements and ensures pointers to the new middle object are accurate
bool Rem_GetTailHead()  {
    printf("%s", "\nRunning function : Rem_GetTailHead\n");
    Breed types[] = {PUT, PUT, PUT, PUT, REM, REM};
    End ends[] = {Head, Head, Tail, Tail, Tail, Head};
    int data[] = {5, 6, 7, 8, 0, 0};
    char *expected = "[6, 7]";

    Test test = createTest(types, ends, data, expected, 6);
    bool result = run(test);

    for (int i = 0; i < test->count; i++) {
        free(test->steps[i]->data);
        free(test->steps[i]);
    }

    free(test->steps);
    free(test);

    return result;
}