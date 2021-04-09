// bula and mon@xyj
inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("盘丝洞",4,"");
	set("title","佛灯孽徒");
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 
 	set("chat_chance_combat", 1+2*level);
 	switch(random(2))
 	{
 		case 0 :
        		set_skill("sword", j);
        		set_skill("chixin-jian", j);
        		map_skill("sword","chixin-jian");
        		map_skill("parry","chixin-jian");
        		carry_object(0,"sword",random(10))->wield();
		        set("chat_msg_combat", ({
        			(: perform_action,"sword", "hongyan" :),
        		}));
        		break;
        	default :
        		set_skill("whip",j);
        		set_skill("yinsuo-jinling",j);
        		map_skill("whip","yinsuo-jinling");
        		map_skill("parry","yinsuo-jinling");
        		carry_object(0,"whip",random(10))->wield();
        		set("chat_msg_combat", ({
        			(: perform_action,"whip", "feiyin" :),
        		}));
        		break;
        }				
        set_skill("yueying-wubu", j);
        set_skill("pansi-dafa", j);
        set_skill("lanhua-shou", j);
        set_skill("jiuyin-xinjing", j);

        map_skill("force", "jiuyin-xinjing");
        map_skill("spells", "pansi-dafa");
        map_skill("dodge", "yueying-wubu");
        map_skill("unarmed", "lanhua-shou");
	setup();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	set("env/wimpy",0);
	set("class","xian");
}
