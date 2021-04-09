// bula and mon@xyj
inherit __DIR__"yaoguai.c";

void set_skills(int j)
{
	create_family("盘丝洞",3,"");
	set_level(j);
        set_skill("unarmed",j*10);
        set_skill("dodge",j*10);
        set_skill("parry",j*10);
        set_skill("force",j*10);
        set_skill("spells",j*10);
 
 	switch(random(2))
 	{
 		case 0 :
        		set_skill("sword",j*10);
        		set_skill("chixin-jian",j*10);
        		map_skill("sword","chixin-jian");
        		map_skill("parry","chixin-jian");
        		carry_object(0,"sword",1)->wield();
		        set("chat_msg_combat", ({
        			(: perform_action,"sword", "hongyan" :),
        			(: perform_action,"sword", "haotan" :),
        		}));
        		break;
        	default :
        		set_skill("whip",j*10);
        		set_skill("yinsuo-jinling",j*10);
        		map_skill("whip","yinsuo-jinling");
        		map_skill("parry","yinsuo-jinling");
        		carry_object(0,"whip",1)->wield();
        		set("chat_msg_combat", ({
        			(: perform_action,"whip", "feiyin" :),
        			(: perform_action,"whip", "wang" :),
        		}));
        		break;
        }				
        set_skill("yueying-wubu",j*10);
        set_skill("pansi-dafa",j*10);
        set_skill("lanhua-shou",j*10);
        set_skill("jiuyin-xinjing",j*10);

        map_skill("force", "jiuyin-xinjing");
        map_skill("spells", "pansi-dafa");
        map_skill("dodge", "yueying-wubu");
        map_skill("unarmed", "lanhua-shou");
	setup();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	set("class","yaomo");
}
