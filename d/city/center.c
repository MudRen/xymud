//changan city
#include <ansi.h>
inherit ROOM;

void create ()
{
        set ("short", "十字街头");
        set ("long", 
"这里便是长安城的中心，四条大街交汇于此。一座巍峨高大的钟楼耸
立于前，很是有些气势。每到清晨，响亮的钟声便会伴着淡淡雾气传
向长安城的大街小巷。路口车水马龙，来往人潮不断。\n");
	set("long2","\n"+
HIR"  ┏┳┳━┳━━━━━━━━┳━━━━━━━━┳━━━━━━━━┳━┳┳┓  \n"NOR+
HIR"┏╋╋┛"NOR+YEL"┏┻┓            ┏┻┓            ┏┻┓            ┏┻┓"NOR+HIR"┗╋╋┓\n"NOR+
HIR"┣╋┛"NOR+RED"◢███◣        ◢███◣        ◢███◣"NOR+RED"        ◢███◣"NOR+HIR"┗╋┫\n"NOR+
HIR"┣┛ "NOR+RED" █"NOR+BRED HIY" 二〇 "NOR+RED"█        █"NOR+BRED HIY" 一四 "NOR+RED"█        █"NOR+BRED HIY" 新年 "NOR+RED"█ "NOR+RED"       █"NOR+BRED HIY" 快乐 "NOR+RED"█ "NOR+HIR" ┗┫\n"NOR+
HIR"┃   "NOR+RED" ◥███◤        ◥███◤  "NOR HIR"◢◣"NOR RED"  ◥███◤        ◥███◤  "NOR+HIR"  ┃\n"NOR+
HIR"┃   "NOR+RED"   ║║║            ║║║  "NOR+HIY"◢"NOR+HBRED"    "NOR+HIY"◣"NOR+RED"  ║║║            ║║║    "NOR+HIR"  ┃\n"NOR+
HIR"┃        "NOR+HIY"ζ"NOR+RED"                    "NOR+HIR"◢"NOR+HBRED"        "NOR+HIR"◣                    "NOR+HIY"ζ"NOR+HIR"        ┃\n"NOR+
HIR"┃       ▄▄               "NOR+HIY"  ◢"NOR+HBRED"            "NOR+HIY"◣              "NOR+HIR"   ▄▄       ┃\n"NOR+
HIR"┃        ▄▄              "NOR+HIR"◢"HIY+HBRED"╭──╮  ╭╮  "NOR+HIR"◣                "NOR+HIR" ▄▄     ┃\n"NOR+
HIR"┃      ▄▄              "NOR+HIY"◢"HIY+HBRED"  │-  -│╭╮╭╮  "NOR+HIY"◣             "NOR+HIR" ▄▄      ┃\n"NOR+
HIR"┃         ▄▄         "NOR+HIR"◢"HIY+HBRED"    │-  -│││││    "NOR+HIR"◣           "NOR+HIR"▄▄       ┃\n"NOR+
HIR"┃        ▄▄        "NOR+HIY"◢"HIY+HBRED"      ╰──╯││││      "NOR+HIY"◣         "NOR+HIR" ▄▄      ┃\n"NOR+
HIR"┃         ▄▄       "NOR+HIR"◥"HIY+HBRED"       │─│ ╰╯__│      "NOR+HIR"◤         "NOR+HIR"  ▄▄     ┃\n"NOR+
HIR"┃      ▄▄            "NOR+HIY"◥"HIY+HBRED"     ╰─╯ │  ─╮    "NOR+HIY"◤          "NOR+HIR" ▄▄       ┃\n"NOR+
HIR"┃        ▄▄            "NOR+HIR"◥"HIY+HBRED"   ╭─╮ ╰──╯  "NOR+HIR"◤             "NOR+HIR" ▄▄      ┃\n"NOR+
HIR"┃        ▄▄              "NOR+HIY"◥"HIY+HBRED" ╰─╯  ╰─╯ "NOR+HIY"◤               "NOR+HIR" ▄▄      ┃\n"NOR+
HIR"┃         "NOR+HIY"ζ                 "NOR+HIR"◥"HIY+HBRED"            "NOR+HIR"◤                   "NOR+HIY"ζ"NOR+HIR"       ┃\n"NOR+
HIR"┣┓    .  "NOR+HIY"*"NOR+HIR" . .                "NOR+HIY"◥"HIY+HBRED"        "NOR+HIY"◤"NOR+HIR"                   * "NOR+HIY"*"NOR+HIR" . .  ┏┫\n"NOR+
HIR"┣╋┓   *  "NOR+HIY"*"NOR+HIR" .                   "NOR+HIR"◥"HIY+HBRED"    "NOR+HIR"◤"NOR+HIR"                      . "NOR+HIY"*"NOR+HIR" . ┏╋┫\n"NOR+
HIR"┗╋╋┓.*                          "NOR+HIY"◥◤"NOR+HIR"                         .* ┏╋╋┛\n"NOR+
HIR"  ┗┻┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻┻┛  \n"NOR);

        set("exits", ([ 
		"south" : __DIR__"zhuque-s1",
		//"up" : "/d/city/paimaiwu",
                "north" : __DIR__"xuanwu-n0",
                "west" : __DIR__"baihu-w1",
                "east" : __DIR__"qinglong-e1",
		"down" : __DIR__"droproom",
	]));
        set("objects", ([
		__DIR__"npc/libai" : 1,
		"/d/qujing/wuzhuang/npc/zhangguolao": 1,
        ]));
        set("outdoors", "changan");
	set("no_clean_up", 0);
        setup();
}

