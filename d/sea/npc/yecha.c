inherit NPC;

void create()
{
       	set_name("巡海夜叉", ({"ye cha", "yecha", "cha"}));
        set_level(90);
       	set("long","一个巡海的夜叉，长的青面獠牙．\n");
       	set("gender", "男性");
       	set("per", 10);
       	set("attitude", "heroism");
	create_family("东海龙宫",4,"");	
	delete("title");
       	set_skill("parry", 900);
       	set_skill("dodge", 900);
       	set_skill("fork", 900);
       	set_skill("force", 900);
       	set_skill("spells", 900);
       	set_skill("fengbo-cha", 900);
	set_skill("dragonforce", 900);
	set_skill("dragonstep", 900);
	set_skill("seashentong", 900);
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