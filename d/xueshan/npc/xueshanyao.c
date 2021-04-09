// xunshi.c
inherit NPC;

void create()
{
	int i = 15+random(70);
	set_name("雪山妖", ({"xushan yao", "yao"}));
      	set_level(i);
	set("gender", "男性" );
	set("age", 33);
	set("long", "雪山中多妖士、多猛兽，但凡那些灵智初开的猛兽，个个嗜血如命。\n");
	set("class", "yaomo");
        set("attitude", "aggressive");
	set_skill("unarmed",i*10);
	set_skill("yingzhao-gong",i*10);
	set_skill("dodge",i*10);
	set_skill("parry",i*10);
	set_skill("blade",i*10);
	set_skill("bingpo-blade",i*10);
	set_skill("xiaoyaoyou",i*10);
	set_skill("force",i*10);   
	set_skill("ningxie-force",i*10);
	map_skill("force", "ningxie-force");
	map_skill("blade", "bingpo-blade");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("unarmed", "yingzhao-gong");
	map_skill("parry", "yingzhao-gong");
	set("per", 19);
	set("force_factor", 5);
	setup();
	carry_object(0,"cloth",random(2))->wear();
	carry_object(0,"shoes",random(2))->wear();
	carry_object(0,"neck",random(2))->wear();
	carry_object(0,"ring",random(2))->wear();
	carry_object(0,"pifeng",random(2))->wear();
	carry_object("/d/obj/weapon/blade/iceblade")->wield();
}

void unconcious ()
{
  object ob;
  object me = this_object();
  object where = environment (me);

  ob = new (__DIR__"jing");
  ob->move(where);
  message_vision ("\n$N一声狂啸，现了原形，原来是只$n！\n",me,ob);
  destruct (me);
}

void die ()
{
  unconcious();  
}

