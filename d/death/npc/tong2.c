//puti.c
inherit NPC;

void create()
{
       set_name("黄衣童子", ({"tongzi"}));
       set_level(15);
       set("gender", "男性");
       set("age", 15);
       set("attitude", "peaceful");
       set("shen_type", 1);
       set("per", 30);
       set("combat_exp", 30000);
	set_skill("unarmed", 140);
	set_skill("dodge", 150);
	set_skill("parry", 150);
	set_skill("jinghun-zhang", 130);
	map_skill("unarmed", "jinghun-zhang");
	set("max_kee", 300);
	set("max_sen", 300);
	set("max_force", 300);
	set("force", 300);
	set("force_factor", 10);

setup();

        carry_object("/d/obj/cloth/huangyi")->wear();
//        carry_object("/d/lingtai/obj/shoe")->wear();
//        carry_object("/d/lingtai/obj/putibang")->wield();
}

