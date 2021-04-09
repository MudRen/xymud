inherit __DIR__"yaoguai.c";

void set_skills(int j)
{
	create_family("阎罗地府",3,"");
	set_level(j);
        set_skill("unarmed",j*10);
        set_skill("dodge",j*10);
        set_skill("parry",j*10);
        set_skill("force",j*10);
        set_skill("spells",j*10);
 	switch(random(4))
 	{
 		case 0 :
 			set_skill("whip",j*10);
        		set_skill("hellfire-whip",j*10);
        		map_skill("whip", "hellfire-whip");
        		map_skill("parry", "hellfire-whip");
        		carry_object(0,"whip",1)->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"whip", "three" :),
        			(: perform_action,"whip", "ldlh" :),
        			(: perform_action,"whip", "biluo" :),
        			(: exert_function, "sheqi" :),
        		}));	
			break;
		case 1 :	
        		set_skill("stick",j*10);
        		set_skill("kusang-bang",j*10);
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
			set_skill("sword",j*10);
			set_skill("zhuihun-sword",j*10);
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
        set_skill("ghost-steps",j*10);
        set_skill("jinghun-zhang",j*10);
        set_skill("tonsillit",j*10);
        set_skill("gouhunshu",j*10);
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