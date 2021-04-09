// bula and mon@xyj
inherit __DIR__"yaoguai.c";

void set_skills(int j)
{
	create_family("蜀山派",3,"");
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 
 	switch(random(2))
 	{
 		case 0 :
        		set_skill("sword", j);
        		set_skill("mindsword", j);
        		map_skill("sword","mindsword");
        		map_skill("parry","mindsword");
        		carry_object(0,"sword",1)->wield();
		        set("chat_msg_combat", ({
        			(: perform_action,"sword", "jianqi" :),
        			(: perform_action,"sword", "tanzhi" :),
        		}));
        		break;
        	default :
        		set_skill("sword",j);
        		set_skill("canxin-jian",j);
        		map_skill("sword","canxin-jian");
        		map_skill("parry","canxin-jian");
        		carry_object(0,"sword",1)->wield();
        		set("chat_msg_combat", ({
        			(: perform_action,"sword", "ninglei" :),
        			(: perform_action,"sword", "xiangsi" :),
        		}));
        		break;
        }				
        set_skill("sevensteps", j);
        set_skill("taoism", j);
        set_skill("hunyuan-zhang", j);
        set_skill("zixia-shengong", j);

        map_skill("force", "zixia-shengong");
        map_skill("spells", "taoism");
        map_skill("dodge", "sevensteps");
        map_skill("unarmed", "hunyuan-zhang");
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	set("class","xian");
}
