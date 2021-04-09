//puti.c
inherit NPC;

void create()
{
       set_name("桥梁使者", ({"bridge guard", "guard"}));
       set_level(15);
       set("gender", "男性");
       set("age", 25+random(10));
       set("attitude", "peaceful");
       set("shen_type", 1);
       set("force_factor", 20);
       set_skill("unarmed", 140);
       set("daoxing",1500000);
       set_skill("dodge", 150);
       set_skill("parry", 150);
	set_skill("whip", 150);
        set_skill("force", 150);
	set_temp("armor_level",1);
	set_temp("weapon_level",1);
	setup();

        carry_object(0,"cloth",random(10))->wear();
        carry_object(0,"shoes",random(10))->wear();
        carry_object(0,"whip",random(10))->wield();

}

int accept_fight(object me)
{
        command("say 你活得不耐烦了？\n");
        kill_ob(me);
        return 1;
}

