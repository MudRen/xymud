//Cracked by Roath
// bonze.c 和尚?// By Dream Dec. 20, 1996
inherit NPC;

void create()
{
	set_name("和尚", ({ "heshang", "bonze" }));
      	set_level(20);
	set("gender", "男性");
	set("age", 30);
	set("attitude", "peaceful");
	set("class", "bonze");
	set("force_factor", 20);
	set("mana_factor", 20);

        set("eff_dx", 35000);
        set("nkgain", 200);

	set_skill("literate", 200);
	set_skill("spells", 200);
	set_skill("buddhism", 200);
	set_skill("unarmed", 200);
	set_skill("jienan-zhi", 200);
	set_skill("dodge", 200);
	set_skill("lotusmove", 200);
	set_skill("parry", 200);
	set_skill("force", 200);
	set_skill("lotusforce", 200);
	set_skill("staff", 200);
	set_skill("lunhui-zhang", 200);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "lunhui-zhang");
	map_skill("staff", "lunhui-zhang");
	set("chat_chance", 5);
	set("chat_msg", ({
		(: random_move :)
	}) );
	create_family("南海普陀山", 3, "弟子");
	setup();
	carry_object(0,"staff",random(2))->wield();
	carry_object("/d/nanhai/obj/sengpao")->wear();
}