//Cracked by Roath
inherit NPC;

void create()
{
	set_name("朱睛冰蟾", ({"bing chan", "hama"}));
	set_level(88);
	set("race", "野兽");
	set("age", 33);

	set("long", @LONG
一只大蟾蜍，通体雪白，眼珠却血也般红，模样甚是可爱，却也不见有何珍异之处。
LONG);

	set("attitude", "aggressive");
	set("class", "yaomo");
	set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }) );
	set("verbs", ({ "bite"}));

	set("force_factor", 30);
	set("mana_factor", 40);
	
	set_skill("unarmed",880);
	set_skill("parry",880);
	set_skill("yingzhao-gong", random(30)+850);
	set_skill("spells", 880);
	set_skill("dengxian-dafa", random(100)+750);
	set_skill("force", 880);
	set_skill("ningxie-force", random(100)+750);

	map_skill("force", "ningxie-force");
	map_skill("spells", "dengxian-dafa");
	map_skill("unarmed", "yingzhao-gong");
	map_skill("parry", "yingzhao-gong");

	set("chat_chance_combat", 40);
	set("chat_msg_combat", ({
    		(: cast_spell, "jieti" :),
	    	(: cast_spell, "juanbi" :),
    		(: cast_spell, "tuntian" :),
  	}) );

	setup();
}

void unconcious ()
{
  	object ob;
  	object me = this_object();
  	object where = environment (me);

  	ob = new ("/d/xueshan/obj/cookfood");
  	ob->set("name",me->query("name"));
  	ob->set("cook/type","hama");
  	ob->set("cook/value",8);
  	ob->move(where);
  	message_vision ("\n$N缩成一团，不再动了。\n",me);
  	destruct (me);
}

void die ()
{
  unconcious();  
}

