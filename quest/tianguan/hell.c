inherit __DIR__"r.c";

void create()
{
::create();
set("short","奖惩");
set("number",8);
set("master","yanluo wang");
set("exits",([
         "up" : __DIR__"xs",
]));    
set("item_desc",([
        "up" : "上方雾气缭绕，你什么也看不清。\n",
        "west" : "上方雾气缭绕，你什么也看不清。\n",
]));
set("objects",([
      __DIR__"npc/hell"  : 1,
      __DIR__"npc/hell2" : 4+random(3),
]));
setup();
}               

