//equip.c
#include <ansi.h>
#include <dbase.h>
#include <weapon.h>

int is_equip() {return 1;}

int valid_level(object who)
{
	int lvl = this_object()->query("level");
	if( !lvl )
		lvl = 0;
	if( !userp(who) )
		return 1;	
	if( lvl<=who->query_level() )
		return 1;
	return 0;
}		

mixed query_class()
{
	string cls = query("class");
	if( !cls || !stringp(cls) )
		return 1;
	switch(cls)
	{
		case "shen"   : 
		case "dragon" :
		case "fighter":
		case "xian"   : return 1;
		case "youling":
		case "ghost"  : return "阎罗地府";
		case "seng"   :
		case "bonze"  : return "南海普陀山";
		case "taoist" : return ({"蜀山派","方寸山三星洞","五庄观"});
		case "yaomo"  : return ({"火云洞","无底洞","大雪山","盘丝洞",});
		default       : return 1;
	}					
}

int wear()
{
	mixed foo;
	object owner;
	mapping armor_prop, applied_prop;
	string *apply, type;

	if( !(owner = environment())
	 || !owner->is_character() ) 
	 	return 0;
	if( query("equipped") ) 
		return 1;
	if( query("breaked") )
		return notify_fail("此防具已被破坏，需要修复。\n");
	if( !mapp(armor_prop = query("armor_prop")) 
	 || query("weapon_prop/damage")>0 )
		return notify_fail("你只能穿戴可当作护具的东西。\n");

	type = query("armor_type");
	if( owner->query_temp("armor/" + type) )
		return notify_fail("你已经穿戴了同类型的护具了。\n");

	if( userp(owner) && query("only_npc") )
		return notify_fail("玩家不能装备此防具。\n");

	if( !valid_level(owner) )
		return notify_fail("你的等级不足"+this_object()->query("level")+"。\n");

	if( query("family_name")
	 && (string)owner->query("family/family_name") != query("family_name") )
	 	return notify_fail("这只有「"HIC+query("family_name")+"弟子"NOR"」才能装备。\n");

	foo = query_class();
	if( stringp(foo) 
	 && owner->query("family/family_name")!=foo )
		return notify_fail("这只有「"HIC+foo+"弟子"NOR"」才能装备。\n");
	else if( arrayp(foo) && sizeof(foo)>0 
	      && member_array(owner->query("family/family_name"),foo)==-1 )
		return notify_fail("因为门派限制，你不能装备。\n");
		
	if( query("female_only")
	 && (string)owner->query("gender") != "女性" )
		return notify_fail("这是女人的衣衫，你一个大男人也想穿，羞也不羞？\n");
		
	owner->set_temp("armor/" + type, this_object());
	apply = keys(armor_prop);
	applied_prop = owner->query_temp("apply");
	if( !mapp(applied_prop) ) applied_prop = ([]);
	for(int i = 0; i<sizeof(apply); i++)
		if( undefinedp(applied_prop[apply[i]]) )
			applied_prop[apply[i]] = armor_prop[apply[i]];
		else
			applied_prop[apply[i]] += armor_prop[apply[i]];
	owner->set_temp("apply", applied_prop);
	set("equipped", "worn");
	MOD_D->equip_mod(owner,this_object());		
	return 1;
}

int wield()
{
	object owner, old_weapon;
	mapping weapon_prop;
	string *apply, type;
	int flag;

	if( !(owner = environment()) || !owner->is_character() ) return 0;
	if( query("equipped") ) return 1;
	if( !mapp(weapon_prop = query("weapon_prop")) )
		return notify_fail("你只能装备可当作武器的东西。\n");
	if( userp(owner) && query("only_npc") )
		return notify_fail("玩家不能装备此武器。\n");
	if( query("breaked") )
		return notify_fail("此武器已被破坏，需要修复。\n");
	if( !valid_level(owner) )
		return notify_fail("你的等级不足"+this_object()->query("level")+"。\n");

	flag = query("flag");

	if( owner->query_temp("secondary_weapon")
   	 && owner->query_temp("secondary_weapon")->query("skill_type")=="unarmed" )
		return notify_fail("你必须空出双手才能装备双手武器。\n");
	if( owner->query_temp("weapon")
   	 && owner->query_temp("weapon")->query("skill_type")=="unarmed" )
       		return notify_fail("你装备了拳套，不能再装备武器。\n");
	if( flag & TWO_HANDED ) 
	{
		if( owner->query_temp("weapon")
		 || owner->query_temp("secondary_weapon")
		 || owner->query_temp("armor/shield") )
			return notify_fail("你必须空出双手才能装备双手武器。\n");
		owner->set_temp("weapon", this_object());
	} 
	else 
	{
		if( !(old_weapon = owner->query_temp("weapon")) )
			owner->set_temp("weapon", this_object());
		else if( !owner->query_temp("secondary_weapon")
		      && !owner->query_temp("armor/shield") ) 
			{
				if(flag & SECONDARY) 
				{
					owner->set_temp("secondary_weapon", this_object());
					if( old_weapon->query("apply/skill_type") 
					 && old_weapon->query("apply/skill_type") == this_object()->query("apply/skill_type") 
					 && old_weapon->query("skill_type") != this_object()->query("skill_type") )  
					{
						owner->set_temp("use_apply_action", 1);
					   	old_weapon->set_temp("use_apply_skill", 1);
                			}
				} 
				else if( (int)old_weapon->query("flag") & SECONDARY ) 
				{
					old_weapon->unequip();
					owner->set_temp("weapon", this_object());
					old_weapon->wield();
				} 
				else	return notify_fail("你必须先放下你目前装备的武器。\n");
			} 
		else	return notify_fail("你必须空出一只手来使用武器。\n");
	}

	apply = keys(weapon_prop);
	for(int i = 0; i<sizeof(apply); i++)
		owner->add_temp("apply/" + apply[i], weapon_prop[apply[i]]);

	if(owner->query_temp("use_apply_action") == 1) 
		owner->reset_apply_action();
    	else	owner->reset_action();
	set("equipped", "wielded");
	//MOD_D->check_mod(owner,this_object());
	return 1;
}

int unequip()
{
	object owner, weapon;
	mapping prop, applied_prop;
	string *apply, equipped;

	if( !(owner = environment())->is_character() ) 
		return 0;

	if( !stringp(equipped = query("equipped")) )
		return notify_fail("你目前并没有装备这样东西。\n");

	if( equipped=="wielded" ) 
	{
		if( (weapon=(object)owner->query_temp("weapon")) == this_object() )
			owner->delete_temp("weapon");
		else if( (object)owner->query_temp("secondary_weapon") == this_object() )
			owner->delete_temp("secondary_weapon");
		owner->delete_temp("use_apply_action");
		if(weapon)
			weapon->delete_temp("use_apply_skill");
		prop = query("weapon_prop");
		owner->delete_temp("perf_quick");
		owner->reset_action();
	} 
	else if( equipped=="worn" ) 
	{
		owner->delete_temp("armor/" + query("armor_type") );
		prop = query("armor_prop");
	}

	apply = keys(prop);
	applied_prop = owner->query_temp("apply");
	for(int i = 0; i<sizeof(apply); i++)
		applied_prop[apply[i]] -= prop[apply[i]];

	delete("equipped");
	weapon=(object)owner->query_temp("secondary_weapon");
	// add by bbs, April 28.
	if(weapon) 
	{
		weapon->unequip();
		weapon->wield();
	}
	//套装
	if( equipped=="worn" )
		MOD_D->unequip_mod(owner,this_object());	
	return 1;
}

int query_needP()
{
        int p,lvl = this_object()->query("level");
	if( lvl>=140 )
		return 2000000000;
	p = (lvl*lvl+60)/5*((lvl-1)*2+60)/10*11;
	if( p<10000 )
		p = 10000;
	return p;	
}

int check_level()
{
	int exp = this_object()->query("exp");
	if( exp>=this_object()->query_max_exp() )
	{
		if( this_object()->level_up() )
		{
			this_object()->set("exp",0);
			return 1;
		}
	}
	return 0;
}
