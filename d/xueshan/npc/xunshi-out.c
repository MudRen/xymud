// xunshi.c
inherit NPC;
void create()
{
	int i = 40+random(10);
	set_name("冰谷巡使", ({"xunshi", "shi"}));
      	set_level(i);
	set("gender", "男性" );
	set("age", 33);
	set("long", "这位巡使来自遥远的大雪山。他身披白袍，腰跨弯刀。\n白袍当胸绣着一只飞扬欲脱的大鹏鸟。弯刀看起来晶莹透明，好像是以寒冰制成。\n");
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
	set_skill("spells",i*10);
	set_skill("dengxian-dafa",i*10);
	set_skill("force",i*10);   
	set_skill("ningxie-force",i*10);
	map_skill("spells", "dengxian-dafa");
	map_skill("force", "ningxie-force");
	map_skill("blade", "bingpo-blade");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("unarmed", "yingzhao-gong");
	map_skill("parry", "yingzhao-gong");
	set("per", 19);
	set("force_factor", 50);
	set("mana_factor", 30);

	set("eff_dx", -15000);
	set("nkgain", 80);

	setup();
	carry_object(0,"cloth",random(2))->wear();
	carry_object(0,"shoes",random(2))->wear();
	carry_object(0,"armor",random(2))->wear();
	carry_object(0,"shield",random(2))->wear();
	carry_object(0,"pifeng",random(2))->wear();
	carry_object("/d/obj/weapon/blade/iceblade")->wield();
}