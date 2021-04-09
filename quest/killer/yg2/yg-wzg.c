// bula and mon@xyj
inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("五庄观",4,"");
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 
 	switch(random(5))
 	{
 		case 0 :
        	case 1 :
        	case 3 :
        		set_skill("sword",j);
        		set_skill("sanqing-jian",j);
        		map_skill("sword","sanqing-jian");
        		map_skill("parry","sanqing-jian");
        		carry_object(0,"sword",1)->wield();
        		break;
        	case 2 :
        		set_skill("blade",j);
        		set_skill("yange-blade",j);
        		map_skill("blade","yange-blade");
        		map_skill("parry","yange-blade");
        		carry_object(0,"blade",1)->wield();
        		break;
        	default :
        		set_skill("sword",j);
        		set_skill("xiaofeng-sword",j);
        		map_skill("sword","xiaofeng-sword");
        		map_skill("parry","xiaofeng-sword");
        		carry_object(0,"sword",1)->wield();
        		break;
        }				
        set_skill("baguazhen", j);
        set_skill("taiyi", j);
        set_skill("wuxing-quan", j);
        set_skill("zhenyuan-force", j);

        map_skill("force", "zhenyuan-force");
        map_skill("spells", "taiyi");
        map_skill("dodge", "baguazhen");
        map_skill("unarmed", "wuxing-quan");
        set("env/test","HIB");
	setup();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	set("env/wimpy",0);
	set("class","xian");
	powerup(1,1);
}
