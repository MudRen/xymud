//changan city
// Cracked by 凌惊雪 1-3-2003

inherit ROOM;

void create ()
{
        set ("short", "崇明大街");
        set ("long", @LONG
你走在一条宽阔的石板大街上，往东就快要出城了，西面就快到城中
心了，可以看到一个很大的广场，人来人往唏唏嚷嚷，热闹非凡。
LONG);

        set("exits", 
        ([ //sizeof() == 4
		"south" : __DIR__"yunbitian",
                "north" : __DIR__"shenhoufu",
                "east" : __DIR__"congming2",
                "west" : __DIR__"center",
        ]));

        set("objects", 
        ([ //sizeof() == 1
//                __DIR__"npc/libai" : 1,
        ]));
        set("outdoors", "luoyang");
	set("no_clean_up", 0);
        setup();
	replace_program(ROOM);
}


