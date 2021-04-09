#include <ansi.h>
inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("火云洞",4,"");
	set("nickname",HIR"别离在今晨 见尔当何秋"NOR);  
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 	set("chat_chance_combat", 1+2*level);
        set_skill("moyun-shou",j);
        set_skill("moshenbu",j);
        set_skill("huomoforce", j);
        set_skill("pingtian-dafa", j);
        set_skill("dali-bang", j);
        switch(random(2))
        {
        	case 0 :
        		set_skill("stick", j);
			map_skill("stick","dali-bang");
			carry_object(0,"stick",1)->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"stick", "shenli" :),
        			(: exert_function, "bugong" :),
        		}));	
			break;	
		default :
			carry_object(0,"unarmed",1)->wield();	
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
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	set("env/wimpy",0);
	set("class","yaomo");
}
