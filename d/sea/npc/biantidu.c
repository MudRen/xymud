inherit NPC;

void create()
{
	int i = 75;
       set_name("鳊提督", ({"bian tidu", "bian", "tidu"}));
       set_level(i);
	set("long","东海龙宫鳊提督。\n");
       set("gender", "男性");
       set("age", 40);
	set("per", 15);
       set("attitude", "heroism");
       set("shen_type", 1);
	set("force_factor", 30);
	set("mana_factor", 30);
	create_family("东海龙宫",3,"");	
	delete("title");
       	set_skill("parry", i*10);
       	set_skill("dodge", i*10);
       	set_skill("fork", i*10);
       	set_skill("force", i*10);
       	set_skill("spells", i*10);
       	set_skill("fengbo-cha", i*10);
	set_skill("dragonforce", i*10);
	set_skill("dragonstep", i*10);
	set_skill("seashentong", i*10);
	map_skill("parry","fengbo-cha");
	map_skill("fork","fengbo-cha");
	map_skill("force","dragonforce");
	map_skill("spells","seashentong");
	map_skill("dodge","dragonstep");
	set_temp("armor_level",10+random(10));
	set_temp("weapon_level",10+random(10));
	setup();
       	carry_object(0,"armor",random(2))->wear();
       	carry_object(0,"unarmed",random(2))->wield();
}