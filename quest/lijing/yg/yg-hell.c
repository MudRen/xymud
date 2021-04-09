inherit __DIR__"yaoguai.c";

void set_skills(int j)
{
	create_family("阎罗地府",3,"");
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
        		carry_object(0,"whip",1)->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"whip", "three" :),
        			(: perform_action,"whip", "ldlh" :),
        			(: exert_function, "sheqi" :),
        		}));	
			break;
		case 1 :	
        		set_skill("stick",j);
        		set_skill("kusang-bang",j);
        		map_skill("stick","kusang-bang");
        		map_skill("parry","kusang-bang");
        		carry_object(0,"whip",1)->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"stick", "three" :),
        			(: perform_action,"stick", "qmly" :),
        			(: exert_function, "sheqi" :),
        		}));	
			break;
		default :
			set_skill("sword",j);
			set_skill("zhuihun-sword",j);
        		map_skill("parry","zhuihun-sword");
        		map_skill("sword","zhuihun-sword");
        		carry_object(0,"sword",1)->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"sword", "three" :),
        			(: perform_action,"sword", "dengku" :),
        			(: perform_action,"sword", "yanluo" :),
        		}));	
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
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	set("class","ghost");
}