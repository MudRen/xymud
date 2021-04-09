#include <combat.h>
#include <ansi.h>
inherit __DIR__"n.c";

void create()
{
	int i;
	mapping names;
	string name,id,tmp,*ids;
	
	names = NAME_D->random_name("male");
	if( !names )
		set_name("邓久宫",({"deng jiugong","deng","di zi",}));
	else
	{
		name = names["name"];
		ids = names["id"];
		id = ids[0];
		if( sscanf(id,"%s %s",tmp,id)==2 )
			ids = ({"deng "+id,id,"deng","di zi"});
		else
			ids = ({"deng","di zi",});	
		i = strlen(name);
		if( i<=2 )
			name = sprintf("%s",name[(i-1)..i]);
		else
			name = sprintf("%s",name[(i-1)..i]);
		name = "邓"+name;			
		set_name(name,ids);
	}	
	set("my_master","huang feihu");
set("gender", "男性");
set("age", 20+random(20));
set("max_force", 9000);
set("force_factor", 125);
set("max_mana", 9000);
set_skill("spear", 400+random(51));
set_skill("force", 400+random(51));
set_skill("dodge", 400+random(51));
set_skill("stick", 400+random(51));
set_skill("literate", 400+random(51));
set_skill("dali-bang", 400+random(51));
set_skill("huoyun-qiang", 400+random(51));
set_skill("parry", 400+random(51));
set_skill("unarmed", 400+random(51));
set_skill("wuyue-spear", 400+random(51));
set_skill("spells", 400+random(51));
set_skill("pingtian-dafa", 400+random(51));
set_skill("moshenbu", 400+random(51));
set_skill("huomoforce", 400+random(51));
set_skill("moyun-shou", 400+random(51));
map_skill("force", "huomoforce");
map_skill("spells", "pingtian-dafa");
map_skill("unarmed", "moyun-shou");
map_skill("spear", "wuyue-spear");
map_skill("parry", "wuyue-spear");
map_skill("stick", "dali-bang");
map_skill("dodge", "moshenbu");
create_family("火云洞", 3, "巡山弟子");
setup();
}

void setup()
{
	int i;
	::setup();      
	set("combat_exp", 9112500);
	set("daoxing", 9112500);
	i = 2000+random(5000);
	add_temp("apply/karma",i);
	carry_object(0,"spear",1)->wield();	
	add_temp("apply/karma",-i);
}

void tiaozhan_hit(object who)
{
	object weapon;
	string msg;
	int d,k;
	this_object()->stop_busy();	
	remove_call_out("tiaozhan_hit");	
	if( !who || !environment() || !this_object()->is_fighting(who) )
	{
		powerup(1);
		remove_all_killer();
		if( environment() )
			all_inventory(environment())->remove_killer(this_object());
		return;
	}
	if( !query_temp("shenli") && random(4)==2 )
	{
		message_vision(HIR"$N"HIR"哞的一声吼，一提丹田气，运力于臂，枪上加力。只见$P四周烈火重重，火焰像一条巨龙一样蜿蜒在枪上,如此的气势吓的敌手心惊丹寒\n" NOR,this_object());
		d = query_skill("spear")/5;
 		add_temp("apply/attack", d);  
        add_temp("apply/strength",d);    
        set_temp("shenli", 1);
    }
	QUEST_D->randomPfm(this_object());
	call_out("tiaozhan_hit",5,who);
}