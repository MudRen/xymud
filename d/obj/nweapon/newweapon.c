//新版装备，下线不掉，死亡会没
//金色装备：有1条随机属性的装备
//蓝色装备：有3到10条随机属性的装备，属性越多，出现的概率越低		
//橙色装备：有2条随机属性的装备
//红色装备：有3条固定属性的装备，第四条属性随机，并有可能额外出现1到3条随机属性
//紫色装备：有4条固定属性的装备，第五条属性随机，并有可能额外出现1到3条随机属性				 
#include <ansi.h>
#include <weapon.h>
inherit EQUIP;
#include "w_title.h"

mapping w_names()
{
	return ([
1  :	({"粗布衫",({"cu bu shan","shan","cloth"}),}),
]);
}

mapping w_title(){ return  w_title;}

mapping equip_apply_prop  = ("/cmds/std/look.c")->query_euqip_look1();
mapping equip_apply_prop2 = ("/cmds/std/look.c")->query_euqip_look2();     

mapping equip_base(object obj)
{
	mapping prop;
	string type;
	if( !obj )
		return 0;
	type = obj->query("skill_type");
	if( !type || !stringp(type) )
		return 0;
	switch(type)
	{
		case "axe" :
			prop = ([
				"combat_damage":35,
				"spells_damage":15,
			]);
			break;
		case "blade" :
			prop = ([
				"combat_damage":30,
				"spells_damage":25,
			]);
			break;
		case "fork" : 
			prop = ([
				"combat_damage":25,
				"spells_damage":20,
			]);
			break;
		case "hammer"  :
			prop = ([
				"combat_damage":40,
				"spells_damage":10,
			]);
			break;
		case "mace" : 
			prop = ([
				"combat_damage":35,
				"spells_damage":20,
			]);
			break;
		case "sword" : 
			prop = ([
				"combat_damage":30,
				"spells_damage":30,
			]);
			break;
		case "staff" : 
			prop = ([
				"combat_damage":30,
				"spells_damage":40,
			]);
			break;
		case "stick" : 
			prop = ([
				"combat_damage":35,
				"spells_damage":25,
			]);
			break;
		case "whip" : 
			prop = ([
				"combat_damage":15,
				"spells_damage":25,
			]);

			break;
		case "spear" : 
			prop = ([
				"spells_damage":15,
				"combat_damage":30,
			]);
			break;
		case "unarmed" : 
			prop = ([
				"spells_damage":15,
				"combat_damage":15,
			]);
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
	type = obj->query("skill_type");
	if( !type || !stringp(type) )
		return 0;
	switch(type)
	{
		case "axe" :
			prop = ({
				([
					"axe" : 1,
					"sanban-axe" : 1,
					"karma" : 1,
				]),
				([
					"ad_sanban-axe" : 1,
					"ad_axe" : 1,
					"max_force" : 30,
					"max_kee" : 50,
				]),
				([
					"strength" : 1,
					"courage" : 1,
					"constitution" : 1,
					"receive_force" : 5,
				]),								
			});
			break;
		case "blade" :
			prop = ({
				([
					"blade" : 1,
					"bingpo-blade" : 1,
					"cibeidao" : 1,
				]),
				([
					"ad_blade" : 1,
					"ad_bingpo-blade" : 1,
					"ad_cibeidao" : 1,
					"ad_kugu-blade" : 1,
				]),
				([
					"kugu-blade" : 1,
					"yange-blade" : 1,
					"ad_yange-blade" : 1,
					"strength" : 1,
				]),								
			});
			break;
		case "fork" : 
			prop = ({
				([
					"fork" : 1,
					"ad_fork" : 1,
					"max_kee" : 50,
				]),
				([
					"fengbo-cha" : 1,
					"courage" : 1,
					"max_force" : 30,
					"max_kee" : 50,
				]),
				([
					"ad_fengbo-cha" : 1,
					"constitution" : 1,
					"receive_force" : 5,
					"strength" : 1,
				]),								
			});
			break;
		case "hammer"  :
			prop = ({
				([
					"hammer" : 1,
					"huntian-hammer" : 1,
					"kaishan-chui" : 1,
				]),
				([
					"ad_hammer" : 1,
					"ad_huntian-hammer" : 1,
					"ad_kaishan-chui" : 1,
					"max_kee" : 50,
				]),
				([
					"strength" : 1,
					"constitution" : 1,
					"courage" : 1,
				]),								
			});
			break;
		case "mace" : 
			prop = ({
				([
					"mace" : 1,
					"wusi-mace" : 1,
					"jinglei-mace" : 1,
				]),
				([
					"ad_mace" : 1,
					"ad_wusi-mace" : 1,
					"ad_jinglei-mace" : 1,
					"max_kee" : 50,
				]),
				([
					"strength" : 1,
					"constitution" : 1,
					"courage" : 1,
				]),								
			});
			break;
		case "sword" : 
			prop = ({
				([
					"ad_sword" : 1,
					"max_kee" : 50,
					"max_force" : 30,
				]),
				([
					"strength" : 1,
					"constitution" : 1,
					"courage" : 1,
				]),
				([
					"ad_bainiao-jian" : 1,
					"ad_liangyi-sword" : 1,
					"ad_xiaofeng-sword" : 1,
					"ad_qixiu-jian" : 1,
					"ad_mindsword" : 1,
					"ad_canxin-jian" : 1,
					"ad_chixin-jian" : 1,
					"ad_qingxia-jian" : 1,
					"ad_zongheng-sword" : 1,
					"ad_yujianshu" : 1,
				]),								
			});
			break;
		case "staff" : 
			prop = ({
				([
					"staff" : 1,
					"lunhui-zhang" : 1,
					"fumo-zhang" : 1,
				]),
				([
					"ad_staff" : 1,
					"ad_lunhui-zhang" : 1,
					"ad_fumo-zhang" : 1,
					"max_kee" : 50,
				]),
				([
					"strength" : 1,
					"constitution" : 1,
					"courage" : 1,
				]),								
			});
			break;
		case "stick" : 
			prop = ({
				([
					"stick" : 1,
					"kusang-bang" : 1,
					"qianjun-bang" : 1,
				]),
				([
					"dali-bang" : 1,
					"ad_kusang-bang" : 1,
					"ad_qianjun-bang" : 1,
					"ad_dali-bang" : 1,
				]),
				([
					"strength" : 1,
					"constitution" : 1,
					"courage" : 1,
				]),								
			});
			break;
		case "whip" : 
			prop = ({
				([
					"whip" : 1,
					"jueqingbian" : 1,
					"hellfire-whip" : 1,
				]),
				([
					"yinsuo-jinling" : 1,
					"ad_jueqingbian" : 1,
					"ad_yinsuo-jinling" : 1,
					"ad_hellfire-whip" : 1,
				]),
				([
					"strength" : 1,
					"constitution" : 1,
					"courage" : 1,
				]),								
			});
			break;
		case "spear" : 
			prop = ({
				([
					"spear" : 1,
					"wuyue-spear" : 1,
					"bawang-qiang" : 1,
				]),
				([
					"ad_huoyun-qiang" : 1,
					"ad_bawang-qiang" : 1,
					"ad_wuyue-spear" : 1,
					"huoyun-qiang" : 1,
				]),
				([
					"strength" : 1,
					"constitution" : 1,
					"courage" : 1,
				]),								
			});
			break;
		case "unarmed" : 
			prop = ({
				([
					"ad_unarmed" : 1,
					"max_kee" : 50,
					"max_force" : 30,
				]),
				([
					"strength" : 1,
					"constitution" : 1,
					"courage" : 1,
				]),
				([
					"ad_baihua-zhang" : 1,
					"ad_jienan-zhi" : 1,
					"ad_jinghun-zhang" : 1,
					"ad_puti-zhi" : 1,
					"ad_cuixin-zhang" : 1,
					"ad_wuxing-quan" : 1,
					"ad_dragonfight" : 1,
					"ad_changquan" : 1,
					"ad_moyun-shou" : 1,
					"ad_hunyuan-zhang" : 1,
					"ad_yinfeng-zhua" : 1,
					"ad_lanhua-shou" : 1,
					"ad_rainbow-zhi" : 1,
				]),								
			});
			break;		
		default : return 0;
	}
	return prop;
}

void create()
{
	set_name("武器◆",({"wu qi"}));
	setup();
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
	if( !query("weapon_color") 
	 || !who )
		return;
	if( query("weapon_color")!="HIM" )
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

int name_2_level(string name)
{
	string *names;
	int i;
	names = keys(w_names());
	if( !names || !arrayp(names) || sizeof(names)<1 )
		return 0;
	for(i=0;i<sizeof(names);i++)
	{
		if( w_names()[i][0]==name )
			return i;
	}
	return 0;		 	
}

int level_2_level(object obj,int level)
{
		int i,*k;
		if( !obj )
			return 0;
		k = keys(obj->w_names());
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

void init_title()
{
	string clr,title,*ts,*da;
	int i,lv,dd;
	if( query("weapon_title") )
		return;
	if( !lv=query("level") )
		return;	
	if( !stringp(clr=query("weapon_color")) 
	  || (clr!="HIM" && clr!="HIR") )
		return;
	if( random(10)<3 )
		return;	
	ts = keys(w_title());
	if( !ts || !arrayp(ts) )
		return;
	title = ts[random(sizeof(ts))];
	da = w_title()[title];
	if( !da || !arrayp(da) )
		return;
	set("weapon_title",title);
	for(i=0;i<sizeof(da);i++)
	{
		dd = lv;
		dd = random(dd/20)+1+random(5);
		add("weapon_prop/"+da[i],dd);
	}
}

int init_weapon(mixed get)
{
	mixed prop;
	mapping temp;
	string name,clr,*ids,*tmp,data;
	int level,i,*k,p,pp,num,a_lvl,m,sheng,qian;
	if( !get )
		return 0;
	if( query("default_set") )
		return 0;	
	if( intp(get) )
	{
		level = get;
		clr = "";
		name = 0;
	}
	else if( objectp(get) )
	{
		level = get->query_level();
		if( get->query_temp("weapon_level")>0 
		 && get->query_temp("weapon_level")<=level )
		 	level = get->query_temp("weapon_level");
		else	level = level*9/10+random(level/10);
		clr = init_color(get);
		name = 0;
	}
	else if( arrayp(get) ) //({5,HIY,"布衣"});
	{
		if( sizeof(get)<3 )
		{
			level = 1;
			clr = "";
			name = 0;
		}
		else
		{
			level = get[0];
			clr = get[1];
			name = get[2];
		}
	}
	else if( stringp(get) )
	{
		level = 0;
		clr = "";
		name = get;
	}
	else	return 0;
	if( name && stringp(name) && strlen(name)>2 )
		level = name_2_level(name);
	if( level<1 )
		return 0;
	if( undefinedp(w_names()[level]) )
		level = level_2_level(this_object(),level);
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
		set("weapon_color",clr);
		switch(clr)
		{	//num:基数 pp:条数 sheng:升级基数 qian:镶嵌基数
			case "HIY" : num = 1;pp = 1;sheng=1;qian=1;break;
			case "HIB" : num = 2;pp = 1+random(5);sheng=1;qian=2;break;
			case "HIC" : num = 3;pp = 2;sheng=2;qian=3;break;
			case "HIR" : num = 4;pp = 3;sheng=3;qian=4;break;
			case "HIM" : num = 6;pp = 4;sheng=4;qian=5;break;
			default :  num = 0;pp=0;sheng=random(2);qian=0;break; 
		}
	}
	if( get && objectp(get) )
		init_class(get);			
	name = w_names()[level][0];
	ids = w_names()[level][1];
	set_name(name,ids);
	set_weight(15*level);
        if( clonep() )
                set_default_object(__FILE__);
	set("material", "iron");
        set("value", 0);
        set("level",level);
        if( !query("actions") )
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
        sheng = random(sheng);
        if( sheng>0 )
        {
        	set("base_level",level);
        	set("max_level",sheng);
        }
	qian = random(qian);
	if( qian>0 )
		set("max_enchase",qian);
	if( clr=="HIM" || clr=="HIR" )
		init_title(); 		
        set("default_set",1);
        set("changed",1);
	tmp = keys(prop);
	for(i=0;i<sizeof(tmp);i++)
	{
		p = prop[tmp[i]];
		if( tmp[i]=="combat_damage"
		 || tmp[i]=="spells_damage" )
			p = 45+p+(level+random(num))*10;
		else if( p<5 )
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
		add("weapon_prop/"+tmp[i],p);	
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
			if( a_lvl>30 ) a_lvl = 30;
		}
		add("weapon_prop/"+data,a_lvl);
	}
	if( pp>sizeof(prop) )
	{
		tmp = ({
       	"receive_force","receive_mana","receive_kee","receive_meditate",
       	"receive_sen","receive_heal_kee","receive_heal_sen",
	"receive_curing_kee","receive_curing_sen","receive_exercise",
	"intelligence","spirituality","composure","personality",			
		});
		pp = pp-sizeof(prop);
		while(pp--)
		{
			data = tmp[random(sizeof(tmp))];
			tmp-= ({data});
			a_lvl = a_lvl/5+random(a_lvl/3);
			if( !undefinedp(equip_apply_prop2[data]) )
			{
				if( a_lvl>25 ) a_lvl = 25;
			}			
			add("weapon_prop/"+data,a_lvl);
		}				
	}
	return 4;
}

string name()
{
	string cls,name = ::name();
	if( query("weapon_title") )
		name = query("weapon_title")+"之"+name;
	if( query("weapon_color") )
	{
		name = query("weapon_color")+name;	
		name = COLOR_D->replace_color(name,1);
		if( query("weapon_color")=="HIM" )
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

int is_weapon(){ return 1;}