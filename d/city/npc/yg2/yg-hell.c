inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("阎罗地府",4,"");
        set("title","倩女幽魂");
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 	switch(random(4))
 	{
 		case 0 :
 			set_skill("whip", j);
        		set_skill("hellfire-whip", j);
        		map_skill("whip", "hellfire-whip");
        		map_skill("parry", "hellfire-whip");
        		carry_object(0,"whip",random(10))->wield();	
			break;
		case 1 :	
        		set_skill("stick",j);
        		set_skill("kusang-bang",j);
        		map_skill("stick","kusang-bang");
        		map_skill("parry","kusang-bang");
        		carry_object(0,"whip",random(10))->wield();	
			break;
		default :
			set_skill("sword",j);
			set_skill("zhuihun-sword",j);
        		map_skill("parry","zhuihun-sword");
        		map_skill("sword","zhuihun-sword");
        		carry_object(0,"sword",random(10))->wield();	
			break;
	}				
        set_skill("ghost-steps", j);
        set_skill("jinghun-zhang", j);
        set_skill("tonsillit", j);
        set_skill("gouhunshu", j);
        map_skill("force", "tonsillit");
        map_skill("spells", "gouhunshu");
        map_skill("dodge", "ghost-steps");
        map_skill("unarmed", "jinghun-zhang");
        setup();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	set("env/wimpy",10);
	set("class","ghost");
}