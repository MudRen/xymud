inherit NPC;

void create()
{
       set_name("鲤总兵", ({"li zongbing", "li", "zongbing"}));
       set_level(50);
	set("long","东海龙宫鲤总兵。\n");
       set("gender", "男性");
       set("age", 40);
	set("per", 15);
       set("attitude", "heroism");
       set("shen_type", 1);
	set("force_factor", 30);
	set("mana_factor", 30);
        set("combat_exp", 500000);

        set_skill("parry", 120);
        set_skill("dodge", 120);
	set_skill("unarmed", 120);
	set_skill("spells", 100);
	set_skill("force", 100);
	set_skill("hammer", 100);
        setup();
  carry_object(0,"armor",random(3))->wear();
  carry_object(0,"cloth",random(3))->wear();
  carry_object(0,"kui",random(3))->wear();
  carry_object(0,"shield",random(3))->wear();
  carry_object(0,"shoes",random(3))->wear();
  carry_object(0,"unarmed",random(3))->wield();
}