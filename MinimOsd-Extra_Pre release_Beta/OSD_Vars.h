/*Panels variables*/
//Will come from APM telem port

static float	nav_roll = 0; // Current desired roll in degrees
static float  nav_pitch = 0; // Current desired pitch in degrees
static int16_t	nav_bearing = 0; // Current desired heading in degrees
static int16_t	    wp_target_bearing = 0; // Bearing to current MISSION/target in degrees
static int8_t       wp_target_bearing_rotate_int = 0;
static uint16_t     wp_dist = 0; // Distance to active MISSION in meters
static uint8_t      wp_number = 0; // Current waypoint number
static float	alt_error = 0; // Current altitude error in meters
static float aspd_error = 0; // Current airspeed error in meters/second
static float	xtrack_error = 0; // Current crosstrack error on x-y plane in meters

static uint8_t base_mode=0;
static bool motor_armed = 0;

static int16_t      chan1_raw = 0;
static int16_t      chan2_raw = 0;
static int16_t      chan1_raw_middle = 0;
static int16_t      chan2_raw_middle = 0;
static uint8_t      ch_toggle = 0;
static boolean      osd_set = 0;
static boolean      switch_mode = 0;
static boolean      pal_ntsc = 0;

static int8_t       setup_menu = 0;
static float        converts = 0;
static float        converth = 0;
static uint8_t      overspeed = 0;
static uint8_t      stall = 0;
static uint8_t      battv = 0;                //Battery warning voltage - units Volt *10 
//static int        battp = 0;

static uint8_t      spe = 0;
static uint8_t      high = 0;
static float        osd_vbat_A = 0;                 // Battery A voltage in milivolt
static int16_t      osd_curr_A = 0;                 // Battery A current
static int8_t       osd_battery_remaining_A = 0;    // 0 to 100 <=> 0 to 1000
//static uint8_t      osd_battery_pic_A = 0xb4;       // picture to show battery remaining
//static float      osd_vbat_B = 0;               // voltage in milivolt
//static float      osd_curr_B = 0;                 // Battery B current
//static uint16_t   osd_battery_remaining_B = 0;  // 0 to 100 <=> 0 to 1000
//static uint8_t    osd_battery_pic_B = 0xb4;     // picture to show battery remaining
static float        start_Time = -1.0;
static uint8_t      osd_mode = 0;                   // Navigation mode from RC AC2 = CH5, APM = CH8
static uint8_t      osd_nav_mode = 0;               // Navigation mode from RC AC2 = CH5, APM = CH8
static unsigned long text_timer = 0;
static unsigned long warning_timer =0;

static uint8_t      warning_type = 0;
static uint8_t      last_warning = 0;
static uint8_t      warning = 0;
static uint8_t      osd_off_switch = 0;
static uint8_t      osd_switch_last = 100;
static unsigned long         osd_switch_time = 0;
static float        osd_climb = 0;

static float        osd_lat = 0;                    // latidude
static float        osd_lon = 0;                    // longitude
static uint8_t      osd_satellites_visible = 0;     // number of satelites
static uint8_t      osd_fix_type = 0;               // GPS lock 0-1=no fix, 2=2D, 3=3D

static uint8_t      osd_got_home = 0;               // tels if got home position or not
static float        osd_home_lat = 0;               // home latidude
static float        osd_home_lon = 0;               // home longitude
static float        osd_home_alt = 0; 
static long         osd_home_distance = 0;          // distance from home
static uint8_t      osd_home_direction;             // Arrow direction pointing to home (1-16 to CW loop)

static int8_t       osd_pitch = 0;                  // pitch from DCM
static int8_t       osd_roll = 0;                   // roll from DCM
static int8_t       osd_yaw = 0;                    // relative heading form DCM
static float        osd_heading = 0;                // ground course heading from GPS

static float        osd_alt = 0;                    // altitude
static float        osd_airspeed = -1;              // airspeed
static float        osd_windspeed = 0;
static float        osd_windspeedz = 0;
static float        osd_winddirection = 0;
static int8_t       osd_wind_arrow_rotate_int;

static uint8_t      osd_alt_cnt = 0;              // counter for stable osd_alt
static float        osd_alt_prev = 0;             // previous altitude

static float        osd_groundspeed = 0;            // ground speed
static uint16_t     osd_throttle = 0;               // throtle

//MAVLink session control
static boolean      mavbeat = 0;
static float        lastMAVBeat = 0;
static boolean      waitingMAVBeats = 1;
static uint8_t      apm_mav_type;
static uint8_t      apm_mav_system; 
static uint8_t      apm_mav_component;
static boolean      enable_mav_request = 0;

static const uint8_t npanels = 2;
static uint8_t panel = 0; 
// Panel BIT registers
byte panA_REG[npanels] = {0b00000000};
byte panB_REG[npanels] = {0b00000000};
byte panC_REG[npanels] = {0b00000000};
byte panD_REG[npanels] = {0b00000000};

byte modeScreen = 0; //NTSC:0, PAL:1

//byte SerCMD1 = 0;
//byte SerCMD2 = 0;

// First 8 panels and their X,Y coordinate holders
byte panCenter_XY[2][npanels]; // = { 13,7,0 };
byte panPitch_XY[2][npanels]; // = { 11,1 };
byte panRoll_XY[2][npanels]; // = { 23,7 };
byte panBatt_A_XY[2][npanels]; // = { 23,1 };
//byte panBatt_B_XY[2]; // = { 23,3 };
byte panGPSats_XY[2][npanels]; // = { 2,12 };
byte panGPL_XY[2][npanels]; // = { 2,11 };
byte panGPS_XY[2][npanels]; // = { 2,13 };
byte panBatteryPercent_XY[2][npanels];


//Second 8 set of panels and their X,Y coordinate holders
byte panRose_XY[2][npanels]; // = { 16,13 };
byte panHeading_XY[2][npanels]; // = { 16,12 };
byte panMavBeat_XY[2][npanels]; // = { 2,10 };
byte panHomeDir_XY[2][npanels]; // = { 0,0 };
byte panHomeDis_XY[2][npanels]; // = { 0,0 };
byte panWPDir_XY[2][npanels]; // = { 27,12 };
byte panWPDis_XY[2][npanels]; // = { 23,11 };
byte panTime_XY[2][npanels];


// Third set of panels and their X,Y coordinate holders
byte panCur_A_XY[2][npanels]; // = { 23,1 };
//byte panCur_B_XY[2]; // = { 23,3 };
byte panAlt_XY[2][npanels]; // = { 0,0 };
byte panHomeAlt_XY[2][npanels]; // = { 0,0 };
byte panVel_XY[2][npanels]; // = { 0,0 };
byte panAirSpeed_XY[2][npanels]; // = { 0,0 };
byte panThr_XY[2][npanels]; // = { 0,0 };
byte panFMod_XY[2][npanels]; // = { 0,0 };
byte panHorizon_XY[2][npanels]; // = {8,centercalc}

// Third set of panels and their X,Y coordinate holders
byte panWarn_XY[2][npanels];
//byte panOff_XY[2];
byte panWindSpeed_XY[2][npanels];
byte panClimb_XY[2][npanels];
byte panTune_XY[2][npanels];
//byte panSetup_XY[2];
byte panRSSI_XY[2][npanels];

//*************************************************************************************************************
//rssi varables
static uint8_t  rssipersent = 0;
static uint8_t  rssical = 0;
static uint8_t  osd_rssi = 0; //raw value from mavlink
static int16_t  rssi = -99; // scaled value 0-100%
static bool rssiraw_on = false; // 0- display scale value | 1- display raw value
//static uint8_t  radio_setup_flag = 0;
static uint16_t  ch_raw = 0;
static uint16_t  osd_chan5_raw = 1000;
static uint16_t  osd_chan6_raw = 1000;
static uint16_t  osd_chan7_raw = 1000;
static uint16_t  osd_chan8_raw = 1000;
