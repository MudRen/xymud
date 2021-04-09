// xunshi.c
inherit NPC;
void create()
{
	int i = 1+random(41);
	set_name("冰谷巡使", ({"xunshi", "shi"}));
      	set_level(i);
	set("gender", "男性" );
	set("age", 33);
	set("long", "雪山门下有很多巡使。因为外人很少能到这里，\n在谷内的巡使大多武功不高，至于大雪山的法术则基本上不会。\n这位巡使身披白袍，腰跨弯刀。白袍当胸绣着一只飞扬欲脱的大鹏鸟。\n弯刀看起来晶莹透明，好像是以寒冰制成。\n");
	set("class", "yaomo");
	set("attitude", "peaceful");
	create_family("大雪山", 4, "弟子");
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
	set("force_factor", 15);

	set("eff_dx", -8000);
	set("nkgain", 60);

	setup();
	carry_object(0,"cloth",random(2))->wear();
	carry_object(0,"shoes",random(2))->wear();
	carry_object(0,"neck",random(2))->wear();
	carry_object(0,"ring",random(2))->wear();
	carry_object(0,"pifeng",random(2))->wear();
	carry_object("/d/obj/weapon/blade/iceblade")->wield();
}