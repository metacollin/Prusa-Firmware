// NOTE:  These are settings for my [metacollin's] custom MK3 which has a lot of weird stuff going on.
// This file is here for my own convenience, but don't try to use this config - it won't work with
// any off-the-shelf prusa printer

#include "variants/1_75mm_MK3-EINSy10a-E3Dv6full.h"

#undef  DEFAULT_AXIS_STEPS_PER_UNIT
#define DEFAULT_AXIS_STEPS_PER_UNIT   {100,100,3200/8,528}

#undef TMC2130_USTEPS
#define TMC2130_USTEPS        16,  16,  16,  32  // Microstepping mode

#undef INVERT_Y_DIR
#define INVERT_Y_DIR 1


#undef INVERT_E0_DIR
#define INVERT_E0_DIR 1

#undef Y_MIN_POS
#define Y_MIN_POS -8

//#undef Z_MAX_POS
//#define Z_MAX_POS 215

#undef DEFAULT_SAFETYTIMER_TIME_MINS
#define DEFAULT_SAFETYTIMER_TIME_MINS 180

#undef MINTEMP_MINAMBIENT
#define MINTEMP_MINAMBIENT      15    // [MC] 25->15, equals 5C

#undef MINTEMP_MINAMBIENT_RAW
#define MINTEMP_MINAMBIENT_RAW  1007  // [MC] 978->1007, equals 5C. Raw value increases as the temperature decreases


#undef TMC2130_CURRENTS_HOME
#define TMC2130_CURRENTS_HOME   { 12,  20,  30,  18}

#undef TMC2130_CURRENTS
#define TMC2130_CURRENTS        { 16,  20,  35,  30}

#undef BED_MAXTEMP
#define BED_MAXTEMP 140

#undef HEATER_0_MINTEMP
#define HEATER_0_MINTEMP 12

#undef TEMP_RUNAWAY_BED_HYSTERESIS
#define TEMP_RUNAWAY_BED_HYSTERESIS 2

#undef TEMP_RUNAWAY_BED_TIMEOUT
#define TEMP_RUNAWAY_BED_TIMEOUT 1800

#undef TEMP_RUNAWAY_EXTRUDER_TIMEOUT
#define TEMP_RUNAWAY_EXTRUDER_TIMEOUT 180

#undef HEATER_0_MAXTEMP
#define HEATER_0_MAXTEMP 410

#undef DEFAULT_Kp
#undef DEFAULT_Ki
#undef DEFAULT_Kd
#define  DEFAULT_Kp 21.70
#define  DEFAULT_Ki 1.60
#define  DEFAULT_Kd 73.76

#undef TEMP_SENSOR_0
#define TEMP_SENSOR_0 247

#undef FANCHECK
