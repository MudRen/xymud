#include <combat.h>
#include <ansi.h>
inherit __DIR__"n.c"; 

void setname() 
{
set_name("凝眸仙子", ({"ningmou xianzi", "ningmou", "xianzi"}));
set("long",@LONG
百花谷主一直是个迷一样的人物，甚至仍然有人说她是仙子。大
约五十年前，一个采药的小童在林间迷路，在饥渴绝望的时刻，花丛
中翩翩飘下一美丽女子，为他指明了出去的道路。时间飞逝，当年的
小童也变成了白发老翁，但在他心中一直把当年救她的女子当成上天
派下来拯救他的仙子，因为她在花间飞舞那轻盈的身姿，根本就不象
凡人......
LONG);
set("gender", "女性");
set("age", 25);
set("rank_info/respect", "神仙");
set("per", 35);

create_family("百花谷",2,"百花谷主");

set_skill("unarmed", 700);
set_skill("dodge", 700);
set_skill("parry", 700);
set_skill("force", 700);
set_skill("spells", 700);

set_skill("whip", 700);
set_skill("jueqingbian", 700);
set_skill("sword",700);
set_skill("zongheng-sword",700);
set_skill("wuyou-steps", 700);
set_skill("baihua-xianfa", 700);
set_skill("rainbow-zhi", 700);
set_skill("siji-zhang", 700);
set_skill("brightjade-force", 700);

map_skill("force", "brightjade-force");
map_skill("sword", "zongheng-sword");
map_skill("whip","jueqingbian");
map_skill("parry", "zongheng-sword");
map_skill("spells", "baihua-xianfa");
map_skill("dodge", "wuyou-steps");
map_skill("unarmed", "rainbow-zhi");
set("skillmark/zongheng-sword",({"heng","zong"})[random(2)]); 
set("skillmark/brightjade-force","yes");
}

int is_boss(){return 1;}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",68600000);
	set("daoxing",68600000);
	i = 5000+random(5000);
	add_temp("apply/karma",i);
	carry_object(0,"sword",1)->wield();
	add_temp("apply/karma",-i);
}

void tiaozhan_hit(object who)
{
	object *inv,weapon;
	string msg,*msgs;
	int d,i,k;
	remove_call_out("tiaozhan_hit");
	this_object()->stop_busy();	
	if( !who || !environment() || !this_object()->is_fighting(who) )
	{
		powerup(1);
		remove_all_killer();
		if( environment() )
			all_inventory(environment())->remove_killer(this_object());
		return;
	}
	weapon = query_temp("weapon");
	if( !weapon || weapon->query("skill_type")!="sword" )
	{
		if( query_temp("apply/damage")<500 )
			set_temp("apply/damage",500);
		if( !who->is_busy() && random(5)==2 )
		{
			message_vision(HIC"$N"HIC"随风而舞，抬起头来朝$n"HIC"妩媚地一笑，如沉鱼落雁，倾国倾城！\n"NOR,this_object(),who);
			if( random(3) )
			{
				message_combatd(HIR"$n"HIR"神不守舍地看着$N"HIR"醉人的容颜，顿时不知所措！\n"NOR,this_object(),who);
				who->start_busy(3);
			}
			else	message_combatd(HIR"不料确被$N"HIR"看破，毫不为所动！$N"HIR"攻其不备，$p反被打了个措手不及！\n"NOR,who,this_object());
		}
		else if( random(2) )
			command("exert hanyulingfeng");
		else if( random(2) )
		{
			msg = HIC"$N"HIC"运起无忧步法，身形恬静轻柔，飘忽不定！$N"HIC"身形突然旋转，回飞，凝神息气，一道劲飞向$n"HIC"。\n"NOR;
    		message_vision(msg,this_object(),who);
    		if( random(3) )
    		{
    			d = 300+random(500);
				who->receive_wound("kee", d, this_object(),TYPE_PERFORM);
				who->receive_damage("kee", d, this_object(),TYPE_PERFORM);
        		if( d<350 )
                	msg = HIY"结果$n"HIY"受到$N"HIY"的明玉神功气劲的攻击，闷哼一声。\n"NOR;
        		else if( d<450 )
                	msg = HIY"结果$n"HIY"被$N"HIY"的明玉神功气劲一击，「嘿」地一声退了两步。\n"NOR;
        		else if( d<650 )
                	msg = HIR"结果$n"HIY"被$N"HIY"的明玉神功气劲一重击，胸口有如受到一记重锤，连退了五六步！\n"NOR;
        		else    
        			msg = RED"结果$n"RED"被$N"RED"的明玉神功气劲击中，眼前一黑，象一捆稻草一样飞出去好几丈远！\n"NOR;
        	}
        	else	msg = CYN"可是$p看破了$P的企图，并没有上当。\n"NOR;		
			message_combatd(msg,this_object(),who);	
		}
		else
		{
			msg = HIY "$N"HIY"忽然身形一拧，越在半空，双臂急挥，双掌化十掌、百掌、千掌、万掌，犹如「四季飞花」，把$n"HIY"完全罩在掌风之中。\n"NOR;
			message_combatd(msg,this_object(),who);	
			set("actions",(: call_other, "/daemon/skill/siji-zhang", "query_action" :));
			set("SJZ",8);
			COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM);
			set("SJZ",16);
			COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM);
			set("SJZ",24);
			COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM);
			if( random(2) )
			{
				set("SJZ",9);
				COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM);
			}
			if( random(2) )
			{
				set("SJZ",15);
				COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM);
			}
			if( random(2) )
			{
				set("SJZ",22);
				COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM);
			}
			delete("SJZ");
			reset_action();
		}
	}	
	else
		QUEST_D->randomPfm(this_object());	
	call_out("tiaozhan_hit",3,who);
}

void tell_object(object who,string arg)
{
	arg = HIG"【星月挑战】"+arg+NOR;
	return efun::tell_object(who,arg);
}

void reward_ob(object who)
{
	object gift,weapon;    
	mapping skill;
	string *skills,temp,*ar;
	int i,pp;
	
	remove_call_out("tiaozhan_hit");
	if( !who || !userp(who) )
		return;

	if( time()<who->query("mark/tiaozhan/last_die")+3600      	//假死时间没到
	 || who->query("combat_exp")<10000
	 || who->query("daoxing")<10000 
	 || !who->query("obstacle/reward") )	
	{	 	
		tell_object(who,"你条件不够，无法在此地图得到任何附加奖励。\n");
		return;
	}

	if( !is_pass(who) )
	{
		who->set("mark/tiaozhan/"+query("name"),1);
		who->add("mark/tiaozhan/num",1);
	}
		
	if( random(30)>10 )
	{
		who->add("potential",50000);	
		tell_object(who,"你获得了50000点潜能。\n");
		who->add("combat_exp",-3000);
		who->add("daoxing",-3000);
		who->save();
		tell_object(who,"因为获得追加奖励，你失去了3000点的武学和道行。\n");
	}			
	
	pp = who->query_temp("tiaozhan_weapon_get");
	pp+= 1;			
	if( random(pp)==0 )
	{
		ar = ({ "sword","unarmed",});	
		gift = new("/d/obj/nweapon/"+ar[random(sizeof(ar))]);
		i = environment()->query("number");
		i = 6000+i*500;
		i = i+who->query_kar()*30;
		i = i-pp*50;
		add_temp("apply/karma",i);
		set_skill("force",300+random(400));
		gift->init_weapon(this_object());
		add_temp("apply/karma",-i);
		if( gift->move(who) )
		{
			CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->short()+HIC"。"NOR);			   
			who->add_temp("tiaozhan_weapon_get",1);
			who->add("combat_exp",-5000);
			who->add("daoxing",-5000);
			who->save();
			tell_object(who,"因为获得追加奖励，你失去了5000点的武学和道行。\n");		 
		}
		else	destruct(gift);
	}	
	else if( random(20)>5 )
	{
		gift = new(sprintf("/d/obj/equip/armor_bd%d",1+random(4)));
		if( gift->move(who) )
		{
			CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->name()+HIC"。"NOR);			   
			who->add("combat_exp",-5000);
			who->add("daoxing",-5000);
			who->save();
			tell_object(who,"因为获得追加奖励，你失去了5000点的武学和道行。\n");		 
		}
		else	destruct(gift);
	}
	return;
}