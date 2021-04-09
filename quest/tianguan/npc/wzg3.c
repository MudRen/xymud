#include <combat.h>
#include <ansi.h>
inherit __DIR__"n2.c"; 
      
void setname() 
{
	set_name("镇元大仙",({"zhenyuan daxian","daxian","zhenyuan"}));
	set("long",@LONG
交游遍三界，桃李漫五行。好一位地仙之祖！
LONG);
	set("gender", "男性");
	set("age", 45);
	set("per", 40);
	set("int", 100);
	set("con", 100);
	set("title","五庄观观主");
	set("rank_info/respect", "观主");
	create_family("五庄观",1,"丝");	
	set_skill("unarmed",700);
	set_skill("wuxing-quan", 700);
	set_skill("dodge",700);
	set_skill("baguazhen",700);
	set_skill("parry",700);
	set_skill("sword",700);
	set_skill("sanqing-jian",700);
	set_skill("staff",700);
	set_skill("fumo-zhang",700);
	set_skill("hammer",700);
	set_skill("kaishan-chui",700);
	set_skill("blade",700);
	set_skill("yange-blade",700);
	set_skill("force",700);   
	set_skill("zhenyuan-force",700);
	set_skill("literate",700);
	set_skill("spells", 700);
	set_skill("taiyi", 700);
   	map_skill("spells", "taiyi");
   	map_skill("force", "zhenyuan-force");
   	map_skill("unarmed", "wuxing-quan");
   	map_skill("sword", "sanqing-jian");
   	map_skill("dodge", "baguazhen");
   	map_skill("staff", "fumo-zhang");
   	map_skill("blade", "yange-blade");
   	map_skill("hammer", "kaishan-chui");
}

void setup()
{
	::setup();      
	set("combat_exp",120000000);
	set("daoxing",120000000);
	if( random(2) )
		carry_object(0,"sword",1)->wield();	
	else if( random(2) )
		carry_object(0,"blade",1)->wield();	
	else
		carry_object(0,"staff",1)->wield();	
}

int is_job(){return 1;}