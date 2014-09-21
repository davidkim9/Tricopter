bool inFlight = 0;
bool armed = 0;

unsigned long previousTime = 0;
unsigned long currentTime = 0;
unsigned long dt = 0;

int motorAxisCommandRoll = 0;
int motorAxisCommandPitch = 0;
int motorAxisCommandYaw = 0;

bool stableMode = 0;

double targetThrottle, targetYaw, targetPitch, targetRoll;

double outputRollStable;
double outputPitchStable;
double outputYawStable;

double outputRoll;
double outputPitch;
double outputYaw;
