inherit __DIR__"r.c";

void create()
{
::create();
set("short","离火");
set("number",5);
set("master","huang feihu");
set("exits",([
        "up" : __DIR__"moon",
]));    
set("item_desc",([
        "up" : "上方雾气缭绕，你什么也看不清。\n",
]));
set("objects",([
      __DIR__"npc/hyd"  : 1,
      __DIR__"npc/hyd2" : 3+random(4),
]));
setup();
}               


