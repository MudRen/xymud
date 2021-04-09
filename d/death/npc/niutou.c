//puti.c
inherit NPC;

void create()
{
       set_name("牛头鬼", ({"niutou gui", "gui", "niutou"}));
       set_level(28);
       set("gender", "男性");
       set("age", 30);
	set("long", "一个牛头鬼，脸部是一野牛模样。\n");
       set("attitude", "heroism");
       set("shen_type", 1);
       set("per", 10);
	set("str",20);
       set("combat_exp", 90000+random(10000));
	set_skill("unarmed", 260);
	set_skill("dodge", 260);
	set_skill("whip", 280);
	set_skill("parry", 280);
	set("force_factor", 15);
	set("mana_factor", 15);
	set("inquiry", ([
		"name": "老子就是杀人无数，爱啃后脑勺的牛头鬼！\n",
		"here": "这就是阴曹地府，哼，等着剥皮抽筋吧你！\n",
	]) );
	set_temp("armor_level",5);
	set_temp("weapon_level",5);
	setup();
        carry_object(0,"armor",random(2))->wear();
        carry_object(0,"whip",random(2))->wield();
}

