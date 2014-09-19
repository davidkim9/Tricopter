#define MINCOMMAND 1000
#define MIDCOMMAND 1500
#define MAXCOMMAND 2000

#define MINTHRUST 1150

#define MIN_THROTTLE 1200
#define MAX_THROTTLE 1820
#define MIN_RUDDER 1150 //1130 , match the midpoints so the zero is at 1500
#define MAX_RUDDER 1850
#define MIN_AILERON 1180
#define MAX_AILERON 1820 //1910
#define MIN_ELEVATOR 1180
#define MAX_ELEVATOR 1820 //1860
bool inFlight = 0;
bool armed = 0;

unsigned long previousTime = 0;
unsigned long currentTime = 0;
unsigned long dt = 0;

int motorAxisCommandRoll = 0;
int motorAxisCommandPitch = 0;
int motorAxisCommandYaw = 0;

double targetThrottle, targetYaw, targetPitch, targetRoll;

double outputRollStable;
double outputPitchStable;
double outputYawStable;

double outputRoll;
double outputPitch;
double outputYaw;
