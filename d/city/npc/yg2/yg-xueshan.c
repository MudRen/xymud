inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("大雪山",4,"");
        set("title","冰天雪地");
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
        		carry_object(0,"blade",random(10))->wield();	
			break;
		default :
			set_skill("sword",j);
			set_skill("sword",j);
			map_skill("sword", "bainiao-jian");
        		map_skill("parry", "bainiao-jian");
        		carry_object(0,"sword",random(10))->wield();	
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
	setup();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	carry_object(0,"fork",random(10))->wield();
	powerup(0,1);
	set("env/wimpy",10);
	set("class","yaomo");
}       