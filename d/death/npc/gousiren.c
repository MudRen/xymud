//puti.c
inherit NPC;

void create()
{
       set_name("勾司人", ({"gousi ren", "ren"}));
       set_level(15);
       set("gender", "男性");
       set("age", 30);
	set("long", "一些地府里的杂务人员．\n");
       set("attitude", "peaceful");
       set("shen_type", 1);
       set("combat_exp", 20000+random(5000));
  set("daoxing", 30000);

	set("bellicosity", 100);
	set_skill("unarmed", 135);
	set_skill("dodge", 135);
	set_skill("parry", 145);
	set("force", 300);
	set("max_force", 300);
	set("force_factor", 5);
	set("max_kee", 450);
set("inquiry", ([
"here": "这就是阴曹地府！\n",
]) );

set("chat_chance", 8);
set("chat_msg", ({
(: random_move :)
}) );

setup();

        carry_object(0,"cloth",random(2))->wear();
//        carry_object("/d/lingtai/obj/shoe")->wear();
//        carry_object("/d/diyu/obj/tielian")->wield();
}


