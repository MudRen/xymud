//changan city
// Cracked by 凌惊雪 1-3-2003

inherit ROOM;

void create ()
{
        set ("short", "神侯府");
        set ("long", @LONG
雪衣神侯水舞寒曾闯荡四方，晚年便在这里归隐，收录手下，尽
徼天下匪徒。府中大红波斯地毯铺地，富丽堂煌。房子的中央有一张
上等翠玉打磨成的八仙桌，桌上放着四只御赐金杯。三面的墙上挂满
了字画，剩下的一面是一道一垂及地的红布挂帘。

LONG);

        set("exits", 
        ([ //sizeof() == 4
                "south" : __DIR__"congming1",
                "north" : __DIR__"shufang",
        ]));

        set("outdoors", "luoyang");
	set("no_clean_up", 0);
        setup();
	replace_program(ROOM);
}


