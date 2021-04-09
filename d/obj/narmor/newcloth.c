//无色装备：无附加属性
//金色装备：有1条随机属性
//蓝色装备：有1到4条随机属性
//青色装备：有2条随机属性
//红色装备：有3条随机属性
//紫色装备：有4条随机属性
//固定属性包括 等级要求、装备基本属性			 
#include <ansi.h>
#include <armor.h>
inherit EQUIP;
#include "a_title.h"

mapping a_names1() //男性
{
	return ([
1  :	({"粗布衫",({"cu bu shan","shan","cloth"}),}),
]);
}

mapping a_names2() //女性
{
	return ([
1  :	({"粗布衫",({"cu bu shan","shan","cloth"}),}),
]);
}

mapping a_title(){ return  a_title;}

mapping equip_apply_prop  = ("/cmds/std/look.c")->query_euqip_look1();
mapping equip_apply_prop2 = ("/cmds/std/look.c")->query_euqip_look2();     	

mapping equip_base(object obj)
{
	mapping prop;
	string type;
	if( !obj )
		return 0;
	type = obj->query("armor_type");
	if( !type || !stringp(type) )
		return 0;
	switch(type)
	{
		case TYPE_ARMOR : //物防
			prop = (["combat_def":35]);
			break;
		case TYPE_CLOTH :
		case TYPE_SKIRT : //双防
			prop = ([
				"combat_def":18,
				"spells_def":18,
			]);
			break;
		case TYPE_SURCOAT : //法防
			prop = ([ "spells_def":24,]);
			break;
		case TYPE_HEAD : //双防
			prop = ([
				"combat_def":6,
				"spells_def":6,
			]);
			break;
		case TYPE_SHIELD : //双防、格挡
			prop = ([
				"combat_def":5,
				"spells_def":5,
				"combat_parry" : 2,
			]);
			break;
		case TYPE_BOOTS : //双防、闪避
			prop = ([
				"combat_def":8,
				"spells_def":8,
				"spells_dodge" : 2,
				"combat_dodge" : 2,
			]);
			break;
		case TYPE_WAIST : //气血上限
			prop = ([ "max_kee":50,]);
			break;
		case TYPE_NECK : //命中、闪避
			prop = ([
				"spells_succ":1,
				"combat_succ":1,
				"spells_dodge" : 1,
				"spells_dodge" : 1,
			]);
			break;
		case TYPE_WRISTS : //精神上限
			prop = ([ "max_sen":50,]);
			break;
		case TYPE_FINGER : //双攻
			prop = ([
				"spells_damage":7,
				"combat_damage":7,
			]);
			break;
		case TYPE_HANDS : //格挡
			prop = ([ "combat_parry" : 4,]);
			break;		
		default : return 0;
	}
	return prop;
}

mapping *equip_apply(object obj)
{
	mapping *prop;
	string type;
	if( !obj )
		return 0;
	type = obj->query("armor_type");
	if( !type || !stringp(type) )
		return 0;
	switch(type)
	{
		case TYPE_ARMOR : 
			prop = ({
				([
					"strength" : 1,
					"receive_exercise" : 1,
					"receive_kee" : 1,
				]),
				([
					"combat_def" : 20,
					"receive_curing_kee" : 1,
					"max_kee" : 20,
					"receive_kee" : 1,
				]),	
				([
					"re_combat_damage" : 1,
					"constitution" : 1,
					"max_force" : 10,
					"receive_heal_kee" : 1,
				]),				
			});	
			break;
		case TYPE_CLOTH :
		case TYPE_SKIRT : //双防
			prop = ({
				([
					"spells_def" : 8,
					"combat_def" : 8,
					"intelligence" : 1,
				]),
				([
					"max_kee" : 10,
					"composure" : 1,
					"receive_kee" : 1,
					"fofce_refresh" : 1, 
				]),	
				([
					"max_sen" : 10,
					"receive_sen" : 1,
					"force_recover" : 1,
				]),				
			});
			break;
		case TYPE_SURCOAT : //法防
			prop = ({
				([
					"spells_def" : 3,
					"receive_curing_sen" : 1,
					"spirituality" : 1,
				]),
				([
					"max_mana" : 6,
					"receive_mana" : 1,
					"fofce_refresh" : 1,
					"receive_sen" : 1,
				]),	
				([
					"spells_dodge" : 1,
					"receive_heal_sen" : 1,
					"max_sen" : 6,
				]),				
			});
			break;
		case TYPE_HEAD : //双防
			prop = ({
				([
					"spells_def" : 5,
					"max_kee" : 10,
					"receive_sen" : 1,
				]),
				([
					"combat_def" : 5,
					"spells_damage" : 3,
					"receive_heal_kee" : 1,
					"receive_kee" : 1,
				]),	
				([
					"combat_damage" : 3,
					"constitution" : 1,
					"receive_sen" : 1,
					"receive_heal_sen" : 1,
				]),				
			});
			break;
		case TYPE_SHIELD : //双防、格挡
			prop = ({
				([
					"spells_def" : 3,
					"defense" : 1,
					"force_recover" : 1,
				]),
				([
					"combat_def" : 3,
					"combat_parry" : 1,
					"composure" : 1,
					"fofce_refresh" : 1,
				]),	
				([
					"re_spells_effdamage" : 1,
					"re_combat_effdamage" : 1,
					"re_spells_damage" : 1,
					"receive_sen" : 1,
				]),				
			});
			break;
		case TYPE_BOOTS : //双防、闪避
			prop = ({
				([
					"spells_def" : 5,
					"combat_dodge" : 1,
					"receive_exercise" : 1,
				]),
				([
					"combat_def" : 5,
					"defense" : 1,
					"max_kee" : 10,
					"max_sen" : 10,
				]),	
				([
					"spells_dodge" : 1,
					"receive_meditate" : 1,
					"composure" : 1,
					"max_force" : 5,
				]),				
			});
			break;
		case TYPE_WAIST : //气血上限
			prop = ({
				([
					"spells_def" : 3,
					"max_sen" : 15,
					"composure" : 1,
				]),
				([
					"combat_def" : 3,
					"max_kee" : 15,
					"constitution" : 1,
					"spells_succ" : 1,
				]),	
				([
					"max_mana" : 10,
					"combat_succ" : 1,
					"max_force" : 10,
				]),				
			});
			break;
		case TYPE_NECK : //命中、闪避
			prop = ({
				([
					"attack" : 1,
					"spells_dodge" : 1,
					"spirituality" : 1,
				]),
				([
					"spells_succ" : 1,
					"combat_succ" : 1,
					"combat_dodge" : 1,
					"constitution" : 1,
				]),	
				([
					"defense" : 1,
					"karma" : 1,
					"personality" : 1,
					"composure" : 1,
				]),				
			});
			break;
		case TYPE_WRISTS : //精神上限
			prop = ({
				([
					"combat_damage" : 2,
					"spells_damage" : 2,
					"max_sen" : 20,		

				]),
				([
					"strength" : 1,
					"personality" : 1,
					"spirituality" : 1,
					"intelligence" : 1,
				]),	
				([
					"max_kee" : 20,
					"receive_meditate" : 1,
					"max_mana" : 20,
					"receive_exercise" : 1,	
				]),				
			});
			break;
		case TYPE_FINGER : //双攻
			prop = ({
				([
					"combat_parry" : 1,
					"karma" : 1,
					"attack" : 1,
				]),
				([
					"parry" : 1,
					"personality" : 1,
					"spells_def" : 2,
					"combat_def" : 2,
				]),	
				([
					"max_kee" : 20,
					"max_sen" : 20,
					"max_mana" : 20,
					"max_force" : 20,
				]),				
			});
			break;
		case TYPE_HANDS : //格挡
			prop = ({
				([
					"combat_damage" : 2,
					"strength" : 1,
					"constitution" : 1,
				]),
				([
					"spells_damage" : 2,
					"personality" : 1,
					"max_kee" : 15,
					"max_sen" : 15,
				]),	
				([
					"max_force" : 10,
					"max_mana" : 10,
					"spells_def" : 5,
					"combat_def" : 5,
				]),				
			});
			break;		
		default : return 0;
	}
	return prop;
}

void create()
{
	set_name("防具◆",({"fang ju"}));
}

string init_color(object who)
{
	string wx1,wx2;
	int i;
	if( !who )
		return "";
	if( (wizardp(who)||!userp(who)) 
	 && who->query("env/test") )
	{
		if( !stringp(who->query("env/test")) )
			return "HIY";
		else	return who->query("env/test");	
	}
	i = random(who->query_kar());
	i = i/2+random(i);
	i+= who->query_level()/2;
	i+= QUEST_D->query_item_gitf();
	wx1 = SPELL_D->player_query_wuxing(who);
	wx2 = SPELL_D->query_time_wuxing();
	switch(SPELL_D->wuxing_xs(wx1,wx2))
	{
		case 1 : i+= 2;break;
		case -1: i-= 2;break;		
		default: i+= 1;break;
	}
	if( random(55)>50000/(i+500) ) //50-100
		return "HIM";
	else if( random(65)>50000/(i+500) ) 
		return "HIR";
	if( random(75)>50000/(i+500) ) 
		return "HIC";
	if( random(85)>50000/(i+500) ) 
		return "HIB";
	if( random(95)>50000/(i+500) ) 
		return "HIY";
	else	return "";	
}

void init_class(object who)
{
	string cls;
	if( !query("armor_color") 
	 || !who )
		return;
	if( query("armor_color")!="HIM" )
		return;
	if( random(10)>1 )
		return;
	if( !stringp(cls=who->query("class")) )
		cls = ({
			"dragon","fighter","xian","ghost","bonze",
			"taoist","scholar","dancer","yaomo"
		})[random(9)];
	if( random(5)==0 )
		cls = ({
			"dragon","fighter","xian","ghost","bonze",
			"taoist","scholar","dancer","yaomo"
		})[random(9)];
	set("class",cls);
}				

void init_title()
{
	string clr,title,*ts,*da;
	int i,lv,dd;
	if( query("armor_title") )
		return;
	if( !lv=query("level") )
		return;	
	if( !stringp(clr=query("armor_color")) 
	  || (clr!="HIM" && clr!="HIR") )
		return;
	if( random(10)<3 )
		return;	
	ts = keys(a_title());
	if( !ts || !arrayp(ts) )
		return;
	title = ts[random(sizeof(ts))];
	da = a_title()[title];
	if( !da || !arrayp(da) )
		return;
	set("armor_title",title);
	for(i=0;i<sizeof(da);i++)
	{
		dd = lv;
		dd = random(dd/20)+1+random(5);
		add("armor_prop/"+da[i],dd);
	}
}			

varargs int name_2_level(string name,int gender)
{
	string *names;
	int i;
	if( gender==1 )
		names = keys(a_names1());
	else	names = keys(a_names2());	
	if( !names || !arrayp(names) || sizeof(names)<1 )
		return 0;
	for(i=0;i<sizeof(names);i++)
	{
		if( gender==1 && a_names1()[i][0]==name )
			return i;
		else if( a_names2()[i][0]==name )
			return i;	
	}
	return 0;		 	
}

varargs int level_2_level(object obj,int level,int gender)
{
		int i,*k;
		if( !obj )
			return 0;
		if( gender==1 )	
			k = keys(obj->a_names1());
		else	k = keys(obj->a_names2());	
		if( !k || !arrayp(k) || sizeof(k)<1 )
			return 0;
		k = sort_array(k,-1);
		if( level>k[0] )
			return k[0];
		reset_eval_cost();	
		for(i=0;i<sizeof(k)-1;i++)
		{
			if( level<k[i] )
			{
				if( level>k[i+1] )	
					return k[i+1];
			}		
		}	
		return 0;
}

int init_armor(mixed get)
{
	mixed prop;
	mapping temp;
	string name,clr,*ids,*tmp,data;
	int gender,level,i,*k,p,pp,num,a_lvl,m,sheng,qian;
	if( !get )
		return 0;
	if( query("default_set") )
		return 0;	
	if( intp(get) )
	{
		level = get;
		clr = "";
		name = 0;
		gender = random(2)+1; //1男 2女
	}
	else if( objectp(get) )
	{
		level = get->query_level();
		if( get->query_temp("armor_level")>0 
		 && get->query_temp("armor_level")<=level )
		 	level = get->query_temp("armor_level");
		else	level = level*9/10+random(level/10);
		clr = init_color(get);
		if( !intp(gender=get->query_temp("equip_gender"))
		  || gender<1 || gender>2 )
			gender = random(2)+1;		  
		name = 0;
	}
	else if( arrayp(get) ) //({5,HIY,"布衣"});
	{
		if( sizeof(get)<3 )
		{
			level = 1;
			clr = "";
			name = 0;
			gender = random(2)+1;
		}
		else
		{
			level = get[0];
			clr = get[1];
			name = get[2];
			gender = random(2)+1;
		}
	}
	else if( stringp(get) )
	{
		level = 0;
		clr = "";
		name = get;
		gender = random(2)+1;
	}
	else	return 0;
	if( name && stringp(name) && strlen(name)>2 )
		level = name_2_level(name,gender);
	if( level<1 )
		return 0;
	if( gender==1 && undefinedp(a_names1()[level]) )
		level = level_2_level(this_object(),level,gender);
	else if( undefinedp(a_names2()[level]) )
		level = level_2_level(this_object(),level,gender);
	if( level<1 )
		return 0;
//基本属性
	prop = equip_base(this_object());
	if( !prop || !mapp(prop) )
		return 0;
	if( level<10 )
	{
		if( clr=="HIC" || clr=="HIR" || clr=="HIM" || clr=="HIB" )
			clr = "HIY";
	}		
	else if( level<25 )
	{
		if( clr=="HIC" || clr=="HIR" || clr=="HIM" )
			clr = "HIB";
	}
	if( clr && stringp(clr) && clr!="" )
	{
		set("armor_color",clr);
		switch(clr)
		{	//num:基数 pp:条数 sheng:升级基数 qian:镶嵌基数
			case "HIY" : num = 1;pp = 1;sheng=1;qian=1;break;
			case "HIB" : num = 1;pp = 1+random(5);sheng=1;qian=2;break;
			case "HIC" : num = 2;pp = 2;sheng=2;qian=3;break;
			case "HIR" : num = 3;pp = 3;sheng=3;qian=4;break;
			case "HIM" : num = 5;pp = 4;sheng=4;qian=5;break;
		}
	}
	if( gender==2 )
		set("female_only",1);
	if( get && objectp(get) )
		init_class(get);
	if( query("female_only")>0 )
	{	
		name = a_names2()[level][0];
		ids = a_names2()[level][1];
	}
	else	
	{
		name = a_names1()[level][0];
		ids = a_names1()[level][1];	
	}	
	set_name(name,ids);
	set_weight(10*level);
        if( clonep() )
                set_default_object(__FILE__);
	set("material", "cloth");
        set("unit", "件");
        set("value", 0);
        set("level",level);
	if( clr=="HIM" || clr=="HIR" )
		init_title();        
        set("default_set",1);
        set("changed",1);
	sheng = random(sheng);
        if( sheng>0 )
        {
        	set("base_level",level);
        	set("max_level",sheng);
        }
	qian = random(qian);
	if( qian>0 )
		set("max_enchase",qian);        
	tmp = keys(prop);
	for(i=0;i<sizeof(tmp);i++)
	{
		p = prop[tmp[i]];
		if( p<5 )
		{
			p+= level/3+random(num+1);
		}
		else
		{
			p+= level*(p/5+1)+num*2;
			p = p*4/5+random(p/5);
		}
		if( !undefinedp(equip_apply_prop2[tmp[i]]) )
		{
			p = p/2+(random(p)+random(num)+random(level/5))/2;
			if( p>30 ) p = 30;
			if( p<1 ) p = 1;
		}
		if( query("class") )
		{
			if( p>100 )
				p+= 10+random(20);
			else 	p+= random(5);	
		}		
		add("armor_prop/"+tmp[i],p);	
	}
//基本属性结束
	if( !clr || !stringp(clr) || clr=="" )
		return 1;
	
	prop = equip_apply(this_object());
	if( !prop || !arrayp(prop) || sizeof(prop)<3 )
		return 3;
	m = pp;
	if( m>sizeof(prop) )
		m = sizeof(prop);
	for(i=0;i<m;i++)
	{
		temp = prop[i];
		if( !temp || !mapp(temp) ) continue;
		tmp = keys(temp);
		if( !tmp || !arrayp(tmp) ) continue;
		data = tmp[random(sizeof(tmp))];
		if( !data || !stringp(data) ) continue;
		a_lvl = temp[data];
		if( a_lvl==1 )
			a_lvl+= random(num*5)+level/5+random(level/5);
		else
		{
			a_lvl+= level*(a_lvl/6+1)+num*5;
			a_lvl = a_lvl*3/5+random(a_lvl*2/5);
		}
		if( !undefinedp(equip_apply_prop2[data]) )
		{
			a_lvl = a_lvl/4+random(a_lvl/2);
			if( a_lvl>25 ) a_lvl = 25;
		}
		add("armor_prop/"+data,a_lvl);
	}
	if( pp>sizeof(prop) )
	{
		tmp = ({
			"force","spells","dodge","axe","blade",
			"fork","hammer","literate","mace","parry",
			"spear","staff","stick","sword","throwing",
			"unarmed","whip",
			"ad_force","ad_spells","ad_dodge","ad_axe","ad_blade",
			"ad_fork","ad_hammer","ad_literate","ad_mace","ad_parry",
			"ad_spear","ad_staff","ad_stick","ad_sword","ad_throwing",
			"ad_unarmed","ad_whip",
		});
		pp = pp-sizeof(prop);
		while(pp--)
		{
			data = tmp[random(sizeof(tmp))];
			tmp-= ({data});
			a_lvl = level/2+num*2;
			a_lvl = level/4+random(level/5);
			add("armor_prop/"+data,a_lvl);
		}				
	}
	return 4;
}		

string name()
{
	string cls,name = ::name();
	if( query("armor_title") )
		name = query("armor_title")+"之"+name;
	if( query("armor_color") )
	{
		name = query("armor_color")+name;	
		name = COLOR_D->replace_color(name,1);
		if( query("armor_color")=="HIM" )
		{
			if( !stringp(cls=query("class")) )
				name = HIM"(灵)"+name;
			else
			{
				switch(cls)
				{
					case "shen" : 
					case "dragon" :
					case "fighter" :
					case "xian" : name = HIM"(仙)"+name;break;
					case "youling" :
					case "ghost" : name = HIM"(鬼)"+name;break;
					case "seng"  :
					case "bonze" : name = HIM"(佛)"+name;break;
					case "taoist": name = HIM"(道)"+name;break;
					case "scholar" : name = HIM"(儒)"+name;break;
					case "dancer" : name = HIM"(魅)"+name;break;
					case "yaomo" : name = HIM"(妖)"+name;break;
					case "tianmo" : name = HIM"(魔)"+name;break;
					default : name = HIM"(灵)"+name;break;
				}
			}	
		}
	}
	return name;
}

int is_armor(){ return 1;}