//Cracked by Roath

inherit ROOM;

void create ()
{
        set ("short", "汤圆店");
        set ("long", @LONG

    刚进来，你第一眼看到的就是那赫赫有名的招牌：
[35m
                □□□□□□□□□
                □   凌记汤圆   □
                □□□□□□□□□
[m
也许这根本就不是正宗的凌记汤圆，但是凌老板服务态度
好，再加上他们的汤圆味道也不错，大家也就习惯了。

LONG);

        set("exits",
        ([ //sizeof() == 4
                "south": __DIR__"sibei-w1",
      ]));
      set("objects", ([
                                __DIR__"npc/ling" :1,
                ]));

      set("outdoors", "JZ");
   set("no_clean_up", 0);
        setup();
   replace_program(ROOM);
}
