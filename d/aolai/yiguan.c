inherit ROOM;

void create ()
{
        set ("short", "傲来医馆");
        set ("long", @LONG
这是傲来国一家老字号的医馆，相传原来的老板是皇宫中的御医，手
段可知一二。馆中的摆设也十分考究，桌椅被勤快的伙计擦的干干净
净。墙上挂满了别人送来的谢匾。
    一旁有须眉皆白的老者帮人诊断，正面的药柜前摆着一张长几，
里面有伙计买些日常丹药。

LONG);

        set("exits", ([
                "west" : __DIR__"south2",
        ]));
        set("objects", ([ 
                __DIR__"npc/danyao" : 1,
        ]));
	set("no_fight",1);
	set("no_clean_up", 0);
        setup();
}


