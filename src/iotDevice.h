
/*****************************************************************************
 *                  Defines                                                  *
 ****************************************************************************/
#define FAHRWEISE_GERADE 0
#define FAHRWEISE_LEICHT_LINKS -1
#define FAHRWEISE_STARK_LINKS -2
#define FAHRWEISE_LEICHT_RECHTS 1
#define FAHRWEISE_STARK_RECHTS 2

#define REIFEN_LENKEN_AUSSEN_LEICHT 3
#define REIFEN_LENKEN_AUSSEN_STARK 4
#define REIFEN_LENKEN_INNEN_LEICHT 2
#define REIFEN_LENKEN_INNEN_STARK 3
#define REIFEN_LENKEN_IDLE 6

#define REIFEN_TEMP_MIN 70
#define REIFEN_TEMP_MAX 120 
#define REIFEN_TEMP_ZUFALLSRAHMEN 3

#define BREMSE_LEICHT 100
#define BREMSE_STARK 200
#define BREMSE_ERHOLEN 90

#define BREMSE_TEMP_MIN 300
#define BREMSE_TEMP_MAX 1200
#define BREMSE_ZUFALLSRAHMEN 20

#define GESCHWINDIGKEIT_MIN 0
#define GESCHWINDIGKEIT_MAX 380

#define GESCHWINDIGKEIT_DIFF_LEICHT 25
#define GESCHWINDIGKEIT_DIFF_STARK 50

#define BESCHLEUNIGUNG_MIN 0
#define BESCHLEUNIGUNG_MAX 100
#define BESCHLEUNIGUNG_LEICHT 5
#define BESCHLEUNIGUNG_STARK 15

#define MOTOR_TEMP_MIN 75
#define MOTOR_TEMP_MAX 130
#define MOTOR_TEMP_LEICHT 2
#define MOTOR_TEMP_STARK 4

#define TANK_MIN 0
#define TANK_MAX 100
#define TANK_DIFF_BESCHLEUNIGUNG 0.04
#define TANK_DIFF_BESCHLEUNIGUNG_STARK 0.07
#define TANK_DIFF_NORMAL 0.02
#define TANK_DIFF_BREAK  0.01
#define TANK_DIFF_IDLE   0.005

#define GESCHWINDIGKEIT_GLEICH 0
#define GESCHWINDIGKEIT_BESCHLEUNIGUNG 1
#define GESCHWINDIGKEIT_STARKE_BESCHLEUNIGUNG 2
#define GESCHWINDIGKEIT_BREMSEN -1
#define GESCHWINDIGKEIT_STARK_BREMSEN -2

#define RANDOM_UPWARDS 1
#define RANDOM_DOWNWARS 0

#define GKRAFT_MIN 0
#define GKRAFT_MAX 5

#define GKRAFT_NORMAL 1.5
#define GKRAFT_LEICHT 2.4
#define GKRAFT_MITTEL 3
#define GKRFT_STARK 4.5
#define GKRAFT_LK 0.5
#define GKRAFT_SK 1.5


/*****************************************************************************
 *                  Structs                                                  *
 ****************************************************************************/

typedef struct __tireStats{
    int tireTemperatur;
    //float tirePressure;
    int brakeTemperatur;
}tireStats;

typedef struct __generalStats{
    tireStats tire1;
    tireStats tire2;
    tireStats tire3;
    tireStats tire4;

    int motorTemp;
    int speed;
    int acceleration;
    float tankFilling;
    float g_force;
    int rundenzeit;
    int lap;
} generalStats;

typedef union __failcondition{
    struct{
        uint8_t tire1Brake:1;
        uint8_t tire1Tire:1;
        uint8_t tire2Brake:1;
        uint8_t tire2Tire:1;
        uint8_t tire3Brake:1;
        uint8_t tire3Tire:1;
        uint8_t tire4Brake:1;
        uint8_t tire4Tire:1;
        uint8_t motor:1;
        uint8_t errorsize:7;
    }errorbits;

    uint8_t ui8_data[2];
    uint16_t ui16_data;
}failStates;