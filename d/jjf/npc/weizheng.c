//created 5-20-97 pickle
 
inherit NPC;
inherit F_MASTER;
 
void create()
{
	set_name("魏徵", ({"wei zheng", "wei", "zheng", "weizheng", "shifu", "master"}));
  	set_level(39);
  	set ("long", @LONG
魏徵先仕齐府为太子李建成屡设妙计。但李建成不听其
劝告，终为太宗所杀。太宗爱魏徵之才，将其收罗，并
封为郑国公。
LONG);
 
  	set("title", "郑国公");
  	set("gender", "男性");
  	set("age", 55);
  	set("per", 35);
  	set("daoxing", 800000);

	set_skill("force",390);
	set_skill("haoran-zhengqi",390);
	set_skill("haoran-jian", 390);
	set_skill("sword", 390);
	set_skill("dodge", 390);
	set_skill("parry", 390);
	set_skill("yanxing-steps", 390);
	set_skill("literate", 390);
  	set_skill("spells", 390);
  	set_skill("baguazhou",390);
	set_skill("yanxing-steps",390);
	set_skill("unarmed",390);
  	set_skill("changquan",390);
	map_skill("dodge","yanxing-steps");
	map_skill("sword","haoran-jian");
	map_skill("parry","haoran-jian");
	map_skill("force","haoran-zhengqi");	
	map_skill("spells", "baguazhou");
  	map_skill("force", "lengquan-force");
  	map_skill("unarmed", "changquan");
  	map_skill("dodge", "yanxing-steps");
	set("force_factor", 10);
  	set("mana_factor", 70);
 	set("env/test","HIB");
 	set_temp("weapon_level",20+random(10));
 	set_temp("armor_level",20+random(10));
	setup();
  	carry_object(0,"sword",1)->wield();
  	carry_object(0,"cloth",1)->wear();
  	carry_object(0,"shoes",1)->wear();
  	powerup(0,1);
}
