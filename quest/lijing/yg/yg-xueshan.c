inherit __DIR__"yaoguai.c";

void set_skills(int j)
{
	create_family("大雪山",3,"");
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 	switch(random(2))
 	{
 		case 1 :
 			set_skill("blade", j);
        		set_skill("bingpo-blade", j);
        		map_skill("blade", "bingpo-blade");
        		map_skill("parry", "bingpo-blade");
        		carry_object(0,"blade",1)->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"blade", "ninxie" :),
        			(: perform_action,"blade", "daobo" :),
        			(: perform_action,"blade", "bingxue" :),
        		}));	
			break;
		default :
			set_skill("sword",j);
			set_skill("bainiao-jian",j);
			map_skill("sword", "bainiao-jian");
        		map_skill("parry", "bainiao-jian");
        		carry_object(0,"sword",1)->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"sword", "chaofeng" :),
        			(: perform_action,"sword", "fengwu" :),
        		}));	
			break;	
	}		
        set_skill("xiaoyaoyou", j);
        set_skill("dengxian-dafa", j);
        set_skill("ningxie-force", j);
        set_skill("cuixin-zhang", j);
        map_skill("force", "ningxie-force");
        map_skill("spells", "dengxian-dafa");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("unarmed", "cuixin-zhang");
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"fork",1)->wield();
	set("class","yaomo");
}       