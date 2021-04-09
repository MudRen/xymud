inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("方寸山三星洞",4,"");
	set("title","方寸妖道");
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 	set("chat_chance_combat", 1+2*level);
 	switch(random(2))
 	{
 		case 0 :
 			set_skill("stick", j);
        		set_skill("qianjun-bang", j);
        		map_skill("stick","qianjun-bang");
        		map_skill("parry", "qianjun-bang");
        		carry_object(0,"stick",random(10))->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"stick", "qiankun" :),
        			(: exert_function, "shenjia" :),
        		}));	
			break;
		default :
			set_skill("sword",j);
  			set_skill("liangyi-sword",j);
  			map_skill("sword","liangyi-sword");
  			map_skill("parry","liangyi-sword");
  			carry_object(0,"sword",random(10))->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"sword", "yin" :),
        			(: exert_function, "shenjia" :),
        		}));	
			break;
	}		
        set_skill("jindouyun", j);
        set_skill("wuxiangforce", j);
        set_skill("puti-zhi", j);
        set_skill("dao", j);
        map_skill("force", "wuxiangforce");
        map_skill("spells", "dao");
        map_skill("dodge", "jindouyun");
        map_skill("unarmed", "puti-zhi");

        setup();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	set("env/wimpy",0);
	set("class","taoist");
}