# include <skill.h>

inherit ITEM;

void create()
{
        set_name("九彩云龙珠", ({"jiucai longzhu", "jiucai", "longzhu"}));
	set_weight(100);
	if( clonep() )
    		set_default_object(__FILE__);
  	else {
		set("no_sell",1);
//		set("no_give",1);
		set("no_put",1);
		set("no_get",1);
		set("value",0);
		set("unit","颗");
		set("long",
"一颗斗大圆润的珍珠，隐见内有九条光影游动，似乎触摸(touch)之下会发出异彩。\n");
	}
	set("is_monitored",1);
	setup();

}
void init()
{

  object me = this_object();
  object where = environment();

  if (userp(where))
  {
    if (me->query("owned"))
    {
      if (me->query("owned")!=where->query("id"))
      {
        call_out("destruct_me",1,where,me);
      }
    }
    else
    {
      me->set("owned",where->query("id"));
    }
  }
	add_action("do_study","touch");
}
void destruct_me(object where, object me)
{
	object pearl;
        if( pearl=new("/d/sea/obj/pearl"))
        	pearl->move(where);
	message_vision("$N手中的$n突发七彩之光，一道霞光过后便失去了颜色。\n",where,me);
	destruct(me);
}

int do_study(string arg)
{
	object me,pearl;
	int i;
	me=this_player();

	if( !arg || (arg!="long zhu"
			&& arg!="zhu"
			&& arg!="pearl") )
		return notify_fail("你要摸什么？\n");

	if( (int)me->query_skill("force",1) < 100)
		return notify_fail("你的内功心法不够，还感受不到龙珠内的灵力。\n");
	if( (int)me->query_skill("force",1) >= 300)
		return notify_fail("你的内功心法过高，龙珠内的灵力以对你豪无作用了。\n");
	if( (int)me->query_skill("spells",1) < 50)
		return notify_fail("你的法术修养不够，还领悟不到龙珠内的灵力。\n");
	if( (int)me->query("kee") < 50)
		return notify_fail("你的气血不足，再练会晕倒过去。\n");
	if( (int)me->query("sen") < 50)
		return notify_fail("你的精神不济，再练会昏迷过去。\n");
	if( (int)me->query("force") <50)
		return notify_fail("你的内力不足，再练有害无益。\n");
	i=(int)me->query_kar()*(int)me->query("spi")*2;
	if( i>1000 ){
		i=1000;
	}

	if( (int)this_object()->query("learned") >= i) {
		message_vision("$N手中的$n突发七彩之光，一道霞光过后便失去了颜色。\n",me,this_object());
		if( pearl=new("/d/sea/obj/pearl")){
			pearl->move(me);
		}
		destruct(this_object());
		return 1;
	}
	message_vision("$N双手轻握$n，只见几缕淡淡霞光流入掌中。\n",me,this_object());
	me->improve_skill("force", random((int)me->query_int()/3 + (int)me->query_spi()/3)+1+random(3));
	me->receive_damage("kee",30);
	me->receive_damage("sen",30);
	me->add("force",-10);
	this_object()->add("learned",1);

	write("你对内功心法的领悟似乎又深了一层。\n");
	return 1;
}
