inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("火云洞",4,"");
	set("title","三昧真火");
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 	set("chat_chance_combat", 1+2*level);
        set_skill("moyun-shou",j+random(2));
        set_skill("moshenbu",j+random(2));
        set_skill("huomoforce", j+random(2));
        set_skill("pingtian-dafa", j+random(2));
        set_skill("dali-bang", j+random(2));
        switch(random(2))
        {
        	case 0 :
        		set_skill("stick", j+random(2));
			map_skill("stick","dali-bang");
			carry_object(0,"stick",random(10))->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"stick", "shenli" :),
        			(: exert_function, "bugong" :),
        		}));	
			break;	
		default :
			carry_object(0,"unarmed",random(10))->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"unarmed", "lei" :),
        			(: exert_function, "bugong" :),
        		}));	
			break;	
	}		
        map_skill("force", "huomoforce");
        map_skill("parry", "dali-bang");
        map_skill("spells", "pingtian-dafa");
        map_skill("dodge", "moshenbu");
        map_skill("unarmed", "moyun-shou");
        setup();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	set("env/wimpy",0);
	set("class","yaomo");
}
