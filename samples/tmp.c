 switch(currentBeschleunigung[0]){
        case GESCHWINDIGKEIT_GLEICH:
            stats.acceleration = getRandomAround(0,1);
            stats.g_force = getRandomFloatAround(2,0.5);
            stats.motorTemp = minMax(getRandomAround(stats.motorTemp,3), MOTOR_TEMP_MIN, MOTOR_TEMP_MAX);
            stats.speed = minMax(getRandomAround(stats.speed, 5), GESCHWINDIGKEIT_MIN, GESCHWINDIGKEIT_MAX);
            stats.tankFilling = minMax(stats.tankFilling - TANK_DIFF_NORMAL, TANK_MIN, TANK_MAX);
            stats.tire1.brakeTemperatur = minMax(getRandom(stats.tire1.brakeTemperatur, BREMSE_ERHOLEN, RANDOM_DOWNWARS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire2.brakeTemperatur = minMax(getRandom(stats.tire2.brakeTemperatur, BREMSE_ERHOLEN, RANDOM_DOWNWARS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire3.brakeTemperatur = minMax(getRandom(stats.tire3.brakeTemperatur, BREMSE_ERHOLEN, RANDOM_DOWNWARS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire4.brakeTemperatur = minMax(getRandom(stats.tire4.brakeTemperatur, BREMSE_ERHOLEN, RANDOM_DOWNWARS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
        break;
        case GESCHWINDIGKEIT_BESCHLEUNIGUNG:
            stats.acceleration = minMax(getRandomAround(BESCHLEUNIGUNG_LEICHT,5), -BESCHLEUNIGUNG_MAX, BESCHLEUNIGUNG_MAX);
            stats.g_force = getRandomFloatAround(2.4,0.25);
            stats.motorTemp = minMax(getRandom(stats.motorTemp,MOTOR_TEMP_LEICHT, RANDOM_UPWARDS), MOTOR_TEMP_MIN, MOTOR_TEMP_MAX);
            stats.speed = minMax(getRandom(stats.speed, GESCHWINDIGKEIT_DIFF_LEICHT, RANDOM_UPWARDS), GESCHWINDIGKEIT_MIN, GESCHWINDIGKEIT_MAX);
            stats.tankFilling = minMax(stats.tankFilling - TANK_DIFF_BESCHLEUNIGUNG, TANK_MIN, TANK_MAX);
            stats.tire1.brakeTemperatur = minMax(getRandom(stats.tire1.brakeTemperatur, BREMSE_ERHOLEN, RANDOM_DOWNWARS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire2.brakeTemperatur = minMax(getRandom(stats.tire2.brakeTemperatur, BREMSE_ERHOLEN, RANDOM_DOWNWARS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire3.brakeTemperatur = minMax(getRandom(stats.tire3.brakeTemperatur, BREMSE_ERHOLEN, RANDOM_DOWNWARS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire4.brakeTemperatur = minMax(getRandom(stats.tire4.brakeTemperatur, BREMSE_ERHOLEN, RANDOM_DOWNWARS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
        break;
        case GESCHWINDIGKEIT_STARKE_BESCHLEUNIGUNG:
            stats.acceleration = minMax(getRandomAround(BESCHLEUNIGUNG_STARK,5), -BESCHLEUNIGUNG_MAX, BESCHLEUNIGUNG_MAX);
            stats.g_force = getRandomFloatAround(3.4,0.25);
            stats.motorTemp = minMax(getRandom(stats.motorTemp,MOTOR_TEMP_STARK, RANDOM_UPWARDS), MOTOR_TEMP_MIN, MOTOR_TEMP_MAX);
            stats.speed = minMax(getRandom(stats.speed, GESCHWINDIGKEIT_DIFF_STARK, RANDOM_UPWARDS), GESCHWINDIGKEIT_MIN, GESCHWINDIGKEIT_MAX);
            stats.tankFilling = minMax(stats.tankFilling - TANK_DIFF_BESCHLEUNIGUNG_STARK, TANK_MIN, TANK_MAX);
            stats.tire1.brakeTemperatur = minMax(getRandom(stats.tire1.brakeTemperatur, BREMSE_ERHOLEN, RANDOM_DOWNWARS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire2.brakeTemperatur = minMax(getRandom(stats.tire2.brakeTemperatur, BREMSE_ERHOLEN, RANDOM_DOWNWARS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire3.brakeTemperatur = minMax(getRandom(stats.tire3.brakeTemperatur, BREMSE_ERHOLEN, RANDOM_DOWNWARS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire4.brakeTemperatur = minMax(getRandom(stats.tire4.brakeTemperatur, BREMSE_ERHOLEN, RANDOM_DOWNWARS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
        break;
        case GESCHWINDIGKEIT_BREMSEN:
            stats.acceleration = minMax(getRandomAround(-BESCHLEUNIGUNG_LEICHT,5), -BESCHLEUNIGUNG_MAX, BESCHLEUNIGUNG_MAX);
            stats.g_force = getRandomFloatAround(2.4,0.25);
            stats.motorTemp = minMax(getRandom(stats.motorTemp,MOTOR_TEMP_STARK, RANDOM_DOWNWARS), MOTOR_TEMP_MIN, MOTOR_TEMP_MAX);
            stats.speed = minMax(getRandom(stats.speed, GESCHWINDIGKEIT_DIFF_LEICHT, RANDOM_DOWNWARS), GESCHWINDIGKEIT_MIN, GESCHWINDIGKEIT_MAX);
            stats.tankFilling = minMax(stats.tankFilling - TANK_DIFF_IDLE, TANK_MIN, TANK_MAX);
            stats.tire1.brakeTemperatur = minMax(getRandom(stats.tire1.brakeTemperatur, BREMSE_LEICHT, RANDOM_UPWARDS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire2.brakeTemperatur = minMax(getRandom(stats.tire2.brakeTemperatur, BREMSE_LEICHT, RANDOM_UPWARDS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire3.brakeTemperatur = minMax(getRandom(stats.tire3.brakeTemperatur, BREMSE_LEICHT, RANDOM_UPWARDS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire4.brakeTemperatur = minMax(getRandom(stats.tire4.brakeTemperatur, BREMSE_LEICHT, RANDOM_UPWARDS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
        break;
        case GESCHWINDIGKEIT_STARK_BREMSEN:
            stats.acceleration = minMax(getRandomAround(-BESCHLEUNIGUNG_STARK,5), -BESCHLEUNIGUNG_MAX, BESCHLEUNIGUNG_MAX);
            stats.g_force = getRandomFloatAround(2.4,0.25);
            stats.motorTemp = minMax(getRandom(stats.motorTemp,MOTOR_TEMP_LEICHT, RANDOM_DOWNWARS), MOTOR_TEMP_MIN, MOTOR_TEMP_MAX);
            stats.speed = minMax(getRandom(stats.speed, GESCHWINDIGKEIT_DIFF_STARK, RANDOM_DOWNWARS), GESCHWINDIGKEIT_MIN, GESCHWINDIGKEIT_MAX);
            stats.tankFilling = minMax(stats.tankFilling - TANK_DIFF_IDLE, TANK_MIN, TANK_MAX);
            stats.tire1.brakeTemperatur = minMax(getRandom(stats.tire1.brakeTemperatur, BREMSE_STARK, RANDOM_UPWARDS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire2.brakeTemperatur = minMax(getRandom(stats.tire2.brakeTemperatur, BREMSE_STARK, RANDOM_UPWARDS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire3.brakeTemperatur = minMax(getRandom(stats.tire3.brakeTemperatur, BREMSE_STARK, RANDOM_UPWARDS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
            stats.tire4.brakeTemperatur = minMax(getRandom(stats.tire4.brakeTemperatur, BREMSE_STARK, RANDOM_UPWARDS), BREMSE_TEMP_MIN, BREMSE_TEMP_MAX);
        break;
        default:
        printf("Ungültige Beschleunigung %i",currentBeschleunigung[0]);
    }
    switch(currentKurve[0]){
        case FAHRWEISE_GERADE:
            stats.tire1.tireTemperatur = minMax(getRandom(stats.tire1.tireTemperatur, REIFEN_LENKEN_IDLE, RANDOM_DOWNWARS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire2.tireTemperatur = minMax(getRandom(stats.tire2.tireTemperatur, REIFEN_LENKEN_IDLE, RANDOM_DOWNWARS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire3.tireTemperatur = minMax(getRandom(stats.tire3.tireTemperatur, REIFEN_LENKEN_IDLE, RANDOM_DOWNWARS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire4.tireTemperatur = minMax(getRandom(stats.tire4.tireTemperatur, REIFEN_LENKEN_IDLE, RANDOM_DOWNWARS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
        break;
        case FAHRWEISE_LEICHT_LINKS:
            stats.tire1.tireTemperatur = minMax(getRandom(stats.tire1.tireTemperatur, REIFEN_LENKEN_INNEN_LEICHT, RANDOM_UPWARDS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire2.tireTemperatur = minMax(getRandom(stats.tire2.tireTemperatur, REIFEN_LENKEN_AUSSEN_LEICHT, RANDOM_UPWARDS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire3.tireTemperatur = minMax(getRandom(stats.tire3.tireTemperatur, REIFEN_LENKEN_AUSSEN_LEICHT, RANDOM_UPWARDS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire4.tireTemperatur = minMax(getRandom(stats.tire4.tireTemperatur, REIFEN_LENKEN_INNEN_LEICHT, RANDOM_UPWARDS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.g_force += getRandomFloatAround(0.5, 0.75);
            break;
        case FAHRWEISE_STARK_LINKS:
            stats.tire1.tireTemperatur = minMax(getRandom(stats.tire1.tireTemperatur, REIFEN_LENKEN_INNEN_STARK, RANDOM_UPWARDS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire2.tireTemperatur = minMax(getRandom(stats.tire2.tireTemperatur, REIFEN_LENKEN_AUSSEN_STARK, RANDOM_UPWARDS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire3.tireTemperatur = minMax(getRandom(stats.tire3.tireTemperatur, REIFEN_LENKEN_AUSSEN_STARK, RANDOM_UPWARDS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire4.tireTemperatur = minMax(getRandom(stats.tire4.tireTemperatur, REIFEN_LENKEN_INNEN_STARK, RANDOM_UPWARDS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.g_force += getRandomFloatAround(1, 0.5);
            break;
        case FAHRWEISE_LEICHT_RECHTS:
            stats.tire1.tireTemperatur = minMax(getRandom(stats.tire1.tireTemperatur, REIFEN_LENKEN_AUSSEN_LEICHT, RANDOM_UPWARDS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire2.tireTemperatur = minMax(getRandom(stats.tire2.tireTemperatur, REIFEN_LENKEN_INNEN_LEICHT, RANDOM_UPWARDS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire3.tireTemperatur = minMax(getRandom(stats.tire3.tireTemperatur, REIFEN_LENKEN_INNEN_LEICHT, RANDOM_UPWARDS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire4.tireTemperatur = minMax(getRandom(stats.tire4.tireTemperatur, REIFEN_LENKEN_AUSSEN_LEICHT, RANDOM_UPWARDS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.g_force += getRandomFloatAround(0.5, 0.75);
            break;
        case FAHRWEISE_STARK_RECHTS:
            stats.tire1.tireTemperatur = minMax(getRandom(stats.tire1.tireTemperatur, REIFEN_LENKEN_AUSSEN_STARK, RANDOM_UPWARDS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire2.tireTemperatur = minMax(getRandom(stats.tire2.tireTemperatur, REIFEN_LENKEN_INNEN_STARK, RANDOM_UPWARDS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire3.tireTemperatur = minMax(getRandom(stats.tire3.tireTemperatur, REIFEN_LENKEN_INNEN_STARK, RANDOM_UPWARDS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.tire4.tireTemperatur = minMax(getRandom(stats.tire4.tireTemperatur, REIFEN_LENKEN_AUSSEN_STARK, RANDOM_UPWARDS), REIFEN_TEMP_MIN, REIFEN_TEMP_MAX);
            stats.g_force += getRandomFloatAround(1, 0.5);
            break;
        default:
            printf("Fehler in der Lenkung: %i",currentKurve[0]);
        }