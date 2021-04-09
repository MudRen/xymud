#include <combat.h>
#include <ansi.h>
inherit __DIR__"n.c"; 

void setname() 
{
set_name("阎罗王", ({"yanluo wang", "wang","yanluo"}));
set("long","身穿大红蟒袍，头戴黑绸软巾。面如锅底，须若钢针，这就是阎罗王。\n");
set("gender", "男性");
set("age", 56);
set("national","鬼族");
set("title", "阴间十王之首");
set("class","youling");
set("per", 5);
set("int", 100);
set("con", 100);
set("str", 100);
create_family("阎罗地府", 2, "鬼魂");

set_skill("whip", 520);
set_skill("hellfire-whip", 520);
set_skill("stick",550);
set_skill("kusang-bang",550);
set_skill("ghost-steps", 520);
set_skill("jinghun-zhang", 520);
set_skill("tonsillit", 520);
set_skill("gouhunshu", 520);
set_skill("zhuihun-sword", 520);
set_skill("sword", 520);
set_skill("force", 520);
set_skill("spells", 520);
set_skill("literate", 520);
set_skill("parry", 520);
set_skill("dodge", 520);
map_skill("sword","zhuihun-sword");
map_skill("force", "tonsillit");
map_skill("whip", "hellfire-whip");
map_skill("stick","kusang-bang");
map_skill("parry", "kusang-bang");
map_skill("spells", "gouhunshu");
map_skill("dodge", "ghost-steps");
map_skill("unarmed", "jinghun-zhang");
}

int is_boss(){return 1;}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",28121600);
	set("daoxing",28121600);
	i = 5000+random(5000);
	add_temp("apply/karma",i);
	if( random(2) )
	{
		carry_object(0,"sword",1)->wield();
		map_skill("parry","zhuihun-sword");
	}
	else if( random(2) )
	{
		carry_object(0,"whip",1)->wield();
		map_skill("parry","hellfire-whip");
	}
	else
	{
		carry_object(0,"stick",1)->wield();
		map_skill("parry","kusang-bang");
	}
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
	if( !query_temp("shenli") )
	{
		message_vision(HIR"$N"HIR"微一凝神，运起反五行摄气诀，头上冒出一股青气，脸部现出一个鬼形。。。\n" NOR,this_object());
		d = query_skill("force")/5;
 		add_temp("apply/attack", d);  
        add_temp("apply/dodge",d);    
        add_temp("apply/parry",d);
        add_temp("apply/strength",d);
        set_temp("shenli", 1);
    }
    if( !present("hell guard",environment()) )
    	command("cast invocation");
	if( random(3)==1 )    	
	{
		weapon = query_temp("weapon");
		if( !weapon )
		{
			if( random(2) )
			{
				msg = HIR"\n$N"HIR"面带狞笑，露出白森森的牙齿往$n"HIR"的鼻孔凑了过去，张嘴就是一吸！\n"NOR;
				message_vision(msg,this_object(),who);
				if( random(3) )
				{
					msg +=  HIR "结果$p头皮一麻，只觉得体内阳气源源不断地流了出去！\n" NOR;
					message_combatd(msg,this_object(),who);
					d = 100+random(300);
					who->receive_damage("kee",d,this_object(),TYPE_PERFORM);
					this_object()->receive_curing("kee",d/3*2);
					this_object()->receive_heal("kee",d);
					this_object()->receive_curing("sen",d/3*2);
					this_object()->receive_heal("sen",d);
					COMBAT_D->report_status(who);
				}
				else	message_combatd(HIR "结果$p一扭头，避了开去！\n" NOR,this_object(),who);
			}	
			else
			{
				message_vision(HIB"\n$N"HIB"口中默念几声：世事无常，死生无常……偏偏今天你"+who->name()+HIB"撞到我喜怒无常，你任命吧，看爪！\n"NOR,this_object(),who);
				if( random(3) )
				{
			        message_combatd(HIG"\n$n"HIG"身子一晃，背上留下了一个惨绿色的爪痕！\n"NOR,this_object(),who);
			        d = 100+random(250);
		    	    who->receive_wound("kee",d,this_object(),TYPE_PERFORM);     
       				who->receive_damage("kee",d,this_object(),TYPE_PERFORM);
	       			who->start_busy(random(2));
    	   			who->apply_condition("hell_zhua",(int)who->query_condition("hell_zhua")+2+d/5);
       				COMBAT_D->report_status(who,1);
					COMBAT_D->report_status(who);
				}
				else
				{
					msg = HIY"\n$n身子一闪，躲开了这一抓！\n"NOR;
					message_combatd(msg,this_object(),who);
				}						
			}				
		}
		else if( weapon->query("skill_type")=="whip" && random(3)==1 )
		{
			msg = HIB"$N"HIB"默运神功，手中"+weapon->name()+HIB"鬼气暴涨,漫天飞舞,瞬间在周身裹成一团鬼火,$n"HIB"的攻击被尽数挡回，忽然，$p发现有一股奇怪的力量袭来,四周一切似乎已经开始凝结！\n"NOR;
			message_vision(msg,this_object(),who);
			msg = HIW"\n$n"HIW "忽然如中魔一般，招招击向自己！\n"NOR;
			message_combatd(msg,this_object(),who);
			who->set_temp("pfm_msg",1);
			COMBAT_D->do_attack(who,who,who->query_temp("weapon"),TYPE_QUICK);
			COMBAT_D->do_attack(who,who,who->query_temp("weapon"),TYPE_QUICK);
			COMBAT_D->do_attack(who,who,who->query_temp("weapon"),TYPE_QUICK);
			who->set_temp("pfm_msg",0);
		}			
		else if( weapon->query("skill_type")=="stick" )
		{
        	msg = HIC"$N"HIC"忽然将"+weapon->name()+HIC"一分，现出"NOR RED"青面獠牙"NOR HIC"的原形，欺近$n"HIC"的身前，张嘴便向$p的咽喉咬去。\n"NOR;
        	message_vision(msg,this_object(),who);
        	if( random(3) )
        	{
	        	msg = HIC "$n"HIC"只觉得咽喉一阵剧痛，$N"HIC"正在狂吸$p的鲜血！\n"NOR;
    	    	message_combatd(msg,this_object(),who);
				d = 200+random(300);
				who->receive_wound("kee",d,this_object(),TYPE_PERFORM);
				COMBAT_D->report_status(who,1);
				this_object()->receive_curing("kee",d/3*2);
				this_object()->receive_heal("kee",d);
				this_object()->receive_curing("sen",d/3*2);
				this_object()->receive_heal("sen",d);
				add("force",50+random(100));	        	
        	}
        	else	message_combatd(HIC "只见$n"HIC"不慌不忙，轻轻一闪，躲过了$P的利齿！\n"NOR,this_object(),who);
		}	
		else if( random(3)==1 )
		{
			message_vision(HIB "\n$N"HIB"法袍一舞，剑招急若骤雨，漫天的剑影裹着一道道黑气向$n"HIB"卷了过去！"HIR"$n"HIR"只觉眼前剑光飞舞，周围鬼影幢幢！似乎已经身陷鲜血淋漓的十八层地狱中一样！"HIB"$n"HIB"腾挪闪跃，竭力招架，试图冲破眼前的黑雾。\n"NOR, this_object(),who);
			message_combatd(HIB"\n$N"HIB"既占先机，後着绵绵而至，$n"HIB"中了一剑，大骇之下，急向後退。"HIR"$p"HIR"只觉一缕缕鲜血从伤口溅出，自身的灵魂逐渐飘出体外，身体越来越虚弱。\n"NOR,this_object(),who);
       		who->set_temp("no_exert",([
                       "start" : time(),
                       "time"  : 10,
                       "msg"   : "你的内息已被"+name()+"的『油尽灯枯』 打乱，暂时无法使用内功。\n",
               ]));    
			message_combatd(HIR"$n觉得自己无法再运起气来了！\n"NOR,this_object(),who);
			who->receive_wound("kee", 300+random(300), this_object(),TYPE_PERFORM);
	        COMBAT_D->report_status(who,1);
		}
		else
		{
				SPELL_D->attacking_cast(
    	    		this_object(), 
        			who, 
        			120,    
        			50,     
	        		"sen",         
    	    		HIC "$N"HIC"对$n"HIC"阴阴地笑着：阎王叫你三更死，不敢留你到五更。。。\n" NOR,
        	    	HIC "$n"HIC"受到$N"HIC"影响，显然有点魂不守舍了！\n" NOR, 
            		HIC "但是$n"HIC"神情专注，对$N"HIC"理都不理。\n" NOR, 
            		HIC "但是$n"HIC"眼一瞪：光天化日之下，岂由恶鬼横行！\n" NOR, 
	            	HIC "结果$n"HIC"反而有点魂不守舍了！\n" NOR);
		}
	}	
	else
		QUEST_D->randomPfm(this_object());
	call_out("tiaozhan_hit",3+random(2),who);
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
		
	if( random(30)>18 )
	{
		who->add("potential",50000);	
		tell_object(who,"你获得了50000点潜能。\n");
		who->add("combat_exp",-3000);
		who->add("daoxing",-3000);
		who->save();
		tell_object(who,"因为获得追加奖励，你失去了3000点的武学和道行。\n");
	}			
	
	pp = who->query_temp("tiaozhan_weapon_get");
	pp+= 3;			
	if( random(pp)==0 )
	{
		ar = ({ "sword","stick","whip",});	
		gift = new("/d/obj/nweapon/"+ar[random(sizeof(ar))]);
		i = environment()->query("number");
		i = 1500+i*500;
		i = i+who->query_kar()*30;
		i = i-pp*50;
		add_temp("apply/karma",i);
		set_skill("force",150+random(200));
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
	else if( random(20)>14 )
	{
		gift = new(sprintf("/d/obj/equip/armor_bd%d",1+random(4)));
		if( gift->move(who) )
		{
			CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->short()+HIC"。"NOR);			   
			who->add("combat_exp",-5000);
			who->add("daoxing",-5000);
			who->save();
			tell_object(who,"因为获得追加奖励，你失去了5000点的武学和道行。\n");		 
		}
		else	destruct(gift);
	}
	return;
}