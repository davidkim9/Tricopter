//RC Input Pins
#define AILERON_IN_PIN 3
#define ELEVATOR_IN_PIN 4
#define THROTTLE_IN_PIN 6
#define RUDDER_IN_PIN 7
#define AUX1_IN_PIN 8
#define AUX2_IN_PIN 12

//Motor Output Pins
#define YAW_MOTOR_OUT_PIN 5
#define LEFT_MOTOR_OUT_PIN 9
#define RIGHT_MOTOR_OUT_PIN 10
#define REAR_MOTOR_OUT_PIN 11

#define LED_PIN 13

//RC Input Pins
#define AILERON_TRIM -14
#define ELEVATOR_TRIM -6
#define THROTTLE_TRIM 0
#define RUDDER_TRIM -8

//Exponential x^EXPO
#define EXPO_ROLL_PITCH 1.0
#define EXPO_YAW 1.0

//Microseconds, 5 seconds = 5000000
#define MAX_ARM_TIME 5000000

//PID VALUES
#define ROLL_PITCH_P 1.4
#define ROLL_PITCH_I 0.8
#define ROLL_PITCH_D -4.0
#define ROLL_PITCH_P_GUARD 500
#define ROLL_PITCH_I_GUARD 200

#define YAW_P 7.0
#define YAW_I 0.1
#define YAW_D 0.0

#define SERVO_FILTER 0.65

//Remote signal timeout: 1.5 seconds
#define SIGNAL_TIMEOUT 1500000

//PWM Values
#define MINCOMMAND 1000
#define MIDCOMMAND 1500
#define MAXCOMMAND 2000

#define MINTHRUST 1150

//1130 , match the midpoints so the zero is around 1500
#define MIN_THROTTLE 1200
#define MAX_THROTTLE 1820
#define MIN_RUDDER 1150
#define MAX_RUDDER 1850
#define MIN_AILERON 1180
#define MAX_AILERON 1820
#define MIN_ELEVATOR 1180
#define MAX_ELEVATOR 1820

#define MIN_AUX1 1100
#define MAX_AUX1 1900

//1000/61.0
