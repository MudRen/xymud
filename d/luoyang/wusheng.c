//changan city
// Cracked by 凌惊雪 1-3-2003

inherit ROOM;

void create ()
{
        set ("short", "武圣祠");
        set ("long", @LONG
这里始终是香火缭绕，台上供奉着一尊威严的神像。然来
当地居民特地将保护本地区的门派掌门人的神像供奉在这
里,以祈求百姓的安居乐业。

LONG);

        set("exits", 
        ([ //sizeof() == 4
                "west" : __DIR__"qianyuan2",
        ]));

        set("objects", 
        ([ //sizeof() == 1
//               __DIR__"npc/guan" : 1,
        ]));
        set("outdoors", "luoyang");
	set("no_clean_up", 0);
        setup();
	replace_program(ROOM);
}


