inherit __DIR__"r.c";

void create()
{
::create();
set("short","菩提");
set("number",12);
set("master","master puti");
set("exits",([
      "up" : __DIR__"sea",
]));    
set("item_desc",([
        "up" : "上方雾气缭绕，你什么也看不清。\n",
        "west" : "上方雾气缭绕，你什么也看不清。\n",
]));
set("objects",([
      __DIR__"npc/fc"  : 1,
      __DIR__"npc/fc2" : 5+random(2),
]));
setup();
}