#include <ansi.h>
inherit SUPER_NPC;

void create()
{
        set_name("慧平", ({"hui ping", "ping"}));
        set_level(30);
        set("gender", "男性" );
        set("age", 23);
        set("attitude", "peaceful");
	set("class", "taoist");
        setup();
}

void set_levels(int i)
{
	int k;
	mapping names;
	string name;
	if( i<30 )
		i = 30;
	names = NAME_D->random_name("male");
	name = names["name"];
	name = sprintf("%s",name[2..3]);
	set_level(i);
	if( i>90 )
	{
		name = "广"+name+"子";
		k = 2;
	}
	else if( i<40 )
	{
		k = 4;
		name = "慧"+name;
	}
	else
	{
		name = "云"+name;
		k = 3;
	}
	set_name(name,({"di zi"}));
	delete("title");
	delete("daoxing");
	create_family("方寸山三星洞", k, "弟子");
        set_skill("unarmed",i*10);
        set_skill("dodge",i*10);
        set_skill("parry",i*10);
        set_skill("spells",i*10);  
        set_skill("dao",i*10);
        set_skill("literate",i*10);
        set_skill("stick",i*10);  
        set_skill("qianjun-bang",i*10);
        set_skill("puti-zhi",i*10);  
        set_skill("jindouyun",i*10);
        set_skill("dodge",i*10);  
        set_skill("force",i*10);   
        set_skill("wuxiangforce",i*10);
        map_skill("spells", "dao");
        map_skill("unarmed", "puti-zhi");
        map_skill("force", "wuxiangforce");
        map_skill("stick", "qianjun-bang");
        map_skill("parry", "qianjun-bang");
        map_skill("dodge", "jindouyun");
	set("force_factor",query("force")/50);
        set("mana_factor",query("spells")/50);
        setup();
        carry_object(0,"stick",1)->wield();
        carry_object(0,"shoes",1)->wear();
        carry_object(0,"cloth",1)->wear();
        carry_object(0,"pifeng",1)->wear();
        carry_object(0,"ring",1)->wear();
	powerup(0,1);
}

void die()
{
	if( environment() )
		message("vision","\n"+this_object()->name()+"脸色一变，闪身退回大阵之中。\n\n",environment());
	destruct(this_object());
}

void unconcious()
{
	::unconcious();
	revive();
	powerup(0,1);
}	