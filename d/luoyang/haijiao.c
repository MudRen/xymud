//changan city
// Cracked by 凌惊雪 1-3-2003

inherit ROOM;
int block_cmd(string);
void create ()
{
        set ("short", "天涯海角");
        set ("long", @LONG
这是洛阳城区一个比较奇怪的建筑，一种血色干凝的暗红色。屋里更是阴
气森森。房子无窗，一盏油灯忽明忽暗。以太极八卦图为底的招牌上用篆体刻
着四个字“天涯海角”，也是黯淡无光的红色。
LONG);

        set("exits", 
        ([ //sizeof() == 4
                "east" : __DIR__"qianyuan1",
                "west" : __DIR__"shikong",
        ]));

        set("objects", 
        ([ //sizeof() == 1
//                __DIR__"npc/xianzhi" : 1,
        ]));
	set("no_clean_up", 0);
  	set("no_fight", 1);
  	set("no_magic", 1);
        setup();
}
void init()
{
    add_action("block_cmd", "", 1);
}

int block_cmd(string args)
{
string verb;
verb = query_verb();

    if (verb == "bian") return 1; // by mon 7/15
    if (verb == "xiudao") return 1;
    if (verb == "exert") return 1;
    if (verb == "bid") return 1;
    return 0;
}

