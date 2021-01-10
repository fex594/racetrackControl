
/*******************************************************************************
 * Copyright (c) 2015 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Jeffrey Dare - initial implementation and API implementation
 *    Lokesh Haralakatta - Added required changes to use Client Side certificates
 *******************************************************************************/

#include "deviceclient.h"
#include "iotDevice.h"
#include <stdlib.h>
#include <time.h>

void deviceInit(void);
int getRandomAround(int base, int radius);
int getRandom(int base, int radius, int way);
void processNextTrackpart();
int sendJSON();
int minMax(int value, int min, int max);
void processTrackpart(void);
float minMaxFloat(float value, float min, float max);
void processRandom(void);


generalStats stats;
generalStats randomStats;
iotfclient  client;
static int gesamtBeschleunigung[] = {0,1,2,2,2,2,1,1,0,0,0,0,-1,-2,-2,-2,-2,-1,-1,0,0,1,1,1,1,1,1,2,2,-2,-1,0};
// static int gesamtBeschleunigung[] = {0,1,2,2,2,2,1,1};
int *currentBeschleunigung;
static int gesamtKurve[] = {0,1,2,2,2,2,1,1,0,0,0,0,-1,-2,-2,-2,-2,-1,-1,0,0,1,1,1,1,1,1,2,2,-2,-1,0};
// static int gesamtKurve[] = {0,1,2,2,2,2,1,1,0};
int *currentKurve;
int trackLength;
int currentTrackpart = 0;
int checkpoint = 0;
unsigned long lastRoundstamp;

void deviceInit(){
    stats.g_force = 1;
    stats.acceleration = BESCHLEUNIGUNG_MIN;
    stats.motorTemp = MOTOR_TEMP_MIN;
    stats.tankFilling = TANK_MAX;
    stats.speed = GESCHWINDIGKEIT_MIN;
    stats.tire1.brakeTemperatur = BREMSE_TEMP_MIN;
    stats.tire1.tireTemperatur = REIFEN_TEMP_MIN;
    stats.tire1.brakeTemperatur = BREMSE_TEMP_MIN;
    stats.tire2.tireTemperatur = REIFEN_TEMP_MIN;
    stats.tire3.brakeTemperatur = BREMSE_TEMP_MIN;
    stats.tire3.tireTemperatur = REIFEN_TEMP_MIN;
    stats.tire4.brakeTemperatur = BREMSE_TEMP_MIN;
    stats.tire4.tireTemperatur = REIFEN_TEMP_MIN;

    stats.rundenzeit = 0;
    stats.lap = 0;
    lastRoundstamp = (unsigned long)time(NULL);

    srand(time(NULL));
    trackLength = sizeof(gesamtBeschleunigung) / sizeof(int);
    printf("Tracklänge: %i",trackLength);
    currentBeschleunigung = &gesamtBeschleunigung[0];
    currentKurve = &gesamtKurve[0];
}
int getRandomAround(int base, int radius){
    return base + ((rand() % (2 * radius))- radius);
}
float getRandomFloatAround(float base, float radius){
    int diff = ((int)(radius * 100) * 2);
    int randomValue = rand() % diff;
    float randomValueSmall = randomValue / 100;
    return base + randomValueSmall - radius;
}
int getRandom(int base, int radius, int way)
{
    if(RANDOM_UPWARDS == way){
        return base + (rand() % radius);
    }
    else
    {
        return base - (rand() % radius);
    }
}
int minMax(int value, int min, int max){
    if(value >= max)
    {
        return max;
    }else if(value <= min){
        return min;
    }else{
        return value;
    }
}
float minMaxFloat(float value, float min, float max){
    if(value >= max)
    {
        return max;
    }else if(value <= min){
        return min;
    }else{
        return value;
    }
}


volatile int interrupt = 0;

// Handle signal interrupt
void sigHandler(int signo) {
	printf("SigINT received.\n");
	interrupt = 1;
}

void processNextTrackpart(){
    if(currentTrackpart >= trackLength){
        checkpoint = 0;
        currentTrackpart = 0;
        stats.lap++;
        currentBeschleunigung = &gesamtBeschleunigung[0];
        currentKurve = &gesamtKurve[0];

        unsigned long currentTimeStamp = time(NULL);
        stats.rundenzeit = (int) (currentTimeStamp - lastRoundstamp);
        lastRoundstamp = currentTimeStamp;

    }else{
        currentKurve++;
        currentBeschleunigung++;
        currentTrackpart++;

        if((currentTrackpart % 5) == 0){
            checkpoint++;
        }
    }
    
}

void processTrackpart(){
    int lastSpeedKmh = stats.speed;
    float lastSpeedMs = (lastSpeedKmh * 1000 ) / 3600;
    switch(currentBeschleunigung[0]){
        case GESCHWINDIGKEIT_GLEICH:
            //stats.acceleration = BESCHLEUNIGUNG_MIN;
            stats.g_force = GKRAFT_NORMAL;
            stats.motorTemp = minMax(stats.motorTemp - 1, MOTOR_TEMP_MIN, MOTOR_TEMP_MAX);
            //stats.speed = minMax(getRandomAround(stats.speed, 5), GESCHWINDIGKEIT_MIN, GESCHWINDIGKEIT_MAX);
            stats.tankFilling = minMaxFloat(stats.tankFilling - TANK_DIFF_NORMAL, TANK_MIN, TANK_MAX);
            stats.tire1.brakeTemperatur = minMax(stats.tire1.brakeTemperatur - BREMSE_ERHOLEN, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire2.brakeTemperatur = minMax(stats.tire2.brakeTemperatur - BREMSE_ERHOLEN, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire3.brakeTemperatur = minMax(stats.tire3.brakeTemperatur - BREMSE_ERHOLEN, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire4.brakeTemperatur = minMax(stats.tire4.brakeTemperatur - BREMSE_ERHOLEN, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
        break;
        case GESCHWINDIGKEIT_BESCHLEUNIGUNG:
         //   stats.acceleration = BESCHLEUNIGUNG_LEICHT;
            stats.g_force = GKRAFT_LEICHT;
            stats.motorTemp = minMax(stats.motorTemp + MOTOR_TEMP_LEICHT, MOTOR_TEMP_MIN, MOTOR_TEMP_MAX);
            stats.speed = minMax(stats.speed + GESCHWINDIGKEIT_DIFF_LEICHT, GESCHWINDIGKEIT_MIN, GESCHWINDIGKEIT_MAX);
            stats.tankFilling = minMaxFloat(stats.tankFilling - TANK_DIFF_BESCHLEUNIGUNG, TANK_MIN, TANK_MAX);
            stats.tire1.brakeTemperatur = minMax(stats.tire1.brakeTemperatur - BREMSE_ERHOLEN, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire2.brakeTemperatur = minMax(stats.tire2.brakeTemperatur - BREMSE_ERHOLEN, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire3.brakeTemperatur = minMax(stats.tire3.brakeTemperatur - BREMSE_ERHOLEN, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire4.brakeTemperatur = minMax(stats.tire4.brakeTemperatur - BREMSE_ERHOLEN, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
        break;
        case GESCHWINDIGKEIT_STARKE_BESCHLEUNIGUNG:
          //  stats.acceleration = BESCHLEUNIGUNG_STARK;
            stats.g_force = GKRAFT_MITTEL;
            stats.motorTemp = minMax(stats.motorTemp + MOTOR_TEMP_STARK, MOTOR_TEMP_MIN, MOTOR_TEMP_MAX);
            stats.speed = minMax(stats.speed + GESCHWINDIGKEIT_DIFF_STARK, GESCHWINDIGKEIT_MIN, GESCHWINDIGKEIT_MAX);
            stats.tankFilling = minMaxFloat(stats.tankFilling - TANK_DIFF_BESCHLEUNIGUNG_STARK, TANK_MIN, TANK_MAX);
            stats.tire1.brakeTemperatur = minMax(stats.tire1.brakeTemperatur - BREMSE_ERHOLEN, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire2.brakeTemperatur = minMax(stats.tire2.brakeTemperatur - BREMSE_ERHOLEN, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire3.brakeTemperatur = minMax(stats.tire3.brakeTemperatur - BREMSE_ERHOLEN, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire4.brakeTemperatur = minMax(stats.tire4.brakeTemperatur - BREMSE_ERHOLEN, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
        break;
        case GESCHWINDIGKEIT_BREMSEN:
        //    stats.acceleration = -BESCHLEUNIGUNG_LEICHT;
            stats.g_force = GKRAFT_LEICHT;
            stats.motorTemp = minMax(stats.motorTemp - MOTOR_TEMP_STARK, MOTOR_TEMP_MIN, MOTOR_TEMP_MAX);
            stats.speed = minMax(stats.speed - GESCHWINDIGKEIT_DIFF_LEICHT, GESCHWINDIGKEIT_MIN, GESCHWINDIGKEIT_MAX);
            stats.tankFilling = minMaxFloat(stats.tankFilling - TANK_DIFF_IDLE, TANK_MIN, TANK_MAX);
            stats.tire1.brakeTemperatur = minMax(stats.tire1.brakeTemperatur + BREMSE_LEICHT, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire2.brakeTemperatur = minMax(stats.tire2.brakeTemperatur + BREMSE_LEICHT, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire3.brakeTemperatur = minMax(stats.tire3.brakeTemperatur + BREMSE_LEICHT, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire4.brakeTemperatur = minMax(stats.tire4.brakeTemperatur + BREMSE_LEICHT, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
        break;
        case GESCHWINDIGKEIT_STARK_BREMSEN:
         //   stats.acceleration = - BESCHLEUNIGUNG_STARK;
            stats.g_force = GKRAFT_MITTEL;
            stats.motorTemp = minMax(stats.motorTemp - MOTOR_TEMP_LEICHT, MOTOR_TEMP_MIN, MOTOR_TEMP_MAX);
            stats.speed = minMax(stats.speed - GESCHWINDIGKEIT_DIFF_STARK, GESCHWINDIGKEIT_MIN, GESCHWINDIGKEIT_MAX);
            stats.tankFilling = minMaxFloat(stats.tankFilling - TANK_DIFF_IDLE, TANK_MIN, TANK_MAX);
            stats.tire1.brakeTemperatur = minMax(stats.tire1.brakeTemperatur + BREMSE_STARK, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire2.brakeTemperatur = minMax(stats.tire2.brakeTemperatur + BREMSE_STARK, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire3.brakeTemperatur = minMax(stats.tire3.brakeTemperatur + BREMSE_STARK, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire4.brakeTemperatur = minMax(stats.tire4.brakeTemperatur + BREMSE_STARK, BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
        break;
        default:
        printf("Ungültige Beschleunigung %i",currentBeschleunigung[0]);
    }

    float currentSpeedMs = (stats.speed * 1000 / 3600);
    float diffSpeedMs = currentSpeedMs - lastSpeedMs;
    stats.acceleration = diffSpeedMs / 2;

    switch(currentKurve[0]){
        case FAHRWEISE_GERADE:
            stats.tire1.tireTemperatur = minMax(stats.tire1.tireTemperatur - REIFEN_LENKEN_IDLE, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire2.tireTemperatur = minMax(stats.tire2.tireTemperatur - REIFEN_LENKEN_IDLE, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire3.tireTemperatur = minMax(stats.tire3.tireTemperatur - REIFEN_LENKEN_IDLE, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire4.tireTemperatur = minMax(stats.tire4.tireTemperatur - REIFEN_LENKEN_IDLE, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
        break;
        case FAHRWEISE_LEICHT_LINKS:
            stats.tire1.tireTemperatur = minMax(stats.tire1.tireTemperatur + REIFEN_LENKEN_INNEN_LEICHT, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire2.tireTemperatur = minMax(stats.tire2.tireTemperatur + REIFEN_LENKEN_AUSSEN_LEICHT, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire3.tireTemperatur = minMax(stats.tire3.tireTemperatur + REIFEN_LENKEN_AUSSEN_LEICHT, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire4.tireTemperatur = minMax(stats.tire4.tireTemperatur + REIFEN_LENKEN_INNEN_LEICHT, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.g_force += GKRAFT_LK;
            break;
        case FAHRWEISE_STARK_LINKS:
            stats.tire1.tireTemperatur = minMax(stats.tire1.tireTemperatur + REIFEN_LENKEN_INNEN_STARK, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire2.tireTemperatur = minMax(stats.tire2.tireTemperatur + REIFEN_LENKEN_AUSSEN_STARK, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire3.tireTemperatur = minMax(stats.tire3.tireTemperatur + REIFEN_LENKEN_AUSSEN_STARK, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire4.tireTemperatur = minMax(stats.tire4.tireTemperatur + REIFEN_LENKEN_INNEN_STARK, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.g_force += GKRAFT_SK;
            break;
        case FAHRWEISE_LEICHT_RECHTS:
            stats.tire1.tireTemperatur = minMax(stats.tire1.tireTemperatur + REIFEN_LENKEN_AUSSEN_LEICHT, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire2.tireTemperatur = minMax(stats.tire2.tireTemperatur + REIFEN_LENKEN_INNEN_LEICHT, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire3.tireTemperatur = minMax(stats.tire3.tireTemperatur + REIFEN_LENKEN_INNEN_LEICHT, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire4.tireTemperatur = minMax(stats.tire4.tireTemperatur + REIFEN_LENKEN_AUSSEN_LEICHT, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.g_force += GKRAFT_LK;
            break;
        case FAHRWEISE_STARK_RECHTS:
            stats.tire1.tireTemperatur = minMax(stats.tire1.tireTemperatur + REIFEN_LENKEN_AUSSEN_STARK, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire2.tireTemperatur = minMax(stats.tire2.tireTemperatur + REIFEN_LENKEN_INNEN_STARK, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire3.tireTemperatur = minMax(stats.tire3.tireTemperatur + REIFEN_LENKEN_INNEN_STARK, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire4.tireTemperatur = minMax(stats.tire4.tireTemperatur + REIFEN_LENKEN_AUSSEN_STARK, REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.g_force += GKRAFT_SK;
            break;
        default:
            printf("Fehler in der Lenkung: %i",currentKurve[0]);
        }
}
void processRandom(){
    randomStats.acceleration = getRandomAround(stats.acceleration,1);
    randomStats.g_force = getRandomFloatAround(stats.g_force, 0.5);
    randomStats.motorTemp = getRandomAround(stats.motorTemp, 2);
    randomStats.speed = getRandomAround(stats.speed, 10);
    randomStats.tankFilling = stats.tankFilling;
    randomStats.tire1.brakeTemperatur = getRandomAround(stats.tire1.brakeTemperatur, BREMSE_ZUFALLSRAHMEN);
    randomStats.tire1.tireTemperatur = getRandomAround(stats.tire1.tireTemperatur, REIFEN_TEMP_ZUFALLSRAHMEN);
    randomStats.tire2.brakeTemperatur = getRandomAround(stats.tire2.brakeTemperatur, BREMSE_ZUFALLSRAHMEN);;
    randomStats.tire2.tireTemperatur = getRandomAround(stats.tire1.tireTemperatur, REIFEN_TEMP_ZUFALLSRAHMEN);
    randomStats.tire3.brakeTemperatur = getRandomAround(stats.tire3.brakeTemperatur, BREMSE_ZUFALLSRAHMEN);;
    randomStats.tire3.tireTemperatur = getRandomAround(stats.tire1.tireTemperatur, REIFEN_TEMP_ZUFALLSRAHMEN);
    randomStats.tire4.brakeTemperatur = getRandomAround(stats.tire4.brakeTemperatur, BREMSE_ZUFALLSRAHMEN);;
    randomStats.tire4.tireTemperatur = getRandomAround(stats.tire1.tireTemperatur, REIFEN_TEMP_ZUFALLSRAHMEN);

}

int sendJSON(){
    int success = 0;
    //printf("Publishing the event stat with rc ");

    char message[600];
    sprintf(message, "{\"data\":{\"tire1\":{\"brake\":%i,\"temp\":%i},\"tire2\":{\"brake\":%i,\"temp\":%i},\"tire3\":{\"brake\":%i,\"temp\":%i},\"tire4\":{\"brake\":%i,\"temp\":%i},\"motortemp\":%i,\"speed\":%i,\"acceleration\":%i,\"tankfilling\":%f,\"g_force\":%f,\"checkpoint\":%i,\"timestamp\":%i,\"lap\":%i}}",
    randomStats.tire1.brakeTemperatur, randomStats.tire1.tireTemperatur, randomStats.tire2.brakeTemperatur, randomStats.tire2.tireTemperatur,
    randomStats.tire3.brakeTemperatur, randomStats.tire3.tireTemperatur, randomStats.tire4.brakeTemperatur, randomStats.tire4.tireTemperatur,
    randomStats.motorTemp, randomStats.speed, randomStats.acceleration, randomStats.tankFilling, randomStats.g_force, checkpoint, 
    stats.rundenzeit, stats.lap);
	success= publishEvent(&client, "status","json", message, QOS0);
	printf("Data send code: %d\n", success);
    printf("%s\n",message);
	yield(&client,1000);
	
    return success;
}

void myCallback (char* commandName, char* format, void* payload)
{
	printf("------------------------------------\n" );
	printf("The command received :: %s\n", commandName);
	printf("format : %s\n", format);
	printf("Payload is : %s\n", (char *)payload);

	printf("------------------------------------\n" );
}

int main(int argc, char const *argv[])
{
	int rc = -1;

	//catch interrupt signal
	signal(SIGINT, sigHandler);
	signal(SIGTERM, sigHandler);

	char* configFilePath;

	if(isEMBDCHomeDefined()){

	    getSamplesPath(&configFilePath);
	    configFilePath = realloc(configFilePath,strlen(configFilePath)+15);
	    strcat(configFilePath,"device.cfg");
    }
	else{
	    printf("IOT_EMBDC_HOME is not defined\n");
	    printf("Define IOT_EMBDC_HOME to client library path to execute samples\n");
	    return -1;
    }

	rc = initialize_configfile(&client, configFilePath,0);
	free(configFilePath);

	if(rc != SUCCESS){
		printf("initialize failed and returned rc = %d.\n Quitting..", rc);
		return 0;
	}

    deviceInit();

	//unsigned short interval = 59;
	//setKeepAliveInterval(interval);

	rc = connectiotf(&client);

	if(rc != SUCCESS){
		printf("Connection failed and returned rc = %d.\n Quitting..", rc);
		return 0;
	}

	if(!client.isQuickstart){
	    subscribeCommands(&client);
	    setCommandHandler(&client, myCallback);
    }
    printf("Setup complete");
	while(!interrupt)
	{
        processNextTrackpart();
        processTrackpart();
        processRandom();
        sendJSON();
		sleep(2);
	}

	printf("Quitting!!\n");

	disconnect(&client);
	return 0;
}

