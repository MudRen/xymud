#include <combat.h>
#include <ansi.h>
inherit __DIR__"n.c";

void setname()
{
	int i;
	mapping names;
	string name,id,tmp,*ids;
	
	names = NAME_D->random_name("female");
	if( !names )
		set_name("踏雪",({"ta xue","xue","di zi",}));
	else
	{
		name = names["name"];
		ids = names["id"];
		id = ids[0];
		if( sscanf(id,"%s %s",tmp,id)==2 )
			ids = ({"yue "+id,id,"yue","di zi"});
		else
			ids = ({"yue","di zi",});	
		i = strlen(name);
		if( i<=2 )
			name = sprintf("%s",name[(i-1)..i]);
		else
			name = sprintf("%s",name[(i-1)..i]);
		name = "月"+name;			
		set_name(name,ids);
	}	
	set("my_master","xi wangmu");
set("gender", "女性");
set("age", 18+random(12));
set("class","xian");
set("attitude", "friendly");
set("cor", 30);
set("per", 30);
set_skill("literate", 420+random(60));
set_skill("unarmed",420+random(60));
set_skill("dodge",420+random(60));
set_skill("force",420+random(60));
set_skill("parry",420+random(60));
set_skill("sword",420+random(60));
set_skill("spells",420+random(60));
set_skill("whip",420+random(60));
set_skill("jueqingbian",420+random(60));
set_skill("moonshentong",420+random(60));
set_skill("baihua-zhang",420+random(60));
set_skill("moonforce",420+random(60));
set_skill("snowsword",420+random(60));
set_skill("moondance",420+random(60));
map_skill("spells", "moonshentong");
map_skill("unarmed", "baihua-zhang");
map_skill("force", "moonforce");
map_skill("sword", "snowsword");
map_skill("parry", "snowsword");
map_skill("dodge", "moondance");
map_skill("whip","jueqingbian");
create_family("月宫",3, "弟子");
}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",11059200);
	set("daoxing",11059200);
	i = 2000+random(5000);
	add_temp("apply/karma",i);
	if( random(2) )
	{
		carry_object(0,"sword",1)->wield();
		map_skill("parry","snowsword");
		set("force_factor",0);
	}
	else
	{
		carry_object(0,"whip",1)->wield();
		map_skill("parry","jueqingbian");
	}
	add_temp("apply/karma",-i);
}

void tiaozhan_hit(object who)
{
	object weapon;
	string msg;
	int d,k;
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
		message_vision(HIW"$N"HIW"略一提气，运起轻功，拔剑起舞。只见$P足不沾地，手中剑越舞越快，逐渐幻做一团白雾，满堂滚动。\n" NOR,this_object());
		d = query_skill("sword")/5;
 		add_temp("apply/attack", d);  
        add_temp("apply/dodge",d);    
        set_temp("shenli", 1);
    }
	if( random(6)==0 )
	{
		weapon = query_temp("weapon");
		if( !weapon )
		{
			msg = MAG "\n\n$N"MAG"微微一笑，身子凌空而起，最高重的「"+HIG"天女散花"NOR+MAG"」转瞬而出，一时花香缭绕！$n"MAG"只觉眼前一花，一时竟然不知如何招架，更不用说躲闪了！\n"NOR;
			message_vision(msg,this_object(),who);
			if( random(3) )
			{
				msg = HIM "\n这些花瓣看似柔弱无力，却如疾风骤雨般射向$n,三千六百片花瓣深深的嵌入$n"HIM"肉里！\n\n" NOR;
				message_combatd(msg,this_object(),who);
				who->receive_wound("kee",500,this_object(),TYPE_PERFORM);
				COMBAT_D->report_status(who,1);
			}	
			else
			{
				msg = HIM"\n谁知$n"HIM"竟险中求胜，长袖一摆，已将所有花瓣打落！\n"NOR;
				message_combatd(msg,this_object(),who);
			}
		}
		else if( weapon->query("skill_type")=="sword" )
		{
			message_vision(HIM"\n$N"HIM"仰天长叹：蒹霞苍苍，白露为霜，所谓伊人，在水一方。随着歌声$P翩翩起舞。\n" NOR,this_object());
			msg = HIM "$n"HIM"听着$N"HIM"凄婉的歌声，看着醉人的舞步，全然忘了自己在战斗中。\n" NOR;
			message_combatd(msg,this_object(),who);
			set_temp("pfm_msg",1);
         	msg =  HIG "\n------天仙降临------"NOR;
        	COMBAT_D->do_attack(this_object(),who,weapon,TYPE_PERFORM,msg);
         	msg =  HIR "\n------天各一方------"NOR;
        	COMBAT_D->do_attack(this_object(),who,weapon,TYPE_PERFORM,msg);
         	msg =  HIB "\n------峰回路转------"NOR;
        	COMBAT_D->do_attack(this_object(),who,weapon,TYPE_PERFORM,msg);
        	msg =  HIC "\n------闭月羞花------"NOR;
			COMBAT_D->do_attack(this_object(),who,weapon,TYPE_PERFORM,msg);
			msg =  MAG "\n------绝世之容------"NOR;
			set_temp("WX_perform",10);
			COMBAT_D->do_attack(this_object(),who,weapon,TYPE_PERFORM,msg);
         	msg =  HIW "\n***万仙临界の天人合一*** \n"NOR;
         	set_temp("WX_perform",10);
			COMBAT_D->do_attack(this_object(),who,weapon,TYPE_PERFORM,msg);
        	set_temp("WX_perform",0);
        	set_temp("pfm_msg",0);
        	reset_action();	
        	msg =  HIM "\n$n皤然醒悟，发现自己迷恋$N的歌声和舞姿而忘了攻击。\n"NOR;
			message_combatd(msg,this_object(),who);
		}
		else 
		{
			message_vision(HIW"\n$N"HIW"鞭法一变，茫茫离恨，万丈情劫席卷而来！~~~\n"NOR,this_object());
			message_combatd(HIC"\n夕殿萤飞思悄然，孤灯挑尽未成眠\n"NOR,this_object());
			message_combatd(HIC"\n迟迟钟鼓初长夜，耿耿星河欲曙天\n"NOR,this_object());
			message_combatd(HIC"\n鸳鸯瓦冷霜华重，翡翠衾寒谁与共\n"NOR,this_object());
			message_combatd(HIC"\n悠悠生死别经年，魂魄不曾来入梦\n"NOR,this_object());
			if( random(3) )
			{
				message_combatd(HIW"\n$n"HIW"听着听着不由心底一酸，心神荡漾，三魂六魄都丢光了\n"NOR,this_object(),who);
				who->receive_wound("kee",450,this_object(),TYPE_PERFORM);
				COMBAT_D->report_status(who,1);
			}
			else
				message_combatd(HIG"\n$n"HIG"冷哼一声，五音不全，跑调了都不知道？\n"NOR	,this_object(),who);
		}		
	}
	else
		QUEST_D->randomPfm(this_object());
	call_out("tiaozhan_hit",4,who);
}