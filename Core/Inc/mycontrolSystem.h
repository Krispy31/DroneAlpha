/*
 * controlSystem.h
 *
 *  Created on: Feb 13, 2025
 *      Author: crist
 */

#ifndef INC_MYCONTROLSYSTEM_H_
#define INC_MYCONTROLSYSTEM_H_

typedef enum MotorNumber {
	MOTOR_ZERO,
	MOTOR_ONE,
	MOTOR_TWO,
	MOTOR_THREE,
	MOTOR_COUNT
}MotorNumber;



static void updateReadings (char);

void addReading(char reading);

void initMotors (void);

void PIDController (void);

void updateMotor(MotorNumber, unsigned char);

#endif /* INC_MYCONTROLSYSTEM_H_ */
