inherit __DIR__"yaoguai.c";

void set_skills(int j)
{
	create_family("将军府",3,"");			
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 	switch(random(3))
 	{
        	case 0 :
        		set_skill("spear", j);
        		set_skill("bawang-qiang", j);
        		map_skill("spear","bawang-qiang");
        		map_skill("parry", "bawang-qiang");
        		carry_object(0,"spear",1)->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"spear", "bugong" :),
        			(: perform_action,"spear", "juanlian" :),
        		}));	
			break;
        	default :
        		set_skill("axe",j);
        		set_skill("sanban-axe",j);
        		map_skill("axe","sanban-axe");
        		map_skill("parry", "sanban-axe");
        		carry_object(0,"axe",1)->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"axe", "potian" :),
        			(: perform_action,"axe", "sanban" :),
        		}));	
			break;
	}		        		
        set_skill("yanxing-steps", j);
        set_skill("changquan", j);
        set_skill("lengquan-force", j);
        set_skill("baguazhou", j);

        map_skill("force", "lengquan-force");
        map_skill("spells", "baguazhou");
        map_skill("dodge", "yanxing-steps");
        map_skill("unarmed", "changquan");
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	set("class","fighter");
}
