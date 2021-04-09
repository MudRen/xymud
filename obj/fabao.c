// fabao.c
/*
法宝常见形态 
索(whip) 
镜(jing) 
铃(ling) 
伞(san) 
石(stone) 
容器(char) 
扇(shan) 
灯(deng) 
符(fu) 
幡(fan) 
印(yin) 
武器形状(weapon)  比如剑形、杵形
衣(cloth) 
环(huan) 
*/
#include <ansi.h>
#include <armor.h>
#include <combat.h>
inherit EQUIP; 
inherit F_SAVE;

nosave string Err_msg = @FABAO
每件法宝的攻防分别对应对方、对方法宝两个方面。
对敌攻防是战斗中对敌方的伤害以及抵御对方伤害，主要涉及自身安全以及对敌伤害；
对敌法宝攻防则是与敌方的法宝相互争斗时，法宝自身的攻防，主要涉及对对方法宝的压制与收取成功率。
每个攻防属性又分最大属性和当前属性两种。
最大属性是法宝产生时即生成的，可以通过道具来升级，
当前属性则需要使用者用自身的法力温养来提高，当提高到最大属性时即不能再提高了。
法宝温养命令格式：charge <法宝id>'s <属性>
温养属性
	对敌气血伤害	: combat_damage
	对敌精神伤害	: spells_damage
	对敌气血保护	: combat_def
	对敌精神保护	: spells_def
	法宝自身伤害	: self_damage
	法宝自身防御	: self_def
FABAO;

int is_fabao(){return 1;}
int is_armor(){return 1;}
int err_msgs(string arg){write(arg);return 0;}
mapping equip_apply_prop  = ("/cmds/std/look.c")->query_euqip_look1();
mapping equip_apply_prop2 = ("/cmds/std/look.c")->query_euqip_look2();     	

mapping fabao_prop = ([
	"combat_damage" : "对敌气血伤害",
	"spells_damage" : "对敌精神伤害",
	"combat_def"	: "对敌气血保护",
	"spells_def"	: "对敌精神保护",
	"self_damage"	: "法宝自身伤害",
	"self_def"	: "法宝自身防御",
]);
	
mapping a_title()
{
	return ([
	"闻仲"   : ({"mace","ad_mace",}),
	"辛环"   : ({"hammer","ad_hammer",}),
	"邓九公" : ({"blade","ad_blade",}),
	"邓婵玉" : ({"throwing","personality",}),
	"余化"   : ({"spells","ad_spells",}),
	"黄飞虎" : ({"spear","ad_spear","wuyue-spear",}),
	"吕岳"   : ({"spells","ad_spells",}),
	"土行孙" : ({"dodge","ad_dodge",}),
	"姜子牙" : ({"spells_succ","spells_dodge",}),
	"申公豹" : ({"combat_succ","combat_dodge","combat_parry",}),
	"相柳"   : ({"spells_damage","combat_damage",}),
	//
	"甄洛"   : ({"personality","intelligence","spells_succ","spells_dodge",}),
	"妲己"   : ({"personality","intelligence","fofce_refresh","receive_heal_kee",}),
	"湘君"   : ({"personality","intelligence","receive_heal_kee","receive_heal_sen",}),
	"娥皇"   : ({"personality","intelligence","receive_heal_sen","receive_curing_kee",}),
	"女英"   : ({"personality","intelligence","receive_curing_kee","receive_curing_sen",}),
	//
	"敖广"   : ({"unarmed","ad_unarmed","ad_dragonfight"}),
	"玉鼠精" : ({"blade","ad_blade","ad_kugu-blade","ad_yinfeng-zhua","personality",}),
	"张果老" : ({"hammer","ad_hammer","ad_kaishan-chui",}),
	"铁拐李" : ({"staff","ad_staff","ad_fumo-zhang",}),
	"汉钟离" : ({"blade","ad_blade","ad_yange-blade",}),
	"曹国舅" : ({"hammer","ad_hammer","ad_baguazhen",}),
	"韩湘子" : ({"ad_sword","sword","ad_xiaofeng-sword"}),
	"吕洞宾" : ({"ad_sword","ad_sanqing-jian",}),
	"何仙姑" : ({"sword","ad_sanqing-jian","personality"}),
	"蓝采和" : ({"ad_blade","ad_dodge","ad_yange-blade",}),
	"嫦娥"   : ({"personality","ad_moondance","ad_snowsword"}),
	"龟八斗" : ({"ad_hammer","hammer","ad_huntian-hammer",}),
	"凝眸仙子":({"personality","ad_zongheng-sword","ad_siji-zhang"}),
	"孙悟空" : ({"ad_stick","ad_qianjun-bang","re_combat_damage"}),
	"白无常" : ({"stick","ad_kusang-bang","ad_stick",}),
	"黑无常" : ({"whip","ad_hellfire-whip",}),
	"痴梦仙子":({"ad_whip","ad_jueqingbian","personality",}),
	"太清真人":({"ad_yujianshu","ad_tianshi-fufa","ad_sword","re_spells_damage",}),
	"孔雀公主":({"personality","ad_bainiao-jian","ad_bingpo-blade","ad_cuixin-zhang",}),
]);
}

string query_save_file()
{
	string name;
	if( !query("owner_id") || !stringp(query("owner_id")) )
        	return 0;
	if( query("valid_time")<=0 )
		return 0;        	
        name = this_object()->name();
        if( !name || !stringp(name) )
        	return 0;
        name = COLOR_D->clean_color(name);	
	return sprintf("/data/equip/%c/%s/fabao_%d_%s", query("owner_id")[0],query("owner_id"),query("valid_time"),name);
}

//法宝本身的攻击防御，针对于法宝之间的相互争斗
int self_damage()
{
	int lvl = query("level");
	if( query("no_fabao/self_damage") )
		return 0;
	lvl = (lvl+1)*4;
	lvl+= query("fabao/self_damage");
	return lvl;
}
int self_def()
{
	int lvl = query("level");
	if( query("no_fabao/self_def") )
		return 0;
	lvl = (lvl+1)*3;
	lvl+= query("fabao/self_def");
	return lvl;
}
//法宝的攻击防御，针对于对攻击对象
int query_combat_damage()
{
	int lvl = query("level");
	if( query("no_fabao/combat_damage") )
		return 0;
	lvl = (lvl+1)*4;
	lvl+= query("armor_prop/combat_damage");
	return lvl;
}
int query_spells_damage()
{
	int lvl = query("level");
	if( query("no_fabao/spells_damage") )
		return 0;
	lvl = (lvl+1)*5;
	lvl+= query("armor_prop/combat_damage");
	return lvl;
}
int query_combat_def()
{
	int lvl = query("level");
	if( query("no_fabao/combat_def") )
		return 0;
	lvl = (lvl+1)*3;
	lvl+= query("armor_prop/combat_def");
	return lvl;
}
int query_spells_def()
{
	int lvl = query("level");
	if( query("no_fabao/spells_def") )
		return 0;
	lvl = (lvl+1)*4;
	lvl+= query("armor_prop/spells_def");
	return lvl;
}

//生成基本属性，根据法宝形态生成
mapping equip_base()
{
	object obj = this_object();
	mapping prop;
	string type;
	type = obj->query("my_type");
	if( !type || !stringp(type) )
		return 0;
	switch(type)
	{
		case "jing" : //镜类 攻击/防御
			prop = ([
				"combat_def": 5,
				"spells_def": 8,
				"combat_damage": 2,
				"spells_damage": 5,
			]);
			break;
		case "san" : //伞类 攻击/防御
			prop = ([
				"combat_def": 8,
				"spells_def": 8,
				"combat_damage": 4,
				"spells_damage": 5,
			]);
			break;
		case "whip" : //索类 攻击
			prop = ([
				"combat_damage": 5,
				"spells_damage": 8,
			]);
			break;
		case "ling" : //铃类 攻击
			prop = ([
				"combat_damage": 1,
				"spells_damage": 6,
			]);
			break;
		case "stone" : //灵石类 攻击
			prop = ([
				"combat_damage": 5,
				"spells_damage": 4,
			]);
			break;
		case "shan" :  //扇类 攻击
			prop = ([
				"combat_damage": 1,
				"spells_damage": 7,
			]);
			break;
		case "fu" :  //符类 攻击
			prop = ([
				"combat_damage": 1,
				"spells_damage": 9,
			]);
			break;
		case "yin" :  //印类 攻击
			prop = ([
				"combat_damage": 9,
				"spells_damage": 6,
			]);
			break;
		case "weapon" :  //武器类 攻击
			prop = ([
				"combat_damage": 8,
				"spells_damage": 8,
			]);
			break;			
		case "char" : //容器类 内法
			prop = ([
				"max_mana": 30,
				"max_force":20,
			]);
			break;
		case "huan" : //环类 气血上限
			prop = ([ "max_kee":50,]);
			break;
		case "deng" : // 灯类 命中、闪避
			prop = ([
				"spells_succ":1,
				"combat_succ":1,
				"spells_dodge" : 1,
				"spells_dodge" : 1,
			]);
			break;
		case "cloth" : //衣类 精神上限
			prop = ([ "max_sen":50,]);
			break;
		case "fan" : //幡类 格挡
			prop = ([ "combat_parry" : 5,]);
			break;		
		default : return 0;
	}
	return prop;
}
//附加属性
mixed *equip_apply()
{
	object obj = this_object();
	string type;
	type = obj->query("my_type");
	if( !type || !stringp(type) )
		return 0;
	switch(type)
	{
		case "jing" : //镜类
			return ({
				(["re_spells_effdamage": 1,]),
				(["re_spells_damage": 1,]),
			});
		case "san" : //伞类
			return ({
				(["re_combat_effdamage": 1,]),
				(["re_combat_damage": 1,]),
			});
		case "whip" : //索类
			return ({
				(["ad_whip": 5,]),
				(["whip"   : 8,]),
				(["ad_juqingbian" : 5,]),
			});	
		case "ling" : //铃类
			return ({
				(["spells_damage": 5,]),
				(["spells_succ": 1,]),
				(["reduce_busy" : 1,]),
			});
		case "stone" : //灵石类
			return ({
				(["combat_succ": 1,]),
				(["attack": 1,]),
			});
		case "shan" :  //扇类
			return ({
				([ "spells_dodge": 1,]),
				(["combat_parry": 1,]),
			});	
		case "fu" :  //符类
			return ({
				([ "receive_heal_sen": 1,]),
				([ "receive_curing_sen": 1,]),
				(["receive_meditate" : 1,]),
			});
		case "yin" :  //印类
			return ({
				([ "combat_succ": 1,]),
				(["combat_damage": 8,]),
				(["strength" : 2,]),
			});
		case "weapon" :  //武器类
			return ({
				(["combat_damage": 5,]),
				(["spells_damage": 5,]),
			});	
		case "char" : //容器类
			return ({
				([ "receive_sen": 5, ]),
				([ "receive_kee": 5, ]),
			});	
		case "huan" : //环类
			return ({
				([ "max_kee":30,]),
				([ "max_sen":30,]),
				([ "max_force":20,]),
				([ "max_mana":20,]),
			});	
		case "deng" : //灯类
			return ({
				([ "spells_succ":1,]),
				(["combat_succ":1,]),
				(["spells_dodge" : 1,]),
				(["spells_dodge" : 1,]),
			});
		case "cloth" : //衣类
			return ({
				([ "max_sen":40,]),
				(["personality" : 2,]),
				([ "karma" : 1,]),
			});	
		case "fan" : //幡类
			return ({
				([ "combat_parry" : 5,]),
				([ "composure" : 2,]),
				([ "courage" : 2,]),
			});	
		default : return 0;
	}
}

//生成法宝颜色
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
//生成头衔
void init_title()
{
	string clr,title,*ts,*da;
	int i,lv,dd;
	if( query("fabao_title") )
		return;
	if( !lv=query("level") )
		return;	
	if( !stringp(clr=query("fabao_color")) 
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
	set("fabao_title",title);
	for(i=0;i<sizeof(da);i++)
	{
		dd = lv;
		dd = random(dd/20)+1+random(5);
		add("armor_prop/"+da[i],dd);
	}
}	

void create()
{
	set_name("自制法宝物件", ({ "fabao object", "fabao", "object" }) );
	set("armor_type","Fabao");
	setup();
}

void init()
{
	if( query("owner_id")==this_player()->query("id") )
	{
		add_action("do_charge", "charge");	//升级
		add_action("do_dest", ({"destruct","zhuxiao"}));	//注销
		add_action("do_res","reserve");
		add_action("do_qu","xishou");
	}
}

void finish_res(object me,object fabao,string arg,int d)
{
	if( !me )
		return;
	if( fabao && present(fabao,me) )
	{
		fabao->add_temp("fabao/"+arg,d);
		if( fabao->query_temp("fabao/"+arg)>=fabao->query("fabao/max_"+arg) )
			fabao->set_temp("fabao/"+arg,fabao->query("fabao/max_"+arg));
		tell_object(me,"\n只见"+fabao->name(1)+"突然放出五彩霞光，你面露喜色，长长地吐了一口气。\n");
		tell_object(me,HIY"【系统】"+fabao->name(1)+HIY"成功充入了"HIR+d+HIY"点"HIC+(arg=="force"?"内力":"法力")+HIY"，你可以随时抽取 "HIR"xishou"HIY" 。"NOR"\n");
	}		
	me->start_busy(1);
}

int do_res(string arg)
{
	int t,d;
	object fabao = this_object(),me = this_player();
	
	if( !query("owner_id") || query("owner_id")!=me->query("id") )
		return 0;
	if( !present(this_object(),me) )
		return 0;
	if( !arg || sscanf(arg,"%s %d",arg,d)!=2 )
		return err_msg("命令格式：reserve <force或mana> <存储数量>\n");
	if( arg!="mana" && arg!="force" )
		return err_msg("你只能存储内力(force)或法力(mana)。\n");
	if( me->is_busy() || me->is_fighting() )
		return err_msg("你现在正忙着呢。\n");
	if( d<50 )
		return err_msg("至少要存储50点。\n");
	if( query_temp("fabao/"+arg)>=query("fabao/max_"+arg) )
		return err_msg(name(1)+"发出炫目的霞光，看来已经充能满了。\n");
	if( me->query(arg)<d*2 )
		return err_msg("你的内法不足，无法充能。\n");
	if( me->query_maxforce()<d && arg=="force" )
		return err_msg("你的内力修为太差了。\n");
	if( me->query_maxmana()<d && arg=="mana" )
		return err_msg("你的法力修为太低了。\n");
	if( arg=="force" )	
		write("你盘膝而坐，内息运转小周天，双手发出幽幽的光华，抵住"+name(1)+"缓缓运功。\n");
	else	write("你盘膝而坐，心神沉寂泥丸宫之后，双手发出幽幽的光华，抵住"+name(1)+"缓缓运功。\n");
	me->add(arg,-d);
	d = d/3+random(d*2/3);
	t = d/100;
	if( t<5 )
		t = 5;
	if( t>10 )
		t = 10;
	me->start_busy(t);
	me->start_call_out( (: call_other, __FILE__, "finish_res", me, fabao,arg,d:), t);
	return 1;
}

int do_qu(string arg)
{
	int t,d;
	object me = this_player();
	
	if( !query("owner_id") || query("owner_id")!=me->query("id") )
		return 0;
	if( !present(this_object(),me) )
		return 0;
	if( !arg || sscanf(arg,"%s %d",arg,d)!=2 )
		return err_msg("命令格式：xishou <force或mana> <抽取数量>\n");
	if( arg!="mana" && arg!="force" )
		return err_msg("你只能抽取内力(force)或法力(mana)。\n");
	if( me->is_busy() )
		return err_msg("你现在正忙着呢。\n");
	if( d<0 )
		return err_msg("你要抽取多少。\n");
	if( query_temp("fabao/"+arg)<d )
		return err_msg(name(1)+"存储的"+(arg=="force"?"内力":"法力")+"已不足"+d+"点。\n");
	if( me->query("force")+d>me->query_maxforce()*2 && arg=="force" )
		return err_msg("你的内力足够充沛。\n");
	if( me->query("mana")+d>me->query_maxmana()*2 && arg=="mana" )
		return err_msg("你的法力足够充沛。\n");
	write("你双手抵住"+name(1)+"，默念口诀，"+name(1)+"上闪了几闪，你只觉如潮的"+(arg=="force"?"内力":"法力")+"瞬间充斥了你全身。\n");
	me->add(arg,d);
	add_temp("fabao/"+arg,-d);
	if( query_temp("fabao/"+arg)<=0 )
		set_temp("fabao/"+arg,0);
	return 1;
}

int init_fabao(object who)
{
	mixed prop;
	mapping temp;
	string clr,*tmp,data;
	int level,i,*k,p,pp,num,a_lvl,m,sheng,qian;
	if( !who )
		return 0;
	if( query("default_set") || !query("fabao_type") 
	 || query("owner_id") )
		return 0;	
	level = who->query_level();
	if( who->query_temp("fabao_level")>0 
         && who->query_temp("fabao_level")<=level )
		level = who->query_temp("fabao_level");
	else	level = level*9/10+random(level/10);
	if( level<1 )
		return 0;
	
	//基本属性
	prop = equip_base();
	if( !prop || !mapp(prop) )
		return 0;
	clr = init_color(who);		
	if( clr && stringp(clr) && clr!="" )
	{
		set("fabao_color",clr);
		switch(clr)
		{	//num:基数 pp:条数 sheng:升级基数 qian:镶嵌基数
			case "HIY" : num = 1;pp = 1;sheng=1;qian=1;break;
			case "HIB" : num = 1;pp = 1+random(5);sheng=1;qian=2;break;
			case "HIC" : num = 2;pp = 2;sheng=2;qian=3;break;
			case "HIR" : num = 3;pp = 3;sheng=3;qian=4;break;
			case "HIM" : num = 5;pp = 4;sheng=4;qian=5;break;
		}
	}
	set_weight(10*level);
        if( clonep() )
                set_default_object(__FILE__);
        set("value", 0);
        set("level",level);
	if( clr=="HIM" || clr=="HIR" )
		init_title();        
        set("default_set",1);
        set("changed",1);
        set("owner_id",who->query("id"));
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
		add("armor_prop/"+tmp[i],p);	
	}
//基本属性结束
	if( !clr || !stringp(clr) || clr=="" )
		return 1;
	prop = equip_apply();
	if( !prop || !arrayp(prop) || sizeof(prop)<1 )
		return 3;
	m = pp;
	if( m>sizeof(prop) )
		m = sizeof(prop);
	for(i=0;i<m;i++)
	{
		if( random(level/2)/2<5 )
			continue;
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

int do_dest(string arg)
{
	mixed *fb;
	string msg,type;
	object me = this_player();
	if( !arg || !id(arg) )
        	return 0;
	if( me!=environment() )
        	return 0;  
	if( !query("owner_id") || !query("valid_time") )
        	return 0;
	if( query("armor_type")!="Fabao" )
		return err_msg(name(1)+"法宝类型缺失。\n");
	type = sprintf("Fabao_%d_%s",query("valid_time"),this_object()->name());
	type = COLOR_D->clean_color(type);
	if( !arrayp(fb=me->query("fabao"))
	 || sizeof(fb)<1 
	 || member_array(type,fb)==-1 )
		return err_msg(name()+"不是你的绑定法宝。\n");	 
	if( query("owner_id")
  	 && me->query("id")!=query("owner_id") )
        	return err_msg(name()+"是"+query("owner_id")+"的专属法宝。\n");
	if( (me->query("potential")-me->query("learned_points"))<800 )   
        	return err_msg("你的潜能不够,无法注销法宝。\n");
        seteuid(getuid());	
	if( !rm(query_save_file()+ __SAVE_EXTENSION__) )
        	return err_msg("注销失败。\n");
	fb-= ({type});
	fb-= ({0});	
	me->add("potential",-800);
	write("注销成功。\n");
	if( sizeof(fb)>0 )
		me->set("fabao",fb);
	else	me->delete("fabao");
	me->save(1);
	if( !stringp(msg=this_object()->query("fabao/dest_msg"))
	 || strlen(msg)<2 )
	 	msg = "$N手中的$n轰的一声炸成了碎片。。。。\n";
	message_vision(msg,me,this_object());
	destruct(this_object());
	return 1;
}

int to_save()
{
	int t;
	string type,name;
	mixed *fb;
	object me = environment();
	if( !me || !query("owner_id") 
	 || me->query("id")!=query("owner_id") )
		return err_msgs("这不是你的。\n");
	if( me->is_busy() )
		return err_msgs("你正忙着。\n");
	if( query("no_save") )
		return err_msgs("这个物品不能绑定。\n");
	if( !stringp(type=query("armor_type"))
	 || type!="Fabao" )
		return err_msgs("这不是法宝。\n");		
	if( query("equipped") )
		return err_msgs("你必须先将"+this_object()->query("name")+"卸下。\n");
	if( (me->query("potential")-me->query("learned_points"))<1000 )   
		return err_msgs("你的潜能不够,无法保存法宝。\n");
	me->start_busy(1); 		
	set("valid_time",time());
	t = query("valid_time");
	fb = me->query("fabao");
	if( !fb || !arrayp(fb) || sizeof(fb)<1 )
		fb = ({});
	fb-= ({0});	
	set("no_give",1);
	set("no_save",1);
	delete("changed");
	set("ids",this_object()->query_my_id());
	set("names",this_object()->query("name"));
	if( this_object()->save() )
	{
        	me->add("potential",-1000);
        	name = this_object()->name();
        	if( !name || !stringp(name) )
        		name = "无名";
        	name = COLOR_D->clean_color(name);
        	fb+= ({type+"_"+t+"_"+name});
		me->set("fabao",fb);
		me->save(1);
		tell_object(me,HIY"【系统】"+this_object()->name()+HIY"绑定成功，如果消失，你可以通过"HIR"zhaohuan Fabao"HIY"|"HIR+name+HIY"命令来重新获得，如要注销，请使用 destruct|zhuxiao 命令。"NOR"\n");
		destruct(this_object());
        	return 1;
	}
	return 0;
}

string status_bar(int max,int val,string fcolor)
{
        string ret;
        int i, n, max_n = 8;
	string bcolor = NOR,dcolor=CYN;
        if( max == 0 ) max = 1;
        n = val * 100 / max / 10;

        if( n < 0 ) n = 0;
        if( n > max_n ) n = max_n;

        ret = NOR  + bcolor + fcolor;
        for( i = 0 ; i < max_n; i ++ ) {
                if( i < n )  ret += "━";
                else ret += NOR+dcolor+"─"NOR;
        }
        ret += NOR;
        return ret;
}

string show_status()
{
	string *types,str,long,status = "";
	int i;
	str="";
	
	if( stringp(long=query("long")) )
		status+= "法宝简介："+long;

	if( arrayp(types=query("fabao_type"))
	 && sizeof(types)>0 )
	{
		for(i=0;i<sizeof(types);i++)
		{
			switch(types[i])
			{
				case "attack" 	: str+= "攻击";break; 
				case "cure"	: str+= "恢复";break;
				case "def"	: str+= "护体";break;
				case "other"	: 
					str+= "辅助";
					if( query("飞行") )
						str+= "<飞行>";
					break;
			}
			str+= "类";
			if( i<sizeof(types)-1 )
				str+= "、";
		}
		str = "法宝类型："+str+"\n";
	}
	
	//法宝本身的攻击防御，针对于法宝之间的相互争斗
	if( self_damage()>0 )
		status += "          法宝自身伤害 " + status_bar(self_damage(), query_temp("fabao/self_damage"), HIR) + NOR" "HIY+query_temp("fabao/self_damage")+"/"+self_damage()+NOR"\n";
	if( self_def()>0 )
		status += "          法宝自身防御 " + status_bar(self_def(), query_temp("fabao/self_def"), HIM) + NOR" "HIY+query_temp("fabao/self_def")+"/"+self_def()+NOR"\n";
	//法宝的攻击防御，针对于对攻击对象
	if( query_combat_damage()>0 )
		status += "          对敌气血伤害 " + status_bar(query_combat_damage(), query_temp("fabao/combat_damage"), HIR)  + NOR" "HIY+query_temp("fabao/combat_damage")+"/"+query_combat_damage()+NOR+HIC" charge"NOR"\n";
	if( query_spells_damage()>0 )
		status += "          对敌精神伤害 " + status_bar(query_spells_damage(), query_temp("fabao/spells_damage"), HIR) + NOR" "HIY+query_temp("fabao/spells_damage")+"/"+query_spells_damage()+NOR+HIC" charge"NOR"\n";
	if( query_combat_def()>0 )
		status += "          对敌气血保护 " + status_bar(query_combat_def(), query_temp("fabao/combat_def"), HIM) + NOR" "HIY+query_temp("fabao/combat_def")+"/"+query_combat_def()+NOR+HIC" charge"NOR"\n";
	if( query_spells_def()>0 )
		status += "          对敌精神保护 " + status_bar(query_spells_def(), query_temp("fabao/spells_def"), HIM) + NOR" "HIY+query_temp("fabao/spells_def")+"/"+query_spells_def()+NOR+HIC" charge"NOR"\n";
	if( query("fabao/max_force")>0 )
		status += "          已存储内力点 " + status_bar(query("fabao/max_force"), query_temp("fabao/force"), HIM) + NOR" "HIY+query_temp("fabao/force")+"/"+query("fabao/max_force")+NOR+HIC+(query_temp("fabao/force")<=0?" reserve":" xishou")+NOR"\n";
	if( query("fabao/max_mana")>0 )
		status += "          已存储法力点 " + status_bar(query("fabao/max_mana"), query_temp("fabao/mana"), HIM) + NOR" "HIY+query_temp("fabao/mana")+"/"+query("fabao/max_mana")+NOR+HIC+(query_temp("fabao/mana")<=0?" reserve":" xishou")+NOR"\n";
	str+= "法宝属性：\n";
	if( status!="" )
		status = str+status;
	if( query("ji_time")>0 )
		status+= "法宝冷却："+query("ji_time")+"秒\n";
	status+= "法宝状态："+(query_temp("jiing")?"祭出":"空闲")+"\n";	
	return status;
}

int do_charge(string arg)
{
	string *types,type,tmp;
	object me= this_player();
	object fabao_ob= this_object();
	int cost = 100;//now fix cost as 100, both fali and neili
        int f = 0,delay_factor = 20;//actually delay is cost/delay_factor...in unit of second.
	
	if( !present(this_object(),me) )
		return 0;
	if( !arg || sscanf(arg,"%s's %s",arg,type)!=2 )
		return notify_fail(Err_msg);
	if( !id(arg) )
		return notify_fail(Err_msg);
	types = keys(fabao_prop);
	if( member_array(type,types)==-1 )
		return notify_fail(Err_msg);
	if( me->is_busy()
	|| me->is_fighting()
	|| me->query_temp("pending/exercising"))
		return err_msg("你正忙着呢．．．\n");
	if( environment(me)->query("no_fight")
	|| environment(me)->query("no_magic") )
		return err_msg("这里不是修炼法宝的地方。\n");
	if( (int)me->query("mana") < 3*cost ) //maybe used to charge 3 parameters.
		return err_msg("你目前的法力太低，不能修炼法宝。\n");
	if( (int)me->query("force") < 3*cost ) //maybe used to charge 3 parameters.
		return err_msg("你目前的内力太低，不能修炼法宝。\n");

	tmp = fabao_prop[type];
	
	switch(type)
	{
		case "combat_damage" : 
			if( query_combat_damage()<=0 )
				return err_msg(name()+"没有提升「"+fabao_prop[type]+"」的可能。\n");
			if( query_temp("fabao/"+type)>=query_combat_damage() )
				f = 1;							
			break;
		case "spells_damage" : 
			if( query_spells_damage()<=0 )
				return err_msg(name()+"没有提升「"+fabao_prop[type]+"」的可能。\n");
			if( query_temp("fabao/"+type)>=query_spells_damage() )
				f = 1;							
			break;
		case "combat_def" : 
			if( query_combat_def()<=0 )
				return err_msg(name()+"没有提升「"+fabao_prop[type]+"」的可能。\n");		
			if( query_temp("fabao/"+type)>=query_combat_def() )
				f = 1;							
			break;
		case "spells_def" : 
			if( query_spells_def()<=0 )
				return err_msg(name()+"没有提升「"+fabao_prop[type]+"」的可能。\n");				
			if( query_temp("fabao/"+type)>=query_spells_def() )
				f = 1;							
			break;
		case "self_damage": 
			if( self_damage()<=0 )
				return err_msg(name()+"没有提升「"+fabao_prop[type]+"」的可能。\n");				
			if( query_temp("fabao/"+type)>=self_damage() )
				f = 1;							
			break;
		case "self_def" : 
			if( self_def()<=0 )
				return err_msg(name()+"没有提升「"+fabao_prop[type]+"」的可能。\n");				
			if( query_temp("fabao/"+type)>=self_def() )
				f = 1;							
			break;
	}
	if( f==1 )
		return err_msg(query("name")+"的"+tmp+"已在最佳状态。\n");

	me->add("force", -cost);
	me->add("mana", -cost);
	message_vision("$N口中念念有词，以法力将自己的内力缓缓地注入$n之中。\n", me, fabao_ob);
	me->start_busy(2);
	remove_call_out("charged");
	call_out("charged",3, me,type);
	return 1;
}

void charged(object me, string type)
{
	string property;
	property = "fabao/"+type;
	switch(type)
	{
		case "combat_damage" : 
			if( query_temp("fabao/"+type)>=query_combat_damage() )
				return;
			else	set_temp(property,query_combat_damage());	
			break;
		case "spells_damage" : 
			if( query_temp("fabao/"+type)>=query_spells_damage() )
				return;
			else	set_temp(property,query_spells_damage());	
			break;
		case "combat_def" : 
			if( query_temp("fabao/"+type)>=query_combat_def() )
				return;
			else	set_temp(property,query_combat_def());	
			break;
		case "spells_def" : 
			if( query_temp("fabao/"+type)>=query_spells_def() )
				return;
			else	set_temp(property,query_spells_def());		
			break;
		case "self_damage": 
			if( query_temp("fabao/"+type)>=self_damage() )
				return;
			else	set_temp(property,self_damage());	
			break;
		case "self_def" : 
			if( query_temp("fabao/"+type)>=self_def() )
				return;
			else	set_temp(property,self_def());	
			break;
	}
	message_vision("\n只见$n突然放出五彩霞光，$N面露喜色，长长地吐了一口气。\n", me, this_object());
	return;
}

//气血自动防御,无效则返回 damage
int protect_qi(int damage)
{
	string msg;
	object me = environment();
	int unit,def = query_temp("fabao/combat_def");
	if( !me || !living(me) || def <= 0 ) 
		return damage;
	if( member_array("def",query("fabao_type"))==-1 )
		return damage;
	if( this_object()->query_combat_def()<=0 )
		return damage;		
	if( !query_temp("jiing") || !query("equipped") )
		return damage;
	if( me->query("mana")<100 )
		return damage;	
	unit = query_temp("fabao/def_unit");	
	if( unit<=0 )
		unit = def/10;
	damage = damage-def;
	if( damage<0 )
		damage = 0;
	unit = unit-1;
	if( unit<=0 )
	{
		set_temp("fabao/combat_def",0);
		set_temp("fabao/def_unit",0);
	}
	else	set_temp("fabao/def_unit",unit);	
	if( stringp(msg=this_object()->query("fabao/def_msg"))
	 && strlen(msg)>2 )
		message_vision(msg,me);	 
	return damage;	
}
//精神自动防御,无效则返回 damage
int protect_shen(int damage)
{
	string msg;
	object me = environment();
	int unit,def = query_temp("fabao/spells_def");
	if( !me || !living(me) || def <= 0 ) 
		return damage;
	if( member_array("def",query("fabao_type"))==-1 )
		return damage;
	if( this_object()->query_spells_def()<=0 )
		return damage;			
	if( !query_temp("jiing") || !query("equipped") )
		return damage;
	if( me->query("mana")<100 )
		return damage;	
	unit = query_temp("fabao/def_unit");	
	if( unit<=0 )
		unit = def/10;
	damage = damage-def;
	if( damage<0 )
		damage = 0;
	unit = unit-1;
	if( unit<=0 )
	{
		set_temp("fabao/spells_def",0);
		set_temp("fabao/def_unit",0);
	}
	else	set_temp("fabao/def_unit",unit);	
	if( stringp(msg=this_object()->query("fabao/def_msg"))
	 && strlen(msg)>2 )
		message_vision(msg,me);	 
	return damage;	
}

//战斗中法宝auto攻击
mixed hit_ob(object attacker,object target,int attack_type)
{
	mapping hit;
        int damage,def;
        object fabao = this_object();
	object t_fabao;
	string msg,succ_msg;
                                	
	if( !attacker || !present(fabao,attacker) )
		return 0;
	if( !fabao->query("equipped") || !fabao->query_temp("jiing") )
	 	return 0;
	if( !target || !attacker->is_fighting(target) )
		return 0;
	if( query("no_fabao/hit_ob") )
		return 0;
	if( COMBAT_D->check_level(attacker,target)==-1 )
		return 0;
	if( this_object()->query_combat_damage()<=0
	 && this_object()->query_spells_damage()<=0 )
	 	return 0;
	if( attack_type!=TYPE_CAST )
		damage = fabao->query_temp("fabao/combat_damage");
	else	damage = fabao->query_temp("fabao/spells_damage");
	if( damage<=0 )
		return 0;
	if( !stringp(msg = fabao->query("fabao/attack_msg"))
	 || strlen(msg)<2 )
	 	return 0;

	if( !objectp(t_fabao=target->query_temp("armor/Fabao")) 
	 || !t_fabao->query("equipped") || !t_fabao->query_temp("jiing") )
	{
		hit = ([
			"damage" : damage,
			"msg" : msg,
		]);	
	}	
	else 
	{
		if( attack_type!=TYPE_CAST )
			def = t_fabao->query_temp("fabao/combat_def");
		else	def = t_fabao->query_temp("fabao/spells_def");		 	
		msg+= stringp(t_fabao->query("fabao/def_msg"))?t_fabao->query("fabao/def_msg"):"";
		damage = damage-def;
		if( damage<0 ) damage = 0;
		hit = ([
			"damage" : damage,
			"msg" : msg,
		]);
	}
	msg = hit["msg"];
	damage = hit["damage"];
	if( damage<=0 )
		return 0;
	if( attack_type==TYPE_CAST )
	{
		damage = target->receive_damage("sen",damage,attacker,TYPE_CAST);
	 	if( COMBAT_D->query_message_type(attacker,target)!=2 )
	 		msg+= "( $n" + COMBAT_D->sen_status_msg((int)target->query("sen") * 100/(1+(int)target->query_maxsen()) ) + " )\n";
	 	else	msg+= "结果造成了"HIR+damage+NOR"点精神减少";
	 	if( random(attacker->query_skill("yujianshu")/50)>5
	 	 && attacker->query("mana_factor")>0 )
		{	 	 
	 		damage = target->receive_wound("sen",damage/5+1,attacker,TYPE_CAST); 
	 		if( COMBAT_D->query_message_type(attacker,target)==2 )
	 			msg+= "和"HIR+damage+NOR"点精神损失。\n";
		}
		else if( COMBAT_D->query_message_type(attacker,target)==2 )
			msg+= "。\n";
	}
	else
	{
	 	damage = target->receive_damage("kee",damage,attacker,TYPE_CAST);
	 	if( COMBAT_D->query_message_type(attacker,target)!=2 )
	 		msg+= "( $n" + COMBAT_D->status_msg((int)target->query("kee") * 100/(1+(int)target->query_maxkee()) ) + " )\n";
	 	else	msg+= "结果造成了"HIR+damage+NOR"点气血减少";
	 	if( random(attacker->query_skill("yujianshu")/50)>5
	 	 && attacker->query("mana_factor")>0 )
		{	 	 
	 		damage = target->receive_wound("kee",damage/5+1,attacker,TYPE_CAST); 
	 		if( COMBAT_D->query_message_type(attacker,target)==2 )
	 			msg+= "和"HIR+damage+NOR"点气血损失。\n";
	 		else	msg+= "( $n" + COMBAT_D->eff_status_msg((int)target->query("eff_kee") * 100/(1+(int)target->query_maxkee()) ) + " )\n";	
		}
		else if( COMBAT_D->query_message_type(attacker,target)==2 )
			msg+= "。\n";
	}
	damage = damage-30;
	if( damage<=0 )
		damage = 0;
	if( attack_type!=TYPE_CAST )
		damage = fabao->set_temp("fabao/combat_damage",damage);
	else	damage = fabao->set_temp("fabao/spells_damage",damage);
	return msg;
}

varargs string name(int v)
{
	string cls,name = ::name(v);
	if( v>0 )
		return name;
	if( query("fabao_title") )
		name = query("fabao_title")+"之"+name;
	if( query("fabao_color") )
	{
		name = query("fabao_color")+name;	
		name = COLOR_D->replace_color(name,1);
		if( query("fabao_color")=="HIM" )
		{
			switch(cls)
			{
				case "shen" : 
				case "dragon" :
				case "fighter" :
				case "xian" : name = HIM"(仙器)"+name;break;
				case "youling" :
				case "ghost" : name = HIM"(鬼器)"+name;break;
				case "seng"  :
				case "bonze" : name = HIM"(佛器)"+name;break;
				case "taoist": name = HIM"(道器)"+name;break;
				case "scholar" : name = HIM"(儒器)"+name;break;
				case "dancer" : name = HIM"(魅器)"+name;break;
				case "yaomo" : name = HIM"(妖器)"+name;break;
				case "tianmo" : name = HIM"(魔器)"+name;break;
				default : name = HIM"(灵器)"+name;break;
			}
		}
	}
	return name;
}

int unequip()
{
	string msg;
	int v = ::unequip();
	if( v>0 )
	{
		if( query_temp("jiing") )
		{
			delete_temp("jiing");
			if( stringp(msg=this_object()->query("fabao/back_msg")) 
		 	 && strlen(msg)>2 )
				message_vision(msg,this_player(),this_object());		 
		}		
	}
	return v;
}	

int is_zhaohuan(){return query("no_save");}