#include <combat.h>
#include <ansi.h>
inherit __DIR__"n.c";

void setname()
{
	int i;
	mapping names;
	string name,id,tmp,*ids;
	
	names = NAME_D->random_name("male");
	if( !names )
		set_name("尉迟霸",({"yuchi ba","ba","di zi",}));
	else
	{
		name = names["name"];
		ids = names["id"];
		id = ids[0];
		i = strlen(name);
		if( i<=2 )
			name = sprintf("%s",name[(i-1)..i]);
		else
			name = sprintf("%s",name[(i-1)..i]);
		if( random(2) )
		{			
			if( sscanf(id,"%s %s",tmp,id)==2 )
				ids = ({"cheng "+id,id,"cheng","di zi"});
			else
				ids = ({"cheng","di zi",});	
			name = "程"+name;			
		}
		else if( random(2) )
		{			
			if( sscanf(id,"%s %s",tmp,id)==2 )
				ids = ({"yuchi "+id,id,"yuchi","di zi"});
			else
				ids = ({"yuchi","di zi",});	
			name = "尉迟"+name;			
		}
		else if( random(2) )
		{			
			if( sscanf(id,"%s %s",tmp,id)==2 )
				ids = ({"qin "+id,id,"qin","di zi"});
			else
				ids = ({"qin","di zi",});	
			name = "秦"+name;			
		}				
		else
		{			
			if( sscanf(id,"%s %s",tmp,id)==2 )
				ids = ({"luo "+id,id,"luo","di zi"});
			else
				ids = ({"luo","di zi",});	
			name = "罗"+name;			
		}				
		set_name(name,ids);
	}	
	set("my_master","lao ren");
	set("gender", "男性");
	set("age", 16+random(20));
	set("per", 15+random(20));
	set("int", 30);
	set("con", 100);
	set("str", 100);
	create_family("将军府", 2+random(3), "偏将");
	set("faith",10000);

set_skill("changquan",450+random(50));
set_skill("yanxing-steps",450+random(50));
set_skill("spear",450+random(50));
set_skill("mace",450+random(50));
set_skill("axe",450+random(50));
set_skill("force",450+random(50));
set_skill("unarmed",450+random(50));
set_skill("dodge",450+random(50));
set_skill("parry",450+random(50));
set_skill("spells",450+random(50));
set_skill("xuanyuan-archery",450+random(50));
set_skill("jinglei-mace",450+random(50));
set_skill("sanban-axe",450+random(50));
set_skill("archery",450+random(50));
set_skill("bawang-qiang",450+random(50));
set_skill("lengquan-force",450+random(50));
set_skill("literate",450+random(50));
set_skill("baguazhou",450+random(50));
map_skill("spells", "baguazhou");
map_skill("force", "lengquan-force");
map_skill("unarmed", "changquan");
map_skill("spear", "bawang-qiang");
map_skill("parry", "jinglei-mace");
map_skill("mace", "jinglei-mace");
map_skill("archery", "xuanyuan-archery");
map_skill("axe", "sanban-axe");
map_skill("dodge", "yanxing-steps");
set("chushi/chushi_jjf","yes");
}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",12500000);
	set("daoxing",12500000);
	i = 3000+random(5000);
	add_temp("apply/karma",i);
	if( random(2) )
	{
		carry_object(0,"axe",1)->wield();
		map_skill("parry","sanban-axe");
		set("family/jjf_type","axe");
	}
	else if( random(2) )
	{
		carry_object(0,"spear",1)->wield();
		map_skill("parry","bawang-qiang");
		set("family/jjf_type","spear");		
	}
	else
	{
		carry_object(0,"mace",1)->wield();
		map_skill("parry","jinglei-mace");
		set("family/jjf_type","mace");		
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
		message_vision(HIR"\n$N"HIR"微一凝神，运起静心诀，登时心平气稳，于周围一切警觉有加。\n"NOR,this_object());
		d = query_skill("force")/5;
 		add_temp("apply/attack", d);  
        add_temp("apply/dodge",d);    
        set_temp("shenli", 1);
    }
	if( random(8)==0 )
	{
		weapon = query_temp("weapon");
		if( !weapon )
		{
			if( who->is_busy() && random(3==0) )
			{
				msg = HIY "$N"HIY"突然向前迈上三大步，气沉丹田，一声闷喝，右拳一记「冲天炮」自腰间猛然挥出，势若奔雷、快若闪电却又简简单单、全无花巧，直奔$n"HIY"$l而去！\n"NOR;
				set_temp("pfm_msg",1);
				d = COMBAT_D->do_attack(this_object(),who,0,TYPE_PERFORM,msg);
				if( d>0 )
					message_combatd(HIR "\n$n"HIR"躲闪不及，被$N"HIR"冲天一拳正中前心，“嘭”一声闷响，前胸已然塌了下去，$n"HIR"的脸色变得煞白，一口鲜血自$p口中狂喷而出。\n"NOR,this_object(),who);
				else
					message_combatd(HIG "只见$n"HIG"神色一凛，不敢硬接，一个翻身及时的退出战圈，躲开了$N"HIG"凌厉的攻势！\n"NOR,this_object(),who);	
				set_temp("pfm_msg",0);	
			}
			else if( random(2) )
			{
				msg = HIY "\n$N"HIY"收拳发力，招化太祖长拳之秘诀「缓字诀」向$n"HIY"攻去，企图减缓$p的攻势！\n"NOR;
				message_vision(msg,this_object(),who);
				if( random(3) )
				{
					msg = HIB "$n被一阵拳风扫中，身形不由慢了下来。\n" NOR;
					message_combatd(msg,this_object(),who);
					who->start_busy(2+random(2));
				}
				else
				{
					msg = HIG "可是$p连跳了几步，闪开了这阵拳风！\n" NOR;
					message_combatd(msg,this_object(),who);
				}					
			}				
		}
		else if( weapon->query("skill_type")=="axe" )
		{
			add_temp("apply/attack",300);
			COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM,HIC"$N"HIC"突然暴喝一声，将手中巨斧斜向上举起，然后在半空中划出一道圆弧，随即径直斜下斩向$n"HIC"！这一瞬间，$n"HIC"只觉得呼吸都停止了！\n"NOR);
			add_temp("apply/attack",-300);
		}
		else if( weapon->query("skill_type")=="spear" )
		{
	        msg = HIC"\n$N"HIC"将手中$w"HIC"一抖，由下而上翻将上来，一股大力向$n"HIC"狂涌而至，如流沙河水，天幕倒垂！\n"NOR;
    	    d = COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM,msg);
        	if( d>0 )
        		msg = HIC"\n$N"HIC"一招得手，顺势双手交错，$w"HIC"似巨蟒般倒卷而回！\n"NOR;     
        	else	
                msg = HIC"\n$N"HIC"见$n"HIC"闪过次招，双手交错，$w"HIC"似巨蟒般倒卷而回！\n"NOR;
        	COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM,msg);
        	msg = HIC"\n$N"HIC"两枪出完，$w"HIC"并不罢休，$w"HIC"斗出绚丽的枪花直扑$n"HIC"$l！\n"NOR;
        	COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM,msg);
        	if( random(3) )
        	{
				msg = HIC"\n三枪出罢，将个$n"HIC"刺得遍体鳞伤，鲜血直冒！\n"NOR;
                message_combatd(msg,this_object(),who);
                who->receive_damage("kee",300+random(100),this_object(),TYPE_PERFORM);
                COMBAT_D->report_status(who);        		
			}
		}	
		else
		{
			message_vision(HIW"\n半空中忽然打了道利闪，直向$n击去！\n"NOR,this_object(),who);
			if( random(3) )
			{
				SPELL_D->attacking_cast(
					this_object(),
					who,
					90,
					50,
					"kee",
					HIR "狂雷夹带着火光，向$n呼啸不止。\n" NOR,
					HIR "$n被雷火击中，一身焦黑！\n" NOR, 
					HIG "$n的衣服已被燃着，所幸人却无恙。\n" NOR, 
					HIB "$n袍袖一挥，将雷火尽数卷回！\n" NOR, 
					RED "$n被雷火反击，自己烧了个灰眉土脸！\n" NOR
				);
			}
		}
	}
	else
		QUEST_D->randomPfm(this_object());
	call_out("tiaozhan_hit",3+random(3),who);
}