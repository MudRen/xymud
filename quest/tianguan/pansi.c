inherit __DIR__"r.c";

void create()
{
::create();
set("short","前世");
set("number",2);
set("master","zixia xianzi");
set("exits",([
        "up" : __DIR__"shushan",
]));    
set("item_desc",([
        "up" : "上方雾气缭绕，你什么也看不清。\n",
]));
set("objects",([
      __DIR__"npc/pansi"  : 1,
      __DIR__"npc/pansi2" : 2+random(5),
]));
setup();
}               

