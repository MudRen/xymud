//Cracked by Roath
// shizhe.c 净瓶使者?// By Dream Dec. 20, 1996

inherit NPC;

void create()
{
	set_name("净瓶使者", ({ "shizhe" }));
      	set_level(90);
      	create_family("南海普陀山", 3, "弟子");
	set("title", "南海观音侍从");   
	set("long", @LONG
南海观音座前净瓶使者。
LONG);
	set("gender", "男性");
	set("age", 20);
	set("attitude", "friendly");
	set("force_factor", 10);
	set("mana_factor", 20);

        set("eff_dx", 40000);
        set("nkgain", 200);

	set_skill("literate",900);
	set_skill("spells",900);
	set_skill("buddhism",900);
	set_skill("unarmed", 900);
	set_skill("jienan-zhi",900);
	set_skill("dodge",900);
	set_skill("lotusmove",900);
	set_skill("parry",900);
	set_skill("force",900);
	set_skill("lotusforce", 900);

	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");

	set("env/test",({"NOR","HIY",})[random(2)]);
	set_temp("weapon_level",40);
	set_temp("armor_level",40);
	setup();
	add_money("gold",1);
	carry_object("/d/nanhai/obj/jingping");
	carry_object(0,"cloth",random(2))->wear();
	carry_object(0,"shoes",random(2))->wear();
	carry_object(0,"staff",random(2))->wield();
	powerup(0,1);
}