// bula and mon@xyj
inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("五庄观",4,"");
	set("title","五庄观凶徒");
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 
 	set("chat_chance_combat", 1+2*level);
 	switch(random(5))
 	{
 		case 0 :
        		set_skill("hammer", j);
        		set_skill("kaishan-chui", j);
        		map_skill("hammer","kaishan-chui");
        		map_skill("parry","kaishan-chui");
        		carry_object(0,"hammer",random(10))->wield();
		        set("chat_msg_combat", ({
        			(: perform_action,"hammer", "jin" :),
        			(: exert_function, "juding" :),
        		}));
        		break;
        	case 1 :
        		set_skill("sword",j);
        		set_skill("sanqing-jian",j);
        		map_skill("sword","sanqing-jian");
        		map_skill("parry","sanqing-jian");
        		carry_object(0,"sword",random(10))->wield();
        		set("chat_msg_combat", ({
        			(: perform_action,"sword", "sanqing" :),
        			(: exert_function, "juding" :),
        		}));
        		break;
        	case 2 :
        		set_skill("blade",j);
        		set_skill("yange-blade",j);
        		map_skill("blade","yange-blade");
        		map_skill("parry","yange-blade");
        		carry_object(0,"blade",random(10))->wield();
        		set("chat_msg_combat", ({
        			(: perform_action,"blade", "yange" :),
        			(: exert_function, "juding" :),
        		}));
        		break;
        	default :
        		set_skill("sword",j);
        		set_skill("xiaofeng-sword",j);
        		map_skill("sword","xiaofeng-sword");
        		map_skill("parry","xiaofeng-sword");
        		carry_object(0,"sword",random(10))->wield();
			set("chat_msg_combat", ({
        			(: perform_action,"sword", "huichang" :),
        			(: exert_function, "juding" :),
        		}));
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
	setup();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	set("env/wimpy",0);
	set("class","xian");
}
