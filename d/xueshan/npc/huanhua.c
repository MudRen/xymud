//huanhua.c
//hehe, this npc is interesting:D...weiqi, 97.09.15

inherit NPC;
void create()
{
	set_name("浣花", ({"huan hua", "huanhua", "hua"}));
      	set_level(43);
	set("gender", "女性" );
	set("age", 16);
	set("long", "雪山门下女弟子。\n");
	set("class", "yaomo");

	set("attitude", "peaceful");
	create_family("大雪山", 4, "弟子");
	set_skill("unarmed", 430);
	set_skill("dodge", 430);
	set_skill("parry", 430);
	set_skill("blade", 430);
	set_skill("bingpo-blade", 430);
	set_skill("xiaoyaoyou", 430);
	set_skill("force", 430);   
	set_skill("ningxie-force", 430);
	map_skill("force", "ningxie-force");
	map_skill("blade", "bingpo-blade");
	map_skill("dodge", "xiaoyaoyou");
	set("force_factor", 5);
	set("eff_dx", -8000);
	set("nkgain", 60);
	setup();
	carry_object(0,"cloth",random(2))->wear();
	carry_object(0,"shoes",random(2))->wear();
	carry_object(0,"neck",random(2))->wear();
	carry_object(0,"ring",random(2))->wear();
	carry_object(0,"pifeng",random(2))->wear();
	carry_object(0,"blade",random(3))->wield();
}