inherit NPC;

string *names = ({
  "青蛇",
  "蜈蚣",
  "蝎子",
  "蜘蛛",
  "蟾蜍",
});

string *ids = ({
  "she",
  "wugong",
  "xie",
  "zhizhu",
  "hama",
});

void create()
{
  int i,ii;
  i = 10+random(40); 
  ii=random(sizeof(names));
	
  set_name(names[ii], ({ids[ii]}));
  set_level(i);
  set("race", "野兽");
  set("age", 10);
  set_skill("dodge",i*10);
  set_skill("unarmed",i*10);
  set_skill("parry",i*10);
  set("limbs", ({ "头部", "身体", "前腿","後腿", "尾巴" }) );
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
  ob->set("cook/type",me->query("id"));
  ob->move(where);
  message_vision ("\n$N缩成一团，不再动了。\n",me,ob);
  destruct (me);
}

void die ()
{
  unconcious();  
}

