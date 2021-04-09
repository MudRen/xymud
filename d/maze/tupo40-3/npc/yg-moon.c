#include <ansi.h>
inherit __DIR__"guai.c";

void set_skills()
{
	int j = 390;
	create_family("月宫",4,"");			
	set("gender","女性");
	set_level(39);
	set("env/test","HIM");
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
        set_skill("sword",j);
        set_skill("snowsword",j);
        set_skill("moondance", j);
        set_skill("moonshentong", j);
        set_skill("baihua-zhang", j);
        set_skill("moonforce", j);

        map_skill("force", "moonforce");
        map_skill("sword", "snowsword");
        map_skill("parry", "snowsword");
        map_skill("spells", "moonshentong");
        map_skill("dodge", "moondance");
        map_skill("unarmed", "baihua-zhang");
	
	setup();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"sword",1)->wield();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	set("force_factor",0);
	delete("env/wimpy");
	set("class","xian");
	powerup(0,1);
}