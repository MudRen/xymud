// look.c
#include <room.h>
#include <ansi.h>
#include <armor.h>
#include <combat.h>
inherit F_CLEAN_UP;
#include <look.h>

int look_room(object me, object env);
int look_home(object me, object env);
varargs int look_item(object me, object obj,int v);
int look_living(object me, object obj);
int look_room_item(object me, string arg);
varargs string mix_arg( string msg_one, string msg_two, int wi );
//点
mapping equip_prop = ([
	"spells_def"	: "法术防御",
	"spells_damage"	: "法术攻击",
	"combat_def"	: "物理防御",
	"combat_damage"	: "物理攻击",
	"strength"	: "后天体格",
	"courage"	: "后天胆识",
	"intelligence"	: "后天悟性",
	"spirituality"	: "后天灵性",
	"composure"	: "后天定力",
	"personality"	: "后天魅力",
	"constitution"	: "后天根骨",
	"karma"		: "后天福缘",
	"max_kee"	: "气血后限",
	"max_sen"	: "精神后限",	
	"max_force"	: "内力后限",
	"max_mana"	: "法力后限",
	"max_gin"	: "活力后限",
       	"receive_force"	: "内力自动恢复",
       	"receive_mana"	: "法力自动恢复",
       	"receive_kee"	: "气血自动恢复",
       	"receive_sen"	: "精神自动恢复",
       	"reduce_busy"	: "僵直效果减少",
]);       	

//百分比
mapping equip_prop2 = ([
	"re_spells_effdamage" : "法术损伤反弹百分比",
	"re_combat_effdamage" : "物理损伤反弹百分比",
       	"attack"	: "攻击命中率",
       	"defense"	: "攻击闪避率",
       	"spells_succ"	: "法术命中率",
       	"spells_dodge"	: "法术闪避率",
       	"combat_succ"	: "物理命中率",
       	"combat_dodge"	: "物理闪避率",
       	"combat_parry"	: "物理招架率",
       	"force_recover" : "吸气效果追加",
       	"fofce_refresh"	: "凝神效果追加",
       	"receive_heal_kee"	: "气血恢复附加率",
	"receive_heal_sen"	: "精神恢复附加率",
	"receive_curing_kee"	: "气血治疗附加率",
       	"receive_curing_sen"	: "精神治疗附加率",
       	"receive_exercise"	: "打坐恢复附加率",
	"receive_meditate"	: "冥思恢复附加率",
	"re_spells_damage" : "法术伤害反弹百分比",
	"re_combat_damage" : "物理伤害反弹百分比",
]);

mapping query_euqip_look1(){ return equip_prop;}
mapping query_euqip_look2(){ return equip_prop2;}

mapping query_euqip_look()
{
	return ([
	"spells_def"	: "法术防御",
	"spells_damage"	: "法术攻击",
	"combat_def"	: "物理防御",
	"combat_damage"	: "物理攻击",
	"strength"	: "后天体格",
	"courage"	: "后天胆识",
	"intelligence"	: "后天悟性",
	"spirituality"	: "后天灵性",
	"composure"	: "后天定力",
	"personality"	: "后天魅力",
	"constitution"	: "后天根骨",
	"karma"		: "后天福缘",
	"max_kee"	: "气血后限",
	"max_sen"	: "精神后限",	
	"max_force"	: "内力后限",
	"max_mana"	: "法力后限",
	"max_gin"	: "活力后限",
       	"receive_force"	: "内力自动恢复",
       	"receive_mana"	: "法力自动恢复",
       	"receive_kee"	: "气血自动恢复",
       	"receive_sen"	: "精神自动恢复",
       	"reduce_busy"	: "僵直效果减少",	
//
	"re_spells_effdamage" : "法术损伤反弹百分比",
	"re_combat_effdamage" : "物理损伤反弹百分比",
       	"attack"	: "攻击命中率",
       	"defense"	: "攻击闪避率",
       	"spells_succ"	: "法术命中率",
       	"spells_dodge"	: "法术闪避率",
       	"combat_succ"	: "物理命中率",
       	"combat_dodge"	: "物理闪避率",
       	"combat_parry"	: "物理招架率",
       	"force_recover" : "吸气效果追加",
       	"fofce_refresh"	: "凝神效果追加",
       	"receive_heal_kee"	: "气血恢复附加率",
	"receive_heal_sen"	: "精神恢复附加率",
	"receive_curing_kee"	: "气血治疗附加率",
       	"receive_curing_sen"	: "精神治疗附加率",
       	"receive_exercise"	: "打坐恢复附加率",
	"receive_meditate"	: "冥思恢复附加率",
	"re_spells_damage" : "法术伤害反弹百分比",
	"re_combat_damage" : "物理伤害反弹百分比",       	
	]);
}

string ride_suffix (object me)
{
	string ridemsg = 0;
	object ridee = 0;

	ridee = me->ride();
	if(ridee)
	{
		if( !ridemsg = ridee->query("ridemsg") )
        		ridemsg = ridee->query("ride/msg")+"在"+ridee->name()+"上";
        }
	return  ridemsg;
}

void create() { seteuid(getuid()); }

int look_book(object me,object obj)
{
	string str,arg,*temp;
	mapping skill;
	int i;
	if( !me || !obj || !obj->is_book() )
		return 0;
	if( !mapp(skill=obj->query("skill"))
	 || sizeof(skill)<1 )
	 	return 0;
	str = obj->name()+"\n";
	if( stringp(arg=obj->query("long")) )
		str+= arg;
	if( !undefinedp(skill["name"]) )
		str+= "    技能：「"+to_chinese(skill["name"])+"」\n";
	if( !undefinedp(skill["exp_required"]) )
		str+= "    增长："+	skill["exp_required"] +" 点\n";
	if( !undefinedp(skill["sen_cost"]) )
		str+= "    耗神："+	skill["sen_cost"] +" 点\n";
	if( !undefinedp(skill["difficulty"]) )	
	{
		if( skill["difficulty"] - (int)me->query_int()<0 )
			arg = "简单";
		else if( skill["difficulty"] - (int)me->query_int()==0 )
			arg = "普通";
		else	arg = "较难";
		str+= "    难度："+	arg +"\n";			
	}
	if( !undefinedp(skill["max_skill"]) )
		str+= "    等级："+	skill["max_skill"] +" 级\n";
	me->start_more(str);
	return 1;
}

int main(object me, string arg)
{
	object obj,who;
	int result;
	string target;

	if( !arg ) 
		result = look_room(me, environment(me));
	else if( sscanf(arg,"%s in %s",arg,target)==2 )
	{
		who = present(target, environment(me));
		if( !who || !who->is_character() )
			return notify_fail("这里没有"+target+"。\n");
		obj = present(arg,who);
		if( !obj ) 
			return notify_fail("对方身上没有这样东西。\n");
		if( !obj->query("equipped") )
			return notify_fail("你只能看对方装备着的物品。\n");
		return  look_item(me, obj);  		
	}	
	else if( (obj = present(arg, me)) || (obj = present(arg, environment(me)))) 
        {
        	if( obj->is_character() && !obj->is_corpse() ) 
        		result = look_living(me, obj);
        	else    result = look_item(me, obj);
        } 
	else    result = look_room_item(me, arg);
	return result;
}

string armor_type(string type)
{
	if( !type )
		return "杂类";
	switch(type)
	{
		case "kui"	:
		case TYPE_HEAD	: return "帽类";
		case "ring" 	:
		case TYPE_NECK	: return "项链";
		case TYPE_CLOTH	: return "衣服";
		case TYPE_ARMOR	: return "盔甲";
		case "pifeng"	:
		case TYPE_SURCOAT : return "披风";
		case TYPE_WAIST	: return "腰带";
		case TYPE_WRISTS : return "护腕";
		case TYPE_SHIELD : return "盾类";
		case TYPE_FINGER : return "戒指";
		case TYPE_HANDS  : return "护手";
		case "shoes"	:
		case TYPE_BOOTS : return "鞋类";
		case "fabao"	: 
		case "Fabao"	: return "法宝";
		default		: return "杂类";
	}
}		

string weapon_type(string type)
{
	if( !type )
		return "奇门兵器";
	switch(type)
	{
		case "archery"	: return "箭";
		case "axe"	: return "斧";
		case "blade"	: return "刀";
		case "bow"	: return "弓";
		case "dagger"	: return "短兵";
		case "fork"	: return "叉";
		case "hammer"	: return "锤";
		case "mace"	: return "锏";
		case "rake"	: return "耙";
		case "sword"	: return "剑";
		case "staff"	: return "杖";
		case "stick"	: return "棍";
		case "throwing"	: return "暗器";
		case "whip"	: return "软鞭";
		case "spear"	: return "枪";
		case "unarmed"	: return "拳套";
		default		: return "奇兵";
	}
}	

varargs string look_equip_level(object obj,int raw)
{
	string str;
	int max,level,ad,i;
	max = obj->query("max_level");
	if( max<=0 || obj->query("base_level")<=0 )
		return 0;
	level = obj->query("level");
	ad = level-obj->query("base_level");
	str = "";
	for(i=0;i<max;i++)
	{
		if( i<ad )
			str+= CYN"★"NOR;
		else	str+= CYN"☆"NOR;	
	}
	if( raw )
		return str;
	if( ad<=0 )
		str+= " [ "NOR HIR+"0/"+max+NOR" ]";
	else	str+= " [ "NOR HIR+ad+"/"+max+NOR" ]";
	//str+= sprintf(" 成长度：%d/%d("HIR"%d%%"NOR") ]",obj->query("exp"),obj->query_needP(),obj->query("exp")*100/obj->query_needP());
	return str;
}

varargs string look_equip_enchase(object obj,int raw)
{
	string str,*enchs;
	int max,now,ad,i;
	max = obj->query("max_enchase");
	if( max<=0 )
		return 0;
	enchs = obj->query("enchase");
	if( !enchs || !arrayp(enchs) )
		ad = 0;
	else	ad = sizeof(enchs);	
	str = "";
	for(i=0;i<max;i++)
	{
		if( i<ad )
			str+= CYN"◆"NOR;
		else	str+= CYN"◇"NOR;	
	}
	if( raw )
		return str;
	if( ad<=0 )
		str+= " [尚未镶嵌]";
	else
	{
		str+= " [镶嵌了 ";
		for(i=0;i<ad;i++)
			str+= enchs[i]+" ";
		str+= "]";	
	}
	return str;
}

int look_armor(object me,object obj)
{
	mapping prop;
	object who;
	int i;
	mixed cls;
	string arg,*temp,str,str2,title,mod_msg;
	if( !obj || !me )
		return 0;
	prop = obj->query("armor_prop");
	if( !prop || !mapp(prop) )
		return look_item(me, obj,1);
	temp = keys(prop);
	if( !temp || !arrayp(temp) || sizeof(temp)<1 )
		return look_item(me, obj,1);	
	arg = obj->short()+"\n";
	if( look_equip_level(obj) )
		arg+= "装备锻造："+ look_equip_level(obj)+"\n";
	if( look_equip_enchase(obj) )
		arg+= "装备镶嵌："+ look_equip_enchase(obj)+"\n";		
	who = environment(obj);
	if( who && who->is_character() )
		arg+= sprintf("目前所属：%s\n",who->name());
	if( obj->query("female_only")
	 || obj->query("level")>1 )
	{
		arg+= "装备要求：";
		if( obj->query("female_only") )
			arg+= "女性 ";
		if( obj->query("level")>1 )
			arg+= " 人物等级"+obj->query("level")+"级 ";
		arg+= "\n";	
	}
	if( obj->query("family_name") )
	{
		arg+= "门派要求：";
		if( obj->query("family_name") )
			arg+= obj->query("family_name");
		arg+= "\n";	
	}
	else
	{
		cls = obj->query_class();
		if( stringp(cls) )
		{
			arg+= "门派要求：";
			arg+= cls+"弟子 ";
			arg+= "\n";	
		}
		else if( arrayp(cls) && sizeof(cls)>0 )
		{
			arg+= "门派要求：";
			for(i=0;i<sizeof(cls);i++)
			{
				if( !cls[i] || !stringp(cls[i]) )
					continue;
				arg+= cls[i];
				if( i<sizeof(cls)-1)
					arg+= "、";	
			}
			arg+= "\n";	
		}
	}
	arg+= sprintf("是否绑定：%s\n",obj->is_zhaohuan()?"是":"未");	
	arg+= sprintf("能否拾取：%s\n",obj->query("no_get")?"否":"能");	
	arg+= sprintf("装备等级：%s\n",obj->query("level")>0?(obj->query("level")+""):"1");
	if( obj->query("from") )
		arg+= sprintf("装备产地："HIG"%s"NOR"\n",obj->query("from"));
	if( obj->query("armor_type")!="Fabao" )	
		arg+= sprintf("装备类型：防具◆%s\n",armor_type(obj->query("armor_type")));
	else	arg+= sprintf("装备类型：法器◆%s\n",armor_type(obj->query("armor_type")));	
	if( obj->show_status() && stringp(obj->show_status()) && obj->show_status()!="" )
		arg+= obj->show_status();
	arg+= "装备属性：\n";
	for(i=0;i<sizeof(temp);i++)
	{
		if( prop[temp[i]]==0 )
			continue;
		if( temp[i]=="dodge" )
			continue;
		if( !undefinedp(equip_prop[temp[i]]) )
			str = equip_prop[temp[i]];
		else if( !undefinedp(equip_prop2[temp[i]]) )	
			str = equip_prop2[temp[i]];
		else
		{
			str = temp[i];
			if( is_chinese(to_chinese(str)) )
				str = to_chinese(str)+"有效等级";
			else if( sscanf(str,"ad_%s",str2) )
			{
				if( is_chinese(to_chinese(str2)) )
					str = to_chinese(str2)+"技能等级";
			}	
		}	
		str2 = sprintf("%d%s",prop[temp[i]]>=0?prop[temp[i]]:-prop[temp[i]],!undefinedp(equip_prop2[temp[i]])?"%":"点");	
		arg+= sprintf("      %20s : "HIR"%s"HIY"%s"NOR"\n",str,prop[temp[i]]>0?"+":"-",str2);
		str = str2 = "";
	}
	if( stringp(title=obj->query("armor_title")) )
	{
		if( MOD_D->is_mod(obj) )
		{
			mod_msg = MOD_D->mod_statue(me,title);
			if( mod_msg && stringp(mod_msg) )
				arg = mix_arg(arg,mod_msg,45);
		}	
	}
	
	me->start_more(arg);
        if( who && living(who) && me!=who )
        	tell_object(who,me->name()+"正盯着你身上的"+obj->name()+"左瞧右看，不知在打什么主意。\n");
	return 1;
}

int look_weapon(object me,object obj)
{
	mapping prop;
	object who;
	int i;
	string arg,*temp,str,str2,str3;
	if( !obj || !me )
		return 0;
	prop = obj->query("weapon_prop");
	if( !prop || !mapp(prop) )
		return look_item(me, obj,1);
	temp = keys(prop);
	if( !temp || !arrayp(temp) || sizeof(temp)<1 )
		return look_item(me, obj,1);
	arg = obj->short()+"\n";			
	if( look_equip_level(obj) )
		arg+= "装备锻造："+ look_equip_level(obj)+"\n";
	if( look_equip_enchase(obj) )
		arg+= "装备镶嵌："+ look_equip_enchase(obj)+"\n";		
	who = environment(obj);
	if( who && who->is_character() )
		arg+= sprintf("目前所属：%s\n",who->name());
	if( obj->query("female_only")
	 || obj->query("family_name")
	 || obj->query("level")>1 )
	{
		arg+= "装备要求：";
		if( obj->query("female_only") )
			arg+= "女性 ";
		if( obj->query("family_name") )
			arg+= obj->query("family_name")+"弟子 ";
		if( obj->query("level")>1 )
			arg+= " 人物等级"+obj->query("level")+"级 ";
		arg+= "\n";	
	}	
	if( obj->query("from") )
		arg+= sprintf("装备产地："HIG"%s"NOR"\n",obj->query("from"));
	arg+= sprintf("是否绑定：%s\n",obj->is_zhaohuan()?"是":"未");	
	arg+= sprintf("能否拾取：%s\n",obj->query("no_get")?"否":"能");	
	arg+= sprintf("装备等级：%s\n",obj->query("level")>0?(obj->query("level")+""):"1");
	arg+= sprintf("装备类型：武器◆%s\n",weapon_type(obj->query("skill_type")));
	arg+= "装备属性：\n";
	for(i=0;i<sizeof(temp);i++)
	{
		if( prop[temp[i]]==0 )
			continue;
		if( temp[i]=="dodge" )
			continue;	
		if( !undefinedp(equip_prop[temp[i]]) )
			str = equip_prop[temp[i]];
		else if( !undefinedp(equip_prop2[temp[i]]) )	
			str = equip_prop2[temp[i]];
		else
		{
			str = temp[i];
			if( is_chinese(to_chinese(str)) )
				str = to_chinese(str)+"有效等级";
			else if( sscanf(str,"ad_%s",str2) )
			{
				if( is_chinese(to_chinese(str2)) )
					str = to_chinese(str2)+"技能等级";
			}	
		}
		str2 = sprintf("%d%s",prop[temp[i]]>=0?prop[temp[i]]:-prop[temp[i]],!undefinedp(equip_prop2[temp[i]])?"%":"点");	
		arg+= sprintf("      %20s : "HIR"%s"HIY"%s"NOR"\n",str,prop[temp[i]]>0?"+":"-",str2);
		str = str2 = "";
	}
	me->start_more(arg);
        if( who && living(who) && me!=who )
        	tell_object(who,me->name()+"正盯着你身上的"+obj->name()+"左瞧右看，不知在打什么主意。\n");
	return 1;
}

string look_room_map(object me,object env)
{
	int idx;
	string msg,map_file,file;
	if( !me || !userp(me) || !living(me) 
	 || !env || env->is_character() )
		return 0;
	file = base_name(env);
	idx = strsrch(file, "/", -1);
	file = file[0..idx-1];
	map_file = file+= "/map";
	if( file_size(map_file)<0 )
		return 0;
	if( stringp(msg = read_file(map_file)) )
		return msg;
	return 0;	
}

int look_room(object me, object env)
{
	int i;
	object *inv;
	mapping exits;
	string long,str, str1="", *dirs,map_str;
	string ridemsg = "";

	if( !env ) 
        {
        	write("你的四周灰蒙蒙地一片，什么也没有。\n");
        	return 1;
        }
	if( env->is_home() )   
		return look_home(me,env);
	if( stringp(str=env->long()) && !env->is_character() )
        {
        	write(str);
        	return 1;
        } 
        long = env->query("long");
        if( !long )
        	long = "\n";
        else
        {
        	long = replace_string(long,"\n","");
        	long = replace_string(long,"    ","\n    ");
        	long = "    "+long;
        	long = sort_string(long,76,0); 
        }
        if( env->query("long2") )
        	long+= env->query("long2");
	str = sprintf( "%s  %s\n%s%s",
        	env->query("short")?(env->query("outdoors")?HIR"「"HIG+(string)env->query("short")+HIR"」"NOR:HIR"「"HIY+(string)env->query("short")+HIR"」"NOR): "",
        	wizardp(me)?HIW+" - "+file_name(env)+NOR: "",
        	long,
        	env->query("outdoors")? NATURE_D->outdoor_room_description() : "" );

	if( mapp(exits = env->query("exits")) ) 
        {
        	dirs = keys(exits);
        	for(i=0; i<sizeof(dirs); i++)
                	if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
                        	dirs[i] = 0;
        	dirs -= ({ 0 });
        	if( sizeof(dirs)==0 )
                	str += "    这里没有任何明显的出路。\n";
        	else if( sizeof(dirs)==1 )
                	str += "    这里唯一的出口是 " + BOLD + dirs[0] + NOR + "。\n";
        	else    str += sprintf("    这里明显的出口是 " + BOLD + "%s" + NOR + " 和 " + BOLD + "%s" + NOR + "。\n",
                                implode(dirs[0..sizeof(dirs)-2], "、"), dirs[sizeof(dirs)-1]);
        }
//   str += env->door_description();
	inv = all_inventory(env);
	i=sizeof(inv);
	while(i--) 
        {
        	if( !me->visible(inv[i]) ) 
        		continue;
        	if( inv[i]==me ) continue;
        	if( ridemsg = ride_suffix(inv[i]) )
                	str1 = "  " + inv[i]->short() + " <"+ridemsg +">\n"+str1;
        	else    str1 = "  " + inv[i]->short() + "\n"+str1;
        }
        str = str+str1;
        write(str);
	return 1;
}

int look_home(object me,object obj)
{
	string str;
	object *inv;
	int i;
	inv = all_inventory(obj);
	str = sprintf( "%s  %s\n    %s",
		obj->query("short")?(HIR"「"HIG+(string)obj->query("short")+HIR"」"NOR): "标准新房",
                wizardp(me)?HIW+" - "+file_name(obj)+NOR: "",
                obj->query("long")? obj->query("long"): "\n",
        );
	str+= "    房间的深处摆放着一榻"+sprintf("%s(bed)。\n",obj->query("bed_short")?obj->query("bed_short"):"新婚木床");       
	str+= NATURE_D->outdoor_room_description();
	str += "    这里唯一的出口是 " + BOLD + "out" + NOR + "。\n";

	for(i=0;i<sizeof(inv);i++)
        {
        	if( !me->visible(inv[i]) ) 
        		continue;
        	if( inv[i]==me ) 
        		continue;
        	if( inv[i]->name()==obj->query("bed_short") )
                	continue;
        	str+= "  " + inv[i]->short() + "\n";
        }
	me->start_more(str);
	return 1;
}

varargs int look_item(object me, object obj,int v)
{
	string str;
	object who;
	mixed *inv;
	
	if( !v )
	{
		if( obj->is_home() )  
			return look_home(me,obj);
		else if( obj->query("weapon_prop") || obj->is_weapon() )
			return look_weapon(me,obj);
		else if( obj->query("armor_prop") || obj->is_armor() )
			return look_armor(me,obj);
		else if( obj->is_book() )
			return look_book(me,obj);
	}				
	str = obj->long();
	str = sort_string(str,76,0); 		
	me->start_more(str);
	inv = all_inventory(obj);
	if( sizeof(inv) ) 
        {
        	inv = map_array(inv, "inventory_look", this_object() );
        	message("vision", sprintf("里面有：\n  %s\n",implode(inv, "\n  ") ), me);
        }
        who = environment(obj);
        if( who && living(who) && me!=who )
        	tell_object(who,me->name()+"正盯着你身上的"+obj->name()+"左瞧右看，不知在打什么主意。\n");
	return 1;
}

string pos_status_msg(object ob)
{ 
	string fam;
	int lvl;
	if( !ob || !living(ob) )	
		return 0;
	if( ob->query_condition() )
		return HIB "脸上隐隐泛出一股煞气。\n" NOR;	
	lvl = ob->query_level();
	if( lvl<10 )
	{
		if( (ob->query("food")*100/ob->max_food_capacity())<=30 )
			return YEL"神如木鸡，面有菜色。\n" NOR;
		if( (ob->query("water")*100/ob->max_water_capacity())<=30 )
			return YEL"口焦唇干，面带病色。\n" NOR;
	}
	if( lvl>=180 )
		return HIY "整个笼罩在"HIW"七"HIR"彩"HIM"祥"HIC"云"HIY"之中。\n" NOR;
	else if( lvl>=150 )
		return HIY "身边围绕着一朵祥云。\n" NOR;
	else if( lvl>=90 )
		return HIY "身上围绕着一团瑞气。\n" NOR;
	else
	{
		if( !fam=ob->query("family/family_name") )
			return HIY "脸上显出一股祥和之气。\n" NOR;
		if( fam=="南海普陀山" || ob->query("bonze/class") )
			return HIY"身后隐隐有梵呗之音。\n"NOR;
		if( fam=="盘丝洞" || fam=="大雪山"
		 || fam=="火云洞" || fam=="陷空山无底洞" )
		 	return HIB "整个笼罩在一团妖气之中。\n" NOR;
		 if( fam=="阎罗地府" )
		 	return HIB "身上围绕着一团黑云。\n" NOR;
		 if( fam=="百花谷" )
		 	return HIG"周身百花缭绕。\n"NOR;
		 if( fam=="月宫" )
		 	return HIC"背后隐隐有月华之光。\n"NOR;
		 if( fam=="蜀山派" )
		 	return HIY"背后隐约有金光攒动。\n"NOR;
		 if( fam=="散仙派" )
		 	return HIM"身形飘飘渺渺，摇曳不定。\n"NOR;
		 if( fam=="东海龙宫" )
		 	return HIG"身后隐约传出波声涛音。\n"NOR;
		 if( fam=="五庄观" )
		 	return HIY"背后隐约有金光翻滚，其内有八卦不断变幻。\n"NOR;
		 else	return HIY "脸上显出一股祥和之气。\n" NOR;		 				
	}
}

string per_status_msg(object who)
{
	int age,per,level;
	string gender;
	if( !who || !living(who) )
		return 0;
	gender = who->query("gender");	
	if( who->query("always_young") ) 
		age = who->query("fake_age");
	else	age = who->query("age");
	per = who->query_per();
	level = who->query_level();
	if( per<1 )
		per = 1;
	if( level<1 )
		level = 1;
	per = per*100/(40+level/2);
	if(age < 14) 
        {
        	if( per>=90 )
                	return ( per_msg_kid1[random(sizeof(per_msg_kid1))]);
        	else if( per>=70 )
                	return ( per_msg_kid2[random(sizeof(per_msg_kid2))]);
        	else if( per>=50 )
                	return ( per_msg_kid3[random(sizeof(per_msg_kid3))]);
        	else    return ( per_msg_kid4[random(sizeof(per_msg_kid4))]);
        }
        if( age>=50 )
        {
        	if( per>=90 )
        	{
        		if( who->query("class") && who->query("class")=="bonze" )
        			return ( per_msg_old11[random(sizeof(per_msg_old11))]);
                	else	return ( per_msg_old1[random(sizeof(per_msg_old1))]);
                }
        	else if( per>=70 )
        	{
        		if( who->query("class") && who->query("class")=="bonze" )
        			return ( per_msg_old11[random(sizeof(per_msg_old11))]);
                	else	return ( per_msg_old2[random(sizeof(per_msg_old2))]);
                }
        	else if( per>=50 )
                	return ( per_msg_old3[random(sizeof(per_msg_old3))]);
        	else    return ( per_msg_old4[random(sizeof(per_msg_old4))]);
        }
        
	if( gender == "女性" ) 
        {
        	if( per>=90 )
                	return ( per_msg_female1[random(sizeof(per_msg_female1))]);
        	else if( per>=70 )
                	return ( per_msg_female2[random(sizeof(per_msg_female2))]);
        	else if( per>=50)
                	return ( per_msg_female3[random(sizeof(per_msg_female3))]);
        	else   return ( per_msg_female4[random(sizeof(per_msg_female4))]);
        }
	else
        {
        	if( per>=90 )
                	return ( per_msg_male1[random(sizeof(per_msg_male1))]);
        	else if( per>=70 )
                	return ( per_msg_male2[random(sizeof(per_msg_male2))]);
        	else if( per>=50 )
                	return ( per_msg_male3[random(sizeof(per_msg_male3))]);
        	else    return ( per_msg_male4[random(sizeof(per_msg_male4))]);
        }
}
 
int look_living(object me, object obj)
{
	string str, limb_status, ridemsg, pro;
	mixed *inv;
	mapping my_fam, fam;
	mapping ofamily;
	string ogender,orace;
	int oage;

	if(obj->query_temp("d_mana")>0) 
        {
        	ofamily=obj->query_temp("family");
        	ogender=obj->query_temp("gender");
        	orace=obj->query_temp("race");
        	oage=obj->query_temp("age");
        } 
	else    
	{
        	ofamily=obj->query("family");
        	ogender=obj->query("gender");
        	orace=obj->query("race");
        	oage=obj->query("age");
        	if(obj->query("always_young") ) 
                	oage=obj->query("fake_age");
        }
	if( me!=obj && obj->visible(me) )
        	message("vision", HIW+me->name() + HIW"正盯着你看，不知道打些什么主意。\n"NOR, obj);
	str = obj->long();
	if( !str || !stringp(str) )  
		str = "";
	str = replace_string(str, "$n", me->name());
	str = replace_string(str, "$N", obj->name());
	str = replace_string(str, "$C", RANK_D->query_respect(obj));
	str = replace_string(str, "$c", RANK_D->query_rude(obj));
	str = replace_string(str, "$R", RANK_D->query_respect(me));
	str = replace_string(str, "$r", RANK_D->query_rude(me));
	//此处加入一个限制，这样一些特殊的NPC只会look到其特定的long()而不会加入其他了。 snowtu 2007
	if( obj->is_pet() )  
        {
        	me->start_more(str);
        	return 1;
        }
	pro = (obj==me) ? gender_self(ogender) : gender_pronoun(ogender);
	if(obj->query_temp("d_mana")==0 || obj->query_temp("is_character")) 
        {
        	if( orace=="人类" && intp(oage) )
        	{
                	if(oage<10) 
                		str += sprintf("%s看起来显然还不到十岁。\n", pro);
			else     
			{
                        	str += sprintf("%s看起来约%s多岁。\n", pro, chinese_number(oage / 10 * 10));
                        	if( obj!=me && RANK_D->gettof(me,obj) )
                        	{
                        		str += sprintf("%s的境界与你相比，似乎"NOR,pro);
                        		str += RANK_D->gettof(me,obj);
                        	}
				if( obj!=me && RANK_D->gettof2(me,obj) )
                        	{
                        		str += sprintf("，");
                        		str += sprintf("%s的实战经验与你相比，似乎"NOR,pro);
                        		str += RANK_D->gettof2(me,obj);
                        		str += sprintf("。\n"NOR);
                        	}
                        	else if( obj!=me )
                        		str+= NOR"。\n";                        		
                        }
			if((obj->parse_command_id_list())[0]==me->query("couple/id") ) 
                	{
                		if( (string)me->query("gender")=="女性" )
                        		str += sprintf("%s是你的丈夫。\n", pro);
                		else    str += sprintf("%s是你的妻子。\n", pro);
                	}
			if( obj!=me && mapp(fam = ofamily) 
         	         && mapp(my_fam = me->query("family")) && fam["family_name"]==my_fam["family_name"] ) 
                	{
                		if( fam["generation"]==my_fam["generation"] ) 
                        	{
                        		if( ogender == "男性" )
                                		str += sprintf( pro + "是你的%s%s。\n",my_fam["master_id"] == fam["master_id"] ? "": "同门",my_fam["enter_time"] > fam["enter_time"] ? "师兄": "师弟");
                        		else    str += sprintf( pro + "是你的%s%s。\n",my_fam["master_id"] == fam["master_id"] ? "": "同门",my_fam["enter_time"] > fam["enter_time"] ? "师姐": "师妹");
                        	} 
                		else if( fam["generation"] < my_fam["generation"] ) 
                        	{
                        		if( member_array(my_fam["master_id"],obj->parse_command_id_list())>-1 )
                                		str += pro + "是你的师父。\n";
                        		else if( my_fam["generation"] - fam["generation"] > 1 )
                                		str += pro + "是你的同门长辈。\n";
                        		else if( fam["enter_time"] < my_fam["enter_time"] )
                                		str += pro + "是你的师伯。\n";
                        		else    str += pro + "是你的师叔。\n";
                        	} 
                		else    
                		{
                        		if( fam["generation"] - my_fam["generation"] > 1 )
                                		str += pro + "是你的同门晚辈。\n";
                        		else if( fam["master_id"] == me->query("id") )
                                		str += pro + "是你的弟子。\n";
                        		else    str += pro + "是你的师侄。\n";
                        	}
                	}
                }	
        	if( obj->query("looking") )
                	str += pro + (string)obj->query("looking") + "\n";
        	else    
        	{
                	string looking = per_status_msg(obj);
                	if( looking && strlen(looking)>1)
                       		str += pro + looking;
                }
        	ridemsg = ride_suffix(obj);
        	if(ridemsg)
                	str += pro + "正" + ridemsg + "。\n";
        	str += pro + pos_status_msg(obj)+"\n";
        	inv = all_inventory(obj);
        	if( sizeof(inv) ) 
                {
                	inv = map_array(inv, "inventory_look", this_object(), obj->is_corpse()? 0 : 1 );
                	inv -= ({ 0 });
                	if( sizeof(inv) )
                       		str += sprintf( obj->is_corpse() ? "%s的遗物有：\n%s\n" : "%s身上带着：\n%s\n",pro, implode(inv, "\n") );
                }
        }
   	if( obj->query("look_msg") )   
   		str = (string)obj->query("look_msg");
	me->start_more(str);
	if( obj!=me && living(obj)
 	&& random((int)me->query_kar())<15 
 	&& obj->query("bellicosity")>0 )
        {
        	write( obj->name() + "突然转过头来瞪你一眼。\n");
        	COMBAT_D->auto_fight(obj, me, "berserk");
        	return 1;
        }
	return 1;
}

string inventory_look(object obj, int flag)
{
string str;
str = obj->short();
if( obj->query("equipped") )
        str = HIC "  □" NOR + str;
else if( !flag )
        str = "    " + str;
else    return 0;
return  str;
}

int look_room_item(object me, string arg)
{
object env;
mapping item, exits;
if( !objectp(env = environment(me)) )
        return notify_fail("这里只有灰蒙蒙地一片，什么也没有。\n");
if( mapp(item = env->query("item_desc")) && !undefinedp(item[arg]) ) 
        {
        if( stringp(item[arg]) )
                write(item[arg]);
        else if( functionp(item[arg]) )
                write((string)(*item[arg])(me));
        return 1;
        }
if( mapp(exits = env->query("exits")) && !undefinedp(exits[arg]) ) 
        {
        if( objectp(env = load_object(exits[arg])) )
                look_room(me, env);
        else    return notify_fail("你什么也看不见。\n");
        return 1;
        }
return notify_fail("你要看什么？\n");
}

varargs string mix_arg( string msg_one, string msg_two, int wi )
{
	string msg,t1,t2;
	string *field_one, *field_two;
	int max_line, i;
	
	if( msg_one=="" )
		return msg_two;
	else	field_one = explode(msg_one, "\n");
	if( msg_two=="" )
		return msg_one;
	else	field_two = explode(msg_two, "\n");
	max_line = (sizeof(field_one) > sizeof(field_two))?sizeof(field_one):sizeof(field_two);
	msg = "";
	for (i=0;i<max_line;i++)
	{
		if( i<sizeof(field_one) )
			msg+= field_one[i];
		if(  i<sizeof(field_two) )
		{
			if(  wi>0 && i>=sizeof(field_one) )
				msg += repeat_string(" ", wi);
			else if( wi>0 && (wi-strlen(COLOR_D->clean_color(field_one[i])))>0 )
				msg += repeat_string(" ", (wi-strlen(COLOR_D->clean_color(field_one[i]))));					
			msg += field_two[i];
		}
		msg += "\n";
	}
	return msg;
}

int help (object me)
{
write(
"\n	指令格式: look [<物品>|<生物>|<方向>]
这个指令让你查看你所在的环境、某件物品、生物、或是方向。
你可以通过描述看出目标的武功、修为。

	指令格式: look [<物品> in <对象>]
这个指令让你查看指定对象身上的装备。
\n\n"

);
return 1;
}
