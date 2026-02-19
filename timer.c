/*
 * File:   black_box.c
 * Author: User
 *
 * Created on 30 December, 2024, 3:44 PM
 */


#include <xc.h>
#include "clcd1.h"
#include "timer.h"
#include<string.h>

void day(int day);
void get_time(void);
void get_date(void);
unsigned char clock_reg[3];
unsigned char calender_reg[4], date[11];
void store(char *lap);
void sort();

char e_arr[10][8];
char str[10][17];

void alarm() {
    get_time();
    //RB0 = 1;

    static char hr, t_min, hr1, min1, ch;
    hr = (time[0] - '0') * 10;
    hr = (time[1] - '0') + hr;
    t_min = (time[3] - '0') * 10;
    t_min = (time[4] - '0') + t_min;

    int index = -1;
    for (int i = 0; i < address / 8; i++) {
        //  clcd_print("im in alarm", LINE2(1));

        hr1 = (e_arr[i][0] - '0') * 10 + (e_arr[i][1] - '0');
        min1 = (e_arr[i][2] - '0') * 10 + (e_arr[i][3] - '0');
        if (clock_reg[0] & 0x20)
            ch = 'P';
        else
            ch = 'A';
        if (ch == e_arr[i][4]) {
            if (hr == hr1 && t_min == min1){
                RB0 = 1;
//                if(e_arr[i][6] == 'O')
//                    index = i;
            }
            else
                RB0 = 0;
        }
        //            clcd_putch(min1%10 + '0', LINE2(1));
        //           clcd_putch(t_min%10 + '0', LINE2(3));
    }
//    if(index != -1){
//        for(int i = index; i < address / 8; i++){
//            e_arr[i] = e_arr[i+1];
//        }
//        address -= 8;
//        static int t_address;
//        t_address = address; address = 
//        for(int j = 0; j < t_address / 8; j++){
//            store(e_arr[j]);
//    }
    
}

void swap(char a[], char b[]) {
    char temp[100];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

void store(char *lap) {
    for (int i = 0; i < 8; i++) {
        ex_eeprom_write(address, lap[i]);
        address++;
    }
    //        address -= 8;
    //        for (int i = 0; i < 8; i++) {
    //            clcd_putch(ex_eeprom_read(address++), LINE1(i));
    //    
    //        }

}

void view_dashboard(void) {

    sec = time[7] - '0' + ((time[6] - '0') * 10);
    get_time();
    if (sec % 7 < 5) {
        clcd_print("TIME ", LINE2(0));
        clcd_print(time, LINE2(5));

        if (clock_reg[0] & 0x20) {
            clcd_print(" PM", LINE2(13));
        } else {
            clcd_print(" AM", LINE2(13));
        }

        get_date();

        clcd_print(date, LINE1(5));
        clcd_print("DATE ", LINE1(0));
        clcd_print("   ", LINE1(13));

    } else {
        clcd_print("TIME ", LINE1(0));
        clcd_print(time, LINE1(5));

        if (clock_reg[0] & 0x20) {
            clcd_print(" PM", LINE1(13));
        } else {
            clcd_print(" AM", LINE1(13));
        }
        if(address != 0){
            clcd_print("EVENT ", LINE2(0));
            clcd_putch(e_arr[0][0], LINE2(6));
             clcd_putch(e_arr[0][1], LINE2(7));
              clcd_putch(':', LINE2(8));
               clcd_putch(e_arr[0][2], LINE2(9));
                clcd_putch(e_arr[0][3], LINE2(10));
                clcd_putch(' ', LINE2(11));
                clcd_putch(e_arr[0][4], LINE2(12));
                 clcd_putch(e_arr[0][5], LINE2(13));
                 clcd_putch(' ', LINE2(14));
                  clcd_putch(e_arr[0][6], LINE2(15));
        }  
            else {
        clcd_print("EVENT ", LINE2(0));
        clcd_print("No event  ", LINE2(6));}
    }

    if (key == 4) {
        state = e_main_menu;
        clcd_print("                ", LINE1(0));
        clcd_print("                ", LINE2(0));
    }
}

void display_main_menu(void) {
    static int pt = 0, flag = 1, temp = 0;
    // clcd_print("                ", LINE1(0));
    //        clcd_print("                ", LINE2(0));
    if (flag) {
        clcd_print(" SET EVENT/VIEW ", LINE1(1));
        clcd_print(" SET TIME/DATE  ", LINE2(1));
    }
    if (temp == 1) {
        clcd_print("   SET EVENT    ", LINE1(1));
        clcd_print("   SET VIEW      ", LINE2(1));
        if (pt == 0 && key == 4) {
            clcd_print("                ", LINE1(0));
            clcd_print("                ", LINE2(0));
            clcd_print(" HH:MM AM/PM MODE", LINE1(0));
            state = e_set_event;
        } else if (pt == 1 && key == 4) {
            clcd_print("                ", LINE1(0));
            clcd_print("                ", LINE2(0));
            clcd_print(" HH:MM AM/PM MODE", LINE1(0));
            state = e_view_log;
        }

    } else if (temp == 2) {
        clcd_print("   SET TIME    ", LINE1(1));
        clcd_print("   SET DATE      ", LINE2(1));
        if (pt == 0 && key == 4) {
            clcd_print("                ", LINE1(0));
            clcd_print("                ", LINE2(0));
            state = e_set_time;
        } else if (pt == 1 && key == 4) {
            clcd_print("                 ", LINE1(0));
            clcd_print("                  ", LINE2(0));
            state = e_set_date;
        }
    }
    else if (key == 4 && pt == 0) {
        temp = 1;
        flag = 0;
    } else if (key == 4 && pt == 1) {
        temp = 2;
        flag = 0;
    }

    //    if (key == 5 && temp) {
    //        flag = 1;
    //        temp = 0;
    //        clcd_print("                ", LINE1(0));
    //        clcd_print("                ", LINE2(0));
    if (key == 5 && temp == 0 || key == 5 && temp) {
        flag = 1;
        temp = 0;
        clcd_print("                ", LINE1(0));
        clcd_print("                ", LINE2(0));
        state = e_dashboard;
    }


    if (key == 1) {
        pt = 0;
    } else if (key == 2) {
        pt = 1;
    }



    if (pt == 0) {
        clcd_putch('*', LINE1(0));
        clcd_putch(' ', LINE2(0));
    } else if (pt == 1) {
        clcd_putch(' ', LINE1(0));
        clcd_putch('*', LINE2(0));
    }

}


// setting time function 

void set_time(void) {
    static unsigned char t_min, t_sec, hr = 0, min = 0, blink = 1, i = 0, j = 0, flag = 0, PM = 0;

    sec = time[7] - '0' + ((time[6] - '0') * 10);
    get_time();
    clcd_print(" HH:MM:SS AM/PM ", LINE1(0));

    if (key == 2) {
        blink++;

    }
    static int x = 1;
    if (x == 1) {
        hr = (time[0] - '0') * 10;
        hr = (time[1] - '0') + hr;
        t_min = (time[3] - '0') * 10;
        t_min = (time[4] - '0') + t_min;
        t_sec = (time[6] - '0') * 10;
        t_sec = (time[7] - '0') + t_sec;
        x = 0;
    }

    if (blink % 4 == 1) {
        if (sec % 2 == 0) {
            clcd_putch(' ', LINE2(1));
            clcd_putch(' ', LINE2(2));
        } else {

            clcd_putch((hr / 10) + '0', LINE2(1));
            clcd_putch((hr % 10) + '0', LINE2(2));
        }
        clcd_putch(':', LINE2(3));
        clcd_putch((t_min / 10) + '0', LINE2(4));
        clcd_putch((t_min % 10) + '0', LINE2(5));
        clcd_putch(':', LINE2(6));
        clcd_putch((t_sec / 10) + '0', LINE2(7));
        clcd_putch((t_sec % 10) + '0', LINE2(8));
        if (clock_reg[0] & 0x20) {
            clcd_print(" PM", LINE2(10));
        } else {
            clcd_print(" AM", LINE2(10));
        }

    } else if (blink % 4 == 2) {
        if (sec % 2 == 0) {
            clcd_putch(' ', LINE2(4));
            clcd_putch(' ', LINE2(5));
        } else {
            clcd_putch((t_min / 10) + '0', LINE2(4));
            clcd_putch((t_min % 10) + '0', LINE2(5));
        }
        clcd_putch(':', LINE2(3));
        clcd_putch((hr / 10) + '0', LINE2(1));
        clcd_putch((hr % 10) + '0', LINE2(2));
        clcd_putch(':', LINE2(6));
        clcd_putch((t_sec / 10) + '0', LINE2(7));
        clcd_putch((t_sec % 10) + '0', LINE2(8));
        if (clock_reg[0] & 0x20) {
            clcd_print(" PM", LINE2(10));
        } else {
            clcd_print(" AM", LINE2(10));
        }

    } else if (blink % 4 == 3) {
        if (sec % 2 == 0) {
            clcd_putch(' ', LINE2(7));
            clcd_putch(' ', LINE2(8));
        } else {

            clcd_putch((t_sec / 10) + '0', LINE2(7));
            clcd_putch((t_sec % 10) + '0', LINE2(8));
        }
        clcd_putch(':', LINE2(3));
        clcd_putch((hr / 10) + '0', LINE2(1));
        clcd_putch((hr % 10) + '0', LINE2(2));
        clcd_putch(':', LINE2(6));
        clcd_putch((t_min / 10) + '0', LINE2(4));
        clcd_putch((t_min % 10) + '0', LINE2(5));
        if (clock_reg[0] & 0x20) {
            clcd_print(" PM", LINE2(10));
        } else {
            clcd_print(" AM", LINE2(10));
        }

    } else if (blink % 4 == 0) {

        if (PM) {
            if (sec % 2 == 0) {
                clcd_putch(' ', LINE2(10));
                clcd_putch(' ', LINE2(11));
                clcd_putch(' ', LINE2(12));
            } else
                clcd_print(" PM", LINE2(10));
        } else {
            if (sec % 2 == 0) {
                clcd_putch(' ', LINE2(10));
                clcd_putch(' ', LINE2(11));
                clcd_putch(' ', LINE2(12));
            } else
                clcd_print(" AM", LINE2(10));
        }
        clcd_putch((t_sec / 10) + '0', LINE2(7));
        clcd_putch((t_sec % 10) + '0', LINE2(8));

    }


    if (key == 1) {
        if (blink % 4 == 1 && hr < 12) {
            hr++;
        } else if (blink % 4 == 1 && hr >= 12) {
            hr = 1;
        }
        if (blink % 4 == 2 && t_min < 59)
            t_min++;
        else if (blink % 4 == 2 && t_min >= 59)
            t_min = 0;
        if (blink % 4 == 3 && t_sec < 59)
            t_sec++;
        else if (blink % 4 == 3 && t_sec >= 59)
            t_sec = 0;
        static char dummy;
        dummy = read_ds1307(HOUR_ADDR);
        if (blink % 4 == 0) {
            PM = !PM;
            if (PM == 1) {
                write_ds1307(HOUR_ADDR, dummy | (PM << 5));
            } else
                write_ds1307(HOUR_ADDR, dummy & 0xDF);
        }
    }

    if (key == 4) {
        write_ds1307(HOUR_ADDR, ((hr % 10) | ((hr / 10) << 4)) | PM << 5);
        write_ds1307(MIN_ADDR, ((t_min % 10) | ((t_min / 10) << 4)));
        write_ds1307(SEC_ADDR, ((t_sec % 10) | ((t_sec / 10) << 4)));
        goto L1;
    }

    if (key == 5) {
L1:
        blink = 1;
        x = 1;
        clcd_print("                ", LINE1(0));
        clcd_print("                ", LINE2(0));
        state = e_main_menu;
    }

}
char DAY = 1;

void set_date(void) {
    static char DD, MM, YY, blink = 1;
    sec = time[7] - '0' + ((time[6] - '0') * 10);
    get_time();
    clcd_putch(' ', LINE2(0));
    clcd_print(" DD-MM-YY DAY ", LINE1(0));

    if (key == 2) {
        blink++;
    }
    static int x = 1;
    if (x == 1) {
        YY = (date[6] - '0') * 10;
        YY = (date[7] - '0') + YY;
        MM = (date[3] - '0') * 10;
        MM = (date[4] - '0') + MM;
        DD = (date[0] - '0') * 10;
        DD = (date[1] - '0') + DD;

        DAY = (date[8] - '0') + 1;
        x = 0;
    }

    if (blink % 4 == 1) {
        if (sec % 2 == 0) {

            clcd_putch(' ', LINE2(1));
            clcd_putch(' ', LINE2(2));
        } else {

            clcd_putch((DD / 10) + '0', LINE2(1));
            clcd_putch((DD % 10) + '0', LINE2(2));
        }
        clcd_putch('-', LINE2(3));
        clcd_putch((MM / 10) + '0', LINE2(4));
        clcd_putch((MM % 10) + '0', LINE2(5));
        clcd_putch('-', LINE2(6));
        clcd_putch((YY / 10) + '0', LINE2(7));
        clcd_putch((YY % 10) + '0', LINE2(8));
        day(DAY);
    } else if (blink % 4 == 2) {
        if (sec % 2 == 0) {
            clcd_putch(' ', LINE2(4));
            clcd_putch(' ', LINE2(5));
        } else {
            clcd_putch((MM / 10) + '0', LINE2(4));
            clcd_putch((MM % 10) + '0', LINE2(5));
        }
        clcd_putch('-', LINE2(3));
        clcd_putch((DD / 10) + '0', LINE2(1));
        clcd_putch((DD % 10) + '0', LINE2(2));
        clcd_putch('-', LINE2(6));
        clcd_putch((YY / 10) + '0', LINE2(7));
        clcd_putch((YY % 10) + '0', LINE2(8));
        day(DAY);

    } else if (blink % 4 == 3) {
        if (sec % 2 == 0) {
            clcd_putch(' ', LINE2(7));
            clcd_putch(' ', LINE2(8));
        } else {

            clcd_putch((YY / 10) + '0', LINE2(7));
            clcd_putch((YY % 10) + '0', LINE2(8));
        }
        clcd_putch('-', LINE2(3));
        clcd_putch((DD / 10) + '0', LINE2(1));
        clcd_putch((DD % 10) + '0', LINE2(2));
        clcd_putch('-', LINE2(6));
        clcd_putch((MM / 10) + '0', LINE2(4));
        clcd_putch((MM % 10) + '0', LINE2(5));
        day(DAY);
    } else if (blink % 4 == 0) {
        if (sec % 2 == 0) {
            clcd_putch(' ', LINE2(10));
            clcd_putch(' ', LINE2(11));
            clcd_putch(' ', LINE2(12));
        } else {

            day(DAY);
        }
        clcd_putch('-', LINE2(3));
        clcd_putch((DD / 10) + '0', LINE2(1));
        clcd_putch((DD % 10) + '0', LINE2(2));
        clcd_putch('-', LINE2(6));
        clcd_putch((MM / 10) + '0', LINE2(4));
        clcd_putch((MM % 10) + '0', LINE2(5));
        clcd_putch((YY / 10) + '0', LINE2(7));
        clcd_putch((YY % 10) + '0', LINE2(8));

    }

    if (key == 1) {

        if (blink % 4 == 1 && DD < 31) {
            DD++;
        } else if (blink % 4 == 1 && DD >= 31) {
            DD = 1;
        }
        if (blink % 4 == 2 && MM < 12)
            MM++;
        else if (blink % 4 == 2 && MM > 11)
            MM = 1;
        if (blink % 4 == 3 && YY < 99)
            YY++;
        else if (blink % 4 == 3 && YY > 98)
            YY = 1;
        if (blink % 4 == 0 && DAY < 7)
            DAY++;
        else if (blink % 4 == 0 && DAY > 6)
            DAY = 1;
    }

    if (key == 4) {
        write_ds1307(YEAR_ADDR, ((YY % 10) | ((YY / 10) << 4)));
        write_ds1307(MONTH_ADDR, ((MM % 10) | ((MM / 10) << 4)));
        write_ds1307(DATE_ADDR, ((DD % 10) | ((DD / 10) << 4)));
        write_ds1307(DAY_ADDR, ((DAY % 10)));
        goto L1;
    }

    if (key == 5) {
L1:
        blink = 1;
        x = 1;
        clcd_print("                ", LINE1(0));
        clcd_print("                ", LINE2(0));
        state = e_main_menu;
    }

}

void get_time(void) {
    clock_reg[0] = read_ds1307(HOUR_ADDR);
    clock_reg[1] = read_ds1307(MIN_ADDR);
    clock_reg[2] = read_ds1307(SEC_ADDR);

    if (clock_reg[0] & 0x40) {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    } else {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    }
    time[2] = ':';
    time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
    time[4] = '0' + (clock_reg[1] & 0x0F);
    time[5] = ':';
    time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
    time[7] = '0' + (clock_reg[2] & 0x0F);
    time[8] = '\0';

}

void get_date(void) {
    calender_reg[0] = read_ds1307(YEAR_ADDR);
    calender_reg[1] = read_ds1307(MONTH_ADDR);
    calender_reg[2] = read_ds1307(DATE_ADDR);
    calender_reg[3] = read_ds1307(DAY_ADDR);

    //    date[0] = '2';
    //    date[1] = '0';
    date[6] = '0' + ((calender_reg[0] >> 4) & 0x0F);
    date[7] = '0' + (calender_reg[0] & 0x0F);
    date[2] = '-';
    date[3] = '0' + ((calender_reg[1] >> 4) & 0x0F);
    date[4] = '0' + (calender_reg[1] & 0x0F);
    date[5] = '-';
    date[0] = '0' + ((calender_reg[2] >> 4) & 0x0F);
    date[1] = '0' + (calender_reg[2] & 0x0F);
    date[8] = '0' + (calender_reg[3] & 0x0F);
    date[9] = '\0';
}

void set_event() {
    static unsigned char t_min, t_sec, hr = 0, min = 0, blink = 1, i = 0, PM = 0, str[] = {'O', 'D', 'W'};
    sec = time[7] - '0' + ((time[6] - '0') * 10);
    get_time();


    if (key == 2) {
        blink++;
    }
    static int x = 1;
    if (x == 1) {
        hr = (time[0] - '0') * 10;
        hr = (time[1] - '0') + hr;
        t_min = (time[3] - '0') * 10;
        t_min = (time[4] - '0') + t_min;
        t_sec = (time[6] - '0') * 10;
        t_sec = (time[7] - '0') + t_sec;
        x = 0;
    }

    if (blink % 4 == 1) {
        if (sec % 2 == 0) {
            clcd_putch(' ', LINE2(1));
            clcd_putch(' ', LINE2(2));
        } else {

            clcd_putch((hr / 10) + '0', LINE2(1));
            clcd_putch((hr % 10) + '0', LINE2(2));
        }
        clcd_putch(':', LINE2(3));
        clcd_putch((t_min / 10) + '0', LINE2(4));
        clcd_putch((t_min % 10) + '0', LINE2(5));


        if (clock_reg[0] & 0x20) {
            clcd_print(" PM", LINE2(6));
        } else {
            clcd_print(" AM", LINE2(6));
        }
        clcd_putch(str[i], LINE2(14));

    } else if (blink % 4 == 2) {
        if (sec % 2 == 0) {
            clcd_putch(' ', LINE2(4));
            clcd_putch(' ', LINE2(5));
        } else {
            clcd_putch((t_min / 10) + '0', LINE2(4));
            clcd_putch((t_min % 10) + '0', LINE2(5));
        }
        clcd_putch(':', LINE2(3));
        clcd_putch((hr / 10) + '0', LINE2(1));
        clcd_putch((hr % 10) + '0', LINE2(2));


        if (clock_reg[0] & 0x20) {
            clcd_print(" PM", LINE2(6));
        } else {
            clcd_print(" AM", LINE2(6));
        }
        clcd_putch(str[i], LINE2(14));

    } else if (blink % 4 == 3) {

        if (PM) {
            if (sec % 2 == 0) {
                clcd_putch(' ', LINE2(6));
                clcd_putch(' ', LINE2(7));
                clcd_putch(' ', LINE2(8));
            } else
                clcd_print(" PM", LINE2(6));
        } else {
            if (sec % 2 == 0) {
                clcd_putch(' ', LINE2(6));
                clcd_putch(' ', LINE2(7));
                clcd_putch(' ', LINE2(8));
            } else
                clcd_print(" AM", LINE2(6));
        }
        clcd_putch((t_min / 10) + '0', LINE2(4));
        clcd_putch((t_min % 10) + '0', LINE2(5));

        clcd_putch(':', LINE2(3));
        clcd_putch((hr / 10) + '0', LINE2(1));
        clcd_putch((hr % 10) + '0', LINE2(2));
        clcd_putch(str[i], LINE2(14));
    }
    if (blink % 4 == 0) {
        if (sec % 2 == 0)
            clcd_putch(' ', LINE2(14));
        else
            clcd_putch(str[i], LINE2(14));

        clcd_putch((t_min / 10) + '0', LINE2(4));
        clcd_putch((t_min % 10) + '0', LINE2(5));

        clcd_putch(':', LINE2(3));
        clcd_putch((hr / 10) + '0', LINE2(1));
        clcd_putch((hr % 10) + '0', LINE2(2));
        if (clock_reg[0] & 0x20) {
            clcd_print(" PM", LINE2(6));
        } else {
            clcd_print(" AM", LINE2(6));
        }
    }

    static char dummy;


    if (key == 1) {
        if (blink % 4 == 1 && hr < 12) {
            hr++;
        } else if (blink % 4 == 1 && hr >= 12) {
            hr = 1;
        }
        if (blink % 4 == 2 && t_min < 59)
            t_min++;
        else if (blink % 4 == 2 && t_min >= 59)
            t_min = 0;
        if (blink % 4 == 0 && i < 2)
            i++;
        else if (blink % 4 == 0 && i >= 2)
            i = 0;

        dummy = read_ds1307(HOUR_ADDR);
        if (blink % 4 == 3) {
            PM = !PM;
            if (PM == 1) {
                write_ds1307(HOUR_ADDR, dummy | (PM << 5));
            } else
                write_ds1307(HOUR_ADDR, dummy & 0xDF);
        }

    }
    static char lap[8];
    lap[0] = hr / 10 + '0';
    lap[1] = hr % 10 + '0';
    lap[2] = t_min / 10 + '0';
    lap[3] = t_min % 10 + '0';
    if (PM)
        lap[4] = 'P';
    else
        lap[4] = 'A';
    lap[5] = 'M';
    lap[6] = str[i];
    if (i == 0)
        lap[7] = '0';
    else if (i == 1)
        lap[7] = '2';
    if (i == 2)
        lap[7] = day + '0';
    static char k = 0, t_address;
    t_address = address;
    if (key == 4) {
        store(lap);
        strcpy(e_arr[k++], lap);
        if (address > 8) {
            sort();

            static char n;
            n = (address / 8);
            address = 0;
            for (int i = 0; i < n; i++) {
                store(e_arr[i]);
            }
        }
        goto L1;
    }
    // else {
    if (key == 5) {
L1:
        blink = 1;
        x = 1;
        PM = 0;
        write_ds1307(HOUR_ADDR, dummy & 0xDF);
        clcd_print(" AM", LINE2(6));
        clcd_print("                ", LINE1(0));
        clcd_print("                ", LINE2(0));
        state = e_main_menu;
    }

}

void view_log() {
    static char i = 0, j = 0, limit, flag = 1;
    int addr1 = 0;
   // clcd_putch(address + '0', LINE1(0));
    limit = (address / 8);
    //    if (address == 0 && sec < 8) {
    //        clcd_print("   EMPTY LOG    ", LINE1(0));
    //        clcd_print("                ", LINE2(0));
    //        if (sec == 7)
    //            goto jump;
    //    }
    //    else {
    if (flag == 1) {
        flag = 0;
        for (int j = 0; j < limit; j++) {
            for (int i = 0; i < 8; i++) {
                str[j][i] = ex_eeprom_read(addr1);
                addr1++;
                //                     clcd_putch(read_internal_eeprom(addr1++),LINE1(i));
            }
            str[j][8] = '\0';
            //           puts(str[j]);
            //           puts("\n\r");
        }

        //        i = 0;
    }
    //}
    //  clcd_print("# HH:MM AM/PM MD", LINE1(0));
    if (key == 1 && i < limit) {
        i++;
    } else if (key == 2 && i > 0)
        i--;

    if (i < limit) {

        clcd_putch((i + '0'), LINE2(0));
        clcd_putch(' ', LINE2(1));
        //}
        clcd_putch(str[i][0], LINE2(2));
        clcd_putch(str[i][1], LINE2(3));
        clcd_putch(':', LINE2(4));
        clcd_putch(str[i][2], LINE2(5));
        clcd_putch(str[i][3], LINE2(6));
        clcd_putch(' ', LINE2(7));
        clcd_putch(str[i][4], LINE2(8));
        clcd_putch(str[i][5], LINE2(9));
        clcd_putch(' ', LINE2(10));
        clcd_putch(str[i][6], LINE2(14));

    }


    if (key == 5) {
        //jump:
        flag = 1;
        state = e_main_menu;
        i = 0;
    }

}

void day(int day) {
    switch (day) {
        case 1: clcd_print("MON", LINE2(10));
            break;
        case 2: clcd_print("TUE", LINE2(10));
            break;
        case 3: clcd_print("WED", LINE2(10));
            break;
        case 4: clcd_print("THU", LINE2(10));
            break;
        case 5: clcd_print("FRI", LINE2(10));
            break;
        case 6: clcd_print("SAT", LINE2(10));
            break;
        case 7: clcd_print("SUN", LINE2(10));
            break;
    }
}

void sort() {
    static char t_address, hr1, hr2, min1, min2;
    t_address = address;

    for (int j = 0; j < (t_address / 8) - 1; j++) {
        for (int i = 0; i < (t_address / 8) - 1 - j; i++) {
            hr1 = (e_arr[i][0] - '0') * 10 + (e_arr[i][1] - '0');
            hr2 = (e_arr[i + 1][0] - '0') * 10 + (e_arr[i + 1][1] - '0');
            min1 = (e_arr[i][2] - '0') * 10 + (e_arr[i][3] - '0');
            min2 = (e_arr[i + 1][2] - '0') * 10 + (e_arr[i + 1][3] - '0');
            if (e_arr[i][4] == 'A' && e_arr[i + 1][4] == 'A') {
                if (hr1 > hr2)
                    swap(e_arr[i], e_arr[i + 1]);
                else if (hr1 == hr2 && min1 > min2)
                    swap(e_arr[i], e_arr[i + 1]);
            } else if (e_arr[i][4] == 'P' && e_arr[i + 1][4] == 'P') {
                if (hr1 > hr2)
                    swap(e_arr[i], e_arr[i + 1]);
                else if (hr1 == hr2 && min1 > min2)
                    swap(e_arr[i], e_arr[i + 1]);
            } else if (e_arr[i][4] == 'P' && e_arr[i + 1][4] == 'A') {
                swap(e_arr[i], e_arr[i + 1]);
            }

        }
    }
}