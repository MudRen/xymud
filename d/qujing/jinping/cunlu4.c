// create by snowcat.c 12/8/1997

inherit ROOM;

void create ()
{
  set ("short", "村路");
  set ("long", @LONG

烟飘飘，雾漫漫，一眼极目望去只见农田翠幽幽，几幢小房在
天边星星点点。脚下是厚实的泥土路，两边是田埂，不时可以
听见溪水在埂下流过。

LONG);

  set("exits", ([
        "northwest"   : __DIR__"cunlu3",
        "southeast"   : __DIR__"cunlu5",
      ]));
  set("outdoors", __DIR__);

  setup();
}



