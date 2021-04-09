//changan city

inherit ROOM;

void create ()
{
        set ("short", "长安城东门");
        set ("long", @LONG

这里是长安城的东门。西面就到了城中，远望人山人海，往来行人车
流不绝。西面一条大路通向远方。城门下有一些执勤的兵士。时下虽
已天下太平，但一干兵将还是英姿勃勃，警惕的盯着往来人士。
LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
                "west" : __DIR__"qinglong-e3",
                "east" : "/d/kaifeng/east1",  
                "northeast" : "/d/luoyang/gudao1",  
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/wujiang" : 1,
		__DIR__"npc/bing" : 3,
        ]));


        set("outdoors", "changan");
	set("no_clean_up", 0);
        setup();
	replace_program(ROOM);
}



