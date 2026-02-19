/*
 * File:   main.c
 * Author: emertxe
 *
 * Created on 14 February, 2024, 5:40 PM
 */

#include<xc.h>
#include "clcd1.h"


char time[17] = "00:00:00";
unsigned short duty_cycle, program_cycle = 1, key, address = 0;
#include "timer.h"
State_t state;
void init_timer0();

void init_config() {
    init_clcd();
    init_matrix_keypad();


    init_adc();
    state = e_dashboard;

    // UART 
    init_uart();

    // i2c 
    init_i2c();

    // rtc
    init_ds1307();



}
char sec = 0;

void main(void) {
    init_config();



    while (1) {
alarm();
        key = read_switches(1);
        switch (state) {
            case e_dashboard:
                // Display dashboard
                view_dashboard();
                break;

            case e_main_menu:
                // Display dashboard
                display_main_menu();
                break;

            case e_view_log:
                // Display dashboard
                view_log();
                break;

            case e_download_log:
                // download_log();
                break;

            case e_clear_log:
                //clear_log();
                break;


            case e_set_time:
                set_time();
                break;

            case e_set_date:
                set_date();
                break;
                
            case e_set_event:
                set_event();
                break;
        }


    }

}








