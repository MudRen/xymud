inherit __DIR__"r.c";

void create()
{
::create();
set("short","昆仑");
set("number",6);
set("master","xi wangmu");
set("exits",([
        "up" : __DIR__"jjf",
]));    
set("item_desc",([
        "up" : "上方雾气缭绕，你什么也看不清。\n",
        "east" : "里面雾气缭绕，你什么也看不清。\n",
]));
set("objects",([
      __DIR__"npc/moon"  : 1,
      __DIR__"npc/moon2" : 3+random(3),
]));
setup();
}
