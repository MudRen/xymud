inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("陷空山无底洞",4,"");	
        set("title","天魔解体");
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
        		carry_object(0,"blade",random(10))->wield();
        		break;
        	case 2 :		
        		set_skill("sword",j);
        		set_skill("qixiu-jian",j);
        		map_skill("parry", "qixiu-jian");
        		map_skill("sword", "qixiu-jian");
        		carry_object(0,"sword",random(10))->wield();
	       		break;
        	default :
        		set_skill("qixiu-jian",j);
        		map_skill("parry", "qixiu-jian");
        		carry_object(0,"unarmed",random(10))->wield();
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
	setup();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	set("env/wimpy",10);
	set("class","yaomo");
}
