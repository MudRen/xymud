inherit __DIR__"r.c";

void create()
{
::create();
set("short","墨香");
set("number",1);
set("master","li bai");
set("exits",([
        "up" : __DIR__"pansi",
]));    
set("item_desc",([
        "up" : "上方雾气缭绕，你什么也看不清。\n",
]));
set("objects",([
      __DIR__"npc/sanxian"  : 1,
      __DIR__"npc/sanxian2" : 2+random(4),
]));
setup();
}               

