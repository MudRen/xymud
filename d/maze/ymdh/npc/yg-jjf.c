inherit __DIR__"yaoguai.c";

void set_skills(int j)
{
	create_family("将军府",3,"");	
	set_level(j);		
        set_skill("unarmed",j*10);
        set_skill("dodge",j*10);
        set_skill("parry",j*10);
        set_skill("force",j*10);
        set_skill("spells",j*10);
 	switch(random(3))
 	{
        	case 0 :
        		set_skill("spear",j*10);
        		set_skill("bawang-qiang",j*10);
        		map_skill("spear","bawang-qiang");
        		map_skill("parry", "bawang-qiang");
        		carry_object(0,"spear",1)->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"spear", "bugong" :),
        			(: perform_action,"spear", "juanlian" :),
        			(: perform_action,"spear", "huima" :),
        			(: perform_action,"spear", "ba" :),
        		}));	
			break;
        	default :
        		set_skill("axe",j*10);
        		set_skill("sanban-axe",j*10);
        		map_skill("axe","sanban-axe");
        		map_skill("parry", "sanban-axe");
        		carry_object(0,"axe",1)->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"axe", "potian" :),
        			(: perform_action,"axe", "sanban" :),
        			(: perform_action,"axe", "kai" :),
        			(: perform_action,"axe", "pidi" :),
        		}));	
			break;
	}		        		
        set_skill("yanxing-steps",j*10);
        set_skill("changquan",j*10);
        set_skill("lengquan-force",j*10);
        set_skill("baguazhou",j*10);

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
