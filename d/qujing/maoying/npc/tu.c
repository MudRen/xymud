// created 11/20/1997 by snowcat

inherit NPC;

string *names = ({
  "白兔精",
  "灰兔精",
  "黑兔精",
  "赤兔精",
  "黄兔精",
  "长毛兔精",
  "短毛兔精",
  "卷毛兔精",
});

void jump_away ();

void create()
{
	int i = 30+random(20);
	set_name(names[random(sizeof(names))], ({ "tu jing", "tu", "jing" }));
	set("long", "一位兔模兔样的女子。\n");
	set("gender", "女性");
	set("age", 20);
	set_level(i);
	set("attitude", "peaceful");
	set("force_factor", 10);
	set("mana_factor", 80);

	set_skill("spells",i*10);
	set_skill("moonshentong",i*10);
	set_skill("unarmed",i*10);
	set_skill("baihua-zhang",i*10);
	set_skill("dodge",i*10);
	set_skill("moondance",i*10);
	set_skill("parry",i*10);
	set_skill("force",i*10);
	set_skill("moonforce",i*10);
  	map_skill("spells", "moonshentong");
  	map_skill("unarmed", "baihua-zhang");
  	map_skill("dodge", "moondance");
  	map_skill("force", "moonforce");
	set("chat_chance_combat", 2);
	set("chat_msg_combat", ({ (: jump_away :) }) );

	setup();
  	carry_object("/d/obj/cloth/shoupiqun")->wear();
}

void jump_away ()
{
  string s;
  object room;
  object me = this_object();
  
  s = sprintf ("/d/qujing/maoying/shanpo%d.c",random(10)+1);
  room = load_object(s);
  message_vision ("嗖地一声，$N向外跳去……\n",me);
  me->move(room);
  if (present("tu jing 6",environment(me)))
    destruct (me);
  else
    message_vision ("$N嗖地一声跳了过来……\n",me);
}

void unconcious ()
{
  die ();
}

void die ()
{
  object me = this_object();
  message_vision ("\n$N翻倒在地，还原为一只野兔，向外一蹿。\n",me);
  destruct(me);
}