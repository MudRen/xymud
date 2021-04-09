//Cracked by Roath
// zhike.c 知客僧?// By Dream Dec. 20, 1996

inherit NPC;

void create()
{
	set_name("知客僧", ({ "zhike seng", "seng" }));
      	set_level(20);
	set("long", "一位年轻的僧人，脸上总是带着热情的笑容。\n他负责在此迎接前来参禅进香的客人。\n");
	set("gender", "男性");
	set("age", 25);
	set("attitude", "peaceful");
	set("class", "bonze");
	set("force_factor", 10);
	set("mana_factor", 10);

	set_skill("literate",200);
	set_skill("unarmed",200);
	set_skill("dodge",200);
	set_skill("parry",200);
	set_skill("force",200);
	set_skill("spells",200);
	set_skill("buddhism",200);
	set_skill("unarmed",200);
	map_skill("spells", "buddhism");
        create_family("南海普陀山", 4, "弟子");
	setup();
	carry_object("/d/nanhai/obj/sengpao")->wear();
}
