// command.h

#define CRA_PATH ({"/cmds/cra/", "/cmds/che/", "/cmds/adm/", "/cmds/arch/", "/cmds/wiz/", "/cmds/imm/", "/cmds/eld/", "/cmds/usr/","/cmds/std/"})
#define ADM_PATH ({"/cmds/adm/", "/cmds/arch/", "/cmds/wiz/", "/cmds/imm/", "/cmds/eld/", "/cmds/usr/","/cmds/std/"})
#define ARC_PATH ({"/cmds/arch/", "/cmds/wiz/", "/cmds/imm/", "/cmds/eld/", "/cmds/usr/","/cmds/std/"})
#define WIZ_PATH ({"/cmds/imm/", "/cmds/eld/", "/cmds/usr/", "/cmds/std/", "/cmds/wiz/"})
#define APR_PATH ({"/cmds/imm/", "/cmds/eld/", "/cmds/usr/", "/cmds/std/", "/cmds/wiz/"})
#define IMM_PATH ({"/cmds/imm/", "/cmds/eld/", "/cmds/usr/", "/cmds/std/"})
#define ELD_PATH ({"/cmds/eld/", "/cmds/usr/", "/cmds/std/"})
#define PLR_PATH ({"/cmds/std/", "/cmds/usr/"})
#define NPC_PATH ({"/cmds/std/"})

// These are command objects that will also be called in those
// non-player objects.

//#define TIME_TICK2 		(time()*60)
//#define TIME_TICK1 		(time()*60)
#define TIME_TICK 		0
#define TIME_TICK1 		((time()-0)*60)
#define TIME_TICK2 		(time()-0)
//#define TIME_TICK3 		(1177851156)*60
//#define TIME_TICK1 		((time()-890000000)*60)
//#define TIME_TICK 		((time()-1000000000)*60)
//#define TIME_TICK1 		((time()-1057442400)*60)
//#define TIME_TICK 		((time()-957542400)*60)

#define DROP_CMD		"/cmds/std/drop"
#define GET_CMD			"/cmds/std/get"
#define GO_CMD			"/cmds/std/go"
#define LOOK_CMD		"/cmds/std/look"
#define QUIT_CMD		"/cmds/usr/quit"
#define REMOVE_CMD              "/cmds/std/remove"
#define TELL_CMD		"/cmds/std/tell"
#define UPTIME_CMD		"/cmds/usr/uptime"
#define WHO_CMD			"/cmds/usr/who"
#define BJTIME_CMD	        "/cmds/usr/bjtime.c"
#define LEVELUP_CMD	        "/cmds/usr/levelup.c"

#define EXAMINE_CMD	        "/cmds/arch/examine"
