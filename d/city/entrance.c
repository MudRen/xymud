// entrance.c
#include <login.h>
#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "二楼雅座");
        set("long", @LONG

这里摆设讲究，用的餐具都是从景德镇运来。摆的桌椅都是红木的，
在光照之下反射出淡淡的光泽。推窗望去，长安城中心尽收眼底。
一群酒客推杯换盏，正喝的热闹。
LONG);

        set("exits", ([
		"down" : "/d/city/kezhan",
                "east" : "/d/wiz/system",
                "west" : __DIR__"spirit",
         ]) );
        set("no_time",1);
	set("objects", ([ /* sizeof() == 2 */
		"/d/city/npc/xiaoyi.c" : 1,
//                   "/u/snowtu/npc/amy" : 1,
	]));
        set("no_fight", 1);
        set("no_magic", 1);
        setup();
 	call_other( "/obj/board/bug_b", "???" );
}
