// by snowcat oct 15 1997

inherit ITEM;

void create()
{
  set_name("鹅笼", ({"e long", "long"}));
  set_weight(6000000);
  set_max_encumbrance(100000000000);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "只");
    set("long", "一只铜框大鹅笼。\n"),
    set("value", 50000);
  }
  setup();
}

void init()
{
  object me = this_object();

  if (! me->query_temp("initialized"))
  {
    object kid = new ("/d/qujing/biqiu/npc/kid");
    me->set_temp("initialized",1);
    kid->move(me);
  }
  add_action ("do_open","open");
}

int do_open (string arg)
{
  object me = this_object();
  object who = this_player();
  object kid;

  if (!arg || !id(arg) )
	return notify_fail("你要打开什么？\n");

  kid = present ("xiao er",me);
  if (kid)
  {
    message_vision ("$N将鹅笼门吱地一声打开。\n",who);
    message_vision ("一位小儿从里面爬出来了。\n",who);
    kid->move(environment());	
  }  
  else
  {
    message_vision ("$N将鹅笼打开，将头伸进去看了看。\n",who);
  }  
  return 1;
}