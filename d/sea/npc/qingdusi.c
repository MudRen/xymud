inherit NPC;

void create()
{
	int i = 80;
       	set_name("鲭都司", ({"qing dusi", "qing", "dusi"}));
       	set_level(i);
        set("long","东海龙宫鲭都司。\n");
       	set("gender", "男性");
       	set("age", 40);
        set("per", 15);
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
       	set("force_factor", 50);
	set("mana_factor", 10);
	set_temp("armor_level",10+random(10));
	set_temp("weapon_level",10+random(10));
	setup();
       	carry_object(0,"armor",random(2))->wear();
       	carry_object(0,"fork",random(2))->wield();
}