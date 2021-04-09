inherit NPC;
string *first_name = ({ "青鳝", "赤鲤", "黄鲳", "白鲨", "紫鲭", "金鳌",
"银蛎", "乌鳅"});
string *name_words = ({ "力士"});

void create()
{
	string name;
	name = first_name[random(sizeof(first_name))];
	name += name_words[random(sizeof(name_words))];

	set_name(name, ({"li shi", "shi"}));
       	set_level(50);
       	set("gender", "男性");
	set("title", "宫前护卫");
	set("age", 20+random(5));
	set("per", 10);
       	set("attitude", "heroism");
       	set("shen_type", 1);

	create_family("东海龙宫",4,"");	
	delete("title");
       	set_skill("parry", 500);
       	set_skill("dodge", 500);
       	set_skill("fork", 500);
       	set_skill("force", 500);
       	set_skill("spells", 500);
       	set_skill("fengbo-cha", 500);
	set_skill("dragonforce", 500);
	set_skill("dragonstep", 500);
	set_skill("seashentong", 500);
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
	carry_object(0,"armor",random(3))->wear();
  	carry_object(0,"cloth",random(3))->wear();
  	carry_object(0,"kui",random(3))->wear();
  	carry_object(0,"shield",random(3))->wear();
  	carry_object(0,"shoes",random(3))->wear();
  	carry_object(0,"fork",random(3))->wield();
  	powerup(0,1);
}
  	
