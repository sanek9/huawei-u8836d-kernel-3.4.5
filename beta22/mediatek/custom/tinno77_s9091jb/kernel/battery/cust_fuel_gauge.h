#include <mach/mt_typedefs.h>

#define BATTERY_LI_POLYMER	1

#define FGAUGE_VOLTAGE_FACTOR           2.44 // mV
#define FGAUGE_CURRENT_FACTOR           6.25 // uV/Rsns
#define FGAUGE_CURRENT_OFFSET_FACTOR    1.56 // uV/Rsns
#define FGAUGE_CAR_FACTOR               6.25 // uV/Rsns
#define FGAUGE_RSNS_FACTOR              0.02 // Ohm

//#define COMPASATE_OCV                   80 // mV for evb
#define COMPASATE_OCV                   40 // mV for phone

#define BATTERY_VOLTAGE_MINIMUM         3400
#define BATTERY_VOLTAGE_MAXIMUM         4200

#define BATTERY_CAPACITY_MAXIMUM        1800

#define TEMPERATURE_T0                  110
#define TEMPERATURE_T1                  0
#define TEMPERATURE_T2                  25
#define TEMPERATURE_T3                  50
#define TEMPERATURE_T                   255 // This should be fixed, never change the value

//#define BATT_CAPACITY                   1280
#define BATT_CAPACITY                   1700

#define ENABLE_SW_COULOMB_COUNTER       0 // 1 is enable, 0 is disable
//#define ENABLE_SW_COULOMB_COUNTER       1 // 1 is enable, 0 is disable

//#define FG_CURRENT_OFFSET_DISCHARGING 	31
#define FG_CURRENT_OFFSET_DISCHARGING 	0

#define FG_RESISTANCE 	20

#define FG_METER_RESISTANCE 	0
//#define FG_METER_RESISTANCE 	540 // current meter

//#define MAX_BOOTING_TIME_FGCURRENT	5*6 // 5 seconds, 6 points = 1s
#define MAX_BOOTING_TIME_FGCURRENT	1*10 // 10s

#if defined(CONFIG_POWER_EXT)
//#define OCV_BOARD_COMPESATE	32 //mV 
#define OCV_BOARD_COMPESATE	72 //mV 
#define R_FG_BOARD_BASE		1000
#define R_FG_BOARD_SLOPE	1000 //slope
#else
//#define OCV_BOARD_COMPESATE	0 //mV 
//#define OCV_BOARD_COMPESATE	48 //mV 
//#define OCV_BOARD_COMPESATE	25 //mV 
#define OCV_BOARD_COMPESATE	0 //mV 
#define R_FG_BOARD_BASE		1000
#define R_FG_BOARD_SLOPE	1000 //slope
//#define R_FG_BOARD_SLOPE	1057 //slope
//#define R_FG_BOARD_SLOPE	1075 //slope
#endif

#if (BATTERY_LI_POLYMER)
#define Q_MAX_POS_50	1800
#define Q_MAX_POS_25	1700
#define Q_MAX_POS_0	1367
#define Q_MAX_NEG_10	1193

#define Q_MAX_POS_50_H_CURRENT	1680
#define Q_MAX_POS_25_H_CURRENT	1580
#define Q_MAX_POS_0_H_CURRENT	952
#define Q_MAX_NEG_10_H_CURRENT	662

#else
#define Q_MAX_POS_50	1814
#define Q_MAX_POS_25	1800
#define Q_MAX_POS_0	1660
#define Q_MAX_NEG_10	1567

#define Q_MAX_POS_50_H_CURRENT	1780
#define Q_MAX_POS_25_H_CURRENT	1740
#define Q_MAX_POS_0_H_CURRENT	1470
#define Q_MAX_NEG_10_H_CURRENT	662

#endif


#define R_FG_VALUE 				20 // mOhm, base is 20
#define CURRENT_DETECT_R_FG	100  //10mA

#define OSR_SELECT_7			0

#define CAR_TUNE_VALUE			100 	//94 //1.00

/////////////////////////////////////////////////////////////////////
// <DOD, Battery_Voltage> Table
/////////////////////////////////////////////////////////////////////
typedef struct _BATTERY_PROFILE_STRUC
{
    kal_int32 percentage;
    kal_int32 voltage;
} BATTERY_PROFILE_STRUC, *BATTERY_PROFILE_STRUC_P;

typedef enum
{
    T1_0C,
    T2_25C,
    T3_50C
} PROFILE_TEMPERATURE;

#if (BATTERY_LI_POLYMER)
// T0 -10C
BATTERY_PROFILE_STRUC battery_profile_t0[] =
{
	{0  , 4180},
	{2  , 4093},
	{4  , 4071},
	{6  , 4049},
	{8  , 4028},
	{10 , 4008},
	{11 , 3998},
	{12 , 3994},
	{13 , 3986},
	{14 , 3980},
	{16 , 3956},
	{17 , 3933},
	{19 , 3909},
	{20 , 3903},
	{22 , 3888},
	{23 , 3885},
	{25 , 3870},
	{27 , 3861},
	{28 , 3851},
	{30 , 3837},
	{31 , 3834},
	{33 , 3818},
	{34 , 3808},
	{36 , 3797},
	{37 , 3793},
	{39 , 3782},
	{41 , 3771},
	{42 , 3764},  
	{44 , 3755}, 
	{45 , 3752},
	{47 , 3744},
	{48 , 3739},  
	{50 , 3734},
	{52 , 3727},
	{53 , 3721},
	{55 , 3715},
	{56 , 3714},
	{58 , 3707},
	{59 , 3703},
	{61 , 3699},
	{62 , 3697},
	{64 , 3693},
	{66 , 3690},
	{67 , 3688},
	{69 , 3685},
	{70 , 3684},
	{72 , 3682},
	{73 , 3678},
  {75 , 3675},
  {76 , 3672},
  {78 , 3667},
  {80 , 3660},
  {81 , 3657},
  {83 , 3648},
  {84 , 3643},
  {86 , 3632},
  {87 , 3629},
  {89 , 3617},
  {91 , 3608},
  {92 , 3604},
  {94 , 3595},
  {95 , 3584},
  {97 , 3562},
  {98 , 3510},
  {100, 3421},
  {100, 3303}

};      
        
// T1 0C
BATTERY_PROFILE_STRUC battery_profile_t1[] =
{
	{0  , 4180},
	{2  , 4093},
	{4  , 4071},
	{6  , 4049},
	{8  , 4028},
	{10 , 4008},
	{11 , 3998},
	{12 , 3994},
	{13 , 3986},
	{14 , 3980},
	{16 , 3956},
	{17 , 3933},
	{19 , 3909},
	{20 , 3903},
	{22 , 3888},
	{23 , 3885},
	{25 , 3870},
	{27 , 3861},
	{28 , 3851},
	{30 , 3837},
	{31 , 3834},
	{33 , 3818},
	{34 , 3808},
	{36 , 3797},
	{37 , 3793},
	{39 , 3782},
	{41 , 3771},
	{42 , 3764},  
	{44 , 3755}, 
	{45 , 3752},
	{47 , 3744},
	{48 , 3739},  
	{50 , 3734},
	{52 , 3727},
	{53 , 3721},
	{55 , 3715},
	{56 , 3714},
	{58 , 3707},
	{59 , 3703},
	{61 , 3699},
	{62 , 3697},
	{64 , 3693},
	{66 , 3690},
	{67 , 3688},
	{69 , 3685},
	{70 , 3684},
	{72 , 3682},
	{73 , 3678},
  {75 , 3675},
  {76 , 3672},
  {78 , 3667},
  {80 , 3660},
  {81 , 3657},
  {83 , 3648},
  {84 , 3643},
  {86 , 3632},
  {87 , 3629},
  {89 , 3617},
  {91 , 3608},
  {92 , 3604},
  {94 , 3595},
  {95 , 3584},
  {97 , 3562},
  {98 , 3510},
  {100, 3421},
  {100, 3303}

}; 
// T2 25C
BATTERY_PROFILE_STRUC battery_profile_t2[] =
{
	{0  , 4180},
	{2  , 4093},
	{4  , 4071},
	{6  , 4049},
	{8  , 4028},
	{10 , 4008},
	{11 , 3998},
	{12 , 3994},
	{13 , 3986},
	{14 , 3980},
	{16 , 3956},
	{17 , 3933},
	{19 , 3909},
	{20 , 3903},
	{22 , 3888},
	{23 , 3885},
	{25 , 3870},
	{27 , 3861},
	{28 , 3851},
	{30 , 3837},
	{31 , 3834},
	{33 , 3818},
	{34 , 3808},
	{36 , 3797},
	{37 , 3793},
	{39 , 3782},
	{41 , 3771},
	{42 , 3764},  
	{44 , 3755}, 
	{45 , 3752},
	{47 , 3744},
	{48 , 3739},  
	{50 , 3734},
	{52 , 3727},
	{53 , 3721},
	{55 , 3715},
	{56 , 3714},
	{58 , 3707},
	{59 , 3703},
	{61 , 3699},
	{62 , 3697},
	{64 , 3693},
	{66 , 3690},
	{67 , 3688},
	{69 , 3685},
	{70 , 3684},
	{72 , 3682},
	{73 , 3678},
  {75 , 3675},
  {76 , 3672},
  {78 , 3667},
  {80 , 3660},
  {81 , 3657},
  {83 , 3648},
  {84 , 3643},
  {86 , 3632},
  {87 , 3629},
  {89 , 3617},
  {91 , 3608},
  {92 , 3604},
  {94 , 3595},
  {95 , 3584},
  {97 , 3562},
  {98 , 3510},
  {100, 3421},
  {100, 3303}

}; 

// T3 50C
BATTERY_PROFILE_STRUC battery_profile_t3[] =
{
	{0  , 4180},
	{2  , 4093},
	{4  , 4071},
	{6  , 4049},
	{8  , 4028},
	{10 , 4008},
	{11 , 3998},
	{12 , 3994},
	{13 , 3986},
	{14 , 3980},
	{16 , 3956},
	{17 , 3933},
	{19 , 3909},
	{20 , 3903},
	{22 , 3888},
	{23 , 3885},
	{25 , 3870},
	{27 , 3861},
	{28 , 3851},
	{30 , 3837},
	{31 , 3834},
	{33 , 3818},
	{34 , 3808},
	{36 , 3797},
	{37 , 3793},
	{39 , 3782},
	{41 , 3771},
	{42 , 3764},  
	{44 , 3755}, 
	{45 , 3752},
	{47 , 3744},
	{48 , 3739},  
	{50 , 3734},
	{52 , 3727},
	{53 , 3721},
	{55 , 3715},
	{56 , 3714},
	{58 , 3707},
	{59 , 3703},
	{61 , 3699},
	{62 , 3697},
	{64 , 3693},
	{66 , 3690},
	{67 , 3688},
	{69 , 3685},
	{70 , 3684},
	{72 , 3682},
	{73 , 3678},
  {75 , 3675},
  {76 , 3672},
  {78 , 3667},
  {80 , 3660},
  {81 , 3657},
  {83 , 3648},
  {84 , 3643},
  {86 , 3632},
  {87 , 3629},
  {89 , 3617},
  {91 , 3608},
  {92 , 3604},
  {94 , 3595},
  {95 , 3584},
  {97 , 3562},
  {98 , 3510},
  {100, 3421},
  {100, 3303}

};              


#else
// T0 -10C
BATTERY_PROFILE_STRUC battery_profile_t0[] =
{
	{0  , 4180},
	{2  , 4160},
	{3  , 4142},
	{5  , 4127},
	{6  , 4112},
	{8  , 4097},
	{9  , 4083},
	{11 , 4071},
	{12 , 4057},
	{14 , 4045},
	{16 , 4030},
	{17 , 4019},
	{19 , 4007},
	{20 , 3996},
	{22 , 3984},
	{23 , 3975},
	{25 , 3965},
	{27 , 3955},
	{28 , 3944},
	{30 , 3935},
	{31 , 3926},
	{33 , 3918},
	{34 , 3909},
	{36 , 3898},
	{37 , 3887},
	{39 , 3873},
	{41 , 3859},
	{42 , 3848},  
	{44 , 3839}, 
	{45 , 3833},
	{47 , 3825},
	{48 , 3819},  
	{50 , 3814},
	{52 , 3808},
	{53 , 3804},
	{55 , 3800},
	{56 , 3795},
	{58 , 3792},
	{59 , 3789},
	{61 , 3787},
	{62 , 3784},
	{64 , 3781},
	{66 , 3778},
	{67 , 3776},
	{69 , 3775},
	{70 , 3770},
	{72 , 3764},
	{73 , 3760},
  {75 , 3753},
  {76 , 3747},
  {78 , 3743},
  {80 , 3739},
  {81 , 3734},
  {83 , 3725},
  {84 , 3718},
  {86 , 3711},
  {87 , 3704},
  {89 , 3691},
  {91 , 3686},
  {92 , 3684},
  {94 , 3679},
  {95 , 3662},
  {97 , 3613},
  {98 , 3535},
  {100, 3422},
  {100, 3303}

};      
        
// T1 0C
BATTERY_PROFILE_STRUC battery_profile_t1[] =
{
	{0  , 4180},
	{2  , 4160},
	{3  , 4142},
	{5  , 4127},
	{6  , 4112},
	{8  , 4097},
	{9  , 4083},
	{11 , 4071},
	{12 , 4057},
	{14 , 4045},
	{16 , 4030},
	{17 , 4019},
	{19 , 4007},
	{20 , 3996},
	{22 , 3984},
	{23 , 3975},
	{25 , 3965},
	{27 , 3955},
	{28 , 3944},
	{30 , 3935},
	{31 , 3926},
	{33 , 3918},
	{34 , 3909},
	{36 , 3898},
	{37 , 3887},
	{39 , 3873},
	{41 , 3859},
	{42 , 3848},  
	{44 , 3839}, 
	{45 , 3833},
	{47 , 3825},
	{48 , 3819},  
	{50 , 3814},
	{52 , 3808},
	{53 , 3804},
	{55 , 3800},
	{56 , 3795},
	{58 , 3792},
	{59 , 3789},
	{61 , 3787},
	{62 , 3784},
	{64 , 3781},
	{66 , 3778},
	{67 , 3776},
	{69 , 3775},
	{70 , 3770},
	{72 , 3764},
	{73 , 3760},
  {75 , 3753},
  {76 , 3747},
  {78 , 3743},
  {80 , 3739},
  {81 , 3734},
  {83 , 3725},
  {84 , 3718},
  {86 , 3711},
  {87 , 3704},
  {89 , 3691},
  {91 , 3686},
  {92 , 3684},
  {94 , 3679},
  {95 , 3662},
  {97 , 3613},
  {98 , 3535},
  {100, 3422},
  {100, 3303}
  

}; 
// T2 25C
BATTERY_PROFILE_STRUC battery_profile_t2[] =
{
	{0  , 4180},
	{2  , 4160},
	{3  , 4142},
	{5  , 4127},
	{6  , 4112},
	{8  , 4097},
	{9  , 4083},
	{11 , 4071},
	{12 , 4057},
	{14 , 4045},
	{16 , 4030},
	{17 , 4019},
	{19 , 4007},
	{20 , 3996},
	{22 , 3984},
	{23 , 3975},
	{25 , 3965},
	{27 , 3955},
	{28 , 3944},
	{30 , 3935},
	{31 , 3926},
	{33 , 3918},
	{34 , 3909},
	{36 , 3898},
	{37 , 3887},
	{39 , 3873},
	{41 , 3859},
	{42 , 3848},  
	{44 , 3839}, 
	{45 , 3833},
	{47 , 3825},
	{48 , 3819},  
	{50 , 3814},
	{52 , 3808},
	{53 , 3804},
	{55 , 3800},
	{56 , 3795},
	{58 , 3792},
	{59 , 3789},
	{61 , 3787},
	{62 , 3784},
	{64 , 3781},
	{66 , 3778},
	{67 , 3776},
	{69 , 3775},
	{70 , 3770},
	{72 , 3764},
	{73 , 3760},
  {75 , 3753},
  {76 , 3747},
  {78 , 3743},
  {80 , 3739},
  {81 , 3734},
  {83 , 3725},
  {84 , 3718},
  {86 , 3711},
  {87 , 3704},
  {89 , 3691},
  {91 , 3686},
  {92 , 3684},
  {94 , 3679},
  {95 , 3662},
  {97 , 3613},
  {98 , 3535},
  {100, 3422},
  {100, 3303}
  

}; 

// T3 50C
BATTERY_PROFILE_STRUC battery_profile_t3[] =
{
	{0  , 4180},
	{2  , 4160},
	{3  , 4142},
	{5  , 4127},
	{6  , 4112},
	{8  , 4097},
	{9  , 4083},
	{11 , 4071},
	{12 , 4057},
	{14 , 4045},
	{16 , 4030},
	{17 , 4019},
	{19 , 4007},
	{20 , 3996},
	{22 , 3984},
	{23 , 3975},
	{25 , 3965},
	{27 , 3955},
	{28 , 3944},
	{30 , 3935},
	{31 , 3926},
	{33 , 3918},
	{34 , 3909},
	{36 , 3898},
	{37 , 3887},
	{39 , 3873},
	{41 , 3859},
	{42 , 3848},  
	{44 , 3839}, 
	{45 , 3833},
	{47 , 3825},
	{48 , 3819},  
	{50 , 3814},
	{52 , 3808},
	{53 , 3804},
	{55 , 3800},
	{56 , 3795},
	{58 , 3792},
	{59 , 3789},
	{61 , 3787},
	{62 , 3784},
	{64 , 3781},
	{66 , 3778},
	{67 , 3776},
	{69 , 3775},
	{70 , 3770},
	{72 , 3764},
	{73 , 3760},
  {75 , 3753},
  {76 , 3747},
  {78 , 3743},
  {80 , 3739},
  {81 , 3734},
  {83 , 3725},
  {84 , 3718},
  {86 , 3711},
  {87 , 3704},
  {89 , 3691},
  {91 , 3686},
  {92 , 3684},
  {94 , 3679},
  {95 , 3662},
  {97 , 3613},
  {98 , 3535},
  {100, 3422},
  {100, 3303}
  

};              

#endif
// battery profile for actual temperature. The size should be the same as T1, T2 and T3
BATTERY_PROFILE_STRUC battery_profile_temperature[] =
{
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},
	  {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},
	  {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0}
    
};    

/////////////////////////////////////////////////////////////////////
// <Rbat, Battery_Voltage> Table
/////////////////////////////////////////////////////////////////////
typedef struct _R_PROFILE_STRUC
{
    kal_int32 resistance; // Ohm
    kal_int32 voltage;
} R_PROFILE_STRUC, *R_PROFILE_STRUC_P;


// T0 -10C
R_PROFILE_STRUC r_profile_t0[] =
{
	{173    ,  4180},
	{165    ,  4160},
	{165    ,  4142},
	{168    ,  4127},
	{168    ,  4112},
	{165    ,  4097},
	{170    ,  4083},
	{173    ,  4071},
	{173    ,  4057},
	{175    ,  4045},
	{175    ,  4030},
	{183    ,  4019},
	{185    ,  4007},
	{188    ,  3996},
	{185    ,  3984},
	{190    ,  3975},
	{193    ,  3965},
	{195    ,  3955},
	{193    ,  3944},
	{198    ,  3935},
	{203    ,  3926},
	{203    ,  3918},
	{205    ,  3909},
	{208    ,  3898},
	{203    ,  3887},
	{193    ,  3873},
	{185    ,  3859},
	{175    ,  3848},  
	{175    ,  3839}, 
	{180    ,  3833},
	{178    ,  3825},
	{178    ,  3819},  
	{178    ,  3814},
	{178    ,  3808},
	{173    ,  3804},
	{178    ,  3800},
	{175    ,  3795},
	{178    ,  3792},
	{180    ,  3789},
	{183    ,  3787},
	{180    ,  3784},
	{183    ,  3781},
	{183    ,  3778},
	{180    ,  3776},
	{185    ,  3775},
	{180    ,  3770},
	{175    ,  3764},
	{175    ,  3760},
  {173    ,  3753},
  {165    ,  3747},
  {170    ,  3743},
  {173    ,  3739},
  {178    ,  3734},
  {173    ,  3725},
  {170    ,  3718},
  {175    ,  3711},
  {180    ,  3704},
  {175    ,  3691},
  {175    ,  3686},
  {183    ,  3684},
  {190    ,  3679},
  {198    ,  3662},
  {200    ,  3613},
  {205    ,  3535},
  {230    ,  3422},
  {260    ,  3303}

};

// T1 0C
R_PROFILE_STRUC r_profile_t1[] =
{
	{173    ,  4180},
	{165    ,  4160},
	{165    ,  4142},
	{168    ,  4127},
	{168    ,  4112},
	{165    ,  4097},
	{170    ,  4083},
	{173    ,  4071},
	{173    ,  4057},
	{175    ,  4045},
	{175    ,  4030},
	{183    ,  4019},
	{185    ,  4007},
	{188    ,  3996},
	{185    ,  3984},
	{190    ,  3975},
	{193    ,  3965},
	{195    ,  3955},
	{193    ,  3944},
	{198    ,  3935},
	{203    ,  3926},
	{203    ,  3918},
	{205    ,  3909},
	{208    ,  3898},
	{203    ,  3887},
	{193    ,  3873},
	{185    ,  3859},
	{175    ,  3848},  
	{175    ,  3839}, 
	{180    ,  3833},
	{178    ,  3825},
	{178    ,  3819},  
	{178    ,  3814},
	{178    ,  3808},
	{173    ,  3804},
	{178    ,  3800},
	{175    ,  3795},
	{178    ,  3792},
	{180    ,  3789},
	{183    ,  3787},
	{180    ,  3784},
	{183    ,  3781},
	{183    ,  3778},
	{180    ,  3776},
	{185    ,  3775},
	{180    ,  3770},
	{175    ,  3764},
	{175    ,  3760},
  {173    ,  3753},
  {165    ,  3747},
  {170    ,  3743},
  {173    ,  3739},
  {178    ,  3734},
  {173    ,  3725},
  {170    ,  3718},
  {175    ,  3711},
  {180    ,  3704},
  {175    ,  3691},
  {175    ,  3686},
  {183    ,  3684},
  {190    ,  3679},
  {198    ,  3662},
  {200    ,  3613},
  {205    ,  3535},
  {230    ,  3422},
  {260    ,  3303}

}; 

// T2 25C
R_PROFILE_STRUC r_profile_t2[] =
{
	{173    ,  4180},
	{165    ,  4160},
	{165    ,  4142},
	{168    ,  4127},
	{168    ,  4112},
	{165    ,  4097},
	{170    ,  4083},
	{173    ,  4071},
	{173    ,  4057},
	{175    ,  4045},
	{175    ,  4030},
	{183    ,  4019},
	{185    ,  4007},
	{188    ,  3996},
	{185    ,  3984},
	{190    ,  3975},
	{193    ,  3965},
	{195    ,  3955},
	{193    ,  3944},
	{198    ,  3935},
	{203    ,  3926},
	{203    ,  3918},
	{205    ,  3909},
	{208    ,  3898},
	{203    ,  3887},
	{193    ,  3873},
	{185    ,  3859},
	{175    ,  3848},  
	{175    ,  3839}, 
	{180    ,  3833},
	{178    ,  3825},
	{178    ,  3819},  
	{178    ,  3814},
	{178    ,  3808},
	{173    ,  3804},
	{178    ,  3800},
	{175    ,  3795},
	{178    ,  3792},
	{180    ,  3789},
	{183    ,  3787},
	{180    ,  3784},
	{183    ,  3781},
	{183    ,  3778},
	{180    ,  3776},
	{185    ,  3775},
	{180    ,  3770},
	{175    ,  3764},
	{175    ,  3760},
  {173    ,  3753},
  {165    ,  3747},
  {170    ,  3743},
  {173    ,  3739},
  {178    ,  3734},
  {173    ,  3725},
  {170    ,  3718},
  {175    ,  3711},
  {180    ,  3704},
  {175    ,  3691},
  {175    ,  3686},
  {183    ,  3684},
  {190    ,  3679},
  {198    ,  3662},
  {200    ,  3613},
  {205    ,  3535},
  {230    ,  3422},
  {260    ,  3303}

};

// T3 50C
R_PROFILE_STRUC r_profile_t3[] =
{
	{173    ,  4180},
	{165    ,  4160},
	{165    ,  4142},
	{168    ,  4127},
	{168    ,  4112},
	{165    ,  4097},
	{170    ,  4083},
	{173    ,  4071},
	{173    ,  4057},
	{175    ,  4045},
	{175    ,  4030},
	{183    ,  4019},
	{185    ,  4007},
	{188    ,  3996},
	{185    ,  3984},
	{190    ,  3975},
	{193    ,  3965},
	{195    ,  3955},
	{193    ,  3944},
	{198    ,  3935},
	{203    ,  3926},
	{203    ,  3918},
	{205    ,  3909},
	{208    ,  3898},
	{203    ,  3887},
	{193    ,  3873},
	{185    ,  3859},
	{175    ,  3848},  
	{175    ,  3839}, 
	{180    ,  3833},
	{178    ,  3825},
	{178    ,  3819},  
	{178    ,  3814},
	{178    ,  3808},
	{173    ,  3804},
	{178    ,  3800},
	{175    ,  3795},
	{178    ,  3792},
	{180    ,  3789},
	{183    ,  3787},
	{180    ,  3784},
	{183    ,  3781},
	{183    ,  3778},
	{180    ,  3776},
	{185    ,  3775},
	{180    ,  3770},
	{175    ,  3764},
	{175    ,  3760},
  {173    ,  3753},
  {165    ,  3747},
  {170    ,  3743},
  {173    ,  3739},
  {178    ,  3734},
  {173    ,  3725},
  {170    ,  3718},
  {175    ,  3711},
  {180    ,  3704},
  {175    ,  3691},
  {175    ,  3686},
  {183    ,  3684},
  {190    ,  3679},
  {198    ,  3662},
  {200    ,  3613},
  {205    ,  3535},
  {230    ,  3422},
  {260    ,  3303}

};

// r-table profile for actual temperature. The size should be the same as T1, T2 and T3
R_PROFILE_STRUC r_profile_temperature[] =
{
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},
	  {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},
	  {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},   
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0}
    
};    


int fgauge_get_saddles(void);
BATTERY_PROFILE_STRUC_P fgauge_get_profile(kal_uint32 temperature);

int fgauge_get_saddles_r_table(void);
R_PROFILE_STRUC_P fgauge_get_profile_r_table(kal_uint32 temperature);
