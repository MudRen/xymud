//puti.c
inherit NPC;

void create()
{
       set_name("马面鬼", ({"mamian gui", "gui", "mamian"}));
       set_level(38);
       set("gender", "男性");
       set("age", 30);
	set("long", "一个马面鬼，脸部是一野马模样。\n");
       set("attitude", "heroism");
       set("shen_type", 1);
       set("per", 10);
	set("str", 20);
       set("combat_exp", 90000+random(10000));
	set_skill("unarmed", 360);
	set_skill("dodge", 360);
	set_skill("hammer", 380);
	set_skill("parry", 380);
	set("force", 300);
	set("max_force", 300);
	set("force_factor", 15);
	set("max_kee",800);
	set("max_sen",800);
	set("mana", 300);
	set("mana_factor", 15);
	set("max_mana", 300);

set("inquiry", ([
"name": "老子就是杀人无数，爱吃手指头的马面鬼！\n",
"here": "这就是阴曹地府，哼，等着剥皮抽筋吧你！\n",
]) );

setup();

         carry_object(0,"armor",random(2))->wear();
        carry_object(0,"hammer",random(2))->wield();

}

