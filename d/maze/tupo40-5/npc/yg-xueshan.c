#include <ansi.h>
inherit __DIR__"guai.c";

void set_skills()
{
	int j = 390;
	create_family("大雪山",4,"");
	set_level(39);
	set("env/test","HIM");
	
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
        setup();
 	switch(random(2))
 	{
 		case 1 :
 			set_skill("blade", j);
        		set_skill("bingpo-blade", j);
        		map_skill("blade", "bingpo-blade");
        		map_skill("parry", "bingpo-blade");
        		carry_object(0,"blade",1)->wield();	
        		break;
		default :
			set_skill("sword",j);
			set_skill("sword",j);
			map_skill("sword", "bainiao-jian");
        		map_skill("parry", "bainiao-jian");
        		carry_object(0,"sword",1)->wield();	
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
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"fork",1)->wield();
	powerup(0,1);
	delete("env/wimpy");
	set("class","yaomo");
}       

