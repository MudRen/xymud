inherit __DIR__"r.c";

void create()
{
::create();
set("short","磨砺");
set("number",3);
set("master","bai mei");
set("exits",([
        "up" : __DIR__"wzg",
]));    
set("item_desc",([
        "up" : "上方雾气缭绕，你什么也看不清。\n",
]));
set("objects",([
      __DIR__"npc/shushan"  : 1,
      __DIR__"npc/shushan2" : 3+random(3),
]));
setup();
}               

