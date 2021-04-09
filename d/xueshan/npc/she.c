inherit NPC;

void create()
{
	set_name("赤练小蛇", ({ "chilian xiaoshe", "she" }) );
  	set_level(46);
  	set("race", "野兽");
  	set("age", 100);

  	set_skill("dodge",460);
  	set_skill("parry",460);
  	set_skill("unarmed",460);
  	set("limbs", ({ "头部", "身体", "尾巴" }) );
  	set("verbs", ({ "bite"}));
	setup();
}

void unconcious ()
{
  object ob;
  object me = this_object();
  object where = environment (me);

  ob = new ("/d/xueshan/obj/cookfood");
  ob->set("name",me->query("name"));
  ob->set("cook/type","she");
  ob->set("cook/value",8);
  ob->move(where);
  message_vision ("\n$N缩成一团，不再动了。\n",me);
  destruct (me);
}

void die ()
{
  unconcious();  
}

