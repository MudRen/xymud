//Cracked by Roath

inherit ROOM;
void create()
{
  set ("short", "江州东门");
  set ("long", @LONG

    这个地方就是江州的东门了，这个地方比起长安城可真是差远了。
 一眼东望，可以看到路上疏疏朗朗的几个行人，这个城门看起来
也很旧了。上书：
[1;32m
                ※※※※※※※※※※※※
                ※                    ※
                ※    江        州    ※
                ※                    ※
                ※※※※※※※※※※※※
[m
LONG);
        set("exits", ([
  "west" : __DIR__"sibei-w2",
  "east": "/d/changan/southseashore.c",
]));
        set("objects", ([
  "/d/city/npc/wujiang":2,
                ]));
  setup();
}
