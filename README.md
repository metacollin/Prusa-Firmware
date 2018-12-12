# Prusa Alternative Firmware

**In case someone manages to stumble upon this in the next 24 hours before I finish, the readme is only half done.  I need to go to bed for now =P.**

## What is this?

This project grew out of my own fairly modest tinkering of the stock Prusa MK3 firmware.  This firmware is by no means 'better' than Prusa Research's own stock firmware, nor will the average user gain any benefit from using it.  

If you want greater control over some of the more advanced and low level features of your printer, or would like a more generalized firmware with certain bugs fixed that are only bugs if you have a non-standard printer configuration, then it might be worth your time to take a look at this firmware.  

A quick example of what I mean:  The stock firmware's XYZ Calibration does not respect the `#define INVERT_<X,Y,Z or E>_AXIS <...>` lines in `Configuration_prusa.h`.  Which is fine - the MK3 doesn't invert any of its X, Y, or Z axes so it doesn't really matter.  

However, if your printer DOES invert one of the axes, then it definitely will be a problem with the stock firmware, but not in this firmware.  

I try to keep this relatively up-to-date with the latest development version of the firmware, but it will likely be a cautious few commits behind, as this is the firmware I use day to day on my own printer, and only push a new update that pulls in the latest Prusa changes after I know it doesn't break anything (or at least, not obviously ;)  ).


## Unofficial Nonstandard Gcodes

The primary enhancement in this Firmware are a number of new TMC stepper driver related gcodes.  Please understand that I just made these up, these gcodes are completely unofficial and are not in any spec, and never will be.  They work with this firmware and only this firmware, and if they exist at all in other firmwares, they almost certainly do something very different.  

**Note 1:** Any gcodes that change motor settings are applied immediately, so you do not need to call M910 (tmc2130_init in the stock firwmare) at all.  In fact, you don't even have to pause - all settings, even the microstepping resolution, can be changed during a print without issue.  

**Note 2:** All set gcodes double as print gcodes.  If you issue one of the set gcodes but without any arguments, it will print the current values without altering them.  Even when setting a value, it will still print the updated values afterwards to confirm the changes were applied. 


* `M910 - Handy help command that will print out all of the motor related gcodes, how to use them, and what they do.`
* `M911 [XYZE]int - Set TMC2130 holding currents.`
* `M912 [XYZE]int - Set TMC2130 running currents.`
* `M913 - Print all TMC2130 currents at once.`
* `M914 - Set normal mode.`
* `M915 - Set silent mode.`
* `M916 [XYZE]int - Set running stallguard threshold.`
* `M919 - Print all stallguard values at once.`
* `M922 [XYZE]int - Set TMC2130 homing currents.`
* `M926 [XYZE]int - Set TMC2130 homing stallguard threshold.`
* `M930 [SETB]int - Set Exturder H[S]art, H[E]ND, [T]OFF, and [B]LANKING TIME(TBL).`
* `M931 [SETB]int - Set XYZ H[S]art, H[E]ND, [T]OFF, and [B]LANKING TIME(TBL).`
* `M932 [ARTF]int - Set Exturder PWM_[A]mpl, PWM_g[R]ad, PWM_au[T]o, PWM_[F]req.`
* `M350 [XYZE]int - Set microstep mode.  Valid modes: 1 (full step), 2, 4, 8, 16, 32, 64, 128.`
* `M361 [XYZE]1|0 - Toggle 256 microstep Interpolation. 1 = ON, 0 = OFF.`
* `M360 - Print detailed table of every single setting for every single axis.`

Expect more codes to be added in the future. 

For now, none of these settings are stored in the EEPROM so will not persist over a reset.  You'll need to change them in `Configuration_prusa.h` and recompile to permanently change them.  This serves two purposes:  you can easily return to a known good configuration after a reset, and to make sure that one can flash the stock firmware back to the printer without needing to erase the EEPROM as well (and recalibrate everything, etc. etc.).

## Tweaks & Fixes

This is not an exhaustive list.  You can find actual areas where I have changed or added code by searching for the `[MC]` tag with your favorite text editor, IDE, or directly on Github.


1. The minimum print temperature has been reduced from 15°C to 5°C.  We're all adults here, we can handle this responsibility.
2. There is a less annoying warning message upon boot that will auto clear itself instead of requiring you to push a button.
3. `Configuration_prusa.h` is symlinked to the correct variant, and only the MK3 varient is supported.
4. `Configuration_prusa.h` has been reworked in some sections to make it easier to customize various aspects and explain what more things actually do.  Also, all deadweight (code that has no effect) has been removed from the config file as well.
  * Completely rewritten TMC driver section:
  ```c++
  // =========== Microstepping Resolution ===========================================
  //                              {  X,   Y,   Z,   E}
  #define TMC2130_USTEPS   		      16,  16,  16,  32  // Microstepping mode
  #define TMC2130_STEP_INTERP     {  1,   1,   1,   1} // 256 microstep interpolation 
  // ================================================================================
  
  
  // =========== PWM Chopper Config ========================================
  //                          {  X,   Y,   Z,   E}
  #define TMC2130_PWM_GRAD		{  2,   2,   4,   4} // [MC] Stock Values
  #define TMC2130_PWM_AMPL		{230, 235, 200, 240} // [MC] Stock Values
  #define TMC2130_PWM_AUTO 		{  1,   1,   1,   1} // [MC] Stock Values
  #define TMC2130_PWM_FREQ 		{  2,   2,   2,   2} // [MC] Stock Values
  
  #define TMC2130_TPWMTHRS  0     
  // These two settings do nothing unless TMC2130_TPWMTHRS isn't 0.  
  #define TMC2130_TCOOLTHRS        430, 430, 500, 500  // [MC] Stock Values
  #define TMC2130_THIGH     0  
  // =======================================================================
  
  
  // =========== Stallguard Config ===============================================
  // [MC] The SG_THRS sets how large a load triggers a stall.  
  // [MC] Valid range is -64 (small load) to 63 (heavy load/crash)
  #define TMC2130_SG_HOMING	1      // stallguard homing
  //                              {  X,   Y,   Z,   E}
  #define TMC2130_HOME_SG_THRS _sg(  3,   3,   4,   3) // [MC] Homing threshold
  #define TMC2130_SG_THRS 	   _sg(  3,   3,   4,   3) // [MC] Printing threshold
  // =============================================================================
  
  
  // =========== Motor Currents ============================================
  // [MC] Values are scaling factors, not milliamps.
  // For a 0.22 Ohm Rsense resistor (Einsy RAMBO), actual RMS currents are:
  /*                                          value+1
     For value < 31, current in milliamps =  –––––––– * 0.53
  										      32
  
                                             value-31
     For value > 31, current in milliamps = ––––––––– * 0.943
                                                32
  */
  //                              {  X,   Y,   Z,   E}
  #define TMC2130_CURRENTS_HOME 	{  8,  10,  20,  18}
  #define TMC2130_CURRENTS 		    { 16,  20,  35,  30}
  #define TMC2130_UNLOAD_CURRENT                   12
  // =======================================================================
  
  
  // =========== SpreadCycle Config ===================
  //                                 X,   Y,   Z,   E
  #define TMC2130_TOFF 			         3,   3,   3,   3
  #define TMC2130_HSTART			       5,   5,   5,   5
  #define TMC2130_HEND               1,   1,   1,   1
  #define TMC2130_BLANK_TIME         2,   2,   2,   2
  // =================================================
  
  // =========== Miscellaneous & Debug ==========================================
  #define TMC2130_STEALTH_Z
  #define TMC2130_SERVICE_CODES_M910_M918 // [MC] Also enables unofficial gcodes.
  #define LINEARITY_CORRECTION
  #define TMC2130_LINEARITY_CORRECTION
  #define TMC2130_LINEARITY_CORRECTION_XYZ
  #define TMC2130_VARIABLE_RESOLUTION 
  #define TMC2130_CHOP_MODE 0 		// 0 = spreadCycle
  #define TMC2130_RANDOM_OFF_TIME 0 	// 0 = off
  #define TMC2130_FAST_DECAY3 0 		// Not used in spreadCycle mode
  //#define TMC2130_DEBUG
  //#define TMC2130_DEBUG_WR
  //#define TMC2130_DEBUG_RD
  // ============================================================================
  ```
