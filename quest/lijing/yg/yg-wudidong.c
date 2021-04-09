inherit __DIR__"yaoguai.c";

void set_skills(int j)
{
	create_family("陷空山无底洞",3,"");	
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 	switch(random(3))
 	{
 		case 1 : 
        		set_skill("blade", j);
        		set_skill("kugu-blade", j);
        		map_skill("parry", "kugu-blade");
        		map_skill("blade", "kugu-blade");
        		carry_object(0,"blade",1)->wield();
        		set("chat_msg_combat", ({
        			(: perform_action,"blade", "pozhan" :),
        			(: perform_action,"blade", "diyu" :),
        			(: perform_action,"blade", "shendao" :),
        		}));
        		break;
        	default :		
        		set_skill("sword",j);
        		set_skill("qixiu-jian",j);
        		map_skill("parry", "qixiu-jian");
        		map_skill("sword", "qixiu-jian");
        		carry_object(0,"sword",1)->wield();
        		set("chat_msg_combat", ({
        			(: perform_action,"sword", "yaowu" :),
        			(: perform_action,"sword", "zxzx" :),
        			(: cast_spell, "huanying" :),
        		}));
	       		break;
        }			
        set_skill("lingfu-steps", j);
        set_skill("yaofa", j);
        set_skill("huntian-qigong", j);
        set_skill("yinfeng-zhua", j);
        map_skill("force", "huntian-qigong");
        map_skill("spells", "yaofa");
        map_skill("dodge", "lingfu-steps");
        map_skill("unarmed", "yinfeng-zhua");
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	set("class","yaomo");
}
