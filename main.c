#include <stdio.h>
#include "WheelTimer.h"
#include "LinkedListApi.h"
#include <string.h>

#define WHEEL_SIZE 10
#define WHEEL_TIMER_CLOCK_TIC_INTERVAL 1

void
print_hello(char *S){ 
    printf("%s\n", S);
}

void wrapper_print_hello(void *arg, int arg_size){
    char *S = (char *)arg;
    print_hello(S);
}

int
main(int argc, char **argv){

    /*create a wheel timer object*/
    wheel_timer_t *wt = init_wheel_timer(WHEEL_SIZE, WHEEL_TIMER_CLOCK_TIC_INTERVAL);
    /*start the wheel timer thread*/
    start_wheel_timer(wt);

    wheel_timer_elem_t * wt_elem = 
        register_app_event(wt, wrapper_print_hello, "MyString", 
                           strlen("MyString"), 
                           5,  /*wrapper_print_hello fn will be called after every 5 seconds*/
                           1); /*1 indefinitely, 0 only once : call for wrapper_print_hello*/

    /*stop the main program from gettin terminated, otherwise wheel timer
     * thread we created will also get terminated*/
    scanf("\n");
    return 0;
}
