#include <xc.h>

/* Enum for maintaining the app state */
typedef enum {
    e_dashboard, e_main_menu, e_view_log, e_set_time, e_download_log, e_clear_log,e_set_date,e_set_event
} State_t;


extern State_t state; // App state

//Function declarations

//Dashboard function declaration
void view_dashboard(void);

//Storing events function declaration
void event_store(void);

//Password function declaration
void password(void);

//main menu function declaration
void display_main_menu(void);

//View log function declaration
void view_log(void);

//Reading events function declaration
void event_reader(void);

//Change password function declaration
void change_password(void);

//Set time function declaration
void set_time(void);

//Set time function declaration
void set_date(void);

//Download log function _decleration
void download_log(void);

//Clear log function declaration
void clear_log(void);

// set event function
void set_event(void);

// CLCD Function 
unsigned char read_switches(unsigned char detection_type);
unsigned char scan_key(void);
void init_matrix_keypad();


extern unsigned short key;
extern unsigned short address;
extern char sec;
extern char time[17];

// EEPROM Function 
unsigned char read_internal_eeprom(unsigned char address);
void write_internal_eeprom(unsigned char address, unsigned char data);

// uart funcitons


#define RX_PIN					TRISC7
#define TX_PIN					TRISC6

void init_uart(void);
void putch(unsigned char byte);
int puts(const char *s);
unsigned char getch(void);
unsigned char getch_with_timeout(unsigned short max_time);
unsigned char getche(void);

// i2c functions 
void init_i2c(void);
void i2c_start(void);
void i2c_rep_start(void);
void i2c_stop(void);
void i2c_write(unsigned char data);
unsigned char i2c_read(void);

// external ee eprom 

#define SLAVE_READ		0xA1
#define SLAVE_WRITE		0xA0

///*
#define SEC_ADDR		0x00
#define MIN_ADDR		0x01
#define HOUR_ADDR		0x02
#define DAY_ADDR		0x03
#define DATE_ADDR		0x04
#define MONTH_ADDR		0x05
#define YEAR_ADDR		0x06
#define CNTL_ADDR		0x07
//*/

void ex_eeprom_write(unsigned char address, unsigned char data);
unsigned char ex_eeprom_read(unsigned char address);

// rtc
void write_ds1307(unsigned char address1,  unsigned char data);
unsigned char read_ds1307(unsigned char address1);
void init_ds1307(void);
//
void alarm();

//matrix 
//void init_matrix_keypad();