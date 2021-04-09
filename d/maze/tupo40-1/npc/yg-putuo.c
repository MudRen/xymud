#include <ansi.h>
inherit __DIR__"guai.c";

void set_skills()
{
	int j = 390;
	create_family("南海普陀山",4,"");		
	set_level(39);
	set("env/test","HIM");
	set_skill("unarmed", j);
	set_skill("dodge", j);
	set_skill("parry", j);
	set_skill("force", j);
	set_skill("spells", j);
	setup();
	switch(random(3))
	{
		case 1 :  
			set_skill("staff", j);
			set_skill("lunhui-zhang", j);
			map_skill("staff", "lunhui-zhang");
        		map_skill("parry", "lunhui-zhang");
        		carry_object(0,"staff",1)->wield();	
			break;
		default :
			set_skill("blade", j);
			set_skill("cibeidao", j);
			map_skill("blade", "cibeidao");
        		map_skill("parry", "cibeidao");
        		carry_object(0,"blade",1)->wield();	
			break;
	}	
	set_skill("lotusmove", j);
	set_skill("buddhism", j);
	set_skill("jienan-zhi", j);
	set_skill("lotusforce", j);
	map_skill("force", "lotusforce");
	map_skill("spells", "buddhism");
	map_skill("dodge", "lotusmove");
	map_skill("unarmed", "jienan-zhi");
	setup();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	delete("env/wimpy");
	set("class","bonze");
	powerup(0,1);
}

                               
          
