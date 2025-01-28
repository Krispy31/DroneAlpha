// structs, many readings and dimentions, this just gives the idea
#define READINGS_COUNT  40
#define OLD_READINGS    3
// Constants I can tune P,ID with
#define PID_CONSTANT_P  1
#define PID_CONSTANT_I  1
#define PID_CONSTANT_D  1

 
/********************************************************************************
// TODO: Add some of these
* Xy parameter should be the same, and different from the z set of PID constants
* Have rails for the x/y dimensions…
* Conver over to struct of xyz
********************************************************************************/

// Psudo header
typedef enum MotorNumber {MOTOR_ZERO, MOTOR_ONE, MOTOR_TWO, MOTOR_THREE, MOTOR_COUNT};


static void updateReadings (char);
void addReading(char);
void initMotors (void);
void PIDController (void);
void updateMotor(MotorNumber, unsigned char);



// todo: add a way to update the target values, I know I'll target positions like 100 or zero, but eventually that changes
// Could have some that I target?
// char targets[3] = {0, 0, 0};// assumes dimentions


// will become an array of structs, 
// typedef struct oneReading {char x, char y, char z};// may need more dimentions,
static char pastReadings[OLD_READINGS];// holds the average for each 
static char readings[READINGS_COUNT];// Just take the last x number, and base it on that, its nice to average, might do EMA?
static _Bool filled;// perhaps make sure I  
static unsigned char endReadings;

static unsigned char readingsTaken;
static float integralTerm = 0;
static char targetZ = 100; // Target position, can be updated as needed



// call this every time we get a reading, periodically it will do all other processing
void addReading(char reading) {
    // May do some extra processing around this, If we have accelerometer rather than position
    // do all that here
    double averageReading = 0;
    unsigned char readingsNumber = 0;

    readings[endReadings++] = reading;
    if (endReadings >= 40) {
        filled = true;
        endReadings = 0;

        if (filled)
            readingsNumber = endReadings;
        else
            readingsNumber = READINGS_COUNT;

        for (int i=0;i<readingsNumber;i++) {
            averageReading += readings[i];
        }
        averageReading /= (float) readingsNumber;
        updateReadings((char) averageReading);
        PIDController();
    }
}


static void updateReadings (char newAverage) {
    // gets rid of the old averaged reading, adds new reading
    for (char i=OLD_READINGS-1;i>0;i--) {
        pastReadings[i] = pastReadings[i-1];
    }
    pastReadings[0] = newAverage;
}


// motor zero is the front left, motor one is the front right, motor two is back right

// We have 4 DACs, going to a part that generates a PWM, which
void initMotors (void) {
    // set the 4 dacs up
}


void updateMotor(MotorNumber, unsigned char setting) {
    // Setting is 0-200, I'll try to have ~100 be where it stays flat
    // Just go to the dac and place a number into it that represents something
}

void PIDController (void) {
    // Need to go over the 3 dimentions
    // There are several passes, first I'll get it with all at the same power, and just based on elevation
    // then extend to other dimentions
    // then account for the vertical portion of the force from the 4 motors`
    
    // unsigned char newSettings[4] = {100, 100, 100, 100};// later all 4 will have their own setting
    // unsigned short averageReadings[4] = {100, 100, 100, 100};// later all 4 will have their own setting
    unsigned char newSetting = 100;// default
    char currentZ = pastReadings[0];
    char error = targetZ - currentZ;

    float proportional;
    float integral;
    float derivative;
    float controlSignal;
    


    if (readingsTaken < 2) {
        readingsTaken++;
        return;
    }

    proportional = PID_CONSTANT_P * error;

    // Integral term
    integralTerm += error;
    integral = PID_CONSTANT_I * integralTerm;

    if (OLD_READINGS >= 2) {
        derivative = PID_CONSTANT_D * (pastReadings[0] - pastReadings[1]);
    }

    controlSignal = proportional + integral - derivative;

    // Clamp to (0-200)
    if (controlSignal < -100)
        controlSignal = -100;
    newSetting += (unsigned char)(controlSignal);
    if (newSetting > 200)
        newSetting = 200;
    // D can just be instantanious based on 2 sets of readings??  // P can just be last set of them,,, I'm still not sure how I want to do it, I think P should go back like 10??
    // That can be adjusted, only one value needs to be retained for each run (per dimention)
    for (char i=0;i<MOTOR_COUNT;i++)
        updateMotor(i, newSetting);
}
