// created by snowcat.c 10/14/1997
// room: /d/qujing/baoxiang/shan3.c

inherit ROOM;

void create ()
{
  set ("short", "碗子山");
  set ("long", @LONG

山上黄土龟裂岩石层层，参差不奇地长着一些树林灌木。路从岩
石周围绕道铺设盘山而行，迂回曲折。四处风吹草动，空谷回音。
令人恍然不知所处。

LONG);

  set("exits", ([
        "northwest"  : __DIR__"shan2",
        "southwest"  : __DIR__"shan4",
        "southeast"  : __DIR__"shan5",
      ]));
  set("outdoors","/d/qujing/baoxiang");

  setup();
}

void init ()
{
  object who = this_player();

  if (who && interactive(who))
    call_out ("appearing", 3+random(3),who);
}

void appearing (object who)
{
  object where = this_object();
  object guai;

  if (! who ||
      environment(who) != where)
    return;

  /*
  if (! present ("zipao guai", where))
  {
    guai = new (__DIR__"npc/zipao");
    guai->move(where);    
    guai->appear();    
    guai->disappear();    
  }
  if (! present ("lupao guai", where))
  {
    guai = new (__DIR__"npc/lupao");
    guai->move(where);    
    guai->appear();    
    guai->disappear();    
  }
  */
  if (! present ("qingpao guai", where))
  {
    guai = new (__DIR__"npc/qingpao");
    guai->move(where);    
    guai->appear();    
    guai->disappear();    
  }
  call_out ("no_reappearing",20);
}

void no_reappearing ()
{
  remove_call_out ("appearing");
}
